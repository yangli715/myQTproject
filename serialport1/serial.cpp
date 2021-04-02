#include "serial.h"
#include "ui_serial.h"
#include"qmessagebox.h"

#include<QMessageBox>
#include<QDataStream>
Serial::Serial(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Serial)
{
    ui->setupUi(this);
    this->resize (1000,600);
    this->setWindowTitle(tr("串口助手"));
    connect(&serial_port, &QSerialPort::readyRead , this , &Serial::serial_read);    this->setWindowTitle("����С����");
}
Serial::~Serial()
{
    delete ui;
}
void Serial::System_init()
{
    serial_port.setPortName("COM1");
    serial_port.setBaudRate(9600);
    serial_port.setDataBits(QSerialPort::Data8);
    serial_port.setStopBits(QSerialPort::OneStop);
    serial_port.setParity(QSerialPort::NoParity);
    serial_port.setFlowControl(QSerialPort::NoFlowControl);

}

void Serial::on_open_Button_clicked()
{
    //设置端口
    switch(ui->portNameBox->currentIndex()){
    case 0:
        serial_port.setPortName("COM1");
        break;
    case 1:
        serial_port.setPortName("COM2");
        break;
    case 2:
        serial_port.setPortName("COM3");
        break;
    case 3:
        serial_port.setPortName("COM4");
        break;
    case 4:
        serial_port.setPortName("COM5");
        break;
    default:
        serial_port.setPortName("COM6");
    }
    //设置波特率
    switch (ui->baudRateBox->currentIndex()) {
    case 0:
        serial_port.setBaudRate(QSerialPort::Baud38400);
        break;
    case 1:
        serial_port.setBaudRate(QSerialPort::Baud19200);
        break;
    case 2:
        serial_port.setBaudRate(QSerialPort::Baud9600);
        break;
    case 3:
        serial_port.setBaudRate(QSerialPort::Baud4800);
        break;
    case 4:
        serial_port.setBaudRate(QSerialPort::Baud2400);
        break;
    default:
        serial_port.setBaudRate(QSerialPort::Baud1200);
        break;
    }
    //设置校验位
    switch (ui->parityBitBox->currentIndex()) {
    case 0:
        serial_port.setParity(QSerialPort::NoParity);
        break;
    default:
        break;
    }

    //设置数据位
    switch (ui->dataBitBox->currentText().toInt()) {
    case 8:
        serial_port.setDataBits(QSerialPort::Data8);
        break;
    case 7:
        serial_port.setDataBits(QSerialPort::Data7);
        break;
    case 6:
        serial_port.setDataBits(QSerialPort::Data6);
        break;
    case 5:
        serial_port.setDataBits(QSerialPort::Data5);
        break;
    }
    //设置停止位
    switch (ui->stopBitBox->currentIndex()) {
    case 1:
        serial_port.setStopBits(QSerialPort::OneStop);
        break;
    case 2:
        serial_port.setStopBits(QSerialPort::TwoStop);
        break;
    default:
        break;
    }
    if(serial_port.open(QIODevice::ReadWrite))
    {
        qDebug()<<serial_port.portName()<<"打开成功";
        ui->open_Button->setText("关闭 " );
    }
    else
    {
        qDebug()<<serial_port.portName()<<"打开失败";
        ui->open_Button->setText("打开");
    }
}

//点击按钮 判断是否位16进制发送
void Serial::on_send_Button_clicked()
{
    //读取发送数据
    QString senddata=ui->sendEdit->toPlainText().toUtf8();
    QByteArray array=senddata.toLatin1();
    int cnt=array.size();
    QChar *data=senddata.data();
    if(ui->send16Box->isChecked()==true)
    {

        for(int i=0;i<cnt;i++)
        {
            if(data[i]>='0'&&data[i]<='9')
               continue;
            else if(data[i]>='a'&&data[i]<='f')
               continue;
            else if(data[i]>='A'&&data[i]<='F')
                continue;
           else
           {
               QMessageBox::warning(this,"warn","Invalid input, please reenter");
               return ;
          }
         }
        array=array.toHex(' ');
        serial_port.write(array);
    }
    else
    {
        serial_port.write(array);
        ui->receiveEdit->insertPlainText(" ");
    }

}

//16进制显示
void Serial::serial_read()
{
    //QByteArray array=ui->sendEdit->toPlainText().toUtf8();
    QByteArray array=serial_port.readAll();
    //QByteArray array=ui->sendEdit->readAll();
    if(ui->show16Box->isChecked()==false)
    {
        //array=array.toHex(' ');
        QString receive=QString(array);
        ui->receiveEdit->insertPlainText(receive);
    }
    else if(ui->show16Box->isChecked()==true)
    {
        array=array.toHex(' ');
        QString receive=QString(array);
        ui->receiveEdit->insertPlainText(receive);
    }
}

//清空发送区
void Serial::on_clear_Button_clicked()
{
    ui->sendEdit->clear();
}

//清空接受区
void Serial::on_pushButton_clicked()
{
    ui->receiveEdit->clear();
}

//发送文件
void Serial::on_sendfile_clicked()
{
    QString file =QFileDialog::getOpenFileName();
    ui->showfile->setText(file);
    QFile f(file);
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,"warn","fail open");
    }
    QTextStream textInput(&f);
    QString lineStr;
    while(!textInput.atEnd ())
    {
        lineStr = textInput.readLine ();
    }
    QByteArray sendFile=lineStr.toLatin1 ();
    int cnt=sendFile.size ();
    QChar *sendData=lineStr.data ();
    if(ui->send16Box->isChecked ()==true)
    {
        for(int i=0;i<cnt;i++)
        {
            if(sendData[i]>='0'&&sendData[i]<='9')
                continue;
            else if(sendData[i]>='a'&&sendData[i]<='z')
                continue;
            else if(sendData[i]>='A'&&sendData[i]<='Z')
                continue;
            else
            {
                QMessageBox::warning (this,"warn","Invalid input, please reenter");
            }
        }
    }
    serial_port.write (sendFile);
}
