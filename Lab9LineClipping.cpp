#include <GL/glut.h>

#include <iostream>
#include <string>
#include <math.h>
using namespace std;

void display();

float xmin = -3, ymin = -3, xmax = 3, ymax = 3;
float dx=xmax-xmin, dy=ymax-ymin;
float xc=(xmax+xmin)/2, yc=(ymax+ymin)/2;
float xd1, yd1, xd2, yd2;
float pts[8][2];

string to_string(int val){
	string s="", sign="";
	if(val<0){
		val*=-1;
		sign="-";
	}
	while(val){
		s+=(val%10+'0');
		val/=10;
	}
	string rev = string(s.rbegin(), s.rend());
	s=sign+rev;
	if(s.size()==0) s="0";
	return s;
}

void init(void){
    glClearColor(0.0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-20, 20, -20, 20);
}

int code(float x, float y){
    int c = 0;
    if (y > ymax) c = 8;
    if (y < ymin) c = 4;
    if (x > xmax) c = c | 2;
    if (x < xmin) c = c | 1;
    return c;
}

void mark_point(float x, float y, string s){
	float xoffset=.3,  yoffset=-.3;
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x + xoffset, y + yoffset);
    for (int i = 0; i < s.size(); i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
    }
}

void cohen_Line(int i,int j){
	float x1=pts[i][0],y1=pts[i][1],x2=pts[j][0],y2=pts[j][1];
	string s="";  s  +=" ("+ to_string(x1)+" ,"+to_string(y1)+")";
	string ss=""; ss +=" ("+ to_string(x2)+" ,"+to_string(y2)+")";

	mark_point(x1, y1, s);
   	mark_point(x2, y2,  ss);
    
	int c1 = code(x1, y1);
    int c2 = code(x2, y2);
    float m = (y2 - y1) / (x2 - x1);
    while ((c1 | c2) > 0){
        if ((c1 & c2) > 0){
            cout << "Completely outisde\n";
            return;
        }

        float xi = x1, yi = y1;
        int c = c1;
        if (c == 0){
            c = c2;
            xi = x2;
            yi = y2;
        }
        float x, y;
        if ((c & 8) > 0){
            y = ymax;
            x = xi + 1.0 / m * (ymax - yi);
        }
        else if ((c & 4) > 0){
            y = ymin;
            x = xi + 1.0 / m * (ymin - yi);
        }
        else if ((c & 2) > 0){
            x = xmax;
            y = yi + m * (xmax - xi);
        }
        else if ((c & 1) > 0){
            x = xmin;
            y = yi + m * (xmin - xi);
        }

        if (c == c1){
            xd1 = x;
            yd1 = y;
            c1 = code(xd1, yd1);
        }

        if (c == c2){
            xd2 = x;
            yd2 = y;
            c2 = code(xd2, yd2);
        }
    }
    if ((x1 == xd1 && y1 == yd1) && (x2 == xd2 && y2 == yd2)){
        cout << "Fully inside\n";
    }
    else{
        cout << "Partially clipped\n";
        cout << "Line Clipped at :\n";
        if (!(x1 == xd1 && y1 == yd1)){
        	string a="("+ to_string(xd1)+" ,"+to_string(yd1)+")";
        	mark_point(xd1, yd1, a);
            cout << "(" << xd1 << "," << yd1 << ")" << endl;
        }
        if (!(x2 == xd2 && y2 == yd2)){
        	string a="("+ to_string(xd2)+" ,"+to_string(yd2)+")";
        	mark_point(xd2, yd2, a);
            cout << "(" << xd2 << "," << yd2 << ")" << endl;
        }
    }
}

void draw_line(int i, int j){
	float xi=pts[i][0],yi=pts[i][1],xf=pts[j][0],yf=pts[j][1];
//	string s1=""; s1+="("+to_string(xi)+", "+to_string(yi)+")"; mark_point(xi, yi, s1);
//	s1=""; s1+="("+to_string(xf)+", "+to_string(yf)+")"; mark_point(xf, yf, s1);
    xd1 = xi, xd2 = xf, yd1 = yi, yd2 = yf;
    cohen_Line(i, j);
    int c1 = code(xi, yi);
    int c2 = code(xf, yf);
    if ((c1 & c2) > 0){
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2i(xi, yi);
        glVertex2i(xf, yf);
        glEnd();
    }
    else{
		glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
	        glVertex2i(xi, yi);
	        glVertex2i(xd1, yd1);
        glEnd();
        
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
	        glVertex2i(xi, yi);
	        glVertex2i(xd1, yd1);
        glEnd();
        
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
	        glVertex2i(xd1, yd1);
	        glVertex2i(xd2, yd2);
        glEnd();
        
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
	        glVertex2i(xd2, yd2);
	        glVertex2i(xf, yf);
        glEnd();
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
	    glVertex2i(xmin, ymin);
	    glVertex2i(xmin, ymax);
	    glVertex2i(xmax, ymax);
	    glVertex2i(xmax, ymin);
    glEnd();

    // Region Codes
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
	    glVertex2i(-10, ymin);
	    glVertex2i(10, ymin);
    glEnd();
    glBegin(GL_LINE_LOOP);
	    glVertex2i(-10, ymax);
	    glVertex2i(10, ymax);
    glEnd();
    glBegin(GL_LINE_LOOP);
	    glVertex2i(xmax, -10);
	    glVertex2i(xmax, 10);
    glEnd();
    glBegin(GL_LINE_LOOP);
	    glVertex2i(xmin, -10);
	    glVertex2i(xmin, 10);
    glEnd();

    mark_point(xc,yc,(char*)"0000");
	mark_point(xc-dx,yc,(char*)"0001");
	mark_point(xc+dx,yc,(char*)"0010");
	mark_point(xc+dx,yc+dy,(char*)"1010");
	mark_point(xc-dx,yc+dy,(char*)"1001");
	mark_point(xc,yc+dy,(char*)"1000");
	mark_point(xc+dx,yc-dy,(char*)"0110");
	mark_point(xc-dx,yc-dy,(char*)"0101");
	mark_point(xc,yc-dy,(char*)"0100");

   	cout << "BC: "; draw_line(1,2);
//   	cout << "CD: "; draw_line(2,3);
//	cout << "CF: "; draw_line(2,5);
	glFlush();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Cohen - Sutherland Algorithm");
    
	pts[0][0]=-5,  pts[0][1]=1;
	pts[1][0]=-7,  pts[1][1]=7;
	pts[2][0]=6,   pts[2][1]=2;
	pts[3][0]=5,   pts[3][1]=-1;
	pts[4][0]=-2,  pts[4][1]=2;
	pts[5][0]=2,   pts[5][1]=-2;
	pts[6][0]=2,   pts[6][1]=6;
	pts[7][0]=-2,  pts[7][1]=5;
    
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
