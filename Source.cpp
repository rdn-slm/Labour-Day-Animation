// Name: Raden Salma Humaira binti Muhammad Mun'im
// Matric No: A23CS0264
// Subject:  SECV2213-02 FUNDAMENTAL OF COMPUTER GRAPHICS
// Lecturer: Dr Goh Eg Su
// Assignment 1b

// Ref 1: https://community.khronos.org/t/color-tables/22518
#include <GL/glut.h> // Include the GLUT header file
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <fstream>
#include <thread>
#include <chrono>

#define PI 3.14159
#define MY_CIRCLE_LIST 1

float xPos = -0.9f;
float yPos = -0.45f;

// Rounding function using inline to reduce function call overhead
//inline GLint round(const GLfloat a) { return GLint(a + 0.5); }

// Setting to initial condition to our canvas
const int font = (int)GLUT_BITMAP_HELVETICA_18; // font style for diaplay text ()

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// Clear the background with white window

	glEnable(GL_POINT_SMOOTH);
	// Enable point to become anti-aliased instead of pixelated

	glMatrixMode(GL_PROJECTION);
	// Defining space using projection matrix

	glLoadIdentity();
	// Load the identity matric to reset drawing location
	// will allow gluOrtho2D() to make transformations without
	// stacking on previous matrix state

	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	// Sets up 2D ortographic viewing region

}
// Set the change size function on glutReshapeFunc() reshape function
void changeSize(int w, int h)
{
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	glViewport(0, 0, w, h);
	// Set the viewport to be the entire window

	glMatrixMode(GL_PROJECTION);
	// Defining space using projection matrix

	glLoadIdentity();
	// Load the identity matric to reset drawing location
	// will allow gluOrtho2D() to make transformations without
	// stacking on previous matrix state

	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
}

void wall()
{
	const float centerX = 0.0f, centerY = 0.0f;
	const float maxRadius = 1.5f;
	const int layers = 30;

	for (int i = 0; i < layers; ++i) {
		float t = (float)i / (float)(layers - 1);
		float size = maxRadius * (1.0f - t);
		// medium orchid color as base then multiply with the whiteness

		float r = (1.0f - t) * 0.576471f + t * 0.696f; // interpolate R
		float g = (1.0f - t) * 0.439216f + t * 0.696f; // interpolate G
		float b = (1.0f - t) * 0.858824f + t * 0.696f; // interpolate B

		glColor3f(r, g, b);

		glBegin(GL_QUADS);
		glVertex2f(centerX - size, centerY + size);
		glVertex2f(centerX + size, centerY + size);
		glVertex2f(centerX + size, centerY - size);
		glVertex2f(centerX - size, centerY - size);
		glEnd();
	}

}

void floor()
{
	// Draw the floor

	glBegin(GL_TRIANGLES);
	glColor3f(0.2f, 0.2f, 0.2f); // dark grey

	glVertex2f(-1.0f, -0.5f);
	glVertex2f(-1.0f, -1.0f);
	glVertex2f(-0.6f, -0.5f);

	glVertex2f(1.0f, -1.0f);
	glVertex2f(0.6f, -0.5f);
	glVertex2f(1.0f, -0.5f);

	glColor3f(0.680, 0.686, 0.736); // lilac

	glVertex2f(0.6f, -0.5f);
	glVertex2f(-0.6f, -0.5f);
	glVertex2f(0.0f, -0.75f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.680, 0.686, 0.736); // lilac
	glVertex2f(-0.6f, -0.5f);
	glVertex2f(-1.0f, -1.0f);
	glVertex2f(0.6f, -0.5f);
	glVertex2f(1.0f, -1.0f);

	glEnd();
}

