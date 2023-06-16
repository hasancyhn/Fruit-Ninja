// HASAN-CEYHAN-20010011091
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    karpuzQTimer();
}

MainWindow::~MainWindow()
{
    delete ui;
}


int kesilenKarpuzSayisi=0, kacanKarpuzSayisi=0;

void MainWindow::karpuzQTimer()
{
    QTimer *karpuzSayac = new QTimer(this);
    connect(karpuzSayac, &QTimer::timeout, this, &MainWindow::karpuzOlusturmaFonksiyonu);
    // Karpuzlarin olusturma sıklıgı yani saniyede 1 tane karpuz olusturulacak.
    karpuzSayac->start(1001);

    QTimer *oyunSuresi= new QTimer(this);
    connect(oyunSuresi, &QTimer::timeout, this, &MainWindow::baslatmaFonksiyonu);
    oyunSuresi->start(501);
}


int maximumSkor;
int oyunSuresi=30;
void MainWindow::karpuzOlusturmaFonksiyonu()
{
    oyunSuresi -= 1;
    ui->labelTime->setText("Süre: <font color='blue'>"+QString::number(oyunSuresi));
    karpuz *karpuzs = new karpuz(this);

    // Konumlari okuyamadim.
    QFile konumOku(":/konumlar/konumlar.txt");
    if(!konumOku.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this, "Hata!", konumOku.errorString());
            return;
    }
    QTextStream stremNeKonumOku(&konumOku);

    QString line;
    while(!stremNeKonumOku.atEnd()){
      line = stremNeKonumOku.readLine();
    }

    QStringList list = line.split(",");
    int x, y;

    if(list.size() == 2){
        x = list.at(0).toInt();
        y = list.at(1).toInt();
        // qDebug() << x;
        // qDebug() << y;
    }
    else{
        // qDebug()<<"Koordinatlar LINE: "<<line;
        // qDebug()<<"Koordinatlar X: "<<x;
        // qDebug()<<"Koordinatlar Y: "<<y;
    }

    konumOku.close();


    // Karpuzlarin olusturulma konumlari
    karpuzs->setGeometry(rand()%(this->width()), 60, 42, 42);
    karpuzs->setStyleSheet("QPushButton {image: url(:/resim/images/1.png);}");
    karpuzs->show();
    karpuzlar.append(karpuzs);


    if(oyunSuresi<=0){
        // Skorlari "skorlar.txt" dosyasina yazma.
        QFile skorlarDosyam("C:/Users/HASAN/Documents/GP_odev-1/skorlar.txt");
        if(!skorlarDosyam.open(QIODevice::Append)){
                QMessageBox::critical(this,"Hata!", skorlarDosyam.errorString());
                return;
        }
        QTextStream streamNeSkorlarDosyam(&skorlarDosyam);
        streamNeSkorlarDosyam << QString::number(kesilenKarpuzSayisi) << "\n";
        skorlarDosyam.close();

        // Dosyadaki en buyuk sayiyi bulma.
        QFile skorOku("C:/Users/HASAN/Documents/GP_odev-1/skorlar.txt");
        if(!skorOku.open(QIODevice::ReadOnly)){
                QMessageBox::critical(this, "Hata!", skorOku.errorString());
                return;
        }
        QTextStream streamNeSkorOku(&skorOku);
        QString string;
        maximumSkor = INT_MIN;

        while (!streamNeSkorOku.atEnd()) {
            string = streamNeSkorOku.readLine();
            maximumSkor = qMax(maximumSkor, string.toInt());
        }
        skorOku.close();

        // Maximum skoru gecip gecmeme durumuna gore if bloguna girecek.
        if(kesilenKarpuzSayisi == maximumSkor){
            QMessageBox::information(this, "Bilgi!", "Oyun Bitti! Maksimum Skor Sizde! \n"
                                                     "Kesilen Karpuz Sayısı: "+QString::number(kesilenKarpuzSayisi)+"\n"
                                                     "Kaçırılan Karpuz Sayısı: "+QString::number(kacanKarpuzSayisi)+"\n"
                                                     "Maximum Skor: "+QString::number(maximumSkor),
                                                     "Ok");
        }
        else{
            QMessageBox::information(this, "Bilgi!", "Oyun Bitti! Maksimum Skoru Geçemediniz! \n"
                                                     "Kesilen Karpuz Sayısı: "+QString::number(kesilenKarpuzSayisi)+"\n"
                                                     "Kaçırılan Karpuz Sayısı: "+QString::number(kacanKarpuzSayisi)+"\n"
                                                     "Maximum Skor: "+QString::number(maximumSkor),
                                                     "Ok");
        }

        this->close();
    }
}

void MainWindow::baslatmaFonksiyonu()
{
    // Resmi ekranda konumlandiriyoruz.
    ui->labelArkaPlanResmi->setGeometry(0, 53, this->width(), this->height());
    foreach(karpuz *karpuz, karpuzlar){
        if(karpuz->y() > this->height()){
            kacanKarpuzSayisi += 1;
            karpuzlar.removeOne(karpuz);
            karpuz->hide();
            ui->labelKacanKarpuz->setText("Kaçırılan Karpuz Sayısı: <font color='red'>"+QString::number(kacanKarpuzSayisi));
        }

        if(karpuz->tiklamaDurumu){
            kesilenKarpuzSayisi += 1;
            karpuzlar.removeOne(karpuz);
            ui->labelKesilenKarpuz->setText("Kesilen Karpuz Sayısı:   <font color='green'>"+QString::number(kesilenKarpuzSayisi));
        }
    }
}


