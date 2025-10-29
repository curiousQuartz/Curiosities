#include "SpecialTiles.h"
#include "ShapeShifter.h"
#include "GamePlay.h"

//get external variables from main file
extern ShapeShifter player;
extern GamePlay MyGame;

///////////////////////////
// SpecialTile funtions //
///////////////////////////

//using polymorphism so these functions are never used
//they just have to exist or I get an error
SpecialTile::SpecialTile(){}
void SpecialTile::draw(){}
void SpecialTile::checkIntersection(){}

////////////////////////////
// ColorChanger functions //
////////////////////////////

ColorChanger::ColorChanger(int c, float px, float py)
{
	color = c;
	x = px;
	y = py;
}
void ColorChanger::draw()
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
	glPushMatrix();
		glBegin( GL_POLYGON );
			glVertex3f( x + 0.1, y + 0.1, 0.0 );	
			glVertex3f( x + 0.4, y, 0.0 );
			glVertex3f( x + 0.1, y - 0.1, 0.0 );	
			glVertex3f( x, y - 0.4, 0.0 );
			glVertex3f( x - 0.1, y - 0.1, 0.0 );	
			glVertex3f( x - 0.4, y, 0.0 );
			glVertex3f( x - 0.1, y + 0.1, 0.0 );
			glVertex3f( x, y + 0.4, 0.0 );	
		glEnd();
	glPopMatrix();
}
void ColorChanger::checkIntersection()
{
	//checks if the player overlaps the square and change its color when it does
	bool left = player.posX + 0.25 > x - 0.5;
	bool right = player.posX - 0.25  < x + 0.5;
	bool top = player.posY - 0.25  < y + 0.5;
	bool bottom = player.posY + 0.25  > y - 0.5;
	if (left && right && top && bottom)
	{
		player.color = color;
	}
}

////////////////////////////
// ShapeChanger functions //
////////////////////////////

ShapeChanger::ShapeChanger(int s, float px, float py)
{
	shape = s;
	x = px;
	y = py;
}
void ShapeChanger::draw()
{
	glColor3f(0.6, 0.55, 0.6);
	// chooses which shape it should be based on its corrisponding number
	switch (shape)
	{
		case 1:
			//triangle
			glPushMatrix();
				glBegin( GL_POLYGON );
					glVertex3f( x, y + 0.25, 0.0 );	
					glVertex3f( x - 0.25, y - 0.25, 0.0 );	
					glVertex3f( x + 0.25, y - 0.25, 0.0 );
				glEnd();
			glPopMatrix();
			break;
		case 2:
			//square
			glPushMatrix();
				glBegin( GL_POLYGON );
					glVertex3f( x - 0.25, y + 0.25, 0.0 );
					glVertex3f( x - 0.25, y - 0.25, 0.0 );	
					glVertex3f( x + 0.25, y - 0.25, 0.0 );	
					glVertex3f( x + 0.25, y + 0.25, 0.0 );
				glEnd();
			glPopMatrix();
			break;
		case 3:
			//circle
			glPushMatrix();
				glTranslatef( x, y, 0.0 );
				glutSolidSphere( 0.25, 20, 20 );
			glPopMatrix();
			break;
	}
}
void ShapeChanger::checkIntersection()
{
	//checks if the player overlaps the square and change its shape when it does
	bool left = player.posX + 0.25 > x - 0.5;
	bool right = player.posX - 0.25  < x + 0.5;
	bool top = player.posY - 0.25  < y + 0.5;
	bool bottom = player.posY + 0.25  > y - 0.5;
	if (left && right && top && bottom)
	{
		player.shape = shape;
	}
}

////////////////////
// Star functions //
////////////////////

Star::Star(float px, float py)
{
	x = px;
	y = py;
}
void Star::draw()
{
	//draws the gold star
	glColor3f(0.8, 0.8, 0.4);
	glPushMatrix();
		glBegin( GL_POLYGON );
			glVertex3f( x + 0.1, y + 0.1, 0.0 );	
			glVertex3f( x + 0.4, y, 0.0 );
			glVertex3f( x + 0.1, y - 0.1, 0.0 );	
			glVertex3f( x, y - 0.4, 0.0 );
			glVertex3f( x - 0.1, y - 0.1, 0.0 );	
			glVertex3f( x - 0.4, y, 0.0 );
			glVertex3f( x - 0.1, y + 0.1, 0.0 );
			glVertex3f( x, y + 0.4, 0.0 );	
		glEnd();
	glPopMatrix();
}

void Star::checkIntersection()
{
	//ends the level when the player overlaps its square
	bool left = player.posX + 0.25 > x - 0.5;
	bool right = player.posX - 0.25  < x + 0.5;
	bool top = player.posY - 0.25  < y + 0.5;
	bool bottom = player.posY + 0.25  > y - 0.5;
	if (left && right && top && bottom)
	{
		MyGame.next();
	}
}

