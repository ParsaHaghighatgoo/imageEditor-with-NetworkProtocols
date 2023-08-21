#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void download_image(const char* url, const char* filename) {
    FILE* file = fopen(filename, "wb");
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

void url(){
    const char* url = "https://www.simplilearn.com/ice9/free_resources_article_thumb/what_is_image_Processing.jpg";
    const char* filename = "C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\img.png";
    download_image(url, filename);
    return;
}

int main(){

    return 0;
}