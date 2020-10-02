#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> // needed for strings in C
#include <sys/types.h> // has definitions for porting in linux 
#include <sys/socket.h> // macro definitions for creating sockets and socket functions e.g sockaddr
#include <netinet/in.h> //contains defs for structures like sockaddr_in
#include <netdb.h> // contains def for structure hostent, which has host info needed

void print_error(const char *msg)
{
    perror(msg); //in built inputs the error number and ouptuts error description
    exit(1); //so when there is an error the program ends
}


int main(int argc, char *argv[])
{
    if(argc < 2) //argc should be 2, port number and file name
    {
        //
        printf("Port Number not provided. Program terminated \n");
        exit(1);
    }

    int sockfd, newsockfd; //sockets needed for data transaction
    int portno; //int value for port
    char buffer[400]; //buffer to transfer data 
    struct sockaddr_in serv_addr, cli_addr; //internet addresses located here
    socklen_t clilen; //socklen_t for client

    sockfd = socket(AF_INET, SOCK_STREAM, 0); //initialise socket
    if(sockfd < 0)
    {
        print_error("Error when opening Socket. \n");
    }
    
    bzero((char *)   &serv_addr , sizeof(serv_addr)); //set internal values to 0
    portno = atoi(argv[1]); //return int value for port

    //necessary definitions to set up socket
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno); //changes byte order type
    
    //binding socket with port number provided, print error if necessary
    if(bind(sockfd, (struct sockaddr *) & serv_addr, sizeof(serv_addr)) < 0)
    {
        print_error("Binding server to port failed. \n");
    }
    printf("port binded! \n");
    listen(sockfd, 5);
    printf("listening.. \n");
    clilen = sizeof(cli_addr);
    //set up socket to accept data from client
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    if(newsockfd < 0)
    {
        print_error("Error on Accepting Connection \n"); //print error if connection cant be made
    }

    /*
    CHAT APPLICATION SERVER SIDE UNUSED IN FINAL DEMO
    while(1)
    {
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255);
        if(n < 0)
        {
            error("Error on reading");
        }
        printf("Client : %s\n", buffer);
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);

        n = write(newsockfd, buffer, strlen(buffer));
        if(n < 0 )
        {
            error("Error on writing");
        }
        int i = strncmp("Bye", buffer, 3);
        if(i == 0)
        break;
    }*/
   
   
    
    FILE *fs;
    int num_words = 0;
    //oddly, because this file does not exist, the program creates it
    //"a" assures that the data will be appended 
    
    
    fs = fopen(("Prescription1uploaded.txt"), "a");
    int words;
    
    read(newsockfd, &words, sizeof(int)); //read-in at new socket

    //while file isnt complete keep reading in
    while(num_words < words)
    {
        read(newsockfd, buffer, 400);
        fprintf(fs, "%s ", buffer);
        num_words++;
    }
    //when file is complete, notify
    if(num_words = words) {
    printf("the file has been received \n");
    }
    else printf("no file uploaded \n");

    //close sockets
    close(newsockfd);
    close(sockfd);
    return 0;


}