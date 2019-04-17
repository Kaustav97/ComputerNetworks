#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main(){
	struct sockaddr_in server,client;
	int s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)return 0;
	cout<<"socket created"<<endl;
	
	int port; cout<<"PORT: ";
	cin>>port;
	server.sin_family=AF_INET;
	server.sin_port=htons(port);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	bind(s,(struct sockaddr*)&server,sizeof(server));
	cout<<"binding done"<<endl;
	
	int r=listen(s,1);
	cout<<"listening"<<endl;
	
	socklen_t len=sizeof(client);	
	int ns=accept(s,(struct sockaddr*)&client,&len);
	cout<<"accepting"<<endl;
	
	while(true){
	
		int flen=0;
		recv(ns,&flen,sizeof(flen),0);
		char buff[flen];
		buff[flen]='\0';
		if(recv(ns,buff,flen,0)==-1)return 0;
		cout<<"FNAME : "<<string(buff)<<endl;
	
		cout<<"CONTENTS:"<<endl;
		
		ifstream fin;
		fin.open(buff);
		string ans;
		if(fin)cout<<"READING"<<endl;
		else ans="NF";
		
		while(fin){
			string line;
			getline(fin,line);
			ans+=line+'\n';
		}
		int alen=ans.size();
		send(ns,&alen,sizeof(alen),0);
		send(ns,ans.c_str(),ans.size(),0);					
	}	
	close(ns);close(ns);					
}







