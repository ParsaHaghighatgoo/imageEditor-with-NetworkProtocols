///////////////////////////////////////////
///INFO
///IMAGE PROCESSING WITH NETWORK PROTOCOLS
///C PROGRAMMING
///ALI SHARAFIAN & PARSA HAGHIGHATGOO
///PROFESSOR : DR. ALI HAMZEH
///SHIRAZ UNIVERSITY
///SEMESTER SPRING - 2023
///YOU CAN READ DOCUMENT OF THE CODE FOR INFORMATION AT ()
///FEEL FREE TO SEND YOUR OPINION FOR US (PARSAALI0002@GMAIL.COM)

///////////////////////////////////////////
///HEADERS AND DIFINES
#include "stdio.h"
#include "stdlib.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_image_resize.h"
#include <conio.h>
#include "curl.h"
#include <string.h>
#include "math.h"
#include <winsock2.h>
#include <ws2tcpip.h>


#define line_len 10000

#pragma comment(lib, "ws2_32.lib")

///////////////////////////////////////////
///EFFECTS FOR APPLYING ON THE PICTURES

//effect bmp
void rgb_to_hsv(int r, int g, int b, float *hsv) {
    float min_val = fminf(fminf(r, g), b);
    float max_val = fmaxf(fmaxf(r, g), b);
    float delta = max_val - min_val;

    hsv[2] = max_val / 255.0f;
    if (max_val == 0) {
        hsv[1] = 0;
    } else {
        hsv[1] = delta / max_val;
    }

    if (delta == 0) {
        hsv[0] = 0;
    } else if (max_val == r) {
        hsv[0] = 60.0f * fmodf((g - b) / delta, 6.0f);
    } else if (max_val == g) {
        hsv[0] = 60.0f * ((b - r) / delta + 2.0f);
    } else {
        hsv[0] = 60.0f * ((r - g) / delta + 4.0f);
    }
    if (hsv[0] < 0.0f) {
        hsv[0] += 360.0f;
    }
}

// helper function to convert HSV color values back to RGB color space
void hsv_to_rgb(float h, float s, float v, float *rgb) {
    if (s == 0) {
        rgb[0] = v * 255.0f;
        rgb[1] = v * 255.0f;
        rgb[2] = v * 255.0f;
    } else {
        h /= 60.0f;
        int i = (int) h;
        float f = h - i;
        float p = v * (1.0f - s);
        float q = v * (1.0f - s * f);
        float t = v * (1.0f - s * (1.0f - f));
        switch (i) {
            case 0:
                rgb[0] = v * 255.0f;
                rgb[1] = t * 255.0f;
                rgb[2] = p * 255.0f;
                break;
            case 1:
                rgb[0] = q * 255.0f;
                rgb[1] = v * 255.0f;
                rgb[2] = p * 255.0f;
                break;
            case 2:
                rgb[0] = p * 255.0f;
                rgb[1] = v * 255.0f;
                rgb[2] = t * 255.0f;
                break;
            case 3:
                rgb[0] = p * 255.0f;
                rgb[1] = q * 255.0f;
                rgb[2] = v * 255.0f;
                break;
            case 4:
                rgb[0] = t * 255.0f;
                rgb[1] = p * 255.0f;
                rgb[2] = v * 255.0f;
                break;
            default:
                rgb[0] = v * 255.0f;
                rgb[1] = p * 255.0f;
                rgb[2] = q * 255.0f;
                break;
        }
    }
}

void hue_bmp(unsigned char *image_data, int height, int row_size, float hue_shift) {
    // loop through each pixel in the image
    for (int y = 0; y < height; y++) {
        if (y < height / 3) {
            for (int x = 0; x < (row_size); x += 3) {
                // get the RGB color values of the current pixel
                int blue = image_data[y * row_size + x];
                int green = image_data[y * row_size + x + 1];
                int red = image_data[y * row_size + x + 2];

                // convert RGB color values to HSV color space
                float hsv[3];
                rgb_to_hsv(red, green, blue, hsv);

                // shift the Hue value
                hsv[0] += hue_shift;
                if (hsv[0] > 360.0f) {
                    hsv[0] -= 360.0f;
                } else if (hsv[0] < 0.0f) {
                    hsv[0] += 360.0f;
                }
                float rgb[3];
                // convert HSV color values back to RGB color space
                rgb[0] = 0.0f;
                rgb[1] = 0.0f;
                rgb[2] = 0.0f;
                hsv_to_rgb(hsv[0], hsv[1], hsv[2], rgb);

                // set the new RGB color values for the current pixel
                image_data[y * row_size + x] = (unsigned char) rgb[2];
                image_data[y * row_size + x + 1] = (unsigned char) rgb[1];
                image_data[y * row_size + x + 2] = (unsigned char) rgb[0];
            }
        }
    }
}

void solarize(unsigned char *image_data, int height, int row_size) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < row_size; j++) {
            if (image_data[i * row_size + j] < 128) {
                image_data[i * row_size + j] = 255 - image_data[i * row_size + j];
            }
        }
    }
}

void revert(unsigned char image_data[], int height, int row_size) {
    // apply effect to image data (example: invert colors)
    for (int i = 0; i < row_size * height; i++) {
        image_data[i] = 255 - image_data[i];
    }
}

void grayscale(unsigned char image_data[], int height, int row_size) {
    // apply grayscale effect to image data
    for (int i = 0; i < row_size * height; i += 3) {
        unsigned char red = image_data[i];
        unsigned char green = image_data[i + 1];
        unsigned char blue = image_data[i + 2];
        unsigned char gray = 0.299 * red + 0.587 * green + 0.114 * blue;
        image_data[i] = image_data[i + 1] = image_data[i + 2] = gray;
    }
}

void sepia(unsigned char image_data[], int height, int row_size) {
    // apply sepia effect to image data
    for (int i = 0; i < row_size * height; i += 3) {
        unsigned char red = image_data[i];
        unsigned char green = image_data[i + 1];
        unsigned char blue = image_data[i + 2];
        unsigned char sepia_red = (unsigned char) (0.393 * red + 0.769 * green + 0.189 * blue);
        unsigned char sepia_green = (unsigned char) (0.349 * red + 0.686 * green + 0.168 * blue);
        unsigned char sepia_blue = (unsigned char) (0.272 * red + 0.534 * green + 0.131 * blue);
        image_data[i] = sepia_red;
        image_data[i + 1] = sepia_green;
        image_data[i + 2] = sepia_blue;
    }
}

void brn(unsigned char *image_data, int height, int row_size) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < row_size; j++) {
            int r = image_data[i * row_size + j + 2];
            int g = image_data[i * row_size + j + 1];
            int b = image_data[i * row_size + j];
            int avg = (r + g + b) / 3;
            image_data[i * row_size + j + 2] = avg * 4;
            image_data[i * row_size + j + 1] = avg * 3;
            image_data[i * row_size + j] = avg * 2;
        }
    }
}

void off_grid(unsigned char *image_data, int height, int row_size) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < row_size; j++) {
            if ((i % 30 == 0) || (j % 50 == 0)) {
                image_data[i * row_size + j] = 0;
            }
        }
    }
}

