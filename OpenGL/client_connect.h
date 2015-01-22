//
//  client_connect.h
//  OpenGL
//
//  Created by Irina on 22/01/15.
//  Copyright (c) 2015 Argon Team. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main1()
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    char buffer[256];
    //    if (argc < 3) {
    //        fprintf(stderr,"usage %s hostname port\n", argv[0]);
    //        exit(0);
    //    }
    portno = 6543;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname("127.0.0.1");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = (int)write(sockfd,buffer,strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    bzero(buffer,256);
    n = (int)read(sockfd,buffer,255);
    if (n < 0)
        error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(sockfd);
    return 0;
}


string take_database(const char ip, int port, long int chunk_id)
{
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    char buffer[256];
    buffer[0] = 1;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server = gethostbyname(&ip);
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(port);
    bzero(buffer,256);
    n = (int)write(sockfd, buffer, strlen(buffer));
    bzero(buffer,256);
    n = (int)read(sockfd,buffer,255);
    if (n < 0)
    printf("%s\n",buffer);
    close(sockfd);
    return buffer;
}



