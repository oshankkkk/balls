#include "raylib.h"
#include <iso646.h>
#include <math.h>

#define WIDTH 1200
#define HEIGHT 800 
#define AGENTCOUNT 4000
#define MINRAD 7
#define MAXRAD 9
#define MINSPEED -4
#define MAXSPEED 9

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
void ballcolors(Agent *agents,int *subtick,int x,int i){
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

		}
	}

}

void ballbounce(Agent *agents,int *subtick){

	for (int x=0;x<AGENTCOUNT;x++){

		for (int i=x+1;i<AGENTCOUNT;i++){

			if (CheckCollisionCircles(agents[x].position,agents[x].radius,agents[i].position,agents[i].radius)){

				
				Vector2 p1=agents[x].position;
				Vector2 p2=agents[i].position;

				double a=p1.x-p2.x;
				double b=p1.y-p2.y;

				//[a,b] is the vector from A to B the particle 
				double d=sqrt(pow(a,2)+pow(b, 2));
				//We take the 2 coordinates of the particle centers, then we get the vector of one particle to another, 
				//we find its distance and divide the vector by its distance to get the unit vector.
				//(this is vector division)
				double nx=a/d;
				double ny=b/d;

				//find the overlapping area n /2 to get each of it
				double ovp=agents[x].radius+agents[i].radius-d;

				agents[x].position.x+=nx*ovp/2;
				agents[i].position.x+=-nx*ovp/2; 
				agents[x].position.y+=ny*ovp/2;
				agents[i].position.y+=-ny*ovp/2;

				double rvx=agents[x].velocity.x-agents[i].velocity.x;
				double rvy=agents[x].velocity.y-agents[i].velocity.y;	

				// the relative velocity in the unit direction vector(collison path), we should reverse this. 
				double collinevelocity=rvx*nx+rvy*ny;

				agents[x].velocity.x+=-collinevelocity*nx;
				agents[x].velocity.y+=-collinevelocity*ny;
				agents[i].velocity.x-=-collinevelocity*nx;
				agents[i].velocity.y-=-collinevelocity*ny;

				ballcolors(agents,subtick,x,i);

				agents[x].collcount++;
				agents[i].collcount++;
			}

		}
	}
}

void setupballstats(Agent *agents){
	for (int i = 0; i < AGENTCOUNT; i++){

		agents[i].radius=GetRandomValue(MINRAD,MAXRAD);
		agents[i].position.x=GetRandomValue(0, WIDTH-agents[i].radius);
		agents[i].position.y=GetRandomValue(0, HEIGHT-agents[i].radius);

		agents[i].velocity.x=GetRandomValue(-4,6);
		agents[i].velocity.y=GetRandomValue(-4, 6);

		agents[i].color=RED;
	}
}

void simstats(void){

	DrawText(TextFormat("FPS: %d", GetFPS()),
			0, 0, 20, WHITE);

	DrawText(TextFormat("Frame: %.2f ms", GetFrameTime() * 1000.0f),
			0, 15, 20, WHITE);
}

int main(void){
	SetRandomSeed(1);
	InitWindow(WIDTH, HEIGHT, "shmol shmol bally balls");

	SetTargetFPS(60);

	Agent agents[AGENTCOUNT]; 

	setupballstats(agents);

	int subtick=0;
	while (!WindowShouldClose()){	

		updateballs(agents);

		BeginDrawing();
		ClearBackground(BLACK);
		simstats();
		drawballs(agents);
		ballbounce(agents,&subtick);
		wallbounce(agents);

		EndDrawing();
	}

	CloseWindow();        

	return 0;
}

//The balls (intial color red) collide and when they collide and the collistion count is 10 factor they color change to green and pink, else if its not a factor of 10 it changes to blue and yellow for 
//30 ticks and when the time exceeds it turns to red until its collied again. 
