#include "ball.h"
#include <iostream>
using namespace std;

ball::ball()
{
    xdir = 1;
    ydir = -1;
    image.load(":/image/ball.png");
    rect = image.rect();
    resetState();
}

ball::~ball(){
    cout << "Ball deleted!" << endl;
}

void ball::move(){
    rect.translate(xdir, ydir);
    if(rect.left() == 0){
        xdir = 1;
    }
    if(rect.right() == RIGHT_EDGE){
        xdir = -1;
    }
    if(rect.top() == 0){
        ydir = 1;
    }
}

void ball::resetState(){
    rect.moveTo(INITIAL_X, INITIAL_Y);
}

void ball::setX(int x){
    xdir = x;
}


void ball::setY(int y){
    ydir = y;
}

int ball::getX(){
    return xdir;
}

int ball::getY(){
    return ydir;
}

QRect ball::getRect() {

  return rect;
}

QImage & ball::getImage() {

  return image;
}
