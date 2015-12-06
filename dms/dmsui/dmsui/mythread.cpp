#include "mythread.h"
void  MyThread::run(){
    /*直接发送数据*/
	sleep(1);
   	qDebug("send data to server");
	emit dataSig("send data to server");
	sleep(1);
   	qDebug("send data to server");
	emit dataSig("send data to server");
	sleep(1);
   	qDebug("send data to server");
	emit dataSig("send data to server");
	sleep(1);
   	qDebug("send data over");
	emit dataSig("send data over"); 
}

