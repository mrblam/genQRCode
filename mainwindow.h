#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
//#include <qrencode.h>
#include <QDebug>
#include <QGraphicsScene>
#include "qrcodegen.h"
#include <QIntValidator>
#include <QFileDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
using qrcodegen::QrCode;
using qrcodegen::QrSegment;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    int beginNumber;
    int endNumber;
    int width;
    Ui::MainWindow *ui;
    QString input;
protected:

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};
#endif // MAINWINDOW_H