void cybr(unsigned char *image_data, int height, int row_size) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < row_size; j++) {
            int r = image_data[i * row_size + j + 2];
            int g = image_data[i * row_size + j + 1];
            int b = image_data[i * row_size + j];
            int avg = (r + g + b) / 3;
            if (avg >= 128) {
                image_data[i * row_size + j + 2] = g;
                image_data[i * row_size + j + 1] = b;
                image_data[i * row_size + j] = r;
            } else {
                image_data[i * row_size + j + 2] = b;
                image_data[i * row_size + j + 1] = r;
                image_data[i * row_size + j] = g;
            }
        }
    }
}

void sharpen(unsigned char *image_data, int height, int row_size) {
    int kernel[3][3] = {{-1, -1, -1},
                        {-1, 9,  -1},
                        {-1, -1, -1}};
    unsigned char *temp_image_data = malloc(height * row_size * sizeof(unsigned char));
    memcpy(temp_image_data, image_data, height * row_size * sizeof(unsigned char));
    for (int i = 1; i < height - 1; i++) {
        for (int j = 3; j < row_size - 3; j++) {
            int sum_r = 0, sum_g = 0, sum_b = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    sum_r += temp_image_data[(i + k) * row_size + (j + l) + 2] * kernel[k + 1][l + 1];
                    sum_g += temp_image_data[(i + k) * row_size + (j + l) + 1] * kernel[k + 1][l + 1];
                    sum_b += temp_image_data[(i + k) * row_size + (j + l)] * kernel[k + 1][l + 1];
                }
            }
            image_data[i * row_size + j + 2] = (unsigned char) fmin(fmax(sum_r, 0), 255);
            image_data[i * row_size + j + 1] = (unsigned char) fmin(fmax(sum_g, 0), 255);
            image_data[i * row_size + j] = (unsigned char) fmin(fmax(sum_b, 0), 255);
        }
    }
    free(temp_image_data);
}

void noise(unsigned char *image_data, int height, int row_size) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < row_size; j++) {
            int noise = rand() % 51 - 25;
            int r = image_data[i * row_size + j + 2];
            int g = image_data[i * row_size + j + 1];
            int b = image_data[i * row_size + j];
            image_data[i * row_size + j + 2] = (unsigned char) fmin(fmax(r + noise, 0), 255);
            image_data[i * row_size + j + 1] = (unsigned char) fmin(fmax(g + noise, 0), 255);
            image_data[i * row_size + j] = (unsigned char) fmin(fmax(b + noise, 0), 255);
        }
    }
}

void vin4(unsigned char *image_data, int height, int row_size) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < row_size; j++) {
            int r = image_data[i * row_size + j + 2];
            int g = image_data[i * row_size + j + 1];
            int b = image_data[i * row_size + j];
            image_data[i * row_size + j + 2] = (unsigned char) fmin(fmax((r - g - b) * 3, 0), 255);
            image_data[i * row_size + j + 1] = (unsigned char) fmin(fmax((g - r - b) * 3, 0), 255);
            image_data[i * row_size + j] = (unsigned char) fmin(fmax((b - r - g) * 3, 0), 255);
        }
    }
}

void warm_color(unsigned char *image_data, int height, int row_size) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < row_size; j++) {
            int b = image_data[i * row_size + j];
            int g = image_data[i * row_size + j + 1];
            int r = image_data[i * row_size + j + 2];
            image_data[i * row_size + j + 2] = (unsigned char) fmin(fmax(r + 50, 0), 255);
            image_data[i * row_size + j + 1] = (unsigned char) fmin(fmax(g + 30, 0), 255);
            image_data[i * row_size + j] = (unsigned char) fmin(fmax(b, 0), 255);
        }
    }
}

void oilPainting(unsigned char *image_data, int height, int row_size) {
    unsigned char *temp_data = malloc(row_size * height * sizeof(unsigned char));
    memcpy(temp_data, image_data, row_size * height * sizeof(unsigned char));
    int radius = 3;
    int intensityLevels = 16;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < row_size; j += 3) {
            int sumR[intensityLevels], sumG[intensityLevels], sumB[intensityLevels], count[intensityLevels];
            for (int k = 0; k < intensityLevels; k++) {
                sumR[k] = 0;
                sumG[k] = 0;
                sumB[k] = 0;
                count[k] = 0;
            }
            for (int k = i - radius; k <= i + radius; k++) {
                for (int l = j - 3 * radius; l <= j + 3 * radius; l += 3) {
                    if (k >= 0 && k < height && l >= 0 && l < row_size) {
                        unsigned char r = temp_data[k * row_size + l + 2];
                        unsigned char g = temp_data[k * row_size + l + 1];
                        unsigned char b = temp_data[k * row_size + l];
                        int intensity = (int) (0.299 * r + 0.587 * g + 0.114 * b) * intensityLevels / 256;
                        sumR[intensity] += r;
                        sumG[intensity] += g;
                        sumB[intensity] += b;
                        count[intensity]++;
                    }
                }
            }
            int maxCount = 0, maxIntensity = 0;
            for (int k = 0; k < intensityLevels; k++) {
                if (count[k] > maxCount) {
                    maxCount = count[k];
                    maxIntensity = k;
                }
            }
            image_data[i * row_size + j + 2] = (unsigned char) (sumR[maxIntensity] / count[maxIntensity]);
            image_data[i * row_size + j + 1] = (unsigned char) (sumG[maxIntensity] / count[maxIntensity]);
            image_data[i * row_size + j] = (unsigned char) (sumB[maxIntensity] / count[maxIntensity]);
        }
    }
    free(temp_data);
}

void motionBlur(unsigned char *image_data, int height, int row_size) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < row_size; j += 3) {
            int sumR = 0, sumG = 0, sumB = 0, count = 0;
            for (int k = j; k < row_size && k < j + 30; k += 3) {
                if (k < row_size) {
                    sumR += image_data[i * row_size + k + 2];
                    sumG += image_data[i * row_size + k + 1];
                    sumB += image_data[i * row_size + k];
                    count++;
                }
            }
            if (count > 0) {
                image_data[i * row_size + j + 2] = (unsigned char) (sumR / count);
                image_data[i * row_size + j + 1] = (unsigned char) (sumG / count);
                image_data[i * row_size + j] = (unsigned char) (sumB / count);
            }
        }
    }
}

void cross(unsigned char *image_data, int height, int row_size) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < row_size; j += 3) {
            if (i % 2 == 0 && j % 6 == 0) {
                unsigned char r = image_data[i * row_size + j + 2];
                unsigned char g = image_data[i * row_size + j + 1];
                unsigned char b = image_data[i * row_size + j];
                unsigned char gray = (unsigned char) (0.299 * r + 0.587 * g + 0.114 * b);
                image_data[i * row_size + j + 2] = gray;
                image_data[i * row_size + j + 1] = gray;
                image_data[i * row_size + j] = gray;
            }
        }
    }
}

