#pragma once

#include <GL/freeglut.h>
#include <math.h>

#include "Bot.h"
void updateCollisionBoxes();

// -----------------
// --- Variables ---
// -----------------

// Robot Dimensions
float botThree_bodyDepth = 10.0;
float botThree_bodyHeight = botThree_bodyDepth * 0.5;
float botThree_bodyWidth = botThree_bodyDepth * 0.5;

float botThree_cannonDiameter = botThree_bodyDepth * 0.2;
float botThree_legDiameter = botThree_bodyDepth * 0.2;
float botThree_upperLegHeight = botThree_bodyDepth * 0.3;
float botThree_lowerLegHeight = botThree_bodyDepth * 0.8;

// Control Robot body rotation on base
float botThree_robotAngle = 0.0;

//Rotation speed
float rotateSpeed = 2.0;

//Control joints
char botThree_jointSelection[] = "    ";
float botThree_bodyAngle = 0.0;

//Control cannon rotation
bool botThree_cannonRotation = false;
float botThree_cannonAngle = 0.0;

//Control walk rotation
bool botThree_walkCycle = false;
bool botThree_collapseOngoing = false;
float botThree_walkArr[][2] = {
	{45.0, 270.0},
	{46.0, 271.0},
	{47.0, 272.0},
	{48.0, 273.0},
	{49.0, 274.0},
	{50.0, 275.0},
	{51.0, 276.0},
	{52.0, 277.0},
	{53.0, 278.0},
	{54.0, 279.0},
	{55.0, 280.0},
	{56.0, 281.0},
	{57.0, 282.0},
	{58.0, 283.0},
	{59.0, 284.0},
	{60.0, 285.0},
	{61.0, 286.0},
	{62.0, 287.0},
	{63.0, 288.0},
	{64.0, 289.0},
	{65.0, 290.0},
	{66.0, 291.0},
	{67.0, 292.0},
	{68.0, 293.0},
	{69.0, 294.0},
	{70.0, 295.0},
	{71.0, 296.0},
	{72.0, 297.0},
	{73.0, 298.0},
	{74.0, 299.0},
	{75.0, 300.0},

	{75.0, 300.0},
	{76.0, 296.0},
	{77.0, 292.0},
	{78.0, 288.0},
	{79.0, 284.0},
	{80.0, 280.0},
	{81.0, 276.0},
	{82.0, 272.0},
	{83.0, 268.0},
	{84.0, 264.0},
	{85.0, 260.0},
	{86.0, 256.0},
	{87.0, 252.0},
	{88.0, 248.0},
	{89.0, 244.0},
	{90.0, 240.0},
	{91.0, 236.0},
	{92.0, 232.0},
	{93.0, 228.0},
	{94.0, 224.0},
	{95.0, 220.0},
	{96.0, 216.0},
	{97.0, 212.0},
	{98.0, 208.0},
	{99.0, 204.0},
	{100.0, 200.0},

	{99.0, 200.9},
	{95.0, 204.5},
	{91.0, 208.1},
	{87.0, 211.7},
	{83.0, 215.3},
	{79.0, 218.9},
	{75.0, 222.5},
	{71.0, 226.1},
	{67.0, 229.7},
	{63.0, 233.3},
	{59.0, 236.9},
	{55.0, 240.5},
	{51.0, 244.1},
	{47.0, 247.7},
	{43.0, 251.3},
	{39.0, 254.9},
	{35.0, 258.5},
	{31.0, 262.1},
	{27.0, 265.7},
	{23.0, 269.3},
	{19.0, 272.9},
	{15.0, 276.5},
	{11.0, 280.1},
	{7.0, 283.7},
	{3.0, 287.3},
	{0.0, 290.0},

	{359.0, 291.5},
	{357.0, 294.5},
	{355.0, 297.5},
	{353.0, 300.5},
	{351.0, 303.5},
	{349.0, 306.5},
	{347.0, 309.5},
	{345.0, 312.5},
	{343.0, 315.5},
	{341.0, 318.5},
	{339.0, 321.5},
	{337.0, 324.5},
	{335.0, 327.5},
	{333.0, 330.5},
	{331.0, 333.5},
	{329.0, 336.5},
	{327.0, 339.5},
	{325.0, 342.5},
	{323.0, 345.5},
	{321.0, 348.5},
	{320.0, 350.0},

	{ 321.0, 349.0 },
	{ 324.0, 346.0 },
	{ 327.0, 343.0 },
	{ 330.0, 340.0 },
	{ 333.0, 337.0 },
	{ 336.0, 334.0 },
	{ 339.0, 331.0 },
	{ 342.0, 328.0 },
	{ 345.0, 325.0 },
	{ 348.0, 322.0 },
	{ 351.0, 319.0 },
	{ 354.0, 316.0 },
	{ 357.0, 313.0 },
	{   0.0, 310.0 },

	{  1.0, 309.1 },
	{  4.0, 306.4 },
	{  7.0, 303.8 },
	{ 10.0, 301.1 },
	{ 13.0, 298.4 },
	{ 16.0, 295.8 },
	{ 19.0, 293.1 },
	{ 22.0, 290.4 },
	{ 25.0, 287.8 },
	{ 28.0, 285.1 },
	{ 31.0, 282.4 },
	{ 34.0, 279.8 },
	{ 37.0, 277.1 },
	{ 40.0, 274.4 },
	{ 43.0, 271.8 },
	{ 45.0, 270.0 }
};

