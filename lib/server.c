#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "defs.h"

int listenSocket;

int main() {
	LibraryType *library = (LibraryType*) malloc(sizeof(LibraryType));
	int clientSocket;
	initLibrary(&library, "Wan Shi Tong's Library");
	setupServerSocket(&listenSocket);
	signal(SIGUSR1, handleSig1);
	acceptConnection(listenSocket, &clientSocket);
	serveOneClient(clientSocket, library);
  	return 0;
}

/*
  Function:  serveOneClient
   Purpose:  receives, formats and sends data to and from the client
   	 0:  sends formatted string of all the books in the library data in a formatted string
   	 1:  checking out - receives inputted id and sends returncode to client 
   	 2:  checking in - receives inputted id and sends returncode to client 
   	 3:  closes the socket and exits the server
        in:  clientsocket, library collection
       out:  book string
    return:  nothing
*/
void serveOneClient(int clientSocket, LibraryType *lib) {
	char buffer[MAX_BUFF];
	char outStr[MAX_BUFF];
	int id, action;
	while (1) {
		rcvData(clientSocket, buffer);
		sscanf(buffer, "%d", &action);
		if (action == 0) {
			formatBooks(&lib ->books, outStr);
			sendData(clientSocket, outStr);
		} else if (action == 1) {
			sscanf(buffer, "%d%d", &action, &id);
			if (checkOutBook(lib, id) == 0) {
				sprintf(outStr, "%d", 0);
			} else if (checkOutBook(lib, id) == -1) {
				sprintf(outStr, "%d", -1);
			} else if (checkOutBook(lib, id) == -2) {
				sprintf(outStr, "%d", -2);
			} else {
				sprintf(outStr, "%d", -3);
			}
			sendData(clientSocket, outStr);
		} else if (action == 2) {
			sscanf(buffer, "%d%d", &action, &id);
			if (checkInBook(lib, id) == 0) {
				sprintf(outStr, "%d", 0);
			} else if (checkInBook(lib, id) == -1) {
				sprintf(outStr, "%d", -1);
			} else if (checkInBook(lib, id) == -2) {
				sprintf(outStr, "%d", -2);
			} else {
				sprintf(outStr, "%d", -3);
			}
			sendData(clientSocket, outStr);
		} else if (action == 3) {
			close(clientSocket);
			closeAll(lib);
			exit(-1);
		}
    	}
}

/*
  Function:  closeAll
   Purpose:  closes socket and frees library as best as possible
        in:  library collection
    return:  nothing
*/
void closeAll(LibraryType *lib) {
	cleanupLibrary(lib);
	close(listenSocket);
}

/*
  Function:  handleSig1
   Purpose:  closes socket and frees library as best as possible
    return:  nothing
*/
void handleSig1(int i) {
	close(listenSocket);
  	exit(SIGUSR1);
}
