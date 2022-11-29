
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <gl/glut.h>
#include <utility>
#include <vector>
#include "VECTOR3D.h"
#include "QuadMesh.h"

const int vWidth  = 650;    // Viewport width in pixels
const int vHeight = 500;    // Viewport height in pixels

// Note how everything depends on robot body dimensions so that can scale entire robot proportionately
// just by changing robot body scale
float robotBodyWidth = 4.5;
float robotBodyLength = 5.5;
float robotBodyDepth = 7.0;
float robotUpperLegLength = 0.95 * robotBodyLength;
float robotUpperLegWidth = 0.125 * robotBodyWidth;
float robotLowerLegLength = robotUpperLegLength;
float robotLowerLegWidth = robotUpperLegWidth;
float robotFootLength = robotLowerLegLength / 3.0;
float ballJointLength = robotLowerLegLength / 5.0;
float robotFootWidth = 2.0 * robotLowerLegWidth;
float robotFootDepth = 2.0 * robotLowerLegWidth;


// Control Robot body rotation on base and gun rotation
float robotAngle = 0.0;
float bodyAngle = 0.0;
float gunAngle = -90.0;

// Control leg rotation
float leftLegAngle = 0.0;
float leftLegBack = -60;
float leftleginit = 8.0;
float leftLegAngle2 = 0.0;
float leftLegAngle3 = 0.0;
float rightLegAngle = 0.0;
float rightLegAngle2 = 0.0;
float rightLegAngle3 = 0.0;


// Lighting/shading and material properties for robot - upcoming lecture - just copy for now
// Robot RGBA material properties (NOTE: we will learn about this later in the semester)
GLfloat robotBody_mat_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
GLfloat robotBody_mat_specular[] = { 0.45f,0.55f,0.45f,1.0f };
GLfloat robotBody_mat_diffuse[] = { 0.1f,0.35f,0.1f,1.0f };
GLfloat robotBody_mat_shininess[] = { 32.0F };


GLfloat robotleg_mat_ambient[] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
GLfloat robotleg_mat_diffuse[] = { 0.5f,0.0f,0.0f,1.0f };
GLfloat robotleg_mat_specular[] = { 0.7f, 0.6f, 0.6f, 1.0f };
GLfloat robotleg_mat_shininess[] = { 32.0F };

GLfloat gun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat gun_mat_diffuse[] = { 0.01f,0.0f,0.01f,0.01f };
GLfloat gun_mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat gun_mat_shininess[] = { 100.0F };

GLfloat robotLegs_mat_ambient[] = { 0.25f, 0.25f, 0.25f, 1.0f };
GLfloat robotLegs_mat_diffuse[] = { 0.4f, 0.4f, 0.4f, 1.0f };
GLfloat robotLegs_mat_specular[] = { 0.774597f, 0.774597f, 0.774597f, 1.0f };
GLfloat robotLegs_mat_shininess[] = { 76.8F };


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
void animationHandler(); 
void animationHandler2();
void animationHandler3();
void animationHandler4();
void gunHandler(int param);
void takeStep();
void drawRobot();
void drawBody();
void drawLeftLeg();
void drawRightLeg();

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
	drawRobot();

	// Draw ground
	glPushMatrix();
	glTranslatef(0.0, -20.0, 0.0);
	groundMesh->DrawMesh(meshSize);
	glPopMatrix();

	glutSwapBuffers();   // Double buffering, swap buffers
}

void drawRobot()
{
	glPushMatrix();
	 // spin robot on base. 
	 glRotatef(robotAngle, 0.0, 1.0, 0.0);

	 drawBody();
	 drawLeftLeg();
	 drawRightLeg();
	

	glPopMatrix();
}


