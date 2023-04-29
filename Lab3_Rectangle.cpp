#include<GL/freeglut.h>

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  	glBegin(GL_LINE_LOOP);
    	glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.4f, 0.2f);
    	glVertex2f(0.4f, 0.2f);
		glVertex2f(0.4f, -0.2f);
	glVertex2f(-0.4f, -0.2f);
  glEnd();

  glFlush();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(800, 500);
  glutCreateWindow("A Simple Rectangle");

  glutDisplayFunc(display);
  glutMainLoop();
}
