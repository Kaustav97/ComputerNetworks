#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include<fcntl.h>
#include <sys/wait.h>

using namespace std;
char buff[50];
struct sockaddr_in server;

void* Send(void* Tid){
  while(1){
    cin>>buff;
    int to=*((int*)Tid);
    if(sendto(to,buff,sizeof(buff),0,(struct sockaddr*)&server,sizeof(server) )==-1){
      cout<<"Sending Failed\n";
      break;
    }
  }
}

void* Receive(void* Tid){
  while(1){
    int frm = *((int*)(Tid));
    socklen_t sa = sizeof(server);
    if(recvfrom(frm,buff,sizeof(buff),0,(struct sockaddr *)&server,&sa)==-1){
      // cout<<"Receiving failed\n";
      continue;
      // break;
    }
    string str =string(buff);
    cout<<"Received: "<<str<<endl;
  }
}

int main(){
  char buff[50];
  int s= socket(AF_INET,SOCK_STREAM,0);
  if(s==-1){cout<<"Socket creation error\n";return 0;}
  cout<<"Socket Created\n"  ;

  int port;
  cout<<"PORT :";  cin>>port;

  server.sin_family=AF_INET;
  server.sin_port=htons(port);
  server.sin_addr.s_addr=inet_addr("127.0.0.1");

  // if(connect(s,(struct sockaddr*)&server,sizeof(server))==-1){
  //   cout<<"Connection Error\n"; return 0;
  // }
  // cout<<"Socket Connected\n";

  pthread_t Snd,Recv;
  pthread_create(&Snd,NULL,Send,&s);
  pthread_create(&Recv,NULL,Receive,&s);
  pthread_exit(NULL);
  close(s);
}
