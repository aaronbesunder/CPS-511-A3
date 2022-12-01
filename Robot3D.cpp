
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <gl/glut.h>
#include <utility>
#include <vector>
#include "VECTOR3D.h"
#include "QuadMesh.h"
#include <GL\freeglut_ext.h>
#include <sstream>

// ----------------
// --- Bot Four ---
// ----------------

// Robot dimensions
float botFour_bodyWidth = 4.5;
float botFour_bodyLength = 5.5;
float botFour_bodyDepth = 7.0;
float botFour_upperLegLength = 0.95 * botFour_bodyLength;
float botFour_upperLegWidth = 0.125 * botFour_bodyWidth;
float botFour_lowerLegLength = botFour_upperLegLength;
float botFour_lowerLegWidth = botFour_upperLegWidth;
float botFour_footLength = botFour_lowerLegLength / 3.0;
float botFour_ballJointLength = botFour_lowerLegLength / 5.0;
float botFour_footWidth = 2.0 * botFour_lowerLegWidth;
float botFour_footDepth = 2.0 * botFour_lowerLegWidth;

// Control Robot body rotation on base and gun rotation
float botFour_angle = 0.0;
float botFour_bodyAngle = 0.0;
float botFour_gunAngle = -90.0;

// Control leg rotation
float botFour_leftLegAngle = 0.0;
float botFour_leftLegBack = -60;
float botFour_leftleginit = 8.0;
float botFour_leftLegAngle2 = 0.0;
float botFour_leftLegAngle3 = 0.0;
float botFour_rightLegAngle = 0.0;
float botFour_rightLegAngle2 = 0.0;
float botFour_rightLegAngle3 = 0.0;

// Animation
bool botFour_start = false;
bool botFour_stop = false;
bool botFour_reverse = false;
bool botFour_firstcheck = false;
bool botFour_stopmovingupper = false;
bool botFour_gunStop = false;

// Functions
void botFour_animateUpperLegUp();
void botFour_animateLowerLegUp();
void botFour_animateUpperLegDown();
void botFour_animateLowerLegDown();
void botFour_gunHandler(int param);
void botFour_takeStep();
void botFour_drawRobot();
void botFour_drawBody();
void botFour_drawLeftLeg();
void botFour_drawRightLeg();

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
float botThree_rotateSpeed = 2.0;

//Control joints
char botThree_jointSelection[] = "    ";
float botThree_bodyAngle = 0.0;
float botThree_hipAngle = 0.0;
float botThree_kneeAngle = 0.0;

//Control cannon rotation
bool botThree_cannonRotation = false;
float botThree_cannonAngle = 0.0;

//Control walk rotation
bool botThree_walkCycle = false;
int botThree_walkIndex = 0;
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
void botThree_drawRobot();

void botThree_drawBody();
void botThree_drawCannons();

void botThree_drawLeg();
void botThree_drawHipJoint(int);
void botThree_drawUpperLeg();
void botThree_drawKneeJoint(int);
void botThree_drawLowerLeg();
void botThree_drawFoot(int);

void botThree_cannonAnimationHandler(int param);
void botThree_walkAnimationHandler(int param);

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

// ------------
// --- Help ---
// ------------
bool help = false;
void drawHelp();
void drawLeftText();
void drawRightText();
void drawCoordinates();

// -------------------------------------------------------

const int vWidth = 650;    // Viewport width in pixels
const int vHeight = 500;    // Viewport height in pixels

