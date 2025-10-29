#include "Door.h"
#include "ShapeShifter.h"

//get external variables from main file
extern ShapeShifter player;

////////////////////
// Door functions //
////////////////////

Door::Door(int c, int s, int d, float px, float py)
{
	color = c;
	shape = s;
	direction = d;
	x = px;
	y = py;
	open = false;
	
}

// draw
//
// draws the door and its color and/or shape on the tile
//
void Door::draw()
{
	//draws the door either horrizontally or vertically on its tiles
	glColor3f(0.4, 0.4, 0.5);
	switch (direction)
	{
		case 1:
			glPushMatrix();
				glBegin( GL_QUADS );
					glVertex3f( x - 0.25, y + 0.5, -1.0 );	
					glVertex3f( x - 0.25, y - 0.5, -1.0 );	
					glVertex3f( x + 0.25, y - 0.5, -1.0 );	
					glVertex3f( x + 0.25, y + 0.5, -1.0 );	
				glEnd();
			glPopMatrix();
			break;
		case 2:
			glPushMatrix();
				glBegin( GL_QUADS );
					glVertex3f( x - 0.5, y + 0.25, -1.0 );	
					glVertex3f( x - 0.5, y - 0.25, -1.0 );	
					glVertex3f( x + 0.5, y - 0.25, -1.0 );	
					glVertex3f( x + 0.5, y + 0.25, -1.0 );	
				glEnd();
			glPopMatrix();
			break;
	}
	//chooses which color it should be based on its corrisponding number
	switch (color)
	{
		case 0:
			glColor3f(0.9, 0.85, 0.8);
			break;
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
	//chooses which shape it should be based on its corrisponding number
	switch (shape)
	{
		case 0:
			//color only shape
			glPushMatrix();
				glBegin( GL_POLYGON );
					glVertex3f( x + 0.05, y + 0.05, 0.0 );	
					glVertex3f( x + 0.2, y, 0.0 );
					glVertex3f( x + 0.05, y - 0.05, 0.0 );	
					glVertex3f( x, y - 0.2, 0.0 );
					glVertex3f( x - 0.05, y - 0.05, 0.0 );	
					glVertex3f( x - 0.2, y, 0.0 );
					glVertex3f( x - 0.05, y + 0.05, 0.0 );
					glVertex3f( x, y + 0.2, 0.0 );	
				glEnd();
			glPopMatrix();
			// glutSolidTorus(0.275, 0.85, 16, 40);
			break;
		case 1:
			//triangle
			glPushMatrix();
				glBegin( GL_POLYGON );
					glVertex3f( x, y + 0.2, 0.0 );	
					glVertex3f( x - 0.2, y - 0.2, 0.0 );	
					glVertex3f( x + 0.2, y - 0.2, 0.0 );
				glEnd();
			glPopMatrix();
			break;
		case 2:
			//square
			glPushMatrix();
				glBegin( GL_POLYGON );
					glVertex3f( x - 0.2, y + 0.2, 0.0 );
					glVertex3f( x - 0.2, y - 0.2, 0.0 );	
					glVertex3f( x + 0.2, y - 0.2, 0.0 );	
					glVertex3f( x + 0.2, y + 0.2, 0.0 );
				glEnd();
			glPopMatrix();
			break;
		case 3:
			glPushMatrix();
				glTranslatef( x, y, 0.0 );
				glutSolidSphere( 0.2, 20, 20 );
			glPopMatrix();
			break;
	}
}

// check intersection
//
// only lets the player go through the doors when the player matches the doors color and/or shape
//
void Door::checkIntersection()
{
	bool left = player.posX + 0.25 > x - 0.5;
	bool right = player.posX - 0.25  < x + 0.5;
	bool top = player.posY - 0.25  < y + 0.5;
	bool bottom = player.posY + 0.25  > y - 0.5;
	if ( left && right && top && bottom )
	{
		//check color
		if ( (color == 0 || color == player.color) && (shape == 0 || shape == player.shape) )
		{
			open = true;
		}
		else
		{
			open = false;
			player.posX = player.prevPosX;
			player.posY = player.prevPosY;
		}
		
	}
	else
	{
		open = false;
	}
}

///////////////////////
// Barrier functions //
///////////////////////

Barrier::Barrier(float x1, float x2, float y1, float y2)
{
	left = x1;
	right = x2;
	top = y1;
	bottom = y2;
}

// draw
//
// draws barrier based on its left, right, top and bottom
//
void Barrier::draw()
{
	glPushMatrix();
		glBegin( GL_QUADS );
			glColor3f( 0.6, 0.6, 0.7 );
			glVertex3f( left, top, 0.0 );	
			glVertex3f( left, bottom, 0.0 );	
			glVertex3f( right, bottom, 0.0 );	
			glVertex3f( right, top, 0.0 );	
		glEnd();
	glPopMatrix();
}

// check intersection
// 
// stops the players from going through the walls
//
void Barrier::checkIntersection()
{
	bool leftTemp = player.posX + 0.25 > left;
	bool rightTemp = player.posX - 0.25  < right;
	bool topTemp = player.posY - 0.25  < top;
	bool bottomTemp = player.posY + 0.25  > bottom;
	if (leftTemp && rightTemp && topTemp && bottomTemp)
	{
		player.posX = player.prevPosX;
		player.posY = player.prevPosY;
	}
}