// Functions
void botThree_drawRobot(int);

void botThree_drawBody();
void botThree_drawCannons();

void botThree_drawLeg(int, int, int, int);
void botThree_drawHipJoint(int);
void botThree_drawUpperLeg();
void botThree_drawKneeJoint(int);
void botThree_drawLowerLeg();
void botThree_drawFoot(int, int, int);

void botThree_cannonAnimationHandler(int);
void botThree_walkAnimationHandler(int);
void botThree_collapseAnimationHandler(int);

// Lighting and Shading
GLfloat botThree_robotBody_mat_ambient[] = { 0.3f, 0.15f, 0.3f, 1.0f };
GLfloat botThree_robotBody_mat_specular[] = { 0.3f, 0.15f, 0.3f, 1.0f };
GLfloat botThree_robotBody_mat_diffuse[] = { 0.3f, 0.15f, 0.3f, 1.0f };
GLfloat botThree_robotBody_mat_shininess[] = { 32.0F };

GLfloat botThree_robotJoints_mat_ambient[] = { 0.25f, 0.25f, 0.25f, 0.25f };
GLfloat botThree_robotJoints_mat_diffuse[] = { 0.25f, 0.25f, 0.25f, 0.25f };
GLfloat botThree_robotJoints_mat_specular[] = { 0.25f, 0.25f, 0.25f, 0.25f };
GLfloat botThree_robotJoints_mat_shininess[] = { 20.0F };

GLfloat botThree_robotLeg_mat_ambient[] = { 0.125f, 0.125f, 0.125f, 0.125f };
GLfloat botThree_robotLeg_mat_diffuse[] = { 0.125f, 0.125f, 0.125f, 0.125f };
GLfloat botThree_robotLeg_mat_specular[] = { 0.125f, 0.125f, 0.125f, 0.125f };
GLfloat botThree_robotLeg_mat_shininess[] = { 10.0F };

// BotThree
GLfloat botThree_startingY = -8.5;

// BotThree: One
bool botThreeOne_active = true;

GLfloat botThreeOne_X = -10;
GLfloat botThreeOne_Y = botThree_startingY;

float botThreeOne_rightHipAngle = 45.0;
float botThreeOne_leftHipAngle = 45.0;
float botThreeOne_rightKneeAngle = 270.0;
float botThreeOne_leftKneeAngle = 270.0;
int botThreeOne_rightWalkIndex = 0;
int botThreeOne_leftWalkIndex = 67;

// BotThree: Two
bool botThreeTwo_active = true;

GLfloat botThreeTwo_X = 30;
GLfloat botThreeTwo_Y = botThree_startingY;

float botThreeTwo_rightHipAngle = 45.0;
float botThreeTwo_leftHipAngle = 45.0;
float botThreeTwo_rightKneeAngle = 270.0;
float botThreeTwo_leftKneeAngle = 270.0;
int botThreeTwo_rightWalkIndex = 0;
int botThreeTwo_leftWalkIndex = 67;

// ------------
// --- Draw ---
// ------------

void botThree_drawRobot(int botNum)
{
	// Bot Number
	float leftHipAngle = 0;
	float rightHipAngle = 0;
	float leftKneeAngle = 0;
	float rightKneeAngle = 0;
	if (botNum == 1)
	{
		leftHipAngle = botThreeOne_leftHipAngle;
		rightHipAngle = botThreeOne_rightHipAngle;
		leftKneeAngle = botThreeOne_leftKneeAngle;
		rightKneeAngle = botThreeOne_rightKneeAngle;
	}
	else if (botNum == 2)
	{
		leftHipAngle = botThreeTwo_leftHipAngle;
		rightHipAngle = botThreeTwo_rightHipAngle;
		leftKneeAngle = botThreeTwo_leftKneeAngle;
		rightKneeAngle = botThreeTwo_rightKneeAngle;
	}

	glPushMatrix();
		// spin robot on base. 
		glRotatef(botThree_robotAngle, 0.0, 1.0, 0.0);

		botThree_drawBody();
		botThree_drawLeg(leftHipAngle, rightHipAngle, leftKneeAngle, rightKneeAngle);

	glPopMatrix();
}

