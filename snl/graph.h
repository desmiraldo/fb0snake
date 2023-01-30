#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FB0 "/sys/class/graphics/fb0/virtual_size"
#define FB0P "/dev/fb0"
struct fb0size{
	int height;
	int width;
};

struct object{
	char *name;
	int width;
	int height;
	int x;
	int y;
	char *sketch;
};

struct fb0size getfb0sz(){
	int len;
	FILE *fp;
	char *buff;
	struct fb0size sizet;

	fp = fopen(FB0,"r");
	fseek(fp,0L,SEEK_END);
	len = ftell(fp);
	fseek(fp,0L,SEEK_SET);
	buff = (char *)malloc(len);
	fread(buff,len,1,fp);

	char *width = strtok(buff,",");
	char *height = strtok(NULL,",");

	sizet.width = atoi(width);
	sizet.height = atoi(height);
	free(buff);

	return sizet;
}

int drawfb0(struct object *block){
	struct fb0size sizet;
	sizet = getfb0sz();
	float blocksz = (float)sizet.width/33.000;
	int blockzsi = (int)blocksz;
	//create buffer
	unsigned char *buffer;
	buffer = (char *)malloc(sizet.height * sizet.width * 4);
	memset(buffer,0,sizet.height*sizet.width * 4);
	
	//writing object to buffer
	int i=0,j=0,bid=0;
	while(block[bid].width != 0){
		i=0;
		while(i < block[bid].height){
			while(j < (block[bid].width*4)){
				buffer[((i+block[bid].y)*sizet.width*4)+(block[bid].x*4)+j] = block[bid].sketch[(i*block[bid].width*4) + j];
				//printf("\n%d",buffer[(i*sizet.width)+100+j]);
				buffer[((i+block[bid].y)*sizet.width*4)+(block[bid].x*4)+j+1] = block[bid].sketch[(i*block[bid].width*4)+(j+1)];
				buffer[((i+block[bid].y)*sizet.width*4)+(block[bid].x*4)+j+2] = block[bid].sketch[(i*block[bid].width*4)+(j+2)];
				buffer[((i+block[bid].y)*sizet.width*4)+(block[bid].x*4)+j+3] = block[bid].sketch[(i*block[bid].width*4)+(j+3)];
				j = j + 4;
				//printf("\n-- %d",block[bid].x);
			}
			j=0;
			i++;
		}
		//printf("\n %d",block[bid].x);
		bid++;
	}
	//exit(1);
	FILE *fp;
	fp = fopen("/dev/fb0","w");
	fwrite(buffer,1,sizet.height*sizet.width * 4,fp);
	fclose(fp);
	free(buffer);
}
