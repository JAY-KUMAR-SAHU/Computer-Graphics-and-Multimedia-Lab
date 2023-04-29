#include <stdio.h>
#include <GL/glut.h>

GLfloat V1X = 100.0f, V1Y = 100.0f, V1Z = 0.0f,
		V2X = 200.0f, V2Y = 100.0f, V2Z = 0.0f,
		V3X = 150.0f, V3Y = 200.0f, V3Z = 0.0f;

void myInit () {
	glClear (GL_COLOR_BUFFER_BIT);
    glClearColor (0, 0, 0, 0);
    glColor3f (0, 0.5, 0.5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-500, 500, -500, 500);
    
    glBegin (GL_LINE_LOOP);
    	glVertex3f (-400.0, 0.0, 0.0);
    	glVertex3f (400.0, 0.0, 0.0);
    glEnd ();
    
    glBegin (GL_LINE_LOOP);
    	glVertex3f (0.0, -400.0, 0.0);
    	glVertex3f (0.0, 400.0, 0.0);
    glEnd ();
    
    glFlush ();
}

void drawTriangle () {
    glBegin (GL_TRIANGLES);
    	glVertex3f (V1X, V1Y, V1Z);
    	glVertex3f (V2X, V2Y, V2Z);
    	glVertex3f (V3X, V3Y, V3Z);
    glEnd ();
    glFlush ();
}
  
void transformRotate (float deg, float xaxis, float yaxis, float zaxis) {
	glColor3f (0, 0, 1);
	glRotatef (deg, xaxis, yaxis, zaxis);
	drawTriangle ();
}

void transformTranslate (float xaxis, float yaxis, float zaxis) {
	glColor3f (0, 1, 0);
	glTranslatef (xaxis, yaxis, zaxis);
	drawTriangle ();
}

void transformScale (float xaxis, float yaxis, float zaxis) {
	glColor3f (1, 0, 0);
	glScalef (xaxis, yaxis, zaxis);
	drawTriangle ();
}

void transformShear (float xaxis, float yaxis, float zaxis) {
	glColor3f (1, 0, 0);
	if (xaxis != 0.0) { V1X += V1Y * xaxis; V2X += V2Y * xaxis; V3X += V3Y * xaxis; }
	if (yaxis != 0.0) {	V1Y += V1X * yaxis; V2Y += V2X * yaxis; V3Y += V3X * yaxis;}
	drawTriangle ();
}

void transformReflect (float xaxis, float yaxis, float zaxis) {
	glColor3f (0.0, 0.5, 0.2);
	if (xaxis == 1.0) { V1Y = -V1Y; V2Y = -V2Y; V3Y = -V3Y; }
	if (yaxis == 1.0) { V1X = -V1X; V2X = -V2X; V3X = -V3X; }
	drawTriangle ();
}
  
void myDisplay () {
	glColor3f (1, 1, 1);
	drawTriangle ();
    int opt;
    printf ("\n ______MENU______\n0. EXIT\n1. TRANSLATION\n2. SCALING\n3. SHEARING\n"
			"4. REFLECTION\n5. ROTATION\n######################\n>> ");
    scanf ("%d", &opt);
    switch (opt) {
    	case 0:
    		exit(1);
    	case 1:
        	transformTranslate (200.0, 200.0, 0.0); break;
    	case 2:
        	transformScale (0.5, 0.5, 0.0); break;
    	case 3:
    		transformShear (1.2, 0.0, 0.0); break;
        case 4:
        	transformReflect (1.0, 0.0, 0.0); break;
        case 5: 
			transformRotate (-45.0, 0.0, 0.0, 1.0); break;
    }
}
  
int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (500, 0);
    glutInitWindowSize (1000, 1000);
    glutCreateWindow ("2D TRANSFORMATION OVER THE TRIANGLE");
    glutDisplayFunc (myDisplay);
    myInit ();
    glutMainLoop ();
    return 0;
}
