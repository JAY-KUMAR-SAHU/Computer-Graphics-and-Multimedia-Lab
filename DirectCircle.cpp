#include <GL/freeglut.h>
#include <math.h>

void display() {
	glClear(GL_COLOR_BUFFER_BIT);  
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(5);
	double x = 100, y = 100, rx=130, ry=100;
	glBegin(GL_POINTS);
		glVertex2f(rx, ry);
		glVertex2f(0, 0);
	glEnd();	
	glBegin(GL_LINE_LOOP);
		glColor3f(0, 0, 1);
		for (int i = 0; i <= 360; i++) {
		    glVertex2f(rx + x * sin(i*0.01746), ry + y * cos(i*0.01746));
		}
	glEnd();
	glFlush();
}

void myinit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500, 500, -500, 500);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("DIRECT CIRCLE");
	glutDisplayFunc(display);

	myinit();
	glutMainLoop();
}

