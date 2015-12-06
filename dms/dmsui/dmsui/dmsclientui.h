#ifndef DMSCLIENTUI_H
#define DMSCLIENTUI_H
#include <QTextBrowser>
#include <QDialog>
#include <QPushButton>
#include "mythread.h"
     class  DmsClient:public QDialog{
		 Q_OBJECT
	     private:
	     QTextBrowser   *showdata;
         QPushButton    *bstart;
         QPushButton    *bclose;
		 /*这就是访问界面的线程指针*/
         MyThread       *myth;
         public:
         DmsClient();
         ~DmsClient();
         /*槽函数负责 启动客户端*/
         public slots:
	     void   startClient();
		 /*接收线程信号中的数据*/
         void   getData(QString  data);
	 };
#endif
