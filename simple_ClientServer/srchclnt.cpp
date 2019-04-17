#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;
char buff[100];

int main(){
  struct sockaddr_in server;
  int s=socket(AF_INET,SOCK_STREAM,0);
  if(s==-1){cout<<"socket error\n";return 0;}
  cout<<"socket created\n";

  int port;
  cout<<"PORT: "; cin>>port;

  server.sin_family=AF_INET;
  server.sin_port=htons(port);
  server.sin_addr.s_addr=inet_addr("127.0.0.1");
  if(connect(s,(struct sockaddr*)&server,sizeof(server))==-1){
    cout<<"connect error\n";return 0;
  }
  cout<<"socket connected\n";

  while(1){
    cin>>buff;
    if(send(s,buff,sizeof(buff),0)==-1 ){
      cout<<"send failed\n";break;
    }
    cin>>buff;
    if(send(s,buff,sizeof(buff),0)==-1 ){
      cout<<"send failed\n";break;
    }

    if(recv(s,buff,sizeof(buff),0)==-1){
      cout<<"Receiving failed\n";
      break;
    }
    string str =string(buff);
    cout<<"Received: "<<str<<endl;
  }
  close(s);
}
