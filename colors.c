#include "raylib.h"

typedef struct{
	Vector2 position;
	Vector2 velocity;
	Vector2 force;
	Vector2 acc;
	int colorcode; 
	int accsatate;
	float radius;
	float mass;
}Agent;

Color hotCold[10] = {
    {   0,  60, 255, 255 },  // 1. Bright Blue
    {  30, 150, 255, 255 },  // 2. Blue
    { 100, 210, 255, 255 },  // 3. Light Blue
    { 200, 245, 255, 255 },  // 4. Very Light Blue
    { 255, 255, 255, 255 },  // 5. White
    { 255, 240,  50, 255 },  // 6. Yellow
    { 255, 190,   0, 255 },  // 7. Yellow-Orange
    { 255, 120,   0, 255 },  // 8. Orange
    { 255,  60,   0, 255 },  // 9. Red-Orange
    { 255,   0,   0, 255 }   // 10. Bright Red
};

void ballcolors(Agent *agents, int x){

    float ax = agents[x].acc.x;
    float ay = agents[x].acc.y;

    // Negative acceleration
    if (ax < 0 || ay < 0) {

        float value = (ax < 0) ? -ax : -ay;

        if (value <= 10) {
            agents[x].colorcode = 0;
        }
        else if (value <= 20) {
            agents[x].colorcode = 1;
        }
        else if (value <= 30) {
            agents[x].colorcode = 2;
        }
        else if (value <= 40) {
            agents[x].colorcode = 3;
        }
        else if (value <= 50) {
            agents[x].colorcode = 4;
        }
        else if (value <= 60) {
            agents[x].colorcode = 5;
        }
        else if (value <= 70) {
            agents[x].colorcode = 6;
        }
        else if (value <= 80) {
            agents[x].colorcode = 7;
        }
        else if (value <= 90) {
            agents[x].colorcode = 8;
        }
        else {
            agents[x].colorcode = 9;
        }

    // Positive acceleration
    } else {

        if (ax <= 10 || ay <= 10) {
            agents[x].colorcode = 0;
        }
        else if (ax <= 20 || ay <= 20) {
            agents[x].colorcode = 1;
        }
        else if (ax <= 30 || ay <= 30) {
            agents[x].colorcode = 2;
        }
        else if (ax <= 40 || ay <= 40) {
            agents[x].colorcode = 3;
        }
        else if (ax <= 50 || ay <= 50) {
            agents[x].colorcode = 4;
        }
        else if (ax <= 60 || ay <= 60) {
            agents[x].colorcode = 5;
        }
        else if (ax <= 70 || ay <= 70) {
            agents[x].colorcode = 6;
        }
        else if (ax <= 80 || ay <= 80) {
            agents[x].colorcode = 7;
        }
        else if (ax <= 90 || ay <= 90) {
            agents[x].colorcode = 8;
        }
        else {
            agents[x].colorcode = 9;
        }
    }
}
