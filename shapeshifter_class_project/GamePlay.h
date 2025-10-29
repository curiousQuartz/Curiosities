#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/freeglut.h>   // or <GL/glut.h> depending on your setup
#endif

#pragma once

using namespace std;

double diffclock( clock_t clock1, clock_t clock2 );

class GamePlay
{
public:
		int level;
		bool homeScreen;
		bool gamePlayed;
		bool paused;
		
		GamePlay();
		void next();
		void clear();
		void levelOne();
		void levelTwo();
		void levelThree();
};

class Camera
{
public:
        float aspect;
        int windowHeight;
        int windowWidth;
        float orthoHeight;
        float fov;
        float nearval;
        float farval;

        Camera();
        void doCamera();
        void doCameraOrthographic( int w, int h);
        void doGraphicsInit();
};
