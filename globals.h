#ifndef GLOBALS_H
#define GLOBALS_H

typedef enum { ReaderFirst, WriterFirst
} Option;

typedef enum {
    Reader, Writer, None
} Type;

// 读者写者公用的缓冲区
extern int value;
// 读者数量
extern int readCount;
// 写者数量
extern int writeCount;
// 标记队列尾部
extern int lastIndex;

// 算法选择， 读者优先或写者优先
extern Option option;

// 访问缓冲区的队列
extern Type people[10];

#endif // GLOBALS_H
