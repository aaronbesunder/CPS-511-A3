#pragma once

#include <GL/freeglut.h>

#include "Bot.h"

// -----------------
// --- Variables ---
// -----------------

// Dimensions
float gunScale = 1.0;

// Control Robot body rotation on base and gun rotation
float botFourOne_robotAngle = 0.0;
float botFourTwo_robotAngle = 0.0;
float botFour_bodyAngle = 0.0;
float botFourOne_bodyHeight = 0.0;
float botFourTwo_bodyHeight = 0.0;
float botFour_gunAngle = -90.0;

// Control leg rotation
float botFour_leftHipAngle = 0.0;
float botFour_leftLegBack = -60;
float botFour_leftleginit = 8.0;
float botFour_rightleginit = 8.0;
float botFour_leftKneeAngle = 0.0;
float botFour_leftFootAngle = 0.0;
float botFour_rightHipAngle = 0.0;
float botFour_rightLegBack = -60;
float botFour_rightKneeAngle = 0.0;
float botFour_rightFootAngle = 0.0;

// Animation
bool botFour_start = false;
bool botFour_stop = false;
bool botFourR_stop = false;
bool botFour_reverse = false;
bool botFour_firstcheck = false;
bool botFour_stopmovingupper = false;
bool botFour_gunStop = false;
bool botFour_walkcheck = false;
bool botFour_collapseOngoing = false;

// Functions
void botFour_animateUpperLegUp();
void botFour_animateLowerLegUp();
void botFour_animateUpperLegDown();
void botFour_animateLowerLegDown();
void botFour_animateUpperRightLegUp();
void botFour_animateLowerRightLegUp();
void botFour_animateUpperRightLegDown();
void botFour_animateLowerRightLegDown();
void botFour_gunHandler(int param);
void botFour_takeStep();
void botFour_takeRightStep();
void botFour_drawRobot(int botnum);
void botFour_drawBody(int botnum);
void botFour_drawLeftLeg(int botnum);
void botFour_drawRightLeg(int botnum);
void botFour_collapseAnimationHandler(int);

// Lighting/shading and material properties for robot
GLfloat botFour_robotBody_mat_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
GLfloat botFour_robotBody_mat_specular[] = { 0.45f,0.55f,0.45f,1.0f };
GLfloat botFour_robotBody_mat_diffuse[] = { 0.1f,0.35f,0.1f,1.0f };
GLfloat botFour_robotBody_mat_shininess[] = { 32.0F };

GLfloat botFour_robotleg_mat_ambient[] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
GLfloat botFour_robotleg_mat_diffuse[] = { 0.5f,0.0f,0.0f,1.0f };
GLfloat botFour_robotleg_mat_specular[] = { 0.7f, 0.6f, 0.6f, 1.0f };
GLfloat botFour_robotleg_mat_shininess[] = { 32.0F };

GLfloat botFour_gun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat botFour_gun_mat_diffuse[] = { 0.01f,0.0f,0.01f,0.01f };
GLfloat botFour_gun_mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat botFour_gun_mat_shininess[] = { 100.0F };

GLfloat botFour_robotLegs_mat_ambient[] = { 0.25f, 0.25f, 0.25f, 1.0f };
GLfloat botFour_robotLegs_mat_diffuse[] = { 0.4f, 0.4f, 0.4f, 1.0f };
GLfloat botFour_robotLegs_mat_specular[] = { 0.774597f, 0.774597f, 0.774597f, 1.0f };
GLfloat botFour_robotLegs_mat_shininess[] = { 76.8F }; 

// BotFour
GLfloat botFour_startingY = -4;

// BotFour: One
bool botFourOne_active = true;

GLfloat botFourOne_X = -30;
GLfloat botFourOne_Y = botFour_startingY;