void botThree_drawBody()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, botThree_robotBody_mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, botThree_robotBody_mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, botThree_robotBody_mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, botThree_robotBody_mat_shininess);

	glPushMatrix();

		//Rotate from hip joint
		glTranslatef(0.0, (botThree_bodyHeight * -0.5) + (botThree_legDiameter * 0.5), (botThree_bodyDepth * -0.5) + (botThree_legDiameter * 0.5));
		glRotatef(botThree_bodyAngle, 1.0, 0.0, 0.0);
		glTranslatef(0.0, (botThree_bodyHeight * 0.5) - (botThree_legDiameter * 0.5), (botThree_bodyDepth * 0.5) - (botThree_legDiameter * 0.5) );
		
		float hypotenuseOneByOne = ( sqrt(pow(1, 2) + pow(1, 2)) ) / 10;
		float hypotenuseFourByOne = (sqrt(pow(0.25, 2) + pow(1, 2))) / 10;

		//Back
		glPushMatrix();
			glTranslatef(0.0f, botThree_bodyDepth * 0.05, botThree_bodyDepth * -0.35f);
			glScalef(botThree_bodyWidth, botThree_bodyHeight * 0.8, botThree_bodyDepth * 0.3);
			glutSolidCube(1.0);
		glPopMatrix();

		//Base
		glPushMatrix();
			glTranslatef(0.0f, botThree_bodyDepth * -0.2, botThree_bodyDepth * -0.05f);
			glScalef(botThree_bodyWidth, botThree_bodyHeight * 0.2, botThree_bodyDepth * 0.9);
			glutSolidCube(1.0);
		glPopMatrix();

		//Bottom Lip
		glPushMatrix();
			glTranslatef(0.0f, botThree_bodyHeight * -0.3, botThree_bodyDepth * 0.4f);
			glRotatef(45.0, 1.0f, 0.0f, 0.0f);
			glScalef(botThree_bodyWidth, botThree_bodyDepth * hypotenuseOneByOne, botThree_bodyDepth * hypotenuseOneByOne);
			glutSolidCube(1.0);
		glPopMatrix();

		//Forward Top Slope
		glPushMatrix();
			glTranslatef(0.0f, botThree_bodyDepth * -0.05f, botThree_bodyDepth * 0.2f);
			glRotatef(45.0, 1.0f, 0.0f, 0.0f);
			glScalef(botThree_bodyWidth, botThree_bodyDepth * (hypotenuseOneByOne * 2), botThree_bodyDepth * (hypotenuseOneByOne * 2));
			glutSolidCube(1.0);
		glPopMatrix();

		//Back Top Slope
		glPushMatrix();
			glTranslatef(0.0f, 0.0, botThree_bodyDepth * -0.05f);
			glRotatef(14.036, 1.0f, 0.0f, 0.0f);
			glScalef(botThree_bodyWidth, botThree_bodyDepth * (hypotenuseFourByOne * 4), botThree_bodyDepth * (hypotenuseFourByOne * 4) );
			glutSolidCube(1.0);
		glPopMatrix();

		//Cannons rotate with the body
		botThree_drawCannons();

		//Bottom
	glPopMatrix();
}

