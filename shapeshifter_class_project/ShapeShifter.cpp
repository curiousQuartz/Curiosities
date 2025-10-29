//include user defined Classes
#include "ShapeShifter.h"
#include "SpecialTiles.h"
#include "GamePlay.h"
#include "Door.h"

//get external vectors from main file
extern vector< Door* > gDoors;
extern vector< Barrier* > gBarriers;
extern vector< SpecialTile* > gTiles;

//
// sets up the player with its initial values
//
void ShapeShifter::playerSetUp(float x, float y, int s, int c)
{
	posX = x;
	posY = y;
	prevPosX = x;
	prevPosY = y;
	
	shape = s;
	color = c;
	movingV = 0.0;
	movingH = 0.0;
	speed = 15.0;
}

//
// draws the player
//
void ShapeShifter::draw()
{
	// chooses which color it should be based on its corrisponding number
	switch (color)
	{
		case 1:
			glColor3f(1.0, 0.3, 0.4);
			break;
		case 2:
			glColor3f(0.4, 0.85, 0.6);
			break;
		case 3:
			glColor3f(0.45, 0.55, 1.0);
			break;
	}
	// chooses which shape it should be based on its corrisponding number
	switch (shape)
	{
		case 1:
			//triangle
			glPushMatrix();
				glBegin( GL_POLYGON );
					glVertex3f( posX, posY + 0.25, 0.1 );	
					glVertex3f( posX - 0.25, posY - 0.25, 0.1 );	
					glVertex3f( posX + 0.25, posY - 0.25, 0.1 );
				glEnd();
			glPopMatrix();
			break;
		case 2:
			//square
			glPushMatrix();
				glBegin( GL_POLYGON );
					glVertex3f( posX - 0.25, posY + 0.25, 0.1 );
					glVertex3f( posX - 0.25, posY - 0.25, 0.1 );	
					glVertex3f( posX + 0.25, posY - 0.25, 0.1 );	
					glVertex3f( posX + 0.25, posY + 0.25, 0.1 );
				glEnd();
			glPopMatrix();
			break;
		case 3:
			glPushMatrix();
				glTranslatef( posX, posY, 0.1 );
				glutSolidSphere( 0.25, 20, 20 );
			glPopMatrix();
			break;
	}
}

// computePosition
//
// Compute tank position
//
// Currently this is set up to move forward in x, you may implement the version
// as shown in class with full rotation or a simpler version of up, down, left, right

void ShapeShifter::computePosition( double elapsed_time )
{
	float velocityX;
	float velocityY;

	if ( elapsed_time > MINIMUM_MILLISECOND_UPDATE )
	{
		velocityX = movingH * speed * elapsed_time;
		velocityY = movingV * speed * elapsed_time;
		
		prevPosX = posX;
		prevPosY = posY;

		posX += velocityX;
		posY += velocityY;
	}
}

// key down
//
// controls using the arrow keys to move the player around the screen
//
void ShapeShifter::keyDown( char key )
{
	switch(key)
	{
		case GLUT_KEY_UP:
			movingV = 1.0;
			break;
		case GLUT_KEY_DOWN:
			movingV = -1.0;
			break;
		case GLUT_KEY_LEFT:
			movingH = -1.0;
			break;
		case GLUT_KEY_RIGHT:
			movingH = 1.0;
			break;
	}
}

// key up
//
// stops the player from moving when the key is no longer being pressed
//
void ShapeShifter::keyUp( char key )
{
	switch(key)
	{
		case GLUT_KEY_UP:
			movingV = 0.0;
			break;
		case GLUT_KEY_DOWN:
			movingV = 0.0;
			break;
		case GLUT_KEY_LEFT:
			movingH = 0.0;
			break;
		case GLUT_KEY_RIGHT:
			movingH = 0.0;
			break;
	}
}
