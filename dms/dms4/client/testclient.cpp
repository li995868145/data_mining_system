#include <iostream>
#include "logreader.h"
#include "logsender.h"
#include <list>
using namespace std;

int main(){
    //cout<<"测试logreader"<<endl;
	LogReader   logreader;
	LogSender   logsender;
	/*得到发送部分 要发送的集合*/
	list<MatchedLogRec> matches=logreader.readLogs();
	logsender.sendMatches(&matches);
}

