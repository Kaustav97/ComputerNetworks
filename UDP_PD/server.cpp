#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <pthread.h>
#include <sys/wait.h>

using namespace std;
char buff[50];
struct sockaddr_in server,client;
bool blk=true;

void* Receive(void* Tid){
  while(blk){
    int frm = *((int*)(Tid));
    socklen_t ca = sizeof(client);
    if(recvfrom(frm,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca)==-1){
      // cout<<"Receiving failed\n";
      continue;
      // break;
    }
    string str =string(buff);
    cout<<"Received: "<<str<<endl;
    blk=false;
  }
}

void* Send(void* Tid){
  while(!blk){
    cin>>buff;
    int to = *((int*)Tid);
    if(sendto(to,buff,sizeof(buff),0,(struct sockaddr*)&client,sizeof(client))==-1){
      cout<<"Sending Failed\n";
      break;
    }
    blk=true;
  }
}

int main(){
  // char buff[50];
  int s,ns;
  blk=true;
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

  pthread_t Snd,Recv;

  int rid=0,sid=0;
  pthread_create(&Snd,NULL,Send,&s);
  pthread_create(&Recv,NULL,Receive,&s);
  pthread_exit(NULL);
  close(s);
}
