/* Program: skeleton_code3D.cpp
*
* This skeleton can be used as a starting
* point for most 3D applications.
*
*/

#ifdef __APPLE__
#include <unistd.h>
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/freeglut.h>
#endif

#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define WinW 500
#define WinH 500

float x_rotate = 0;
float y_rotate = 0;
float rotation_factor = 7;

float left_arm_rotate = 0;
float right_arm_rotate = 0;
float left_leg_rotate = 0;
float right_leg_rotate = 0;

bool animating = false;

// I used glutSolidCylinder for everything except the head. I rotated each individual part of the ragdoll so each cylinder is displayed correctly.
// Toggle animation mode by pressing the 'a' key.
// When not in animation mode, use the arrow keys to perform freeform rotation on each individual part.

// Dimension key:
//		1 = 0.1
//		2 = 0.2
//		3 = 0.3
//		4 = 0.4
//		5 = 0.5

void head() {
	glPushMatrix();

	glScalef(2, 3, 1);
	glutSolidSphere(0.10, 18, 8);		// The head is a sphere

	glPopMatrix();
}

void torso() {
	glPushMatrix();

	glRotatef(90, 1, 0, 0);

	// glutSolidCylinder(width,height,slices,stacks)
	// Each cylinder's height was off. I multiplied each height by 1.8x and that fixed the problem.

	glutSolidCylinder(0.20, 0.9, 18, 8);

	glPopMatrix();
}

void left_upper_arm() {
	// The computer user's left. (Ragdoll's right arm)
	glPushMatrix();
	
	glRotatef(-90, 0, 1, 0);
	glutSolidCylinder(0.10, 0.54, 18, 8);

	glPopMatrix();
}

void left_lower_arm() {
	glPushMatrix();

	glRotatef(-90, 0, 1, 0);
	glutSolidCylinder(0.10, 0.36, 18, 8);

	glPopMatrix();
}

void right_upper_arm() {
	// The computer user's right. (Ragdoll's left arm)
	glPushMatrix();
	
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(0.10, 0.54, 18, 8);

	glPopMatrix();
}

void right_lower_arm() {
	glPushMatrix();
	
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(0.10, 0.36, 18, 8);

	glPopMatrix();
}

void left_upper_leg() {
	// The computer user's left. (Ragdoll's right leg)
	glPushMatrix();
	
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(0.10, 0.54, 18, 8);

	glPopMatrix();
}

void left_lower_leg() {
	glPushMatrix();
	
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(0.10, 0.40, 18, 8);

	glPopMatrix();
}

void right_upper_leg() {
	// The computer user's right. (Ragdoll's left leg)
	glPushMatrix();
	
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(0.10, 0.54, 18, 8);

	glPopMatrix();
}

void right_lower_leg() {
	glPushMatrix();
	
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(0.10, 0.40, 18, 8);

	glPopMatrix();
}

void increase_rotation(int id) {
	// This function sets the interval for rotation.
	// This is only used when in animation mode.
	// This ensures that the ragdoll's parts go back and forth continuously.
	if (x_rotate >= 60) {
		rotation_factor = -3.5;
	}
	else if(x_rotate <= -60) {
		rotation_factor = 3.5;
	}

	x_rotate += rotation_factor;

	glutPostRedisplay();
}

