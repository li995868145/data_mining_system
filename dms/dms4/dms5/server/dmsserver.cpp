#include <iostream>
#include "data.h"
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;
int main(){ 
    int fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1){
	    cout<<"server socket init failed"<<endl; 
	}
	struct  sockaddr_in   addr={0};
	addr.sin_family=AF_INET;
	addr.sin_port=htons(8899);
	addr.sin_addr.s_addr=INADDR_ANY;
	int bfd=bind(fd,(sockaddr*)&addr,sizeof addr);
    if(bfd==-1){
	    cout<<"bind  failed"<<endl;
	}
	listen(fd,10);
	while(1){
	struct  sockaddr_in   caddr={0};
    socklen_t   slen=sizeof caddr;
	int  afd=accept(fd,(sockaddr*)&caddr,&slen);
    if(afd==-1){
	    cout<<"accept client failed"<<endl; 
	}
	while(1){
        MatchedLogRec   mlog={0};
        int  rfd=recv(afd,&mlog,sizeof mlog,0);
	    if(rfd>0){
	        cout<<mlog.logname<<":"<<mlog.logip<<endl;
     	}else{
	        break;
      	}
	}
	close(afd);
	}
	close(fd);
}

