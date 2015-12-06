#include <iostream>
#include "logreader.h"
#include <list>
using namespace std;

int main(){
    cout<<"测试logreader"<<endl;
	LogReader   logreader;
	/*得到发送部分 要发送的集合*/
	list<MatchedLogRec> matches=logreader.readLogs();
}

