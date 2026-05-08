#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <complex>
#include <QWheelEvent>
#include <cmath>

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::obliczKolor(double x, double y)
{
    complex<double> z(0, 0); //zmienna zn z iteracji mandelbrota (z wikipedii) (na poczatku z0=0)



    double prawdziwe_x = double(x) / double(width()) - 0.5; //wspolrzedne przeskalowane o pozycje myszy (tak zeby operowac np. na x pod myszą, a nie x wzgledem srodka)
    double prawdziwe_y = double(y) / double(height()) - 0.5;


    double odwZoom = 1.0 / zoom;
    double czReczywista = offsetX +prawdziwe_x * odwZoom;
    double czUrojona = offsetY + prawdziwe_y * odwZoom;

    //pkt odpowiadajacy pikselowi (x,y)
    complex<double> pktZespolony(czReczywista, czUrojona);

    int jasnosc_temp = jasnosc;

    while((abs(z) < 2 ) && ( jasnosc_temp <= czulosc ))
    {
        z = z * z + pktZespolony;
        jasnosc_temp++;
    }

    if (jasnosc_temp < czulosc)
    {
        return int(( 255 * jasnosc_temp ) / czulosc );
    }

    else
    {
        return 0;
    }
}

void MainWindow::paintEvent(QPaintEvent *pEvent) //pomalowanie kazdego piksela
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen;
    int kolor = 0;


    for (int x= 0; x < width(); ++x) //dwie petle rysujace piksel po pikselu przez drawPoint()
    {
        for (int y = 0; y < height(); ++y)
        {
            kolor = obliczKolor(double(x), double(y));

            pen.setColor(QColor(kolor, 0, 0));
            painter.setPen(pen);
            painter.drawPoint(x, y);

        }
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    //poz kursora
    QPoint pozycja = event->position().toPoint();
    double prawdziwe_x = double(pozycja.x()) / double(width()) - 0.5;
    double prawdziwe_y = double(pozycja.y()) / double(height()) - 0.5; //znowu - wspolrzedne przeskalowane o pozycje myszy

    double odwZoomPrzed = 1.0 / zoom;
    double czRzeczywista = offsetX + prawdziwe_x * odwZoomPrzed;

    double czUrojona = offsetY+prawdziwe_y*odwZoomPrzed;


    int delta = event->angleDelta().y();
    double ZmianaZooma = pow(1.0015, delta); //delta ujemna to ZmianaZooma<1 czyli oddala, delta dodatnia to ZmianaZooma>1 czyli przybliza

    if (ZmianaZooma <= 0.0) return;

    zoom *= ZmianaZooma;
    double odwZoomPo = 1.0 / zoom;

    //offsety ustawiam tak by punkt pod kursorem dalej byl tym samym pkt zespolonym
    offsetX= czRzeczywista - prawdziwe_x * odwZoomPo;
    offsetY= czUrojona - prawdziwe_y *odwZoomPo;
    update();
}


void MainWindow::on_suwakJasnosc_valueChanged(int value)
{
    jasnosc = value;
    update();
}


void MainWindow::on_suwakCzulosc_valueChanged(int value)
{
    czulosc = value;
    update();
}


void MainWindow::on_pushButton_clicked()
{
    zoom = 0.4;
    offsetX = -0.5;
    offsetY = 0.0;
    update();
}

