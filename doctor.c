#include <stdio.h> 
#include <stdlib.h>  
#include <unistd.h>
#include <string.h> // needed for strings in C
#include <sys/types.h> // has definitions for porting in linux 
#include <sys/socket.h> // macro definitions for creating sockets and socket functions e.g sockaddr
#include <netinet/in.h> //contains defs for structures like sockaddr_in
#include <netdb.h> // contains def for structure hostent, which has host info needed
#include <ctype.h> // useful for handling characters - getchar(), EOF

void print_error(const char *msg)
{
    perror(msg); //in built inputs the error number and ouptuts error description
    exit(1); //so when there is an error the program ends
}

int main(int argc, char *argv[])
{	
    //name socket to be used
    //initialise int for port num
    int sockfd, portno;
    struct sockaddr_in serv_addr; //structure w/ internet address
    struct hostent *server; //need hostent for host info

    char buffer[400]; //buffer for file transfer
    if(argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]); //warning when an argument is missing when running code
        exit(1);
    }

    portno = atoi(argv[2]); //assigns int value to portno
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //initialise socket
    if(sockfd < 0){
        print_error("Error when opening specified socket \n"); //error if sockfd returns neg value
    }
    server = gethostbyname(argv[1]); //returns pointer to hostent which has host IP address
    if(server == NULL)
    {
        fprintf(stderr, "Error: Cannot find host \n"); //IP address not found
    }
    printf("Connection being made with Server! \n");

    bzero((char *) &serv_addr, sizeof(serv_addr)); //zero all values
    serv_addr.sin_family = AF_INET; //standard practise to connect with internet
    bcopy((char *) server->h_addr , (char*) &serv_addr.sin_addr.s_addr, server->h_length); //copies specified num of bytes to specified loc.
    serv_addr.sin_port = htons(portno); //converts from host byte order to network byte order
    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0)
    {
        print_error("server offline \n");
    }
    /* 
    --------------------------------------------------
    CHAT APPLICATION USED FOR TESTING PROTOCOLS 
    --------------------------------------------------      
    while(1)
    {
    printf("while entered \n");
    bzero(buffer, 255);
    fgets(buffer, 255, stdin);
    n = write(sockfd, buffer, strlen(buffer));
    if(n < 0)
    {
        error("Error on writing");
    }
    bzero(buffer, 255);
    n = read(sockfd, buffer, 255);
    if(n < 0)
    {
        error("Error on reading");
    }
    printf("server: %s", buffer);
    int i = strncmp("Bye", buffer, 3);
    if(i == 0)
    {
        break;
    }
           
    }*/

    bzero(buffer, 400); //sets buff value to 0
    FILE *f;
    char c;
    char filename[20]; //char array used for exiting
    int words = 0;
    //calculate how many words in file, use this amount to 
    //run loop appropriate amount of times, prescription1
    printf("Enter a filename to transfer to HSE database, or 'exit' to leave program: \n");
    scanf("%s", filename); //basic read-in functionality
    printf("%s", filename);
    int i = strcmp("exit", filename);
    
    if(i ==0)
    {
        printf("Thank you for using this service, goodbye \n");
        exit(1);
    }
    f = fopen("Prescription1.txt", "r"); //opens file provided, in future version will be specified by user
    while((c = getc(f)) != EOF)
    {
        fscanf(f, "%s", buffer);
        if(isspace(c) || c== '\t') {
            words++;
        }
    }
    //send word count to server
    write(sockfd, &words, sizeof(int));
    rewind(f); //sets file to start

    char ch;
    //while loop that incrementally send chunks of .txt file
    while(ch != EOF)
    {
        fscanf(f, "%s", buffer);
        write(sockfd, buffer, 400);
        ch = fgetc(f);
    }
    
    printf(" has been successfully sent to HSE\n");

    close(sockfd); //close socket used
    return 0;



        
    
    

}
