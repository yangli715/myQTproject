#ifndef SERIAL_H
#define SERIAL_H

#include <QWidget>
#include"qmessagebox.h"
#include<QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>
#include<QString>
#include<QByteArray>
#include<QDebug>
#include<QTextEdit>
#include<QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Serial; }
QT_END_NAMESPACE

class Serial : public QWidget
{
    Q_OBJECT

public:
    Serial(QWidget *parent = nullptr);
    ~Serial();

private:
    Ui::Serial *ui;
public:
    QSerialPort serial_port;
    void System_init();//初始化
private slots:
    void on_open_Button_clicked();
    void on_send_Button_clicked();
    void on_clear_Button_clicked();
    void serial_read();
    void on_pushButton_clicked();
    QString  on_chosefile_clicked();
    void on_sendfile_clicked();
};
#endif // SERIAL_H
