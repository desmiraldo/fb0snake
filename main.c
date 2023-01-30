#include<pthread.h>
#include"snl/keyboard.h"
#include"snl/graph.h"


struct gjarprii{
	char kokah;
	char kokaw;
	char bishtih;
	char bishtiw;
};
struct food{
	int x;
	int y;
};

struct food snakefood;

#define GH 12
#define GW 18
#define WW 33
#define WH 14



unsigned char game[GH][GW];
char gameover = 0;
int snakebishti = 4;


int create_food(){
	jump:
	snakefood.x = rand() % GW;
	snakefood.y = rand() % GH;
	if(game[snakefood.y][snakefood.y] == 0){
		return 1;
	}
	goto jump;
}


int movesnake(char move,struct gjarprii snake){
	

	if(move == 1){
		if(game[snake.kokah][snake.kokaw - 1] == 0 || game[snake.kokah][snake.kokaw - 1] == 255){

			
			if(snake.kokaw - 1 < 0){
				gameover=1;
			}else{
				if(game[snake.kokah][(snake.kokaw - 1)] == 255){
					game[snake.kokah][(snake.kokaw - 1)] = 254;
					snakebishti = snakebishti+1;
					game[snake.bishtih][snake.bishtiw] = snakebishti;
					create_food();
					game[snakefood.y][snakefood.x] = 255;
					return 0;
				}else{
					game[snake.kokah][(snake.kokaw - 1)] = 254;
				}
			}
		}else{
			gameover=1;
		}
		
	}else if(move == 2){
		if(game[snake.kokah][(snake.kokaw + 1)] == 0  || game[snake.kokah][snake.kokaw + 1] == 255){
			if(snake.kokaw + 1 == GW){
				gameover = 1;
			}
			else{
				if(game[snake.kokah][(snake.kokaw + 1)] == 255){
					game[snake.kokah][(snake.kokaw + 1)] = 254;
					snakebishti = snakebishti+1;
					game[snake.bishtih][snake.bishtiw] = snakebishti;
					create_food();
					game[snakefood.y][snakefood.x] = 255;
					return 0;
				}else{
					game[snake.kokah][(snake.kokaw + 1)] = 254;
				}
			}
		}else{
			gameover=1;
		}
	
	}else if(move == 3){
		if(game[(snake.kokah - 1)][snake.kokaw] == 0  || game[snake.kokah-1][snake.kokaw] == 255){

			
			if((snake.kokah-1)<0){
				gameover=1;
			}else{
				if(game[snake.kokah - 1][snake.kokaw] == 255){
					game[snake.kokah - 1][snake.kokaw] = 254;
					snakebishti = snakebishti+1;
					game[snake.bishtih][snake.bishtiw] = snakebishti;
					create_food();
					game[snakefood.y][snakefood.x] = 255;
					return 0;
				}else{
					game[(snake.kokah - 1)][snake.kokaw] = 254;
				}
			}
		}else{
			gameover=1;
		}
	
	}else if(move == 4){
		if(game[(snake.kokah + 1)][snake.kokaw] == 0  || game[snake.kokah + 1][snake.kokaw] == 255){

			
			if((snake.kokah+1)>=GH){
					gameover=1;
			}else{
				if(game[snake.kokah + 1][snake.kokaw] == 255){
					game[snake.kokah + 1][snake.kokaw ] = 254;
					snakebishti = snakebishti+1;
					game[snake.bishtih][snake.bishtiw] = snakebishti;
					create_food();
					game[snakefood.y][snakefood.x] = 255;
					return 0;
				}else{
					game[(snake.kokah + 1)][snake.kokaw] = 254;
				}
			}
		}else{
			gameover=1;
		}
	
	}
	if(gameover==1){
		return 0;
	}

	if(game[snake.bishtih][(snake.bishtiw - 1)] == (snakebishti-1)){
		game[snake.bishtih][snake.bishtiw] = 0;
		game[snake.bishtih][(snake.bishtiw - 1)] = snakebishti;
	}else if(game[snake.bishtih][(snake.bishtiw + 1)] == (snakebishti-1)){
		game[snake.bishtih][snake.bishtiw] = 0;
		game[snake.bishtih][(snake.bishtiw + 1)] = snakebishti;
	}else if(game[(snake.bishtih - 1)][snake.bishtiw] == (snakebishti-1)){
		game[snake.bishtih][snake.bishtiw] = 0;
		game[(snake.bishtih - 1)][snake.bishtiw] = snakebishti;
	}else if(game[(snake.bishtih + 1)][snake.bishtiw] == (snakebishti-1)){
		game[snake.bishtih][snake.bishtiw] = 0;
		game[(snake.bishtih + 1)][snake.bishtiw] = snakebishti;
	}

	return 0;
}

