#ifndef  DMSEXCEPTION_H
#define  DMSEXCEPTION_H
#include <string.h>
    class   DmsException{
	    private:
	    char    msg[200];		
	    public:
		DmsException(){
		    strcpy(msg,"dms exception"); 
		}
		DmsException(const char *msg){
		    strcpy(this->msg,msg);
		}
		public:
		virtual const char *  what()const throw(){
		    return  msg;
		}
	};
    class  DmsClientException:public DmsException{
	    public:
		DmsClientException():DmsException("dms client exception"){
		    
		}
	    DmsClientException(const char *msg)
			:DmsException(msg){
		
		}	
	   /*	public:
        const  char* what()const  throw(){
		    return  "test  dms  client exception"; 
		}*/
	};
    /*让DmsInitNetWorkException  和DmsDataSendException 
	 继承自DmsClientException*/
    class   DmsInitNetWorkException:
		public DmsClientException{
	    public:
		DmsInitNetWorkException():
			DmsClientException("dms init network exception"){
		
		}	
		DmsInitNetWorkException(const char*msg):
			DmsClientException(msg){
			
		}
	}; 
    class   DmsSendDataException:
		public DmsClientException{
	    public:
		DmsSendDataException():
			DmsClientException("dms send data exception"){
		
		}	
		DmsSendDataException(const char*msg):
			DmsClientException(msg){
			
		}
	}; 
#endif

