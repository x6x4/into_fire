#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>
#include <QGridLayout>

std::pair <QString, QString> make_path (BinarySignal &sig) {
    QString up_path;
    QString down_path;

    auto str = sig.plot();

    QString fire = QString::fromUtf8("🔥");
    QString chain = QString::fromUtf8("⛓");

    for (std::size_t i = 0; i < str.size(); i++) {
        if (str.at(i) == '-') {
            up_path += fire;
            down_path += chain;
        }
        else if (str.at(i) == '_') {
            up_path += " ";
            down_path += "_";
        }
        else {
            up_path += " ";
            down_path += str.at(i);
        }
    }

    return std::make_pair(up_path, down_path);
}

void Fire_Path::update () {
    auto pair = make_path(sig_fire);

    if (ascent == Ascent::UP) {
        path.first->setText(pair.first.insert(0, ' '));
        path.second->setText(pair.second.insert(0, '/'));
    }
    else if (ascent == Ascent::DOWN) {
        path.first->setText(pair.first.insert(0, ' '));
        path.second->setText(pair.second.insert(0, '\\'));
    }
    else {
        path.first->setText(pair.first);
        path.second->setText(pair.second);
    }
}

Fire_Path::Fire_Path (std::size_t path_len, QWidget *parent, std::size_t x, std::size_t y) : sig_fire (get_rand_game_sig(path_len)), len (path_len) {
    auto pair = make_path(sig_fire);

    path.first = new QLabel(pair.first, parent);
    path.second = new QLabel(pair.second, parent);
    auto label = new QLabel(parent);

    label->setStyleSheet("background-color: #000000");
    path.first->setStyleSheet("background-color: #000000");
    path.second->setStyleSheet("background-color: #000000");

    label->move(x, y);
    label->setFixedWidth(300);
    path.first->move(x, y+34);
    path.first->setFixedWidth(300);
    path.second->move(x, y+69);
    path.second->setFixedWidth(300);
};

void Fire_Path::step () {
    if (sig_fire.getSize()) {
        bool prev = sig_fire[1];
        sig_fire.delete_signal(1, 1);
        if (prev < sig_fire[1]) ascent = Ascent::UP;
        else if (prev > sig_fire[1]) ascent = Ascent::DOWN;
        else ascent = Ascent::NO;

        update();
    }
    else {
        path.first->setText("THE END");
    }
};

void Fire_Path::restart () {
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

