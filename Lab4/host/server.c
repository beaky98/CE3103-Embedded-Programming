#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <strings.h>
#include<pthread.h>

void error(char *m)
{
perror(m); 
}

char buffer[256];
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *serve(void *newsockfd)
{
  pthread_mutex_lock( &mutex1 );  // LOCK MUTEX
  int n = read((int)newsockfd,buffer,255);
  if (n < 0) 
      error("ERROR reading from socket"); 
  printf("Message received: %s\n",buffer);
  int num = atoi(buffer);
  pthread_mutex_unlock( &mutex1 );  //UNLOCK MUTEX

  num *= 5;
  printf("%d \n", num);

  n = write((int)newsockfd,"Message Acknowledged",21); 
  if (n < 0)
      error("ERROR writing back to socket"); 
  return NULL;
}


int main(int argc, char *argv[])
{ 
  int sockfd, newsockfd, port, n;
  socklen_t clilen;

  struct sockaddr_in serv_addr, cli_addr;
  if (argc < 2)
      error("ERROR, no port provided\n");
  port = atoi(argv[1]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
      error("ERROR opening socket");
  memset((char *) &serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET; serv_addr.sin_addr.s_addr = INADDR_ANY; serv_addr.sin_port = htons(port); //host to network
  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
      error("ERROR binding to socket");
  listen(sockfd,2);
  clilen = sizeof(cli_addr);

  pthread_t thread;
  int Tret;
  
while (1){
  newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
  if (newsockfd < 0)
      error("ERROR on accept");
  
  Tret = pthread_create(&thread, NULL, serve, (void*) newsockfd);
 }

  return 0;
}
