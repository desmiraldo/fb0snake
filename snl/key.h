
char *keyboardpath(){
	//get keyboard location device
	char *buff;
	FILE *fp;
	long int size;
	static char c=' ',path[255];
	int i=0,len,j,check=0,check1=0,loc=-1,len1;
	char *word = "Keyboard";
	char *word1 = "/input/";
	len = strlen(word);
	len1 = strlen(word1);
	fp = fopen("/proc/bus/input/devices","r");
	while(c!= -1){
		c=fgetc(fp);
		i++;
	}
	size = i;
	buff = (char *)malloc(size);
	fseek(fp,0L,SEEK_SET);
	fread(buff,i,1,fp);
	i=0;
	j=0;
	check = 0;
	check1 = 0;
	//get location of keyword
	while(i < size){
		while(j < len && check != 2){
			if(word[j] == buff[i+j]){
				check = 1;
			}else{
				check = 0;
				break;
			}
			j++;
		}
		if(check == 1){
			check=2;
		}
		j=0;
		while(j < len1 && check == 2 && check1 != 2){
			if(word1[j] == buff[i+j]){
				check1 = 1;
			}else{
				check1 = 0;
				loc=i+1;
				break;
			}
			j++;
		}
		if(check1 == 1){
			check1 = 2;
		}
		j=0;
		if(check1==2 && buff[i]!='\n'){
			path[i-loc] = buff[i];
		}else if(check1 == 2 && buff[i]=='\n'){
			path[i-loc] = '\0';
			break;
		}
		i++;
	}
	static char rpath[255]="/dev";
	char vpath[255]="/input/event";
	//char *last = &path[strlen(path)-1];
	char *last = "2";
	strcat(rpath,vpath);
	strcat(rpath,last);
	free(buff);
	fclose(fp);
	return rpath;
}
