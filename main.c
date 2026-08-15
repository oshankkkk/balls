#include "raylib.h"
#include <iso646.h>

#define WIDTH 1200
#define HEIGHT 800 
#define AGENTCOUNT 35
//#define AGENTCOUNT 1

//#define agent[x].radius 2
//#define agent[x].radius 50

#define COLS (WIDTH / agent[x].radius)
#define ROWS (HEIGHT / agent[x].radius)
//#define CAMSPEED 3
#define ZOOMRATE 0.5f

typedef struct{
	Vector2 position;
	Vector2 velocity;
	Color color; 
	int collcount;
	float radius;
}Agent;

void drawballs(Agent *agents){

	for (int x=0;x<AGENTCOUNT;x++){

		DrawCircleV(agents[x].position,agents[x].radius, agents[x].color);

	}	
}
void updateballs(Agent *agents){

	for (int x=0;x<AGENTCOUNT;x++){

		agents[x].position.x += agents[x].velocity.x;
		agents[x].position.y += agents[x].velocity.y;

	}	
}
void wallbounce(Agent *agents){

	for (int x=0;x<AGENTCOUNT;x++){

		if (agents[x].position.x-agents[x].radius < 0){
			agents[x].position.x=agents[x].radius;
			agents[x].velocity.x *= -1;
		}else if (agents[x].position.x+agents[x].radius> WIDTH){
			agents[x].position.x=WIDTH-agents[x].radius;
			agents[x].velocity.x *= -1;
		}else if (agents[x].position.y-agents[x].radius < 0){
			agents[x].position.y=agents[x].radius;
			agents[x].velocity.y *= -1;
		}else if (agents[x].position.y+agents[x].radius >HEIGHT){
			agents[x].position.y=HEIGHT-agents[x].radius;
			agents[x].velocity.y *= -1;
		}

	}
}
void ballbounce(Agent *agents,int *subtick){

	for (int x=0;x<AGENTCOUNT;x++){

		for (int i=x+1;i<AGENTCOUNT;i++){

			if (CheckCollisionCircles(agents[x].position,agents[x].radius,agents[i].position,agents[i].radius)){

				agents[x].velocity.x *= -1;
				agents[x].velocity.y *= -1;
				agents[i].velocity.x *= -1;
				agents[i].velocity.y *= -1;

				*subtick=*subtick+1;
				if (agents[x].collcount%10==0|| agents[i].collcount%10==0){
					agents[x].color=GREEN;
					agents[x].collcount++;
					agents[i].color=PINK;	
					agents[i].collcount++;

				}else{

					if(*subtick<=30){

						agents[x].color=BLUE;
						agents[i].color=YELLOW;	

					}else{

						*subtick=0;
						agents[x].color=RED;
						agents[i].color=RED;	

					}}

				agents[x].collcount++;
				agents[i].collcount++;
			}
		}
	}
}
void setupballstats(Agent *agents){
for (int i = 0; i < AGENTCOUNT; i++){

		agents[i].radius=GetRandomValue(2,9);
		agents[i].position.x=GetRandomValue(0, WIDTH-agents[i].radius);
		agents[i].position.y=GetRandomValue(0, HEIGHT-agents[i].radius);

		agents[i].velocity.x=GetRandomValue(-5,5);
		agents[i].velocity.y=GetRandomValue(-5, 5);
		agents[i].color=RED;
	}
}
int main(void){
	SetRandomSeed(1);
	InitWindow(WIDTH, HEIGHT, "shmol shmol bally balls");

	SetTargetFPS(60);

	Agent agents[AGENTCOUNT]; 
	
	setupballstats(agents);
	int tick,subtick=0;
	while (!WindowShouldClose()){	

		updateballs(agents);

		BeginDrawing();
		DrawFPS(0,0);
		ClearBackground(BLACK);

		drawballs(agents);
		ballbounce(agents,&subtick);
		wallbounce(agents);

		tick++;
		EndDrawing();
	}

	CloseWindow();        

	return 0;
}

//The balls (intial color red) collide and when they collide and the collistion count is 10 factor they color change to green and pink, else if its not a factor of 10 it changes to blue and yellow for 
//30 ticks and when the time exceeds it turns to red until its collied again. 
