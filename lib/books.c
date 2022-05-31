#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

/*
  Function:  initList
   Purpose:  initialises BookListType fields
        in:  collection of books
    return:  nothing
*/
void initList(BookListType *list) {
	list ->head = NULL;
	list ->tail = NULL;
}

/*
  Function:  initBook
   Purpose:  initialises BookType fields
        in:  id, title, author, year, status
       out:	 new book
    return:  nothing
*/
void initBook(int i, char *t, char *a, int y, BookStatusType st, BookType **book) {
	BookType *new = (BookType*) malloc(sizeof(BookType));
	(new) ->id =i;
	strcpy((new)->title, t);
	strcpy((new)->author, a);
	(new) ->year = y;
	(new) ->status = st;
	*book = new;
}

/*
  Function:  addBook
   Purpose:  adds new book to collection in alphabetically by title
        in:  collection of books, book
    return:  nothing
*/
void addBook(BookListType *list, BookType *b) {
	NodeType *currNode;
  	NodeType *prevNode;
  	NodeType *newNode;

  	currNode = list ->head;
  	prevNode = NULL;
  	while (currNode != NULL) {
  		if (strcmp(b ->title, currNode ->data ->title) < 0) {
      		break;
    	}
    	prevNode = currNode;
    	currNode = currNode ->next;
  	}
  	newNode = malloc(sizeof(NodeType));
  	newNode ->data = b;
  	newNode ->next = NULL;

  	if (prevNode == NULL) {
    		list ->head = newNode;
    	} else {
    		prevNode->next = newNode;
	}
	newNode->next = currNode;
	if (currNode == NULL) {
		list ->tail = newNode;
	}
}

/*
  Function:  findBook
   Purpose:  traverse book collection and finds book with inputted id
        in:  collection of books, id
       out:  found book data
    return:  C_OK or C_NOK
*/
int findBook(BookListType *list, int id, BookType **b) {
	int flag = C_NOK;
	NodeType *currNode = list ->head;
	while (currNode != NULL) {
		if (currNode ->data ->id == id) {
			*b = currNode ->data;
			flag = C_OK;
		}
		currNode = currNode ->next;
	}
	return flag;
}

/*
  Function:  convertStatus
   Purpose:  converts BookStatusType enum values to strings
        in:  status value
       out:  status string
    return:  nothing
*/
void convertStatus(BookStatusType status, char *strstatus) {
	if (status == CHECKED_IN) {
		strcpy(strstatus, "Checked in");
	}
	if (status == CHECKED_OUT) {
		strcpy(strstatus, "Checked out");
	}
	if (status == UNDER_REPAIR) {
		strcpy(strstatus, "Under repair");
	}
	if (status == LOST) {
		strcpy(strstatus, "Lost");
	}
}

/*
  Function:  formatBook
   Purpose:  formats string for single book
        in:  book
       out:  book string
    return:  nothing
*/
void formatBook(BookType *b, char *outStr) {
	char statusstr[MAX_STR];
	char eachbook[MAX_ARR];
	convertStatus(b ->status, statusstr);
	sprintf(eachbook, "%-5d| %-37s| %-19s| %-5d| %-14s\n", b ->id, b ->title, b ->author, b ->year, statusstr);
	strcpy(outStr, eachbook);
}

/*
  Function:  formatBooks
   Purpose:  formats single list for all the books
        in:  book collection
       out:  book string
    return:  nothing
*/
void formatBooks(BookListType *list, char *outStr) {
	char temporary[MAX_ARR];
	char allbooks[MAX_BUFF] = {0};
	NodeType *currNode = list ->head;
	while (currNode != NULL) {
		formatBook(currNode ->data, temporary);
		strcat(allbooks, temporary);
		currNode = currNode ->next;
	}
	strcpy(outStr, allbooks);
}

/*
  Function:  cleanupList
   Purpose:  frees memory in the book collection
        in:  book collection
    return:  nothing
*/
void cleanupList(BookListType *list) {
	 NodeType *currNode = NULL;
	 NodeType *nextNode = NULL;
	 currNode = list -> head;
	 while (currNode != NULL) {
	 	nextNode = currNode->next;
    		free(currNode->data);
    		free(currNode);
    		currNode = nextNode;
  	 }
}