void draw_objects() {

	glLoadIdentity();
	// Draw Head		--------------------
	glColor3f(1.00, 0.8784, 0.7412);
	glRotatef(x_rotate * 0.15, 1, 0, 0);		// Bob the head when animating
	glTranslatef(0, 1.2, 0);
	head();

	// Draw Torso		--------------------	
	glColor3f(0.25, 0.89, 0.30);
	glLoadIdentity();
	glTranslatef(0, 0.90, 0);
	glRotatef(x_rotate * 0.05, 1, 0, 0);		// Bob the torso when animating
	torso();

	// Draw Left Arm	--------------------

	// Draw Left Upper Arm
	glLoadIdentity();
	glColor3f(0.25, 0.89, 0.30);
	
	glTranslatef(-0.15, 0.7, 0);

	if (animating)
		glRotatef(x_rotate * 0.05 + 50, 0, 0, 1);		// Animation rotate
	else
		glRotatef(left_arm_rotate * 0.9, 0, 0, 1);		// Freeform rotate (when not animating)
														// Each element from here down has both an animation rotate and a freeform rotate.
	left_upper_arm();	

	// Draw Left Lower Arm
	glColor3f(1.00, 0.8784, 0.7412);
	glTranslatef(-0.52, 0, 0);

	if (animating)
		glRotatef(x_rotate * 0.05 + 80, 0, 0, 1);
	else
		glRotatef(left_arm_rotate * 0.9, 0, 0, 1);

	left_lower_arm();

	// Draw Right Arm	--------------------

	// Draw Right Upper Arm
	glLoadIdentity();
	glColor3f(0.25, 0.89, 0.30);
	glTranslatef(0.15, 0.7, 0);

	if (animating)
		glRotatef(x_rotate * 0.9, 0, 0, 1);
	else
		glRotatef(right_arm_rotate * 0.9, 0, 0, 1);

	right_upper_arm();

	// Draw Right Lower Arm
	glColor3f(1.00, 0.8784, 0.7412);
	glTranslatef(0.52, 0, 0);

	if (animating)
		glRotatef(x_rotate * 0.9, 0, 0, 1);
	else
		glRotatef(right_arm_rotate * 0.9, 0, 0, 1);

	right_lower_arm();

	// Draw Left Leg	--------------------

	// Draw Left Upper Leg
	glLoadIdentity();
	glColor3f(0.00, 0.4431, 0.8941);
	glTranslatef(-0.10, 0.02, 0);

	if (animating)
		glRotatef(-10 + x_rotate * 0.10, 0, 0, 1);
	else
		glRotatef(left_leg_rotate, 0, 0, 1);

	left_upper_leg();

	// Draw Left Lower Leg
	glTranslatef(0, -0.54, 0);

	if (animating)
		glRotatef(-x_rotate * 0.3, 0, 0, 1);
	else
		glRotatef(left_leg_rotate, 0, 0, 1);

	left_lower_leg();

	// Draw Right Leg	--------------------

	// Draw Right Upper Leg
	glLoadIdentity();
	glTranslatef(0.10, 0.02, 0);

	if (animating)
		glRotatef(10 + -x_rotate * 0.15, 0, 0, 1);
	else
		glRotatef(right_leg_rotate, 0, 0, 1);

	right_upper_leg();

	// Draw Right Lower Leg
	glTranslatef(0, -0.54, 0);

	if (animating)
		glRotatef(x_rotate * 0.25, 0, 0, 1);
	else
		glRotatef(right_leg_rotate, 0, 0, 1);

	right_lower_leg();
}

/*
*  This function is called whenever the display needs to redrawn.
*  First call when program starts.
*/
void Display(void)
{
	/* draw to the back buffer */
	glDrawBuffer(GL_BACK);

	/* clear the display */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	/* insert graphics code here that draws the scene */
	cout << "Display event occurred" << endl;

	if (animating) {
		glutTimerFunc(10, increase_rotation, 1);		// If animating, play the animation.
	}

	draw_objects();		// Draw the ragdoll.


	/* before returning, flush the graphics buffer
	* so all graphics appear in the window */
	glFlush();
	glutSwapBuffers();
}

/*
*  reshape event occurs when the user resizes
*  the window and when the window first pops up;
*  unregistered callback.
*/
void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
		2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat)w / (GLfloat)h,
		2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

/*
*  Mouse event occurs when a mouse button is pressed
*  OR released. The button parameter may be
*  GLUT_LEFT_BUTTON (0), GLUT_RIGHT_BOTTON (2), or
*  GLUT_MIDDLE_BUTTON (1). The state parameter is
*  GLUT_DOWN (0) if the mouse button was pressed, andq
*  GLUT_UP (1) if the mouse button was released.
*  (x,y) is the location of the mouse in the screen
*  window coordinate system.
*/
void Mouse(int button, int state, int x, int y)
{
	cout << "The mouse event occurred." << endl;
	cout << "button: " << button << endl;
	cout << "state:  " << state << endl;
	cout << "x:      " << x << endl;
	cout << "y:      " << y << endl;
}

