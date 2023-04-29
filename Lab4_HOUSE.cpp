#include<GL/freeglut.h>

void initGL () {
}

void display() {

  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.3f, 0.3f);
    glVertex2f(0.3f, 0.3f);
	glVertex2f(0.3f, -0.3f);
	glVertex2f(-0.3f, -0.3f);
  glEnd();
  
  glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 0.6f);
	glVertex2f(-0.3f, 0.3f);
    glVertex2f(0.3f, 0.3f);
  glEnd();
  
  glBegin(GL_LINE_LOOP); // door
    glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.2f, -0.3f);
    glVertex2f(-0.2f, 0.0f);
	glVertex2f(-0.1f, 0.0f);
	glVertex2f(-0.1f, -0.3f);
  glEnd();
  
  glBegin(GL_LINE_LOOP); // window
    glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 0.1f);
	glVertex2f(0.1f, 0.1f);
	glVertex2f(0.1f, 0.0f);
  glEnd();

  glFlush();
}


int main(int argc, char** argv) {


  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500, 300);
  glutCreateWindow("A Simple Rectangle");

  initGL ();
  glutDisplayFunc(display);

  glutMainLoop();
}
