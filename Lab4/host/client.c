#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <strings.h>
#include <sched.h>
#include<pthread.h>

void error(char *m)
{   
  perror(m);
  exit(0); 
}


int main(int argc, char *argv[ ])
{ 
  int sockfd1,sockfd2,sockfd3, port, n;
  struct sockaddr_in serv_addr; 
  struct hostent *server;
  char buffer[256];

  pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

  if (argc < 3) error("usage client [hostname] [port]\n"); 
  port = atoi(argv[2]);

  server = gethostbyname(argv[1]);
  if (server == NULL) error("ERROR, no such host\n");
// start with a clean address structure
  memset((char *)&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET; // internet socket
  bcopy((char *)server->h_addr, &serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(port);

  pid_t ch_pid1, ch_pid2, ch_pid3;
  int status;
  char a[] = "11", b[] = "22", c[] = "33";
  
  ch_pid1 = fork();
  if (ch_pid1 != 0)
  {
    ch_pid2 = fork();
    if (ch_pid2 != 0)
    {
      ch_pid3 = fork();
      if (ch_pid3 != 0)
      {
        wait(&status);
      }
      else
      {
        sockfd3 = socket(AF_INET, SOCK_STREAM, 0); 
        if (sockfd3 < 0) error("ERROR opening socket");

        if (connect(sockfd3,(struct sockaddr*)&serv_addr ,sizeof(serv_addr)) < 0)
          error("ERROR connecting");
    
        printf("Sending %s \n", c); 

        pthread_mutex_lock( &mutex1 );  // LOCK MUTEX
        strcpy(buffer, c);
        n = write(sockfd3,buffer,strlen(buffer));
        pthread_mutex_unlock( &mutex1 );  //UNLOCK MUTEX

        if (n < 0)
          error("ERROR writing to socket");
        n = read(sockfd3,buffer,255);
        if (n < 0)
          error("ERROR reading from socket");
        printf("%s\n",buffer);
      }
    }
    else
    {
      sockfd2 = socket(AF_INET, SOCK_STREAM, 0); 
      if (sockfd2 < 0) error("ERROR opening socket");
      if (connect(sockfd2,(struct sockaddr*)&serv_addr ,sizeof(serv_addr)) < 0)
      error("ERROR connecting");
    
      printf("Sending %s \n", b); 

      pthread_mutex_lock( &mutex1 );  // LOCK MUTEX
      strcpy(buffer, b);
      n = write(sockfd2,buffer,strlen(buffer));
      if (n < 0)
        error("ERROR writing to socket");
      pthread_mutex_unlock( &mutex1 );  //UNLOCK MUTEX

      n = read(sockfd2,buffer,255);
      if (n < 0)
        error("ERROR reading from socket");
      printf("%s\n",buffer);
    }
  }
  else
  {
    sockfd1 = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd1 < 0) error("ERROR opening socket");
    if (connect(sockfd1,(struct sockaddr*)&serv_addr ,sizeof(serv_addr)) < 0)
      error("ERROR connecting");
    
    printf("Sending %s \n", a); 
    
    pthread_mutex_lock( &mutex1 );  // LOCK MUTEX
    strcpy(buffer, a);
    n = write(sockfd1,buffer,strlen(buffer));
    pthread_mutex_unlock( &mutex1 );  //UNLOCK MUTEX

    if (n < 0)
      error("ERROR writing to socket");
    n = read(sockfd1,buffer,255);
    if (n < 0)
      error("ERROR reading from socket");
    printf("%s\n",buffer);
  }


  return 0; 
}

