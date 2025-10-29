#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/freeglut.h>   // or <GL/glut.h> depending on your setup
#endif

#pragma once

const float MINIMUM_MILLISECOND_UPDATE = (float) .0001;

//
// The player is controled with the arrow keys and changes shape and color when it touches special tiles
//
class ShapeShifter
{
public:
	//variables
	int shape;
	int color;
	float movingV;
	float movingH;
	float posX;
	float posY;
	float prevPosX;
	float prevPosY;
	float speed;
	
	//functions
	void playerSetUp(float x, float y, int s, int c);
	void draw();
	void computePosition( double elapsed_time );
	void keyDown( char key );
	void keyUp( char key );
};
