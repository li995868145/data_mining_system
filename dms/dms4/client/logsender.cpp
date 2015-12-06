#include "logsender.h"		
#include "dmsexception.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;
LogSender::LogSender(){
    port=8899;
    strcpy(serverIp,"127.0.0.1");
    strcpy(failSendFileName,"sendfailed.dat");	
}
		
LogSender::~LogSender(){}
		
void   LogSender::sendMatches
			(list<MatchedLogRec> *matches){
	/*调用下面函数的顺序？*/			
     try{ 				
	 initNetWork();
     readSendFailed(matches);
     /*循环发送数据*/
     while(matches->size()>0){
	     int sfd=send(fd,&(*(matches->begin())),
				 sizeof (MatchedLogRec),0);
		 if(sfd<=0){
		     throw   DmsSendDataException("send data toserver failed"); 
		 }
		 matches->erase(matches->begin());
	 }	 
	 }catch(DmsInitNetWorkException e){
         cout<<e.what()<<endl;	 
	 }catch(DmsSendDataException  e){
	     cout<<e.what()<<endl;
	 }
	 close(fd);
}
void  LogSender::initNetWork(){
    fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1){
	    throw  DmsInitNetWorkException("init socket failed");
	}
	struct   sockaddr_in addr={0};
    addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=inet_addr(serverIp);
    int  cfd=connect(fd,(sockaddr*)&addr,sizeof addr);
    if(cfd==-1){
	    throw  DmsInitNetWorkException("connect server failed"); 
	}

}
void  LogSender::readSendFailed
			(list<MatchedLogRec> *matches){
			
}
void  LogSender::saveSendFailed
			(list<MatchedLogRec> *matches){
			
} 
