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

// Projectile Dimensions
float projectile_height = 0.3;
float projectile_width = 0.3;
float projectile_depth = 5;

// Cannon
GLfloat cannonMat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat cannonMat_specular[] = { 0.45, 0.55, 0.45, 1.0 };
GLfloat cannonMat_diffuse[] = { 0.2f, 0.2f, 0.2f, 0.2f };
GLfloat cannonMat_shininess[] = { 5.0F };

//Projectile
GLfloat projectileMat_ambient[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat projectileMat_specular[] = { 0.45, 0.55, 0.45, 1.0 };
GLfloat projectileMat_diffuse[] = { 0.1f, 0.1f, 0.1, 0.2f };
GLfloat projectileMat_shininess[] = { 5.0F };

//Functions
void generateBuffers();
void deleteBuffers();
void drawDefensiveCannon();
void exportCannonMesh();
void drawCannonProjectile();

// ------------
// --- Draw ---
// ------------

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

void drawCannonProjectile()
{
	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, projectileMat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, projectileMat_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, projectileMat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, projectileMat_shininess);

		glRotatef(botThree_robotAngle, 0.0, 1.0, 0.0);

		//glScalef(x, y, z);
		glScalef(projectile_width, projectile_height, projectile_depth);

		//glRotatef(angle, x, y, z)
		glRotatef(90.0, 0.0, 0.0, 1.0);

		//gluCylinder(quad, base radius, top radius, height, slice, stacks)
		gluCylinder(gluNewQuadric(), 0.5, 0.5, 1.0, 20, 1);
	glPopMatrix();
}

#pragma once