float botFourOne_bodyWidth = 4.5;
float botFourOne_bodyLength = 5.5;
float botFourOne_bodyDepth = 7.0;
float botFourOne_upperLegLength = 0.95 * botFourOne_bodyLength;
float botFourOne_upperLegWidth = 0.125 * botFourOne_bodyWidth;
float botFourOne_lowerLegLength = botFourOne_upperLegLength;
float botFourOne_lowerLegWidth = botFourOne_upperLegWidth;
float botFourOne_footLength = botFourOne_lowerLegLength / 3.0;
float botFourOne_ballJointLength = botFourOne_lowerLegLength / 5.0;
float botFourOne_footWidth = 2.0 * botFourOne_lowerLegWidth;
float botFourOne_bar = 1.6 * botFourOne_bodyWidth;
float botFourOne_footDepth = 2.0 * botFourOne_lowerLegWidth;

// BotFour: Two
bool botFourTwo_active = true;

GLfloat botFourTwo_X = 10;
GLfloat botFourTwo_Y = botFour_startingY;

float botFourTwo_bodyWidth = 4.5;
float botFourTwo_bodyLength = 5.5;
float botFourTwo_bodyDepth = 7.0;
float botFourTwo_upperLegLength = 0.95 * botFourTwo_bodyLength;
float botFourTwo_upperLegWidth = 0.125 * botFourTwo_bodyWidth;
float botFourTwo_lowerLegLength = botFourTwo_upperLegLength;
float botFourTwo_lowerLegWidth = botFourTwo_upperLegWidth;
float botFourTwo_footLength = botFourTwo_lowerLegLength / 3.0;
float botFourTwo_ballJointLength = botFourTwo_lowerLegLength / 5.0;
float botFourTwo_footWidth = 2.0 * botFourTwo_lowerLegWidth;
float botFourTwo_bar = 1.6 * botFourTwo_bodyWidth;
float botFourTwo_footDepth = 2.0 * botFourTwo_lowerLegWidth;

// ------------
// --- Draw ---
// ------------

void botFour_drawRobot(int botnum)
{
	float botFour_robotAngle;
		if (botnum == 1) {
			botFour_robotAngle = botFourOne_robotAngle;
	}
		else if (botnum == 2) {
		botFour_robotAngle = botFourTwo_robotAngle;
	}
	glPushMatrix();
	 // spin robot on base. 
	 glRotatef(botFour_robotAngle, 0.0, 1.0, 0.0);
	 if (botnum == 1) {
		 botFour_drawBody(1);
		 botFour_drawLeftLeg(1);
		 botFour_drawRightLeg(1);
	 }
	 else if (botnum == 2) {
		 botFour_drawBody(2);
		 botFour_drawLeftLeg(2);
		 botFour_drawRightLeg(2);
	 }
	glPopMatrix();
}


