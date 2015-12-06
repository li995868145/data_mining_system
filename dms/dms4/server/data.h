#ifndef   DATA_H
#define   DATA_H
    struct  LogRec{
	    char  logname[32];
		int   pid;
		short logtype;
	    int   logtime;
	    char  logip[257];	
	};
    struct  MatchedLogRec{
	    char   logname[32];
        int    pid;
	    int    logintime;
	    int    logouttime;
	    int    durations;
	    char   logip[257]; 
	    /*出租服务器的ip*/
	    char   serverip[20];	
	};
#endif
