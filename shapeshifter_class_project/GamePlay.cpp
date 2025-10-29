//include user defined Classes
#include "ShapeShifter.h"
#include "SpecialTiles.h"
#include "GamePlay.h"
#include "Door.h"

//get external variables from main file
extern ShapeShifter player;
extern vector< Door* > gDoors;
extern vector< Barrier* > gBarriers;
extern vector< SpecialTile* > gTiles;


// FUNCTION FOR TRACKING TIME

double diffclock( clock_t clock1, clock_t clock2 )
{
        double diffticks = clock1 - clock2;
        double diffms = ( diffticks * 1000 ) / CLOCKS_PER_SEC;
        return diffms;
}


////////////////////////
// GamePlay functions //
////////////////////////

GamePlay::GamePlay()
{
	homeScreen = true;
	gamePlayed = false;
	paused = false;
	level = 0;
}

// next
//
// checks what should happen next based on level when it is called
//
void GamePlay::next()
{
	switch (level)
	{
		case 0:
			clear();
			levelOne();
			break;
		case 1: 
			clear();
			levelTwo();
			break;
		case 2:
			clear();
			levelThree();
			break;
		case 3:
			homeScreen = true;
			gamePlayed = true;
			break;
	}
}

// clear
//
// empties all of the arrays so the next level can be set up
//
void GamePlay::clear()
{
	gDoors.clear();
	gBarriers.clear();
	gTiles.clear();
}

// level one 
//
// sets up the first level
//
void GamePlay::levelOne()
{
	level = 1;
	
	//player set up (posX, posY, shape, color, leftKey, rightKey, upKey, downKey)
	player.playerSetUp(-7.5, -0.5, 3, 2);
	
	//add boarder barriers (left, right, top, bottom)
	gBarriers.push_back( new Barrier (-9.5 , 9.5, -8.0, -8.5) );
	gBarriers.push_back( new Barrier (-9.5 , 9.5, 8.5, 8.0) );
	gBarriers.push_back( new Barrier (-9.5 , -9.0, 8.5, -8.5) );
	gBarriers.push_back( new Barrier (9.0 , 9.5, 8.5, -8.5) );
	//add level boarder
	gBarriers.push_back( new Barrier (-9.0, -6.0, 7.0, 6.0) );
	gBarriers.push_back( new Barrier (-7.0, -6.0, 8.0, 7.0) );
	
	//play area (left -9.0) (right 9.0) (top 8.0) (bottom -8.0)
	
	//add barriers (left, right, top, bottom)
	gBarriers.push_back( new Barrier (-9.0, -5.0, -2.0, -3.0) );
	gBarriers.push_back( new Barrier (-9.0, -5.0, 2.0, 1.0) );
	gBarriers.push_back( new Barrier (-6.0, -5.0, 1.0, 0.0) );
	gBarriers.push_back( new Barrier (-6.0, -5.0, -1.0, -2.0) );
	gBarriers.push_back( new Barrier (-3.0, -2.0, 4.0, -5.0) );
	gBarriers.push_back( new Barrier (-3.0, 2.0, 5.0, 4.0) );
	gBarriers.push_back( new Barrier (-3.0, 1.0, -5.0, -6.0) );
	gBarriers.push_back( new Barrier (-2.0, 6.0, 1.0, 0.0) );
	gBarriers.push_back( new Barrier (-2.0, 6.0, -1.0, -2.0) );
	gBarriers.push_back( new Barrier (5.0, 6.0, -2.0, -6.0) );
	gBarriers.push_back( new Barrier (3.0, 5.0, -5.0, -6.0) );
	gBarriers.push_back( new Barrier (5.0, 6.0, 5.0, 1.0) );
	gBarriers.push_back( new Barrier (3.0, 5.0, 5.0, 4.0) );
	
	//add doors (color, shape, direction, x, y)
	gDoors.push_back( new Door (2, 3, 1, -5.5, -0.5) );
	gDoors.push_back( new Door (0, 1, 2, 2.5, 4.5) );
	gDoors.push_back( new Door (1, 0, 1, 4.5, -0.5) );
	
	//add star tile
	gTiles.push_back( new Star (-1.5, -0.5) );
	
	//add changer tiles
	gTiles.push_back( new ColorChanger (1, -0.5, 1.5) );
	gTiles.push_back( new ShapeChanger (1, -0.5, -2.5) );
	
}