/*
*  A keyboard event occurs when the user presses a key.
*/
void Keyboard(unsigned char key, int x, int y)
{
	cout << "Keyboard event occurred\n";
	cout << "key:    " << key << endl;
	cout << "x:      " << x << endl;
	cout << "y:      " << y << endl;

	switch (key)
	{
	case 'q':	exit(0);
	case 'a':	
		if (!animating) {				// If not animating, start animating.
			animating = true;
			glutPostRedisplay();
		}
		else {							// When the animation stops, reset the ragdoll's rotation values.
			animating = false;
			left_arm_rotate = 0.0;
			right_arm_rotate = 0.0;
			left_leg_rotate = 0.0;
			right_leg_rotate = 0.0;
		}
	}
}

/**
*  If you uncomment the glutSpecialFunc() call in the the main program,
*  then this will be called when the user presses certain special
*  keys on the keyboard, such  as the arrow keys and function keys.
*/
void special(int key, int x, int y) {
	// These controls allow for freeform rotation when not animating the ragdoll.
	// Controls:
	//	UP ARROW	= LEFT LEG
	//	DOWN ARROW	= RIGHT LEG
	//	LEFT ARROW	= LEFT ARM
	//	RIGHT ARROW = RIGHT ARM
	
	// The rotation for each part is fixed between two values. By holding down the up arrow, for example, the
	// left leg will rotate all the way to the left, then all the way to the right, etc...

	if (animating)
		return;
	if (key == GLUT_KEY_LEFT) {				// Left arm freeform
		if (left_arm_rotate >= 60)
			rotation_factor = -15;
		else if (left_arm_rotate <= -60) {
			rotation_factor = 15;
		}

		left_arm_rotate += rotation_factor;

		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_RIGHT) {		// Right arm freeform
		if (right_arm_rotate >= 60)
			rotation_factor = -15;
		else if (right_arm_rotate <= -60) {
			rotation_factor = 15;
		}

		right_arm_rotate += rotation_factor;

		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_UP) {			// Left leg freeform
		if (left_leg_rotate >= 60)
			rotation_factor = -15;
		else if (left_leg_rotate <= -60) {
			rotation_factor = 15;
		}

		left_leg_rotate += rotation_factor;

		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_DOWN) {		// Right leg freeform
		if (right_leg_rotate >= 60)
			rotation_factor = -15;
		else if (right_leg_rotate <= -60) {
			rotation_factor = 15;
		}

		right_leg_rotate += rotation_factor;

		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_HOME) {		// Reset the freeform rotation.
		left_arm_rotate = 0.0;
		right_arm_rotate = 0.0;
		left_leg_rotate = 0.0;
		right_leg_rotate = 0.0;
		glutPostRedisplay();
	}
}



/*
* An idle event is generated when no other
* event occurs.
*/
void Idle(void)
{
	cout << "Idle event occurred\n";
}

///*
//* Timer callback function.
//*/
//void Timer(int value)
//{
//	/* Set the next timer event to occur.
//	* The arguments 100, Timer, and 1 are
//	* the number of milliseconds until the
//	* event is triggered, the name of the
//	* function to invoke at that time, and
//	* the value to be passed to that function.
//	*/
//	
//}

/*
* Set window attributes
*/
void myInit()
{
	/* set color used when clearing the window to black */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* set drawing color to white */
	glColor3f(1.0, 1.0, 1.0);

	/* set up orthographic projection */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -10.0, 10.0);

	/* Enable hidden--surface--removal */
	// Enable shading
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
}

void main(int argc, char ** argv)
{
	/* initialize graphics window */
	glutInit(&argc, argv);

	/* need both double buffering and z buffer */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	/* set size of graphics window and position
	* of upper left corner on display */
	glutInitWindowSize(WinW, WinH);
	glutInitWindowPosition(0, 0);

	/* create the window */
	glutCreateWindow("Lab 5");

	/* register callback functions */
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);

	//glutIdleFunc(Idle);
	/* set window attributes */
	myInit();

	/* start event processing */
	glutMainLoop();
}