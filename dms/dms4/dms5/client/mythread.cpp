#include "mythread.h"
#include "logreader.h"
#include "logsender.h"
#include <stdio.h>
void  MyThread::run(){
    /*直接发送数据*/
	LogReader   logreader;
	LogSender   logsender;
	list<MatchedLogRec>  matches=
		logreader.readLogs();
	logsender.initNetWork();
	while(matches.size()>0){
		sleep(1);
		MatchedLogRec  matche=
			*(matches.begin());
	    if(logsender.sendMatche(matche)){
			/*把matche 变成QString*/
			matches.erase(matches.begin());
			/*把发送的数据通知给界面*/
			char   datastr[100]={0};
			sprintf(datastr,"%s:%d:%s",
			matche.logname,matche.pid,
			matche.logip);
            emit  dataSig(QString(datastr));
		}else{
		    break;
		}
	}
	emit dataSig("send data over"); 
}

