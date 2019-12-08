#include <Windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

#define pi 3.1417
#define inc 0.003
#define radius 9
#define PacRadius 25
#define angle pi/2

static GLfloat spin = 0.0;
static GLfloat deltaz = 0.0;
static GLfloat deltax = 0.0;
static GLfloat deltay = 0.0;

void display();
void initialize();
void draw_PacBuddy();
void draw_Button();
void draw_Maze();
void draw_Pellet(int pelletRadius, int pelletX, int pelletY);
void handleButton(int button, int state, int x, int y);

static int index = -1;
static float mouthSize = 0.6;

const int numPellets = 43;
int pelletOn[numPellets] = { 0 };

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Mini - Pac");
	glutDisplayFunc(display);
	glutMouseFunc(handleButton);
	initialize();
	glutMainLoop();
}

int menuindex(int x, int y)
{
	if (x >= 65 && x <= 115 && y >= 45 && y <= 75)
	{
		return 1;
	}

	if(x >= 65 && x <= 115 && y >= 130 && y <= 160)
	{
		return 2;
	}
	if (x <= 45 && x <= 65 && y >= 90 && y <= 120)
	{
	    return 3;
	}
	if(x >= 115 && x <= 135 && y >= 90 && y <= 120)
	{
		return 4;
	}
	    return 100;

}

void draw_Pellet(int pelletRadius, int pellet, int pelletY)
{
	float theta;
	glBegin(GL_POLYGON);
	for (theta = 0.0; theta <= 2 * pi; theta += inc)
	{
		glColor4f(0.95, 0.95, 0.95, 0);
		glVertex2f(pellet + pelletRadius * cos(theta), pelletY + pelletRadius * sin(theta));
	}
	glEnd();
}

