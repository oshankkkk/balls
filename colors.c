#include "raylib.h"

typedef struct{
	Vector2 position;
	Vector2 velocity;
	Vector2 force;
	Vector2 acc;
	int colorcode; 
	Vector2 prevvelstate;
	float radius;
	float mass;

}Agent;

Color colors[20] = {
	{   0,  60, 255, 255 },  // 1. Bright Blue
	{  30, 150, 255, 255 },  // 2. Blue
	{ 100, 210, 255, 255 },  // 3. Light Blue
	{ 200, 245, 255, 255 },  // 4. Very Light Blue
	{ 255, 255, 255, 255 },  // 5. White
	{ 255, 240,  50, 255 },  // 6. Yellow
	{ 255, 190,   0, 255 },  // 7. Yellow-Orange
	{ 255, 120,   0, 255 },  // 8. Orange
	{ 255,  60,   0, 255 },  // 9. Red-Orange
	{ 255,   0,   0, 255 },  // 10. Bright Red
	
	{   0, 255,  80, 255 },  // 1. Bright Green
	{  50, 230, 100, 255 },  // 2. Green
	{ 120, 240, 150, 255 },  // 3. Light Green
	{ 200, 255, 210, 255 },  // 4. Very Light Green
	{ 255, 255, 255, 255 },  // 5. White
	{ 255, 200, 230, 255 },  // 6. Light Pink
	{ 255, 120, 190, 255 },  // 7. Pink
	{ 230,  60, 170, 255 },  // 8. Hot Pink
	{ 180,  30, 180, 255 },  // 9. Purple-Pink
	{ 120,   0, 180, 255 }   // 10. Purple
						 //
};
void ballcolors(Agent *agents, int x){
	float vx = agents[x].velocity.x;
	float vy = agents[x].velocity.y;
	float pvx = agents[x].prevvelstate.x;
	float pvy = agents[x].prevvelstate.y;

	float dx = vx - pvx;
	float dy = vy - pvy;

	if (dx > dy) {
		if (vx > pvx) {
			if (agents[x].colorcode< 9) {
				agents[x].colorcode+= 1;
			}
		}else if (vx < pvx) {
			if (agents[x].colorcode> 0) {
				agents[x].colorcode-= 1;
			}
		}
	}else {
		if (vy > pvy) {
			if (agents[x].colorcode< 19) {
				agents[x].colorcode+= 1;
			}
		}else if (vy < pvy) {
			if (agents[x].colorcode> 10) {
				agents[x].colorcode -= 1;
			}
		}

	}

	agents[x].prevvelstate.x = vx;
	agents[x].prevvelstate.y = vy;
}

