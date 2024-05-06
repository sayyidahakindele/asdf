# Library

AUTHOR
------
Doyinsola Sayyidah Akindele

PURPOSE
-------
Simulates an online library that gives the user the ability to check in or out books

Prompts user to pick between 4 options
- option 1:
  - prints books with their information
- option 2:
  - asks for book id
	- checks out book if no errors
- option 3:
  - asks for book id
	- checks in book if no errors
- option 4:
  - exits the menu

TECHNICAL SKILLS
----------------
This multi-process program implements a dual server process that communicates using TCP/IP sockets. It receives the available books and its particular information as a line-separated block of strings in a text file and the program prepares the data into a more suitable format for processing


COMPILING AND LAUNCHING
------------------------
1.  make
2.  In terminal 1, run ./server
3.  In terminal 2, run ./client
    
DEBUGGING
---------
In case of server errors while running:

- COULD NOT BIND TO SOCKET: run >fuser -k 60002/tcp
- CLIENT COULD NOT CONNECT TO SERVER: close the server and client and restart the server


LIST OF SOURCE AND HEADER FILES
-------------------------------
- defs.h
- server.c
- lib.c
- books.c
- connect.c
- booksData.txt
- makefile
- client.c
