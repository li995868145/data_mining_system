#include "dmsclientui.h"         
#include <pthread.h>
DmsClient::DmsClient(){
    this->resize(500,600);
	showdata=new QTextBrowser(this);
	showdata->resize(460,500);
	bstart=new QPushButton("start",this);
	bclose=new QPushButton("close",this);
	showdata->move(20,20);
	bstart->move(100,540);
	bclose->move(300,540);
	myth=new  MyThread();
	/*绑定线程 和 当前对象*/
	connect(myth,SIGNAL(dataSig(QString)),
			this,SLOT(getData(QString)));
	/*连接bstart 和 槽函数*/
	connect(bstart,SIGNAL(clicked()),
			this,SLOT(startClient()));
}
         
DmsClient::~DmsClient(){
    delete showdata;
	delete bstart;
	delete bclose;
}
/*把耗时的操作交给线程*/
void  *  processData(void *par){
	QTextBrowser *showdata=(QTextBrowser*)par;
	sleep(1);
	showdata->append("send data to server");
	sleep(1);
	showdata->append("send data to server");
	sleep(1);
	showdata->append("send data to server");
	sleep(1);
    showdata->append("send data over");
	return par;
}

/*槽函数负责 启动客户端*/
	     
void   DmsClient::startClient(){
    showdata->append("start client");
	/*创建线程
	pthread_t  thid;
	pthread_create(&thid,0,processData,
			showdata);*/
	/*启动qt的线程*/
	myth->start();
}
void  DmsClient::getData(QString  data){
    showdata->append(data); 
}