void neon(unsigned char *image_data, int height, int row_size, int intensity) {
    // loop through all pixels in image
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < row_size; x += 3) {
            // get RGB values of current pixel
            unsigned char blue = image_data[y * row_size + x];
            unsigned char green = image_data[y * row_size + x + 1];
            unsigned char red = image_data[y * row_size + x + 2];

            // calculate neon RGB values
            int neon_blue = (intensity * 255 + blue * (255 - intensity)) / 255;
            int neon_green = (intensity * 255 + green * (255 - intensity)) / 255;
            int neon_red = (intensity * 255 + red * (255 - intensity)) / 255;

            // set new RGB values for current pixel
            image_data[y * row_size + x] = neon_blue;
            image_data[y * row_size + x + 1] = neon_green;
            image_data[y * row_size + x + 2] = neon_red;
        }
    }
}

void comic(unsigned char *image_data, int height, int row_size, int threshold) {
    // loop through all pixels in image
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < row_size; x += 3) {
            // get RGB values of current pixel
            unsigned char blue = image_data[y * row_size + x];
            unsigned char green = image_data[y * row_size + x + 1];
            unsigned char red = image_data[y * row_size + x + 2];

            // calculate average color value of current pixel
            int avg = (red + green + blue) / 3;

            // set color of current pixel to black or white depending on average color value
            if (avg >= threshold) {
                image_data[y * row_size + x] = 255;
                image_data[y * row_size + x + 1] = 255;
                image_data[y * row_size + x + 2] = 255;
            } else {
                image_data[y * row_size + x] = 0;
                image_data[y * row_size + x + 1] = 0;
                image_data[y * row_size + x + 2] = 0;
            }
        }
    }
}

void watercolor(unsigned char *image_data, int height, int row_size, int brush_size) {
    // create copy of image data to use as source for watercolor effect
    unsigned char *source_data = malloc(row_size * height * sizeof(unsigned char));
    memcpy(source_data, image_data, row_size * height * sizeof(unsigned char));

    // loop through all pixels in image
    for (int y = brush_size; y < height - brush_size; y++) {
        for (int x = brush_size; x < row_size - brush_size; x += 3) {
            // initialize color accumulator for current pixel
            int blue = 0;
            int green = 0;
            int red = 0;
            int count = 0;

            // loop through all pixels within brush size of current pixel
            for (int dy = -brush_size; dy <= brush_size; dy++) {
                for (int dx = -brush_size; dx <= brush_size; dx += 3) {
                    // calculate coordinates of current pixel within brush
                    int brush_x = x + dx;
                    int brush_y = y + dy;

                    // get color of current pixel within brush
                    int index = brush_y * row_size + brush_x;
                    blue += source_data[index];
                    green += source_data[index + 1];
                    red += source_data[index + 2];
                    count++;
                }
            }

            // calculate average color of all pixels within brush
            int avg_blue = blue / count;
            int avg_green = green / count;
            int avg_red = red / count;

            // set color of current pixel to average color
            image_data[y * row_size + x] = avg_blue;
            image_data[y * row_size + x + 1] = avg_green;
            image_data[y * row_size + x + 2] = avg_red;
        }
    }

    // free memory used by source data
    free(source_data);
}

void polygon(unsigned char *image_data, int height, int row_size, int sides) {
    // calculate radius of polygon
    int radius = height / 4;

    // calculate center point of image
    int center_x = row_size / 2;
    int center_y = height / 2;

    // loop through all pixels in image
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < row_size; x += 3) {
            // calculate distance from current pixel to center point
            int dist_x = x - center_x;
            int dist_y = y - center_y;
            int distance = sqrt(dist_x * dist_x + dist_y * dist_y);

            // check if current pixel is within radius of polygon
            if (distance < radius) {
                // calculate angle of current pixel relative to center point
                double angle = atan2(dist_y, dist_x);

                // calculate index of vertex that current pixel is closest to
                int index = (int) round(sides * angle / (2 * M_PI) + sides) % sides;

                // set color of current pixel to color of vertex
                int vertex_x = center_x + radius * cos(index * 2 * M_PI / sides);
                int vertex_y = center_y + radius * sin(index * 2 * M_PI / sides);
                int vertex_index = vertex_y * row_size + vertex_x * 3;
                image_data[y * row_size + x] = image_data[vertex_index];
                image_data[y * row_size + x + 1] = image_data[vertex_index + 1];
                image_data[y * row_size + x + 2] = image_data[vertex_index + 2];
            }
        }
    }
}

void mirror(unsigned char *image_data, int height, int row_size) {
    int row, col;
    unsigned char temp;

    for (row = 0; row < height; row++) {
        for (col = 0; col < row_size / 2; col++) {
            // swap pixels across the vertical center line of the image
            temp = image_data[row * row_size + col];
            image_data[row * row_size + col] = image_data[(row + 1) * row_size - col - 1];
            image_data[(row + 1) * row_size - col - 1] = temp;
        }
    }
}

//-----------------------------------------
//png and jpg effects

void hue_png_jpg(unsigned char *image_data, int width, int height, int channels, float hue_shift) {
    // loop through each pixel in the image
    for (int i = 0; i < (width * height * channels); i += channels) {
        // get the RGB color values of the current pixel
        int red = image_data[i];
        int green = image_data[i + 1];
        int blue = image_data[i + 2];

        // convert RGB color values to HSV color space
        float hsv[3];
        rgb_to_hsv(red, green, blue, hsv);

        // shift the Hue value
        hsv[0] += hue_shift;
        if (hsv[0] > 360.0f) {
            hsv[0] -= 360.0f;
        } else if (hsv[0] < 0.0f) {
            hsv[0] += 360.0f;
        }

        // convert HSV color values back to RGB color space
        float rgb[3];
        hsv_to_rgb(hsv[0], hsv[1], hsv[2], rgb);

        // set the new RGB color values for the current pixel
        image_data[i] = (unsigned char) rgb[0];
        image_data[i + 1] = (unsigned char) rgb[1];
        image_data[i + 2] = (unsigned char) rgb[2];
    }
}

void solarize_png_jpg(unsigned char *image_data, int width, int height, int channels, int threshold) {
    int i;
    for (i = 0; i < width * height * channels; i++) {
        if (image_data[i] < threshold) {
            image_data[i] = 255 - image_data[i];
        }
    }
}

void revert_png_jpg(unsigned char *image_data, int width, int height, int channels) {
    int i;
    for (i = 0; i < width * height * channels; i++) {
        image_data[i] = 255 - image_data[i];
    }
}

void grayscale_png_jpg(unsigned char *image_data, int width, int height, int channels) {
    int i;
    for (i = 0; i < width * height * channels; i += channels) {
        unsigned char gray_value = (image_data[i] + image_data[i + 1] + image_data[i + 2]) / 3;
        image_data[i] = gray_value;
        image_data[i + 1] = gray_value;
        image_data[i + 2] = gray_value;
    }
}

