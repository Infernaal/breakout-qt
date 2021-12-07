#ifndef BLOCKSIZE_H
#define BLOCKSIZE_H

#include <QImage>
#include <QRect>

class blocksize{

public:
    blocksize(int,int);
    ~blocksize();
    bool blockDestroyed();
    void setblockDestroyed(bool);
    QRect getRect();
    void setRect(QRect);
    QImage & getImage();

private:
    QImage image;
    QRect rect;
    bool blockdestroyed;
};

#endif // BLOCKSIZE_H