void botFour_drawBody(int botnum)
{
	float botFour_bodyWidth;
	float botFour_bodyLength;
	float botFour_bodyDepth;
	float botFour_bar;

	if (botnum == 1) {
		botFour_bodyWidth=botFourOne_bodyWidth;
		botFour_bodyLength=botFourOne_bodyLength;
		botFour_bodyDepth=botFourOne_bodyDepth;
		botFour_bar = botFourOne_bar;
	}
	else if (botnum == 2) {
		botFour_bodyWidth = botFourTwo_bodyWidth;
		botFour_bodyLength = botFourTwo_bodyLength;
		botFour_bodyDepth = botFourTwo_bodyDepth;
		botFour_bar = botFourTwo_bar;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, botFour_robotBody_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, botFour_robotBody_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, botFour_robotBody_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, botFour_robotBody_mat_shininess);

	//draw main body that can rotate along y axis
	glPushMatrix();
	glRotatef(botFour_bodyAngle, 0, 1.0, 0);

	glPushMatrix();
	glScalef(botFour_bodyWidth, botFour_bodyLength, botFour_bodyDepth);
	glutSolidCube(1.0);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, botFour_robotLegs_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, botFour_robotLegs_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, botFour_robotLegs_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, botFour_robotLegs_mat_shininess);

	//draw gun that can rotate
	GLUquadricObj* myquadric;
	myquadric = gluNewQuadric();
	glPushMatrix();
	glRotatef(botFour_gunAngle, 0, 0, 1.0);
	glScalef(gunScale, gunScale, gunScale);
	glPushMatrix();
	gluCylinder(myquadric, 1, 1, 5, 6, 60);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0,0, 5);
	gluDisk(myquadric, 0, 1, 6, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 5);
	gluCylinder(myquadric, 0.5, 0.5, 0.5, 6, 60);
	glPopMatrix();

	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, botFour_gun_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, botFour_gun_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, botFour_gun_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, botFour_gun_mat_shininess);
	//second part of the gun
	glPushMatrix();
	glRotatef(botFour_gunAngle, 0, 0, 1.0);
	glScalef(gunScale, gunScale, gunScale);
	glTranslatef(0, 0, 0.7);
	glPushMatrix();
	glScalef(gunScale, gunScale, gunScale);
	gluCylinder(myquadric, 0.2, 0.2, 5, 8, 60);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 5);
	gluDisk(myquadric, 0, 0.2, 8, 50);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//leg/hip bar for the robot
	glPushMatrix();
	glScalef(botFour_bar, 1, 1);
	glTranslatef(0, -0.55 * botFour_bodyLength, 2);
	glutSolidCube(1.0);
	glPopMatrix();
}

void botFour_drawLeftLeg(int botnum)
{
	float botFour_bodyWidth;
	float botFour_upperLegWidth;
	float botFour_upperLegLength;
	float botFour_ballJointLength;

	if (botnum == 1) {
		botFour_bodyWidth = botFourOne_bodyWidth;
		botFour_upperLegLength = botFourOne_upperLegLength;
		botFour_upperLegWidth = botFourOne_upperLegWidth;
		botFour_ballJointLength = botFourOne_ballJointLength;
	}
	else if (botnum == 2) {
		botFour_bodyWidth = botFourTwo_bodyWidth;
		botFour_upperLegLength = botFourTwo_upperLegLength;
		botFour_upperLegWidth = botFourTwo_upperLegWidth;
		botFour_ballJointLength = botFourTwo_ballJointLength;
		
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, botFour_robotleg_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, botFour_robotleg_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, botFour_robotleg_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, botFour_robotleg_mat_shininess);

	//first ball joint
	glPushMatrix();
	glTranslatef((0.7 * botFour_bodyWidth + 0.7 * botFour_upperLegWidth), -0.65 * botFour_upperLegLength, 2.0);
	glScalef(botFour_upperLegWidth, botFour_ballJointLength, botFour_upperLegWidth);
	glRotatef(botFour_leftHipAngle, 1.0, 0.0, 0);
	glTranslatef(-(0.7 * botFour_bodyWidth + 0.7 * botFour_upperLegWidth), 0.65 * botFour_upperLegLength, -2.0);
	glTranslatef((0.7 * botFour_bodyWidth + 0.7 * botFour_upperLegWidth), -0.65 * botFour_upperLegLength, 2.0);
	glPushMatrix();

	glutSolidSphere(1.25, 50, 50);
	glPopMatrix();

	//upper leg
	glPushMatrix();
	glTranslatef(-(0.5 * botFour_bodyWidth + 0.5 * botFour_upperLegWidth), 0.5 * botFour_upperLegLength, 0.0);
	glTranslatef(-(0.5 * botFour_bodyWidth + 0.5 * botFour_upperLegWidth), 0.5 * botFour_upperLegLength, 0.0);
	// Position leg with respect to parent body
	glTranslatef((1* botFour_bodyWidth + 1 * botFour_upperLegWidth), -7.5, 0); // this will be done last
	
	// build upper leg
	glPushMatrix();
	glScalef(botFour_upperLegWidth, botFour_upperLegLength, botFour_upperLegWidth);
	glutSolidCube(1.0);
	glPopMatrix();

	// Position ball joint with respect to upper leg
	glTranslatef(0, -2.5, 0);

	// build ball joint
	glPushMatrix();
	glutSolidSphere(0.6, 50, 50);
	glPopMatrix();

	//glTranslatef(-(0.5 * botFour_bodyWidth + 0.5 * botFour_upperLegWidth), 0.5 * botFour_upperLegLength, 0.0);
	glRotatef(botFour_leftKneeAngle, 1.0, 0.0, 0.0);
	glRotatef(19.0, -1.0, 0.0, 0.0);
	//glTranslatef((0.5 * botFour_bodyWidth + 0.5 * botFour_upperLegWidth), -0.5 * botFour_upperLegLength, 0.0);

	//position lower leg wrt ball joint
	glTranslatef(0, -2.5 * botFour_ballJointLength, 0);
	
	glPushMatrix();
	glScalef(botFour_upperLegWidth, botFour_upperLegLength, botFour_upperLegWidth);
	glutSolidCube(1.0);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, botFour_robotleg_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, botFour_robotleg_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, botFour_robotleg_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, botFour_robotleg_mat_shininess);

	// Position ball joint with respect to upper leg
	glTranslatef(0, -2.5, 0); // this will be done last

	// build ball joint
	glPushMatrix();
	glutSolidSphere(0.6, 50, 50);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, botFour_robotleg_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, botFour_robotleg_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, botFour_robotleg_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, botFour_robotleg_mat_shininess);

	//glRotatef(botFour_leftFootAngle, 1.0, 0.0, 0.0);
	//Get Foot Angle
	float footAngle = botFour_leftHipAngle + botFour_leftKneeAngle;
	while (footAngle > 360)
		{ footAngle -= 360; }

	//Unrotate Foot Angle if clip
	if ((footAngle > 200) || (footAngle < 20))
		{ glRotatef(-footAngle + 20, 1.0, 0.0, 0.0); }

	glTranslatef(0, -1.5, 0);

	glPushMatrix();
	glScalef(2.0, 2.0, 5.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}