// Lighting/shading and material properties for robot - upcoming lecture - just copy for now
// Robot RGBA material properties (NOTE: we will learn about this later in the semester)
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
int meshSize = 16;

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
	VECTOR3D origin = VECTOR3D(-16.0f, 0.0f, 16.0f);
	VECTOR3D dir1v = VECTOR3D(1.0f, 0.0f, 0.0f);
	VECTOR3D dir2v = VECTOR3D(0.0f, 0.0f, -1.0f);
	groundMesh = new QuadMesh(meshSize, 32.0);
	groundMesh->InitMesh(meshSize, origin, 32.0, 32.0, dir1v, dir2v);

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
	gluPerspective(60.0, (GLdouble)w / h, 0.2, 40.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set up the camera at position (0, 6, 22) looking at the origin, up along positive y axis
	gluLookAt(0.0, 6.0, 22.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


// Callback, called whenever GLUT determines that the window should be redisplayed
// or glutPostRedisplay() has been called.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	// Create Viewing Matrix V
	// Set up the camera at position (0, 6, 30) looking at the origin, up along positive y axis
	gluLookAt(0.0, 6.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// Draw Robot

	// Apply modelling transformations M to move robot
	// Current transformation matrix is set to IV, where I is identity matrix
	// CTM = IV

	// Bot Three
	glPushMatrix();
		glTranslatef(-10, 0, 0);
		botThree_drawRobot();
	glPopMatrix();

	// Bot Four
	glPushMatrix();
		glTranslatef(10, 0, 0);
		botFour_drawRobot();
	glPopMatrix();

	// Help
	drawHelp();

	// Draw ground
	glPushMatrix();
	glTranslatef(0.0, -20.0, 0.0);
	groundMesh->DrawMesh(meshSize);
	glPopMatrix();

	glutSwapBuffers();   // Double buffering, swap buffers
}

// ----------------
// --- Bot Four ---
// ----------------

void botFour_drawRobot()
{
	glPushMatrix();
	 // spin robot on base. 
	 glRotatef(botFour_angle, 0.0, 1.0, 0.0);

	 botFour_drawBody();
	 botFour_drawLeftLeg();
	 botFour_drawRightLeg();
	

	glPopMatrix();
}


void botFour_drawBody()
{
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

	glTranslatef(0, 0, 0.7);
	glPushMatrix();
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
	glScalef((1.6 * botFour_bodyWidth), 1, 1);
	glTranslatef(0, -0.55 * botFour_bodyLength, 2);
	glutSolidCube(1.0);
	glPopMatrix();

	
}

void botFour_drawLeftLeg()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, botFour_robotleg_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, botFour_robotleg_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, botFour_robotleg_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, botFour_robotleg_mat_shininess);

	//first ball joint
	glPushMatrix();
	glTranslatef((0.7 * botFour_bodyWidth + 0.7 * botFour_upperLegWidth), -0.65 * botFour_upperLegLength, 2.0);
	glScalef(botFour_upperLegWidth, botFour_ballJointLength, botFour_upperLegWidth);
	glRotatef(botFour_leftLegAngle, 1.0, 0.0, 0);
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
	glRotatef(botFour_leftLegAngle2, 1.0, 0.0, 0.0);
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

	glRotatef(botFour_leftLegAngle3, 1.0, 0.0, 0.0);
	glTranslatef(0, -1.5, 0);

	glPushMatrix();
	glScalef(2.0, 2.0, 5.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}
void botFour_drawRightLeg()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, botFour_robotleg_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, botFour_robotleg_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, botFour_robotleg_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, botFour_robotleg_mat_shininess);

	//first ball joint
	glPushMatrix();
	glTranslatef(-(0.7 * botFour_bodyWidth + 0.7 * botFour_upperLegWidth), -0.65 * botFour_upperLegLength, 2.0);
	glScalef(botFour_upperLegWidth, botFour_ballJointLength, botFour_upperLegWidth);
	glRotatef(botFour_rightLegAngle, 1.0, 0.0, 0);
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
	glRotatef(botFour_rightLegAngle2, 1.0, 0.0, 0.0);
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

	glRotatef(botFour_rightLegAngle3, 1.0, 0.0, 0.0);
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
		if (botFour_leftLegAngle > -60) {
			botFour_leftLegAngle -= 0.1;
			//printf("%lf\n", botFour_leftLegAngle);
			glutPostRedisplay();
		}

					
		
	}
}
// move lower leg up
void botFour_animateLowerLegUp()
{
	if (!botFour_stop)
	{
		if (botFour_leftLegAngle2 <60) {
			botFour_leftLegAngle2 += 0.05;
			//printf("%lf\n", (botFour_leftLegAngle2+botFour_leftleginit));
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
		if (botFour_reverse==true && botFour_leftLegAngle<=0) {
			botFour_leftLegAngle += 0.1;
			//printf("%lf\n", botFour_leftLegAngle);
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
		if (botFour_reverse == true && botFour_leftLegAngle2 >= (botFour_leftleginit)) {
			botFour_leftLegAngle2 -= 0.05;
			//printf("%lf\n", botFour_leftLegAngle2);
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
		botFour_leftLegAngle = 0;
		botFour_leftLegAngle2 = botFour_leftleginit;
		botFour_start = true;
		botFour_stopmovingupper = false;
	}
	else if (botFour_leftLegAngle >= -60 && botFour_leftLegAngle2 < 60 && botFour_stopmovingupper==false) {
		botFour_animateUpperLegUp();
	}
	else if (botFour_leftLegAngle < -60 && botFour_leftLegAngle2 < 60) {
		botFour_animateLowerLegUp();
	}
	else if (botFour_reverse == true && botFour_leftLegAngle<=0) {
		botFour_animateUpperLegDown();

	}
	else if (botFour_reverse == true && botFour_firstcheck==true && botFour_leftLegAngle2 >= botFour_leftleginit) {
		botFour_animateLowerLegDown();
		
	}
	
	
}

// -----------------
// --- Bot Three ---
// -----------------

void botThree_drawRobot()
{
	glPushMatrix();
		// spin robot on base. 
		glRotatef(botThree_robotAngle, 0.0, 1.0, 0.0);

		botThree_drawBody();
		botThree_drawLeg();

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

void botThree_drawLeg()
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
		
			if (legNum == -1)
			{
				//Rotate Hip Joint
				glRotatef(botThree_hipAngle, 1.0, 0.0, 0.0);
			}

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

						if (legNum == -1)
						{
							//Rotate Knee Joint
							glTranslatef(0.05 * botThree_bodyDepth, botThree_lowerLegHeight, 0.0);
							glRotatef(botThree_kneeAngle, 1.0, 0.0, 0.0);
							glTranslatef(-0.05 * botThree_bodyDepth, -botThree_lowerLegHeight, 0.0);
						}

						//Draw Lower Leg
						botThree_drawLowerLeg();

						//Foot
						botThree_drawFoot(legNum);

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

void botThree_drawFoot(int legNum)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, botThree_robotJoints_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, botThree_robotJoints_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, botThree_robotJoints_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, botThree_robotJoints_mat_shininess);

	//Foot
	glPushMatrix();
		// Position foot with respect to parent lower leg
		glTranslatef(0.0, botThree_legDiameter * -0.5, 0.0);

		if (legNum == -1)
		{
			//Get Foot Angle
			float footAngle = botThree_hipAngle + botThree_kneeAngle;
			while (footAngle > 360)
			{ footAngle -= 360; }

			//Unrotate Foot Angle if clip
			if (footAngle > 180)
				{ glRotatef(-footAngle, 1.0, 0.0, 0.0); }
		}

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
		botThree_cannonAngle += botThree_rotateSpeed;
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
		botThree_hipAngle = botThree_walkArr[botThree_walkIndex][0];
		botThree_kneeAngle = botThree_walkArr[botThree_walkIndex][1];
		botThree_walkIndex++;

		int arrLen = (int)( sizeof(botThree_walkArr) / sizeof(botThree_walkArr[0]) );
		if (botThree_walkIndex >= arrLen)
		{
			botThree_walkIndex = 0;
		}

		glutPostRedisplay();
		glutTimerFunc(10, botThree_walkAnimationHandler, 0);
	}
}

// ------------
// --- Help ---
// ------------
void drawHelp()
{
	glDisable(GL_LIGHTING);

	drawLeftText();
	drawRightText();
	if (help == true) 
		{ drawCoordinates(); }

	glEnable(GL_LIGHTING);
}

void drawLeftText()
{
	glPushMatrix();
		int x = -23;
		int y = 12;
		float r = 255;
		float g = 255;
		float b = 255;
		glColor3f(r, g, b);
		glRasterPos2f(x, y);
		char str[400] = "";
		if (help != true)
		{
			sprintf_s(str, "Press F1 for help");
		}
		else
		{
			sprintf_s(str, "Press F1 to hide\n\nRotate Robot\n   CCW: r\n   CW: R\n\nJoint Selection\n   Body: b\n   Hip: h\n   Knee: k\n   Deselect: backspace\n\nJoint Angle Change: Arrow Keys\n\nRotation Speed\n   Select: s\n   Increase: Right Arrow Key\n   Decrease: Left Arrow Key\n\nCannon Animation\n   Start: c\n   Stop: C\n\nWalk Animation\n   Start: w\n   Stop: W\n\nReset: t");
		}
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>
			(str));
	glPopMatrix();
}

