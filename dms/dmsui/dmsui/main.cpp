#include "dmsclientui.h"
#include <QApplication>
int main(int argc,char **argv){
	QApplication app(argc,argv);
    DmsClient   dmsc;
	dmsc.show();
    return  app.exec();
}
