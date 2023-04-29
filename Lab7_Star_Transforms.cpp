/* draw a star  and perform

1. scaling with parameter(20x, 30y towards " " axis_
2. tranbslation with distance 10 towards x axis, 15 towardss y axis
3. reflection on x axis
4. share parameter 30 on x axis and 40 on y axis
5. rotation 90* clockwise */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

GLfloat R=490.0f, r=280.0f, pi=22/7;
GLfloat AX=0, AY=R, BX=R*cos(pi/10), BY=R*sin(pi/10), CX=R*sin(pi/5), CY=-1*R*cos(pi/5);
GLfloat DX=-1*CX, DY=CY, EX=-1*BX, EY=BY; // Original Points

GLfloat ax=r*cos(3*pi/10), ay=r*sin(3*pi/10), bx=r*cos(pi/10), by=-1*r*sin(pi/10), cx=0, cy=-1*r;
GLfloat dx=-1*bx, dy=by, ex=-1*ax, ey=ay;
  
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
void drawStar() {
	glBegin(GL_LINE_LOOP);
		glVertex2f(AX, AY);
		glVertex2f(ax, ay);
		glVertex2f(BX, BY);
		glVertex2f(bx, by);
		glVertex2f(CX, CY);
		glVertex2f(cx, cy);
		glVertex2f(DX, DY);
		glVertex2f(dx, dy);
		glVertex2f(EX, EY);
		glVertex2f(ex, ey);
	glEnd();	
	glFlush();
}
void Scale (float x, float y, float z) {
	glColor3f (1.0f, 0.0f, 0.0f); // red scale
	AY*=y; BY*=y; CY*=y; DY*=y; EY*=y; ay*=y; by*=y; cy*=y; dy*=y; ey*=y;
    AX*=x; BX*=x; CX*=x; DX*=x; EX*=x; ax*=x; bx*=x; cx*=x; dx*=x; ex*=x; 
	drawStar();
}
void Translate (float x, float y, float z) {
	glColor3f (0.0f, 1.0f, 0.0f); // green translate
	AY+=y; BY+=y; CY+=y; DY+=y; EY+=y; ay+=y; by+=y; cy+=y; dy+=y; ey+=y;
    AX+=x; BX+=x; CX+=x; DX+=x; EX+=x; ax+=x; bx+=x; cx+=x; dx+=x; ex+=x; 
	drawStar();
}
void Rotate (float deg, float x, float y, float z) {
	glRotatef(deg, x, y, z);
	glColor3f (0.0f, 0.0f, 1.0f);
	drawStar();
}
void Shear (float x, float y, float z) {
	glClear (GL_COLOR_BUFFER_BIT);
	drawAxes();
	glColor3f (1.0f, 1.0f, 1.0f);
	drawStar ();
	AX += y * AY;    ax += y * ay;
	BX += y * BY;    bx += y * by;
	CX += y * CY;    cx += y * cy;
	DX += y * DY;    dx += y * dy;
	EX += y * EY;    ex += y * ey;
	AY += x * AX;    ay += x * ax;
	BY += x * BX;    by += x * bx;
	CY += x * CX;    cy += x * cx;
	DY += x * DX;    dy += x * dx;
	EY += x * EX;    ey += x * ex;
	glColor3f (0.7f, 0.5f, 0.3f);
	drawStar();
}

void Reflect (int x, int y, int z) {
	if(x==1) { AY*= -1; BY*= -1; CY*= -1; DY*= -1; EY*= -1; ay*= -1; by*= -1; cy*= -1; dy*= -1; ey*= -1; }
	if(y==1) { AX*= -1; BX*= -1; CX*= -1; DX*= -1; EX*= -1; ax*= -1; bx*= -1; cx*= -1; dx*= -1; ex*= -1; }
	glColor3f(0.63f, 0.05f, 0.7f);
	drawStar(); // reflected star - violet
}
void myDisplay () {
	glLineWidth(6.0f);
	drawAxes();
	glColor3f (1.0f, 1.0f, 1.0f);
	drawStar (); // white
	
	Scale(0.4, 0.4, 0); //red
	Translate(200.0, 200.0, 0.0); //green
	
	Reflect(1, 0, 0); // violet
	Rotate(50.0, 0.0, 0.0, 1.0); // blue
//	Shear(1.2, 0.0, 0.0);
}
  
int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (100, 0);
    glutInitWindowSize (1000, 1000);
    glutCreateWindow ("2D TRANSFORMATION OVER THE STAR");
    glutDisplayFunc (myDisplay);
    myInit ();
    glutMainLoop ();
    return 0;
}