void botFour_drawRightLeg(int botnum)
{
	float botFour_bodyWidth;
	float botFour_upperLegWidth;
	float botFour_upperLegLength;
	float botFour_ballJointLength;

	if (botnum == 1) {
		botFour_bodyWidth = botFourOne_bodyWidth;
		botFour_upperLegLength = botFourOne_upperLegLength;
		botFour_upperLegWidth = botFourOne_upperLegWidth;
		botFour_ballJointLength = botFourOne_ballJointLength;
	}
	else if (botnum == 2) {
		botFour_bodyWidth = botFourTwo_bodyWidth;
		botFour_upperLegLength = botFourTwo_upperLegLength;
		botFour_upperLegWidth = botFourTwo_upperLegWidth;
		botFour_ballJointLength = botFourTwo_ballJointLength;

	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, botFour_robotleg_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, botFour_robotleg_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, botFour_robotleg_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, botFour_robotleg_mat_shininess);

	//first ball joint
	glPushMatrix();
	glTranslatef(-(0.7 * botFour_bodyWidth + 0.7 * botFour_upperLegWidth), -0.65 * botFour_upperLegLength, 2.0);
	glScalef(botFour_upperLegWidth, botFour_ballJointLength, botFour_upperLegWidth);
	glRotatef(botFour_rightHipAngle, 1.0, 0.0, 0);
	glTranslatef((0.7 * botFour_bodyWidth + 0.7 * botFour_upperLegWidth), 0.65 * botFour_upperLegLength, -2.0);
	glTranslatef(-(0.7 * botFour_bodyWidth + 0.7 * botFour_upperLegWidth), -0.65 * botFour_upperLegLength, 2.0);
	glPushMatrix();

	glutSolidSphere(1.25, 50, 50);
	glPopMatrix();

	//upper leg
	glPushMatrix();
	glTranslatef(-(0.5 * botFour_bodyWidth + 0.5 * botFour_upperLegWidth), 0.5 * botFour_upperLegLength, 0.0);
	glTranslatef(-(0.5 * botFour_bodyWidth + 0.5 * botFour_upperLegWidth), 0.5 * botFour_upperLegLength, 0.0);
	// Position leg with respect to parent body
	glTranslatef((1 * botFour_bodyWidth + 1 * botFour_upperLegWidth), -7.5, 0); // this will be done last



	// build upper leg
	glPushMatrix();
	glScalef(botFour_upperLegWidth, botFour_upperLegLength, botFour_upperLegWidth);
	glutSolidCube(1.0);
	glPopMatrix();



	// Position ball joint with respect to upper leg
	glTranslatef(0, -2.5, 0);

	// build ball joint
	glPushMatrix();
	glutSolidSphere(0.6, 50, 50);
	glPopMatrix();


	//glTranslatef(-(0.5 * botFour_bodyWidth + 0.5 * botFour_upperLegWidth), 0.5 * botFour_upperLegLength, 0.0);
	glRotatef(botFour_rightKneeAngle, 1.0, 0.0, 0.0);
	glRotatef(19.0, -1.0, 0.0, 0.0);
	//glTranslatef((0.5 * botFour_bodyWidth + 0.5 * botFour_upperLegWidth), -0.5 * botFour_upperLegLength, 0.0);

	//position lower leg wrt ball joint
	glTranslatef(0, -2.5 * botFour_ballJointLength, 0);

	glPushMatrix();
	glScalef(botFour_upperLegWidth, botFour_upperLegLength, botFour_upperLegWidth);
	glutSolidCube(1.0);
	glPopMatrix();


	glMaterialfv(GL_FRONT, GL_AMBIENT, botFour_robotleg_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, botFour_robotleg_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, botFour_robotleg_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, botFour_robotleg_mat_shininess);

	// Position ball joint with respect to upper leg
	glTranslatef(0, -2.5, 0); // this will be done last

	// build ball joint
	glPushMatrix();
	glutSolidSphere(0.6, 50, 50);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, botFour_robotleg_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, botFour_robotleg_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, botFour_robotleg_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, botFour_robotleg_mat_shininess);

	//glRotatef(botFour_rightFootAngle, 1.0, 0.0, 0.0);
	//Get Foot Angle
	float footAngle = botFour_rightHipAngle + botFour_rightKneeAngle;
	while (footAngle > 360)
		{ footAngle -= 360; }
	//Unrotate Foot Angle if clip
	if ((footAngle > 200) || (footAngle < 20))
		{ glRotatef(-footAngle + 20, 1.0, 0.0, 0.0); }

	glTranslatef(0, -1.5, 0);

	glPushMatrix();
	glScalef(2.0, 2.0, 5.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

}

