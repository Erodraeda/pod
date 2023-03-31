
#include <windows.h>
#include <winsock.h>

#include <stdio.h>

#define LOCAL_SERVER_PORT 2022
#define MAX_MSG 2048

int main(int argc, char *argv[]) {

    int pnt_sck, tam_msg, i;
    struct sockaddr_in cliAddr, servAddr;
    char msg[MAX_MSG];

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 1), &wsaData);

    pnt_sck = socket(AF_INET, SOCK_DGRAM, 0);

    if (pnt_sck < 0) {
        printf(" \n %s: Unable to open socket \n", argv[0]);
        exit(1);
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(LOCAL_SERVER_PORT);

    if (bind (pnt_sck, (struct sockaddr *) &servAddr,sizeof(servAddr)) < 0) {
        printf(" %s: Unable to bind port %d \n", argv[0], LOCAL_SERVER_PORT);
        exit(1);
    }

    printf(" %s: Awaiting UDP data %u\n", argv[0], LOCAL_SERVER_PORT);

    char bufferMaiusculo[MAX_MSG];
    while(1) {
        memset(msg, 0x0, MAX_MSG);
        tam_msg = sizeof(cliAddr);
        if (recvfrom(pnt_sck, msg, MAX_MSG, 0, (struct sockaddr *) &cliAddr, &tam_msg) < 0) {
            printf(" Unable to receive message \n");
            continue;
        } else {
            printf(" %s: Received from %s:UDP Port: %u message: %s \n", argv[0], inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port), msg);
            for (i = 0; i < strlen(msg); i++) {
                msg[i] = toupper(msg[i]);
            }

            if (sendto(pnt_sck, msg, strlen(msg) + 1, 0,(LPSOCKADDR) &cliAddr, sizeof(struct sockaddr)) < 0) {
                printf(" Unable to send message \n");
                closesocket(pnt_sck);
                exit(1);
            }
        }
    }

  closesocket(pnt_sck);
  WSACleanup();
  // return 0;
}