void botThree_drawCannons()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, botThree_robotJoints_mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, botThree_robotJoints_mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, botThree_robotJoints_mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, botThree_robotJoints_mat_shininess);

	float studDiameter = botThree_cannonDiameter * 0.4;
	int studNum = 3;

	//Draw Left and Right Cannons
	for (int canNum = -1; canNum <= 1; canNum = canNum + 2)
	{
		glPushMatrix();
			//Translate whole cannon
			//glTranslatef(x, y, z)
			glTranslatef((0.5 * botThree_bodyWidth * canNum) + (0.5 * botThree_cannonDiameter * canNum), (0.5 * botThree_bodyHeight), -0.45 * botThree_bodyDepth);

			//Rotate whole left cannon
			//glRotate(angle, x, y, z)
			glRotatef(-botThree_cannonAngle * canNum, 0.0, 0.0, 1.0);

			//Sphere
			glPushMatrix();
				//glScalef(x, y, z);
				glScalef(botThree_cannonDiameter * 1.5, botThree_cannonDiameter * 1.5, botThree_cannonDiameter * 2.0);

				//gluSphere(quad, radius, slices, stacks)
				gluSphere(gluNewQuadric(), 0.5, 20, 20);
			glPopMatrix();//Sphere

			//Cylinder Inside
			//Done to prevent clipping with the body from showing
			glPushMatrix();
				//glTranslatef(x, y, z)
				glTranslatef(0.0, 0.0, 0.2 * botThree_bodyDepth);

				//glRotatef(angle, x, y, z)
				glRotatef(-90.0, 1.0, 0.0, 0.0);

				//glScalef(x, y, z)
				glScalef(botThree_cannonDiameter * 1.5, (botThree_bodyDepth * 0.9) - botThree_cannonDiameter, botThree_cannonDiameter * 1.5);

				//glRotatef(angle, x, y, z)
				glRotatef(90.0, 1.0, 0.0, 0.0);

				//gluCylinder(quad, base radius, top radius, height, slice, stacks)
				gluCylinder(gluNewQuadric(), 0.0, 0.35, 1.0, 20, 1);
			glPopMatrix();//Cylinder Inside

			//Cylinder Outside
			glPushMatrix();
				//glRotatef(angle, x, y, z)
				glRotatef(90.0, 1.0, 0.0, 0.0);

				//glScalef(x, y, z)
				glScalef(botThree_cannonDiameter * 1.5, botThree_bodyDepth * 0.9, botThree_cannonDiameter * 1.5);

				//glRotatef(angle, x, y, z)
				glRotatef(-90.0, 1.0, 0.0, 0.0);

				//gluCylinder(quad, base radius, top radius, height, slice, stacks)
				gluCylinder(gluNewQuadric(), 0.5, 0.35, 1.0, 20, 1);
			glPopMatrix();//Cylinder Outside

			//Disk
			glPushMatrix();
				//glTranslatef(x, y, z)
				glTranslatef(0.0, 0.0, botThree_bodyDepth * 0.9);

				//glScalef(x, y, z)
				glScalef(botThree_cannonDiameter, botThree_cannonDiameter, botThree_cannonDiameter);

				//gluDisk(quad, inner radius, outer radius, slices, loops)
				gluDisk(gluNewQuadric(), 0.4, 0.55, 20, 1);
			glPopMatrix();//Disk

			//Studs
			for (int deg = 0; deg < studNum; deg++)
			{
				glPushMatrix();
					//glRotatef(angle, x, y, z)
					glRotatef(deg * (360 / studNum), 0.0, 0.0, 1.0);

					//glTranslatef(x, y, z)
					glTranslatef(0.0, 0.5 * botThree_cannonDiameter, (botThree_bodyDepth * 0.9) - studDiameter);

					//glScalef(x, y, z)
					glScalef(studDiameter, studDiameter, studDiameter);

					//glRotatef(angle, x, y, z)
					glRotatef(-90.0, 1.0, 0.0, 0.0);

					//glutSolidCone(base radius, height, slices, stacks);
					glutSolidCone(0.5, 1.0, 10, 1);
				glPopMatrix();
			}
		
		glPopMatrix();
	}
}

void botThree_drawLeg(int leftHipAngle, int rightHipAngle, int leftKneeAngle, int rightKneeAngle)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, botThree_robotJoints_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, botThree_robotJoints_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, botThree_robotJoints_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, botThree_robotJoints_mat_shininess);

	for (int legNum = -1; legNum <= 1; legNum = legNum + 2)
	{
		int negZero = 1;
		int posZero = 1;
		if (legNum == 1) //Left Leg
			{ posZero = 0; }
		else             //Right Leg
			{ negZero = 0; }

		glPushMatrix();
			// Position whole leg with respect to body
			glTranslatef(
				(0.5 * botThree_bodyWidth* legNum) + (botThree_legDiameter * -0.5 * posZero), 
				(-0.5 * botThree_bodyHeight) + (0.5 * botThree_legDiameter), 
				(-0.5 * botThree_bodyDepth) + (0.5 * botThree_legDiameter)
			);
			
			//Rotate Hip Joint
			if (legNum == -1)
				{ glRotatef(rightHipAngle, 1.0, 0.0, 0.0);	}
			else if (legNum == 1)
				{ glRotatef(leftHipAngle, 1.0, 0.0, 0.0);	}


			// Hip Joint
			botThree_drawHipJoint(legNum);

			// Upper Leg
			glPushMatrix();
				// Position upper leg with respect to parent hip joint
				glTranslatef(botThree_legDiameter * 0.5 * negZero, 0.0, 0.0);

				//Draw Upper Leg
				botThree_drawUpperLeg();

				//Knee Joint
				glPushMatrix();
					// Position knee joint with respect to parent upper leg
					glTranslatef(0.0, -botThree_upperLegHeight, 0.0);

					//Draw Knee Joint
					botThree_drawKneeJoint(legNum);

					// Lower Leg
					glPushMatrix();
						// Position lower leg with respect to parent knee joint
						glTranslatef(
							botThree_legDiameter * 0.75 * legNum, 
							-botThree_lowerLegHeight, 
							(-0.5 * botThree_legDiameter * negZero) + (0.5 * botThree_legDiameter * negZero) 
						);

						//Rotate Knee Joint
						glTranslatef(0.05 * botThree_bodyDepth, botThree_lowerLegHeight, 0.0);
						if (legNum == -1)
							{ glRotatef(rightKneeAngle, 1.0, 0.0, 0.0); }
						else if (legNum == 1)
							{ glRotatef(leftKneeAngle, 1.0, 0.0, 0.0); }
						glTranslatef(-0.05 * botThree_bodyDepth, -botThree_lowerLegHeight, 0.0);

						//Draw Lower Leg
						botThree_drawLowerLeg();

						//Foot
						if (legNum == -1)
							{ botThree_drawFoot(legNum, rightHipAngle, rightKneeAngle); }
						else if (legNum == 1)
							{ botThree_drawFoot(legNum, leftHipAngle, leftKneeAngle); }

					glPopMatrix();//Lower Leg

				glPopMatrix();//Knee Joint

			glPopMatrix();//Upper Leg

		glPopMatrix();
	}
}