// level two 
//
// sets up the second level
//
void GamePlay::levelTwo()
{
	level = 2;
	
	//player set up (posX, posY, shape, color, leftKey, rightKey, upKey, downKey)
	player.playerSetUp(-7.5, -0.5, 3, 1);
	
	//add boarder barriers (left, right, top, bottom)
	gBarriers.push_back( new Barrier (-9.5 , 9.5, -8.0, -8.5) );
	gBarriers.push_back( new Barrier (-9.5 , 9.5, 8.5, 8.0) );
	gBarriers.push_back( new Barrier (-9.5 , -9.0, 8.5, -8.5) );
	gBarriers.push_back( new Barrier (9.0 , 9.5, 8.5, -8.5) );
	//add level boarder
	gBarriers.push_back( new Barrier (-9.0, -6.0, 7.0, 6.0) );
	gBarriers.push_back( new Barrier (-7.0, -6.0, 8.0, 7.0) );
	
	//play area (left -9.0) (right 9.0) (top 8.0) (bottom -8.0)
	
	//add barriers (left, right, top, bottom)
	gBarriers.push_back( new Barrier (-6.0, -5.0, 8.0, 0.0) );
	gBarriers.push_back( new Barrier (-6.0, -5.0, -1.0, -8.0) );
	gBarriers.push_back( new Barrier (-2.0, -1.0, 1.0, -5.0) );
	gBarriers.push_back( new Barrier (-2.0, -1.0, 4.0, 2.0) );
	gBarriers.push_back( new Barrier (-1.0, 0.0, 4.0, 3.0) );
	gBarriers.push_back( new Barrier (1.0, 2.0, 4.0, 1.0) );
	gBarriers.push_back( new Barrier (-1.0, 2.0, 1.0, 0.0) );
	gBarriers.push_back( new Barrier (-1.0, 3.0, -1.0, -2.0) );
	gBarriers.push_back( new Barrier (3.0, 4.0, 4.0, -4.0) );
	gBarriers.push_back( new Barrier (4.0, 9.0, 4.0, 3.0) );
	gBarriers.push_back( new Barrier (4.0, 7.0, 0.0, -1.0) );
	gBarriers.push_back( new Barrier (-2.0, 4.0, -5.0, -6.0) );
	
	//add doors (color, shape, direction, x, y)
	gDoors.push_back( new Door (3, 2, 1, -5.5, -0.5) );
	gDoors.push_back( new Door (2, 0, 1, 3.5, -4.5) );
	gDoors.push_back( new Door (0, 3, 1, -1.5, 1.5) );
	gDoors.push_back( new Door (2, 0, 1, 1.5, -0.5) );
	gDoors.push_back( new Door (0, 1, 2, 2.5, 2.5) );
	gDoors.push_back( new Door (0, 1, 2, 0.5, 3.5) );
	
	//add star tile (x,y)
	gTiles.push_back( new Star (-0.5, -0.5) );
	
	//add changer tiles (changer, x, y)
	gTiles.push_back( new ColorChanger (3, -7.5, 4.5) );
	gTiles.push_back( new ColorChanger (2, 4.5, 2.5) );
	gTiles.push_back( new ShapeChanger (2, -7.5, -6.5) );
	gTiles.push_back( new ShapeChanger (3, -0.5, -3.5) );
	gTiles.push_back( new ShapeChanger (1, 0.5, 1.5) );
}

