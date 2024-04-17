#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include <QEventLoop>

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
    void on_pushButton_start_clicked();

    void on_pushButton_reset_clicked();

    void ticked();

    void boomTicked();

    void delayTimerTicked();

    void on_pushButton_reset_boom_clicked();

    void on_pushButton_timer_clicked();

    void on_dial_valueChanged(int value);

    void on_pushButton_boomCancel_clicked();

    void on_pushButton_delayCancel_clicked();

    QString display_time(int counter);

    QString another_display_time(int counter_boom);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *timer_boom;
    QTimer *timer_delay;
    int counter;
    int counter_boom;
    int counter_info;
    int num_delay;
    QString text;
};
#endif // MAINWINDOW_H
