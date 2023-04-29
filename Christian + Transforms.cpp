#include <stdio.h>
#include <GL/glut.h>

GLfloat AX=-10, AY=30,
		BX=10, BY=30,
		CX=10, CY=10,
		DX=30, DY=10,
		EX=30, EY=-10,
		FX=10, FY=-10,
		GX=10, GY=-60,
		HX=-10, HY=-60,
		IX=-10, IY=-10,
		JX=-30, JY=-10,
		KX=-30, KY=10,
		LX=-10, LY=10;

void myInit () {
	glClear (GL_COLOR_BUFFER_BIT);
    glClearColor (0, 0, 0, 0);
    glColor3f (0, 0.5, 0.5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-8, 8, 8, 8);
    
    glBegin (GL_LINE_LOOP);
    	glVertex3f (-8,0,0);
    	glVertex3f (8, 0, 0);
    glEnd ();
    
    glBegin (GL_LINE_LOOP);
    	glVertex3f (0.0, -8, 0.0);
    	glVertex3f (0.0, 8, 0.0);
    glEnd ();
    
    glFlush ();
}
void draw() {
    glBegin (GL_LINE_LOOP);
    	glVertex2d(AX, AY);
    	glVertex2d(BX, BY);
    	glVertex2d(CX, CY);
    	glVertex2d(DX, DY);
    	glVertex2d(EX, EY);
    	glVertex2d(FX, FY);
    	glVertex2d(GX, GY);
    	glVertex2d(HX, HY);
    	glVertex2d(IX, IY);
    	glVertex2d(JX, JY);
    	glVertex2d(KX, KY);
    	glVertex2d(LX, LY);
    glEnd ();
//    glFlush ();
}
  
void transformRotate (float deg, float xaxis, float yaxis, float zaxis) {
	glColor3f (0, 0, 1);
	glRotatef (deg, xaxis, yaxis, zaxis);
	draw ();
}

void transformTranslate (float xaxis, float yaxis, float zaxis) {
	glColor3f (0, 1, 0);
	glTranslatef (xaxis, yaxis, zaxis);
	draw ();
}









void transformScale (float xaxis, float yaxis, float zaxis) {
	glColor3f (1, 0, 0);
	glScalef (xaxis, yaxis, zaxis);
	draw ();
}
















void transformShear (float x, float y, float z) {
	glColor3f (1, 0, 0);
	if (x != 0.0) { AX+=AY*x; BX+=BY*x; CX+=CY*x, DX+=DY*x; EX+=EY*x; FX+=FY*x;
	 GX+=GY*x; HX+=HY*x; IX+=IY*x; JX+=JY*x; KX+=KY*y; LX+=LY*x; }
	if (y != 0.0) {	AY+=AX*y; BY+=BX*y; CY+=CX*y, DY+=DX*y; EY+=EX*y; FY+=FX*y;
	 GY+=GX*y; HY+=HX*y; IY+=IX*y; JY+=JX*y; KY+=KX*y; LY+=LX*y;}
	draw ();
}

void transformReflect (float xaxis, float yaxis, float zaxis) {
	glColor3f (0.0, 0.5, 0.2);
	if (xaxis == 1.0) { AX*=-1; BX*=-1; CX*=-1; DX*=-1; EX*=-1; FX*=-1; GX*=-1; HX*=-1; IX*=-1; JX*=-1; KX*=-1; LX*=-1; }
	if (yaxis == 1.0) { AY*=-1; BY*=-1; CY*=-1; DY*=-1; EY*=-1; FY*=-1; GY*=-1; HY*=-1; IY*=-1; JY*=-1; KY*=-1; LY*=-1; }
	draw ();
}
  
void myDisplay () {
	glColor3f (1, 1, 1);
	draw();
    int opt;
//    printf ("\n ______MENU______\n0. EXIT\n1. TRANSLATION\n2. SCALING\n3. SHEARING\n"
//			"4. REFLECTION\n5. ROTATION\n######################\n>> ");
//    scanf ("%d", &opt);
//    switch (opt) {
//    	case 0:
//    		exit(1);
//    	case 1:
//        	transformTranslate (200.0, 200.0, 0.0); break;
//    	case 2:
//        	transformScale (0.5, 0.5, 0.0); break;
//    	case 3:
//    		transformShear (1.2, 0.0, 0.0); break;
//        case 4:
//        	transformReflect (1.0, 0.0, 0.0); break;
//        case 5: 
//			transformRotate (-45.0, 0.0, 0.0, 1.0); break;
//    }
}
  
int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (100,100);
    glutCreateWindow ("2D TRANSFORMATIONS ON PLUS");
    glutDisplayFunc (myDisplay);
    myInit ();
    glutMainLoop ();
    return 0;
}