int printgame(){
	//getting block size commponents 
	struct fb0size sizet;
	sizet = getfb0sz();
	float blocksz = (float)sizet.width/WW;
	int blockzsi = (int)blocksz;
	
	//creating max objects for game
	static struct object block[WH*WW];
	memset(block,0,sizeof(block));
	
	//creating snake body sketch
	FILE *fp;
	
	char *snkbody;
	snkbody = (char *)malloc(blockzsi*blockzsi*4);
	/*fp = fopen("textures/snakebody.rgba","r");
	fread(snkbody,1,blockzsi*blockzsi*4,fp);
	fclose(fp);*/
	
	memset(snkbody,254,blockzsi*blockzsi*4);
	
	int i=0,j=0,k=0;
			while(i<GH){
				j=0;
				while(j<GW){
					if(game[i][j] <= snakebishti && game[i][j]!=0){
						block[k].name = "snake";
						block[k].width = blockzsi;
						block[k].height = blockzsi;
						block[k].x = (j+1)*blockzsi;
						block[k].y = (i+1)*blockzsi;
						block[k].sketch = (char *)snkbody;
						//printf("\n%d",block[k].x);
						k++;
					}else if(game[i][j] == 255){
						block[k].name = "food";
						block[k].width = blockzsi;
						block[k].height = blockzsi;
						block[k].x = (j+1)*blockzsi;
						block[k].y = (i+1)*blockzsi;
						block[k].sketch = (char *)snkbody;
						k++;
					}
					j++;
				}
				i++;
			}
	//r and l borders
	char *borderlr;
	borderlr = (char *)malloc(blockzsi*blockzsi*4*(WH+1));
	memset(borderlr,254,blockzsi*blockzsi*4*(WH+1));
	
	block[k].name="border left";
	block[k].width = blockzsi;
	block[k].height = (WH)*blockzsi;
	block[k].sketch = (char *)borderlr;
	block[k].x=0;
	block[k].y=0;
	k++;
	block[k].name="border right";
	block[k].width = blockzsi;
	block[k].height = (WH)*blockzsi;
	block[k].sketch = (char *)borderlr;
	block[k].x=blockzsi*(GW+1);
	block[k].y=0;
	k++;
	block[k].name="border right++";
	block[k].width = blockzsi;
	block[k].height = (WH)*blockzsi;
	block[k].sketch = (char *)borderlr;
	block[k].x=blockzsi*(WW-1);
	block[k].y=0;
	
	//t and b borders
	k++;
	char *bordertb;
	bordertb = (char *)malloc(blockzsi*blockzsi*4*(WW+1));
	memset(bordertb,254,blockzsi*blockzsi*4*(WW+1));
	
	block[k].name="border top";
	block[k].width = blockzsi*(WW);
	block[k].height = blockzsi;
	block[k].sketch = (char *)bordertb;
	block[k].x=0;
	block[k].y=0;
	k++;
	block[k].name="border right";
	block[k].width = (WW)*blockzsi;
	block[k].height = blockzsi;
	block[k].sketch = (char *)bordertb;
	block[k].x=0;
	block[k].y=blockzsi*(GH+1);
	
	
	//exit(1);
	//printf("%d\n",block[k].height);


	//puting numbers

	char *chars;
	chars = (char *)malloc(31*31*4);
	fp = fopen("textures/s.rgba","r");
	fread(chars,1,31*31*4,fp);
	fclose(fp);
	k++;
	block[k].name = "s";
	block[k].width = 31;
	block[k].height = 31;
	block[k].x = (WW - 8)*blockzsi;
	block[k].y = (2)*blockzsi;
	block[k].sketch = (char *)chars;


	char *chara;
	chara = (char *)malloc(31*31*4);
	fp = fopen("textures/n.rgba","r");
	fread(chara,1,31*31*4,fp);
	fclose(fp);
	k++;
	block[k].name = "n";
	block[k].width = 31;
	block[k].height = 31;
	block[k].x = (WW - 7)*blockzsi;
	block[k].y = (2)*blockzsi;
	block[k].sketch = (char *)chara;

	char *charr;
	charr = (char *)malloc(31*31*4);
	fp = fopen("textures/a.rgba","r");
	fread(charr,1,31*31*4,fp);
	fclose(fp);
	k++;
	block[k].name = "n";
	block[k].width = 31;
	block[k].height = 31;
	block[k].x = (WW - 6)*blockzsi;
	block[k].y = (2)*blockzsi;
	block[k].sketch = (char *)charr;

	char *chark;
	chark = (char *)malloc(31*31*4);
	fp = fopen("textures/k.rgba","r");
	fread(chark,1,31*31*4,fp);
	fclose(fp);
	k++;
	block[k].name = "n";
	block[k].width = 31;
	block[k].height = 31;
	block[k].x = (WW - 5)*blockzsi;
	block[k].y = (2)*blockzsi;
	block[k].sketch = (char *)chark;

	char *chare;
	chare = (char *)malloc(31*31*4);
	fp = fopen("textures/e.rgba","r");
	fread(chare,1,31*31*4,fp);
	fclose(fp);
	k++;
	block[k].name = "n";
	block[k].width = 31;
	block[k].height = 31;
	block[k].x = (WW - 4)*blockzsi;
	block[k].y = (2)*blockzsi;
	block[k].sketch = (char *)chare;

	drawfb0(block);
	free(chars);
	free(chara);
	free(snkbody);
	
}

