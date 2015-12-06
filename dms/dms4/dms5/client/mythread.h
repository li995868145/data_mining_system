#ifndef  MYTHREAD_H
#define  MYTHREAD_H
#include <QThread>
    class  MyThread:public QThread{
		Q_OBJECT
	    public:
		void run();	
		/*定义一个信号 用来把发送的数据通知
		 给界面*/
		public:signals:
	    void   dataSig(QString  par);	   
	};
#endif
