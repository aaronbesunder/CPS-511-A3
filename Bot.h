#pragma once

#include <GL/freeglut.h>

#include "BotThree.h"
#include "BotFour.h"
#include "Help.h"
#include "Cannon.h"

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

// --- Projectile ---
float bot_projectileSpeed = 0.5;
bool bot_projectileExists = false;
bool bot_isFiring = false;

// Projectile Dimensions
float botproj_height = 0.3;
float botproj_width = 0.3;
float botproj_depth = 5;
const int bot_maxProjectileNum = 30;

GLfloat botprojMat_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat botprojMat_specular[] = { 0.45, 0.55, 0.45, 1.0 };
GLfloat botprojMat_diffuse[] = { 0.1f, 0.1f, 0.1f, 0.2f };
GLfloat botprojMat_shininess[] = { 5.0F };

bool bot_projectile_active[bot_maxProjectileNum];
bool bot_projectile_cannonHit[bot_maxProjectileNum];
int bot_projectile_botNum[bot_maxProjectileNum];
float bot_projectile_xAng[bot_maxProjectileNum];
float bot_projectile_yAng[bot_maxProjectileNum];
float bot_projectile_xPos[bot_maxProjectileNum];
float bot_projectile_yPos[bot_maxProjectileNum];
float bot_projectile_zPos[bot_maxProjectileNum]; // Distance
void bot_drawProjectile(int);
void bot_addProjectile(int);
void bot_projectileAnimationHandler(int);
void bot_printProjectileArray();
void bot_resetProjectileArray();
void bot_updateProjectileExist();

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
void bot_updateCollisionBoxes();
bool bot_checkBotCollision(float, float, float);

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

		/*if (help == true)
			{ drawCoordinates(); }*/

	glPopMatrix();
}

float DotProduct(float lhsX, float lhsY, float lhsZ, float rhsX, float rhsY, float rhsZ)
{
	return lhsX * rhsX + lhsY * rhsY + lhsZ * rhsZ;
}

void bot_updateCollisionBoxes()
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

bool bot_checkBotCollision(float xPos, float yPos, float zPos)
{
	//Update positions
	//glTranslatef(0.0, -18, 40 + projectile_depth);
	float x = xPos;
	float y = yPos - 18;
	float z = (40 + projectile_depth) - zPos;

	// BotThree: One
	if (botThreeOne_active)
	{
		if ( (x <= botThreeOne_collisionMaxX) && (x >= botThreeOne_collisionMinX)
		  && (y <= botThreeOne_collisionMaxY) && (y >= botThreeOne_collisionMinY)
		  && (z <= botThreeOne_collisionMaxZ) && (z >= botThreeOne_collisionMinZ) )
		{ collapseBotThree(1); return true; }
	}

	// BotThree: Two
	if (botThreeTwo_active)
	{
		if ( (x <= botThreeTwo_collisionMaxX) && (x >= botThreeTwo_collisionMinX)
		  && (y <= botThreeTwo_collisionMaxY) && (y >= botThreeTwo_collisionMinY)
		  && (z <= botThreeTwo_collisionMaxZ) && (z >= botThreeTwo_collisionMinZ) )
		{ collapseBotThree(2); return true; }
	}

	// BotFour: One
	if (botFourOne_active)
	{
		if ( (x <= botFourOne_collisionMaxX) && (x >= botFourOne_collisionMinX)
		  && (y <= botFourOne_collisionMaxY) && (y >= botFourOne_collisionMinY)
		  && (z <= botFourOne_collisionMaxZ) && (z >= botFourOne_collisionMinZ) )
		{ collapseBotFour(1); return true; }
	}

	// BotFour: Two
	if (botFourTwo_active)
	{
		if ( (x <= botFourTwo_collisionMaxX) && (x >= botFourTwo_collisionMinX)
		  && (y <= botFourTwo_collisionMaxY) && (y >= botFourTwo_collisionMinY)
		  && (z <= botFourTwo_collisionMaxZ) && (z >= botFourTwo_collisionMinZ) )
		{ collapseBotFour(2); return true; }
	}

	return false;
}


