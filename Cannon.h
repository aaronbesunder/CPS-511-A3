#pragma once

#include "Array.h"
#include "Window.h"
#include <corecrt_math_defines.h>

#include "Bot.h"
bool checkBotCollision(float, float, float);

// -----------------
// --- Variables ---
// -----------------

bool mallocCannonVbo;

// Cannon VBO
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

// Projectile
bool cannon_projectileExists = false;
float cannon_projectileSpeed = 1;
float cannon_projectileStartZ = 45;

// Projectile Dimensions
float projectile_height = 0.3;
float projectile_width = 0.3;
float projectile_depth = 5;

// Cannon
GLfloat cannonMat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat cannonMat_specular[] = { 0.45, 0.55, 0.45, 1.0 };
GLfloat cannonMat_diffuse[] = { 0.2f, 0.2f, 0.2f, 0.2f };
GLfloat cannonMat_shininess[] = { 5.0F };

// Projectile
GLfloat projectileMat_ambient[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat projectileMat_specular[] = { 0.45, 0.55, 0.45, 1.0 };
GLfloat projectileMat_diffuse[] = { 0.1f, 0.1f, 0.1, 0.2f };
GLfloat projectileMat_shininess[] = { 5.0F };

// Functions
void generateBuffers();
void deleteBuffers();
void drawDefensiveCannon();
void exportCannonMesh();

void cannon_drawProjectile(int);
void cannon_addProjectile();
void cannon_projectileAnimationHandler(int);
void cannon_printProjectileArray();
void cannon_resetProjectileArray();

//Projectile Arrays
//arrayClass arrayprojectile_Ypos{};
//arrayClass arrayprojectile_Xpos{};
//arrayClass arrayprojectile_Zpos{}; // Distance
//arrayClass arrayprojectile_Yang{};
//arrayClass arrayprojectile_Xang{};

const int cannon_maxProjectileNum = 10;
bool projectile_active[cannon_maxProjectileNum];
float projectile_xAng[cannon_maxProjectileNum];
float projectile_yAng[cannon_maxProjectileNum];
float projectile_xPos[cannon_maxProjectileNum];
float projectile_yPos[cannon_maxProjectileNum];
float projectile_zPos[cannon_maxProjectileNum]; // Distance

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
		cannon_resetProjectileArray();
	}

	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cannonMat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cannonMat_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cannonMat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cannonMat_shininess);

		// Transformations
		glTranslatef(0, -18.0, 45);
		glRotatef(-90, 1, 0, 0);

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
		//glDrawElements(GL_LINE_LOOP, cannon_quadSize, GL_UNSIGNED_INT, (void*)0);
		deleteBuffers();
	glPopMatrix();
}

// ------------------
// --- Projectile ---
// ------------------

void cannon_drawProjectile(int index)
{
	if (projectile_active[index])
	{
		float xAng = projectile_xAng[index];
		float yAng = projectile_yAng[index];
		float xPos = projectile_xPos[index];
		float yPos = projectile_yPos[index];
		float zPos = projectile_zPos[index];

		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, projectileMat_ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, projectileMat_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, projectileMat_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, projectileMat_shininess);

			glTranslatef(xPos, yPos, -zPos); // Comment out to make projectile stand still
			glTranslatef(0.0, -18, 40 + projectile_depth);

			// Rotate according to use mouse input
			glRotatef(yAng, 1, 0, 0);
			glRotatef(xAng, 0, 1, 0);

			//glScalef(x, y, z);
			glScalef(projectile_width, projectile_height, projectile_depth);

			//gluCylinder(quad, base radius, top radius, height, slice, stacks)
			gluCylinder(gluNewQuadric(), 0.5, 0.5, 1.0, 20, 1);

		glPopMatrix();
	}
}

void cannon_addProjectile()
{

	// Go through projectile list to see if there is an empty one
	for (int index = 0; index < cannon_maxProjectileNum; index++)
	{
		// If one is not active
		if (!projectile_active[index])
		{
			// Insert into array
			projectile_active[index] = true;
			projectile_xAng[index] = cannon_rotateX;
			projectile_yAng[index] = cannon_rotateY;
			projectile_xPos[index] = 0;
			projectile_yPos[index] = 0;
			projectile_zPos[index] = 0;

			if (cannon_projectileExists == false)
			{
				cannon_projectileExists = true;
				glutTimerFunc(10, cannon_projectileAnimationHandler, 0);
			}

			//cannon_printProjectileArray();
			return;
		}//if not active
	}//for index

}

void cannon_projectileAnimationHandler(int param)
{
	if (cannon_projectileExists)
	{
		for (int index = 0; index < cannon_maxProjectileNum; index++)
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
			if (projectile_active[index])
			{
				float toRad = M_PI / 180;

				float xAng = projectile_xAng[index];
				float yAng = projectile_yAng[index];
				float xPos = projectile_xPos[index];
				float yPos = projectile_yPos[index];
				float zPos = projectile_zPos[index];

				float xAdd = tan(-xAng * toRad) * cannon_projectileSpeed;
				float yAdd = sin(yAng * toRad) * cannon_projectileSpeed;
				float zAdd = cannon_projectileSpeed;

				xPos += xAdd;
				yPos += yAdd;
				zPos += zAdd;

				// Update array
				projectile_xPos[index] = xPos;
				projectile_yPos[index] = yPos;
				projectile_zPos[index] = zPos;

				// Deactivate if reached farplane
				if (projectile_zPos[index] >= farPlane)
					{ projectile_active[index] = false; }

				// Check for collision
				if (checkBotCollision(xPos, yPos, zPos))
					{ projectile_active[index] = false; }
			}

		}//for index

		glutPostRedisplay();
		glutTimerFunc(10, cannon_projectileAnimationHandler, 0);
	}//if projectile exists
}

void cannon_printProjectileArray()
{
	printf("\nAngle:\n");
	printf("   X:");
	for (int index = 0; index < cannon_maxProjectileNum; index++)
	{ if (projectile_active[index]) { printf(" %f", projectile_xAng[index]); }}
	printf("\n   Y:");
	for (int index = 0; index < cannon_maxProjectileNum; index++)
		{ if (projectile_active[index]) { printf(" %f", projectile_yAng[index]); }}
	printf("\nPosition:\n");
	printf("   X:");
	for (int index = 0; index < cannon_maxProjectileNum; index++)
		{ if (projectile_active[index]) { printf(" %f", projectile_xPos[index]); }}
	printf("\n   Y:");
	for (int index = 0; index < cannon_maxProjectileNum; index++)
		{ if (projectile_active[index]) { printf(" %f", projectile_yPos[index]); }}
	printf("\n   Z:");
	for (int index = 0; index < cannon_maxProjectileNum; index++)
		{ if (projectile_active[index]) { printf(" %f", projectile_zPos[index]); }}
	printf("\n");
}

void cannon_resetProjectileArray()
{
	for (int index = 0; index < cannon_maxProjectileNum; index++)
	{
		projectile_active[index] = false;
		projectile_xAng[index] = 0;
		projectile_yAng[index] = 0;
		projectile_xPos[index] = 0;
		projectile_yPos[index] = 0;
		projectile_zPos[index] = 0;
	}
}

#pragma once
