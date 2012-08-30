#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

#include <pthread.h>

void *t (void *Params) {
  int s = ((int*)Params)[1];
  //close(*(int*)Params);
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family=AF_UNIX;
  char ss[] = "hello world\0";
  while(1) {
    sleep(1);
    printf("sending\n");
    sendto(s, ss, sizeof(ss), 0, (struct sockaddr*)NULL, (socklen_t)0);
  }
}

int main (int argc, char **argv) {
  int sockets[2];
  socketpair(AF_UNIX, SOCK_DGRAM, 0, sockets);
  
  pthread_t what;
  pthread_create(&what, 0, t, (void*)sockets);
  //close(sockets[1]);

  struct sockaddr_in from;
  char buffer[1024];
  int size_from = sizeof(from);
  while(1) {
    printf("waiting\n");
    int bytes = recv(sockets[0], &buffer, sizeof(buffer), 0);//, (struct sockaddr*)&from, (socklen_t*)&size_from);
    printf("%s\n", buffer); 
  }
}