void sepia_png_jpg(unsigned char *image_data, int width, int height, int channels) {
    int i;
    for (i = 0; i < width * height * channels; i += channels) {
        unsigned char r = image_data[i];
        unsigned char g = image_data[i + 1];
        unsigned char b = image_data[i + 2];
        image_data[i] = (unsigned char) min(0.393 * r + 0.769 * g + 0.189 * b, 255);
        image_data[i + 1] = (unsigned char) min(0.349 * r + 0.686 * g + 0.168 * b, 255);
        image_data[i + 2] = (unsigned char) min(0.272 * r + 0.534 * g + 0.131 * b, 255);
    }
}

void brn_png_jpg(unsigned char *image_data, int width, int height, int channels, int brightness, float contrast) {
    int i;
    float contrast_factor = (259 * (contrast + 255)) / (255 * (259 - contrast));

    for (i = 0; i < width * height * channels; i++) {
        int value = ((int) image_data[i] - 128) * contrast_factor + 128 + brightness;
        image_data[i] = (unsigned char) max(min(value, 255), 0);
    }
}

void offgrid_png_jpg(unsigned char *image_data, int width, int height, int channels, int grid_size) {
    int i, j, k;
    for (i = 0; i < height; i += grid_size) {
        for (j = 0; j < width; j += grid_size) {
            // compute average color of grid
            int r_sum = 0, g_sum = 0, b_sum = 0, count = 0;
            for (k = 0; k < grid_size && i + k < height; k++) {
                for (int l = 0; l < grid_size && j + l < width; l++) {
                    int idx = ((i + k) * width + j + l) * channels;
                    r_sum += image_data[idx];
                    g_sum += image_data[idx + 1];
                    b_sum += image_data[idx + 2];
                    count++;
                }
            }
            unsigned char r_avg = (unsigned char) (r_sum / count);
            unsigned char g_avg = (unsigned char) (g_sum / count);
            unsigned char b_avg = (unsigned char) (b_sum / count);

            // set all pixels in grid to average color
            for (k = 0; k < grid_size && i + k < height; k++) {
                for (int l = 0; l < grid_size && j + l < width; l++) {
                    int idx = ((i + k) * width + j + l) * channels;
                    image_data[idx] = r_avg;
                    image_data[idx + 1] = g_avg;
                    image_data[idx + 2] = b_avg;
                }
            }
        }
    }
}

void cybr_png_jpg(unsigned char *image_data, int width, int height, int channels) {
    int i;
    for (i = 0; i < width * height * channels; i += channels) {
        image_data[i] = (image_data[i] + image_data[i + 1] + image_data[i + 2]) / 3;
        image_data[i + 2] = (unsigned char) max(image_data[i + 2] * 3, 255);
    }
}

void sharpen_png_jpg(unsigned char *image_data, int width, int height, int channels) {
    int i, j, k, l;
    int kernel[3][3] = {
            {-1, -1, -1},
            {-1, 9,  -1},
            {-1, -1, -1}
    };
    unsigned char *new_image_data = (unsigned char *) malloc(width * height * channels * sizeof(unsigned char));
    memset(new_image_data, 5, width * height * channels * sizeof(unsigned char));

    for (i = 1; i < height - 1; i++) {
        for (j = 1; j < width - 1; j++) {
            for (k = 0; k < 3; k++) {
                for (l = 0; l < 3; l++) {
                    int idx = ((i + k - 1) * width + j + l - 1) * channels;
                    new_image_data[idx] += image_data[(i * width + j) * channels + k] * kernel[k][l];
                }
            }
        }
    }

    for (i = 0; i < height * width * channels; i++) {
        image_data[i] = (unsigned char) max(min(new_image_data[i], 255), 0);
    }

    free(new_image_data);
}

void noise_png_jpg(unsigned char *image_data, int width, int height, int channels, int amount) {
    int i, j, k;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            for (k = 0; k < channels; k++) {
                int rand_val = rand() % (2 * amount + 1) - amount;
                int idx = (i * width + j) * channels + k;
                image_data[idx] = (unsigned char) max(min(image_data[idx] + rand_val, 255), 0);
            }
        }
    }
}

void vin4_png_jpg(unsigned char *image_data, int width, int height, int channels, float strength) {
    int i, j, k;
    float x_center = width / 2.0f;
    float y_center = height / 2.0f;
    float max_radius = sqrt(x_center * x_center + y_center * y_center);

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            float x_dist = j - x_center;
            float y_dist = i - y_center;
            float radius = sqrt(x_dist * x_dist + y_dist * y_dist) / max_radius;
            float multiplier = 1.0f - (radius * strength);

            for (k = 0; k < channels; k++) {
                int idx = (i * width + j) * channels + k;
                image_data[idx] = (unsigned char) max(min(image_data[idx] * multiplier, 255), 0);
            }
        }
    }
}

void warm_color_png_jpg(unsigned char *image_data, int width, int height, int channels, int amount) {
    int i, j, k;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            for (k = 0; k < channels; k++) {
                int idx = (i * width + j) * channels + k;
                int new_val = image_data[idx] + amount;
                image_data[idx] = (unsigned char) max(min(new_val, 255), 0);
            }
        }
    }
}

void oilPainting_png_jpg(unsigned char *image_data, int width, int height, int channels, int radius, int levels) {
    int i, j, k;
    int histogram[256];
    memset(histogram, 0, 256 * sizeof(int));

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            int pixel_idx = (i * width + j) * channels;
            int color_idx = 0;
            int max_count = 0;

            // compute histogram for each channel within the given radius
            for (k = 0; k < channels; k++) {
                memset(histogram, 0, 256 * sizeof(int));
                int l, m;

                for (l = -radius; l <= radius; l++) {
                    for (m = -radius; m <= radius; m++) {
                        int x = j + m;
                        int y = i + l;

                        if (x < 0 || y < 0 || x >= width || y >= height) {
                            continue;
                        }

                        int idx = (y * width + x) * channels + k;
                        histogram[image_data[idx]]++;
                    }
                }

                // find the most common color within the histogram
                for (l = 0; l < 256; l++) {
                    if (histogram[l] > max_count) {
                        max_count = histogram[l];
                        color_idx = l;
                    }
                }

                // assign the most common color to the pixel
                image_data[pixel_idx + k] = color_idx;
            }
        }
    }

    // apply the posterization effect by quantizing the colors to the specified number of levels
    if (levels > 1) {
        int interval = 256 / levels;
        for (i = 0; i < height * width * channels; i++) {
            image_data[i] = (unsigned char) (interval * (image_data[i] / interval));
        }
    }
}

void motion_blur_png_jpg(unsigned char *image_data, int width, int height, int channels, int amount) {
    int i, j, k;
    int half_amount = amount / 2;
    unsigned char *new_image_data = (unsigned char *) malloc(width * height * channels * sizeof(unsigned char));
    memset(new_image_data, 0, width * height * channels * sizeof(unsigned char));

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            for (k = 0; k < channels; k++) {
                int sum = 0, count = 0;
                int l;

                for (l = -half_amount; l <= half_amount; l++) {
                    int x = j + l;
                    if (x < 0 || x >= width) {
                        continue;
                    }

                    int idx = (i * width + x) * channels + k;
                    sum += image_data[idx];
                    count++;
                }

                int new_val = sum / count;
                int idx = (i * width + j) * channels + k;
                new_image_data[idx] = (unsigned char) max(min(new_val, 255), 0);
            }
        }
    }

    memcpy(image_data, new_image_data, width * height * channels * sizeof(unsigned char));
    free(new_image_data);
}

