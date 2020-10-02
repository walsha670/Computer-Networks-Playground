4 files provided in zip folder
1. README.md
2. HSE.c
3. doctor.c
4. Prescription1.txt

Environment set-up
- linux based operating system required
- gcc compiler required

Compilation Instructions
- Make sure all files are located in same directory
- Open 2 seperate terminal tabs, set to directory
- makefile 
    1. HSE.c
    gcc HSE.c -o server
    2. doctor.c
    gcc doctor.c -o client

Running the code
1. server takes port number as arg, so ->  
./server 6000
2. client takes I.P. address and port number as args, so -> 
./client 127.0.0.1 6000 
//loopback ip address shown for running on same device



Test cases
1. Run client when server is offline, recieves error message
2. Run Server and then client and forget client arguments, 
displays correct format to run, then closes 
3. Run server with no arg,
displays correct error and exits
4. Run server then client and enter exit, 
server and client close 

$$-ACTUAL DEMONSTRATION OF IMPLEMENTATION-$$
5. Run server then client and enter EXACTLY AS FOLLOWS
Prescription1.txt
file will be duplicated into file directory as Prescription1uploaded.txt and both client and server close


