#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#pragma comment(lib, "ws2_32.lib")

//correct
void dlfromsocket(){
    WSADATA wsaData;
    SOCKET sock;
    struct addrinfo hints, *res;
    char request[1024];
    int bytesReceived, totalBytesReceived;
    FILE *fp;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return ;
    }

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Error creating socket\n");
        WSACleanup();
        return ;
    }

    // Resolve URL to IP address
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo("www.cs.sjsu.edu", "80", &hints, &res) != 0) {
        printf("Error resolving URL\n");
        closesocket(sock);
        WSACleanup();
        return ;
    }

    // Connect to server
    if (connect(sock, res->ai_addr, res->ai_addrlen) == SOCKET_ERROR) {
        printf("Error connecting to server\n");
        freeaddrinfo(res);
        closesocket(sock);
        WSACleanup();
        return ;
    }

    // Send HTTP GET request
    sprintf(request, "GET /~pearce/modules/lectures/web/html/HTTP_files/image001.jpg HTTP/1.1\r\nHost:www.cs.sjsu.edu\r\n\r\n");
    send(sock, request, strlen(request), 0);

    // Receive response
    totalBytesReceived = 0;
    fp = fopen("./temp.txt", "wb");
    while ((bytesReceived = recv(sock, request, sizeof(request), 0)) > 0) {
        fwrite(request, 1, bytesReceived, fp);
        totalBytesReceived += bytesReceived;
        printf("%c",bytesReceived);
    }


    // Clean up
    freeaddrinfo(res);
    closesocket(sock);
    WSACleanup();
    fclose(fp);

    printf("Downloaded %d bytes\n", totalBytesReceived);
    return;
}
void cuttheencodedtxtofimagefromdltxt(){
    FILE *fs, *fn;
    fs = fopen("C:\\project\\fetch\\tt.txt", "rb");
    if(fs == NULL)
    {
        printf("\nError in Opening the dledtxt file");
        getch();
        return ;
    }
    fn = fopen("C:\\project\\fetch\\tn.txt", "w");
    if(fn == NULL)
    {
        printf("\nError in Opening the encodedtxtofimage file");
        getch();
        return ;
    }
    char c;
    int count = 0,flag = 0;
    while (1){
        if(feof(fs)){
            break;
        }
        c = fgetc(fs);
        if(c == '\n'){
            count++;
            if(count == 2){
                flag = 1;
                break;
            }
        } else{
            count = 0;
        }
    }
    int i=0;
    while (flag){
        if(feof(fs)){
            break;
        }
        c = fgetc(fs);
        fputc(c,fn);
        i++;
        if(i==274){
            continue;
        }
    }
    fclose(fs);
    fclose(fn);
    printf("cut done!\n");
    return;
}

void urlwithsocket (){

    dlfromsocket();
    ///////////////////////////////////////////
    cuttheencodedtxtofimagefromdltxt();
    return;

}

int main() {


    return 0;
}

