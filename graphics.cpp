//
// Created by Drew Smith on 4/30/21.
//

#include "graphics.h"
#include "rect.h"
#include "circle.h"
#include <iostream>
#include <vector>
using namespace std;

GLdouble width, height;
int wd;

const color skyBlue(77/255.0, 213/255.0, 240/255.0);
const color grassGreen(26/255.0, 176/255.0, 56/255.0);
const color white(1, 1, 1);
const color brickRed(201/255.0, 20/255.0, 20/255.0);
const color darkBlue(1/255.0, 110/255.0, 214/255.0);
const color purple(119/255.0, 11/255.0, 224/255.0);
const color black(0, 0, 0);
const color magenta(1, 0, 1);
const color orange(1, 163/255.0, 22/255.0);
const color cyan (0, 1, 1);

// brick breaker game objects
Rect user;
vector<unique_ptr<Shape>> ball;
vector<Rect> blocks;

void init() {
    width = 750;
    height = 750;
    initUser();
    initBall();
    initBlocks();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

// user init
void initUser(){
    user.setColor(white);
    user.setSize(100, 15);
    user.setCenter(325 ,700);

}

// game blocks init
void initBlocks(){
    int row = 5;
    double h = 25;
    int x = 5;
    vector<double> size = {155, 132, 114, 105};
    vector<int> yval = {10, 40, 75, 110};
    vector<color> colors = {brickRed, darkBlue, grassGreen, purple};
    for(int i = 0; i < size.size(); i++){
        for(int j = 0; j < row; j++){
            dimensions s = {size[i], h};
            blocks.push_back(Rect(colors[i], x + 50, yval[i], s));
            x = x + size[i] + 2;
        }
        x = 5;
        row++;
    }
}

// init ball
void initBall(){
    ball.push_back(make_unique<Circle>(grassGreen, 350, 650, 9));
    dimensions dim = {18,18};
    point2D pt = {350, 650};
    ball.push_back(make_unique<Rect>(white, pt, dim));
}

/* Handler for window-repaint event. Call back when the window first appears and
whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE (unless you're on a Mac running Catalina)

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    /*
     * Draw here
     */
    if(user.getSC() == start){
        string message3 = "Brick Breaker";
        glColor3f(1,1,1);
        point2D center3 = {355, 100};
        glRasterPos2i(center3.x - (4 * message3.length()), center3.y + 7);
        for (const char &letter : message3) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string message2 = "To win the game clear the screen of all blocks.";
        glColor3f(1,1,1);
        point2D center2 = {355, 370};
        glRasterPos2i(center2.x - (4 * message2.length()), center2.y + 7);
        for (const char &letter : message2) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }


        string message = "Press the space bar to begin.";
        glColor3f(1, 1, 1);
        point2D center = {355, 650};
        glRasterPos2i(center.x - (4 * message.length()), center.y + 7);
        for (const char &letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string message4 = "Press ESC to leave.";
        glColor3f(1, 1, 1);
        point2D center4 = {355, 675};
        glRasterPos2i(center4.x - (4 * message4.length()), center4.y + 7);
        for (const char &letter : message4) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }

    if(user.getSC() == game) {
        user.draw();
        ball[0]->draw();

        for (int i = 0; i < blocks.size(); i++) {
            // only draw if block is alive
            if (blocks[i].getIsHit() == alive) {
                blocks[i].draw();
            }
        }
    }

    if(user.getSC() == win){
        string message = "Congrats you have won have a nice day!";
        glColor3f(1, 1, 1);
        point2D center = {355, 300};
        glRasterPos2i(center.x - (4 * message.length()), center.y + 7);
        for (const char &letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string message2 = "Press ESC to leave.";
        glColor3f(1, 1, 1);
        point2D center2 = {355, 650};
        glRasterPos2i(center2.x - (4 * message2.length()), center2.y + 7);
        for (const char &letter : message2) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }

    if(user.getSC() == loss){
        string message = "You lost, try getting good and try again.";
        glColor3f(1, 1, 1);
        point2D center = {355, 300};
        glRasterPos2i(center.x - (4 * message.length()), center.y + 7);
        for (const char &letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string message3 = "Press Space bar to try again.";
        glColor3f(1, 1, 1);
        point2D center3 = {355, 625};
        glRasterPos2i(center3.x - (4 * message3.length()), center3.y + 7);
        for (const char &letter : message3) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string message2 = "Press ESC to leave.";
        glColor3f(1, 1, 1);
        point2D center2 = {355, 650};
        glRasterPos2i(center2.x - (4 * message2.length()), center2.y + 7);
        for (const char &letter : message2) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }
    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y){
    if(key == 27){
        glutDestroyWindow(wd);
        exit(0);
    }
    if(key == 32){
        if(user.getSC() == start) {
            user.setSC(game);
            ball[0]->setVelocity(10, -10);
        } else if(user.getSC() == game || user.getSC() == loss || user.getSC() == win){
            user.setSC(start);
            ball[0]->setVelocity(0,0);
            for(int i = 0; i < ball.size(); i++) {
                ball[i]->setCenter(35, 650);
            }
            for(int i = 0; i < blocks.size(); i++){
                blocks[i].setIsHit(alive);
            }
        }
    }
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:

            break;
        case GLUT_KEY_LEFT:
            // move user to the left
            user.move(-15, 0);
            break;
        case GLUT_KEY_RIGHT:
            // move user to the right
            user.move(15,0);
            break;
        case GLUT_KEY_UP:

            break;
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {

    glutPostRedisplay();
}

void timer(int dummy) {
    // moves the ball
    ball[0]->move(ball[0]->getXVelocity(), ball[0]->getYVelocity());
    ball[1]->move(ball[0]->getXVelocity(), ball[0]->getYVelocity());
    // check for bouces on walls and user
    if(ball[1]->getLeftX() < 0){
        ball[0]->bounceX();
    } else if(ball[1]->getRightX() > width){
        ball[0]->bounceX();
    }
    if(ball[1]->getTopY() < 0){
        ball[0]->bounceY();
    } else if(ball[1]->getBottomY() > height){
        // only temp will swap to making this a loss but for testing purposses
        user.setSC(loss);
    }

    // bouce off of user
    if (dynamic_cast<Rect&>(*ball[1]).isOverlapping(user)){
        ball[0]->bounceY();
    }

    // when block is hit set is hit to dead
    for(int i = 0; i < blocks.size(); i++){
        if(blocks[i].getIsHit() == alive) {
            if (dynamic_cast<Rect &>(*ball[1]).isOverlapping(blocks[i])) {
                ball[0]->bounceY();
                blocks[i].setIsHit(dead);
            }
        }
    }

    int deadBlocks = 0;
    for(int i = 0; i < blocks.size(); i++){
        if(blocks[i].getIsHit() == dead){
            deadBlocks++;
        }
        if(deadBlocks == blocks.size()){
            user.setSC(win);
        }
    }


    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Brick Breaker" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}