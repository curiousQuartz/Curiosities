// Adira Lindzon
// Shape Shifter
// November 13, 2019
//
// inputs:
// esc - quits program
// arrow keys - character movement
// left click and some keys - press buttons on the home screen
//
// Description:
// reads in grades and weights and outputs:
// 1. Grades and weights summery 
// 2. Average 
// 3. Letter grade 
// for any number of grades, for any number of students. 

//include user defined Classes
#include "ShapeShifter.h"
#include "SpecialTiles.h"
#include "GamePlay.h"
#include "Door.h"

// Define these globally due to glut's implementation
GamePlay MyGame;
Camera MyCamera;
ShapeShifter player;
vector<Door*> gDoors;
vector<Barrier*> gBarriers;
vector<SpecialTile*> gTiles;

clock_t gPastTime = 0;

//functions
void myMenu(int value);
void display( void );
void reshape( int w, int h );
void moveWorld();
void mousebutton(int button, int state, int x, int y);
void keyboardDown( unsigned char key, int x, int y );
void specialDown( int key, int x, int y );
void specialUp( int key, int x, int y );
void displaySquare( float x, float y, float scalex, float scaley );
void displayString( string s, void * font );
void displayStroke( string s, void * font );

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);  
    MyCamera.doGraphicsInit();
	
	MyCamera.doCamera();
	
	moveWorld();
	
	// Add a Menu
	glutCreateMenu(myMenu);
	glutAddMenuEntry("Return to Home", 1);
	glutAddMenuEntry("Restart Level", 2);
	glutAddMenuEntry("Restart Game", 3);
	glutAddMenuEntry("Exit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutIdleFunc( moveWorld );
	
	//user input functions
	glutIgnoreKeyRepeat( 1 );
	glutKeyboardFunc( keyboardDown );
	glutSpecialFunc( specialDown );
	glutSpecialUpFunc( specialUp );
	glutMouseFunc(mousebutton);
	
	glutMainLoop();

	return 0;
}


// myMenu
//
// checks which menu item was pressed and acts on it
//
void myMenu(int value)
{
	switch (value)
	{
		case 1:
			//return home
			MyGame.homeScreen = true;
			MyGame.paused = true;
			break;
		case 2:
			// restart level
			MyGame.homeScreen = false;
			MyGame.level--;
			MyGame.next();
			break;
		case 3:
			// restart game
			MyGame.homeScreen = false;
			MyGame.level = 0;
			MyGame.next();
			break;
		case 4:
			// quit
			exit(0);
			break;
	}
}

