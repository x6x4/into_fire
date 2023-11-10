#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <random>
#include "/home/cracky/oop_lab2_application/BinarySignal/BinarySignal.h"
#include "qelapsedtimer.h"
#include "qwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
};

enum class Ascent {
    NO,
    UP,
    DOWN
};

class Fire_Path : public QObject {

Q_OBJECT

    BinarySignal sig_fire;
    std::pair <QLabel*, QLabel*> path;
    std::size_t len = 0;
    QElapsedTimer game_time;
    bool happy_end = 1;

    void update ();

public:
    Fire_Path (std::size_t path_len, QWidget *parent, std::size_t x, std::size_t y);

public slots:
    void step ();
    void restart ();
};

BinarySignal get_rand_game_sig (std::size_t len);

#endif // WIDGET_H
