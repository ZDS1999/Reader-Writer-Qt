#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->btnAddReader->setEnabled(false);
    ui->btnAddWriter->setEnabled(false);
    ui->radioButton->setChecked(true);

    this->setFixedSize(720, 340);
    this->setWindowTitle("Reader Writer Problem");

    connect(ui->btnQuit, &QPushButton::clicked, this, &Widget::close);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnStart_clicked()
{
   if (ui->radioButton->isChecked())
       option = ReaderFirst;
   else
       option = WriterFirst;
    ui->btnAddReader->setEnabled(true);
    ui->btnAddWriter->setEnabled(true);
}


void Widget::updateView()
{
    for (int i = 0; i < 10; i++ ) {
        if (people[i] == Reader)
            setColor(i, QString("blue"));
        else if (people[i] == Writer)
            setColor(i, QString("red"));
        else
            setColor(i, QString("white"));
    }
    ui->labReaderCount->setText(QString::number(readCount));
    ui->labWriterCount->setText(QString::number(writeCount));
    ui->labVal->setText(QString::number(value));
}

void Widget::setColor(int index, const QString &color)
{
    // qDebug() << index << " : " << color;
    switch(index) {
        case 0:
            ui->lab0->setStyleSheet(QString("background: %1").arg(color));
            break;
        case 1:
            ui->lab1->setStyleSheet(QString("background: %1").arg(color));
        break;
        case 2:
            ui->lab2->setStyleSheet(QString("background: %1").arg(color));
        break;
        case 3:
            ui->lab3->setStyleSheet(QString("background: %1").arg(color));
        break;
        case 4:
            ui->lab4->setStyleSheet(QString("background: %1").arg(color));
        break;
        case 5:
            ui->lab5->setStyleSheet(QString("background: %1").arg(color));
        break;
        case 6:
            ui->lab6->setStyleSheet(QString("background: %1").arg(color));
        break;
        case 7:
            ui->lab7->setStyleSheet(QString("background: %1").arg(color));
        break;
        case 8:
            ui->lab8->setStyleSheet(QString("background: %1").arg(color));
        break;
        case 9:
            ui->lab9->setStyleSheet(QString("background: %1").arg(color));
        break;
        default:
            qDebug() << "should never come here";
        break;
    }
}

void Widget::on_btnAddReader_clicked()
{
    MyThread *thread = new MyThread(Reader, option);
    QObject::connect(thread, &MyThread::sigUpdate, this, &Widget::updateView);
    thread->start();
}

void Widget::on_btnAddWriter_clicked()
{
    MyThread *thread = new MyThread(Writer, option);
    QObject::connect(thread, &MyThread::sigUpdate, this, &Widget::updateView);
    thread->start();
}