// display
// 
// draw the scene in the graphics window
//
void display()
{
	glMatrixMode( GL_MODELVIEW );
	MyCamera.doCamera();

	//background color
	glClearColor( 0.9, 0.9, 0.92, 0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	//homescreen display
	if (MyGame.homeScreen)
	{
		//play and quit boarders
		displaySquare( 0, 1.5, 3, 1 );
		displaySquare( 0, -1.5, 3, 1 );
		
		if (MyGame.gamePlayed)
		{
			//squares around level selects
			displaySquare(-4, -6, 1.5, 0.5);
			displaySquare(0, -6, 1.5, 0.5);
			displaySquare(4, -6, 1.5, 0.5);
		}
		
		if (MyGame.paused)
		{
			//add resume button when game is paused
			glColor3f(0.0, 0.0, 0.0);
			displaySquare( 0, 4, 3, 0.75 );
			glPushMatrix();
				glScalef(.005,.005,.005);
				glTranslatef(-500, 750, 0);
				displayStroke("Resume (R)", GLUT_STROKE_MONO_ROMAN);
			glPopMatrix();
		}
		
		//title and play and quit text
		glScalef(.015,.015,.015);
		glTranslatef(-400, 375, 0);
		glColor3f(0.0, 0.0, 0.0);
		displayStroke("Shape Shifter", GLUT_STROKE_ROMAN);
		glScalef(.3,.3,.3);
		glTranslatef(-1850, -975, 0);
		glColor3f(0.0, 0.0, 0.0);
		displayStroke("Play (P)", GLUT_STROKE_MONO_ROMAN);
		glTranslatef(-850, -670, 0);
		glColor3f(0.0, 0.0, 0.0);
		displayStroke("Quit (Q)", GLUT_STROKE_MONO_ROMAN);
		
		if (MyGame.gamePlayed)
		{
			//level selection text
			glScalef(.7,.7,.7);
			glTranslatef(-1480, -700, 0);
			glColor3f(0.0, 0.0, 0.0);
			displayStroke("Level Select", GLUT_STROKE_MONO_ROMAN);
			glScalef(.7,.7,.7);
			glTranslatef(-2400, -300, 0);
			displayStroke("Use number keys to select level", GLUT_STROKE_MONO_ROMAN);
			glScalef(1.5,1.5,1.5);
			glTranslatef(-2600, -475, 0);
			displayStroke("Level 1", GLUT_STROKE_MONO_ROMAN);
			glTranslatef(500, 0, 0);
			displayStroke("Level 2", GLUT_STROKE_MONO_ROMAN);
			glTranslatef(500, 0, 0);
			displayStroke("Level 3", GLUT_STROKE_MONO_ROMAN);
		}
		// instructions at the start
		else
		{
			glScalef(.7,.7,.7);
			glTranslatef(-1280, -700, 0);
			glColor3f(0.0, 0.0, 0.0);
			displayStroke("Instructions", GLUT_STROKE_MONO_ROMAN);
			glScalef(.7,.7,.7);
			glTranslatef(-1900, -400, 0);
			glColor3f(0.0, 0.0, 0.0);
			displayStroke("Movement: arrow keys", GLUT_STROKE_MONO_ROMAN);
			glTranslatef(-3700, -300, 0);
			glColor3f(0.0, 0.0, 0.0);
			displayStroke("Move through doors that match your color and shape", GLUT_STROKE_MONO_ROMAN);
			glTranslatef(-5000, -300, 0);
			glColor3f(0.0, 0.0, 0.0);
			displayStroke("Change shape and color with tiles on the floor", GLUT_STROKE_MONO_ROMAN);
			glTranslatef(-3800, -300, 0);
			glColor3f(0.0, 0.0, 0.0);
			displayStroke("Reach the gold star to win", GLUT_STROKE_MONO_ROMAN);
		}
	}
	//displays the level if the homescreen is not active
	else
	{
		//display level number
		stringstream ss;
		ss << MyGame.level;
		string lev;
		ss >> lev;
		
		glColor3f(0.419608, 0.137255, 0.556863);
		glRasterPos2f(-8.7, 7.3);
		displayString("Level " + lev, GLUT_BITMAP_TIMES_ROMAN_24);
		
		//draw grid
		glColor3f( 0.7, 0.65, 0.75 );
		for ( float i = -8.5; i < 9; i++ )
		{
			for ( float j = -7.5; j < 8; j++ )
			{
				//leave out squares in level display spot
				if ( !(i == -8.5 && j == 7.5) && !(i == -7.5 && j == 7.5) )
				{
					displaySquare( i, j, 0.5, 0.5 );
				}
			}
		}
		//draw player
		player.draw();
		//draw doors
		for ( unsigned int i = 0; i < gDoors.size(); ++i )
		{
			if(!gDoors[i]->open)
			{
				gDoors[i]->draw();
			}
		}
		//draw barriers
		for ( unsigned int i = 0; i < gBarriers.size(); ++i )
		{
			gBarriers[i]->draw();
		}
		//draw special tiles
		for ( unsigned int i = 0; i < gTiles.size(); ++i )
		{
			gTiles[i]->draw();
		}
	}
	
	glutSwapBuffers();
}

// reshape
//
// handle the reshaping of the graphics display window
//
void reshape( int w, int h )
{
	MyCamera.windowWidth = w;
	MyCamera.windowHeight = h;
	glViewport( 0, 0, w, h);
	MyCamera.doCameraOrthographic( w, h );
}

// moveWorld
//
// compute the new position as time passes
//
void moveWorld()
{
		double elapsedTime; 
        clock_t currentTime;

        if ( gPastTime == 0 )
        {
                gPastTime = clock();
        }
        else 
        {
                currentTime = clock();
                elapsedTime = double( diffclock( currentTime, gPastTime ) ) / 1000.0;   

                if ( elapsedTime > MINIMUM_MILLISECOND_UPDATE )
                {
					if (!MyGame.paused)
					{
						//compute player position
                        player.computePosition( elapsedTime );
						//check player intersection with doors
						for ( unsigned int i = 0; i < gDoors.size(); ++i )
						{
							gDoors[i]->checkIntersection();
						}
						//check player intersection with barriers
						for ( unsigned int i = 0; i < gBarriers.size(); ++i )
						{
							gBarriers[i]->checkIntersection();
						}
						//check player intersection with special tiles
						for ( unsigned int i = 0; i < gTiles.size(); ++i )
						{
							gTiles[i]->checkIntersection();
						}
					}
						
                    gPastTime = currentTime;

                    glutPostRedisplay();
                }
        }
	
}

void mousebutton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// make sure the home screen is active
		if (MyGame.homeScreen)
		{
			if (x > 340 && x < 660)
			{
				if (MyGame.paused && y > 200 && y < 280)
				{
					//resume was pressed
					MyGame.homeScreen = false;
					MyGame.paused = false;
				}
				if (y > 320 && y < 425)
				{
					//play was pressed
					MyGame.homeScreen = false;
					MyGame.level = 0;
					MyGame.next();
				}
				if (y > 475 && y < 585)
				{
					//quit was pressed
					exit(0);
				}
			}
			if (MyGame.gamePlayed)
			{
				if (y > 740 && y < 795)
				{
					if (x > 210 && x < 370)
					{
						//level 1 was pressed
						MyGame.homeScreen = false;
						MyGame.level = 0;
						MyGame.next();
					}
					if (x > 420 && x < 580)
					{
						//level 2 was pressed
						MyGame.homeScreen = false;
						MyGame.level = 1;
						MyGame.next();
					}
					if (x > 635 && x < 790)
					{
						//level 3 was pressed
						MyGame.homeScreen = false;
						MyGame.level = 2;
						MyGame.next();
					}
				}
			}
		}
	}
}

