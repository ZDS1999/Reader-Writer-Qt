#ifndef WIDGET_H
#define WIDGET_H

#include "ui_widget.h"
#include "globals.h"
#include "mythread.h"
#include <QWidget>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void updateView();
    void setColor(int index, const QString &color);
public:
    Ui::Widget *ui;

    QLabel * labels[10] = {
        ui->lab0, ui->lab1, ui->lab2, ui->lab3, ui->lab4,
        ui->lab5, ui->lab6, ui->lab7, ui->lab8, ui->lab9
    };

private slots:
    void on_btnStart_clicked();

    void on_btnAddReader_clicked();
    void on_btnAddWriter_clicked();
};
#endif // WIDGET_H
