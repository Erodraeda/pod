#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define REMOTE_SERVER_PORT 2022
#define MAX_MSG 2048
#define SERVIDOR "127.0.0.1"

int main() {

    int sd, pnt_bind, i;
    struct sockaddr_in cliAddr, remoteServAddr;
    WSADATA wsaData;
    LPHOSTENT lpHostEntry;
    char message[20];
    struct stat file_stat;

    WSAStartup(MAKEWORD(2, 1), &wsaData);

    lpHostEntry = gethostbyname(SERVIDOR);

    /* create socket */
    sd = socket(AF_INET,SOCK_DGRAM,0);

    if (sd < 0) {
    printf(" \n Unable to create socket with server: %s:\n", SERVIDOR);
    exit(1);
    }

    /* bind socket */
    cliAddr.sin_family = AF_INET;
    cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    cliAddr.sin_port = htons(0);

    remoteServAddr.sin_family = AF_INET;
    remoteServAddr.sin_addr = *((LPIN_ADDR) * lpHostEntry -> h_addr_list);
    remoteServAddr.sin_port = htons(REMOTE_SERVER_PORT);
  
	FILE *txt;
	if ((txt = fopen("file.txt", "r+")) == NULL) {
		printf(" Unable to open file");
	} else {
		FILE *txt2;
		if ((txt2 = fopen("upperCaseFile.txt", "w+")) == NULL) {
			printf(" Unable to open upper case file\n");
		} else {
			while(!feof(txt)) {
				fgets(message, MAX_MSG, txt);

			  	if (sendto(sd, message, strlen(message) + 1, 0, (LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr)) < 0) {
					printf(" Unable to send message\n");
			    	closesocket(sd);
			    	exit(1);
			    }
			    
			    printf(" Sent message: %s\n", message);
				
				memset(message, 0, strlen(message));
				int servLen = sizeof(remoteServAddr);
			    if (recvfrom(sd, message, MAX_MSG, 0, (struct sockaddr *) &remoteServAddr, &servLen) < 0) {
			    	printf(" Unable ");
			    	continue;
			    }
				
				printf(" Received message: %s\n", message);
				fprintf(txt2, "%s", message);
				memset(message, 0, strlen(message));
			}
		}
        fclose(txt);
        fclose(txt2);
	}
	system("pause");
	
	closesocket(sd);
	return 1;

}
