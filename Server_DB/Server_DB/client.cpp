#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

using namespace std;

void send_str(string &str,int &addr){
  int flen=str.size();
  send(addr,&flen,sizeof(flen),0);
  send(addr,str.c_str(),str.size(),0);
}
void recv_str(string &str,int &addr){
  int rlen;
  recv(addr,&rlen,sizeof(int),0);

  char cont[rlen];
  cont[rlen]='\0';
  recv(addr,cont,rlen,0);
  str=string(cont);
}

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

  while(true){
    string cont;
    recv_str(cont,s);
    cout<<cont<<endl;

    int sel; cin>>sel;
    send(s,&sel,sizeof(int),0);

    if(sel==1){
      string src; cin>>src;
      send_str(src,s);
    }
    
    if(sel==2){
      string src; cin>>src;
      send_str(src,s);                 	    	    
    }
    if(sel==3){
      string prmp;
      recv_str(prmp,s);
      cout<<recv<<endl;
      
      string subcode,name;
      cin>>subcode>>name;
      send_str(subcode,s);
      send_str(name,s);    
      /*
      int mks;
      recv(s,&mks,sizeof(int),0);
      cout<<mks<<endl;*/
    }

    string ans;
    recv_str(ans,s);
    cout<<ans<<endl;
  }
}
