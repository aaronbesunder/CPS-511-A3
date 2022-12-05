#include <GL/freeglut.h>

#include "BotThree.h"
#include "BotFour.h"
#include "Help.h"

// -----------------
// --- Variables ---
// -----------------

// ---------------------
// --- Bot Instances ---
// ---------------------

unsigned int botCollapseCount = 0;
bool botsMoving = false;

GLfloat startingZ = -200;
GLfloat endingZ = -5;

// BotThree: One
GLfloat botThreeOne_Z = startingZ;
// BotThree: Two
GLfloat botThreeTwo_Z = startingZ;

// BotFour: One
GLfloat botFourOne_Z = startingZ;
// BotFour: Two
GLfloat botFourTwo_Z = startingZ;

void translateAnimationHandler(int);
void drawRobot(int botNum);

// -----------------
// --- Functions ---
// -----------------

void drawRobot(int botNum)
{
	glPushMatrix();
		switch (botNum)
		{
		case 1:
			glTranslatef(botFourOne_X, botFourOne_Y, botFourOne_Z);
			botFour_drawRobot(1);
			break;
		case 2:
			glTranslatef(botThreeOne_X, botThreeOne_Y, botThreeOne_Z);
			botThree_drawRobot(1);
			break;
		case 3:
			glTranslatef(botFourTwo_X, botFourTwo_Y, botFourTwo_Z);
			botFour_drawRobot(2);
			break;
		case 4:
			glTranslatef(botThreeTwo_X, botThreeTwo_Y, botThreeTwo_Z);
			botThree_drawRobot(2);
			break;
		}

		if (help == true)
			{ drawCoordinates(); }
	glPopMatrix();
}

// ------------------
// --- Animations ---
// ------------------

void translateAnimationHandler(int param)
{
	if (botsMoving)
	{
		// Walk Cycle: Bot Three
		if (botThree_walkCycle == false)
		{
			botThree_walkCycle = true;
			glutTimerFunc(10, botThree_walkAnimationHandler, 0);
		}

		// Walk Cycle: Bot Four
		if (botFour_walkcheck == false) {
			botFour_walkcheck = true;
			glutIdleFunc(botFour_takeStep);
		}
	
		// Update Z
		double speed = 0.2;
		bool threeCollapse = false;
		bool fourCollapse = false;

		if (botThreeOne_active)
		{
			botThreeOne_Z += speed;
			if (botThreeOne_Z >= endingZ)
				{ botThreeOne_active = false; threeCollapse = true; }
		}
		if (botThreeTwo_active)
		{
			botThreeTwo_Z += speed;
			if (botThreeTwo_Z >= endingZ)
				{ botThreeTwo_active = false; threeCollapse = true; }
		}

		if (botFourOne_active)
		{
			botFourOne_Z += speed;
			if (botFourOne_Z >= endingZ)
				{ botFourOne_active = false; botFour_stop = true; fourCollapse = true; }
		}
		if (botFourTwo_active)
		{
			botFourTwo_Z += speed;
			if (botFourTwo_Z >= endingZ)
				{ botFourTwo_active = false; botFour_stop = true; fourCollapse = true; }
		}

		glutPostRedisplay();

		//If botThree becomes inactive, collapse
		if ((threeCollapse) && (!botThree_collapseOngoing))
			{ glutTimerFunc(10, botThree_collapseAnimationHandler, 0); botThree_collapseOngoing = true; }
	
		//If botFour becomes inactive, collapse
		if (fourCollapse) 
			{ glutTimerFunc(10, botFour_collapseAnimationHandler, 0); botFour_collapseOngoing = true; }

		//If not all at end of line, continue
		if ((botThreeOne_active) || (botThreeTwo_active) || (botFourOne_active) || (botFourTwo_active))
			{ glutTimerFunc(10, translateAnimationHandler, 0); }
		else
			{ botsMoving = false; }
	}
}

#pragma once
