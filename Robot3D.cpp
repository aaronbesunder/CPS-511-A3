
#include <stdlib.h>
#include <stdio.h>
#include <dos.h> 
#include <string.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <gl/glut.h>
#include <utility>
#include <vector>
#include <GL\freeglut_ext.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#include "VECTOR3D.h"
#include "QuadMesh.h"
#include "BotThree.h"
#include "BotFour.h"
#include "Cannon.h"

// ---------------------
// --- Bot Instances ---
// ---------------------

unsigned int botCollapseCount = 0;
bool botsMoving = false;

GLfloat botThree_startingY = -8.5;
GLfloat botFour_startingY = -4;

GLfloat startingZ = -200;
GLfloat endingZ = -5;

// BotThree: One
GLfloat botThreeOne_X = -10;
GLfloat botThreeOne_Y = botThree_startingY;
GLfloat botThreeOne_Z = startingZ;

// BotThree: Two
GLfloat botThreeTwo_X = 30;
GLfloat botThreeTwo_Y = botThree_startingY;
GLfloat botThreeTwo_Z = startingZ;

// BotFour: One
GLfloat botFourOne_X = -30;
GLfloat botFourOne_Y = botFour_startingY;
GLfloat botFourOne_Z = startingZ;

// BotFour: Two
GLfloat botFourTwo_X = 10;
GLfloat botFourTwo_Y = botFour_startingY;
GLfloat botFourTwo_Z = startingZ;

void translateAnimationHandler(int);
void drawRobot(int botNum);

// ------------
// --- Help ---
// ------------
bool help = false;
void drawHelp();
void drawLeftText();
void drawRightText();
void drawCoordinates();

// --------------
// --- Window ---
// --------------

const int vWidth = 650;		// Viewport width in pixels
const int vHeight = 500;	// Viewport height in pixels

GLdouble nearPlane = 0.10;	// 0.2		0.10
GLdouble farPlane = 250.0;	// 40.0		100.0

GLdouble eyeX = 0;
GLdouble eyeY = -5;
GLdouble eyeZ = 50;

GLdouble centerX = 0;
GLdouble centerY = -20.0;
GLdouble centerZ = 0;

GLfloat mouse_prevX;
GLfloat mouse_prevY;

// -------------------------------------------------------

// Light properties
GLfloat light_position0[] = { -4.0F, 8.0F, 8.0F, 1.0F };
GLfloat light_position1[] = { 4.0F, 8.0F, 8.0F, 1.0F };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_ambient[] = { 0.2F, 0.2F, 0.2F, 1.0F };

// Mouse button
int currentButton;

// A flat open mesh
QuadMesh *groundMesh = NULL;

// Structure defining a bounding box, currently unused
typedef struct BoundingBox {
    VECTOR3D min;
	VECTOR3D max;
} BBox;

// Default Mesh Size
int meshSize = 16; //Default: 16

// Prototypes for functions in this module
void initOpenGL(int w, int h);
void display(void);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void mouseMotionHandler(int xMouse, int yMouse);
void keyboard(unsigned char key, int x, int y);
void functionKeys(int key, int x, int y);

int main(int argc, char **argv)
{
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(vWidth, vHeight);
	glutInitWindowPosition(200, 30);
	glutCreateWindow("3D Hierarchical Example");

	// Initialize GL
	initOpenGL(vWidth, vHeight);

	// Register callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotionHandler);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(functionKeys);
	// Start event loop, never returns
	glutMainLoop();

	return 0;
}


// Set up OpenGL. For viewport and projection setup see reshape(). 
void initOpenGL(int w, int h)
{
	// Set up and enable lighting
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);   // This second light is currently off

	// Other OpenGL setup
	glEnable(GL_DEPTH_TEST);   // Remove hidded surfaces
	glShadeModel(GL_SMOOTH);   // Use smooth shading, makes boundaries between polygons harder to see 
	glClearColor(0.4F, 0.4F, 0.4F, 0.0F);  // Color and depth for glClear
	glClearDepth(1.0f);
	glEnable(GL_NORMALIZE);    // Renormalize normal vectors 
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   // Nicer perspective

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		

	// Other initializatuion
	// Set up ground quad mesh
	float groundSize = 400.0f;
	float halfGroundSize = groundSize / 2;
	VECTOR3D origin = VECTOR3D(-halfGroundSize, 0.0f, halfGroundSize/4);
	VECTOR3D dir1v = VECTOR3D(1.0f, 0.0f, 0.0f);
	VECTOR3D dir2v = VECTOR3D(0.0f, 0.0f, -1.0f);
	groundMesh = new QuadMesh(meshSize, groundSize);
	groundMesh->InitMesh(meshSize, origin, groundSize, groundSize, dir1v, dir2v);
	//VECTOR3D origin = VECTOR3D(-16.0f, 0.0f, 16.0f);
	//groundMesh = new QuadMesh(meshSize, 32.0);
	//groundMesh->InitMesh(meshSize, origin, 32.0, 32.0, dir1v, dir2v);

	VECTOR3D ambient = VECTOR3D(0.0f, 0.05f, 0.0f);
	VECTOR3D diffuse = VECTOR3D(0.4f, 0.8f, 0.4f);
	VECTOR3D specular = VECTOR3D(0.04f, 0.04f, 0.04f);
	float shininess = 0.2;
	groundMesh->SetMaterial(ambient, diffuse, specular, shininess);

}

