#include "blocksize.h"
#include <iostream>
using namespace std;

blocksize::blocksize(int x, int y) {
    image.load(":/image/block.png");
    blockdestroyed = false;
    rect = image.rect();
    rect.translate(x, y);
}

blocksize::~blocksize(){
    cout << "Block deleted!" << endl;
}

QRect blocksize::getRect(){
    return rect;
}

void blocksize::setRect(QRect rct){
    rect = rct;
}

bool blocksize::blockDestroyed(){
    return blockdestroyed;
}

QImage & blocksize::getImage(){
    return image;
}

void blocksize::setblockDestroyed(bool des){
    blockdestroyed = des;
}
