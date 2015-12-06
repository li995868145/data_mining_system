/*制造一个文件被不断访问的场景*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int  main(){
    double    data=1.0;
    while(1){
	    int  fd=open("logwtmpx.dat",O_CREAT|O_RDWR|O_APPEND,0777);
		char   datastr[50]={0};
		sprintf(datastr,"%lf\n",data);
        write(fd,datastr,strlen(datastr));
		data=data+1.0;
		close(fd);
	}
}


