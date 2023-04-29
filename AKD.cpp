#include <stdio.h>
#include <GL/glut.h>

GLfloat V1X = 100.0f, V1Y = 100.0f, V1Z = 0.0f;
GLfloat V2X = 200.0f, V2Y = 100.0f, V2Z = 0.0f;
GLfloat V3X = 150.0f, V3Y = 200.0f, V3Z = 0.0f;
GLfloat xc=150.0f, yc=140.0f, r=70;


void myInit () {
	glClear (GL_COLOR_BUFFER_BIT);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glColor3f (1.0f, 0.0f, 0.0f);
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
 
void plot(int x, int y){
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc - y, yc - x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc + x, yc - y);
    glEnd();
}

void bresenham_circle(){
    int x = 0, y = r;
    int d = 3 - 2 * r;

    plot(x, y);

    while (x <= y)
    {
        if (d < 0)
        {
            d = d + 4 * x + 6;
        }
        else
        {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;

        plot(x, y);
    }
} 
void transformRotate (float deg, float xaxis, float yaxis, float zaxis) {
	glColor3f (0.0f, 0.0f, 1.0f);
	glRotatef (deg, xaxis, yaxis, zaxis);
	drawTriangle ();
}

void transformTranslate (float xaxis, float yaxis, float zaxis) {
	glColor3f (0.0f, 1.0f, 0.0f);
	glTranslatef (xaxis, yaxis, zaxis);
	drawTriangle ();
}

void transformScale (float xaxis, float yaxis, float zaxis) {
	glColor3f (1.0f, 0.0f, 0.0f);
	glScalef (xaxis, yaxis, zaxis);
	drawTriangle ();
}

void transformShear (float xaxis, float yaxis, float zaxis) {
	glColor3f (0.7f, 0.5f, 0.0f);
	if (xaxis != 0.0) {
		V1X += V1Y * xaxis; V2X += V2Y * xaxis; V3X += V3Y * xaxis;
		xc += yc * xaxis; xc += yc * xaxis; xc += yc * xaxis;
	}
	if (yaxis != 0.0) {
		V1Y += V1X * yaxis; V2Y += V2X * yaxis; V3Y += V3X * yaxis;
         	yc += xc * yaxis; yc += xc * yaxis; yc += xc * yaxis;
	}
	drawTriangle ();
}

void transformReflect (float xaxis, float yaxis, float zaxis) {
	glColor3f (0.0f, 0.5f, 0.2f);
	if (xaxis == 1.0) {
		V1Y = -V1Y; V2Y = -V2Y; V3Y = -V3Y;
			yc = -yc; 
	}
	if (yaxis == 1.0) {
		V1X = -V1X; V2X = -V2X; V3X = -V3X;
		xc=-xc;
	}
	drawTriangle ();
}
  
void myDisplay () {
		glColor3f (0.7, 0.0, 0.0);
		bresenham_circle();
	glColor3f (1.0, 0.0, 0.0);
	drawTriangle ();
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
        	transformTranslate (200.0, 200.0, 0.0);
        	break;
    	case 2:
        	transformScale (0.5, 0.5, 0.0);
        	break;
    	case 3:
    		transformShear (1.2, 0.0, 0.0);
        	break;
        case 4:
        	transformReflect (1.0, 0.0, 0.0);
        	break;
        case 5: 
			transformRotate (-45.0, 0.0, 0.0, 1.0);
			break;
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
