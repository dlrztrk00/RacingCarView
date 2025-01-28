/*********
   CTIS164 - HW1
----------
STUDENT : Dilara Öztürk
SECTION : 01
HOMEWORK: 1
----------
PROBLEMS:
----------
ADDITIONAL FEATURES:

I created two cars -> drawCar, drawCar2
I added two clouds moving in the opposite direction of the car -> drawCloud, drawCloud2
I added a traffic light -> drawTrafficLight
I added keyboard keys to control the speed of the cars. -> 'd' and 's'
I added a child that watch the race from his home window ->drawChild
I added birds -> drawBird
I added a sky -> drawSky
I added a road -> drawRoad

*********/


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

#define TIMER_PERIOD  16 // Period for the timer 
#define TIMER_ON       0 // 0: timer off, 1: timer on


/* Global Variables */
bool isAnimated = true;
float carPosition = 0.0f;
float cloudPosition = 0.0f;
float carMovementSpeed = 2.0f;
float cloudMovementSpeed = 0.3f;
float speedIncrease = 2.0f;
float birdSpeed = 0.8f;
float birdPosition = 0.0f;



void circle(int x, int y, int r)
{
    const float PI = 3.14159f;
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void rectangle(int x, int y, int width, int height)
{
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}


void drawCar()
{

    glColor3f(0.3, 0.3, 0.3); // dark gray
    //rear left wheel
    circle(-38, -9, 8);
    //rear right wheel
    circle(22, -9, 8);

    //car body
    glColor3f(0.8, 0.2, 0.2); // red
    rectangle(-50, -10, 100, 20);

    glColor3f(0.6, 0.6, 0.6); // light gray
    //front left wheel
    circle(-27, -17, 10);
    //front right wheel
    circle(35, -17, 10);

    glColor3f(0.2, 0.3, 0.1); //  brown
    //front right wheel
    circle(35, -17, 5);
    //front left wheel
    circle(-27, -17, 5);

    //window
    glColor3f(0.0, 0.8, 0.8);
    rectangle(-35, -5, 40, 10);
    glColor3f(0.0f, 0.9f, 1.0f);
    rectangle(-35, 5, 40, 10);
}

void drawCar2()
{
    glColor3f(0.3, 0.3, 0.3); // dark gray
    //rear left wheel
    circle(-38, -9, 8);
    //rear right wheel
    circle(22, -9, 8);

    //car body
    glColor3f(0.2, 0.8, 0.2); // green
    rectangle(-50, -10, 100, 20);

    //wheel color
    glColor3f(0.6, 0.6, 0.6); // light gray
    //front right wheel
    circle(35, -17, 10);
    //front left wheel
    circle(-27, -17, 10);

    //wheel color
    glColor3f(0.2, 0.3, 0.1); //  brown
    //front right wheel
    circle(35, -17, 5);
    //front left wheel
    circle(-27, -17, 5);


    glColor3f(0.0, 0.8, 0.8);
    //front window
    rectangle(-35, -5, 40, 10);

    glColor3f(0.0, 0.9, 1.0);
    //rear window
    rectangle(-35, 5, 40, 10);
}

void drawTrafficLight()
{

    glColor3f(1.0, 0.0, 0.0); // Red
    circle(225.0, 100.0, 5.0);

    glColor3f(1.0, 1.0, 0.0); // Yellow
    circle(225.0, 110.0, 5.0);

    glColor3f(0.0, 1.0, 0.0); // Green
    circle(225.0, 120.0, 5.0);

    glColor3f(0.0, 0.0, 0.0); // Black
    glRectf(230.0, 70.0, 225.0, 130.0);
}

void drawCloud()
{
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);


    glColor3f(1.0, 1.0, 1.0);
    float cloudRadius = 20.0;
    float cloudOffset = 30.0;

    //first circle
    circle(-cloudOffset, 0, cloudRadius);
    //second circle
    circle(0, 0, static_cast<int>(cloudRadius * 1.4));
    //third circle
    circle(cloudOffset, 0, cloudRadius);

    glPopMatrix();
}

void drawCloud2()
{
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);


    glColor3f(0.8, 0.8, 0.8);
    float cloudRadius = 20.0;
    float cloudOffset = 30.0;

    //first circle
    circle(-cloudOffset, 0, cloudRadius);
    //second circle
    circle(0, 0, static_cast<int>(cloudRadius * 1.4));
    //third circle
    circle(cloudOffset, 0, cloudRadius);

    glPopMatrix();
}