// -----------------
// --- Animation ---
// -----------------

//move upper leg up
void botFour_animateUpperLegUp()
{
	if (!botFour_stop)
	{
		if (botFour_leftHipAngle > -60) {
			botFour_leftHipAngle -= 0.9;
			//printf("%lf\n", botFour_leftHipAngle);
			glutPostRedisplay();
		}
	}
}
void botFour_animateUpperRightLegUp()
{
	if (!botFourR_stop)
	{
		if (botFour_rightHipAngle > -60) {
			botFour_rightHipAngle -= 0.9;
			//printf("%lf\n", botFour_leftHipAngle);
			glutPostRedisplay();
		}
	}
}
// move lower leg up
void botFour_animateLowerLegUp()
{
	if (!botFour_stop)
	{
		if (botFour_leftKneeAngle <60) {
			botFour_leftKneeAngle += 0.9;
			//printf("%lf\n", (botFour_leftKneeAngle+botFour_leftleginit));
			glutPostRedisplay();
			botFour_reverse = true;
			botFour_stopmovingupper = true;
		}
	}
}
void botFour_animateLowerRightLegUp()
{
	if (!botFourR_stop)
	{
		if (botFour_rightKneeAngle < 60) {
			botFour_rightKneeAngle += 0.9;
			//printf("%lf\n", (botFour_leftKneeAngle+botFour_leftleginit));
			glutPostRedisplay();
			botFour_reverse = true;
			botFour_stopmovingupper = true;
		}
	}
}

