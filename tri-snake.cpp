#include <winbgim.h>
#include <windows.h>

#define SCR_WIDTH 1200
#define SCR_HEIGHT 700
#define SCALE 12
#define LOW_WIDTH (SCR_WIDTH/SCALE*2)
#define LOW_HEIGHT SCR_HEIGHT/SCALE
#define TAN30 0.5 
#define DELAY 70

void Tri(int x, int y, int col);
void Setka();
void Draw();
void InitScene();
void UpdateScene();
void Keys();
void GameOver();


int Play=1, Num=3, Dir=0;

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
		line(i*SCALE-SCALE/2,0,i*SCALE-SCR_HEIGHT*TAN30-SCALE/2,SCR_HEIGHT);			
		line(i*SCALE-SCALE/2,0,i*SCALE+SCR_HEIGHT*TAN30-SCALE/2,SCR_HEIGHT);			
	}
}

void Draw(){
	cleardevice();
	Setka();

	setfillstyle(1, COLOR(0,220,0));
	Tri(s[0].x*SCALE, s[0].y*SCALE, (s[0].x+1)*SCALE, (s[0].y+1)*SCALE);
	setfillstyle(1, COLOR(0,150,0));
	for (int k=1; k<Num; k++){
		bar(s[k].x*SCALE, s[k].y*SCALE, (s[k].x+1)*SCALE, (s[k].y+1)*SCALE);
	}
	//apple
	setfillstyle(1, COLOR(200,0,0));
		bar(apple.x*SCALE, apple.y*SCALE, (apple.x+1)*SCALE, (apple.y+1)*SCALE);
	
}


void InitScene(){
	Apple.x=rand()%LOW_WIDTH;
	Apple.y=rand()%LOW_HEIGHT;
}


void UpdateScene(){

}


void Keys(){
	switch(getch()){
		case 27: Play=0; break;
		case 72: Dir=0; break; // 
		case 75: Dir=1; break; // left
		case 80: Dir=2; break; //
		case 77: Dir=3; break; // right
		case 32: Move=1-Move; break;	
		default: break;
	};

}

void GameOver(){

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


	return 0;
}
