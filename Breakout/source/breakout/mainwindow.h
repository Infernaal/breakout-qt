#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
class QSlider;
class QPixmap;
QT_END_NAMESPACE
class Breakout;

class mainwindow : public QWidget
{
    Q_OBJECT

public:
    mainwindow(QWidget *parent = nullptr);
private:
    Breakout *board;
    QLabel *createLabel(const QString &string);
    QLCDNumber *score;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *exitButton;
    QPushButton *aboutButton;
    QSlider *volumeSlider;
};

#endif // MAINWINDOW_H
