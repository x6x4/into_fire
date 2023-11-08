#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>
#include <QGridLayout>

std::pair <QString, QString> make_path (BinarySignal &sig) {
    QString up_path = "";
    QString down_path = "";

    auto str = sig.plot();

    QString dynamite = QString::fromUtf8("🧨");
    QString chain = QString::fromUtf8("⛓");

    for (std::size_t i = 0; i < str.size(); i++) {
        if (str.at(i) == '-') {
            if (i == 0) up_path = "🔥";
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

Fire_Path::Fire_Path (std::size_t path_len, QWidget *parent, std::size_t x, std::size_t y) : sig_fire (get_rand_game_sig(path_len)), len (path_len) {
    auto pair = make_path(sig_fire);

    path.first = new QLabel(pair.first, parent);
    path.second = new QLabel(pair.second, parent);
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
};

void Fire_Path::step () {

    if (sig_fire.getSize()) {
        sig_fire.delete_signal(1, 1);

        update();
    }
    else {
        path.first->setText("💥💥💥 YOU WIN! WOW! 💥💥💥");
        path.first->setAlignment(Qt::Alignment(Qt::AlignHCenter));
    }
};

void Fire_Path::restart () {
    path.first->setAlignment(Qt::Alignment());
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
    rand_sig += bsig;
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

