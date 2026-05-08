#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int obliczKolor(double ptX, double ptY);

protected:
    void paintEvent(QPaintEvent* pEvent) override;
    void wheelEvent(QWheelEvent *event) override;

private slots:
    void on_suwakJasnosc_valueChanged(int value);

    void on_suwakCzulosc_valueChanged(int value);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    int jasnosc = 0;
    int czulosc = 30;


    double offsetX = -0.5;
    double zoom = 0.4;
    double offsetY = 0.0;
};
#endif // MAINWINDOW_H