void draw_PacBuddy()
{
	float theta;

	//body
	glBegin(GL_POLYGON);
	for (theta = 0.0; theta <= 2 * pi; theta += inc)
	{
		glColor4f(1, 1, 0.3, 0);
		glVertex2f((PacRadius)* cos(theta), (PacRadius * sin(theta)));
	}glEnd();

	//mouth
	glBegin(GL_POLYGON);
	glColor4f(0, 0, 0, 0);
	glVertex2f(0, 0);
	for (theta = -mouthSize; theta <= mouthSize; theta += inc)
	{
		glColor4f(0, 0, 0, 0);
		glVertex2f((PacRadius)* cos(theta), (PacRadius)* sin(theta));
	}
	glEnd();
	glFlush();
}
void draw_Button()
{
	//corner box border
	glBegin(GL_POLYGON);
	glColor4f(1, 1, 1, 0);
	glVertex2i(-460, 450);
	glVertex2i(-460, 340);
	glVertex2i(-350, 340);
	glVertex2i(-350, 450);
	glEnd();

	//corner box
	glBegin(GL_POLYGON);
	glColor4f(0.3, 0.3, 0.3, 0);
	glVertex2i(-455, 455);
	glVertex2i(-455, 345);
	glVertex2i(-355, 345);
	glVertex2i(-355, 445);
	glEnd();

	//up down arrow line
	glBegin(GL_POLYGON);
	glColor3f(0.75, 0, 0);
	glVertex2i(-408, 430);
	glVertex2i(-408, 360);
	glVertex2i(-402, 360);
	glVertex2i(-402, 430);
	glEnd();

	//up arrow
	glBegin(GL_TRIANGLES);
	glColor3f(0.75, 0, 0);
	glVertex2i(-405, 440);
	glVertex2i(-415, 420);
	glVertex2i(-395, 420);
	glEnd();

	//down arrow
	glBegin(GL_TRIANGLES);
	glColor3f(0.75, 0, 0);
	glVertex2i(-405, 350);
	glVertex2i(-415, 370);
	glVertex2i(-395, 370);
	glEnd();

	//left and right arrow line
	glBegin(GL_POLYGON);
	glColor3f(0.75, 0, 0);
	glVertex2i(-445, 398);
	glVertex2i(-445, 392);
	glVertex2i(-365, 392);
	glVertex2i(-365, 398);
	glEnd();

	//left arrow
	glBegin(GL_TRIANGLES);
	glColor3f(0.75, 0, 0);
	glVertex2i(-450, 395);
	glVertex2i(-430, 405);
	glVertex2i(-430, 385);
	glEnd();

	//right arrow
	glBegin(GL_TRIANGLES);
	glColor3f(0.75, 0, 0);
	glVertex2i(-350, 395);
	glVertex2i(-380, 405);
	glVertex2i(-380, 385);
	glEnd();

	//center circle
	float t;
	glBegin(GL_POLYGON);
	for (t = 0.0; t <= 2 * pi; t += inc)
	{
		glColor4f(0.1, 0.1, 0.1, 1);
		glVertex2f(-405 + radius * cos(t), 395 + radius * sin(t));
	}
	glEnd();
	glFlush();

}
void draw_Maze()
{
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0.750);
	glVertex2i(45, 45);
	glVertex2i(45, 315);
	glVertex2i(315, 315);
	glVertex2i(315, 45);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0.75);
	glVertex2i(315, 45);
	glVertex2i(315, -315);
	glVertex2i(225, -315);
	glVertex2i(225, 45);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0.75);
	glVertex2i(315, -315);
	glVertex2i(-315, -315);
	glVertex2i(-315, -225);
	glVertex2i(225, -225);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0.75);
	glVertex2i(135, -45);
	glVertex2i(135, -135);
	glVertex2i(-135, -135);
	glVertex2i(-135, -45);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0.75);
	glVertex2i(-135, -45);
	glVertex2i(-135, 450);
	glVertex2i(-45, 450);
	glVertex2i(-45, -45);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0.75);
	glVertex2i(-135, 225);
	glVertex2i(-135, 315);
	glVertex2i(-450, 315);
	glVertex2i(-450, 225);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0.75);
	glVertex2i(-135, 225);
	glVertex2i(-135, 315);
	glVertex2i(-450, 315);
	glVertex2i(-450, 225);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0.75);
	glVertex2i(-450, 225);
	glVertex2i(-450, -450);
	glVertex2i(-405, -450);
	glVertex2i(-405, 225);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0.75);
	glVertex2i(-450, -450);
	glVertex2i(-450, -405);
	glVertex2i(450, -405);
	glVertex2i(450, -450);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0.75);
	glVertex2i(450, -405);
	glVertex2i(450, 450);
	glVertex2i(405, 450);
	glVertex2i(405, -405);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0.75);
	glVertex2i(405, 450);
	glVertex2i(405, 405);
	glVertex2i(-90, 405);
	glVertex2i(-90, 450);
	glEnd();
}

