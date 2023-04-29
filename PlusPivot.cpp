#include<stdio.h>
#include<GL/glut.h>
#include <string.h>
#include <iostream>
using namespace std;

float ax =-10, ay = 30.0;
float bx = 10.0,by = 30.0;
float cx = 10.0,cy = 10+.0;
float dx = 30.0,dy = 10.0;
float ex = 30.0,ey = -10.0;
float fx = 10.0,fy = -10.0;
float gx = 10.0,gy = -60.0;
float hx = -10.0,hy = -60.0;
float ix =-10.0 ,iy = -10.0;
float jx = -30.0,jy = -10.0;
float kx =-30.0 ,ky = 10.0;
float lx =-10.0 ,ly = 10.0;

void draw(){
//    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
      glVertex2i(ax,ay);
      glVertex2i(bx,by);
      glVertex2i(cx,cy);
      glVertex2i(dx,dy);
      glVertex2i(ex,ey);
      glVertex2i(fx,fy);
      glVertex2i(gx,gy);
      glVertex2i(hx,hy);
      glVertex2i(ix,iy);
      glVertex2i(jx,jy);
      glVertex2i(kx,ky);
      glVertex2i(lx,ly);
    glEnd();
    glFlush();
    
}

void transformRotate (float deg, float xaxis, float yaxis, float zaxis) {
//	glTranslatef (5.0, 5.0, 0.0);
	glColor3f (0.0f, 0.0f, 1.0f);
	glRotatef (deg, xaxis, yaxis, zaxis);
	draw ();
}

void transformTranslate (float xaxis, float yaxis, float zaxis) {
	glColor3f (0.0f, 1.0f, 0.0f);
	glTranslatef (xaxis, yaxis, zaxis);
	draw ();
}

void transformScale (float xaxis, float yaxis, float zaxis) {
	glColor3f (1.0f, 0.0f, 0.0f);
	glScalef (xaxis, yaxis, zaxis);
	draw ();
}

void transformShear (float x, float y, float z) {
	glColor3f (0, 1, 0);
	if (x != 0) {
		ax+=ay*x; bx+=by*x; cx+=cy*x; dx+=dy*x; ex+=ey*x; fx+=fy*x;
		gx+=gy*x; hx+=hy*x; ix+=iy*x; jx+=jy*x; kx+=ky*x; lx+=ly*x;
	}
	if (y != 0) {
		ay+=ax*y; by+=bx*y; cy+=cx*y; dy+=dx*y; ey+=ex*y; fy+=fx*y;
		gy+=gx*y; hy+=hx*y; iy+=ix*y; jy+=jx*y; ky+=kx*y; ly+=lx*y;
	}
	draw ();
}

void transformReflect (float xaxis, float yaxis, float zaxis) {
	glColor3f (1.0f, 0.0f, 0.0f);
	if (xaxis == 1.0) {
		ay = -ay; by = -by; cy = -cy; dy = -dy;
		ey = -ey; fy = -fy; gy = -gy; hy = -hy;
		iy = -iy; jy = -jy; ky = -ky; ly = -ly;
	}
	if (yaxis == 1.0) {
		ax = -ax; bx = -bx; cx = -cx; dx = -dx;
		ex = -ex; fx = -fx; gx = -gx; hx = -hx;
		ix = -ix; jx = -jx; kx = -kx; lx = -lx;
	}
	draw ();
}
  
void display () {
	glColor3f (1.0, 1.0, 1.0);
	glLineWidth(5);
	glBegin(GL_LINES);
	  glVertex2i(-100,0);
	  glVertex2i(100,0);
	glEnd();
	glBegin(GL_LINES);
	  glVertex2i(0, -100);
	  glVertex2i(0, 100);
	glEnd();

    draw ();
    int opt;
    printf ("######################\n"
           	"######## MENU ########\n"
           	"######################\n"
           	"1. TRANSLATION\n"
		   	"2. SCALING\n"
		   	"3. SHEARING\n"
		   	"4. REFLECTION\n"
		   	"5. ROTATION\n"
			"######################\n"
			"> ");
    scanf (" %d", &opt);
    switch (opt) {
    	case 1:
        	transformTranslate (30, 30, 0);
        	break;
    	case 2:
        	transformScale (2.0, 1.5, 0.0);
        	break;
    	case 3:
    		transformShear (1.5, 0, 0);
        	break;
        case 4:
        	transformReflect (1.0, 0.0, 0.0);
        	break;
        case 5: 
			transformRotate (45.0, 0.0, 0.0, 1.0);
			break;
    }
}
  
void myinit(){   
    glClearColor(0.0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);
}
int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("EXAM CODE"); 
    
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
    return 0;
}