void bot_drawProjectile(int index)
{
	if ((bot_projectileExists) && (bot_projectile_active[index]))
	{
		float xAng = bot_projectile_xAng[index];
		float yAng = bot_projectile_yAng[index];
		float xPos = bot_projectile_xPos[index];
		float yPos = bot_projectile_yPos[index];
		float zPos = bot_projectile_zPos[index];

		float botX = 0;
		float botY = 0;
		float botZ = 0;
		int botNum = bot_projectile_botNum[index];

		switch (botNum)
		{
			case 1:
				botX = botFourOne_X;
				botY = botFourOne_Y;
				botZ = botFourOne_Z;
				break;
			case 2:
				botX = botThreeOne_X;
				botY = botThreeOne_Y;
				botZ = botThreeOne_Z;
				break;
			case 3:
				botX = botFourTwo_X;
				botY = botFourTwo_Y;
				botZ = botFourTwo_Z;
				break;
			case 4:
				botX = botThreeTwo_X;
				botY = botThreeTwo_Y;
				botZ = botThreeTwo_Z;
				break;
		}

		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, botprojMat_ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, botprojMat_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, botprojMat_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, botprojMat_shininess);

			glTranslatef(botX, botY, botZ);
			glTranslatef(xPos, yPos, zPos); // Comment out to make projectile stand still
			
			// Rotate according to use mouse input
			glRotatef(-yAng, 1, 0, 0);
			glRotatef(-xAng, 0, 1, 0);

			//glScalef(x, y, z);
			glScalef(projectile_width, projectile_height, projectile_depth);

			//gluCylinder(quad, base radius, top radius, height, slice, stacks)
			gluCylinder(gluNewQuadric(), 0.5, 0.5, 1.0, 20, 1);

		glPopMatrix();
	}
}
void bot_addProjectile(int botNum)
{

	// Go through projectile list to see if there is an empty one
	for (int index = 0; index < bot_maxProjectileNum; index++)
	{
		// If one is not active
		if (!bot_projectile_active[index])
		{
			int min = -30;
			int max = 30;

			// Insert into array
			bot_projectile_active[index] = true;
			bot_projectile_botNum[index] = botNum;
			bot_projectile_xAng[index] = rand() % (max + 1 - min) + min;
			bot_projectile_yAng[index] = rand() % (max + 1 - min) + min;
			bot_projectile_xPos[index] = 0;
			bot_projectile_yPos[index] = 0;
			bot_projectile_zPos[index] = 0;

			/*float botX = 0;
			float botY = 0;
			float botZ = 0;
			switch (botNum)
			{
				case 1:
					botX = botFourOne_X;
					botY = botFourOne_Y;
					botZ = botFourOne_Z;
					break;
				case 2:
					botX = botThreeOne_X;
					botY = botThreeOne_Y;
					botZ = botThreeOne_Z;
					break;
				case 3:
					botX = botFourTwo_X;
					botY = botFourTwo_Y;
					botZ = botFourTwo_Z;
					break;
				case 4:
					botX = botThreeTwo_X;
					botY = botThreeTwo_Y;
					botZ = botThreeTwo_Z;
					break;
			}
			float deltaX = botX;
			float deltaY = botY + 1;
			float deltaZ = botZ + 45;
			float dpX = DotProduct(0, 0, 0, botX, 0, 0);
			float dpY = DotProduct(0, -19, 0, 0, botY, 0);
			float lnX = 0 * botX;
			float lnY = -19 * botY;
			float angX = acos(dpX/lnX);
			float angY = atan(dpY/lnY);
			bot_projectile_xAng[index] = angX;
			bot_projectile_yAng[index] = angY;*/

			//// Will hit?
			//float randNum = rand() % (max + 1 - min) + min;
			//if (randNum == 0)
			//	{ bot_projectile_cannonHit[index] = true; }

			if (bot_projectileExists == false)
			{
				bot_projectileExists = true;
				glutTimerFunc(10, bot_projectileAnimationHandler, 0);
			}

			//cannon_printProjectileArray();
			return;
		}//if not active
	}//for index

}

