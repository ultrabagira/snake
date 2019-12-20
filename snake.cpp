#include <winbgim.h>
#include <windows.h>
#include <stdio.h>

#define SCALE 15
#define LOW_WIDTH 85
#define LOW_HEIGHT 40
#define SCR_WIDTH LOW_WIDTH*SCALE
#define SCR_HEIGHT LOW_HEIGHT*SCALE
#define CENTERX SCR_WIDTH/2
#define CENTERY SCR_HEIGHT/2
#define DELAY 70

void Setka();
void InitScene();
void Keys();
void Draw();
void GameOver();

struct point{
	int x, y;
} s[100], apple;

int Dir=2, Num=4, Play=1, Move=1;

void Setka(){
	setcolor(COLOR(30,60,30));
	for (int i=0; i<LOW_WIDTH; i++)
		line(i*SCALE, 0, i*SCALE, SCR_HEIGHT);
	for (int j=0; j<LOW_HEIGHT; j++)
		line(0, j*SCALE, SCR_WIDTH, j*SCALE);
}

void InitScene(){
	apple.x=rand()%LOW_WIDTH;
	apple.y=rand()%LOW_HEIGHT;

	//for(int k=0;k<Num;k++) s[k].x=s[k].y=LOW_HEIGHT>>1;

	// status
	settextjustify(RIGHT_TEXT, TOP_TEXT);
	settextstyle(3, HORIZ_DIR, 2);

}

void Keys(){
	switch(getch()){
		case 27: Play=0; break;
		case 72: Dir=0; break;
		case 75: Dir=1; break;
		case 77: Dir=3; break;
		case 80: Dir=2; break;
		case 32: Move=1-Move; break;	
		default: break;
	};
}


void Draw(){
	char msg[10];
	cleardevice();
	Setka();
	
		// snake
	setfillstyle(1, COLOR(0,220,0));
	bar(s[0].x*SCALE, s[0].y*SCALE, (s[0].x+1)*SCALE, (s[0].y+1)*SCALE);
	setfillstyle(1, COLOR(0,150,0));
	for (int k=1; k<Num; k++){
		bar(s[k].x*SCALE, s[k].y*SCALE, (s[k].x+1)*SCALE, (s[k].y+1)*SCALE);
	}
	//apple
	setfillstyle(1, COLOR(200,0,0));
		bar(apple.x*SCALE, apple.y*SCALE, (apple.x+1)*SCALE, (apple.y+1)*SCALE);
		
	// status
	setcolor(COLOR(250,250,250));
	sprintf(msg, "%3d", (int)(Num-4));
	outtextxy(SCR_WIDTH-15, 0, msg);
}

void UpdateScene(){
	if(Move){
		for(int i=Num;i>0;--i){
			s[i].x=s[i-1].x;
			s[i].y=s[i-1].y;
		}
		switch(Dir){
			case 0: s[0].y--; if(s[0].y<=0) {Move=0; Play=0; } break; 
			case 1: s[0].x--; if(s[0].x<=0) {Move=0; Play=0; } break;
			case 2: s[0].y++; if(s[0].y>=LOW_HEIGHT) {Move=0; Play=0; } break;
			case 3: s[0].x++; if(s[0].x>=LOW_WIDTH) {Move=0; Play=0; } break;
		}
		
	}
	else{
		GameOver();
		//Play=0;
	}

	if (s[0].x==apple.x && s[0].y==apple.y) {  // eat apple
		apple.x=rand()%LOW_WIDTH; 
		apple.y=rand()%LOW_HEIGHT; 
		Num++;
	}	
	
}

void GameOver(){
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(8, HORIZ_DIR, 25);
	setcolor(COLOR(200,0,0));
	outtextxy(CENTERX, CENTERY, "GAME OVER");		
	while(getch()!=27){};
}


int main(){
	int i, j, Page=0;
	
	initwindow(SCR_WIDTH, SCR_HEIGHT);
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

