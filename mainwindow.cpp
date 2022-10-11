#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
//static void Draw(QRcode *qrc, QImage &image);
static void Draw(QrCode qr, QImage &image);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->from->setValidator( new QIntValidator(0, 999999, this) );
    ui->to->setValidator( new QIntValidator(0, 999999, this) );

    ui->factory->addItem("101");
    ui->year->addItem("2022");
    ui->year->addItem("2023");
    ui->year->addItem("2024");
    ui->year->addItem("2025");
    ui->modul->addItem("BE");
    ui->modul->addItem("HM");
    ui->modul->addItem("PM");
    ui->modul->addItem("AB");
    ui->modul->addItem("MC");
    ui->modul->addItem("BC");
    ui->modul->addItem("BS");
    ui->modul->addItem("MB");

    ui->version->setMinimum(1);
    ui->size->addItem("65");
    ui->size->addItem("128");
    ui->size->addItem("256");
    ui->size->addItem("512");
    ui->size->addItem("1024");
//    ui->labelTest->setStyleSheet("background-image: url(D:/a.png);");
//    ui->backGround->addItem("");
//    ui->backGround->addItem("white");
//    ui->foreGround->addItem("black");
//    ui->foreGround->addItem("white");

//    ui->version->addItem("1");
//    ui->version->addItem("2");
//    ui->version->addItem("3");
//    ui->version->addItem("4");
//    ui->version->addItem("5");
//    ui->version->addItem("6");
//    ui->version->addItem("7");
//    ui->version->addItem("8");
//    ui->size->setValidator( new QIntValidator(0, 10000, this) );
//    this->setStyleSheet("{background-image: url(:/home/hoanpx/Pictures/White_full.png);}");
}

MainWindow::~MainWindow()
{
    delete ui;
}
#if 0
void Draw(QRcode *qrc, QImage &image)
{
    const int width = qrc->width > 0 ? qrc->width : 1;
    double scale = image.width()/width;
    QPainter painter;

    painter.begin(&image);
    //White background image.
    QColor background(Qt::white);
    painter.setBrush(background);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, image.width(), image.width());
    qDebug()<<image.width();
    //The code value is black.
    QColor foreground(Qt::red);
    painter.setBrush(foreground);

    //The conversion of the two-dimensional code data into an image needs to be enlarged, otherwise a single pixel will represent the code value, which looks weird.
    for(int y=0; y<width; y++)
    {
        for(int x=0; x<width; x++)
        {
            unsigned char b=qrc->data[y*width+x];
            /**
             * Each byte of qrc->data corresponds to a small square in the QR code. If the lowest bit of the byte is high, a black square is drawn.
             * The meaning of each bit in the byte is as follows
             *
             * bit0: 1=black/0=white
             * bit1: data and ecc code area
             * bit2: format information
             * bit3: version information
             * bit4: timing pattern
             * bit5: alignment pattern
             * bit6: finder pattern and separator
             * bit7: non-data modules (format, timing, etc.)
             */
            if(b&0x01)
            {
                QRectF r(x*scale, y*scale, scale, scale);
                painter.drawRects(&r, 1);
            }
        }
    }
    painter.end();
}
#endif
void MainWindow::on_pushButton_clicked()
{
    QString factory = ui->factory->currentText();
    QString modul  = ui->modul->currentText();
    QString version  = ui->version->text();
    int year    = ui->year->currentText().split(" ")[0].toInt();
    QString yearEnCode;
    switch (year)
    {
    case 2022:
        yearEnCode = "N";
        break;
    case 2023:
        yearEnCode = "P";
        break;
    case 2024:
        yearEnCode = "R";
        break;
    case 2025:
        yearEnCode = "S";
        break;
    default:
        break;
    }
    QString from    = ui->from->text();
    QString to      = ui->to->text();
    QString path    = ui->path->text();
    QString size = ui->size->currentText();
    width        = size.split(" ")[0].toInt();

//    width        = 64;
    beginNumber  = from.split(" ")[0].toInt();
    endNumber    = to.split(" ")[0].toInt();
    for(int a=beginNumber;a<=endNumber; a++ )
    {
        QString s ;
        s = QString::number(a).rightJustified(6, '0');

        input =QString(factory) + QString(modul) +QString(version) + QString(yearEnCode) + QString(s);
//        QRcode *qr = QRcode_encodeString(input.toStdString().c_str(), 1, QR_ECLEVEL_L, QR_MODE_8, 1);
        const QrCode::Ecc errCorLvl = QrCode::Ecc::LOW;

        QrCode qr = QrCode::encodeText(input.toStdString().c_str(), errCorLvl);
        QImage image(width, width, QImage::Format_RGB32);
        Draw(qr, image);
        //Use QImage to save the QR code as a picture, the string extension determines the image encoding format.
        image.save(QString(path) + "/" + QString(input) +".png");
        qDebug()<<QString(path);
        QGraphicsScene *graphic = new QGraphicsScene(this);
        graphic->addPixmap(QPixmap::fromImage(image));
        ui->graphicsView->setScene(graphic);
    }
}
void Draw(QrCode qr, QImage &image)
{
    const int width =  qr.getSize()> 0 ?  qr.getSize() : 1;
    double scale = image.width()/width;
    QPainter painter;

    painter.begin(&image);
    //White background image.
    QColor background(Qt::black);
    painter.setBrush(background);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, image.width(), image.width());
    qDebug()<<image.width();
    //The code value is black.
    QColor foreground(Qt::white);
    painter.setBrush(foreground);

    //The conversion of the two-dimensional code data into an image needs to be enlarged, otherwise a single pixel will represent the code value, which looks weird.
    for(int y=0; y<width+2; y++)
    {
        for(int x=0; x<width+2; x++)
        {
            unsigned char b=qr.getModule(x, y);
             qDebug()<<b;
            /**
             * Each byte of qrc->data corresponds to a small square in the QR code. If the lowest bit of the byte is high, a black square is drawn.
             * The meaning of each bit in the byte is as follows
             *
             * bit0: 1=black/0=white
             * bit1: data and ecc code area
             * bit2: format information
             * bit3: version information
             * bit4: timing pattern
             * bit5: alignment pattern
             * bit6: finder pattern and separator
             * bit7: non-data modules (format, timing, etc.)
             */
            if(b&0x01)
            {
                QRectF r(x*scale+1, y*scale+1, scale , scale);
                painter.drawRects(&r, 1);
            }
        }
    }
    painter.end();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
    "D:/Documents/Images/QR",
    QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    ui->path->setText(dir);

}