void bot_projectileAnimationHandler(int param)
{
	if (bot_projectileExists)
	{
		for (int index = 0; index < bot_maxProjectileNum; index++)
		{

			//     X/Y/Z
			//     _____
			//    |    /
			//    |   /                           Opp   X/Y/Z
			//    |  / Speed      SOH -> Sin(θ) = --- = -----  -> X/Y/Z = Sin(θ) * Speed
			//    |θ/                             Hyp   Speed
			//    |/
			//   /|
			//  / | Cannon
			//  ‾‾

			// Update only if active
			if (bot_projectile_active[index])
			{
				float toRad = M_PI / 180;

				float xAng = bot_projectile_xAng[index];
				float yAng = bot_projectile_yAng[index];
				float xPos = bot_projectile_xPos[index];
				float yPos = bot_projectile_yPos[index];
				float zPos = bot_projectile_zPos[index];

				float xAdd = tan(-xAng * toRad) * bot_projectileSpeed;
				float yAdd = sin(yAng * toRad) * bot_projectileSpeed;
				float zAdd = bot_projectileSpeed;

				xPos += xAdd;
				yPos += yAdd;
				zPos += zAdd;

				// Update array
				bot_projectile_xPos[index] = xPos;
				bot_projectile_yPos[index] = yPos;
				bot_projectile_zPos[index] = zPos;

				// Deactivate if reached farplane
				if (bot_projectile_zPos[index] >= farPlane)
					{ bot_projectile_active[index] = false; }

				float botX = 0;
				float botY = 0;
				float botZ = 0;
				int botNum = bot_projectile_botNum[index];

				switch (botNum)
				{
					case 1:
						botX = botFourOne_X;
						botY = botFourOne_Y;
						botZ = botFourOne_Z;
						break;
					case 2:
						botX = botThreeOne_X;
						botY = botThreeOne_Y;
						botZ = botThreeOne_Z;
						break;
					case 3:
						botX = botFourTwo_X;
						botY = botFourTwo_Y;
						botZ = botFourTwo_Z;
						break;
					case 4:
						botX = botThreeTwo_X;
						botY = botThreeTwo_Y;
						botZ = botThreeTwo_Z;
						break;
				}

				// Check for collision
				if (cannon_checkCollision(xPos + botX, yPos + botY, zPos + botZ))
					{ bot_projectile_active[index] = false; }
			}

		}//for index

		glutPostRedisplay();
		glutTimerFunc(10, bot_projectileAnimationHandler, 0);
	}//if projectile exists
}

void bot_addProjectileAnimationHandler(int param)
{
	if (bot_isFiring)
	{
		int min = 1;
		int max = 100;
		int randNum = rand() % (max + 1 - min) + min;
	
		bool active = false;
		switch (randNum)
		{
			case 1:
				active = botFourOne_active;
				break;
			case 2:
				active = botThreeOne_active;
				break;
			case 3:
				active = botFourTwo_active;
				break;
			case 4:
				active = botThreeTwo_active;
				break;
		}
		if (active)
			{ bot_addProjectile(randNum); } 
		glutTimerFunc(10, bot_addProjectileAnimationHandler, 0);
	}
}

void bot_resetProjectileArray()
{
	bot_projectileExists = false;
	for (int index = 0; index < bot_maxProjectileNum; index++)
	{
		bot_projectile_active[index] = false;
		bot_projectile_cannonHit[index] = false;
		bot_projectile_xAng[index] = 0;
		bot_projectile_yAng[index] = 0;
		bot_projectile_xPos[index] = 0;
		bot_projectile_yPos[index] = 0;
		bot_projectile_zPos[index] = 0;
	}
}

void bot_updateProjectileExist()
{
	for (int index = 0; index < bot_maxProjectileNum; index++)
	{
		if (bot_projectile_active[index])
		{
			bot_projectileExists = true;
			return;
		}
	}
	bot_projectileExists = false;
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
		double speed = 0.1;

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

		bot_updateCollisionBoxes();
		glutPostRedisplay();

		//If not all at end of line, continue
		if ((botThreeOne_active) || (botThreeTwo_active) || (botFourOne_active) || (botFourTwo_active))
			{ glutTimerFunc(10, translateAnimationHandler, 0); }
		else
			{ botsMoving = false; }
	}
}

#pragma once
