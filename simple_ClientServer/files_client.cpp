#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

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
	string buff;cin>>buff;
	int flen=buff.size();
	send(s,&flen,sizeof(flen),0);
	send(s,buff.c_str(),buff.size(),0);

	int rlen;
	recv(s,&rlen,sizeof(rlen),0);

	char cont[rlen];
	cont[rlen]='\0';
	recv(s,cont,rlen,0);
	if(string(cont)=="NF")cout<<"FILE NOT PRESENT"<<endl;
	else cout<<string(cont)<<endl;		    
  }
}




