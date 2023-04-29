#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

float x1, x2, y1, y2;

void make_pixel(int x, int y){
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

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(6.0f);
	box_and_axes();
    
    float dy, dx, step, x, y, k, Xin, Yin;
    dx = x2-x1, dy = y2-y1;
	
    if (abs(dx) > abs(dy)) step = abs(dx);
    else step = abs(dy);
    
    Xin = dx/step, Yin = dy/step;
    x = x1, y = y1;
    make_pixel(x, y);
    for (k = 1; k <= step; k++){
        x += Xin, y += Yin;
        make_pixel(x, y);
    }
    glFlush();
}

void myInit(){
    glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5.0);
	gluOrtho2D(-500, 500, -500, 500);
}

int main(int argc, char **argv)
{
    printf("Value of x1, y1 : "); scanf("%f %f", &x1, &y1);
    printf("Value of x2, y2 : "); scanf("%f %f", &x2, &y2);
    printf("slope = %f\n", (y2-y1)/(x2-x1));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("DDA Line Drawing Algorithm");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();
}