void botThree_drawHipJoint(int legNum)
{
	int negZero = 1;
	if (legNum == -1)
		{ negZero = 0; }

	// Hip Joint
	glPushMatrix();
		//Cylinder
		glPushMatrix();
			//glRotatef(angle, x, y, z)
			glRotatef(90.0, 0.0, 0.0, 1.0);

			//glScalef(x, y, z);
			glScalef(botThree_legDiameter, botThree_legDiameter * 0.5, botThree_legDiameter);

			//glRotatef(angle, x, y, z)
			glRotatef(90.0, 1.0, 0.0, 0.0);

			//gluCylinder(quad, base radius, top radius, height, slice, stacks)
			gluCylinder(gluNewQuadric(), 0.5, 0.5, 1.0, 20, 1);
		glPopMatrix();

		//Sphere
		glPushMatrix();
			// Position sphere with respect to parent hip joint
			glTranslatef(botThree_legDiameter * 0.5 * negZero, 0.0, 0.0);

			//glScalef(x, y, z);
			glScalef(botThree_legDiameter, botThree_legDiameter, botThree_legDiameter);

			//gluSphere(quad, radius, slices, stacks)
			gluSphere(gluNewQuadric(), 0.5, 20, 20);
		glPopMatrix();
	glPopMatrix();//Hip Joint
}

void botThree_drawUpperLeg()
{
	glPushMatrix();
		//glScalef(x, y, z);
		glScalef(botThree_legDiameter, botThree_upperLegHeight, botThree_legDiameter);

		//glRotatef(angle, x, y, z)
		glRotatef(90.0, 1.0, 0.0, 0.0);

		//gluCylinder(quad, base radius, top radius, height, slice, stacks)
		gluCylinder(gluNewQuadric(), 0.5, 0.5, 1.0, 20, 1);
	glPopMatrix();//Create Upper Leg
}

void botThree_drawKneeJoint(int legNum)
{
	int posZero = 1;
	if (legNum == 1)
		{ posZero = 0; }

	//Create Knee Joint
	glPushMatrix();
		//Back Sphere
		glPushMatrix();
			//glScalef(x, y, z);
			glScalef(botThree_legDiameter, botThree_legDiameter, botThree_legDiameter);

			//gluSphere(quad, radius, slices, stacks)
			gluSphere(gluNewQuadric(), 0.5, 20, 20);
		glPopMatrix();//Back Sphere

		glMaterialfv(GL_FRONT, GL_AMBIENT, botThree_robotLeg_mat_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, botThree_robotLeg_mat_specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, botThree_robotLeg_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SHININESS, botThree_robotLeg_mat_shininess);

		//Cylinder
		glPushMatrix();
			// Position back sphere with respect to parent upper leg
			glTranslatef(-botThree_legDiameter * posZero, 0.0, 0.0);

			//glRotatef(angle, x, y, z)
			glRotatef(90.0, 0.0, 0.0, 1.0);

			//glScalef(x, y, z);
			glScalef(botThree_legDiameter, botThree_legDiameter, botThree_legDiameter);

			//glRotatef(angle, x, y, z)
			glRotatef(90.0, 1.0, 0.0, 0.0);

			//gluCylinder(quad, base radius, top radius, height, slice, stacks)
			gluCylinder(gluNewQuadric(), 0.5, 0.5, 1.0, 20, 1);
		glPopMatrix();//Cylinder

		//Front Sphere
		glPushMatrix();
			// Position back sphere with respect to parent upper leg
			glTranslatef(botThree_legDiameter * legNum, 0.0, 0.0);

			//glScalef(x, y, z);
			glScalef(botThree_legDiameter, botThree_legDiameter, botThree_legDiameter);

			//gluSphere(quad, radius, slices, stacks)
			gluSphere(gluNewQuadric(), 0.5, 20, 20);
		glPopMatrix();//Front Sphere

	glPopMatrix(); //Create Knee Joint
}

