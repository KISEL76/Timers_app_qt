#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_info->hide();

    counter = 0;

    timer = new QTimer(this);

    timer->setInterval(10);

    connect(timer, SIGNAL(timeout()), this, SLOT(ticked()));

    timer_boom = new QTimer(this);

    connect(timer_boom, SIGNAL(timeout()), this, SLOT(boomTicked()));

    timer_delay = new QTimer(this);

    connect(timer_delay, SIGNAL(timeout()), this, SLOT(delayTimerTicked()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_start_clicked()
{
    if (ui->pushButton_reset->text() == "Стоп"){
        counter = 0;
        timer->start(10);
    }
    else{
        counter = 0;
        ui->lcdNumber->display(0);
    }
}

void MainWindow::on_pushButton_reset_clicked()
{
    if (timer->isActive()){
        timer->stop();
        ui->pushButton_reset->setText("Старт");
    }
    else{
        timer->start(10);
        ui->pushButton_reset->setText("Стоп");
    }
}

void MainWindow::ticked()
{
    counter++;
    QString text = display_time(counter);
    ui->lcdNumber->display(text);
}

void MainWindow::on_pushButton_reset_boom_clicked()
{
    if (ui->dial->value() == 0){
        QMessageBox::information(this, "Внимание!", "Значение таймера равно 0!");
        return;
    }
    counter_boom = ui->dial->value();
    timer_boom->start(1000);
    ui->dial->setEnabled(false);
}

void MainWindow::boomTicked(){
    counter_boom--;
    QString text = another_display_time(counter_boom);
    ui->lcdNumber_2->display(text);

    if (counter_boom == 0){
        ui->dial->setEnabled(true);
        timer_boom->stop();
        setEnabled(false);
        timer_delay->stop();
        timer->stop();
        ui->lcdNumber->display(0);
        ui->lcdNumber_3->display(0);
        QMessageBox::information(this, "Упс", "Кажется все взорвалось!");
    }
}

void MainWindow::on_pushButton_timer_clicked()
{
    num_delay = ui->spinBox_delay->text().toInt() * 1000;
    if (num_delay != 0){
        timer_delay->start(10);
    }
    counter_info = ui->spinBox_timer->text().toInt() * 1000;

    timer_delay->start(10);
}

void MainWindow::delayTimerTicked(){
    if (num_delay != 0){
        ui->label_info->setVisible(true);
        QTime time = QTime::fromMSecsSinceStartOfDay(num_delay);
        QString text = time.toString("HH:mm:ss");
        ui->label_info->setText("Таймер включится через " + text);
        num_delay -= 10;
    }
    else{
        ui->label_info->setVisible(false);
        if (counter_info > 0){
            QTime time = QTime::fromMSecsSinceStartOfDay(counter_info);
            QString text = time.toString("HH:mm:ss");
            ui->lcdNumber_3->display(text);
        }
        else{
            timer_delay->stop();
        }
    }
}

void MainWindow::on_dial_valueChanged(int value)
{
    QTime time = QTime::fromMSecsSinceStartOfDay(value * 1000);
    QString text = time.toString("HH:mm:ss");
    ui->lcdNumber_2->display(text);
}

void MainWindow::on_pushButton_boomCancel_clicked() 
{
    ui->lcdNumber_2->display(0);
    ui->dial->setEnabled(true);
    timer_boom->stop();
    int value = ui->dial->value();
    QTime time = QTime::fromMSecsSinceStartOfDay(value * 1000);
    QString text = time.toString("HH:mm:ss");
    ui->lcdNumber_2->display(text);

}

void MainWindow::on_pushButton_delayCancel_clicked()  
{
    timer_delay->stop();
    ui->lcdNumber_3->display(0);
}

QString MainWindow::display_time(int counter){
    counter++;

    int msec = counter * 10;

    int sec = msec / 1000 % 60;
    int min = msec / 1000 / 60 % 60;
    int hour = msec / 1000 / 60 / 60;
    int s_sec = counter % 100;

    text = QString("%1:%2:%3.%4").arg(hour, 2, 10, QChar('0')).
                   arg(min, 2, 10, QChar('0')).
                   arg(sec, 2, 10, QChar('0')).
                   arg(s_sec, 2, 10, QChar('0'));
    return text;
}

QString MainWindow::another_display_time(int counter_boom){
    QTime time = QTime::fromMSecsSinceStartOfDay(counter_boom * 1000);
    QString text = time.toString("HH:mm:ss");

    return text;
}
