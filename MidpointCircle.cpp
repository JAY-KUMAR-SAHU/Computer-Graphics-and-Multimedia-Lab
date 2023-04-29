#include<GL/freeglut.h>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

float x,y,radius=50,rx=10,ry=25;


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
 
void draw_pixel(int x, int y) {
	glBegin(GL_POINTS);
		glVertex2i(x+rx, y+ry);
		glVertex2i(y+rx, x+ry);
		glVertex2i(y+rx, -x+ry);
		glVertex2i(x+rx, -y+ry);
		glVertex2i(-x+rx, y+ry);
		glVertex2i(-y+rx, x+ry);
		glVertex2i(-x+rx, -y+ry);
		glVertex2i(-y+rx, -x+ry);
	glEnd();
}

void draw_circle_midpoint(int r) {
	int p=1-r, xp=0, yp=r;
	draw_pixel(xp,yp);
	while(xp<yp){
		if(p<=0){
			xp++;
			draw_pixel(xp,yp);
			p+=2*(xp)+1;
		}
		else{
			xp++;
			yp--;
			draw_pixel(xp,yp);
			p+=2*xp + 1-2*yp;
		}
	}
}
void draw_circle_brasenham(int r) {
	int p=3-2*r, xp=0,yp=r;
	draw_pixel(xp,yp);
	while(xp<yp){
		if(p<=0){
			xp++;
			draw_pixel(xp,yp);
			p+=4*(xp-1)+6;
		}
		else{
			xp++;
			yp--;
			draw_pixel(xp,yp);
			p+=4*(xp-yp-2)+10;
		}
	}
}

void myDisplay() {
	glPointSize(5);
	glLineWidth(6.0f);
	box_and_axes();
	
	glBegin(GL_POINTS);
		glVertex2f(rx, ry);
	glEnd();
	
	draw_circle_brasenham(radius);
//	draw_circle_midpoint(radius);
	glFlush();
}
 
void init(void){
	glClearColor(0.7,0.7,0.7,0.7);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100,100,-100,100);
}
 
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (0,0);
	glutCreateWindow ("Brasenham Line Algo");
	init();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
