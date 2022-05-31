#include "defs.h"


int main()
{
	int  choice = -1;
  	int clientSocket;
   	setupClientSocket(&clientSocket);
   	char request[MAX_STR];
   	int input, flag;
  	char str[MAX_STR];
  	char response[MAX_BUFF];
  while (1) {
   clientMenu(&choice);
  
		switch(choice) {
      		case 1:   // Print books
      			sprintf(request, "%d", REQ_RET_BOOKS);
      			sendData(clientSocket, request);
      			rcvData(clientSocket, response);
      			printf("%s", response);
        		break;

      		case 2:   // Check out a book
			printf("Please enter a book id: ");
			fgets(str, sizeof(str), stdin);
			sscanf(str, "%d", &input);
			sprintf(request, "%d %d", REQ_CHECK_IN, input);
			sendData(clientSocket, request);
			rcvData(clientSocket, response);
      			sscanf(response, "%d", &flag);
      			if (flag == 0) {
      				printf("The book with the id %d has been successfully checked out\n", input);
      			} else if (flag == -1) {
      				printf("ERROR: The book with the id %d has already been checked out\n", input);
      			}else if (flag == -2) {
      				printf("ERROR: The book with the id %d does not exist\n", input);
      			} else if (flag == -3) {
      				printf("ERROR: The book with the id %d is lost or is under repair\n", input);
      			}
        		break;

      		case 3:   // Check in a book
			printf("Please enter a book id: ");
			fgets(str, sizeof(str), stdin);
			sscanf(str, "%d", &input);
			sprintf(request, "%d %d", REQ_CHECK_OUT, input);
			sendData(clientSocket, request);
      			rcvData(clientSocket, response);
      			sscanf(response, "%d", &flag);
      			if (flag == 0) {
      				printf("The book with the id %d has been successfully checked in\n", input);
      			} else if (flag == -1) {
      				printf("ERROR: The book with the id %d has already been checked in\n", input);
      			} else if (flag == -2) {
      				printf("ERROR: The book with the id %d does not exist\n", input);
      			} else if (flag == -3) {
      				printf("ERROR: The book with the id %d is lost or is under repair\n", input);
      			}
        		break;

      		case 0:   // Close everything
			sprintf(request, "%d", REQ_CLOSE);
      			sendData(clientSocket, request);
      			close(clientSocket);
      			exit(-1);
        		break;

      		default:
        		printf("ERROR:  invalid option\n");
    }
  }

  return 0;
}

void clientMenu(int* choice)
{
  int c = -1;
  int numOptions = 3;
  char str[MAX_STR];

  printf("\nMAIN MENU\n");
  printf("  (1) Print books\n");
  printf("  (2) Check out a book\n");
  printf("  (3) Check in a book\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  fgets(str, sizeof(str), stdin);
  str[strcspn(str, "\n")] = 0;
  sscanf(str, "%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d", &c);
  }

  *choice = c;
}