void cross_png_jpg(unsigned char *image_data, int width, int height, int channels) {
    int i, j, k;
    unsigned char *new_image_data = (unsigned char *) malloc(width * height * channels * sizeof(unsigned char));
    memset(new_image_data, 0, width * height * channels * sizeof(unsigned char));

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            int idx = (i * width + j) * channels;
            if (i == height / 2 || j == width / 2) {
                for (k = 0; k < channels; k++) {
                    new_image_data[idx + k] = 255 - image_data[idx + k];
                }
            } else {
                memcpy(new_image_data + idx, image_data + idx, channels * sizeof(unsigned char));
            }
        }
    }

    memcpy(image_data, new_image_data, width * height * channels * sizeof(unsigned char));
    free(new_image_data);
}

void neon_png_jpg(unsigned char *image_data, int width, int height, int channels, int threshold) {
    int i, j, k;
    unsigned char *new_image_data = (unsigned char *) malloc(width * height * channels * sizeof(unsigned char));
    memset(new_image_data, 0, width * height * channels * sizeof(unsigned char));

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            int idx = (i * width + j) * channels;
            for (k = 0; k < channels; k++) {
                if (image_data[idx + k] > threshold) {
                    new_image_data[idx + k] = 255;
                } else {
                    new_image_data[idx + k] = image_data[idx + k];
                }
            }
        }
    }

    memcpy(image_data, new_image_data, width * height * channels * sizeof(unsigned char));
    free(new_image_data);
}

void polygon_png_jpg(unsigned char *image_data, int width, int height, int channels, int sides) {
    int i, j, k;
    unsigned char *new_image_data = (unsigned char *) malloc(width * height * channels * sizeof(unsigned char));
    memset(new_image_data, 0, width * height * channels * sizeof(unsigned char));

    // Compute center of image
    int center_x = width / 2;
    int center_y = height / 2;

    // Compute radius of inscribed circle
    int radius = min(center_x, center_y);

    // Compute angle between adjacent vertices
    double angle = 2 * M_PI / sides;

    // Iterate over each pixel in the image
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            int idx = (i * width + j) * channels;

            // Compute distance to center of image
            int dx = j - center_x;
            int dy = i - center_y;
            int dist = sqrt(dx * dx + dy * dy);

            // Compute angle of pixel relative to center of image
            double pixel_angle = atan2(dy, dx);

            // Compute index of nearest polygon vertex
            int vertex_index = floor((pixel_angle + M_PI) / angle);

            // Compute angle of nearest polygon vertex
            double vertex_angle = vertex_index * angle - M_PI;

            // Compute distance to nearest polygon vertex
            int vertex_dist = radius;

            // If pixel is inside polygon, set value to white
            if (dist <= vertex_dist) {
                for (k = 0; k < channels; k++) {
                    new_image_data[idx + k] = 255;
                }
            } else {
                memcpy(new_image_data + idx, image_data + idx, channels * sizeof(unsigned char));
            }
        }
    }

    memcpy(image_data, new_image_data, width * height * channels * sizeof(unsigned char));
    free(new_image_data);
}

void watercolor_png_jpg(unsigned char *image_data, int width, int height, int channels, int radius) {
    int i, j, k;
    unsigned char *new_image_data = (unsigned char *) malloc(width * height * channels * sizeof(unsigned char));
    memset(new_image_data, 0, width * height * channels * sizeof(unsigned char));

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            int idx = (i * width + j) * channels;

            int sum_r = 0, sum_g = 0, sum_b = 0, count = 0;
            int l, m;

            for (l = -radius; l <= radius; l++) {
                int y = i + l;
                if (y < 0 || y >= height) {
                    continue;
                }

                for (m = -radius; m <= radius; m++) {
                    int x = j + m;
                    if (x < 0 || x >= width) {
                        continue;
                    }

                    int idx2 = (y * width + x) * channels;
                    sum_r += image_data[idx2];
                    sum_g += image_data[idx2 + 1];
                    sum_b += image_data[idx2 + 2];
                    count++;
                }
            }

            int new_r = sum_r / count;
            int new_g = sum_g / count;
            int new_b = sum_b / count;

            new_image_data[idx] = (unsigned char) max(min(new_r, 255), 0);
            new_image_data[idx + 1] = (unsigned char) max(min(new_g, 255), 0);
            new_image_data[idx + 2] = (unsigned char) max(min(new_b, 255), 0);
        }
    }

    memcpy(image_data, new_image_data, width * height * channels * sizeof(unsigned char));
    free(new_image_data);
}

void comic_png_jpg(unsigned char *image_data, int width, int height, int channels) {
    int i, j, k;
    unsigned char *new_image_data = (unsigned char *) malloc(width * height * channels * sizeof(unsigned char));
    memset(new_image_data, 0, width * height * channels * sizeof(unsigned char));

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            int idx = (i * width + j) * channels;

            // Compute luminance of pixel
            int r = image_data[idx];
            int g = image_data[idx + 1];
            int b = image_data[idx + 2];
            int luminance = (r * 299 + g * 587 + b * 114) / 1000;

            // Apply threshold to luminance
            int threshold = 128;
            int new_val = luminance > threshold ? 255 : 0;

            // Set new pixel value
            for (k = 0; k < channels; k++) {
                new_image_data[idx + k] = (unsigned char) new_val;
            }
        }
    }

    memcpy(image_data, new_image_data, width * height * channels * sizeof(unsigned char));
    free(new_image_data);
}

void mirror_png_jpg(unsigned char *image_data, int width, int height, int channels) {
    int i, j, k;
    unsigned char *new_image_data = (unsigned char *) malloc(width * height * channels * sizeof(unsigned char));
    memset(new_image_data, 0, width * height * channels * sizeof(unsigned char));

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            int idx = (i * width + j) * channels;
            int mirror_idx = (i * width + (width - j - 1)) * channels;
            memcpy(new_image_data + mirror_idx, image_data + idx, channels * sizeof(unsigned char));
        }
    }

    memcpy(image_data, new_image_data, width * height * channels * sizeof(unsigned char));
    free(new_image_data);
}

///////////////////////////////////////////
///URL SECTION