void botThree_drawLowerLeg()
{
	//Create Lower Leg
	glPushMatrix();

		//Cylinder
		glPushMatrix();
			//glScalef(x, y, z);
			glScalef(botThree_legDiameter * 1.5, botThree_lowerLegHeight, botThree_legDiameter);

			//glRotatef(angle, x, y, z)
			glRotatef(-90.0, 1.0, 0.0, 0.0);

			//gluCylinder(quad, base radius, top radius, height, slice, stacks)
			gluCylinder(gluNewQuadric(), 1.0, 0.5, 1.0, 20, 1);
		glPopMatrix();

		//Disk
		glPushMatrix();
			//glScalef(x, y, z)
			glScalef(botThree_legDiameter * 1.5, botThree_lowerLegHeight, botThree_legDiameter);

			//glRotatef(angle, x, y, z)
			glRotatef(90.0, 1.0, 0.0, 0.0);

			//gluDisk(quad, inner radius, outer radius, slices, loops)
			gluDisk(gluNewQuadric(), 0.0, 1.0, 20, 1);
		glPopMatrix();

	glPopMatrix();//Create Lower Leg
}

void botThree_drawFoot(int legNum, int hipAngle, int kneeAngle)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, botThree_robotJoints_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, botThree_robotJoints_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, botThree_robotJoints_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, botThree_robotJoints_mat_shininess);

	//Foot
	glPushMatrix();
		// Position foot with respect to parent lower leg
		glTranslatef(0.0, botThree_legDiameter * -0.5, 0.0);

		//Get Foot Angle
		float footAngle = hipAngle + kneeAngle;
		while (footAngle > 360)
			{ footAngle -= 360; }
			
		//Unrotate Foot Angle if clip
		if (footAngle > 180)
			{ glRotatef(-footAngle, 1.0, 0.0, 0.0); }	

		//Ball of foot
		glPushMatrix();
			//glScalef(x, y, z);
			glScalef(botThree_legDiameter * 2, botThree_legDiameter * 1.6, botThree_legDiameter * 2);

			//gluSphere(quad, radius, slices, stacks)
			gluSphere(gluNewQuadric(), 0.5, 20, 20);
		glPopMatrix();//Ball of foot

		//Right Toe
		glPushMatrix();
			//Rotate whole toe
			glRotatef(-50.0, 0.0, 1.0, 0.0);

			//Translate whole toe
			glTranslatef(botThree_legDiameter * -0.25, 0.0, botThree_legDiameter * -0.5);

			//Right Toe Cylinder
			glPushMatrix();
				glTranslatef(0.0, 0.0, botThree_legDiameter * 0.5);

				//glRotatef(angle, x, y, z)
				glRotatef(-90.0, 0.0, 1.0, 0.0);
				glRotatef(90.0, 0.0, 0.0, 1.0);

				//glScalef(x, y, z);
				glScalef(botThree_legDiameter, botThree_legDiameter * 1.5, botThree_legDiameter);

				//glRotatef(angle, x, y, z)
				glRotatef(90.0, 1.0, 0.0, 0.0);

				//gluCylinder(quad, base radius, top radius, height, slice, stacks)
				gluCylinder(gluNewQuadric(), 0.7, 0.25, 1.0, 20, 1);
			glPopMatrix();//Right Toe Cylinder

			//Right Toe Sphere
			glPushMatrix();
				glTranslatef(0.0, 0.0, botThree_legDiameter * 1.95);

				//glScalef(x, y, z);
				glScalef(botThree_legDiameter * 0.5, botThree_legDiameter * 0.5, botThree_legDiameter * 0.5);

				//gluSphere(quad, radius, slices, stacks)
				gluSphere(gluNewQuadric(), 0.5, 20, 20);
			glPopMatrix();//Right Toe Sphere

		glPopMatrix();//Right Toe

		//Middle Toe Cylinder
		glPushMatrix();
			glTranslatef(0.0, 0.0, botThree_legDiameter * 0.5);

			//glRotatef(angle, x, y, z)
			glRotatef(-90.0, 0.0, 1.0, 0.0);
			glRotatef(90.0, 0.0, 0.0, 1.0);

			//glScalef(x, y, z);
			glScalef(botThree_legDiameter, botThree_legDiameter * 1.5, botThree_legDiameter);

			//glRotatef(angle, x, y, z)
			glRotatef(90.0, 1.0, 0.0, 0.0);

			//gluCylinder(quad, base radius, top radius, height, slice, stacks)
			gluCylinder(gluNewQuadric(), 0.7, 0.25, 1.0, 20, 1);
		glPopMatrix();//Middle Toe Cylinder

		//Middle Toe Sphere
		glPushMatrix();
			glTranslatef(0.0, 0.0, botThree_legDiameter * 1.95);

			//glScalef(x, y, z);
			glScalef(botThree_legDiameter * 0.5, botThree_legDiameter * 0.5, botThree_legDiameter * 0.5);

			//gluSphere(quad, radius, slices, stacks)
			gluSphere(gluNewQuadric(), 0.5, 20, 20);
		glPopMatrix();//Middle Toe Sphere

		//Left Toe
		glPushMatrix();
			//Rotate whole toe
			glRotatef(50.0, 0.0, 1.0, 0.0);

			//Translate whole toe
			glTranslatef(botThree_legDiameter * 0.25, 0.0, botThree_legDiameter * -0.5);

			//Left Toe Cylinder
			glPushMatrix();
				glTranslatef(0.0, 0.0, botThree_legDiameter * 0.5);

				//glRotatef(angle, x, y, z)
				glRotatef(-90.0, 0.0, 1.0, 0.0);
				glRotatef(90.0, 0.0, 0.0, 1.0);

				//glScalef(x, y, z);
				glScalef(botThree_legDiameter, botThree_legDiameter * 1.5, botThree_legDiameter);

				//glRotatef(angle, x, y, z)
				glRotatef(90.0, 1.0, 0.0, 0.0);

				//gluCylinder(quad, base radius, top radius, height, slice, stacks)
				gluCylinder(gluNewQuadric(), 0.7, 0.25, 1.0, 20, 1);
			glPopMatrix();//Left Toe Cylinder

			//Left Toe Sphere
			glPushMatrix();
				glTranslatef(0.0, 0.0, botThree_legDiameter * 1.95);

				//glScalef(x, y, z);
				glScalef(botThree_legDiameter * 0.5, botThree_legDiameter * 0.5, botThree_legDiameter * 0.5);

				//gluSphere(quad, radius, slices, stacks)
				gluSphere(gluNewQuadric(), 0.5, 20, 20);
			glPopMatrix();//Left Toe Sphere

		glPopMatrix();//Left Toe

	glPopMatrix();//Foot
}