void drawWindow()
{
    // brown frame for the window
    glColor3f(0.6, 0.4, 0.2);
    glLineWidth(12.0);
    glBegin(GL_LINE_LOOP);
    // outer frame
    glVertex2f(-255, -205);
    glVertex2f(-255, 205);
    glVertex2f(255, 205);
    glVertex2f(255, -205);
    glEnd();

    // black lines
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(5.0);

    // inner edges
    glBegin(GL_LINES);
    glVertex2f(-250, -210); // left edge (inner)
    glVertex2f(-250, 210);
    glVertex2f(-260, -200); // bottom edge (inner)
    glVertex2f(260, -200);
    glVertex2f(-260, 200); // top edge (inner)
    glVertex2f(260, 200);
    glVertex2f(250, -210); // right edge (inner)
    glVertex2f(250, 210);
    glEnd();

    // outer edges
    glBegin(GL_LINES);
    glVertex2f(-260, -210); // left edge (outer)
    glVertex2f(-260, 210);
    glVertex2f(-260, -210); // bottom edge (outer)
    glVertex2f(260, -210);
    glVertex2f(-260, 210); // top edge (outer)
    glVertex2f(260, 210);
    glVertex2f(260, -210); // right edge (outer)
    glVertex2f(260, 210);
    glEnd();

    
}

void drawWallpaper()
{

    glColor3f(0.62, 0.7, 0.51);

    rectangle(-400, 200, 800, 100);

    rectangle(-400, -200, 800, -100);

    rectangle(250, -200, 500, 500);

    rectangle(-450, -200, 200, 500);

    // line 
    glColor3f(0.1, 0.1, 0.1); // dark gray

    // horizontal lines
    float lineWidth = 1.0;
    float lineSpacing = 70.0;
    int numLines = (int)(WINDOW_HEIGHT / (lineWidth + lineSpacing));

    for (int i = -numLines; i <= numLines; i++)
    {
        float yPos = i * (lineWidth + lineSpacing);
        rectangle(-400, yPos - lineWidth / 2.0, 150, lineWidth);
        rectangle(250, yPos - lineWidth / 2.0, 150, lineWidth);
    }


    drawWindow();

    // frame
    glColor3f(0.2, 0.2, 0.2);
    rectangle(-260, 230, 520, 70);

    // name background
    glColor3f(1.0, 1.6, 0.9);
    rectangle(-250, 240, 500, 50);

    // name
    glColor3f(0.1, 0.1, 0.1);
    vprint(-200, 260, GLUT_BITMAP_8_BY_13, "Racing Car View From a Window by Dilara Ozturk");

    glColor3f(0.1, 0.1, 0.1);
    vprint(-350, -230, GLUT_BITMAP_8_BY_13, "Press 'D' to increase the speed of cars");
    glColor3f(0.1, 0.1, 0.1);
    vprint(-350, -250, GLUT_BITMAP_8_BY_13, "Press 'S' to decrease the speed of cars");
    glColor3f(0.1, 0.1, 0.1);
    vprint(-350, -270, GLUT_BITMAP_8_BY_13, "Press 'SpaceBar' to stop the motion");
}

void drawChild()
{
    // head
    glColor3f(0.9, 0.7, 0.5);
    glRectf(-30, -5, 30, 25);

    // hair
    glColor3f(0.0, 0.0, 0.0);
    glRectf(-40, 80, 40, 8);

    // shirt
    glColor3f(0.2, 0.2, 0.8);
    glRectf(-60, -100, 60, 0);

    // right arm
    glColor3f(0.9, 0.6, 0.4);
    glRectf(60, -100, 80, -20);

    //left arm
    glColor3f(0.9, 0.6, 0.4);
    glRectf(-80, -100, -60, -20);
    
}



void drawRoad()
{
    //the road
    glColor3f(0.9, 0.9, 0.9);
    rectangle(-250, -100, 500, 170);
    glColor3f(0.1, 0.1, 0.1);
    rectangle(-250, -90, 500, 150);

    // road lines 
    glColor3f(0.9, 0.9, 0.9);
    rectangle(-10, -15, 50, 6);
    glColor3f(0.9, 0.9, 0.9);
    rectangle(-80, -15, 50, 6);
    glColor3f(0.9, 0.9, 0.9);
    rectangle(-150, -15, 50, 6);
    glColor3f(0.9, 0.9, 0.9);
    rectangle(60, -15, 50, 6);
    glColor3f(0.9, 0.9, 0.9);
    rectangle(-220, -15, 50, 6);
    glColor3f(0.9, 0.9, 0.9);
    rectangle(130, -15, 50, 6);
    glColor3f(0.9, 0.9, 0.9);
    rectangle(200, -15, 50, 6);
    glColor3f(0.9, 0.9, 0.9);
    rectangle(-260, -15, 20, 6);
}