// Callback, called at initialization and whenever user resizes the window.
void reshape(int w, int h)
{
	// Set up viewport, projection, then change to modelview matrix mode - 
	// display function will then set up camera and do modeling transforms.
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(60.0, (GLdouble)w / h, 0.2, 40.0);
	gluPerspective(60.0, (GLdouble)w / h, nearPlane, farPlane);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set up the camera at position (0, 6, 22) looking at the origin, up along positive y axis
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0, 1.0, 0.0);
}


// Callback, called whenever GLUT determines that the window should be redisplayed
// or glutPostRedisplay() has been called.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	// Create Viewing Matrix V
	// Set up the camera at position (0, 6, 30) looking at the origin, up along positive y axis
	//gluLookAt(0.0, 6.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0, 1.0, 0.0);

	//Ground Level
	//gluLookAt(0.0, -19.9, 30.0, 0.0, -19.9, 0.0, 0.0, 1.0, 0.0);

	// Defensive Cannon
	drawDefensiveCannon();
	drawCannonProjectile();

	// Draw Robots
	
	// Bot Four: One
	drawRobot(1);
	// Bot Three: One
	drawRobot(2);
	// Bot Four: Two
	drawRobot(3);
	// Bot Three: Two
	drawRobot(4);
	
	// Help
	drawHelp();

	// Draw ground
	glPushMatrix();
	glTranslatef(0.0, -20.0, 0.0);
	groundMesh->DrawMesh(meshSize);
	glPopMatrix();

	glutSwapBuffers();   // Double buffering, swap buffers
}

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

// ------------
// --- Help ---
// ------------
void drawHelp()
{
	glDisable(GL_LIGHTING);

	drawLeftText();
	drawRightText();
	/*if (help == true) 
		{ drawCoordinates(); }*/

	glEnable(GL_LIGHTING);
}

void drawLeftText()
{
	glPushMatrix();
		int x = 10;
		int y = vHeight - 20;

		//Colours
		float r = 255;
		float g = 255;
		float b = 255;
		glColor3f(r, g, b);
		glWindowPos2f(x, y);
		char str[400] = "";
		if (help != true)
		{
			sprintf_s(str, "Press F1 for help");
		}
		else
		{
			sprintf_s(str, "Press F1 to hide\n\nRotate Robot\n   CCW: r\n   CW: R\n\nBody\n   Down / CCW: b\n   Up / CW: B\n\nHip\n  CCW: h\n   CW: H\n\nKnee\n   CCW: k\n   CW: K\n\nCannon Animation\n   Start: c\n   Stop: C\n\nWalk Animation\n   Start: w\n   Stop: W\n\nMove Forward\n   Start: a\n\nReset: t");
		}
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>
			(str));
	glPopMatrix();
}

void drawRightText()
{
	glPushMatrix();
		int x = vWidth - 130;
		int y = vHeight - 20;

		// Colours
		float r = 255;
		float g = 255;
		float b = 255;
		glColor3f(r, g, b);
		glWindowPos2f(x, y);
		char str[1000] = "";
		if (help != true)
		{
			sprintf_s(str, "");
		}
		else
		{
			sprintf_s(str, "Robot Angle: %0.1f\n\nBotThree: One Angles\n   Body: %0.1f\n   Hip: %0.1f\n   Knee: %0.1f\n\nBotThree: Two Angles\n   Body: %0.1f\n   Hip: %0.1f\n   Knee: %0.1f\n\nBotFour: One Angles\n   Body: %0.1f\n   Hip: %0.1f\n   Knee: %0.1f\n\nBotFour: Two Angles\n   Body: %0.1f\n   Hip: %0.1f\n   Knee: %0.1f\n\nRotation Speed: %0.1f\n\nCannon Angle\n   X: %0.1f\n   Y: %0.1f", 
				botThree_robotAngle, botThree_bodyAngle, botThreeOne_rightHipAngle, botThreeOne_rightKneeAngle,
				botThree_bodyAngle, botThreeTwo_rightHipAngle, botThreeTwo_rightKneeAngle,
				botFour_bodyAngle, botFour_leftHipAngle, botFour_leftKneeAngle, 
				botFour_bodyAngle, botFour_leftHipAngle, botFour_leftKneeAngle,
				rotateSpeed, cannon_rotateX, cannon_rotateY);
		}
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>
			(str));
	glPopMatrix();
}

