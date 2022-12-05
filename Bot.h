#include <GL/freeglut.h>

#include "BotThree.h"
#include "BotFour.h"
#include "Help.h"

// -----------------
// --- Variables ---
// -----------------

// --- General ---
unsigned int botCollapseCount = 0;
bool botsMoving = false;

// --- Instances ---

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

// --- Collision Box ---

// BotThree: One
float botThreeOne_collisionMaxX;
float botThreeOne_collisionMinX;
float botThreeOne_collisionMaxY;
float botThreeOne_collisionMinY;
float botThreeOne_collisionMaxZ;
float botThreeOne_collisionMinZ;

// BotThree: Two
float botThreeTwo_collisionMaxX;
float botThreeTwo_collisionMinX;
float botThreeTwo_collisionMaxY;
float botThreeTwo_collisionMinY;
float botThreeTwo_collisionMaxZ;
float botThreeTwo_collisionMinZ;

// BotFour: One
float botFourOne_collisionMaxX;
float botFourOne_collisionMinX;
float botFourOne_collisionMaxY;
float botFourOne_collisionMinY;
float botFourOne_collisionMaxZ;
float botFourOne_collisionMinZ;

// BotFour: Two
float botFourTwo_collisionMaxX;
float botFourTwo_collisionMinX;
float botFourTwo_collisionMaxY;
float botFourTwo_collisionMinY;
float botFourTwo_collisionMaxZ;
float botFourTwo_collisionMinZ;

// --- Functions ---
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

void updateCollisionBoxes()
{
	// BotThree: One
	botThreeOne_collisionMaxX = botThreeOne_X + (botThree_bodyWidth / 2);
	botThreeOne_collisionMinX = botThreeOne_X - (botThree_bodyWidth / 2);
	botThreeOne_collisionMaxY = botThreeOne_Y + (botThree_bodyHeight / 2);
	botThreeOne_collisionMinY = botThreeOne_Y - (botThree_bodyHeight / 2);
	botThreeOne_collisionMaxZ = botThreeOne_Z + (botThree_bodyDepth / 2);
	botThreeOne_collisionMinZ = botThreeOne_Z - (botThree_bodyDepth / 2);

	// BotThree: Two
	botThreeTwo_collisionMaxX = botThreeTwo_X + (botThree_bodyWidth / 2);
	botThreeTwo_collisionMinX = botThreeTwo_X - (botThree_bodyWidth / 2);
	botThreeTwo_collisionMaxY = botThreeTwo_Y + (botThree_bodyHeight / 2);
	botThreeTwo_collisionMinY = botThreeTwo_Y - (botThree_bodyHeight / 2);
	botThreeTwo_collisionMaxZ = botThreeTwo_Z + (botThree_bodyDepth / 2);
	botThreeTwo_collisionMinZ = botThreeTwo_Z - (botThree_bodyDepth / 2);

	// BotFour: One
	botFourOne_collisionMaxX = botFourOne_X + (botFourOne_bodyWidth / 2);
	botFourOne_collisionMinX = botFourOne_X - (botFourOne_bodyWidth / 2);
	botFourOne_collisionMaxY = botFourOne_Y + (botFourOne_bodyLength / 2);
	botFourOne_collisionMinY = botFourOne_Y - (botFourOne_bodyLength / 2);
	botFourOne_collisionMaxZ = botFourOne_Z + (botFourOne_bodyDepth / 2);
	botFourOne_collisionMinZ = botFourOne_Z - (botFourOne_bodyDepth / 2);

	// BotFour: Two
	botFourTwo_collisionMaxX = botFourTwo_X + (botFourTwo_bodyWidth / 2);
	botFourTwo_collisionMinX = botFourTwo_X - (botFourTwo_bodyWidth / 2);
	botFourTwo_collisionMaxY = botFourTwo_Y + (botFourTwo_bodyLength / 2);
	botFourTwo_collisionMinY = botFourTwo_Y - (botFourTwo_bodyLength / 2);
	botFourTwo_collisionMaxZ = botFourTwo_Z + (botFourTwo_bodyDepth / 2);
	botFourTwo_collisionMinZ = botFourTwo_Z - (botFourTwo_bodyDepth / 2);
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

		if (botThreeOne_active)
		{
			botThreeOne_Z += speed;
			if (botThreeOne_Z >= endingZ)
				{ collapseBotThree(1); }
		}
		if (botThreeTwo_active)
		{
			botThreeTwo_Z += speed;
			if (botThreeTwo_Z >= endingZ)
				{ collapseBotThree(2); }
		}

		if (botFourOne_active)
		{
			botFourOne_Z += speed;
			if (botFourOne_Z >= endingZ)
				{ collapseBotFour(1); }
		}
		if (botFourTwo_active)
		{
			botFourTwo_Z += speed;
			if (botFourTwo_Z >= endingZ)
				{ collapseBotFour(2); }
		}

		updateCollisionBoxes();
		glutPostRedisplay();

		//If not all at end of line, continue
		if ((botThreeOne_active) || (botThreeTwo_active) || (botFourOne_active) || (botFourTwo_active))
			{ glutTimerFunc(10, translateAnimationHandler, 0); }
		else
			{ botsMoving = false; }
	}
}

#pragma once