void drawRightText()
{
	glPushMatrix();
		int x = 15;
		int y = 12;
		float r = 255;
		float g = 255;
		float b = 255;
		glColor3f(r, g, b);
		glRasterPos2f(x, y);
		char str[400] = "";
		if (help != true)
		{
			sprintf_s(str, "");
		}
		else
		{
			char jointStr[] = "     ";
			if (strcmp(botThree_jointSelection, "    ") == 0)
				{ strcpy_s(jointStr, "None "); }
			else if (strcmp(botThree_jointSelection, "body") == 0)
				{ strcpy_s(jointStr, "Body "); }
			else if (strcmp(botThree_jointSelection, "hip ") == 0)
				{ strcpy_s(jointStr, "Hip  "); }
			else if (strcmp(botThree_jointSelection, "knee") == 0)
				{ strcpy_s(jointStr, "Knee "); }
			else if (strcmp(botThree_jointSelection, "rspd") == 0)
				{ strcpy_s(jointStr, "Speed"); }
			sprintf_s(str, "\n\nRobot Angle: %0.1f\n\nJoint Angles\n   Body: %0.1f\n   Hip: %0.1f\n   Knee: %0.1f\nSelected: %s\n\nRotation Speed: %0.1f", botThree_robotAngle, botThree_bodyAngle, botThree_hipAngle, botThree_kneeAngle, jointStr, botThree_rotateSpeed);
		}
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>
			(str));
	glPopMatrix();
}

