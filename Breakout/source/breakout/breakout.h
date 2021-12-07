#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QWidget>
#include <QKeyEvent>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QFrame>
#include <QBasicTimer>
#include <QTimer>
#include <QMediaPlayer>
#include "ball.h"
#include "blocksize.h"
#include "paddle.h"

class Breakout : public QFrame {

  Q_OBJECT

public:
    Breakout(QWidget *parent = nullptr);
    ~Breakout();

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public slots:
    void startGame();
    void pauseGame();
    void stopGame();
    void setVolume(int volume);
    void victory();
    void checkCollision();

signals:
    void scoreChanged(int score);

 private:
    void drawObjects(QPainter *);
    void finishGame(QPainter *, QString);
    void moveObjects();
    int x;
    int volume;
    int score;
    int timerId;
    static const int N_OF_BRICKS = 49;
    static const int DELAY = 10;
    static const int BOTTOM_EDGE = 400;
    ball *Ball;
    Paddle *paddle;
    QMediaPlayer player;
    QMediaPlayer pieceSound;
    blocksize *block[N_OF_BRICKS];
    bool gameOver;
    bool gameWon;
    bool isStarted;
    bool isPaused;
};
#endif // BREAKOUT_H
