#include "logreader.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <cstring>
#include <time.h>
#include <stdio.h>
using namespace std;
LogReader::LogReader(){
	strcpy(logFileName,"/home/tarena/dms5/client/wtmpx");
	strcpy(backFileName,"wtmpx");
    strcpy(failLoginsFileName,"failmatchlogins.dat");
}
	    
LogReader::~LogReader(){}
	    
list<MatchedLogRec>  LogReader::readLogs(){
    /*顺序调用5个私有函数*/
	backup();
	readFailLogins();
	readBackupFile();
	cout<<"logins="<<logins.size()<<endl;
	cout<<"logouts="<<logouts.size()<<endl;
    matchLogRec();
	cout<<"---------------"<<endl;
	cout<<"logins="<<logins.size()<<endl;
	cout<<"logouts="<<logouts.size()<<endl;
	cout<<"matches="<<matches.size()<<endl;
	saveFailLogins();
	rename(backFileName,"/home/tarena/dms5/client/wtmpx");
    return  matches;
}
	    
void  LogReader:: backup(){
    cout<<"1.备份并清空日志文件"<<endl;
    /*备份出的文件名以 yyyymmdd-hh:mi:sswtmpx 
	 20130111 20131101*/
	time_t   mytime=time(NULL);
	struct   tm* mytm=localtime(&mytime);
	sprintf(backFileName,"/home/tarena/dms5/client/%4d%02d%02d-%02d%02d%02dwtmpx",
			mytm->tm_year+1900,mytm->tm_mon+1,mytm->tm_mday,
			mytm->tm_hour,mytm->tm_min,mytm->tm_sec); 
    rename(logFileName,backFileName);
}
	    
void  LogReader:: readFailLogins(){
    cout<<"2.读取上一次匹配失败的登入记录"<<endl;
    /*以结构体为单位进行读取*/
    int  fd=open(failLoginsFileName,O_CREAT|O_RDONLY,0777);
	while(1){
		LogRec   log={0};
	    int  rfd=read(fd,&log,sizeof  log);
        if(rfd<=0){
		    break;
		}
		logins.push_back(log);
	}
    close(fd);	
}
	    
void  LogReader:: readBackupFile(){
    cout<<"3.读取备份的日志文件"<<endl; 
	/*把读取到的数据  包装成对象 然后按照
	  登入登出类型 分别放入 logins  logouts*/
	int  fd=open(backFileName,O_RDONLY);
	if(fd==-1){
	    cout<<"open backfile failed"<<endl;
	}
    struct  stat fs={0};
    fstat(fd,&fs);
    cout<<fs.st_size<<endl;    	
	int   loopcount=(fs.st_size)/372;
	for(int i=0;i<loopcount;i++){
	    LogRec   log={0};
		read(fd,&log.logname,32);
		lseek(fd,36,SEEK_CUR);
		read(fd,&log.pid,4);
		log.pid=htonl(log.pid);
		read(fd,&log.logtype,2);
		log.logtype=htons(log.logtype); 
		lseek(fd,6,SEEK_CUR);
		read(fd,&log.logtime,4);
		log.logtime=htonl(log.logtime);
		lseek(fd,30,SEEK_CUR);
		read(fd,log.logip,257);
		/*把点开头的用户名去掉*/
		if(log.logname[0]!='.'){
		//cout<<log.logname<<":"<<log.logtype<<endl;
			if(log.logtype==7){
			     logins.push_back(log);
			}else if(log.logtype==8){
			     logouts.push_back(log); 
			}else{
			    ;
			}
		}
		lseek(fd,1,SEEK_CUR);
	}
}
	    
void  LogReader:: matchLogRec(){
    cout<<"4.匹配日志记录得到匹配集合"<<endl;  
	 /*logname  pid   logip 相同就是匹配*/
	/*1.从匹配集合中循环取出登出记录
	  2.在登入集合中循环查找 
	    如果找到匹配 就构建匹配对象  给匹配对象赋值
	    删除登入记录  终断本次查找
	    如果本次没找到 则继续查找 直到循环结束
	  3.当所有的登出记录查找结束 清空登出集合*/
	  list<LogRec>::iterator  oit;
	  list<LogRec>::iterator  iit;
	 for(oit=logouts.begin();oit!=logouts.end();oit++){
	     iit=logins.begin();
		 while(iit!=logins.end()){
		     if(!strcmp(iit->logname,oit->logname)
			    && iit->pid==oit->pid &&
				!strcmp(iit->logip,oit->logip)){
			     MatchedLogRec  mlog={0};
				 //赋值
				 strcpy(mlog.logname,iit->logname);
                 mlog.pid=iit->pid;
				 mlog.logintime=iit->logtime;
				 mlog.logouttime=oit->logtime;
				 mlog.durations=mlog.logouttime-
					 mlog.logintime;
				 strcpy(mlog.logip,iit->logip); 
				 matches.push_back(mlog);	 
				 logins.erase(iit);
			     break;	 
			 }
			 iit++;
		 } 
	 }
	 logouts.clear(); 
}
	    
void  LogReader:: saveFailLogins(){
    cout<<"5.保存没有匹配成功的登入记录"<<endl;
    int  fd=open(failLoginsFileName,O_CREAT|O_RDWR|O_TRUNC,0777);
    if(fd==-1){
	    cout<<"open file failed"<<endl;
	}
	/*以结构体为单位 把数据写入文件*/
    while(logins.size()>0){
        int wfd=write(fd,&(*(logins.begin())),
				sizeof(LogRec));
	    if(wfd<=0){
		     break;
		} 	
        logins.erase(logins.begin());
	}
	close(fd);
}	