// -----------------
// --- Animation ---
// -----------------

void botThree_cannonAnimationHandler(int param)
{
	//Cannon
	if (botThree_cannonRotation)
	{
		botThree_cannonAngle += rotateSpeed;
		if (botThree_cannonAngle >= 360)
		{
			botThree_cannonAngle -= 360.0;
		}
		glutPostRedisplay();
		glutTimerFunc(10, botThree_cannonAnimationHandler, 0);
	}
}

void botThree_walkAnimationHandler(int param)
{
	//Walk
	if (botThree_walkCycle)
	{
		int arrLen = (int)(sizeof(botThree_walkArr) / sizeof(botThree_walkArr[0]));

		// BotThree: One
		if (botThreeOne_active)
		{
			// Right Leg
			botThreeOne_rightHipAngle = botThree_walkArr[botThreeOne_rightWalkIndex][0];
			botThreeOne_rightKneeAngle = botThree_walkArr[botThreeOne_rightWalkIndex][1];
			botThreeOne_rightWalkIndex++;

			if (botThreeOne_rightWalkIndex >= arrLen)
				{ botThreeOne_rightWalkIndex = 0; }

			// Left Leg
			botThreeOne_leftHipAngle = botThree_walkArr[botThreeOne_leftWalkIndex][0];
			botThreeOne_leftKneeAngle = botThree_walkArr[botThreeOne_leftWalkIndex][1];
			botThreeOne_leftWalkIndex++;

			if (botThreeOne_leftWalkIndex >= arrLen)
				{ botThreeOne_leftWalkIndex = 0; }
		}
		else
		{
			botThreeOne_rightHipAngle = 45.0;
			botThreeOne_leftHipAngle = 45.0;
			botThreeOne_rightKneeAngle = 270.0;
			botThreeOne_leftKneeAngle = 270.0;
		}

		// BotThree: Two
		if (botThreeTwo_active)
		{
			// Right Leg
			botThreeTwo_rightHipAngle = botThree_walkArr[botThreeTwo_rightWalkIndex][0];
			botThreeTwo_rightKneeAngle = botThree_walkArr[botThreeTwo_rightWalkIndex][1];
			botThreeTwo_rightWalkIndex++;

			if (botThreeTwo_rightWalkIndex >= arrLen)
				{ botThreeTwo_rightWalkIndex = 0; }

			// Left Leg
			botThreeTwo_leftHipAngle = botThree_walkArr[botThreeTwo_leftWalkIndex][0];
			botThreeTwo_leftKneeAngle = botThree_walkArr[botThreeTwo_leftWalkIndex][1];
			botThreeTwo_leftWalkIndex++;

			if (botThreeTwo_leftWalkIndex >= arrLen)
				{ botThreeTwo_leftWalkIndex = 0; }
		}
		else
		{
			botThreeTwo_rightHipAngle = 45.0;
			botThreeTwo_leftHipAngle = 45.0;
			botThreeTwo_rightKneeAngle = 270.0;
			botThreeTwo_leftKneeAngle = 270.0;
		}

		// Both not active
		if ((!botThreeOne_active) && (!botThreeTwo_active))
			{ botThree_walkCycle = false; }
		else
		{
			glutPostRedisplay();
			glutTimerFunc(10, botThree_walkAnimationHandler, 0);
		}
			
	}
}

