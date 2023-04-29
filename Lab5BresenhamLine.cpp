#include <GL/freeglut.h>
#include <stdio.h>

int x1, y1, x2, y2;

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(6.0f);
	glPointSize(5.0);
	gluOrtho2D(-500, 500, -500, 500);
}

void draw_pixel(int x, int y) {
	glBegin(GL_POINTS);
		glColor3f(0.0f, 1.0f, 1.0f);
	    glVertex2i(x, y);
	glEnd();
}

void box_and_axes(){
	// x axis
	glBegin(GL_LINE_LOOP);
	    glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2i(-500, 0);
		glVertex2i(500, 0);
  	glEnd();
  	
  	// y axis
	glBegin(GL_LINE_LOOP);
	    glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2i(0, 500);
		glVertex2i(0, -500);
  	glEnd();
  	
  	// box
	glBegin(GL_LINE_LOOP);
	    glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2i(-500,500);
		glVertex2i(500, 500);
		glVertex2i(500, -500);
		glVertex2i(-500, -500);
  	glEnd();
}
void draw_line(int x1, int x2, int y1, int y2) {
	int dx = abs(x2-x1), dy = abs(y2-y1);
	int incx=1, incy=1, inc1, inc2;
	if (x2 < x1) incx = -1;
	if (y2 < y1) incy = -1;
	
	int x = x1, y = y1;
	if (dx > dy) {
		draw_pixel(x, y);
		int e = 2*dy - dx;
		inc1 = 2*(dy-dx), inc2 = 2*dy;
		for (int i=0; i<dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else e += inc2;
			x += incx;
			draw_pixel(x, y);
		}
	}
	else {
		draw_pixel(x, y);
		int e = 2*dx - dy;
		inc1 = 2*(dx-dy), inc2 = 2*dx;
		for (int i=0; i<dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else e += inc2;
			y += incy;
			draw_pixel(x, y);
		}
	}
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	box_and_axes();
	draw_line(x1, x2, y1, y2);
	glFlush();
}

int main(int argc, char **argv) {
	printf( "Enter (x1, y1, x2, y2)\n");
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	float slope = y2-y1;
	slope /= x2-x1;
	printf("slope = %f", slope);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Bresenham's Line Drawing Algorithm");
	myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}
