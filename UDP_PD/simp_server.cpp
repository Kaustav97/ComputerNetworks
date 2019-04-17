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

// void* Receive(void* Tid){
//   while(1){
//     int frm = *((int*)(Tid));
//     int len;
//     if(recv(frm,buff,sizeof(buff),MSG_WAITALL,(struct sockaddr*)&client,&len)==-1){
//       cout<<"Receiving failed\n";
//       break;
//     }
//     string str =string(buff);
//     cout<<"Received: "<<str<<endl;
//   }
// }
//
// void* Send(void* Tid){
//   while(1){
//     cin>>buff;
//     int to = *((int*)Tid);
//     if(send(to,buff,sizeof(buff),0)==-1){
//       cout<<"Sending Failed\n";
//       break;
//     }
//   }
// }

int main(){
  // char buff[50];

  int s,ns;
  s=socket(AF_INET,SOCK_DGRAM,0);
  if(s<0){cout<<"Socket error\n";return 0;}
  cout<<"socket created\n";

  int port;
  cout<<"PORT: ";cin>>port;
  server.sin_family=AF_INET;
  server.sin_port=htons(port);
  server.sin_addr.s_addr=htonl(INADDR_ANY);
  if(bind(s,(struct sockaddr*)&server,sizeof(server))<0){cout<<"Binding error\n";return 0;}
  cout<<"Socket Binded\n";

  int n;
  socklen_t len=sizeof(client);
  n= recvfrom(s,buff,sizeof(buff),MSG_WAITALL,(struct sockaddr*)&client,&len);
  buff[n]='\0';
  printf("Client : %s\n", buff);

  string qry = string(buff);
  string rev=qry;
  reverse(begin(qry),end(qry));
  char *ans;
  if(qry == rev)ans="Palin";
  else ans="NotPalin";

  sendto(s, (const char*)ans,strlen(ans),
      MSG_CONFIRM, (const struct sockaddr *) &client,
          len);
  printf("Hello message sent.\n");

  // pthread_t Snd,Recv;
  //
  // pthread_create(&Recv,NULL,Receive,&s);
  // pthread_create(&Snd,NULL,Send,&s);
  // pthread_exit(NULL);
  close(s);close(ns);
}
