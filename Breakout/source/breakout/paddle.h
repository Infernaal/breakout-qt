#ifndef PADDLE_H
#define PADDLE_H

#include <QImage>
#include <QRect>

class Paddle {

  public:
    Paddle();
    ~Paddle();

  public:
    void resetState();
    void move();
    void setDx(int);
    QRect getRect();
    QImage & getImage();

  private:
    QImage image;
    QRect rect;
    int dx;
    static const int INITIAL_X = 150;
    static const int INITIAL_Y = 360;
};

#endif // PADDLE_H
