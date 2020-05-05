#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "globals.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(Type tpye, Option option);

    // 读者优先
    void reader();
    void writer();
    // 写者优先
    void reader2();
    void writer2();
    // 对缓冲区的读写
    void read();
    void write();
    // 队列的插入和删除
    void insertReader();
    void insertWriter();
    void deQueue();

protected:
    virtual void run() override;

private:
    Type type;
    Option option;


signals:
    void sigUpdate();
};

#endif // MYTHREAD_H
