#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <pthread.h>
#include <sys/wait.h>

using namespace std;
char buff[50];

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

void* Send(void* Tid){
  while(1){
    cin>>buff;
    int to = *((int*)Tid);
    if(send(to,buff,sizeof(buff),0)==-1){
      cout<<"Sending Failed\n";
      break;
    }
  }
}

int main(){
  // char buff[50];
  struct sockaddr_in server,client;
  int s,ns;
  s=socket(AF_INET,SOCK_STREAM,0);
  if(s==-1){cout<<"Socket error\n";return 0;}
  cout<<"socket created\n";

  int port;
  cout<<"PORT: ";cin>>port;
  server.sin_family=AF_INET;
  server.sin_port=htons(port);
  server.sin_addr.s_addr=htonl(INADDR_ANY);
  if(bind(s,(struct sockaddr*)&server,sizeof(server))==-1){cout<<"Binding error\n";return 0;}
  cout<<"Socket Binded\n";

  int r =listen(s,1);
  if(r==-1){close(s);return 0;}
  cout<<"Socket listening\n";

  socklen_t len=sizeof(client);
  ns=accept(s,(struct sockaddr*)&client,&len);
  if(ns==-1){close(s);return 0;}
  cout<<"socket accepting\n";

  pthread_t Snd,Recv;

  int rid=0,sid=0;
  pthread_create(&Recv,NULL,Receive,&ns);
  pthread_create(&Snd,NULL,Send,&ns);
  pthread_exit(NULL);
  close(s);close(ns);
}
