#include <iostream>
#include "data.h"
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <deque>
using namespace std;
/*数据缓冲池*/
deque<MatchedLogRec>   datapool;
/*写一个线程  封装一个生产者线程*/
class   ProducterThread{
/*线程处理函数*/
public:	
static void*    reciveData(void *par){
	/*把par做为this*/
    ((ProducterThread*)par)->run();
}	
/*真正完成线程功能的函数*/
virtual void    run(){
	int afd=this->afd;
	while(1){
        MatchedLogRec   mlog={0};
        int  rfd=recv(afd,&mlog,sizeof mlog,0);
	    if(rfd>0){
			/*把接收到的数据放入数据缓冲池*/
			datapool.push_back(mlog);
	        cout<<afd<<":"<<mlog.logname<<":"<<
				mlog.logip<<endl;
     	}else{
	        break;
      	}
	}
	close(afd);
	//delete   this;
}
    private:
	int   afd;
    pthread_t  thid;
    public:
    ProducterThread(int afd){
	    this->afd=afd;
	}	
    public:
	void  start(){
     	pthread_create(&thid,0,reciveData,
				this);	
	}
};
/*消费者线程的作用 是从datapool 中取出数据*/
class   CustomerThread{
    private:
	pthread_t  thid;
	public:
    CustomerThread(){
	}
    public:
	/*供pthread_create 调用的函数*/
    static  void*  getData(void*par){
	    ((CustomerThread*)par)->run();
	}
    public:
	/*真正完成线程功能的函数*/
	void  run(){
		while(1){
            MatchedLogRec  mlog=
		        datapool.front();
			/*调用Dao的存储函数把数据
			 放入数据库*/
	        datapool.pop_front();		
		}
	}
	/*启动线程的函数*/
	void  start(){
        pthread_create(&thid,0,getData,this);   	
	}
};
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
	/*当接收到客户端时  启动线程为客户端进行服务*/
   // pthread_t    thid;
	/*ProducterThread   *producter=new 
		 ProducterThread(afd);
    producter->start();*/
	 ProducterThread  producter(afd);
	 producter.start();
	}
	close(fd);
}