void bed()
{
	// bed with 5 lines as its skeleton
	// and the mattress
	// with the blanket
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES);
	glColor3f(0.39f, 0.29f, 0.19f); //almost black
	glVertex2f(0.5f, -0.4f);
	glVertex2f(0.5f, -0.8f);

	glVertex2f(0.4f, -0.4f);
	glVertex2f(0.5f, -0.4f);

	glVertex2f(0.4f, -0.4f);
	glVertex2f(0.4f, -0.75f);

	glVertex2f(-0.4f, -0.7f);
	glVertex2f(-0.4f, -0.75f);

	glVertex2f(-0.5f, -0.7f);
	glVertex2f(-0.5f, -0.8f);

	glEnd();

	glBegin(GL_QUADS);

	glColor3f(0.600f, 0.652f, 0.756f); // dusty blue
	glVertex2f(0.4f, -0.6f);
	glVertex2f(0.5f, -0.7f);
	glVertex2f(-0.5f, -0.7f);
	glVertex2f(-0.4f, -0.6f);

	// pillow
	glColor3f(0.90f, 0.99f, 0.99f); // super light grey
	glVertex2f(0.3f, -0.6f);
	glVertex2f(0.4f, -0.6f);
	glVertex2f(0.48f, -0.68f);
	glVertex2f(0.38f, -0.68f);
	glEnd();
}

void person(GLfloat x, GLfloat y)
{
	float radius = 0.05;

	glColor3f(0.74902, 0.847059, 0.847059); // light blue shirt
	glBegin(GL_QUADS);
	glVertex2f(x - 0.04, y - 0.05);
	glVertex2f(x + 0.04, y - 0.05);
	glVertex2f(x + 0.04, y - 0.20);
	glVertex2f(x - 0.04, y - 0.20);

	glVertex2f(x - 0.04, y - 0.05);
	glVertex2f(x - 0.17, y - 0.15);
	glVertex2f(x - 0.14, y - 0.17);
	glVertex2f(x - 0.04, y - 0.10);

	glColor3f(0.3, 0.1, 0.1); // dark brown 
	glVertex2f(x - 0.10, y - 0.20);
	glVertex2f(x + 0.04, y - 0.20);
	glVertex2f(x + 0.04, y - 0.25);
	glVertex2f(x - 0.10, y - 0.25);
	glEnd();

	// Head (circle)
	glColor3f(1.0, 0.756, 0.628); // skin tone
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		float angle = 2 * PI * i / 100;
		glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
	}
	glEnd();

	// Nose (triangle)
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.756, 0.628); // skin tone
	glVertex2f(x - 0.01, y - 0.03);
	glVertex2f(x - 0.01, y + 0.01);
	glVertex2f(x - 0.1, y - 0.03);

	// Hair ikat
	glColor3f(0.2, 0.1, 0.0); // dark brown 
	glVertex2f(x + 0.02, y + 0.02);
	glVertex2f(x + 0.04, y + 0.06);
	glVertex2f(x + 0.1, y + 0.05);

	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i <= 50; i++)  // only half a circle
	{
		float angle = PI * i / 50; // Half-circle: from 0 to PI
		glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
	}
	glEnd();

	// Eye (line)
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0); // black
	glVertex2f(x + 0.01, y - 0.01);
	glVertex2f(x - 0.02, y - 0.01);

	glVertex2f(x - 0.015, y - 0.02);
	glVertex2f(x - 0.015, y - 0.01);
	glEnd();

}

void movePerson()
{
	glPushMatrix();
	person(0.3, -0.45);
	glPopMatrix();

	// Change position over time
	xPos += 0.001f;
	if (xPos > 1.0f) xPos = -1.0f; // Reset position once out of view
}

void blanket(GLfloat x, GLfloat y)
{
	float radius = 0.3;
	glColor3f(0.39f, 0.49f, 0.66f);  // blue

	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i <= 50; i++)
	{
		glVertex2f(x + (1.3 * radius * cos(i * PI / 50)),
			y + (0.5 * radius * sin(i * PI / 50)));
	}

	glEnd();
}


void ceiling()
{
	// trapezium
	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.2f, 0.2f); // dark grey
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(0.65f, 0.6f);
	glVertex2f(-0.65f, 0.6f);
	glEnd();

	// confettis
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.2f, 0.8f, 1.0f); // blue
	glVertex2f(0.1f, 0.8f);
	glVertex2f(-0.6f, 0.9f);
	glVertex2f(0.5f, 0.78f);

	glColor3f(0.8f, 0.1f, 0.8f); // neon pink
	glVertex2f(-0.15f, 0.9f);
	glVertex2f(0.30f, 0.69f);
	glVertex2f(0.78f, 0.85f);


	glColor3f(0.847059f, 0.74902f, 0.847059f); // thistle
	glVertex2f(0.45f, 0.87f);
	glVertex2f(-0.19f, 0.7f);
	glVertex2f(-0.33f, 0.75f);

	glEnd();
	glPointSize(1.0f);

}