void drawSky()
{
    //sky
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.7, 1.2);
    glVertex2f(-250, 100);
    glColor3f(0.1, 0.4, 0.8);
    glVertex2f(-250 + 500, 100);
    glColor3f(0.1, 0.2, 0.6);
    glVertex2f(-250 + 500, 200);
    glColor3f(0.2, 0.6, 1.0);
    glVertex2f(-250, 200);
    glEnd();

    glColor3f(0.0, 0.5, 0.0); //green
    rectangle(-250, 70, 500, 60);
    glColor3f(0.0, 0.5, 0.0);
    rectangle(-250, -200, 500, 100);
}

void drawBird()
{
    // body
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.0);
    glVertex2f(20.0, -10.0);
    glVertex2f(25.0, 0.0);
    glVertex2f(20.0, 10.0);
    glEnd();

    // beak
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(25.0, 0.0);
    glVertex2f(30.0, -5.0);
    glVertex2f(30.0, 5.0);
    glEnd();

    // eyes
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(3.0);
    glBegin(GL_POINTS);
    glVertex2f(11.0, 3.0);
    glVertex2f(11.0, -3.0);
    glEnd();

    // wings
    glColor3f(0.7, 0.7, 0.7);

    glBegin(GL_TRIANGLES);
    glVertex2f(13.0, 0.0);
    glVertex2f(20.0, -20.0);
    glVertex2f(27.0, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(13.0, 0.0);
    glVertex2f(20.0, 20.0);
    glVertex2f(27.0, 0.0);
    glEnd();
}

void display() {
    glClearColor(0.2, 0.2, 0.2, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-WINDOW_WIDTH / 2, WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, WINDOW_HEIGHT / 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

   
    drawWindow();
    

    drawRoad();

    drawSky();

    drawTrafficLight();

   
    //cloud
    glPushMatrix();
    glTranslatef(-cloudPosition, 170, 0);
    drawCloud();
    glPopMatrix();

    //cloud
    glPushMatrix();
    glTranslatef(-cloudPosition + 250, 150, 0);
    drawCloud2();
    glPopMatrix();

    //bird
    glPushMatrix();
    glTranslatef(-birdPosition, 180, 0);
    drawBird();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-birdPosition + 200, 150, 0);
    drawBird();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-birdPosition + 400, 170, 0);
    drawBird();
    glPopMatrix();

    // car
    glPushMatrix();
    glTranslatef(carPosition, 25, 0);
    drawCar();
    glPopMatrix();

    //  another car
    glPushMatrix();
    glTranslatef(carPosition + 100, -50, 0);
    drawCar2();
    glPopMatrix();

    drawWallpaper();

    glPushMatrix();
    glTranslatef(150, -200, 0);
    drawChild();
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display();
}

void timer(int v)
{
    if (isAnimated)
    {
        carPosition += carMovementSpeed;
        cloudPosition += cloudMovementSpeed;
        birdPosition += birdSpeed;

        if (birdPosition > WINDOW_WIDTH)
            birdPosition = -WINDOW_WIDTH / 2 - 50;

        if (cloudPosition > WINDOW_WIDTH / 2 + 50) {
            cloudPosition = -WINDOW_WIDTH / 2 - 50;
        }

        if (carPosition > WINDOW_WIDTH / 2 + 50)
            carPosition = -WINDOW_WIDTH / 2 - 50;

        glutPostRedisplay();
    }

    glutTimerFunc(TIMER_PERIOD, timer, v);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ':
        isAnimated = !isAnimated;
        break;
    case 27:
        exit(0);
        break;
    case 100:
        carMovementSpeed += speedIncrease;
        break;
    case 115:
        carMovementSpeed -= speedIncrease;
        break;
    default:
        break;
    }
}

void initialize()
{
    glClearColor(0.2, 0.2, 0.2, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-WINDOW_WIDTH / 2, WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, WINDOW_HEIGHT / 2);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("HW1 : Racing Car View From a Window by Dilara Ozturk");

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutTimerFunc(TIMER_PERIOD, timer, 0);

    initialize();
    glutMainLoop();
    return 0;
}