void drawBody()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, robotBody_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotBody_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotBody_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotBody_mat_shininess);

	//draw main body that can rotate along y axis
	glPushMatrix();
	glRotatef(bodyAngle, 0, 1.0, 0);

	glPushMatrix();
	glScalef(robotBodyWidth, robotBodyLength, robotBodyDepth);
	glutSolidCube(1.0);
	glPopMatrix();

	
	

	glMaterialfv(GL_FRONT, GL_AMBIENT, robotLegs_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotLegs_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotLegs_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotLegs_mat_shininess);

	//draw gun that can rotate
	GLUquadricObj* myquadric;
	myquadric = gluNewQuadric();
	glPushMatrix();
	glRotatef(gunAngle, 0, 0, 1.0);

	
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



	glMaterialfv(GL_FRONT, GL_AMBIENT, gun_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, gun_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, gun_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, gun_mat_shininess);
	//second part of the gun
	glPushMatrix();
	glRotatef(gunAngle, 0, 0, 1.0);

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
	glScalef((1.6 * robotBodyWidth), 1, 1);
	glTranslatef(0, -0.55 * robotBodyLength, 2);
	glutSolidCube(1.0);
	glPopMatrix();

	
}

void drawLeftLeg()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, robotleg_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotleg_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotleg_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotleg_mat_shininess);

	//first ball joint
	glPushMatrix();
	glTranslatef((0.7 * robotBodyWidth + 0.7 * robotUpperLegWidth), -0.65 * robotUpperLegLength, 2.0);
	glScalef(robotUpperLegWidth, ballJointLength, robotUpperLegWidth);
	glRotatef(leftLegAngle, 1.0, 0.0, 0);
	glTranslatef(-(0.7 * robotBodyWidth + 0.7 * robotUpperLegWidth), 0.65 * robotUpperLegLength, -2.0);
	glTranslatef((0.7 * robotBodyWidth + 0.7 * robotUpperLegWidth), -0.65 * robotUpperLegLength, 2.0);
	glPushMatrix();

	glutSolidSphere(1.25, 50, 50);
	glPopMatrix();

	//upper leg
	glPushMatrix();
	glTranslatef(-(0.5 * robotBodyWidth + 0.5 * robotUpperLegWidth), 0.5 * robotUpperLegLength, 0.0);
	glTranslatef(-(0.5 * robotBodyWidth + 0.5 * robotUpperLegWidth), 0.5 * robotUpperLegLength, 0.0);
	// Position leg with respect to parent body
	glTranslatef((1* robotBodyWidth + 1 * robotUpperLegWidth), -7.5, 0); // this will be done last

	
	
	// build upper leg
	glPushMatrix();
	glScalef(robotUpperLegWidth, robotUpperLegLength, robotUpperLegWidth);
	glutSolidCube(1.0);
	glPopMatrix();



	// Position ball joint with respect to upper leg
	glTranslatef(0, -2.5, 0);

	// build ball joint
	glPushMatrix();
	glutSolidSphere(0.6, 50, 50);
	glPopMatrix();


	//glTranslatef(-(0.5 * robotBodyWidth + 0.5 * robotUpperLegWidth), 0.5 * robotUpperLegLength, 0.0);
	glRotatef(leftLegAngle2, 1.0, 0.0, 0.0);
	glRotatef(19.0, -1.0, 0.0, 0.0);
	//glTranslatef((0.5 * robotBodyWidth + 0.5 * robotUpperLegWidth), -0.5 * robotUpperLegLength, 0.0);

	//position lower leg wrt ball joint
	glTranslatef(0, -2.5 * ballJointLength, 0);
	
	glPushMatrix();
	glScalef(robotUpperLegWidth, robotUpperLegLength, robotUpperLegWidth);
	glutSolidCube(1.0);
	glPopMatrix();
	

	glMaterialfv(GL_FRONT, GL_AMBIENT, robotleg_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotleg_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotleg_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotleg_mat_shininess);

	// Position ball joint with respect to upper leg
	glTranslatef(0, -2.5, 0); // this will be done last

	// build ball joint
	glPushMatrix();
	glutSolidSphere(0.6, 50, 50);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, robotleg_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotleg_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotleg_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotleg_mat_shininess);

	glRotatef(leftLegAngle3, 1.0, 0.0, 0.0);
	glTranslatef(0, -1.5, 0);

	glPushMatrix();
	glScalef(2.0, 2.0, 5.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}
