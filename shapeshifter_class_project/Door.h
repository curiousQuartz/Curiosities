#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/freeglut.h>   // or <GL/glut.h> depending on your setup
#endif

#include <iostream>
using namespace std;

#pragma once

//
// Doors are like walls that only open when a player has a specific color and/or shape
//
class Door
{
public:
	//variables
	int color;
	int shape;
	int direction;
	float x;
	float y;
	bool open;
	
	//functions
	Door(int c, int s, int d, float px, float py);
	void draw();
	void checkIntersection();
};

//
// Barriers are walls to keep the player out of certain areas so the game is not too easy
//
class Barrier
{
public:
	//variables
	float left;
	float right;
	float top;
	float bottom;
	
	//functions
	Barrier(float x1, float x2, float y1, float y2);
	void draw();
	void checkIntersection();
};
