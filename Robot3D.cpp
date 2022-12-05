
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
#include "VECTOR3D.h"
#include "QuadMesh.h"
#include <GL\freeglut_ext.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>




// ----------------
// --- Bot Four ---
// ----------------

// Robot dimensions
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
bool botFour_walkcheck = false;

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

// -----------------
// --- Bot Three ---
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

// ---------------------
// --- Bot Instances ---
// ---------------------

unsigned int botCollapseCount = 0;

GLfloat botThree_startingY = -8.5;
GLfloat botFour_startingY = -4;

GLfloat startingZ = -200;
GLfloat endingZ = -5;

// BotThree: One
bool botThreeOne_active = true;
GLfloat botThreeOne_X = -10;
GLfloat botThreeOne_Y = botThree_startingY;
GLfloat botThreeOne_Z = startingZ;
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
GLfloat botThreeTwo_Z = startingZ;
float botThreeTwo_rightHipAngle = 45.0;
float botThreeTwo_leftHipAngle = 45.0;
float botThreeTwo_rightKneeAngle = 270.0;
float botThreeTwo_leftKneeAngle = 270.0;
int botThreeTwo_rightWalkIndex = 0;
int botThreeTwo_leftWalkIndex = 67;

// BotFour: One
bool botFourOne_active = true;
GLfloat botFourOne_X = -30;
GLfloat botFourOne_Y = botFour_startingY;
GLfloat botFourOne_Z = startingZ;

// BotFour: Two
bool botFourTwo_active = true;
GLfloat botFourTwo_X = 10;
GLfloat botFourTwo_Y = botFour_startingY;
GLfloat botFourTwo_Z = startingZ;


void translateAnimationHandler(int);
void drawRobot(int botNum);

// --------------
// --- Cannon ---
// --------------
bool mallocCannonVbo;

int cannon_vertexLen = 0;
int cannon_vertexSize = 0;
int cannon_quadLen = 0;
int cannon_quadSize = 0;
float cannon_rotateX = 0;
float cannon_rotateY = 0;
unsigned int cannon_vertexVboID;
unsigned int cannon_normalVboID;
unsigned int cannon_indexVboID;
GLdouble* cannon_vertexPositionVao;
GLdouble* cannon_vertexNormalVao;
GLuint* cannon_quadIndicesVao;
static GLuint cannontexture;

// Set up lighting/shading and material properties for cannon
GLfloat cannonMat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat cannonMat_specular[] = { 0.45, 0.55, 0.45, 1.0 };
GLfloat cannonMat_diffuse[] = { 0.2f, 0.2f, 0.2f, 0.2f };
GLfloat cannonMat_shininess[] = { 5.0F };

//Functions
void generateBuffers();
void deleteBuffers();
void drawDefensiveCannon();
void exportCannonMesh();

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