//URL WITH SOCKET
void dlfromsocket() {
    WSADATA wsaData;
    SOCKET sock;
    struct addrinfo hints, *res;
    char request[1024];
    int bytesReceived, totalBytesReceived;
    FILE *fp;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return;
    }

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Error creating socket\n");
        WSACleanup();
        return;
    }

    // Resolve URL to IP address
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo("www.cs.sjsu.edu", "80", &hints, &res) != 0) {
        printf("Error resolving URL\n");
        closesocket(sock);
        WSACleanup();
        return;
    }

    // Connect to server
    if (connect(sock, res->ai_addr, res->ai_addrlen) == SOCKET_ERROR) {
        printf("Error connecting to server\n");
        freeaddrinfo(res);
        closesocket(sock);
        WSACleanup();
        return;
    }

    // Send HTTP GET request
    sprintf(request,
            "GET /~pearce/modules/lectures/web/html/HTTP_files/image001.jpg HTTP/1.1\r\nHost:www.cs.sjsu.edu\r\n\r\n");
    send(sock, request, strlen(request), 0);

    // Receive response
    totalBytesReceived = 0;
    fp = fopen("./tempsocket.txt", "wb");
    while ((bytesReceived = recv(sock, request, sizeof(request), 0)) > 0) {
        fwrite(request, 1, bytesReceived, fp);
        totalBytesReceived += bytesReceived;
        printf("%c", bytesReceived);
    }


    // Clean up
    freeaddrinfo(res);
    closesocket(sock);
    WSACleanup();
    fclose(fp);

    printf("Downloaded %d bytes\n", totalBytesReceived);
    return;
}

void cuttheencodedtxtofimagefromdltxt() {
    FILE *fs, *fn;
    fs = fopen("C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\tempsocket.txt", "rb");
    if (fs == NULL) {
        printf("\nError in Opening the dledtxt file");
        getch();
        return;
    }
    fn = fopen("C:\\project\\fetch\\tempcutsocket.txt", "w");
    if (fn == NULL) {
        printf("\nError in Opening the encodedtxtofimage file");
        getch();
        return;
    }
    char c;
    int count = 0, flag = 0;
    while (1) {
        if (feof(fs)) {
            break;
        }
        c = fgetc(fs);
        if (c == '\n') {
            count++;
            if (count == 2) {
                flag = 1;
                break;
            }
        } else {
            count = 0;
        }
    }
    int i = 0;
    while (flag) {
        if (feof(fs)) {
            break;
        }
        c = fgetc(fs);
        fputc(c, fn);
        i++;
        if (i == 274) {
            continue;
        }
    }
    fclose(fs);
    fclose(fn);
    printf("cut done!\n");
    return;
}

void urlwithsocket() {
    dlfromsocket();
    cuttheencodedtxtofimagefromdltxt();
    return;
}

//-------------------------------------------------------------------------------------------------------------------
void bmp(char input[]) {
    {
        FILE *bmp_file = fopen(input,"rb"); // open BMP file in binary mode
        if (bmp_file == NULL) {
            printf("Error: could not open BMP file.\n");
            return;
        }

        // read BMP file header
        unsigned char header[54];
        fread(header, sizeof(unsigned char), 54, bmp_file);

        // get image width, height, and bit depth from BMP file header
        int width = *(int *) &header[18];
        int height = *(int *) &header[22];
        int bit_depth = *(int *) &header[28];

        // read color table (if any) from BMP file
        if (bit_depth <= 8) {
            int color_table_size = 4 * (1 << bit_depth);
            unsigned char color_table[color_table_size];
            fread(color_table, sizeof(unsigned char), color_table_size, bmp_file);
        }

        // read image data from BMP file
        int row_size = ((width * bit_depth + 31) / 32) * 4;
        unsigned char *image_data = malloc((row_size * height) * sizeof(unsigned char));
        fread(image_data, sizeof(unsigned char), row_size * height, bmp_file);

        // close BMP file
        fclose(bmp_file);
        printf("\nplease choose your effect:\n1.hue\n2.solarize\n3.revert\n4.grayscale\n5.sepia\n6.brn\n7.off grid\n8.cybr\n9.sharpen\n10.noise\n11.vin4\n");
        printf("12.warm color\n13.oil painting\n14.motion blur\n15.cross\n16.neon\n17.comic\n18.water color\n19.polygon\n20.mirror\n");
        int c, i = 0;
        for (; (c = getchar()) != '\n';) {
            i = i * 10;
            i = i + (c - '0');
        }
        if (i == 1) {
            hue_bmp(image_data, height, row_size, 30.0f);
        } else if (i == 2) {
            solarize(image_data, height, row_size);
        } else if (i == 3) {
            revert(image_data, height, row_size);
        } else if (i == 4) {
            grayscale(image_data, height, row_size);
        } else if (i == 5) {
            sepia(image_data, height, row_size);
        } else if (i == 6) {
            brn(image_data, height, row_size);
        } else if (i == 7) {
            off_grid(image_data, height, row_size);
        } else if (i == 8) {
            cybr(image_data, height, row_size);
        } else if (i == 9) {
            sharpen(image_data, height, row_size);
        } else if (i == 10) {
            noise(image_data, height, row_size);
        } else if (i == 11) {
            vin4(image_data, height, row_size);
        } else if (i == 12) {
            warm_color(image_data, height, row_size);
        } else if (i == 13) {
            oilPainting(image_data, height, row_size);
        } else if (i == 14) {
            motionBlur(image_data, height, row_size);
        } else if (i == 15) {
            cross(image_data, height, row_size);
        } else if (i == 16) {
            neon(image_data, height, row_size, 90);
        } else if (i == 17) {
            comic(image_data, height, row_size, 50);
        } else if (i == 18) {
            watercolor(image_data, height, row_size, 60);
        } else if (i == 19) {
            polygon(image_data, height, row_size, 5);
        } else if (i == 20) {
            mirror(image_data, height, row_size);
        }
        // read color table (if any) from BMP file
        int color_table_size = 0;
        unsigned char color_table[1024]; // maximum size of color table
        if (bit_depth <= 8) {
            color_table_size = 4 * (1 << bit_depth);
            fread(color_table, sizeof(unsigned char), color_table_size, bmp_file);
        }




        // open new BMP file in binary write mode
        FILE *new_bmp_file = fopen(
                "C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\bmpnew.bmp",
                "wb");
        if (new_bmp_file == NULL) {
            printf("Error: could not create new BMP file.\n");
            return;
        }

        // write BMP file header to new file
        fwrite(header, sizeof(unsigned char), 54, new_bmp_file);

        // write color table (if any) to new BMP file
        if (bit_depth <= 8) {
            int colorTableSize = 4 * (1 << bit_depth);
            fwrite(color_table, sizeof(unsigned char), colorTableSize, new_bmp_file);
        }

        // write modified image data to new BMP file
        fwrite(image_data, sizeof(unsigned char), row_size * height, new_bmp_file);

        // close new BMP file
        fclose(new_bmp_file);
        printf("new photo saved to : C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\newbmp.bmp ");
    }
}

