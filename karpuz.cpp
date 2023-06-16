// HASAN-CEYHAN-20010011091
#include "karpuz.h"

karpuz::karpuz(QWidget *parrent):QPushButton(parrent)
{
    tiklamaDurumu=false;

    // Function based kullandim.
    connect(this, &QPushButton::clicked, this, &karpuz::tiklayinceKes);

    sayac = new QTimer(this);
    connect(sayac, &QTimer::timeout, this, &karpuz::karpuzBuyukluk);
    // Karpuzlarin yere dusus hizini ayarliyoruz.
    sayac->start(10);
}

void karpuz::tiklayinceKes()
{
    tiklamaDurumu = !tiklamaDurumu;
    QTimer *karpuzKes = new QTimer(this);

    connect(karpuzKes, &QTimer::timeout, this, &karpuz::karpuzKes);

    this->setStyleSheet("QPushButton { image: url(:/resim/images/2.png)}");

    // Karpuz kesildikten ne kadar sure sonra ekrandan ayrilacagini hesapliyoruz.
    karpuzKes->start(712);
}

// Eger bu fonksiyon olmazsa karpuz kesilme efektinden sonra karpuz ekrandan kaybolmaz.
void karpuz::karpuzKes()
{
    // Karpuzun kesildikten sonra ekrandan gitmesini sagliyoruz.
    this->hide();
}

void karpuz::karpuzBuyukluk()
{
    if(!tiklamaDurumu){
        // Karpuzlarin buyuklugunu ayarliyoruz. (71x71)
        // Karpuzlarin yere dusus koordinatlarini (this->x(), this->y()+2) olarak belirledik.
        this->setGeometry(this->x(), this->y()+1, 71, 71);
    }
}
