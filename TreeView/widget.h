#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QDebug>
#include<QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    void initTreeWidget();

private slots:
    void addTree();
    void deleteTree();
};
#endif // WIDGET_H
