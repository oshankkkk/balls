#include "raylib.h"
#include <iso646.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 1200
#define HEIGHT 800 
#define AGENTCOUNT 500

#define CELLSIZE 5
#define COLS (WIDTH / CELLSIZE)
#define ROWS (HEIGHT / CELLSIZE)
#define CAMSPEED 3
#define ZOOMRATE 0.5f

typedef struct{
	Vector2 position;
	Vector2 velocity;
	Color color; 
	int collcount;
}Agent;

int main(void){
	srand(time(0));
	InitWindow(WIDTH, HEIGHT, "slimsim");

	SetTargetFPS(60);

	Agent agents[AGENTCOUNT]; 
	for (int i = 0; i < AGENTCOUNT; i++){

		agents[i].position.x=rand()%WIDTH;
		agents[i].position.y=rand()%HEIGHT;

		agents[i].velocity.x=-1+rand()%20;
		agents[i].velocity.y=-1+rand()%20;
		agents[i].color=RED;
	}
	int tick,subtick=0;
	while (!WindowShouldClose()){	

		for (int x=0;x<AGENTCOUNT;x++){

			agents[x].position.x += agents[x].velocity.x;
			agents[x].position.y += agents[x].velocity.y;

		}	

		BeginDrawing();

		ClearBackground(BLACK);

		for (int x=0;x<AGENTCOUNT;x++){

			DrawCircleV(agents[x].position, CELLSIZE, agents[x].color);

		}	

		for (int x=0;x<AGENTCOUNT;x++){

			for (int i=x+1;i<AGENTCOUNT;i++){

				if (CheckCollisionCircles(agents[x].position,CELLSIZE,agents[i].position,CELLSIZE)){
					subtick++;	
					if (agents[x].collcount%10==0|| agents[i].collcount%10==0){
						agents[x].color=GREEN;
						agents[x].collcount++;
						agents[i].color=PINK;	
						agents[i].collcount++;

					}else{

						if(subtick<=30){

							agents[x].color=BLUE;
							agents[i].color=YELLOW;	

						}else{
							subtick=0;
							agents[x].color=RED;
							agents[i].color=RED;	

						}}

					agents[x].collcount++;
					agents[i].collcount++;
				}
			}
		}

			for (int x=0;x<AGENTCOUNT;x++){

				if (agents[x].position.x < 0 ||	agents[x].position.x > WIDTH){
					agents[x].velocity.x *= -1;
				}

				if (agents[x].position.y < 0 ||agents[x].position.y >HEIGHT){
					agents[x].velocity.y *= -1;
				}

			}
			tick++;
			EndDrawing();
		}

		CloseWindow();        

		return 0;
	}
//the balls (intial color red) collide and when they collide and the collistion count is 10 factor they color change to green and pink, else if its not a factor of 10 it changes to blue and yellow for 
//30 ticks and when the time exceeds it turns to red until its collied again. 
//
