#pragma once

#include <GL/glew.h>
#include <gl/glut.h>

#include "Window.h"
#include "BotThree.h"
#include "BotFour.h"
#include "Cannon.h"

// -----------------
// --- Variables ---
// -----------------
bool help = false;
void drawHelp();
void drawLeftText();
void drawRightText();
void drawCoordinates();
void drawCollisionBox(float, float, float, float, float, float);

// -----------------
// --- Functions ---
// -----------------
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
			sprintf_s(str, "Press F1 to hide\n\nStart: s\n\nReset: r\n\nCannon\n   Move: Mouse\n   Shoot: Space Bar");
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
			sprintf_s(str, "Robot Angle: %0.1f\n\nBotThree: One Angles\n   Body: %0.1f\n   Hip: %0.1f\n   Knee: %0.1f\n\nBotThree: Two Angles\n   Body: %0.1f\n   Hip: %0.1f\n   Knee: %0.1f\n\nBotFour: One Angles\n   Body: %0.1f\n   Hip: %0.1f\n   Knee: %0.1f\n\nBotFour: Two Angles\n   Body: %0.1f\n   Hip: %0.1f\n   Knee: %0.1f\n\nCannon Angle\n   X: %0.1f\n   Y: %0.1f", 
				botThree_robotAngle, botThree_bodyAngle, botThreeOne_rightHipAngle, botThreeOne_rightKneeAngle,
				botThree_bodyAngle, botThreeTwo_rightHipAngle, botThreeTwo_rightKneeAngle,
				botFour_bodyAngle, botFour_leftHipAngle, botFour_leftKneeAngle, 
				botFour_bodyAngle, botFour_leftHipAngle, botFour_leftKneeAngle,
				cannon_rotateX, cannon_rotateY);
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

void drawCollisionBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	GLfloat botThree_collision_mat_ambient[] = { 0.3f, 0.15f, 0.3f, 0.5f };
	GLfloat botThree_collision_mat_specular[] = { 0.3f, 0.15f, 0.3f, 0.5f };
	GLfloat botThree_collision_mat_diffuse[] = { 0.3f, 0.15f, 0.3f, 0.5f };
	GLfloat botThree_collision_mat_shininess[] = { 32.0F };

	glMaterialfv(GL_FRONT, GL_AMBIENT, botThree_collision_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, botThree_collision_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, botThree_collision_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, botThree_collision_mat_shininess);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//glDepthMask(GL_FALSE);

	//    v1-------v4        Y
	//     /|     /|         |
	//    / |    / |         |____ X
	//  v2-------v3|          \
	//   |v5|___|__|v8         \
	//   |  /   | /             Z
	//   | /    |/
	// v6‾‾‾‾‾‾‾‾v7
	glPushMatrix();
		glBegin(GL_QUADS);
			//Top
			glVertex3f(xMin, yMax, zMin);	//v1
			glVertex3f(xMin, yMax, zMax);	//v2
			glVertex3f(xMax, yMax, zMax);	//v3
			glVertex3f(xMax, yMax, zMin);	//v4
		glEnd();

		glBegin(GL_QUADS);
			//Bottom
			glVertex3f(xMin, yMin, zMin);	//v5
			glVertex3f(xMin, yMin, zMax);	//v6
			glVertex3f(xMax, yMin, zMax);	//v7
			glVertex3f(xMax, yMin, zMin);	//v8
		glEnd();

		glBegin(GL_QUADS);
			//Front
			glVertex3f(xMin, yMax, zMax);	//v2
			glVertex3f(xMax, yMax, zMax);	//v3
			glVertex3f(xMax, yMin, zMax);	//v7
			glVertex3f(xMin, yMin, zMax);	//v6
		glEnd();

		glBegin(GL_QUADS);
			//Back
			glVertex3f(xMin, yMax, zMin);	//v1
			glVertex3f(xMax, yMax, zMin);	//v4
			glVertex3f(xMax, yMin, zMin);	//v8
			glVertex3f(xMin, yMin, zMin);	//v5
		glEnd();

		glBegin(GL_QUADS);
			//Right
			glVertex3f(xMin, yMax, zMin);	//v1
			glVertex3f(xMin, yMax, zMax);	//v2
			glVertex3f(xMin, yMin, zMax);	//v6
			glVertex3f(xMin, yMin, zMin);	//v5
		glEnd();

		glBegin(GL_QUADS);
			//Left
			glVertex3f(xMax, yMax, zMin);	//v4
			glVertex3f(xMax, yMax, zMax);	//v3
			glVertex3f(xMax, yMin, zMax);	//v7
			glVertex3f(xMax, yMin, zMin);	//v8
		glEnd();
	glPopMatrix();

	//glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

#pragma once