// level three 
//
// sets up the thirds and final level
//
void GamePlay::levelThree()
{
	level = 3;
	
	//player set up (posX, posY, shape, color, leftKey, rightKey, upKey, downKey)
	player.playerSetUp(7.5, -6.5, 3, 3);
	
	//add boarder barriers (left, right, top, bottom)
	gBarriers.push_back( new Barrier (-9.5 , 9.5, -8.0, -8.5) );
	gBarriers.push_back( new Barrier (-9.5 , 9.5, 8.5, 8.0) );
	gBarriers.push_back( new Barrier (-9.5 , -9.0, 8.5, -8.5) );
	gBarriers.push_back( new Barrier (9.0 , 9.5, 8.5, -8.5) );
	//add level boarder
	gBarriers.push_back( new Barrier (-9.0, -6.0, 7.0, 6.0) );
	gBarriers.push_back( new Barrier (-7.0, -6.0, 8.0, 7.0) );
	
	//play area (left -9.0) (right 9.0) (top 8.0) (bottom -8.0)
	
	//add barriers (left, right, top, bottom)
	gBarriers.push_back( new Barrier (-4.0, -3.0, -1.0, -6.0) );
	gBarriers.push_back( new Barrier (-4.0, -3.0, -7.0, -8.0) );
	gBarriers.push_back( new Barrier (-9.0, -7.0, -7.0, -8.0) );
	gBarriers.push_back( new Barrier (-9.0, -7.0, -5.0, -6.0) );
	gBarriers.push_back( new Barrier (-9.0, -7.0, -3.0, -4.0) );
	gBarriers.push_back( new Barrier (-9.0, -5.0, -1.0, -2.0) );
	gBarriers.push_back( new Barrier (-6.0, -3.0, 8.0, 6.0) );
	gBarriers.push_back( new Barrier (-4.0, -3.0, 6.0, 5.0) );
	gBarriers.push_back( new Barrier (-4.0, -3.0, 4.0, 1.0) );
	gBarriers.push_back( new Barrier (-5.0, -4.0, 2.0, 1.0) );
	gBarriers.push_back( new Barrier (-9.0, -6.0, 2.0, 1.0) );
	gBarriers.push_back( new Barrier (6.0, 9.0, 4.0, 3.0) );
	gBarriers.push_back( new Barrier (0.0, 5.0, 4.0, 3.0) );
	gBarriers.push_back( new Barrier (0.0, 1.0, 5.0, 4.0) );
	gBarriers.push_back( new Barrier (0.0, 1.0, 8.0, 6.0) );
	gBarriers.push_back( new Barrier (-1.0, 0.0, -7.0, -8.0) );
	gBarriers.push_back( new Barrier (-1.0, 0.0, -4.0, -6.0) );
	gBarriers.push_back( new Barrier (-2.0, 4.0, -3.0, -4.0) );
	gBarriers.push_back( new Barrier (5.0, 7.0, -3.0, -4.0) );
	gBarriers.push_back( new Barrier (8.0, 9.0, -3.0, -4.0) );
	gBarriers.push_back( new Barrier (0.0, 9.0, 0.0, -1.0) );
	gBarriers.push_back( new Barrier (0.0, 3.0, -5.0, -6.0) );
	gBarriers.push_back( new Barrier (-2.0, -1.0, 0.0, -3.0) );
	gBarriers.push_back( new Barrier (0.0, 1.0, -1.0, -3.0) );
	gBarriers.push_back( new Barrier (5.0, 6.0, -1.0, -2.0) );
	gBarriers.push_back( new Barrier (-3.0, -2.0, 0.0, -4.0) );
	
	//add doors (color, shape, direction, x, y)
	gDoors.push_back( new Door (0, 3, 1, -3.5, -6.5) );
	gDoors.push_back( new Door (2, 2, 2, -4.5, -1.5) );
	gDoors.push_back( new Door (3, 0, 2, -5.5, 1.5) );
	gDoors.push_back( new Door (2, 0, 1, -3.5, 4.5) );
	gDoors.push_back( new Door (0, 1, 1, 0.5, 5.5) );
	gDoors.push_back( new Door (0, 2, 2, 5.5, 3.5) );
	gDoors.push_back( new Door (1, 0, 1, -0.5, -6.5) );
	gDoors.push_back( new Door (0, 1, 1, 2.5, -4.5) );
	gDoors.push_back( new Door (0, 1, 2, 4.5, -3.5) );
	gDoors.push_back( new Door (3, 0, 2, 7.5, -3.5) );
	gDoors.push_back( new Door (3, 1, 2, -0.5, -0.5) );
	gDoors.push_back( new Door (0, 2, 1, 5.5, -2.5) );
	gDoors.push_back( new Door (1, 0, 1, -7.5, -6.5) );
	gDoors.push_back( new Door (0, 1, 1, -7.5, -4.5) );
	gDoors.push_back( new Door (2, 0, 1, -7.5, -2.5) );
	
	//add star tile (x,y)
	gTiles.push_back( new Star (-0.5, -2.5) );
	
	//add changer tiles (changer, x, y)
	gTiles.push_back( new ColorChanger (2, -8.5, -4.5) );
	gTiles.push_back( new ColorChanger (3, -7.5, 4.5) );
	gTiles.push_back( new ColorChanger (1, 0.5, -4.5) );
	gTiles.push_back( new ShapeChanger (1, -8.5, -6.5) );
	gTiles.push_back( new ShapeChanger (2, -8.5, -2.5) );
	gTiles.push_back( new ShapeChanger (3, -1.5, -4.5) );
	gTiles.push_back( new ShapeChanger (3, -4.5, -3.5) );
	gTiles.push_back( new ShapeChanger (3, -6.5, -5.5) );
	gTiles.push_back( new ShapeChanger (3, -5.5, -7.5) );
	gTiles.push_back( new ShapeChanger (1, 7.5, 6.5) );
	gTiles.push_back( new ShapeChanger (2, 4.5, 6.5) );
	gTiles.push_back( new ShapeChanger (1, 1.5, -1.5) );
	gTiles.push_back( new ShapeChanger (2, 7.5, -1.5) );
}

//////////////////////
// Camera functions //
//////////////////////

Camera::Camera()
{
        aspect = 1;
        windowWidth = 1000;
        windowHeight = 900;
        orthoHeight = 17;

        fov = 45.0;
        aspect = 1.0;
        nearval = 1.5;
        farval = 50.0;
}

// do graphics init
//
// sets up window
//
void Camera::doGraphicsInit()
{
        glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
        glutInitWindowSize( windowWidth, windowHeight);
        glutInitWindowPosition( 300, 50 );

        glutCreateWindow( "Adira's Shape Shifter Game" );
        glEnable( GL_DEPTH_TEST );
}

// do camera
//
// looks at screen
//
void Camera::doCamera()
{
        glLoadIdentity();
        // gluLookAt location, look at, up vector values
        gluLookAt(  0.0, 0.0, 5.0  ,  0.0, 0.0, 0.0  ,  0.0, 1.0, 0.0  );
}

// do camera orthographic
//
// used in the reshape function to keep me looking at the board
//
void Camera::doCameraOrthographic( int w, int h)
{
        windowWidth = w;
        windowHeight = h;
        aspect = ( float ) w / ( float ) h ;
        float top = orthoHeight / 2.0;
        float bottom = -top;
        float right = ( orthoHeight * aspect ) /2.0;
        float left = -right;

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( left, right, bottom, top, nearval, farval );
} 
