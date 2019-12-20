#include <winbgim.h>
#include <windows.h>

#define SCR_WIDTH 1200
#define SCR_HEIGHT 700
#define SCALE 12
#define LOW_WIDTH (SCR_WIDTH/SCALE*2)
#define LOW_HEIGHT SCR_HEIGHT/SCALE
#define TAN30 0.5 
#define CENTERX SCR_WIDTH/2
#define CENTERY SCR_HEIGHT/2
#define DELAY 70
#define DIR_UP	1
#define DIR_DN	2
#define DIR_LT	3
#define DIR_RT	4
#define DIR_UPLT	5
#define DIR_UPRT	6
#define DIR_DNLT	7
#define DIR_DNRT	8




void Tri(int x, int y, int col);
void Setka();
void Draw();
void InitScene();
void UpdateScene();
void Keys();
void GameOver();


int Play=1, Num=20, Dir=0, Move=1;

struct Point{
	int x;
	int y;
} Snake[100], Apple;

void Tri(int x, int y, int color=255){   // x,y - коорд. левой вершины, size-ширина, dir=0 - вверх, dir=1 - вниз
	int poly[6], x1, y1;
	
	
	if (color<255) setfillstyle(1,COLOR(0,color,0));
	
	x1=(x*SCALE)>>1;	
	y1=(y + ((x+y)&1))*SCALE;
	
	poly[0]=x1;
	poly[1]=y1;

	poly[2]=x1+(SCALE>>1);
	poly[3]=((x+y+1)&1) ? y1+SCALE : y1-SCALE;

	poly[4]=x1+SCALE;
	poly[5]=y1;

	fillpoly(3,poly);
}


void Setka(){
	setcolor(COLOR(30,60,30));	
	for(int j=0;j<LOW_HEIGHT;j++){
		line(0, j*SCALE, SCR_WIDTH, j*SCALE);
	}
	for (int i=-LOW_HEIGHT/2;i<LOW_WIDTH/2+LOW_HEIGHT/2;i++){
		line(i*SCALE,0,i*SCALE-SCR_HEIGHT*TAN30,SCR_HEIGHT);			
		line(i*SCALE,0,i*SCALE+SCR_HEIGHT*TAN30,SCR_HEIGHT);			
	}
}

void Draw(){
	cleardevice();
	Setka();

	setfillstyle(1, COLOR(0,220,0));
	Tri(Snake[0].x, Snake[0].y);
	setfillstyle(1, COLOR(0,150,0));
	for (int k=1; k<Num; k++){
		Tri(Snake[k].x, Snake[k].y);
	}
	//apple
	setfillstyle(1, COLOR(200,0,0));
		Tri(Apple.x, Apple.y);
	
}


void InitScene(){
	Apple.x=rand()%LOW_WIDTH;
	Apple.y=rand()%LOW_HEIGHT;
	Dir=DIR_RT;
}


void UpdateScene(){
	if(Move){
		for(int i=Num;i>0;--i){
			Snake[i].x=Snake[i-1].x;
			Snake[i].y=Snake[i-1].y;
		}
		switch(Dir){
//			case DIR_UP: if ((Snake[0].x+Snake[0].y) & 1) Snake[0].y--; else  if(Snake[0].y<=0) {Move=0; Play=0; } break; 
			case DIR_LT: Snake[0].x--; if(Snake[0].x<=0) {Move=0; Play=0; } break;
			case DIR_RT: Snake[0].x++; if(Snake[0].x>=LOW_WIDTH) {Move=0; Play=0; } break;
			case DIR_UPLT: if ((Snake[0].x+Snake[0].y) & 1) Snake[0].x--; else Snake[0].y--; if(Snake[0].x<=0 || Snake[0].y<=0) {Move=0; Play=0; } break;
			case DIR_UPRT: if ((Snake[0].x+Snake[0].y) & 1) Snake[0].x++; else Snake[0].y--; if(Snake[0].x>=LOW_WIDTH || Snake[0].y<=0) {Move=0; Play=0; } break;
//			case DIR_DN: Snake[0].y++; if(Snake[0].y>=LOW_HEIGHT) {Move=0; Play=0; } break;
			case DIR_DNLT: if ((Snake[0].x+Snake[0].y) & 1) Snake[0].y++; else Snake[0].x--; if(Snake[0].x<=0 || Snake[0].y>=LOW_HEIGHT) {Move=0; Play=0; } break;
			case DIR_DNRT: if ((Snake[0].x+Snake[0].y) & 1) Snake[0].y++; else Snake[0].x++; if(Snake[0].x>=LOW_WIDTH || Snake[0].y>=LOW_HEIGHT) {Move=0; Play=0; } break;
		}
		
	}
	else{
//		GameOver();
		//Play=0;
	}

	if (Snake[0].x==Apple.x && Snake[0].y==Apple.y) {  // eat apple
		Apple.x=rand()%LOW_WIDTH; 
		Apple.y=rand()%LOW_HEIGHT; 
		Num++;
	}	
		
}


void Keys(){
	switch(getch()){
		case 27: Play=0; break;
		case 72: Dir=DIR_UP; break; // up
		case 75: Dir=DIR_LT; break; // left
		case 80: Dir=DIR_DN; break; // down
		case 77: Dir=DIR_RT; break; // right
		case 71: Dir=DIR_UPLT; break;	// home = up-left
		case 79: Dir=DIR_DNLT; break;	// end = down-left
		case 73: Dir=DIR_UPRT; break; 	// pgup = up-right
		case 81: Dir=DIR_DNRT; break; 	// pgdn = down-right
//		case 32: Move=1-Move; break;	
		default: break;
	};

}

void GameOver(){
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(8, HORIZ_DIR, 25);
	setcolor(COLOR(200,0,0));
	outtextxy(CENTERX, CENTERY, "GAME OVER");		
	while(getch()!=27){};
}

int main(){
	int Page=0;
	
	initwindow(SCR_WIDTH,SCR_HEIGHT);
	InitScene();

	while(Play){
		if (kbhit()) Keys();
		setactivepage(Page);
		UpdateScene();
		Draw();
		setvisualpage(Page);
		Page=1-Page;
		Sleep(DELAY);
	}

	GameOver();
	return 0;
}