void drawCoordinates()
{
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
		botFour_angle += 2.0;
		break;
	case 'R':
		botFour_angle -= 2.0;
		break;
	case 'b':
		botFour_bodyAngle += 2.0;
		break;
	case 'B':
		botFour_bodyAngle -= 2.0;
		break;

	case 'h':
		botFour_leftLegAngle += 1;
		break;


	case'H':
		botFour_leftLegAngle -= 1;
		break;


	case 'k':
		if (botFour_leftLegAngle2 >= -132 && botFour_leftLegAngle2 < 132.0)
		{
			botFour_leftLegAngle2 += 2.0;
			printf("%lf\n", botFour_leftLegAngle2);
			break;
		}
		else {
			break;
		}


	case 'K':
		if (botFour_leftLegAngle2 > -132 && botFour_leftLegAngle2 <= 132)
		{
			botFour_leftLegAngle2 -= 2.0;
			printf("%lf\n", botFour_leftLegAngle2);
			break;
		}
		else {
			break;
		}
	case 'f':
		if (botFour_leftLegAngle3 >= -132 && botFour_leftLegAngle3 < 74)
		{
			botFour_leftLegAngle3 += 2.0;
			printf("%lf\n", botFour_leftLegAngle3);
			break;
		}
		else {
			break;
		}


	case 'F':
		if (botFour_leftLegAngle3 > -52 && botFour_leftLegAngle3 <= 132)
		{
			botFour_leftLegAngle3 -= 2.0;
			printf("%lf\n", botFour_leftLegAngle3);
			break;
		}
		else {
			break;
		}
	case 'c':
		botFour_gunStop = false;
		glutTimerFunc(10, botFour_gunHandler, 0);
		break;
	case 'C':
		botFour_gunStop = true;
		break;
	case 'w':
		glutIdleFunc(botFour_takeStep);
		botFour_start = false;
		break;
	case 'W':
		botFour_stop = true;
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
			;

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
		;
	}

	glutPostRedisplay();   // Trigger a window redisplay
}

