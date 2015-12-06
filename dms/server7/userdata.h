#ifndef    USERDATA_H
#define    USERDATA_H
#include   "data.h"
#include   <pthread.h>
#include   <deque>
using namespace std;
    class  UserData{
	     private:
		 /*真正存放数据的地方*/
		 deque<MatchedLogRec>  datas;
	     /*保证线程访问安全*/
	     pthread_mutex_t       mutext;
	     /*保证生产和消费的协调*/
	     pthread_cond_t        pcon;
	     pthread_cond_t        ccon;
	     public:
		 /*给互斥量和条件量赋值*/ 
	     UserData();
		 /*销毁条件量和互斥量*/
	     ~UserData();
	     /*线程安全的函数*/	 
         public: 
         void    push_back(MatchedLogRec mlog);
	     MatchedLogRec   frontAndPop();	 
	};
#endif
