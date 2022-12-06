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

#pragma once