void drawRightLeg()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, robotleg_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotleg_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotleg_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotleg_mat_shininess);

	//first ball joint
	glPushMatrix();
	glTranslatef(-(0.7 * robotBodyWidth + 0.7 * robotUpperLegWidth), -0.65 * robotUpperLegLength, 2.0);
	glScalef(robotUpperLegWidth, ballJointLength, robotUpperLegWidth);
	glRotatef(rightLegAngle, 1.0, 0.0, 0);
	glTranslatef((0.7 * robotBodyWidth + 0.7 * robotUpperLegWidth), 0.65 * robotUpperLegLength, -2.0);
	glTranslatef(-(0.7 * robotBodyWidth + 0.7 * robotUpperLegWidth), -0.65 * robotUpperLegLength, 2.0);
	glPushMatrix();

	glutSolidSphere(1.25, 50, 50);
	glPopMatrix();

	//upper leg
	glPushMatrix();
	glTranslatef(-(0.5 * robotBodyWidth + 0.5 * robotUpperLegWidth), 0.5 * robotUpperLegLength, 0.0);
	glTranslatef(-(0.5 * robotBodyWidth + 0.5 * robotUpperLegWidth), 0.5 * robotUpperLegLength, 0.0);
	// Position leg with respect to parent body
	glTranslatef((1 * robotBodyWidth + 1 * robotUpperLegWidth), -7.5, 0); // this will be done last



	// build upper leg
	glPushMatrix();
	glScalef(robotUpperLegWidth, robotUpperLegLength, robotUpperLegWidth);
	glutSolidCube(1.0);
	glPopMatrix();



	// Position ball joint with respect to upper leg
	glTranslatef(0, -2.5, 0);

	// build ball joint
	glPushMatrix();
	glutSolidSphere(0.6, 50, 50);
	glPopMatrix();


	//glTranslatef(-(0.5 * robotBodyWidth + 0.5 * robotUpperLegWidth), 0.5 * robotUpperLegLength, 0.0);
	glRotatef(rightLegAngle2, 1.0, 0.0, 0.0);
	glRotatef(19.0, -1.0, 0.0, 0.0);
	//glTranslatef((0.5 * robotBodyWidth + 0.5 * robotUpperLegWidth), -0.5 * robotUpperLegLength, 0.0);

	//position lower leg wrt ball joint
	glTranslatef(0, -2.5 * ballJointLength, 0);

	glPushMatrix();
	glScalef(robotUpperLegWidth, robotUpperLegLength, robotUpperLegWidth);
	glutSolidCube(1.0);
	glPopMatrix();


	glMaterialfv(GL_FRONT, GL_AMBIENT, robotleg_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotleg_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotleg_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotleg_mat_shininess);

	// Position ball joint with respect to upper leg
	glTranslatef(0, -2.5, 0); // this will be done last

	// build ball joint
	glPushMatrix();
	glutSolidSphere(0.6, 50, 50);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, robotleg_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotleg_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotleg_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotleg_mat_shininess);

	glRotatef(rightLegAngle3, 1.0, 0.0, 0.0);
	glTranslatef(0, -1.5, 0);

	glPushMatrix();
	glScalef(2.0, 2.0, 5.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	
	

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
bool start = false;
bool stop = false;
bool reverse = false;
bool firstcheck = false;
bool stopmovingupper = false;
bool gunStop = false;

// Callback, handles input from the keyboard, non-arrow keys
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'r':
		robotAngle += 2.0;
		break;
	case 'R':
		robotAngle -= 2.0;
		break;
	case 'b':
		bodyAngle += 2.0;
		break;
	case 'B':
		bodyAngle -= 2.0;
		break;

	case 'h':
		leftLegAngle += 1;
		break;
		
		
		case'H':
		leftLegAngle -= 1;
		break;
		

	case 'k':
		if (leftLegAngle2 >= -132 && leftLegAngle2 < 132.0)
		{
			leftLegAngle2 += 2.0;
			printf("%lf\n", leftLegAngle2);
			break;
		}
		else {
			break;
		}


	case 'K':
		if (leftLegAngle2 > -132 && leftLegAngle2 <= 132)
		{
			leftLegAngle2 -= 2.0;
			printf("%lf\n", leftLegAngle2);
			break;
		}
		else {
			break;
		}
	case 'f':
		if (leftLegAngle3 >= -132 && leftLegAngle3 < 74)
		{
			leftLegAngle3 += 2.0;
			printf("%lf\n", leftLegAngle3);
			break;
		}
		else {
			break;
		}


	case 'F':
		if (leftLegAngle3 > -52 && leftLegAngle3 <= 132)
		{
			leftLegAngle3 -= 2.0;
			printf("%lf\n", leftLegAngle3);
			break;
		}
		else {
			break;
		}
	case 'c':
		gunStop = false;
		glutTimerFunc(10, gunHandler, 0);
		break;
	case 'C':
		gunStop = true;
		break;
	case 'w':
		glutIdleFunc(takeStep);
		start = false;
		break;
	case 'W':
		stop = true;
		break;
	}

	glutPostRedisplay();   // Trigger a window redisplay
}

