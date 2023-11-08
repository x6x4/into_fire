#include "widget.h"

#include <QApplication>
#include <QPushButton>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet("QLabel{font-size: 30pt; color : white;}");

    QFont mfont("Monospace");
    mfont.setStyleHint(QFont::TypeWriter);

    QWidget win;
    win.setStyleSheet("background-color: #000000");
    win.setFont(mfont);
    std::size_t win_w = 1000;
    win.setFixedSize(win_w, 500);
    win.setToolTip("Into Fire");

    std::size_t b_sz = 50;

    Fire_Path path(20, &win, 100, 100);

    QPushButton *b_quit = new QPushButton ("Exit", &win);
    b_quit->setGeometry(win_w - b_sz - 10, 10, b_sz, b_sz);
    b_quit->setStyleSheet("background-color: red");
    win.connect(b_quit, SIGNAL (clicked()), a.instance(), SLOT (quit()));

    QPushButton *b_light = new QPushButton ("light", &win);
    b_light->setGeometry(30, 90, b_sz, b_sz);
    b_light->setStyleSheet("background-color: red");
    win.connect(b_light, SIGNAL (clicked()), &path, SLOT (step()));

    QPushButton *b_new = new QPushButton ("New Game", &win);
    b_new->setGeometry(30, 10, 3*b_sz, b_sz);
    b_new->setStyleSheet("background-color: red");
    win.connect(b_new, SIGNAL (clicked()), &path, SLOT (restart()));

    win.show();
    return a.exec();
}