void botThree_collapseAnimationHandler(int param)
{
	if (botThree_collapseOngoing)
	{
		bool done = true;
		float yCollapseSpeed = -0.07;
		float yEnd = -14;
		float hipEnd = 75;
		float kneeEnd = 210;

		// BotThree: One
		if (!botThreeOne_active)
		{
			// Y
			if (botThreeOne_Y > yEnd)
				{ botThreeOne_Y += yCollapseSpeed; done = false; }

			// Hip
			if (botThreeOne_leftHipAngle > hipEnd)
				{ botThreeOne_leftHipAngle--; done = false; }
			else if (botThreeOne_leftHipAngle < hipEnd)
				{ botThreeOne_leftHipAngle++; done = false; }

			if (botThreeOne_rightHipAngle > hipEnd)
				{ botThreeOne_rightHipAngle--; done = false; }
			else if (botThreeOne_rightHipAngle < hipEnd)
				{ botThreeOne_rightHipAngle++; done = false; }

			// Knee
			if (botThreeOne_leftKneeAngle > kneeEnd)
				{ botThreeOne_leftKneeAngle--; done = false; }
			else if (botThreeOne_leftKneeAngle < kneeEnd)
				{ botThreeOne_leftKneeAngle++; done = false; }

			if (botThreeOne_rightKneeAngle > kneeEnd)
				{ botThreeOne_rightKneeAngle--; done = false; }
			else if (botThreeOne_rightKneeAngle < kneeEnd)
				{ botThreeOne_rightKneeAngle++; done = false; }
		}

		// BotThree: Two
		if (!botThreeTwo_active)
		{
			// Y
			if (botThreeTwo_Y > yEnd)
				{ botThreeTwo_Y += yCollapseSpeed; done = false; }

			// Hip
			if (botThreeTwo_leftHipAngle > hipEnd)
				{ botThreeTwo_leftHipAngle--; done = false; }
			else if (botThreeTwo_leftHipAngle < hipEnd)
				{ botThreeTwo_leftHipAngle++; done = false; }

			if (botThreeTwo_rightHipAngle > hipEnd)
				{ botThreeTwo_rightHipAngle--; done = false; }
			else if (botThreeTwo_rightHipAngle < hipEnd)
				{ botThreeTwo_rightHipAngle++; done = false; }

			// Knee
			if (botThreeTwo_leftKneeAngle > kneeEnd)
				{ botThreeTwo_leftKneeAngle--; done = false; }
			else if (botThreeTwo_leftKneeAngle < kneeEnd)
				{ botThreeTwo_leftKneeAngle++; done = false; }

			if (botThreeTwo_rightKneeAngle > kneeEnd)
				{ botThreeTwo_rightKneeAngle--; done = false; }
			else if (botThreeTwo_rightKneeAngle < kneeEnd)
				{ botThreeTwo_rightKneeAngle++; done = false; }
		}

		updateCollisionBoxes();
		glutPostRedisplay();

		//If not all at end of line, continue
		if (!done)
			{ glutTimerFunc(10, botThree_collapseAnimationHandler, 0); }
		else
			{ botThree_collapseOngoing = false; }
	}
}

// -----------------
// --- Functions ---
// -----------------

void collapseBotThree(int botNum)
{
	switch (botNum)
	{
	case 1:
		botThreeOne_active = false;
		break;
	case 2:
		botThreeTwo_active = false;
		break;
	}

	if (!botThree_collapseOngoing)
	{
		botThree_collapseOngoing = true;
		glutTimerFunc(10, botThree_collapseAnimationHandler, 0);
	}
}

#pragma once