#include <GL/freeglut.h>

// -----------------
// --- Variables ---
// -----------------

const int vWidth = 650;		// Viewport width in pixels
const int vHeight = 500;	// Viewport height in pixels

GLdouble nearPlane = 0.10;	// 0.2		0.10
GLdouble farPlane = 250.0;	// 40.0		100.0

GLdouble eyeX = 0;
GLdouble eyeY = -10;
GLdouble eyeZ = 50;

GLdouble centerX = 0;
GLdouble centerY = -20.0;
GLdouble centerZ = 0;

GLfloat mouse_prevX;
GLfloat mouse_prevY;

#pragma once
