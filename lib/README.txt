---------------------------------------------------------------------------------------------
COMP 2401- Dr Christine Laurendeau
---------------------------------------------------------------------------------------------
AUTHOR => Doyinsola Sayyidah Akindele 101192813
-------
PURPOSE
-------
/*
	-prompts user to pick between 6 options
	-option 1:
		- prints books with their information
	-option 2:
		- asks for book id
		- checks out book if no errors
	-option 3:
		- asks for book id
		- checks in book if no errors
	-option 4:
		-exits the menu
*/

COMPILATION INSTRUCTIONS
------------------------
make


LAUNCHING INSTRUCTIONS 
----------------------
1. In terminal 1, run >./server
2. In terminal 2, run >./client

DEBUGGING
---------
In case of server errors while running:
	COULD NOT BIND TO SOCKET: run >fuser -k 60002/tcp
	CLIENT COULD NOT CONNECT TO SERVER: close the server and client and restart the server


LIST OF SOURCE AND HEADER FILES
-------------------------------
defs.h
server.c
lib.c
books.c
connect.c
booksData.txt
makefile
client.c