void doctor()
{
	float centerX1 = xPos + 0.15f; // Center of cabinet 1
	//clothes 1 - doctor

	glColor3f(0.95f, 0.95f, 0.95f); // VVVLight Grey
	glBegin(GL_TRIANGLE_FAN);

	glVertex2f(centerX1, 0.15f);

	// Right side with sleeve
	glVertex2f(centerX1 + 0.06f, 0.12f);
	glVertex2f(centerX1 + 0.14f, 0.10f);
	glVertex2f(centerX1 + 0.14f, 0.05f);
	glVertex2f(centerX1 + 0.10f, 0.03f);
	glVertex2f(centerX1 + 0.12f, -0.10f);

	// Left side with sleeve
	glVertex2f(centerX1 - 0.12f, -0.10f);
	glVertex2f(centerX1 - 0.10f, 0.03f);
	glVertex2f(centerX1 - 0.14f, 0.05f);
	glVertex2f(centerX1 - 0.14f, 0.10f);
	glVertex2f(centerX1 - 0.06f, 0.12f);
	glEnd();

	//  sleeve cuffs
	glColor3f(0.458824f, 0.458824f, 0.458824f); // darker Grey
	glBegin(GL_LINE_LOOP);
	glVertex2f(centerX1 + 0.14f, 0.05f);
	glVertex2f(centerX1 + 0.10f, 0.03f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2f(centerX1 - 0.14f, 0.05f);
	glVertex2f(centerX1 - 0.10f, 0.03f);
	glEnd();

	//collar
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.95f, 0.95f, 0.95f); // VVVLight Grey
	glVertex2f(xPos + 0.15f, 0.12f); // Center
	glVertex2f(xPos + 0.18f, 0.15f);
	glVertex2f(xPos + 0.20f, 0.12f);
	glVertex2f(xPos + 0.20f, 0.10f);
	glVertex2f(xPos + 0.10f, 0.10f);
	glVertex2f(xPos + 0.10f, 0.12f);
	glVertex2f(xPos + 0.12f, 0.15f);
	glEnd();

	// pants
	glBegin(GL_QUADS);
	glVertex2f(xPos + 0.07f, -0.25f);
	glVertex2f(xPos + 0.07f, -0.10f);
	glVertex2f(xPos + 0.14f, -0.10f);
	glVertex2f(xPos + 0.14f, -0.25f);

	glVertex2f(xPos + 0.15f, -0.25f);
	glVertex2f(xPos + 0.15f, -0.10f);
	glVertex2f(xPos + 0.23f, -0.10f);
	glVertex2f(xPos + 0.23f, -0.25f);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	// to cover the shirt extension
	glColor3f(0.80f, 0.80f, 0.80f); // VLight Grey
	glVertex2f(centerX1, 0.14f);
	for (float angle = 0; angle <= 3.14159; angle += 0.2f) {
		glVertex2f(centerX1 + cos(angle) * 0.05f, 0.14f + sin(angle) * 0.04f);
	}
	glEnd();

	// For hanging clothes
	glBegin(GL_LINES);
	glColor3f(0.2f, 0.2f, 0.2f); // dark grey
	// rod 1
	glVertex2f(xPos + 0.3f, 0.2f);
	glVertex2f(xPos, 0.2f);

	//hook of the hanger 1
	glVertex2f(xPos + 0.15f, 0.2f);
	glVertex2f(xPos + 0.15f, 0.15f);

	// hanger 1
	// the left side
	glColor3f(0.0, 0.0, 0.0); //  black
	glVertex2f(xPos + 0.12f, 0.135f);
	glVertex2f(xPos + 0.15f, 0.15f);
	// the right side
	glVertex2f(xPos + 0.15f, 0.15f);
	glVertex2f(xPos + 0.18f, 0.135f);

	glColor3f(0.0, 0.0, 0.0); //  black

	// Stethoscope - 2 lines
	glLineWidth(2.0);
	glVertex2f(xPos + 0.10f, 0.12f);
	glVertex2f(xPos + 0.15f, 0.05f);

	glVertex2f(xPos + 0.15f, 0.05f);
	glVertex2f(xPos + 0.20f, 0.12f);

	// the trail
	glVertex2f(xPos + 0.15f, 0.05f);
	glVertex2f(xPos + 0.15f, 0.00f);
	glLineWidth(1.0);

	glColor3f(0.9, 0.9, 0.9); //  v light grey

	// Stethoscope upper part silver - 2 lines
	glVertex2f(xPos + 0.10f, 0.12f);
	glVertex2f(xPos + 0.13f, 0.08f);

	glVertex2f(xPos + 0.17f, 0.08f);
	glVertex2f(xPos + 0.20f, 0.12f);

	glEnd();

	// the chestpiece
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.89f, 0.897f, 0.867f); // grey mild
	for (float angle = 0; angle <= 2 * 3.14159; angle += 0.2f) {
		glVertex2f(xPos + 0.15f + cos(angle) * 0.01f, 0.00f + sin(angle) * 0.01f);
	}
	glEnd();

	// the earpiece left
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.89f, 0.897f, 0.867f); // grey mild
	for (float angle = 0; angle <= 2 * 3.14159; angle += 0.2f) {
		glVertex2f(xPos + 0.10f + cos(angle) * 0.019f, 0.12f + sin(angle) * 0.01f);
	}
	glEnd();

	// the earpiece right
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.89f, 0.897f, 0.867f); // grey mild
	for (float angle = 0; angle <= 2 * 3.14159; angle += 0.2f) {
		glVertex2f(xPos + 0.20f + cos(angle) * 0.019f, 0.12f + sin(angle) * 0.01f);
	}
	glEnd();

}