void png(char input[]) {
    int width, height, channels;
    unsigned char *image_data = stbi_load(input, &width, &height, &channels, 0);
    if (image_data == NULL) {
        printf("Error: Could not load image\n");
        return;
    }

    printf("\nplease choose your effect:\n1.hue\n2.solarize\n3.revert\n4.grayscale\n5.sepia\n6.brn\n7.off grid\n8.cybr\n9.sharpen\n10.noise\n11.vin4\n");
    printf("12.warm color\n13.oil painting\n14.motion blur\n15.cross\n16.neon\n17.comic\n18.water color\n19.polygon\n20.mirror\n");
    int c, i = 0;
    for (; (c = getchar()) != '\n';) {
        i = i * 10;
        i = i + (c - '0');
    }
    if (i == 1) {
        hue_png_jpg(image_data, width, height, channels, 30.0f);
    } else if (i == 2) {
        solarize_png_jpg(image_data, width, height, channels, 30);
    } else if (i == 3) {
        revert_png_jpg(image_data, width, height, channels);
    } else if (i == 4) {
        grayscale_png_jpg(image_data, width, height, channels);
    } else if (i == 5) {
        sepia_png_jpg(image_data, width, height, channels);
    } else if (i == 6) {
        brn_png_jpg(image_data, width, height, channels, 25, 12.5f);
    } else if (i == 7) {
        offgrid_png_jpg(image_data, width, height, channels, 40);
    } else if (i == 8) {
        cybr_png_jpg(image_data, width, height, channels);
    } else if (i == 9) {
        sharpen_png_jpg(image_data, width, height, channels);
    } else if (i == 10) {
        noise_png_jpg(image_data, width, height, channels, 60);
    } else if (i == 11) {
        vin4_png_jpg(image_data, width, height, channels, 30);
    } else if (i == 12) {
        warm_color_png_jpg(image_data, width, height, channels, 50);
    } else if (i == 13) {
        oilPainting_png_jpg(image_data, width, height, channels, 20, 2);
    } else if (i == 14) {
        motion_blur_png_jpg(image_data, width, height, channels, 90);
    } else if (i == 15) {
        cross_png_jpg(image_data, width, height, channels);
    } else if (i == 16) {
        neon_png_jpg(image_data, width, height, channels, 40);
    } else if (i == 17) {
        comic_png_jpg(image_data, width, height, channels);
    } else if (i == 18) {
        watercolor_png_jpg(image_data, width, height, channels, 36);
    } else if (i == 19) {
        polygon_png_jpg(image_data, width, height, channels, 13);
    } else if (i == 20) {
        mirror_png_jpg(image_data, width, height, channels);
    }

    // Save the modified image
    stbi_write_png("C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\newpng.png", width,
                   height, channels, image_data, width * channels);

    // Free the image data
    stbi_image_free(image_data);
    printf("new photo saved to : C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\newpng.png");
}

void jpg(char input[]) {
    int width, height, channels;
    unsigned char *image_data = stbi_load(
            input, &width, &height,
            &channels, STBI_rgb);
    if (image_data == NULL) {
        printf("Error: Could not load image\n");
        return;
    }

    printf("\nplease choose your effect:\n1.hue\n2.solarize\n3.revert\n4.grayscale\n5.sepia\n6.brn\n7.off grid\n8.cybr\n9.sharpen\n10.noise\n11.vin4\n");
    printf("12.warm color\n13.oil painting\n14.motion blur\n15.cross\n16.neon\n17.comic\n18.water color\n19.polygon\n20.mirror\n");
    int c, i = 0;
    for (; (c = getchar()) != '\n';) {
        i = i * 10;
        i = i + (c - '0');
    }
    if (i == 1) {
        hue_png_jpg(image_data, width, height, channels, 30.0f);
    } else if (i == 2) {
        solarize_png_jpg(image_data, width, height, channels, 30);
    } else if (i == 3) {
        revert_png_jpg(image_data, width, height, channels);
    } else if (i == 4) {
        grayscale_png_jpg(image_data, width, height, channels);
    } else if (i == 5) {
        sepia_png_jpg(image_data, width, height, channels);
    } else if (i == 6) {
        brn_png_jpg(image_data, width, height, channels, 25, 12.5f);
    } else if (i == 7) {
        offgrid_png_jpg(image_data, width, height, channels, 40);
    } else if (i == 8) {
        cybr_png_jpg(image_data, width, height, channels);
    } else if (i == 9) {
        sharpen_png_jpg(image_data, width, height, channels);
    } else if (i == 10) {
        noise_png_jpg(image_data, width, height, channels, 60);
    } else if (i == 11) {
        vin4_png_jpg(image_data, width, height, channels, 30);
    } else if (i == 12) {
        warm_color_png_jpg(image_data, width, height, channels, 50);
    } else if (i == 13) {
        oilPainting_png_jpg(image_data, width, height, channels, 20, 2);
    } else if (i == 14) {
        motion_blur_png_jpg(image_data, width, height, channels, 40);
    } else if (i == 15) {
        cross_png_jpg(image_data, width, height, channels);
    } else if (i == 16) {
        neon_png_jpg(image_data, width, height, channels, 40);
    } else if (i == 17) {
        comic_png_jpg(image_data, width, height, channels);
    } else if (i == 18) {
        watercolor_png_jpg(image_data, width, height, channels, 36);
    } else if (i == 19) {
        polygon_png_jpg(image_data, width, height, channels, 13);
    } else if (i == 20) {
        mirror_png_jpg(image_data, width, height, channels);
    }

    // Save the modified image
    stbi_write_jpg("C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\newjpg.jpg", width,
                   height, channels, image_data, 100);

    // Free the image data
    stbi_image_free(image_data);
    printf("new photo saved to : C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\newjpg.jpg");
}

//-------------------------------------------------------------------------------------------------------------------

// Callback function to write attachment data to file
size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    FILE *file = (FILE *) userp;
    size_t written = fwrite(contents, size, nmemb, file);
    return written;
}

int uidplus() {
    char c;
    int uid = 0;
    FILE *file = fopen("C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\uid.txt", "r");
    while (1) {
        if (feof(file)) {
            break;
        }
        c = fgetc(file);
        if (c >= '0' && c <= '9') {
            uid = (uid * 10) + (c - '0');
        }
    }
    rewind(file);
    fclose(file);
    file = fopen("C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\uid.txt", "w");
    int i = uid + 1;
    fprintf(file, "%d", i);
    fclose(file);
    return uid;
}

int uidmines() {
    char c;
    int uid = 0;
    FILE *file = fopen("C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\uid.txt", "r");
    while (1) {
        if (feof(file)) {
            break;
        }
        c = fgetc(file);
        if (c >= '0' && c <= '9') {
            uid = (uid * 10) + (c - '0');
        }
    }
    rewind(file);
    fclose(file);
    file = fopen("C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\uid.txt", "w");
    int i = uid - 1;
    fprintf(file, "%d", i);
    fclose(file);
    return 0;
}

