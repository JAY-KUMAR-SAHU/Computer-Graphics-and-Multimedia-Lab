#include <iostream>
#include <GL/glut.h>
using namespace std;

double PX=200.0, PY=200.0;
double AX=200, AY=450, BX=300, BY=252, CX=320, CY=153, DX=248, DY=70;
double EX=152, EY=DY, FX=80, FY=CY, GX=100, GY=BY;

double xm=(AX+BX+CX+DX+EX+FX+GX)/7, ym=(AY+BY+CY+DY+EY+FY+GY)/7;

void drawHeptagon() {
	glBegin(GL_LINE_LOOP);
		glVertex2f(AX, AY);
		glVertex2f(BX, BY);
		glVertex2f(CX, CY);
		glVertex2f(DX, DY);
		glVertex2f(EX, EY);
		glVertex2f(FX, FY);
		glVertex2f(GX, GY);
	glEnd();	
	glFlush();
}
void myinit () {
	glClear (GL_COLOR_BUFFER_BIT);
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (-700, 700, -700, 700);
}
void drawQuadrants () {
	glPointSize (6.0f);   
	glColor3f (0.0f, 0.5f, 0.5f);
	
	glBegin (GL_LINE_LOOP);
    	glVertex3f (-700.0, 0.0, 0.0);
    	glVertex3f (700.0, 0.0, 0.0);
    glEnd ();
    
    glBegin (GL_LINE_LOOP);
    	glVertex3f (0.0, -700.0, 0.0);
    	glVertex3f (0.0, 700.0, 0.0);
    glEnd ();
}

void display () {
	glLineWidth(6.0f);
	glPointSize (12.0f);
	drawQuadrants();
	
	glColor3f (1.0f, 1.0f, 1.0f);
	drawHeptagon();
	
	printf("line 51 : %f %f\n", xm, ym);
	glBegin (GL_POINTS);
		glColor3f(1.0f, 1.0f, 1.0f); glVertex2d(xm, ym); // white
	glEnd ();
	
	// 1. Translate object to origin from its original position
	glTranslatef (-xm, -ym, 0.0);
	glColor3f (0, 1,0); // green
	drawHeptagon();
	
	// 2. Rotate the object about the origin
	float Rotation = -27;
	glTranslatef (PX, PY, 0.0f);
	glRotatef (Rotation, 0.0f, 0.0f, 1.0f);
	glTranslatef (-PX, -PY, 0.0f);
	glColor3f (1, 0, 0); // red
	drawHeptagon();
	
	// 3. Scale the object
	glTranslatef (PX, PY, 0.0f);
	glScalef (1.75, 1.75, 0);
	glTranslatef (-PX, -PY, 0.0f);
	glColor3f (0.0f, 0.0f, 1.0f); // blue
	drawHeptagon();
	
	// 4. Translate the object to its original position from origin.		
	glTranslatef (58, 180, 0);
	glColor3f (1, 1, 0); // yellow		
	drawHeptagon();
	
	glFlush ();
}

int main (int argc, char **argv) {
	glutInit (&argc, argv);
    glutInitWindowSize (1000, 1000);
    glutInitWindowPosition (200, 0);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow ("HEPTAGON");
	myinit ();
    glutDisplayFunc (display);
    glutMainLoop ();
    return 0;
}
