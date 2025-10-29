#include "ShapeShifter.h"
#include <iostream>
using namespace std;

#pragma once

//
// SpecialTile is any tile on the grid which has a different appearance then the the others, not including the player, walls, or doors
// This is the parent class, each tile has its own version of the functions and its own variable stating its appearance. 
//
class SpecialTile
{
public:
	//variables
	float x;
	float y;
	
	//function
	SpecialTile();
	virtual void draw();
	virtual void checkIntersection();
};

//
// Color changer tiles are also shaped like a star but in one of the colors that the player can shift into 
// the player shifts to this color when they touch
//
class ColorChanger : public SpecialTile
{
public:
	//variables
	int color;
	
	//functions
	ColorChanger(int c, float px, float py);
	void draw();
	void checkIntersection();
};

//
// Shape changer tiles have a neutrally colored shape which will change the players shape to match it when they touch
//
class ShapeChanger : public SpecialTile
{
public:
	//variables
	int shape;
	
	//functions
	ShapeChanger(int s, float px, float py);
	void draw();
	void checkIntersection();
};

//
// Star class is used only once for each level and it draws a gold star that when reached, the level ends
//
class Star : public SpecialTile
{
public:
	//variables
	
	//functions
	Star(float px, float py);
	void draw();
	void checkIntersection();
};
