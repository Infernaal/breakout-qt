#include <QPainter>
#include <QCoreApplication>
#include "breakout.h"

Breakout::Breakout(QWidget *parent) : QFrame (parent) {

  setFrameStyle(QFrame::Panel | QFrame::Sunken);
  setFocusPolicy(Qt::StrongFocus);
  x = 0;
  gameOver = false;
  gameWon = false;
  isPaused = false;
  isStarted = false;
  Ball = new ball();
  paddle = new Paddle();
  player.setMedia(QUrl("qrc:/sound/sound.mp3"));
  player.setVolume(volume);
  int k = 0;

  for (int i=0; i<7; i++) {
    for (int j=0; j<7; j++) {
      block[k] = new blocksize(j*40+10, i*20+50);
      k++;
    }
  }
}

void Breakout::paintEvent(QPaintEvent *event) {

    QFrame::paintEvent(event);
    QPainter painter(this);
    QRect rect = contentsRect();
    QFont font("Courier", 15, QFont::DemiBold);
    painter.setFont(font);
  if(player.state()== QMediaPlayer::StoppedState) {
          player.play();
  }
  if (isPaused) {
      painter.setPen ( Qt::black );
      painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
      return;
  }

  if (gameOver) {

    finishGame(&painter, "Game over!");

  } else if(gameWon) {

    finishGame(&painter, "You win!");
  }
  else {

    drawObjects(&painter);
  }
}

Breakout::~Breakout() {

 delete Ball;
 delete paddle;

 for (int i=0; i<N_OF_BRICKS; i++) {
   delete block[i];
 }
}

void Breakout::finishGame(QPainter *painter, QString message) {

  QFont font("Courier", 15, QFont::DemiBold);
  QFontMetrics fm(font);
  int textWidth = fm.width(message);

  painter->setFont(font);
  int h = height();
  int w = width();

  painter->translate(QPoint(w/2, h/2));
  painter->drawText(-textWidth/2, 0, message);
}

void Breakout::drawObjects(QPainter *painter) {
  painter->drawImage(Ball->getRect(), Ball->getImage());
  painter->drawImage(paddle->getRect(), paddle->getImage());
  for (int i=0; i<N_OF_BRICKS; i++) {
    if (!block[i]->blockDestroyed()) {
      painter->drawImage(block[i]->getRect(), block[i]->getImage());
    }
  }
}

void Breakout::timerEvent(QTimerEvent *event) {

  Q_UNUSED(event);

  moveObjects();
  checkCollision();
  repaint();
}

void Breakout::moveObjects() {

  Ball -> move();
  paddle -> move();
}

void Breakout::keyReleaseEvent(QKeyEvent *event) {

    int dx = 0;

    switch (event->key()) {
        case Qt::Key_Left:
            dx = 0;
            paddle->setDx(dx);
            break;

        case Qt::Key_Right:
            dx = 0;
            paddle->setDx(dx);
            break;
    }
}

void Breakout::keyPressEvent(QKeyEvent *event) {

    int dx = 0;

    switch (event->key()) {
    case Qt::Key_Left:

        dx = -1;
        paddle->setDx(dx);

        break;

    case Qt::Key_Right:

        dx = 1;
        paddle->setDx(dx);
        break;

    case Qt::Key_P:

        pauseGame();
        break;

    case Qt::Key_Space:

        startGame();
        break;

    case Qt::Key_Escape:

        qApp->exit();
        break;

    default:
        QWidget::keyPressEvent(event);
    }
}

void Breakout::startGame() {
    if (isPaused) {
        return;
    }
    isStarted = true;
    player.play();
    score = 0;
    emit scoreChanged(score);
    volume = 10;
    for (int i=0; i<N_OF_BRICKS; i++) {
      block[i] -> setblockDestroyed(false);
    }
    player.setVolume(volume);
    pieceSound.setVolume(volume);
    gameOver = false;
    gameWon = false;
    timerId = startTimer(DELAY);
    Ball -> resetState();
    paddle -> resetState();
    update();
  }

void Breakout::setVolume(int volume)
{
    if(volume == 0)
    {
        player.setMuted(true);
        pieceSound.setMuted(true);
    }
    else{
        player.setMuted(false);
        player.setVolume(volume);
        pieceSound.setMuted(false);
        pieceSound.setVolume(volume);
    }
}

void Breakout::pauseGame() {

    if (isPaused) {
        timerId = startTimer(DELAY);
        isPaused = false;
        player.play();
      } else {

        isPaused = true;
        killTimer(timerId);
        player.pause();
      }
    update();
}

void Breakout::stopGame() {

  killTimer(timerId);
  gameOver = true;
  isStarted = false;
}

void Breakout::victory() {

  killTimer(timerId);
  gameWon = true;
  isStarted = false;
}

void Breakout::checkCollision() {
  int number = 0;
  if (Ball->getRect().bottom() > BOTTOM_EDGE) {
        stopGame();
    }
  for (int i=0, j=0; i<N_OF_BRICKS; i++) {
    if (block[i] -> blockDestroyed()) {
      number++;
      score = number * 7;
      emit scoreChanged(score);
      j++;
    }
    if (j == N_OF_BRICKS) {
      victory();
    }
  }
  if ((Ball -> getRect()).intersects(paddle->getRect())) {

    int paddleLPos = paddle -> getRect().left();
    int ballLPos = Ball -> getRect().left();

    int first = paddleLPos + 8;
    int second = paddleLPos + 16;
    int third = paddleLPos + 24;
    int fourth = paddleLPos + 32;

    if (ballLPos < first) {
      Ball -> setX(-1);
      Ball -> setY(-1);
    }

    if (ballLPos >= first && ballLPos < second) {
      Ball->setX(-1);
      Ball->setY(-1 * Ball->getY());
    }

    if (ballLPos >= second && ballLPos < third) {
       Ball->setX(0);
       Ball->setY(-1);
    }

    if (ballLPos >= third && ballLPos < fourth) {
       Ball->setX(1);
       Ball->setY(-1 * Ball->getY());
    }

    if (ballLPos > fourth) {
      Ball -> setX(1);
      Ball -> setY(-1);
    }
  }

  for (int i=0; i<N_OF_BRICKS; i++) {

    if ((Ball -> getRect()).intersects(block[i]->getRect())) {

      int ballLeft = Ball -> getRect().left();
      int ballHeight = Ball -> getRect().height();
      int ballWidth = Ball -> getRect().width();
      int ballTop = Ball -> getRect().top();

      QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
      QPoint pointLeft(ballLeft - 1, ballTop);
      QPoint pointTop(ballLeft, ballTop -1);
      QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);

      if (!block[i]->blockDestroyed()) {
        if(block[i]->getRect().contains(pointRight)) {
           Ball -> setX(-1);
        }

        else if(block[i]->getRect().contains(pointLeft)) {
           Ball -> setX(1);
        }

        if(block[i]->getRect().contains(pointTop)) {
           Ball -> setY(1);
        }

        else if(block[i]->getRect().contains(pointBottom)) {
           Ball -> setY(-1);
        }

        block[i] -> setblockDestroyed(true);
      }
    }
  }
}