void drawCoordinates()
{
	glDisable(GL_LIGHTING);

	glPushMatrix();
		GLfloat lineLen = 11.0f;

		// spin coordinates on base.
		glRotatef(botThree_robotAngle, 0.0, 1.0, 0.0);

		// x
		glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos3f(lineLen + 0.5, 0, 0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>("x"));
		glBegin(GL_LINES);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(lineLen, 0.0f, 0.0f);
		glEnd();
		glFlush();

		// y
		glColor3f(0.0f, 1.0f, 0.0f);
		glRasterPos3f(0, lineLen + 0.5, 0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>("y"));
		glBegin(GL_LINES);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, lineLen, 0.0f);
		glEnd();
		glFlush();

		// z
		glColor3f(0.0f, 0.0f, 1.0f);
		glRasterPos3f(0, 0, lineLen + 0.5);
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>("z"));
		glBegin(GL_LINES);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, lineLen);
		glEnd();
		glFlush();

		glLineWidth(1.0);
	glPopMatrix();

	glEnable(GL_LIGHTING);
}

// --------------------------
// --- Mouse and Keyboard ---
// --------------------------

// Callback, handles input from the keyboard, non-arrow keys
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'r':
		// Bot Four
		
		// Bot Three
		botThree_robotAngle += rotateSpeed;
		if (botThree_robotAngle >= 360)
			{ botThree_robotAngle -= 360.0; }
		break;

	case 'R':
		// Bot Four
		
		// Bot Three
		botThree_robotAngle -= rotateSpeed;
		if (botThree_robotAngle < 0)
			{ botThree_robotAngle += 360.0; }
		break;

	case 'b':
		// Bot Four
		botFour_bodyAngle += rotateSpeed;
		if (botFour_bodyAngle >= 360)
			{ botFour_bodyAngle -= 360.0; }
		// Bot Three
		botThree_bodyAngle += rotateSpeed;
		if (botThree_bodyAngle >= 360)
			{ botThree_bodyAngle -= 360.0; }
		break;

	case 'B':
		// Bot Four
		botFour_bodyAngle -= rotateSpeed;
		if (botFour_bodyAngle < 0)
			{ botFour_bodyAngle += 360.0; }
		// Bot Three
		botThree_bodyAngle -= rotateSpeed;
		if (botThree_bodyAngle < 0)
			{ botThree_bodyAngle += 360.0; }
		break;

	case 'h':
		// Bot Four
		botFour_rightHipAngle += rotateSpeed;
		botFour_leftHipAngle += rotateSpeed;
		if (botFour_rightHipAngle >= 360)
		{
			botFour_rightHipAngle -= 360.0;
			botFour_leftHipAngle -= 360.0;
		}
		// Bot Three
		botThreeOne_rightHipAngle += rotateSpeed;
		botThreeOne_leftHipAngle += rotateSpeed;
		if (botThreeOne_rightHipAngle >= 360)
		{ 
			botThreeOne_rightHipAngle -= 360.0;
			botThreeOne_leftHipAngle -= 360.0;
		}
		break;

	case'H':
		// Bot Four
		botFour_rightHipAngle -= rotateSpeed;
		botFour_leftHipAngle -= rotateSpeed;
		if (botFour_rightHipAngle < 0)
		{
			botFour_rightHipAngle += 360.0;
			botFour_leftHipAngle += 360.0;
		}
		// Bot Three
		botThreeOne_rightHipAngle -= rotateSpeed;
		botThreeOne_leftHipAngle -= rotateSpeed;
		if (botThreeOne_rightHipAngle < 0)
		{
			botThreeOne_rightHipAngle += 360.0;
			botThreeOne_leftHipAngle += 360.0;
		}
		break;

	case 'k':
		// Bot Four
		botFour_rightKneeAngle += rotateSpeed;
		botFour_leftKneeAngle += rotateSpeed;
		if (botFour_rightKneeAngle >= 360)
		{
			botFour_rightKneeAngle -= 360.0;
			botFour_leftKneeAngle -= 360.0;
		}
		// Bot Three
		botThreeOne_rightKneeAngle += rotateSpeed;
		botThreeOne_leftKneeAngle += rotateSpeed;
		if (botThreeOne_rightKneeAngle >= 360)
		{
			botThreeOne_rightKneeAngle -= 360.0;
			botThreeOne_leftKneeAngle -= 360.0;
		}
		break;


	case 'K':
		// Bot Four
		botFour_rightKneeAngle -= rotateSpeed;
		botFour_leftKneeAngle -= rotateSpeed;
		if (botFour_rightKneeAngle < 0)
		{
			botFour_rightKneeAngle += 360.0;
			botFour_leftKneeAngle += 360.0;
		}
		// Bot Three
		botThreeOne_rightKneeAngle -= rotateSpeed;
		botThreeOne_leftKneeAngle -= rotateSpeed;
		if (botThreeOne_rightKneeAngle < 0)
		{
			botThreeOne_rightKneeAngle += 360.0;
			botThreeOne_leftKneeAngle += 360.0;
		}
		break;

	case 'f':
		// Bot Four
		if (botFour_leftFootAngle >= -132 && botFour_leftFootAngle < 74)
			{ botFour_leftFootAngle += 2.0; }
		break;


	case 'F':
		// Bot Four
		if (botFour_leftFootAngle > -52 && botFour_leftFootAngle <= 132)
		{
			botFour_leftFootAngle -= 2.0;
			//printf("%lf\n", botFour_leftFootAngle);
			break;
		}
		break;

	case 'c':
		// Bot Four
		botFour_gunStop = false;
		glutTimerFunc(10, botFour_gunHandler, 0);
		// Bot Three
		if (botThree_cannonRotation == false)
		{
			botThree_cannonRotation = true;
			glutTimerFunc(10, botThree_cannonAnimationHandler, 0);
		}
		break;

	case 'C':
		// Bot Four
		botFour_gunStop = true;
		// Bot Three
		botThree_cannonRotation = false;
		break;

	case 'w':
		// Bot Four
		glutIdleFunc(botFour_takeStep);
		botFour_start = false;
		// Bot Three
		if (botThree_walkCycle == false)
		{
			botThree_walkCycle = true;
			glutTimerFunc(10, botThree_walkAnimationHandler, 0);
		}
		break;

	case 'W':
		// Bot Four
		botFour_stop = true;
		botFourR_stop = true;
		// Bot Three
		botThree_walkCycle = false;
		break;
	
	case 't':
	case 'T':
		// Bot Four
		
		botFour_gunAngle = 270;
		botFour_bodyAngle = 0.0;
		botFour_rightHipAngle = 0.0;
		botFour_leftHipAngle = 0.0;
		botFour_rightKneeAngle = 0.0;
		botFour_leftKneeAngle = 0.0;

		botFour_start = false;
		botFour_stop = false;
		botFourR_stop = false;
		botFour_reverse = false;
		botFour_firstcheck = false;
		botFour_stopmovingupper = false;
		botFour_gunStop = false;

		botFourOne_robotAngle = 0;
		botFourOne_upperLegLength = 0.95 * botFourOne_bodyLength;
		botFourOne_upperLegWidth = 0.125 * botFourOne_bodyWidth;
		botFourOne_lowerLegLength = botFourOne_upperLegLength;
		botFourOne_lowerLegWidth = botFourOne_upperLegWidth;
		botFourOne_footLength = botFourOne_lowerLegLength / 3.0;
		botFourOne_ballJointLength = botFourOne_lowerLegLength / 5.0;
		botFourOne_footWidth = 2.0 * botFourOne_lowerLegWidth;
		botFourOne_bar = 1.6 * botFourOne_bodyWidth;
		botFourOne_footDepth = 2.0 * botFourOne_lowerLegWidth;

		botFourTwo_robotAngle = 0;
		botFourTwo_upperLegLength = 0.95 * botFourTwo_bodyLength;
		botFourTwo_upperLegWidth = 0.125 * botFourTwo_bodyWidth;
		botFourTwo_lowerLegLength = botFourTwo_upperLegLength;
		botFourTwo_lowerLegWidth = botFourTwo_upperLegWidth;
		botFourTwo_footLength = botFourTwo_lowerLegLength / 3.0;
		botFourTwo_ballJointLength = botFourTwo_lowerLegLength / 5.0;
		botFourTwo_footWidth = 2.0 * botFourTwo_lowerLegWidth;
		botFourTwo_bar = 1.6 * botFourTwo_bodyWidth;
		botFourTwo_footDepth = 2.0 * botFourTwo_lowerLegWidth;

		botFour_collapseOngoing = false;
		botFour_walkcheck = false;

		// Bot Three
		botThree_robotAngle = 0.0;
		botThree_cannonAngle = 0.0;
		botThree_bodyAngle = 0.0;
		botThreeOne_rightHipAngle = 45.0;
		botThreeOne_leftHipAngle = 45.0;
		botThreeOne_rightKneeAngle = 270.0;
		botThreeOne_leftKneeAngle = 270.0;
		botThreeOne_leftWalkIndex = 67;
		botThreeOne_rightWalkIndex = 0;
		botThreeTwo_rightHipAngle = 45.0;
		botThreeTwo_leftHipAngle = 45.0;
		botThreeTwo_rightKneeAngle = 270.0;
		botThreeTwo_leftKneeAngle = 270.0;
		botThreeTwo_leftWalkIndex = 67;
		botThreeTwo_rightWalkIndex = 0;

		botThree_cannonRotation = false;
		botThree_walkCycle = false;

		// General
		rotateSpeed = 2.0;
		botsMoving = false;

		botThreeOne_active = true;
		botThreeOne_Y = botThree_startingY;
		botThreeOne_Z = startingZ;
		botThreeTwo_active = true;
		botThreeTwo_Y = botThree_startingY;
		botThreeTwo_Z = startingZ;

		botFourOne_active = true;
		botFourOne_Y = botFour_startingY;
		botFourOne_Z = startingZ;
		botFourTwo_active = true;
		botFourTwo_Y = botFour_startingY;
		botFourTwo_Z = startingZ;
		break;

	case 'a':
	case 'A':
		if (!botsMoving)
		{
			botsMoving = true;
			glutTimerFunc(10, translateAnimationHandler, 0);
		}
		break;
	}

	glutPostRedisplay();   // Trigger a window redisplay
}