// keyboardDown
//
// check for input from the keyboard for each tank
//
void keyboardDown( unsigned char key, int x, int y )
{
	if (key == 27)
	{
		exit(0);
	}
	if (MyGame.homeScreen)
	{
		switch (key)
		{
			//case 'P':
			case 'p':
				MyGame.homeScreen = false;
				MyGame.level = 0;
				MyGame.next();
				break;
			case 'q':
			//case 'Q':
				exit(0);
				break;
		}
		if (MyGame.paused && key == 'r')
		{
			MyGame.homeScreen = false;
			MyGame.paused = false;
		}
		if (MyGame.gamePlayed)
		{
			switch (key)
			{
				case '1':
					MyGame.clear();
					MyGame.levelOne();
					break;
				case '2':
					MyGame.clear();
					MyGame.levelTwo();
					break;
				case '3':
					MyGame.clear();
					MyGame.levelThree();
					break;
			}
		}
	}
}
void specialDown( int key, int x, int y )
{
	player.keyDown( key );
}



// keyboardUp
//
// check for input from the keyboard for each tank
//
void specialUp( int key, int x, int y )
{
	player.keyUp( key );
}

//displaySquare
//
//prints lines in a square so there is no fill
//
void displaySquare( float x, float y, float scalex, float scaley )
{
	glBegin( GL_LINES );
		glVertex2f( x-scalex, y+scaley);
		glVertex2f( x-scalex, y-scaley);
	glEnd();
	glBegin( GL_LINES );
		glVertex2f( x+scalex, y-scaley);
		glVertex2f( x+scalex, y+scaley);
	glEnd();
	glBegin( GL_LINES );
		glVertex2f( x-scalex, y+scaley);
		glVertex2f( x+scalex, y+scaley);
	glEnd();
	glBegin( GL_LINES );
		glVertex2f( x-scalex, y-scaley);
		glVertex2f( x+scalex, y-scaley);
	glEnd();
}

//displayString
//
//translates a string onto the screen
//
void displayString( string s, void * font )
{
	for ( string::iterator i = s.begin(); i != s.end(); ++i )
	{
		char c = *i;
		glutBitmapCharacter( font, c );
	}
}
void displayStroke( string s, void * font )
{
	for ( string::iterator i = s.begin(); i != s.end(); ++i )
	{
		char c = *i;
		glutStrokeCharacter( font, c );
	}
}