void translatePacBuddy()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (index == 1)
	{
		if (deltax == 0 && deltay <= 360)
		{
			deltay += 3;
			if (deltay > 360)
			{
				deltay = 360;
			}
		}
		if (deltax == 360 && deltay <= 360)
		{
			deltay += 3;
			if (deltay > 360)
			{
				deltay = 360;
			}
		}
		if (deltax == -360 && deltay <= 180)
		{
			deltay += 3;
			if (deltay > 180)
			{
				deltay = 180;
			}
		}
		if (deltax == -180 && deltay <= 180)
		{
			deltay += 3;
			if (deltay > 180)
			{
				deltay = 180;
			}
		}
		if (deltax == 180 && deltay <= 0)
		{
			deltay += 3;
			if (deltay > 0)
			{
				deltay = 0;
			}
		}
		
	}
	if (index == 2)//move down
	{
		if (deltax == 0 && deltay >= 0)
		{
			deltay -= 3;
			if (deltay < 0)
			{
				deltay = 0;
			}
		}
		if (deltax == 360 && deltay >= -360)
		{
			deltay -= 3;
			if (deltay <360)
			{
				deltay = -360;
			}
		}
		if (deltax == -360 && deltay >= -360)
		{
			deltay -= 3;
			if (deltay < -360)
			{
				deltay = -360;
			}
		}
		if (deltax == -180 && deltay >= -180)
		{
			deltay -= 3;
			if (deltay < -180)
			{
				deltay = -180;
			}
		}
		if (deltax == 180 && deltay >= -180)
		{
			deltay -= 3;
			if (deltay < -180)
			{
				deltay = -180;
			}
		}
	}
	if (index == 3) //move left
	{
		if (deltay == 360 && deltax >= 0)
		{
			deltax -= 3;
			if (deltax < 0)
			{
				deltax = 0;
			}
		}
		if (deltay == 180 && deltax >= 360)
		{
			deltax -= 3;
			if (deltax < -360)
			{
				deltax = -360;
			}
		}
		if (deltay == 0 && deltax >= 0)
		{
			deltax -= 3;
			if (deltax < 0)
			{
				deltax = 0;
			}
		}
		if (deltay == -180 && deltax >= -180)
		{
			deltax -= 3;
			if (deltax < -180)
			{
				deltax = -180;
			}
		}
		if (deltay == -360 && deltax >= -360)
		{
			deltax -= 3;
			if (deltax < -360)
			{
				deltax = -360;
			}
		}
	}
	if (index == 4)//move right
	{
		if (deltay == 360 && deltax <= 360)
		{
			deltax -= 3;
			if (deltax > 360)
			{
				deltax = 360;
			}
		}

		if (deltay == 180 && deltax <= -180)
		{
			deltax -= 3;
			if (deltax > -180)
			{
				deltax = -180;
			}
		}
		if (deltay == 0 && deltax <= 180)
		{
			deltax -= 3;
			if (deltax > 180)
			{
				deltax = 180;
			}
		}
		if (deltay == -180 && deltax <= 180)
		{
			deltax -= 3;
			if (deltax > 180)
			{
				deltax = 180;
			}
		}
		if (deltay == -360 && deltax <= 360)
		{
			deltax -= 3;
			if (deltax > 360)
			{
				deltax = 360;
			}
		}
	}

	//pac rotation
	if (index == 1)
	{
		spin = 90;
	}

	if (index == 2)
	{
		spin = 270;
	}
	if (index == 3)
	{
		spin = 180;
	}
	if (index == 4)
	{
		spin = 0;
	}

	//translate mini-pac
	glPushMatrix();
	glTranslatef(deltax, deltay, 0);
	glRotatef(spin, 0, 0, 1.0);
	draw_PacBuddy();
	glPopMatrix();

	//pellet switches
	if (deltax == 0 && deltay == 90)
		pelletOn[0] = 1;

	if (deltax == 0 && deltay == 180)
		pelletOn[1] = 1;

	if (deltax == 0 && deltay == 270)
		pelletOn[2] = 1;

	if (deltax == 0 && deltay == 360)
		pelletOn[3] = 1;

	if (deltax == 90 && deltay == 360)
		pelletOn[4] = 1;

	if (deltax == 180 && deltay == 360)
		pelletOn[5] = 1;

	if (deltax == 270 && deltay == 360)
		pelletOn[6] = 1;

	if (deltax == 360 && deltay == 360)
		pelletOn[7] = 1;

	if (deltax == 360 && deltay == 270)
		pelletOn[8] = 1;

	if (deltax == 360 && deltay == 180)
		pelletOn[9] = 1;

	if (deltax == 360 && deltay == 90)
		pelletOn[10] = 1;

	if (deltax == 360 && deltay == 0)
		pelletOn[11] = 1;

	if (deltax == 360 && deltay == -90)
		pelletOn[12] = 1;

	if (deltax ==360 && deltay == -180)
		pelletOn[13] = 1;

	if (deltax == 360 && deltay == -270)
		pelletOn[14] = 1;

	if (deltax == 360 && deltay == -360)
		pelletOn[15] = 1;

	if (deltax == 270 && deltay == -360)
		pelletOn[16] = 1;

}
