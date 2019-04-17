#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;
char buff[50],buff1[50];

string Palin(string str){
  for(int i=0;i<str.size()/2;i++){
    if(str[i]!=str[str.size()-i-1])return "NOT";
  }
  return "PAILN";
}

int main(){
  struct sockaddr_in server,client;
  int s=socket(AF_INET,SOCK_STREAM,0);
  if(s==-1){cout<<"Socket error\n";return 0;}
  cout<<"Socket created\n";

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
  int ns=accept(s,(struct sockaddr*)&client,&len);
  if(ns==-1){close(s);return 0;}
  cout<<"socket accepting\n";

  int clk=1;
  string qry,srch;
  while(1){
    if(recv(ns,buff,sizeof(buff),0)==-1){
      cout<<"Receiving string failed\n";
      break;
    }
    srch=string(buff);cout<<"GOT QRY\n";
    // else{ srch=string(buff);cout<<"GOT SRCH\n";}

    if(recv(ns,buff,sizeof(buff),0)==-1){
      cout<<"Receiving string failed\n";
      break;
    }
    if(clk%2)qry=srch;
    // srch=string(buff);cout<<"GOT SRCH\n";
    // if(clk%2==0)srch=string(buff);

    if(clk%2==0){
      printf("QRY: %s\nSRCH: %s\n",qry.c_str(),srch.c_str());
      string rnd=(qry.find(srch)==string::npos)?"NOT FOUND":"FOUND";
      char ans[50];
      strcpy(ans,rnd.c_str());
      if(send(ns,ans,sizeof(ans),0)==-1){
        cout<<"Sending Failed\n";
        break;
      }
    }
    clk++;
    cout<<"SENT"<<endl;
  }

}
