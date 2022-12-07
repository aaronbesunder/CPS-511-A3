
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
#include "Window.h"
#include "Bot.h"
#include "Cannon.h"

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
	//gluLookAt(0.0, -19.9, 50.0, 0.0, -19.9, 0.0, 0.0, 1.0, 0.0);

	//Top Down
	//gluLookAt(0.0, 100, 80.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//Cannon Top View
	//gluLookAt(0.0, 15, 45.0, 0.0, 0.0, 45.0, 0.0, 0.0, -1.0);

	//Cannon Back View
	//gluLookAt(0.0, -15.5, 60, 0.0, -10.5, 0.0, 0.0, 1.0, 0.0);

	//Cannon Side View
	//gluLookAt(-20, -19, 45, 0.0, -19, 45, 0.0, 1.0, 0.0);

	// Defensive Cannon
	drawDefensiveCannon();
	for (int index = 0; index < cannon_maxProjectileNum; index++)
		{cannon_drawProjectile(index);};

	// Draw Robots
	
	// Bot Four: One
	drawRobot(1);
	// Bot Three: One
	drawRobot(2);
	// Bot Four: Two
	drawRobot(3);
	// Bot Three: Two
	drawRobot(4);

	// Bot Projectile
	for (int index = 0; index < bot_maxProjectileNum; index++)
		{bot_drawProjectile(index);}
	
	// Help
	drawHelp();

	// Draw ground
	glPushMatrix();
		glTranslatef(0.0, -20.0, 0.0);
		groundMesh->DrawMesh(meshSize);
	glPopMatrix();

	glutSwapBuffers();   // Double buffering, swap buffers
}

// --------------------------
// --- Mouse and Keyboard ---
// --------------------------

// Callback, handles input from the keyboard, non-arrow keys
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 32: //Space
			cannon_addProjectile();
			break;

		case 's':
		case 'S':
			if (!botsMoving)
			{
				botsMoving = true;
				bot_resetProjectileArray();
				glutTimerFunc(10, bot_addProjectileAnimationHandler, 0);
				bot_isFiring = true;
				glutTimerFunc(10, translateAnimationHandler, 0);
			}
			break;

		case 'r':
		case 'R':
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
			bot_isFiring = false;
			bot_resetProjectileArray();

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

			// Cannon
			cannon_active = true;
			cannon_collapseOngoing = false;
			cannon_shakeSeconds = 0;
			cannon_resetProjectileArray();
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
		if (cannon_active)
		{
			float sensitivity = 0.5;

			// Cannon Rotate X
			float deltaX = xMouse - mouse_prevX;
			cannon_rotateX += -deltaX * sensitivity;

			// Cannon Rotate X: Limit
			float xLimit = 75;
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
		}

		// For testing
		//cannon_rotateX = 0;
		//cannon_rotateY = 0;

		glutPostRedisplay();
	}

	   // Trigger a window redisplay
}