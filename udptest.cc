#include <iostream>
using namespace std;

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main () {
  cout << "running\n";
  struct sockaddr_in si_me, si_other;
  int s, i, slen=sizeof(si_other);
  char buf[512];

  if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
    exit(1);
  
  memset((char*) &si_me, 0, sizeof(si_me));
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(6667);
  si_me.sin_addr.s_addr = htonl(INADDR_ANY);

  if(bind(s, (sockaddr*) &si_me, sizeof(si_me)) == -1)
    exit(1);
  
  cout << "sending...\n";

  
}
