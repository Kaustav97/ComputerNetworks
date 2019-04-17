#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <fstream>
#include <pthread.h>

using namespace std;

// REGNO ->
struct location{
  string name,address;
  // location(string n,string a):name(n),address(a){}
};
// NAME ->
struct enroll{
  string dept,sem,sectn;
};

unordered_map<string,location> locdb;
unordered_map<string,enroll> coursedb;
unordered_map<string,vector< pair<string,int > > > marks;

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

void* regno_resp(void *Tid){
  string rno;
  int clt= *((int*)Tid);
  recv_str(rno,clt);
  
  cout<<"GOT: "<<rno<<endl;
  string ans="";  
  ans= locdb[rno].name+" - "+locdb[rno].address+"\0";
  send_str(ans,clt);
}

void* name_resp(void* Tid){
  string nm;  
  int clt= *((int*)Tid);
    
  recv_str(nm,clt);
  string ans;
  ans = coursedb[nm].dept+" - "+ coursedb[nm].sem+" - "+coursedb[nm].sectn+"\0";
  send_str(ans,clt);
}

void* subj_resp(void *Tid){
  string subcode,name;
  cin>>subcode>>name;

  int clt= *((int*)Tid);
  
  recv_str(subcode,clt);
  recv_str(name,clt);
  
  string ans="";
     
  for(auto x:marks[subcode]){
    if(x.first==name){
      int mks=x.second;
      ans=to_string(mks);
    }
  }
  //send(clt,&mks,sizeof(int),0);
  send_str(ans,clt);
}


int main(){  
  coursedb["Sayan"]= enroll{"ICT","6","B"};
  coursedb["Kaustav"]= enroll{"CCE","3","C"};
  coursedb["Kunal"]= enroll{"CSE","4","A"};
  
  locdb["156"]=location{"Kunal","Powai"};
  locdb["163"]=location{"Kaustav","Mumbai"};
  locdb["144"]=location{"Sayan","Kolkata"};
  
  marks["ICT01"]={make_pair("Sayan",99), make_pair("Kunal",98)};

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

  pthread_t op1,op2,op3;
	while(true){
		string ans1="1.Regno 2.Name 3.SubCode";
		send_str(ans1,ns);

		int sel;
		recv(ns,&sel,sizeof(int),0);

		if(sel==1){
      pthread_create(&op1,NULL,regno_resp,&ns);      
      pthread_join(op1,NULL);
		}
		if(sel==2){
      pthread_create(&op2,NULL,name_resp,&ns);      
      pthread_join(op2,NULL);      		
		}
		if(sel==3){
      pthread_create(&op3,NULL,subj_resp,&ns);      
      pthread_join(op3,NULL);      		
		}

		// send_str(ans,ns);
	}
  pthread_exit(NULL);
	close(ns);close(ns);
}