// ----------------
// --- Bot Four ---
// ----------------

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
	
	if (botFour_start == false) {
		botFour_leftHipAngle = 0;
		botFour_leftKneeAngle = botFour_leftleginit;
		botFour_start = true;
		botFour_stopmovingupper = false;
	}
	else if (botFour_leftHipAngle >= -60 && botFour_leftKneeAngle < 60 && botFour_stopmovingupper==false) {
		botFour_animateUpperLegUp();
	}
	else if (botFour_leftHipAngle < -60 && botFour_leftKneeAngle < 60) {
		botFour_animateLowerLegUp();
	}
	else if (botFour_reverse == true && botFour_leftHipAngle<=0) {
		botFour_animateUpperLegDown();
	}
	else if (botFour_reverse == true && botFour_firstcheck==true && botFour_leftKneeAngle >= botFour_leftleginit) {
		botFour_animateLowerLegDown();
		botFour_start = false;
		glutIdleFunc(botFour_takeRightStep);
	}
}
void botFour_takeRightStep() {

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



// -----------------
// --- Bot Three ---
// -----------------

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

// --------------
// --- Cannon ---
// --------------

void generateBuffers()
{
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "Glew error: %s\n", glewGetErrorString(err));
	}  
	


	//Position
	glGenBuffers(1, &cannon_vertexVboID);
	glBindBuffer(GL_ARRAY_BUFFER, cannon_vertexVboID);
	glBufferData(GL_ARRAY_BUFFER, cannon_vertexSize, cannon_vertexPositionVao, GL_STATIC_DRAW);
	glVertexPointer(3, GL_DOUBLE, 0, NULL);
	glEnable(GL_TEXTURE_2D);	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Normal
	glGenBuffers(1, &cannon_normalVboID);
	glBindBuffer(GL_ARRAY_BUFFER, cannon_normalVboID);
	glBufferData(GL_ARRAY_BUFFER, cannon_vertexSize, cannon_vertexNormalVao, GL_STATIC_DRAW);
	glNormalPointer(GL_DOUBLE, 0, NULL);
	glEnableClientState(GL_NORMAL_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Indices
	glGenBuffers(1, &cannon_indexVboID);
	glBindBuffer(GL_ARRAY_BUFFER, cannon_indexVboID);
	glBufferData(GL_ARRAY_BUFFER, cannon_quadSize, cannon_quadIndicesVao, GL_DYNAMIC_DRAW);
	glEnableClientState(GL_NORMAL_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void deleteBuffers()
{
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &cannon_indexVboID);
	glDeleteBuffers(1, &cannon_normalVboID);
	glDeleteBuffers(1, &cannon_vertexVboID);
}

void exportCannonMesh() {
	// Array sizes
	int subcurveNumCurvePoints = 33;
	int numberOfSides = 16;
	int doubleSize = 8;
	int intSize = 4;

	int cannon_verLen = subcurveNumCurvePoints * numberOfSides;
	cannon_vertexLen = cannon_verLen * 3;
	cannon_vertexSize = cannon_vertexLen * doubleSize;

	int cannon_quadLen = (subcurveNumCurvePoints - 1) * numberOfSides;
	cannon_quadLen = cannon_quadLen * 4;
	cannon_quadSize = cannon_quadLen * intSize;

	// Malloc
	cannon_vertexPositionVao = (GLdouble*)malloc(cannon_vertexSize);
	cannon_vertexNormalVao = (GLdouble*)malloc(cannon_vertexSize);
	cannon_quadIndicesVao = (GLuint*)malloc(cannon_quadSize);

	// Read File
	std::ifstream MyReadFile("output.txt");//read from output txt file
	std::string inputdata;
	std::string data;
	while (std::getline(MyReadFile, inputdata)) {//get the data as a string of values seperated by spaces
		std::stringstream stream;
		stream << inputdata;
		data += stream.str();
		data += " ";
	}
	MyReadFile.close();

	// Fill VAOs
	int vertexCounter = 0;
	int normalCounter = 0;
	int quadCounter = 0;
	std::istringstream copy(data);
	std::string s;
	while (std::getline(copy, s, ' ')) {//go through the string and assign all the vertices normals and quads to their respective arrays
		if (vertexCounter < 1584) {
			cannon_vertexPositionVao[vertexCounter] = std::stod(s.c_str());//convert string to double
			vertexCounter++;
		}
		else if (normalCounter < 1584) {
			cannon_vertexNormalVao[normalCounter] = std::stod(s.c_str());//convert string to double
			normalCounter++;
		}
		else {
			cannon_quadIndicesVao[quadCounter] = std::stoi(s.c_str());//convert string to int 
			quadCounter++;
		}
	}
}

void drawDefensiveCannon()
{
	if (!mallocCannonVbo)
	{
		exportCannonMesh();
		mallocCannonVbo = true;
	}

	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cannonMat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cannonMat_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cannonMat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cannonMat_shininess);

		// Transformations
		glTranslatef(0, -10.0, 45);
		glRotatef(-70, 1, 0, 0);

		// Rotate according to use mouse input
		//Y
		glRotatef(cannon_rotateY, 1, 0, 0);

		//X
		glTranslatef(0, 0, 45);
		glRotatef(cannon_rotateX, 0, 0, 1);
		glTranslatef(0, 0, -45);

		// Draw elements
		generateBuffers();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cannon_indexVboID);
		glDrawElements(GL_QUADS, cannon_quadSize, GL_UNSIGNED_INT, (void*)0);
		deleteBuffers();
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
		glutTimerFunc(10, translateAnimationHandler, 0);
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
	
	// Walk Cycle: Bot Three
	if (botThree_walkCycle == false)
	{
		botThree_walkCycle = true;
		glutTimerFunc(10, botThree_walkAnimationHandler, 0);
	}

	// Walk Cycle: Bot Four
	if (botFour_walkcheck == false) {
		glutIdleFunc(botFour_takeStep);
		botFour_walkcheck = true;
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
		int spinSpeed = 4;
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

