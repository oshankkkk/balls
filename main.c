// DOD for better FPS?
// SIMD for better FPS?
// wdym, move according to my velocity for the amount of time that actually passed

#include "raylib.h"
#include <iso646.h>
#include <math.h>
#include "colors.c"
#define WIDTH 1200
#define HEIGHT 800 
#define AGENTCOUNT 4000
#define MINRAD 2
#define MAXRAD 5
#define MINSPEED -1000
#define MAXSPEED 1000

void drawballs(Agent *agents){

	for (int x=0;x<AGENTCOUNT;x++){

		DrawCircleV(agents[x].position,agents[x].radius, colors[agents[x].colorcode]);
	}	
}

void updateballs(Agent *agents, float dt){
	
	for (int x=0;x<AGENTCOUNT;x++){
		
		agents[x].acc.x = agents[x].force.x * agents[x].mass;
		agents[x].acc.y = agents[x].force.y * agents[x].mass;
		ballcolors(agents, x);

		agents[x].velocity.x += agents[x].acc.x * dt;
		agents[x].velocity.y += agents[x].acc.y * dt;

		agents[x].position.x += agents[x].velocity.x * dt;
		agents[x].position.y += agents[x].velocity.y * dt;	

	}	
}

void wallbounce(Agent *agents){

	for (int x=0;x<AGENTCOUNT;x++){

		if (agents[x].position.x - agents[x].radius < 0){
			agents[x].position.x = agents[x].radius;
			agents[x].velocity.x *= -1;
		} else if (agents[x].position.x + agents[x].radius > WIDTH){
			agents[x].position.x = WIDTH - agents[x].radius;
			agents[x].velocity.x *= -1;
		}

		if (agents[x].position.y - agents[x].radius < 0){
			agents[x].position.y = agents[x].radius;
			agents[x].velocity.y *= -1;
		} else if (agents[x].position.y + agents[x].radius > HEIGHT){
			agents[x].position.y = HEIGHT - agents[x].radius;
			agents[x].velocity.y *= -1;
		}	
	}
	
}


void ballbounce(Agent *agents){
	for (int x=0;x<AGENTCOUNT;x++){

		for (int i=x+1;i<AGENTCOUNT;i++){

			if (CheckCollisionCircles(agents[x].position,agents[x].radius,agents[i].position,agents[i].radius)){

				Vector2 p1=agents[x].position;
				Vector2 p2=agents[i].position;

				float m1=agents[x].mass;	
				float m2=agents[i].mass;	

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

				//substituting formula:
				// mass-weighted exchange coefficients
				double invMassSum = 1.0 / (m1 + m2);
				double coef1 = (2.0 * m2) * invMassSum;   // for particle 1 (agents[x])
				double coef2 = (2.0 * m1) * invMassSum;   // for particle 2 (agents[i])

				// only resolve if they're actually approaching each other along the normal
				// (collinevelocity > 0 means moving toward each other, given rv = v1-v2 and n points 1->... check your sign convention)
				if (collinevelocity < 0) {
					agents[x].velocity.x -= coef1 * collinevelocity * nx;
					agents[x].velocity.y -= coef1 * collinevelocity * ny;

					agents[i].velocity.x += coef2 * collinevelocity * nx;
					agents[i].velocity.y += coef2 * collinevelocity * ny;
				}				

				//using impluse:
				//double j = -1.0 *collinevelocity/ (1.0 / m1 + 1.0 / m2);

				//double jx = j * nx;
				//double jy = j * ny;

				//agents[x].velocity.x+=jx/m1;
				//agents[x].velocity.y+=jy/m1;
				//agents[i].velocity.x-=jx/m2;
				//agents[i].velocity.y-=jy/m2;

				//only changing velocity:
				//agents[x].velocity.x+=-collinevelocity*nx;
				//agents[x].velocity.y+=-collinevelocity*ny;
				//agents[i].velocity.x-=-collinevelocity*nx;
				//agents[i].velocity.y-=-collinevelocity*ny;

			}

		}
	}
}

void setupballstats(Agent *agents){
	for (int i = 0; i < AGENTCOUNT; i++){

		agents[i].radius=GetRandomValue(MINRAD,MAXRAD);
		agents[i].position.x=GetRandomValue(0, WIDTH-agents[i].radius);
		agents[i].position.y=GetRandomValue(0, HEIGHT-agents[i].radius);

		agents[i].velocity.x=GetRandomValue(MINSPEED,MAXSPEED);
		agents[i].velocity.y=GetRandomValue(MINSPEED,MAXSPEED);
		agents[i].force.x=0;
		agents[i].force.y=0;
		agents[i].mass=agents[i].radius;

		agents[i].colorcode=0;
	}
}
void simstats(void){
	DrawText(TextFormat("FPS: %d", GetFPS()),
			0, 0, 20, WHITE);
}

int main(void){
	SetRandomSeed(1);
	InitWindow(WIDTH, HEIGHT, "shmol shmol bally balls");

	SetTargetFPS(60);

	Agent agents[AGENTCOUNT]; 

	setupballstats(agents);
	//Color bgcolor={107, 102, 89,0};

	while (!WindowShouldClose()){	
		float dt=GetFrameTime();
		updateballs(agents,dt);

		BeginDrawing();
		ClearBackground(BLACK);
		simstats();
		drawballs(agents);
		ballbounce(agents);
		wallbounce(agents);

		EndDrawing();
	}

	CloseWindow();        

	return 0;
}
