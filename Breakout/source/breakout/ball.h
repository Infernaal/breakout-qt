#ifndef BALL_H
#define BALL_H

#include <QRect>
#include <QImage>

class ball {

public:
    ball();
    ~ball();
    void resetState();
    void move();
    void setX(int);
    void setY(int);
    int getX();
    int getY();
    QRect getRect();
    QImage & getImage();

private:
    int xdir;
    int ydir;
    QImage image;
    QRect rect;
    static const int INITIAL_X = 170;
    static const int INITIAL_Y = 350;
    static const int RIGHT_EDGE = 300;
};

#endif // BALL_H
