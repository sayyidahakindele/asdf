#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "defs.h"

/*
  Function:  loadBooks
   Purpose:  reads data from textfile bookData.txt and adds it to the library
        in:  list of books
    return:  nothing
*/
void loadBooks(BookListType *books) {
	int id = 1001;
	FILE *fd;
	BookType *book;
	char buffer[MAX_BUFF];
	char title[MAX_STR];
	char author[MAX_STR];
	int year;
	int status;
	fd = fopen("booksData.txt", "r");
	if (!fd) {
		printf("ERROR: Could not open file\n");
	 	exit(1);
	}
  	while (1) {
		fgets(title, MAX_STR, fd);
		title[strlen(title) - 1] = '\0';
		fgets(author, MAX_STR, fd);
		author[strlen(author) - 1] = '\0';
		fgets(buffer, MAX_BUFF, fd);
		sscanf(buffer, "%d", &year);
		fgets(buffer, MAX_BUFF, fd);
		sscanf(buffer, "%d", &status);
		if (feof(fd)) {
			break;
		}
		initBook(id, title, author, year, status, &book);
	   	id++;
	    	addBook(books, book);
  	}
  	
  	fclose(fd);
}

/*
  Function:  initLibrary
   Purpose:  library of books
        in:  name of library
       out:  new library
    return:  nothing
*/
void initLibrary(LibraryType **library, char *n) {
	char string[MAX_BUFF];
	char head[MAX_ARR];
	char tail[MAX_ARR];
	LibraryType *new = (LibraryType*) malloc(sizeof(LibraryType));
	strcpy((new)->name, n);
	initList(&new ->books);
	loadBooks(&new ->books);
	printf("\n%s\n", n);
	printf("\n%-5s| %-37s| %-19s| %-5s| %-14s\n", "ID", "TITLE", "AUTHOR", "YEAR", "STATUS");
	printf("--------------------------------------------------------------------------------------\n");
	formatBooks(&new ->books, string);
	formatBook(new ->books.head ->data, head);
	formatBook(new ->books.tail ->data, tail);
	printf("%s\n", string);
	printf("--HEAD: %s", head);
	printf("--TAIL: %s\n", tail);
	*library = new;
}

/*
  Function:  checkOutBook
   Purpose:  checks status of book and validates whether a book can be checked out
        in:  inputted book id, library collection
    return:  C_OK, C_NOK, C_BOOK_NOT_FOUND, C_BAD_STATUS
*/
int checkOutBook(LibraryType *lib, int bookId) {
	BookType *book;
	int flag = C_BOOK_NOT_FOUND;
	if (findBook(&lib ->books, bookId, &book) == 0) {
		if (book ->status == CHECKED_IN) {
			flag = C_OK;
		} else if (book ->status == CHECKED_OUT) {
			flag = C_NOK;
		} else {
			flag = C_BAD_STATUS;
		}
	}
	if (flag == C_OK) {
		book ->status = 1;
	}
	return flag;
}

/*
  Function:  checkIntBook
   Purpose:  checks status of book and validates whether a book can be checked in
        in:  inputted book id, library collection
    return:  C_OK, C_NOK, C_BOOK_NOT_FOUND, C_BAD_STATUS
*/
int checkInBook(LibraryType *lib, int bookId) {
	BookType *book;
	int flag = C_BOOK_NOT_FOUND;
	if (findBook(&lib ->books, bookId, &book) == 0) {
		if (book ->status == CHECKED_OUT) {
			flag = C_OK;
		} else if (book ->status == CHECKED_IN) {
			flag = C_NOK;
		} else {
			flag = C_BAD_STATUS;
		} 
	}
	if (flag == C_OK) {
		book ->status = 0;
	}
	return flag;
}

/*
  Function:  cleanupLibrary
   Purpose:  frees memory in the library
        in:  libraries collection
    return:  nothing
*/
void cleanupLibrary(LibraryType *lib) {
	cleanupList(&lib ->books);
	free(lib);
}
