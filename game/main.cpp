#include <GL/glut.h>
#include <iostream>
#include <string>
using namespace std;
float ball_x=6.7;
float ball_y=1.5;
float radius=0.5;
float pad_x=5.0;
float pad_y=0.0;
float width=4.0;
float height=1.0;
float ball_x_vel=0.0;
float ball_y_vel=0.0;
bool ball_attach=true;
int lives=3;

//return random speed
float getRandom(float a){
    int getRandom=rand()%10;
    float increment=getRandom /a;
    return increment;
}

//function for motion..
void motion(){
    ball_x+=ball_x_vel/2;
    ball_y+=ball_y_vel/2;
    glutPostRedisplay();
    float increment=getRandom(28211.881);
    if(ball_x > 20){
        ball_x_vel=-ball_x_vel;
        ball_y_vel+=increment;
    }
    if(ball_x < 0){
        ball_x_vel=-ball_x_vel;
        ball_y_vel-=increment;
    }
    if(ball_y > 20){
        ball_y_vel=-ball_y_vel;
        ball_x_vel+=increment;
    }
    if(ball_y < 0){
        ball_y_vel=-ball_y_vel;
        ball_x_vel+=increment;
    }
}
// function to render rectangle
void rectangle(){
    glBegin(GL_POLYGON);
        glVertex2f(pad_x,pad_y);
        glVertex2f(pad_x, pad_y+height );
        glVertex2f(pad_x+width , pad_y+height);
        glVertex2f(pad_x+width,pad_y);
    glEnd();
}
//check the current position of the ball
void checkPosition(){
    if(ball_y > pad_y-radius && ball_y < pad_y+height-radius+0.8 && ball_x>pad_x && ball_x < pad_x+width && !ball_attach){
        ball_y_vel=-ball_y_vel;
    }
    if(ball_y+radius<0.6){
    lives-=1;
    ball_x=6.7;
    ball_y=1.5;
    pad_x=5.0;
    pad_y=0.0;
    ball_x_vel=0.0;
    ball_y_vel=0.0;
    ball_attach=true;
        if(lives==0){
            exit(0);
        }
    }
    glutPostRedisplay();
}
//show the text
void showText(){
    glRasterPos2f(17.0, 18.0);
   string s="LIVES";
    for(int i=0;i<s.length();i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    glBegin(GL_LINES);
    if(lives==0){
       glutPostRedisplay();
       return;
    }
    glVertex2f(17.0,17.0);
    glVertex2f(17.0,16.5);
    if(lives==1){
        glEnd();
        glutPostRedisplay();
       return;
    }
    glVertex2f(18.0,17.0);
    glVertex2f(18.0,16.5);
    if(lives==2){
         glEnd();
        glutPostRedisplay();
       return;
    }
    glVertex2f(19.0,17.0);
    glVertex2f(19.0,16.5);
    glEnd();
    glutPostRedisplay();
}

//main display function
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,20.0,0.0,20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Ball Pad
    rectangle();

    //BALL
    glPushMatrix();
    glTranslatef(ball_x,ball_y,0);
    glutSolidSphere(radius,20,20);
    glPopMatrix();
    showText();
    glFlush();
    motion();

    checkPosition();
}

//function to handle keyboard
void keyboardFunc(unsigned char key,int x,int y){
    if(ball_attach){
        glutPostRedisplay();
        return;
    }
    if(key=='a'){
        pad_x-=0.5;
        glutPostRedisplay();
    }
    else if(key == 'd'){
        pad_x+=0.5;
        glutPostRedisplay();
    }
    glutPostRedisplay();
}

//function to launch ball on left click
void mouseFunc(int button , int state , int x ,int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ball_attach){
        float increment=getRandom(281.881);
        int randDir=rand()%2;
        ball_y_vel+=0.05;
        if(randDir == 1){
            ball_x_vel+=increment;
        }
        else
            ball_x_vel-=increment;
        ball_attach=false;
        glutPostRedisplay();
    }
}

//main function
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(700 , 700);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Ball Game");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardFunc);
    glutMouseFunc(mouseFunc);
    glutMainLoop();
    return 0;
}
