#include <stdio.h>
#include <string.h>
#include "curl.h"
#include <stdlib.h>
#include <conio.h>

//max len for reading eachline in fetch txt file
#define line_len 10000

// Callback function to write attachment data to file
size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    FILE* file = (FILE*)userp;
    size_t written = fwrite(contents, size, nmemb, file);
    return written;
}

// fetch func for fetch email
void fetchemail(){
    //GMAIL DL PIC
    CURL* curl;
    CURLcode res;
    FILE* file;

    // Set up libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        // Set IMAP server and account details
        //char email[] = "project.hamzeh@gmail.com"; // Replace with your Gmail address
        //char password[] = ""; // Replace with your Gmail password
        char email[] = "parsaali0002@gmail.com"; // Replace with your Gmail address
        char password[] = ":D"; // Replace with your Gmail password
        curl_easy_setopt(curl, CURLOPT_CAINFO, "C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\cacert-2023-05-30.pem");

        // Set the mailbox name and UID
        char mailbox[] = "INBOX";
        int uid = 7;

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
            return ;
        }

        // Open a file to save the fetched email
        file = fopen("C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\att.txt", "wb");
        if (!file) {
            printf("Error opening file for writing.");
            return ;
        }

        // Set the write callback function to write data into the file
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        // Perform the fetch request and save the email content to the file
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            printf("Failed to fetch email: %s\n", curl_easy_strerror(res));
            return ;
        }

        // Clean up and close the file
        fclose(file);

        // Clean up and close the IMAP session
        curl_easy_cleanup(curl);
    } else {
        printf("Error initializing libcurl.\n");
        return ;
    }

    // Clean up libcurl
    curl_global_cleanup();


    return;
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
void extractdecodetxt(){
    FILE *att;
    char line[line_len];
    const char *decode = "C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\decode.txt";

    att = fopen("C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\att.txt", "r");
    if (att == NULL) {
        printf("\nError in Opening the attachment txt temp");
        getch();
        return ;
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
void decodeFile(const char* inputFile, const char* outputFile) {
    char command[456];
    sprintf(command, "certutil -decode %s %s", inputFile, outputFile);
    system(command);
}

//decoding sec
void decodefetchtxttoimg(){
    const char* inputFileName = "C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\decode.txt";
    const char* outputFileName = "C:\\Users\\parca\\Desktop\\networkingphotoshopproject\\decodedimg.png";
    decodeFile(inputFileName, outputFileName);
    return;
}


int main() {
    //fetch email
    fetchemail();

    //fetch txt extract to img decode txt
    extractdecodetxt();

    //decoding sex
    decodefetchtxttoimg();

    return 0;
}