//move upper leg down
void botFour_animateUpperLegDown()
{
	if (!botFour_stop)
	{
		if (botFour_reverse==true && botFour_leftHipAngle<=0) {
			botFour_leftHipAngle += 0.9;
			//printf("%lf\n", botFour_leftHipAngle);
			glutPostRedisplay();
			botFour_firstcheck = true;
		}
	}
}
void botFour_animateUpperRightLegDown()
{
	if (!botFourR_stop)
	{
		if (botFour_reverse == true && botFour_rightHipAngle <= 0) {
			botFour_rightHipAngle += 0.9;
			//printf("%lf\n", botFour_leftHipAngle);
			glutPostRedisplay();
			botFour_firstcheck = true;
		}
	}
}
//move lower leg down
void botFour_animateLowerLegDown()
{
	if (!botFour_stop)
	{
		if (botFour_reverse == true && botFour_leftKneeAngle >= (botFour_leftleginit)) {
			botFour_leftKneeAngle -= 0.9;
			//printf("%lf\n", botFour_leftKneeAngle);
			glutPostRedisplay();
		}
	}
}
void botFour_animateLowerRightLegDown()
{
	if (!botFourR_stop)
	{
		if (botFour_reverse == true && botFour_rightKneeAngle >= (botFour_rightleginit)) {
			botFour_rightKneeAngle -= 0.9;
			//printf("%lf\n", botFour_leftKneeAngle);
			glutPostRedisplay();
		}
	}
}

//rotate gun
void botFour_gunHandler(int param) {
	if (!botFour_gunStop) {
		botFour_gunAngle += 5;
		glutPostRedisplay();
		glutTimerFunc(10, botFour_gunHandler, 0);
	}
}

//cases for the robot to call in order to animate taking a step
void botFour_takeStep() {
	if (botFour_walkcheck)
	{
		if (botFour_start == false) {
			botFour_leftHipAngle = 0;
			botFour_leftKneeAngle = botFour_leftleginit;
			botFour_start = true;
			botFour_stopmovingupper = false;
		}
		else if (botFour_leftHipAngle >= -60 && botFour_leftKneeAngle < 60 && botFour_stopmovingupper == false) {
			botFour_animateUpperLegUp();
		}
		else if (botFour_leftHipAngle < -60 && botFour_leftKneeAngle < 60) {
			botFour_animateLowerLegUp();
		}
		else if (botFour_reverse == true && botFour_leftHipAngle <= 0) {
			botFour_animateUpperLegDown();
		}
		else if (botFour_reverse == true && botFour_firstcheck == true && botFour_leftKneeAngle >= botFour_leftleginit) {
			botFour_animateLowerLegDown();
			botFour_start = false;
			glutIdleFunc(botFour_takeRightStep);
		}
	}
}
void botFour_takeRightStep() {
	if (botFour_walkcheck)
	{
		if (botFour_start == false) {
			botFour_rightHipAngle = 0;
			botFour_rightKneeAngle = botFour_rightleginit;
			botFour_start = true;
			botFour_stopmovingupper = false;
		}
		else if (botFour_rightHipAngle >= -60 && botFour_rightKneeAngle < 60 && botFour_stopmovingupper == false) {
			botFour_animateUpperRightLegUp();
		}
		else if (botFour_rightHipAngle < -60 && botFour_rightKneeAngle < 60) {
			botFour_animateLowerRightLegUp();
		}
		else if (botFour_reverse == true && botFour_rightHipAngle <= 0) {
			botFour_animateUpperRightLegDown();
		}
		else if (botFour_reverse == true && botFour_firstcheck == true && botFour_rightKneeAngle >= botFour_rightleginit) {
			botFour_animateLowerRightLegDown();
			botFour_start = false;
			glutIdleFunc(botFour_takeStep);
		}
	}
}

