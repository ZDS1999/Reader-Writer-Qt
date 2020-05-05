#include "mythread.h"
#include <QDebug>
#include <QMutex>

// 读者优先所需要的锁
QMutex mutex, rmutex;

// 写者优先需要的额外锁
QMutex wmutex, readable;

MyThread::MyThread(Type type, Option option)
{
    this->type = type;
    this->option = option;
}

void MyThread::run()
{
    if (type == Reader) {
        if (option == ReaderFirst) {
            reader();
        } else {
            reader2();
        }
    } else {
        if (option == ReaderFirst) {
            writer();
        } else {
            writer2();
        }
    }
    QThread::exit(0);
}

void MyThread::read()
{
    // reading
    qDebug() << "reader " << readCount << " start to read...";
    QThread::sleep(4);
    qDebug() << "reader " << readCount << " read value: " << value;
    // reading ends
}

void MyThread::write()
{
    // writing
    qDebug() << "writer " << writeCount << " start to write...";
    QThread::sleep(4);
    value = rand() % 20 + 1;
    qDebug() << "writer " << writeCount << " write value: " << value;
    // writing ends
}

/*********************
 *       读者优先     *
 * *******************/

void MyThread::reader()
{
    rmutex.lock();			// 申请访问readCount
    if (readCount == 0)
        mutex.lock();		// 申请访问数据区，阻止写者进入
    readCount++;
    insertReader();
    rmutex.unlock();

    read();					// 对于缓冲区的读操作可以并行

    rmutex.lock();			// 申请访问readCount
    readCount--;
    deQueue();
    if (readCount == 0)
        mutex.unlock();
    rmutex.unlock();
}

void MyThread::writer()
{
    mutex.lock();			// 申请访问数据区

    writeCount++;
    insertWriter();
    write();
    writeCount--;
    deQueue();

    mutex.unlock();
}

/*********************
 *       写者优先     *
 * *******************/

void MyThread::reader2()
{
    readable.lock();		// 检查是否存在写者，若没有则占用，反之等待
    rmutex.lock();			// 申请访问readCount
    if (readCount == 0)
        mutex.lock();		// 申请访问数据区，阻止写者进入
    readCount++;
    insertReader();
    rmutex.unlock();
    readable.unlock();

    read();

    rmutex.lock();			// 申请访问readCount
    readCount--;
    deQueue();
    if (readCount == 0)
        mutex.unlock();
    rmutex.unlock();
}

void MyThread::writer2()
{
    wmutex.lock();			// 申请访问writeCount
    if (writeCount == 0)
        readable.lock();	// 如果是第一个写者，则阻止后续读者进入
    writeCount++;
    insertWriter();
    wmutex.unlock();

    mutex.lock();			// 申请访问数据区，阻止其他写者进入
    write();
    mutex.unlock();

    wmutex.lock();			// 申请访问writeCount
    writeCount--;
    deQueue();
    if (writeCount == 0)
        readable.unlock();	// 最后一个写者完成，允许后续读者进入
    wmutex.unlock();
}

/*********************
 *       队列操作     *
 * *******************/

void MyThread::insertReader()
{
    int writerIn;
    for (writerIn = 0; writerIn < lastIndex; writerIn++) {
        if (people[writerIn] == Writer)
            break;
    }
    /* no writer in queue */
    if (writerIn == lastIndex)
        people[lastIndex++] = Reader;
    else {
        people[writerIn++] = Reader;
        for (; writerIn <= lastIndex; writerIn++) {
            people[writerIn] = Writer;
        }
        lastIndex++;
    }
    emit sigUpdate();
}

void MyThread::insertWriter()
{
    people[lastIndex++] = Writer;
    emit sigUpdate();
}

void MyThread::deQueue()
{
    for (int i = 0; i < lastIndex - 1; i++) {
        people[i] = people[i+1];
    }
    people[--lastIndex] = None;
    emit sigUpdate();
}
