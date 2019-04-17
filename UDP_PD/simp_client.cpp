#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/wait.h>

using namespace std;
char buff[50];

void* Send(void* Tid){
  while(1){
    cin>>buff;
    int to=*((int*)Tid);
    if(send(to,buff,sizeof(buff),0)==-1){
      cout<<"Sending Failed\n";
      break;
    }
  }
}

void* Receive(void* Tid){
  while(1){
    int frm = *((int*)(Tid));
    if(recv(frm,buff,sizeof(buff),0)==-1){
      cout<<"Receiving failed\n";
      break;
    }
    string str =string(buff);
    cout<<"Received: "<<str<<endl;
  }
}

int main(){
  char buff[50];
  struct sockaddr_in server;
  int s= socket(AF_INET,SOCK_DGRAM,0);
  if(s<0){cout<<"Socket creation error\n";return 0;}
  cout<<"Socket Created\n"  ;

  int port;
  cout<<"PORT :";  cin>>port;

  server.sin_family=AF_INET;
  server.sin_port=htons(port);
  server.sin_addr.s_addr=INADDR_ANY;

  int n;
  socklen_t len= sizeof(server);

  cin>>buff;
  sendto(s, buff, strlen(buff),
        MSG_CONFIRM, (const struct sockaddr *) &server,
            sizeof(server));
  printf("Hello message sent.\n");

  n = recvfrom(s, buff, sizeof(buff),
              MSG_WAITALL, (struct sockaddr *) &server,
              &len);
  buff[n] = '\0';
  printf("Server : %s\n", buff);
  // pthread_t Snd,Recv;
  // pthread_create(&Recv,NULL,Receive,&s);
  // pthread_create(&Snd,NULL,Send,&s);
  // pthread_exit(NULL);
  close(s);
}
