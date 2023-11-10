#include "widget.h"
#include "./ui_widget.h"
#include "qglobal.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include <QDebug>
#include <QGridLayout>
#include <QElapsedTimer>

std::pair <QString, QString> make_path (BinarySignal &sig) {
    QString up_path = "";
    QString down_path = "";

    auto str = sig.plot();

    QString dynamite = QString::fromUtf8("🧨");
    QString chain = QString::fromUtf8("⛓");

    for (std::size_t i = 0; i < str.size(); i++) {
        if (str.at(i) == '-') {
            if (i == 0) up_path = "🔥";
            else if (i == str.size() - 1) up_path += "💣";
            else up_path += dynamite;
            down_path += chain;
        }
        else if (str.at(i) == '_') {
            if (i == 0) { down_path = "💥";}
            else down_path += "_";
            up_path += "  ";
        }
        else {
            up_path += "  ";
            down_path += str.at(i);
        }
    }

    //qDebug() << up_path;
    //qDebug() << down_path;

    return std::make_pair(up_path, down_path);
}

void Fire_Path::update () {
    auto pair = make_path(sig_fire);

    path.first->setText(pair.first);
    path.second->setText(pair.second);

}

Fire_Path::Fire_Path (std::size_t path_len, QWidget *parent, std::size_t x, std::size_t y) : len (path_len) {

    path.first = new QLabel(parent);
    path.second = new QLabel(parent);
    auto label = new QLabel(parent);

    path.first->setStyleSheet("background-color: #000000");
    path.second->setStyleSheet("background-color: #000000");

    std::size_t w = 800;
    std::size_t h = 60;

    label->move(x, y);
    label->setFixedWidth(w);
    label->setFixedHeight(2*h);
    label->setText("Sanctified by Dynamite");
    label->setStyleSheet("QLabel { color : red; background-color: #000000}");
    label->setAlignment(Qt::Alignment(Qt::AlignCenter));

    path.first->move(x, y+2*h);
    path.first->setFixedWidth(w);
    path.first->setFixedHeight(h);

    path.second->move(x, y+3*h);
    path.second->setFixedWidth(w);
    path.second->setFixedHeight(h);

    restart();
};


void Fire_Path::step () {

    auto choice = qobject_cast<QPushButton*>(sender())->text();
    static qint64 res = 0;

    if (sig_fire.getSize() > 1) {

        bool dyn = sig_fire[2];

        if (dyn && choice == "jump" || !dyn && choice == "go") {
            sig_fire.delete_signal(1, 1);
            update();
            if (sig_fire.getSize() != 1) return;
            res = game_time.elapsed();
        } else { happy_end = 0; }
    }

    if (happy_end) {
        sig_fire = BinarySignal();
        update();
        path.first->setText("💥💥💥 YOU WON! 💥💥💥");
        path.first->setAlignment(Qt::Alignment(Qt::AlignHCenter));
        path.second->setText(QString("Time: %1.%2s").arg(res/1000).arg(res%1000));
        path.second->setAlignment(Qt::Alignment(Qt::AlignHCenter));
    } else {
        happy_end = 0;
        sig_fire = BinarySignal();
        update();
        path.first->setText("🔥🔥🔥 YOU ARE DEFEATED! 🔥🔥🔥");
        path.first->setAlignment(Qt::Alignment(Qt::AlignHCenter));
    }
};


void Fire_Path::restart () {
    happy_end = 1;
    game_time.start();
    path.first->setAlignment(Qt::Alignment());
    path.second->setAlignment(Qt::Alignment());
    sig_fire = get_rand_game_sig(len);
    update();
}

BinarySignal get_rand_game_sig (std::size_t len) {
    std::string rand_seq(len, '\0');

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> distr{0, 1};

    for (std::size_t i = 0; i < len; i++)
        rand_seq[i] = distr(gen) + 48;

    BinarySignal rand_sig(rand_seq);
    BinarySignal bsig (3, 0);
    rand_sig += BinarySignal(1, 1);
    bsig += rand_sig;

    return bsig;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

