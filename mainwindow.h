// HASAN-CEYHAN-20010011091
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QtGlobal>
#include <QFile>
#include <QStringList>
#include <QList>
#include "karpuz.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void karpuzOlusturmaFonksiyonu();

    void baslatmaFonksiyonu();

    void karpuzQTimer();

private:
    Ui::MainWindow *ui;

    QList<karpuz*>karpuzlar;

};
#endif // MAINWINDOW_H