void *gamematrix(){
	int times = 0;

	int lsnakemax = GH * GW;
	struct gjarprii gjarpri;
	memset(game,0,sizeof(game));
	game[0][1] = snakebishti;
	game[0][2] = 3;
	game[0][3] = 2;
	game[0][4] = 1;
	game[1][8] = 255;


	char move = 4;
	int i=0,j=0;
	while(1){
			if(retkey == 105){
				if(move != 2){
					move=1;
				}
			}else if(retkey == 106){
				if(move != 1){
				move=2;
				}
			}else if(retkey == 103){
				if(move != 4){
					move=3;
				}
			}else if(retkey == 108){
				if(move !=3){
					move=4;				
				}
			}
			
			
			if(gameover==0 && times!=0){	
				movesnake(move,gjarpri);
				if(gameover == 1){
					return 0;
				}
				i=0;
				while(i<GH){
					//printf("\n");
					j=0;
					while(j<GW){
						//printf("%d",game[i][j]);
						if((game[i][j] < snakebishti) && game[i][j]!=0){
								game[i][j]=game[i][j]+1;
							
						}
						j++;
					}
					i++;
				}

				i=0;
				//system("clear");
				while(i<GH){
					//printf("\n");
					j=0;
					while(j<GW){
						
						if(game[i][j] == 254){
							game[i][j] = 1;
							gjarpri.kokah = i;
							gjarpri.kokaw = j;
						}else if(game[i][j] == snakebishti){
							gjarpri.bishtih = i;
							gjarpri.bishtiw = j;
						}
						//printf("%d",game[i][j]);
						j++;
					}
					i++;
				}
				//return 0 ;
				printgame();

				
			}else{
				i=0;
				while(i<GH){
					j=0;
					while(j<GW){
						
						if(game[i][j] == 254 || game[i][j] == 1){
							game[i][j] = 1;
							gjarpri.kokah = i;
							gjarpri.kokaw = j;
						}else if(game[i][j] == snakebishti){
							gjarpri.bishtih = i;
							gjarpri.bishtiw = j;
						}
						j++;
					}
					i++;
				}
				times++;
			}
			
			//printf("\n");


			
			
			
		
			usleep(300000);
		

	}


}

int main(){
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, key, NULL);
	pthread_create(&thread2, NULL, gamematrix, NULL);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	return 0;

}
