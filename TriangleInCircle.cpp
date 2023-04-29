#include <windows.h>
#include <GL/glut.h>
#include<stdio.h>

float x,y,radius=50,rx=0,ry=0;

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


void draw_pixel_a(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x+rx+10, y+ry+23);
	glVertex2i(y+rx+10, x+ry+23);
	glVertex2i(y+rx+10, -x+ry+23);
	glVertex2i(x+rx+10, -y+ry+23);
	glVertex2i(-x+rx+10, y+ry+23);
	glVertex2i(-y+rx+10, x+ry+23);
	glVertex2i(-x+rx+10, -y+ry+23);
	glVertex2i(-y+rx+10, -x+ry+23);
	glEnd();
}

void draw_circle_midpoint(int r) {
	int p=1-r;
	int xp=0,yp=r;
	draw_pixel(xp,yp);
	while(xp<yp){
		if(p<=0){
			xp++;
			draw_pixel_a(xp,yp);
			p+=2*(xp)+1;
		}
		else{
			xp++;
			yp--;
			draw_pixel_a(xp,yp);
			p+=2*xp+1-2*yp;
		}
	}
}
void draw_circle_brasenheim(int r) {
	int p=3-2*r;
	int xp=0,yp=r;
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

float x1,x2,x3,y1,y2,y3;
void initGL() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-200, 200,-200,200);
}


void original(){
	glBegin(GL_LINE_LOOP);
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex2f(x1,y1);
      glVertex2f(x2,y2);
      glVertex2f(x3,y3);
   glEnd();
}

void translate(){
	glTranslatef(10.0f,23.0f,0.0f);
	glBegin(GL_LINE_LOOP);
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex2f(x1,y1);
      glVertex2f(x2,y2);
      glVertex2f(x3,y3);
   glEnd();
}

void scale(){
	glScalef(4, 4, 1);
	glBegin(GL_LINE_LOOP);
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex2f(x1,y1);
      glVertex2f(x2,y2);
      glVertex2f(x3,y3);
   	glEnd();
   	
}

void rotate(){
	glRotatef(-90, 0.0f,0.0f,1.0f);
	glBegin(GL_LINE_LOOP);
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex2f(x1,y1);
      glVertex2f(x2,y2);
      glVertex2f(x3,y3);
   glEnd();
}

void reflection(){
	GLfloat m[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
	};
	glMultMatrixf(m);
	glBegin(GL_LINE_LOOP);
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex2f(x1,y1);
      glVertex2f(x2,y2);
      glVertex2f(x3,y3);
   glEnd();
}

void shearing(){
	GLfloat m[16] = {
    1.0f, 2.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
	};
	glMultMatrixf(m);
	glBegin(GL_LINE_LOOP);
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex2f(x1,y1);
      glVertex2f(x2,y2);
      glVertex2f(x3,y3);
   glEnd();
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   draw_circle_brasenheim(radius);
   draw_circle_midpoint(radius);
   original();
   translate();
   glFlush();  
}

void display2() {
   glClear(GL_COLOR_BUFFER_BIT);
   draw_circle_brasenheim(radius);
   x3 -= 4; x2 += 4;
   draw_circle_brasenheim(radius+10);
   original();
   scale();
   glFlush();  
}

void display3() {
   glClear(GL_COLOR_BUFFER_BIT);
   draw_circle_brasenheim(radius);
   original();
   rotate();
   glFlush();  
}

void display4() {
   glClear(GL_COLOR_BUFFER_BIT);
   draw_circle_brasenheim(radius);
   original();
   reflection();
   glFlush();  
}

void display5(){
   glClear(GL_COLOR_BUFFER_BIT);
//   draw_circle_brasenheim(radius);
   original();
   shearing();
   glFlush();
}

int main(int argc, char** argv) {
   x1 = 0, y1 = 50, x2 = -43, y2 = -25, x3 = 43, y3 = -25;
   int choice;
   printf("Enter the choice for transformation\n");
   printf("1. Translation\n");
   printf("2. Scaling\n");
   printf("3. Rotation\n");
   printf("4. Reflection\n");
   printf("5. Shearing\n");
   scanf("%d",&choice);
   glutInit(&argc, argv);
   glutCreateWindow("Triangle Transformation");
   glutInitWindowSize(1600, 900);
   glutInitWindowPosition(0, 0);
   glLineWidth(3);
   glPointSize(3);
   if (choice ==1){
   		glutDisplayFunc(display);
   }
    else if (choice ==2){
    	glutDisplayFunc(display2);
	}
	else if(choice ==3){
		glutDisplayFunc(display3);
	}
	else if(choice ==4){
		glutDisplayFunc(display4);
	}
	else if(choice == 5){
		glutDisplayFunc(display5);
	}
	else{
		printf("Invalid Input");
		return 0;
	}
   	initGL();
   	glutMainLoop();
   return 0;
}