void botFour_collapseAnimationHandler(int param)
{
	if (botFour_collapseOngoing)
	{
		bool done = true;
		int spinSpeed = 5;
		int endHeight = -17.4;
		double fallSpeed = -0.5;

		// BotFour: One
		if (!botFourOne_active)
		{
			if (botFourOne_robotAngle > 360) {
				//If spun, then make legs disappear
				if (botFourOne_bar != 0)
				{
					botFourOne_upperLegLength = 0 * botFourOne_bodyLength;
					botFourOne_upperLegWidth = 0 * botFourOne_bodyWidth;
					botFourOne_lowerLegLength = botFourOne_upperLegLength;
					botFourOne_lowerLegWidth = botFourOne_upperLegWidth;
					botFourOne_footLength = botFourOne_lowerLegLength * 0;
					botFourOne_ballJointLength = botFourOne_lowerLegLength * 0;
					botFourOne_footWidth = 0 * botFourOne_lowerLegWidth;
					botFourOne_footDepth = 0 * botFourOne_lowerLegWidth;
					botFourOne_bar = 0;
					done = false;
				}
				//If legs have disappeared, then fall
				else
				{
					if (botFourOne_Y >= endHeight)
					{
						botFourOne_Y += fallSpeed;
						done = false;
					}
				}
			}
			//If not spun, then spin
			else
			{ 
				botFourOne_robotAngle += spinSpeed;
				done = false; 
			}
		}

		// BotFour: Two
		if (!botFourTwo_active)
		{
			if (botFourTwo_robotAngle > 360) {
				//If spun, then make legs disappear
				if (botFourTwo_bar != 0)
				{
					botFourTwo_upperLegLength = 0 * botFourTwo_bodyLength;
					botFourTwo_upperLegWidth = 0 * botFourTwo_bodyWidth;
					botFourTwo_lowerLegLength = botFourTwo_upperLegLength;
					botFourTwo_lowerLegWidth = botFourTwo_upperLegWidth;
					botFourTwo_footLength = botFourTwo_lowerLegLength * 0;
					botFourTwo_ballJointLength = botFourTwo_lowerLegLength * 0;
					botFourTwo_footWidth = 0 * botFourTwo_lowerLegWidth;
					botFourTwo_footDepth = 0 * botFourTwo_lowerLegWidth;
					botFourTwo_bar = 0;
				}
				//If legs have disappeared, then fall
				else
				{
					if (botFourTwo_Y >= endHeight)
					{
						botFourTwo_Y += fallSpeed;
						done = false;
					}
				}
			}
			//If not spun, then spin
			else
			{
				botFourTwo_robotAngle += spinSpeed;
				done = false;
			}
		}

		glutPostRedisplay();
		//If not all at end of line, continue
		if (!done)
			{ glutTimerFunc(10, botFour_collapseAnimationHandler, 0); }
		else
			{ botFour_collapseOngoing = false; }
	}
}

// -----------------
// --- Functions ---
// -----------------

void collapseBotFour(int botNum)
{
	switch (botNum)
	{
	case 1:
		botFourOne_active = false;
		break;
	case 2:
		botFourTwo_active = false;
		break;
	}
	botFour_stop = true;

	if (!botFour_collapseOngoing)
	{
		botFour_collapseOngoing = true;
		glutTimerFunc(10, botFour_collapseAnimationHandler, 0);
	}
}

#pragma once
