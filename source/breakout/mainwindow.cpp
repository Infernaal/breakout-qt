#include "mainwindow.h"
#include "breakout.h"

#include <QCoreApplication>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>
#include <QGridLayout>
#include <QSlider>
#include <QPixmap>

QLabel *mainwindow::createLabel(const QString &string){
    QLabel *label = new QLabel(string);
    label -> setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}

mainwindow::mainwindow(QWidget *parent) : QWidget(parent), board(new Breakout)
{
    score = new QLCDNumber(5);
    score -> setSegmentStyle(QLCDNumber::Flat);
    board -> resize(300,430);
    board -> setStyleSheet("background-image: url(:/image/background.jpg);");
    startButton = new QPushButton(tr("&Start"));
    startButton -> setFocusPolicy(Qt::NoFocus);
    startButton -> setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa);");
    exitButton = new QPushButton(tr("&Quit"));
    exitButton -> setFocusPolicy(Qt::NoFocus);
    exitButton -> setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa);");
    pauseButton = new QPushButton(tr("&Pause"));
    pauseButton -> setFocusPolicy(Qt::NoFocus);
    pauseButton -> setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa);");
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider -> setRange(0, 100);
    volumeSlider -> setFixedWidth(100);
    volumeSlider -> setValue(10);
    volumeSlider -> setStyleSheet("QSlider{ background: #FFE5CC; } QSlider::groove:horizontal {  height: 10px; margin: 0px; border-radius: 5px; background: #B0AEB1;} QSlider::handle:horizontal { background: #fff; border: 1px solid #E3DEE2; width: 17px; margin: -5px 0; border-radius: 8px;} QSlider::sub-page:qlineargradient { background: #3B99FC; border-radius: 5px;};");
    connect(startButton, &QPushButton::clicked,  board, &Breakout::startGame);
    connect(pauseButton, &QPushButton::clicked, board, &Breakout::pauseGame);
    connect(exitButton,&QPushButton::clicked, qApp, &QCoreApplication::quit);
    connect(volumeSlider, SIGNAL(valueChanged(int)), board, SLOT(setVolume(int)));

#if __cplusplus >= 201402L
    connect(board, &Breakout::scoreChanged,
            score, qOverload<int>(&QLCDNumber::display));
#else
    connect(board, &Breakout::scoreChanged,
            score, QOverload<int>::of(&QLCDNumber::display));
#endif



    QGridLayout *layout = new QGridLayout;
    layout -> addWidget(board, 0, 0, 13, 8);
    layout -> addWidget(createLabel(tr("Score")), 1, 9);
    layout -> addWidget(score, 2, 9);
    layout -> addWidget(createLabel(tr("Volume")), 3, 9);
    layout -> addWidget(volumeSlider, 4, 9);
    layout -> addWidget(startButton, 8, 9);
    layout -> addWidget(pauseButton, 9, 9);
    layout -> addWidget(exitButton, 10, 9);
    setLayout(layout);
    setWindowTitle("Breakout v1.0");
    setStyleSheet("background-color: #FFE5CC");
    setWindowIcon(QIcon(":/image/title.png"));
    setFixedSize(430, 460);
}
