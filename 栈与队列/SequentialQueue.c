#include<stdio.h>
#include <malloc.h>

const int maxSize=5;
typedef struct{
    int data[maxSize];  //顺序栈存储空间
    int front;  //队头指针
    int rear;   //队尾指针
}SqQueue;

void initSqQueue(SqQueue *sqQueue){
    /*
     * 初始化线性队
     */
    sqQueue->front=sqQueue->rear=0; //清空队列,并指向存储空间0的位置
}
bool isEmptySqQueue(SqQueue *sqQueue){
    /*
     * 判断队列是否空
     */
    return sqQueue->front==sqQueue->rear;
}
bool isFullSqQueue(SqQueue *sqQueue){
    /*
     * 判断队列是否满
     */
    return (sqQueue->rear+1)%maxSize==sqQueue->front;
}
bool enSqQueue(SqQueue *sqQueue,int x){
    /*
     * 数据x进入顺序队
     */
    //队满 无法入队
    if(isFullSqQueue(sqQueue))
        return false;
    //入队
    sqQueue->rear=(sqQueue->rear+1)%maxSize;
    sqQueue->data[sqQueue->rear]=x;
    return true;
}
bool deSqQueue(SqQueue *sqQueue,int &x){
    /*
     * 队头数据出队
     */
    //队空 没有元素出队
    if(isEmptySqQueue(sqQueue))
        return false;
    //出队
    sqQueue->front=(sqQueue->front+1)%maxSize;
    x=sqQueue->data[sqQueue->front];
    return true;
}

void testSqQueue(){
    /*
     * 测试队列
     */
    //创建队列
    SqQueue *sqQueue=(SqQueue *) malloc(sizeof(SqQueue));
    initSqQueue(sqQueue);
    //元素入队列
    for(int i=0;i<8;i++){
        if(enSqQueue(sqQueue,i))
            printf("元素:%d 入队成功!!!\n",i);
        else
            printf("元素:%d 入队失败!!!\n",i);
    }

    printf("1---------------------------------------------\n");

    int temp;
    for(int i=0;i<3;i++){
       if(deSqQueue(sqQueue,temp))
           printf("元素:%d 出队成功!!!\n",temp);
       else
           printf("出队失败!\n");
    }

    printf("2---------------------------------------------\n");

    for(int i=0;i<8;i++){
        if(enSqQueue(sqQueue,i+1000))
            printf("元素:%d 入队成功!!!\n",i+1000);
        else
            printf("元素:%d 入队失败!!!\n",i+1000);
    }

    printf("3--------------------------------------------\n");

    for(int i=0;i<10;i++){
        if(deSqQueue(sqQueue,temp))
            printf("元素:%d 出队成功!!!\n",temp);
        else
            printf("出队失败!\n");
    }

    //释放队列
    free(sqQueue);
}
