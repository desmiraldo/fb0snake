#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<linux/input.h>
#include<pthread.h>

#include "key.h"

void INThandler(){
	exit(0);
}

int retkey;

void *key(void *p){
	int device;
	char path[255];
	strcpy(path,keyboardpath());
	device = open(path,O_RDONLY);
	struct input_event ev;

	signal(SIGINT, INThandler);
	while(1){
		read(device,&ev,sizeof(ev));
		if(ev.type == 1 && ev.value == 1){
			retkey = ev.code;
		}
	}
	return 0;
}
