#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

GLfloat R=400, pi=22/7;
GLfloat AX=0, AY=R, DX=0, DY=-R, BX=R*cos(pi/6), BY=R*sin(pi/6);
GLfloat CX=BX, CY=-BY, EX=-BX, EY=-BY, FX=-BX, FY=BY; // Original Points
  
void drawAxes () {
	glPointSize (5.0);   
	glColor3f (0.0f, 0.5f, 0.5f);
	
	glBegin (GL_LINE_LOOP);
    	glVertex2f (-500.0, 0.0);
    	glVertex2f (500.0, 0.0);
    glEnd ();
    
    glBegin (GL_LINE_LOOP);
    	glVertex2f (0.0, -500.0);
    	glVertex2f (0.0, 500.0);
    glEnd ();
}
void myInit () {
	glClear (GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (-500, 500, -500, 500);
}
void drawHexagon() {
	glBegin(GL_LINE_LOOP);
		glVertex2f(AX, AY);
		glVertex2f(BX, BY);
		glVertex2f(CX, CY);
		glVertex2f(DX, DY);
		glVertex2f(EX, EY);
		glVertex2f(FX, FY);
	glEnd();	
	glFlush();
}
void Scale (float x, float y, float z) {
	glColor3f (1.0f, 0.0f, 0.0f); // red scale
	AY*=y; BY*=y; CY*=y; DY*=y; EY*=y; FY*=y;
    AX*=x; BX*=x; CX*=x; DX*=x; EX*=x; FX*=x; 
	drawHexagon();
}
void Translate (float x, float y, float z) {
	glColor3f (0.0f, 1.0f, 0.0f); // green translate
	AY+=y; BY+=y; CY+=y; DY+=y; EY+=y; FY+=y;
    AX+=x; BX+=x; CX+=x; DX+=x; EX+=x; FX+=x; 
	drawHexagon();
}
void Rotate (float deg, float x, float y, float z) {
	glRotatef(deg, x, y, z);
	glColor3f (0.0f, 0.0f, 1.0f);
	drawHexagon();
}
void Shear (float x, float y, float z) {
	glClear (GL_COLOR_BUFFER_BIT);
	drawAxes();
	glColor3f (1.0f, 1.0f, 1.0f);
	drawHexagon ();
	AX += y * AY; AY += x * AX;
	BX += y * BY; BY += x * BX;
	CX += y * CY; CY += x * CX;
	DX += y * DY; DY += x * DX;
	EX += y * EY; EY += x * EX;
	FX += y * FY; FY += x * FX;	
	
	glColor3f (0.7f, 0.5f, 0.3f);
	drawHexagon();
}

void Reflect (int x, int y, int z) {
	if(x==1) { AY*= -1; BY*= -1; CY*= -1; DY*= -1; EY*= -1; FY*= -1; }
	if(y==1) { AX*= -1; BX*= -1; CX*= -1; DX*= -1; EX*= -1; FX*= -1; }
	glColor3f(0.63f, 0.05f, 0.7f);
	drawHexagon(); // reflected - violet
}
void myDisplay () {
	glLineWidth(6.0f);
	drawAxes();
	glColor3f (1.0f, 1.0f, 1.0f);
	drawHexagon (); // white
	Rotate(50.0, 0.0, 0.0, 1.0); // blue
	Scale(0.4, 0.4, 0); //red
	Translate(225, 225, 225); //green
	
//	Reflect(0, 1, 0); // violet
	
//	Shear(1.2, 0.0, 0.0);
}
  
int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (100, 0);
    glutInitWindowSize (1000, 1000);
    glutCreateWindow ("2D TRANSFORMATION OVER THE HEXAGON");
    glutDisplayFunc (myDisplay);
    myInit ();
    glutMainLoop ();
    return 0;
}