// Callback, handles input from the keyboard, function and arrow keys
void functionKeys(int key, int x, int y)
{
	// Help key
	if (key == GLUT_KEY_F1)
	{
		if (help == true)
		{
			help = false;
		}
		else
		{
			help = true;
		}
	}
	// Do transformations with arrow keys
	//else if (...)   // GLUT_KEY_DOWN, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_LEFT
	//{
	//}

	glutPostRedisplay();   // Trigger a window redisplay
}


// Mouse button callback - use only if you want to 
void mouse(int button, int state, int x, int y)
{
	currentButton = button;

	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			mouse_prevX = x;
			mouse_prevY = y;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			;
		}
		break;
	default:
		break;
	}

	glutPostRedisplay();   // Trigger a window redisplay
}


// Mouse motion callback - use only if you want to 
void mouseMotionHandler(int xMouse, int yMouse)
{
	if (currentButton == GLUT_LEFT_BUTTON)
	{
		float sensitivity = 0.5;

		// Cannon Rotate X
		float deltaX = xMouse - mouse_prevX;
		cannon_rotateX += -deltaX * sensitivity;

		// Cannon Rotate X: Limit
		float xLimit = 50;
		if (cannon_rotateX > xLimit)
			{ cannon_rotateX = xLimit; }
		if (cannon_rotateX < -xLimit)
			{ cannon_rotateX = -xLimit; }

		// Cannon Rotate X: Update Prev
		mouse_prevX = xMouse;

		// Cannon Rotate Y
		float deltaY = yMouse - mouse_prevY;
		cannon_rotateY += -deltaY * sensitivity;

		// Cannon Rotate Y: Limit
		float yLimit = 20;
		if (cannon_rotateY > yLimit)
			{ cannon_rotateY = yLimit; }
		if (cannon_rotateY < -yLimit)
			{ cannon_rotateY = -yLimit; }

		// Cannon Rotate Y: Update Prev
		mouse_prevY = yMouse;

		glutPostRedisplay();
	}

	   // Trigger a window redisplay
}

// -----------------
// --- Animation ---
// -----------------

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

		glutPostRedisplay();
		//If not all at end of line, continue
		if (!done)
			{ glutTimerFunc(10, botThree_collapseAnimationHandler, 0); }
		else
			{ botThree_collapseOngoing = false; }
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

