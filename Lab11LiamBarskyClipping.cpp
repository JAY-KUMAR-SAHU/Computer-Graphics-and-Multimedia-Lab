#include <GL/glut.h>
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

void display();
float xmin = -30, ymin = 40, xmax = 100, ymax = 120;
float xd1, yd1, xd2, yd2;
int N=200;
float pts[10][2];
double p[4], q[4];

string to_string(float val){
	string s="";
	char str[20];
	sprintf(str,"%.2f",val);
	int n=strlen(str);
	for(int i=0; i<n-1; i++) s+=str[i];
	return s;
}

void init(void){
    glClearColor(0.0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-200, N, N, -200);
}


void mark_point(float x, float y, string s){
	float xoffset=.3,  yoffset=-.3;
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x + xoffset, y + yoffset);
    for (int i = 0; i < s.size(); i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, s[i]);
    }
}

void clip(int x1, int y1, int x2, int y2){
	float t1 = 0, t2 = 1;
    int dx = x2 - x1, dy = y2 - y1, i;
    double t;
    p[0] = -dx; q[0] = x1 - xmin;
    p[1] = dx; q[1] = xmax - x1;
    p[2] = -dy; q[2] = y1 - ymin;
    p[3] = dy; q[3] = ymax - y1;

    for (i = 0; i < 4; i++){
        if (p[i] == 0 && q[i] < 0)
            return;
        if (p[i] < 0){
            t = (q[i]) / (p[i]);
            if (t > t1 && t < t2) t1 = t;
        }
        else if (p[i] > 0){
            t = (q[i]) / (p[i]);
            if (t > t1 && t < t2) t2 = t;
        }
    }
    if (t1 < t2){
        x1 = x1 + t1*(x2 - x1);
        y1 = y1 + t1*(y2 - y1);
        x2 = x1 + t2*(x2 - x1);
        y2 = y1 + t2*(y2 - y1);
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINES);
	        glVertex2i(x1, y1);
	        glVertex2i(x2, y2);
        glEnd();
    }
}

void draw_line(int i, int j){
	float xi=pts[i][0],yi=pts[i][1],xf=pts[j][0],yf=pts[j][1];
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(xi, yi);
        glVertex2i(xf, yf);
    glEnd();
    clip(xi, yi,xf,yf);
    
    string s="";s+=(i+'A');s+=" ("+ to_string(xi)+" ,"+to_string(yi)+")";
	string ss="";ss+=(j+'A');ss+=" ("+ to_string(xf)+" ,"+to_string(yf)+")";
	
	mark_point(xi,yi,s);
	mark_point(xf,yf,ss);    
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(4);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
	    glVertex2i(xmin, ymin);
	    glVertex2i(xmin, ymax);
	    glVertex2i(xmax, ymax);
	    glVertex2i(xmax, ymin);
    glEnd();
	
   	draw_line(0,1);
   	draw_line(2,3);
   	draw_line(4,5);
   	draw_line(6,7);
   	draw_line(8,9);
	glFlush();
}

int main(int argc, char **argv){
	pts[0][0]=40,  pts[0][1]=50;
	pts[1][0]=80,  pts[1][1]=-80;
	pts[2][0]=-120,  pts[2][1]=30;
	pts[3][0]=120,  pts[3][1]=100;
	pts[4][0]=-60,  pts[4][1]=150;
	pts[5][0]=-60,  pts[5][1]=-70;
	pts[6][0]=0,  pts[6][1]=80;
	pts[7][0]=-140,  pts[7][1]=80;
	pts[8][0]=-20,  pts[8][1]=60;
	pts[9][0]=-80,  pts[9][1]=30;

    cout << "------------------------------" << endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Liang Barsky Line Clipping Algorithm Clipping");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
