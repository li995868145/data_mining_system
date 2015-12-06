#ifndef LOGREADER_H
#define LOGREADER_H
#include "data.h"
#include <list>
using namespace std;
    class  LogReader{
	    private:
	    char   logFileName[52];
        char   backFileName[52];
        char   failLoginsFileName[52];
	    list<LogRec>  logins;
	    list<LogRec>  logouts;
	    list<MatchedLogRec> matches;
	    public:
	    LogReader();
	    ~LogReader();
	    list<MatchedLogRec>  readLogs();
	    private:
	    void   backup();
	    void   readFailLogins();
	    void   readBackupFile();
	    void   matchLogRec();
	    void   saveFailLogins();	
	};
#endif
