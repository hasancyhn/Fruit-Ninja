// HASAN-CEYHAN-20010011091
#ifndef KARPUZ_H
#define KARPUZ_H

#include <QPushButton>
#include <QTimer>

namespace Ui {
class karpuz;
}

class karpuz : public QPushButton
{
    Q_OBJECT

public:
    karpuz(QWidget *parent = 0);

    bool tiklamaDurumu;

    QTimer *sayac;

public slots:
    void tiklayinceKes();

    void karpuzKes();

    void karpuzBuyukluk();

};

#endif // KARPUZ_H
