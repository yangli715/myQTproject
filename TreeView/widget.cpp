#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initTreeWidget();
    connect(ui->addButton,SIGNAL(clicked()),this,SLOT(addTree()));
    connect(ui->deleteButton,SIGNAL(clicked()),this,SLOT(deleteTree()));
}

//初始化
void Widget::initTreeWidget()
{
    QStandardItemModel *model = new QStandardItemModel(ui->treeView);
    QStandardItem *item1 = new QStandardItem(QStringLiteral("控制器1"));
    model->appendRow(item1);

    QStandardItem *item11 = new QStandardItem(QString("传感器1"));
    QStandardItem *item12 = new QStandardItem(QString("传感器2"));
    QStandardItem *item13 = new QStandardItem(QString("传感器3"));
    item1->appendRow(item11);
    item1->appendRow(item12);
    item1->appendRow(item13);

    QStandardItem *item11_1 = new QStandardItem(QString("参数1"));
    QStandardItem *item11_2 = new QStandardItem(QString("参数2"));
    QStandardItem *item11_3 = new QStandardItem(QString("参数3"));
    item11->appendRow(item11_1);
    item11->appendRow(item11_2);
    item11->appendRow(item11_3);


    QStandardItem *item2 = new QStandardItem(QStringLiteral("控制器2"));
    QStandardItem *item3 = new QStandardItem(QStringLiteral("控制器3"));
    model->appendRow(item2);
    model->appendRow(item3);

    QStandardItem *item21 = new QStandardItem(QString("传感器1"));
    QStandardItem *item22 = new QStandardItem(QString("传感器2"));
    item2->appendRow(item21);
    item2->appendRow(item22);

    ui->treeView->setHeaderHidden(true);
    ui->treeView->setModel(model);
}

void Widget::addTree()
{
    QModelIndex current = ui->treeView->currentIndex();
    //qDebug()<<current;

}

void Widget::deleteTree()
{
    ui->treeView->selectionModel()->clear();
}

Widget::~Widget()
{
    delete ui;
}