//move upper leg up
void animationHandler()
{
	if (!stop)
	{
		if (leftLegAngle > -60) {
			leftLegAngle -= 0.1;
			printf("%lf\n", leftLegAngle);
			glutPostRedisplay();
		}

					
		
	}
}
// move lower leg up
void animationHandler2()
{
	if (!stop)
	{
		if (leftLegAngle2 <60) {
			leftLegAngle2 += 0.05;
			printf("%lf\n", (leftLegAngle2+leftleginit));
			glutPostRedisplay();
			reverse = true;
			stopmovingupper = true;
		}
	}
}
//move upper leg down
void animationHandler3()
{
	if (!stop)
	{
		if (reverse==true && leftLegAngle<=0) {
			leftLegAngle += 0.1;
			printf("%lf\n", leftLegAngle);
			glutPostRedisplay();
			firstcheck = true;
		}


	}
}
//move lower leg down
void animationHandler4()
{
	if (!stop)
	{
		if (reverse == true && leftLegAngle2 >= (leftleginit)) {
			leftLegAngle2 -= 0.05;
			printf("%lf\n", leftLegAngle2);
			glutPostRedisplay();
		}


	}
}
//rotate gun
void gunHandler(int param) {
	if (!gunStop) {
		gunAngle += 5;
		glutPostRedisplay();
		glutTimerFunc(10, gunHandler, 0);
	}
}
//cases for the robot to call in order to animate taking a step
void takeStep() {
	
	if (start == false) {
		leftLegAngle = 0;
		leftLegAngle2 = leftleginit;
		start = true;
		stopmovingupper = false;
	}
	else if (leftLegAngle >= -60 && leftLegAngle2 < 60 && stopmovingupper==false) {
		animationHandler();
	}
	else if (leftLegAngle < -60 && leftLegAngle2 < 60) {
		animationHandler2();
	}
	else if (reverse == true && leftLegAngle<=0) {
		animationHandler3();

	}
	else if (reverse == true && firstcheck==true && leftLegAngle2 >= leftleginit) {
		animationHandler4();
		
	}
	
	
}



// Callback, handles input from the keyboard, function and arrow keys
void functionKeys(int key, int x, int y)
{
	// Help key
	if (key == GLUT_KEY_F1)
	{

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