// fetch func for fetch email
void fetchemail() {
    //GMAIL DL PIC
    CURL *curl;
    CURLcode res;
    FILE *file;

    // Set up libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        // Set IMAP server and account details
        char email[] = "parsaali0002@gmail.com"; // Replace with your Gmail address
        char password[] = ":D"; // Replace with your Gmail password

        curl_easy_setopt(curl, CURLOPT_CAINFO,
                         "C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\cacert-2023-05-30.pem");

        // Set the mailbox name and UID
        char mailbox[] = "INBOX";
        int uid = 6;

        ///In this section u can add uid functions (plus or mines) for
        ///calling and getting uid from file for saving the uid and change it
        ///after each email


        // Create the URL with the UID
        char url[100];
        sprintf(url, "imaps://imap.gmail.com/%s;UID=%d", mailbox, uid);

        // Connect to the IMAP server and log in
        curl_easy_setopt(curl, CURLOPT_USERNAME, email);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Perform the fetch request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            printf("Failed to fetch email: %s\n", curl_easy_strerror(res));
            return;
        }

        // Open a file to save the fetched email
        file = fopen("C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\att.txt", "wb");
        if (!file) {
            printf("Error opening file for writing.");
            return;
        }

        // Set the write callback function to write data into the file
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        // Perform the fetch request and save the email content to the file
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            printf("Failed to fetch email: %s\n", curl_easy_strerror(res));
            return;
        }

        // Clean up and close the file
        fclose(file);

        // Clean up and close the IMAP session
        curl_easy_cleanup(curl);
    } else {
        printf("Error initializing libcurl.\n");
        return;
    }

    // Clean up libcurl
    curl_global_cleanup();

}

//writing decode fetched txt to a file
void finddecodetxt(const char *text, const char *outputFileName) {
    char check[16] = "X-Attachment-Id:";
    const char *decodetxtstart = strstr(text, check);
    if (decodetxtstart == NULL) {
        printf("there ins't exist fetch decode txt!\n");
        return;
    }

    decodetxtstart += strlen("X-Attachment-Id:");

    decodetxtstart = strstr(decodetxtstart, "\n\n");
    if (decodetxtstart == NULL) {
        printf("Invalid text format\n");
        return;
    }

    decodetxtstart += strlen("\n\n");

    const char *decodetxtend = strstr(decodetxtstart, "\n--");
    if (decodetxtend == NULL) {
        printf("Invalid text format. Base64 code end not found.\n");
        return;
    }

    size_t decodetxtlen = decodetxtend - decodetxtstart;
    char *decodetxt = (char *) malloc(decodetxtlen + 1);
    strncpy(decodetxt, decodetxtstart, decodetxtlen);
    decodetxt[decodetxtlen] = '\0';

    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Failed to open the decode txt file.\n");
        return;
    }

    fprintf(outputFile, "%s", decodetxt);
    fclose(outputFile);

    printf("image fetch txt extracted and saved to '%s'.\n", outputFileName);
    free(decodetxt);
}

//extract decode fetched txt from total fetched file txt
void extractdecodetxt() {
    FILE *att;
    char line[line_len];
    const char *decode = "C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\decode.txt";

    att = fopen("C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\att.txt", "r");
    if (att == NULL) {
        printf("\nError in Opening the attachment txt temp");
        getch();
        return;
    }

    fseek(att, 0, SEEK_END);
    long file_size = ftell(att);
    rewind(att);

    char *temp = (char *) malloc(file_size + 1);
    fread(temp, sizeof(char), file_size, att);
    temp[file_size] = '\0';

    finddecodetxt(temp, decode);

    free(temp);
    fclose(att);
}

//decodefile func for decoding file to img
void decodeFile(const char *inputFile, char outputFile[]) {
    char command[456];
    sprintf(command, "certutil -decode %s %s", inputFile, outputFile);
    system(command);
}

//decoding sec
void decodefetchtxttoimg(char path[], int i) {
    const char *inputFileName = "C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\decode.txt";

    printf("\n%s", path);
    decodeFile(inputFileName, path);

    if (path[i - 1] == 'p') {
        bmp(path);
    } else if (path[i - 2] == 'n') {
        png(path);
    } else {
        jpg(path);
    }
    return;
}
//end of gmail functions

//--------------------------------------------------------------------------------------------------------------------

void download_image(const char *url, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Failed to open the file for writing.\n");
        return;
    }

    // Create the command to download the image using curl
    char command[256];
    snprintf(command, sizeof(command), "curl -o \"%s\" \"%s\"", filename, url);

    // Execute the command using the system function
    int result = system(command);

    if (result == 0) {
        printf("Image downloaded successfully.\n");
    } else {
        printf("Failed to download the image.\n");
    }

    fclose(file);
}

void url() {

    //url for example:(this is a png file)
    //const char* url = "https://th.bing.com/th/id/OIP.Dpt7YmriHx7OeGoVXx8vsQHaKE?w=140&h=191&c=7&r=0&o=5&dpr=1.5&pid=1.7";
    int c, i = 0, j = 0, m;
    char url[1000], path[1000];
    printf("please write your url link:");
    getchar();
    for (; (c = getchar()) != '\n'; i++) {
        url[i] = c;
        url[i + 1] = '\0';
    }

    printf("please write your path for saving downloded image :");
    for (; (c = getchar()) != '\n'; j++) {
        path[j] = c;
        path[j + 1] = '\0';
    }

    //const char* filename = "c";
    download_image(url, path);

    printf("%s", url);
    printf("\n%s", path);

    if (path[j - 1] == 'p') {
        bmp(path);
    } else if (path[j - 2] == 'n') {
        png(path);
    } else {
        jpg(path);
    }
    return;
}

//---------------------------------------------------------------------------------------------------------------------

int main() {
    char c, m;
    char rrr, rr, r, input[1000];
    int rate = 0;
    printf("Welcome to our C programming project\n");
    printf("We have 4 way to get input\nPlease choose your choice:\n1.path in pc\n2.url\n3.Email\n4.socket but its not correct it download the picture correctly but cant cu  the disired encoded txt of the pic\n");
    printf("For exit : press Enter Key\n");
    for (; (c = getchar()) != '\n';) {
        if (c == '1') {
            printf("please choose your image format\n1.jpg or jpeg\n2.png\n3.bitmap\n");
            scanf("%c", &rr);
            scanf("%c", &r);
            printf("please entry path of your image.\n");
            int i = 0;
            scanf("%c", &rrr);
            for (; (m = getchar()) != '\n'; i++) {
                input[i] = m;
                input[i + 1] = '\0';
            }
            if (r == '3') {
                bmp(input);
            } else if (r == '2') {
                png(input);
            } else if (r == '1') {
                jpg(input);
            }
        } else if (c == '2') {
            url();
        } else if (c == '3') {

            //fetch email
            fetchemail();

            //fetch txt extract to img decode txt
            extractdecodetxt();

            //decoding sec
            char path[1000];
            int c, i = 0;
            printf("please write your path for save:");
            printf("\n");
            getchar();
            for (; (c = getchar()) != '\n'; i++) {
                path[i] = c;
                path[i + 1] = '\0';
            }
            decodefetchtxttoimg(path, i);

        } else if (c == '4') {
            urlwithsocket();
        }
        printf("your job done! if you have another task please enter a number between 0 and 5 ");
    }
    printf("if you are satisfied ,please enter a number between 1 and 10 for rating to the program and you dont please enter 0:");
    scanf("%d", &rate);

    printf("\nyour rate is : %d", rate);

    printf("\nIf you want to contact with us you can send your opinion or problem to our program's e-mail (parsaali0002@gmail.com)!");

    printf("\nEND OF PROGRAM :D");
    return 0;
}