void fireman()
{
	float centerX2 = xPos + 0.75f; // Center of cabinet 2

	// clothes 2 - fireman
	glColor3f(0.9f, 0.25f, 0.0f); //orange
	glBegin(GL_TRIANGLE_FAN);

	glVertex2f(centerX2, 0.15f);

	// Right side with sleeve
	glVertex2f(centerX2 + 0.06f, 0.12f);
	glVertex2f(centerX2 + 0.14f, 0.10f);
	glVertex2f(centerX2 + 0.14f, 0.05f);
	glVertex2f(centerX2 + 0.10f, 0.03f);
	glVertex2f(centerX2 + 0.12f, -0.10f);

	// Left side with sleeve
	glVertex2f(centerX2 - 0.12f, -0.10f);
	glVertex2f(centerX2 - 0.10f, 0.03f);
	glVertex2f(centerX2 - 0.14f, 0.05f);
	glVertex2f(centerX2 - 0.14f, 0.10f);
	glVertex2f(centerX2 - 0.06f, 0.12f);
	glEnd();

	// sleeve cuffs
	glColor3f(0.95f, 0.08f, 0.01f); // darker orange
	glBegin(GL_LINE_LOOP);
	glVertex2f(centerX2 + 0.14f, 0.05f);
	glVertex2f(centerX2 + 0.10f, 0.03f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2f(centerX2 - 0.14f, 0.05f);
	glVertex2f(centerX2 - 0.10f, 0.03f);
	glEnd();

	//collar
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(xPos + 0.75f, 0.12f); // Center
	glVertex2f(xPos + 0.78f, 0.15f);
	glVertex2f(xPos + 0.80f, 0.12f);
	glVertex2f(xPos + 0.80f, 0.10f);
	glVertex2f(xPos + 0.70f, 0.10f);
	glVertex2f(xPos + 0.70f, 0.12f);
	glVertex2f(xPos + 0.72f, 0.15f);
	glEnd();

	// pants
	glColor3f(0.9f, 0.25f, 0.0f); //orange
	glBegin(GL_QUADS);
	glVertex2f(xPos + 0.67f, -0.25f);
	glVertex2f(xPos + 0.67f, -0.10f);
	glVertex2f(xPos + 0.74f, -0.10f);
	glVertex2f(xPos + 0.74f, -0.25f);

	glVertex2f(xPos + 0.75f, -0.25f);
	glVertex2f(xPos + 0.75f, -0.10f);
	glVertex2f(xPos + 0.82f, -0.10f);
	glVertex2f(xPos + 0.82f, -0.25f);
	glEnd();
	
	// to cover the shirt extension
	glColor3f(0.80f, 0.80f, 0.80f); // VLight Grey
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(centerX2, 0.14f);
	for (float angle = 0; angle <= 3.14159; angle += 0.2f) {
		glVertex2f(centerX2 + cos(angle) * 0.05f, 0.14f + sin(angle) * 0.04f);
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //  black
	glBegin(GL_LINES);

	// rod 2
	glVertex2f(xPos + 0.9f, 0.2f);
	glVertex2f(xPos + 0.6f, 0.2f);

	//hook of the hanger 2
	glVertex2f(xPos + 0.75f, 0.2f);
	glVertex2f(xPos + 0.75f, 0.15f);

	// hanger 2
	// the left side
	glVertex2f(xPos + 0.72f, 0.135f);
	glVertex2f(xPos + 0.75f, 0.15f);
	// the right side
	glVertex2f(xPos + 0.75f, 0.15f);
	glVertex2f(xPos + 0.78f, 0.135f);
	glEnd();

	// the helmet base
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.99f, 0.95f, 0.95f); //super very light grey
	for (float angle = 0; angle <=  PI; angle += 0.1f) {
		glVertex2f(xPos + 0.75f + cos(angle) * 0.08f, 0.20f + sin(angle) * 0.08);
	}
	glEnd();

	glLineWidth(3.0);
	glBegin(GL_LINES);
	glColor3f(0.1f, 0.15f, 0.15f); //super very dark grey
	glVertex2f(xPos + 0.75f, 0.28f);
	glVertex2f(xPos + 0.75f, 0.23f);

	// lining on the outfit
	// lining on clothes
	glColor3f(0.90f, 0.80f, 0.0f); //neon yellow
	glVertex2f(xPos + 0.75f, 0.10f);
	glVertex2f(xPos + 0.75f, -0.10f);

	glVertex2f(xPos + 0.63f, -0.10f);
	glVertex2f(xPos + 0.87f, -0.10f);

	//lining on pants
	glVertex2f(xPos + 0.67f, -0.23f);
	glVertex2f(xPos + 0.74f, -0.23f);

	glVertex2f(xPos + 0.75f, -0.23f);
	glVertex2f(xPos + 0.82f, -0.23f);

	glEnd();
	glLineWidth(1.0);


}

void policeman()
{
	float centerX3 = xPos + 1.35f; // Center of cabinet 3

	// clothes 3 - policeman
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.2, 0.20, 0.3); // dark grey with bluish tone

	// Right side with sleeve
	glVertex2f(centerX3 + 0.06f, 0.12f);
	glVertex2f(centerX3 + 0.14f, 0.10f);
	glVertex2f(centerX3 + 0.14f, 0.05f);
	glVertex2f(centerX3 + 0.10f, 0.03f);
	glVertex2f(centerX3 + 0.12f, -0.10f);

	// Left side with sleeve
	glVertex2f(centerX3 - 0.12f, -0.10f);
	glVertex2f(centerX3 - 0.10f, 0.03f);
	glVertex2f(centerX3 - 0.14f, 0.05f);
	glVertex2f(centerX3 - 0.14f, 0.10f);
	glVertex2f(centerX3 - 0.06f, 0.12f);
	glEnd();

	// sleeve cuffs
	glColor3f(0.15, 0.10, 0.35); // darker grey with bluish tone
	glBegin(GL_LINE_LOOP);
	glVertex2f(centerX3 + 0.14f, 0.05f);
	glVertex2f(centerX3 + 0.10f, 0.03f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2f(centerX3 - 0.14f, 0.05f);
	glVertex2f(centerX3 - 0.10f, 0.03f);
	glEnd();

	//collar
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(xPos + 1.35f, 0.12f); // Center
	glVertex2f(xPos + 1.38f, 0.15f);
	glVertex2f(xPos + 1.40f, 0.12f);
	glVertex2f(xPos + 1.40f, 0.10f);
	glVertex2f(xPos + 1.30f, 0.10f);
	glVertex2f(xPos + 1.30f, 0.12f);
	glVertex2f(xPos + 1.32f, 0.15f);
	glEnd();

	// pants
	glBegin(GL_QUADS);
	glColor3f(0.2, 0.20, 0.3); // dark grey with bluish tone
	glVertex2f(xPos + 1.27f, -0.25f);
	glVertex2f(xPos + 1.27f, -0.10f);
	glVertex2f(xPos + 1.34f, -0.10f);
	glVertex2f(xPos + 1.34f, -0.25f);

	glVertex2f(xPos + 1.35f, -0.25f);
	glVertex2f(xPos + 1.35f, -0.10f);
	glVertex2f(xPos + 1.43f, -0.10f);
	glVertex2f(xPos + 1.43f, -0.25f);
	glEnd();

	// to cover the shirt extension
	glColor3f(0.80f, 0.80f, 0.80f); // VLight Grey
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(centerX3, 0.14f);
	for (float angle = 0; angle <= 3.14159; angle += 0.2f) {
		glVertex2f(centerX3 + cos(angle) * 0.05f, 0.14f + sin(angle) * 0.04f);
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //  black
	glBegin(GL_LINES);
	// rod 3
	glVertex2f(xPos + 1.5f, 0.2f);
	glVertex2f(xPos + 1.2f, 0.2f);

	//hook of the hanger 3
	glVertex2f(xPos + 1.35f, 0.2f);
	glVertex2f(xPos + 1.35f, 0.15f);

	// hanger 3
	// the left side
	glVertex2f(xPos + 1.32f, 0.135f);
	glVertex2f(xPos + 1.35f, 0.15f);
	// the right side
	glVertex2f(xPos + 1.35f, 0.15f);
	glVertex2f(xPos + 1.38f, 0.135f);
	glEnd();

	// film of the beret
	glColor3f(0.3f, 0.3f, 0.3f); // dark grey
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(xPos + 1.37f, yPos + 0.68f);
	for (float angle = 0; angle <= 2 * 3.14159; angle += 0.2f) {
		glVertex2f(xPos + 1.37f + cos(angle) * 0.08f,
			yPos + 0.65f + sin(angle) * 0.015f);
	}
	glEnd();

	// base of the beret
	glColor3f(0.2, 0.20, 0.3); // dark grey with bluish tone
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(xPos + 1.37f, yPos + 0.68f); 

	for (float angle = 0; angle <= 2.09 * 3.14159; angle += 0.2f) {
		float yScale = (angle > 3.14159) ? 0.5f : 1.0f;
		glVertex2f(xPos + 1.38f + cos(angle) * 0.10f,  
			yPos + 0.68 + sin(angle) * 0.05 * yScale); 
	}
	glEnd();

}

void soldier()
{
	float centerX4 = xPos - 0.45f; // Center of cabinet 4
	// clothes 4 - soldier
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.184314	, 0.309804, 0.184314); // Dark green 

	// Right side with sleeve
	glVertex2f(centerX4 + 0.06f, 0.12f);
	glVertex2f(centerX4 + 0.14f, 0.10f);
	glVertex2f(centerX4 + 0.14f, 0.05f);
	glVertex2f(centerX4 + 0.10f, 0.03f);
	glVertex2f(centerX4 + 0.12f, -0.10f);

	// Left side with sleeve
	glVertex2f(centerX4 - 0.12f, -0.10f);
	glVertex2f(centerX4 - 0.10f, 0.03f);
	glVertex2f(centerX4 - 0.14f, 0.05f);
	glVertex2f(centerX4 - 0.14f, 0.10f);
	glVertex2f(centerX4 - 0.06f, 0.12f);
	glEnd();

	//  sleeve cuffs
	glColor3f(0.2, 0.3, 0.3); // Darker collar color
	glBegin(GL_LINE_LOOP);
	glVertex2f(centerX4 + 0.14f, 0.05f);
	glVertex2f(centerX4 + 0.10f, 0.03f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2f(centerX4 - 0.14f, 0.05f);
	glVertex2f(centerX4 - 0.10f, 0.03f);
	glEnd();

	// collar
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.1, 0.1, 0.1); // dark grey
	glVertex2f(xPos - 0.45f, 0.12f); // Center
	glVertex2f(xPos - 0.48f, 0.15f);
	glVertex2f(xPos - 0.50f, 0.12f);
	glVertex2f(xPos - 0.50f, 0.10f);
	glVertex2f(xPos - 0.40f, 0.10f);
	glVertex2f(xPos - 0.40f, 0.12f);
	glVertex2f(xPos - 0.42f, 0.15f);
	glEnd();

	// pants
	glColor3f(0.184314, 0.309804, 0.184314); // Dark green 
	glBegin(GL_QUADS);
	glVertex2f(xPos - 0.36f, -0.25f);
	glVertex2f(xPos - 0.36f, -0.10f);
	glVertex2f(xPos - 0.44f, -0.10f);
	glVertex2f(xPos - 0.44f, -0.25f);

	glVertex2f(xPos - 0.45f, -0.25f);
	glVertex2f(xPos - 0.45f, -0.10f);
	glVertex2f(xPos - 0.53f, -0.10f);
	glVertex2f(xPos - 0.53f, -0.25f);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	// to cover the shirt extension
	glColor3f(0.80f, 0.80f, 0.80f); // VLight Grey
	glVertex2f(centerX4, 0.14f);
	for (float angle = 0; angle <= 3.14159; angle += 0.2f) {
		glVertex2f(centerX4 + cos(angle) * 0.05f, 0.14f + sin(angle) * 0.04f);
	}
	glEnd();

	// belt
	glColor3f(0.1, 0.1, 0.1); // dark grey
	glBegin(GL_QUADS);
	glVertex2f(xPos - 0.56f, -0.04f);
	glVertex2f(xPos - 0.33f, -0.07f);
	glVertex2f(xPos - 0.34f, -0.03f);
	glVertex2f(xPos - 0.55f, 0.00f);
	glEnd();


	glColor3f(0.0, 0.0, 0.0); //  black
	glBegin(GL_LINES);
	// rod 4
	glVertex2f(xPos - 0.3f, 0.2f);
	glVertex2f(xPos - 0.6f, 0.2f);

	//hook of the hanger 4
	glVertex2f(xPos - 0.45f, 0.2f);
	glVertex2f(xPos - 0.45f, 0.15f);

	//hanger 4
	// the left side
	glVertex2f(xPos - 0.42f, 0.135f);
	glVertex2f(xPos - 0.45f, 0.15f);
	// the right side
	glVertex2f(xPos - 0.45f, 0.15f);
	glVertex2f(xPos - 0.48f, 0.135f);
	glEnd();

	// base of the beret
	glColor3f(0.13f, 0.37f, 0.31f); // hunter green
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(xPos - 0.45f, yPos + 0.68f);

	for (float angle = 0; angle <= 2.09 * 3.14159; angle += 0.2f) {
		float yScale = (angle > 3.14159) ? 0.5f : 1.0f;
		glVertex2f(xPos - 0.45f + cos(angle) * 0.10f,
			yPos + 0.68 + sin(angle) * 0.05 * yScale);
	}
	glEnd();


}

void closet()
{
	glBegin(GL_QUADS);
	// Draw rectangle for 4 closets

	glColor3f(0.80f, 0.80f, 0.80f); // VLight Grey
	glVertex2f(xPos, -0.3f);
	glVertex2f(xPos + 0.3f, -0.3f);
	glVertex2f(xPos + 0.3f, 0.3f);
	glVertex2f(xPos, 0.3f);

	glVertex2f(xPos + 0.6f, -0.3f);
	glVertex2f(xPos + 0.9f, -0.3f);
	glVertex2f(xPos + 0.9f, 0.3f);
	glVertex2f(xPos + 0.6f, 0.3f);

	glVertex2f(xPos + 1.2f, -0.3f);
	glVertex2f(xPos + 1.5f, -0.3f);
	glVertex2f(xPos + 1.5f, 0.3f);
	glVertex2f(xPos + 1.2f, 0.3f);

	glVertex2f(xPos - 0.6f, -0.3f);
	glVertex2f(xPos - 0.3f, -0.3f);
	glVertex2f(xPos - 0.3f, 0.3f);
	glVertex2f(xPos - 0.6f, 0.3f);
	glEnd();

	policeman();
	fireman();
	doctor();
	soldier();

}

void curtain()
{
	glBegin(GL_TRIANGLE_STRIP);

	// draw the curtain
	glColor3f(0.600f, 0.652f, 0.756f); // dusty blue
	glVertex2f(-0.55f, -0.65f);
	glVertex2f(-1.0f, -0.6f);

	glColor3f(0.184314f, 0.600f, 0.756f); // light steel blue
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(-0.55f, 1.0f);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	// draw the curtain
	glColor3f(0.600f, 0.652f, 0.756f); // dusty blue
	glVertex2f(0.55f, -0.68f);
	glVertex2f(1.0f, -0.6f);
	glColor3f(0.184314f, 0.600f, 0.756f); // light steel blue
	glVertex2f(1.0f, 1.0f);
	glVertex2f(0.55f, 1.0f);

	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.600f, 0.652f, 0.756f); // dusty 

	glVertex2f(0.8f, -0.55f);
	glVertex2f(1.5f, -0.55f);
	glVertex2f(0.75f, -0.70f);

	glVertex2f(-0.8f, -0.55f);
	glVertex2f(-0.75f, -0.70f);
	glVertex2f(-1.5f, -0.55f);

	glVertex2f(0.9f, -0.55f);
	glVertex2f(1.5f, -0.55f);
	glVertex2f(0.95f, -0.7f);

	glVertex2f(-0.9f, -0.55f);
	glVertex2f(-0.95f, -0.7f);
	glVertex2f(-1.5f, -0.55f);
	glEnd();

	// want to thicken the line for the ribbon
	glLineWidth(2.0f);

	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	// Left side
	glVertex2f(-1.0f, 0.33f);
	glVertex2f(-0.75f, 0.15f);
	glVertex2f(-0.85f, 0.22f);
	glVertex2f(-0.90f, 0.10f);
	glVertex2f(-0.85f, 0.22f);
	glVertex2f(-0.80f, 0.12f);

	// Right side
	glVertex2f(1.0f, 0.33f);
	glVertex2f(0.75f, 0.15f);
	glVertex2f(0.85f, 0.22f);
	glVertex2f(0.90f, 0.10f);
	glVertex2f(0.85f, 0.22f);
	glVertex2f(0.80f, 0.12f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	// Left end 1
	glVertex2f(-0.95f, 0.25f);
	glVertex2f(-0.85f, 0.22f);
	glVertex2f(-0.95f, 0.19f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	// Left end 2
	glVertex2f(-0.84f, 0.30f);
	glVertex2f(-0.85f, 0.22f);
	glVertex2f(-0.79f, 0.25f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	// Right end 1
	glVertex2f(0.95f, 0.25f);
	glVertex2f(0.85f, 0.22f);
	glVertex2f(0.95f, 0.19f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	// Right end 2
	glVertex2f(0.84f, 0.30f);
	glVertex2f(0.85f, 0.22f);
	glVertex2f(0.79f, 0.25f);
	glEnd();

	glLineWidth(1.0f);

}

// updating value for frame rate
void update(int value) {
	xPos += 0.001f;
	if (xPos > 1.0f) xPos = -1.0f;

	glutPostRedisplay();
	glutTimerFunc(160, update, 0);
}

void displayText(float x, float y, void* font, const char* string) {
	const char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Clear the color buffer and depth buffer

	glLoadIdentity();
	// Load Identity Matrix to reset drawing

	glMatrixMode(GL_MODELVIEW);
	// Use the Modelview Matrix

	// Call all the functions
	wall();
	floor();
	bed();
	movePerson();
	blanket(-0.1, -0.7);
	closet();
	curtain();
	ceiling();

	// Full text
	glColor3f(1.0f, 1.0f, 1.0f);	//white
	displayText(-0.2, 0.5, (void*)font, "Selamat Hari Pekerja!");
	displayText(-0.3, 0.4, (void*)font, "Silalah berehat untuk hari ini.");

	glFlush();
	// Flush the OpenGL buffers to the window

	glutPostRedisplay();
	// if change scene in current window

	glutSwapBuffers();

}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	// Initialize GLUT

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(720, 900);
	// Setting the width and height of the window

	glutInitWindowPosition(0, 0);
	// Set the position of the window

	glutCreateWindow("Selamat Hari Pekerja!");
	// Title for the window

	init();
	// Call the initial condition

	glutDisplayFunc(display);
	// Calling display function in the GLUT function

	glutReshapeFunc(changeSize);

	glutTimerFunc(0, update, 0);

	glutMainLoop();
	// Enters GLUT's main loop
	return 0;
}