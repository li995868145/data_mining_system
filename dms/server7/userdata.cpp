#include "userdata.h"		 
/*给互斥量和条件量赋值*/ 
UserData::UserData(){
    pthread_mutex_init(&mutext,0);
	pthread_cond_init(&pcon,0);
	pthread_cond_init(&ccon,0); 
}
/*销毁条件量和互斥量*/
	     
UserData::~UserData(){
    pthread_mutex_destroy(&mutext);
	pthread_cond_destroy(&pcon);
	pthread_cond_destroy(&ccon);
}
/*线程安全的函数*/	 
         
void    UserData::push_back(MatchedLogRec mlog){
    pthread_mutex_lock(&mutext);
        while(datas.size()>1024*10){
		    /*等待生产条件为真*/
			pthread_cond_wait(&pcon,&mutext);
		}
		datas.push_back(mlog);
		/*当生产了一条数据后  肯定可以消费
		 通知消费者*/
		pthread_cond_signal(&ccon);
	pthread_mutex_unlock(&mutext);
}
	     
MatchedLogRec   UserData::frontAndPop(){
    pthread_mutex_lock(&mutext);
        while(datas.empty()){
			/*等待消费条件为真*/
		    pthread_cond_wait(&ccon,&mutext);
		}
        MatchedLogRec   mlog=datas.front();
		datas.pop_front();
		/*消费了一条数据后 肯定是可以生产数据
		 通知生产*/
        pthread_cond_signal(&pcon);
	pthread_mutex_unlock(&mutext);
        return   mlog;
}

