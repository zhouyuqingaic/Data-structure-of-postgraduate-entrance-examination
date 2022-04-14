#include<stdio.h>
#include <malloc.h>


typedef struct LNode{
    int data;   //数据
    LNode *next;    //下个节点
}LNode;     //链表节点
typedef struct{
    LNode *front;   //队头指针
    LNode *rear;    //队尾指针
}LQueue;   //链队列

void initLQueue(LQueue *lQueue){
    /*
     * 初始化线性队
     */
    lQueue->front=lQueue->rear=NULL;   //清空队列,并指向存储空间0的位置
}
bool isEmptyLQueue(LQueue *lQueue){
    /*
     * 判断队列是否空
     */
    return lQueue->front==NULL;
}
bool isFullLQueue(LQueue *lQueue){
    /*
     * 判断队列是否满
     */
    LNode *temp=(LNode *) malloc(sizeof (LNode));
    //如果无法再申请内存空间，则队列满了;能申请到的话则没满
    if(temp==NULL){
        return true;
    }else{
        free(temp); //释放掉申请的测试空间
        return false;
    }
}
bool enLQueue(LQueue *lQueue,int x){
    /*
     * 数据x进入顺序队
     */
    //队满 无法入队
    if(isFullLQueue(lQueue))
        return false;
    //创建x的节点
    LNode *temp=(LNode *) malloc(sizeof(LNode));
    temp->data=x;
    temp->next=NULL;
    //将节点挂在rear后并更新rear
    if(isEmptyLQueue(lQueue)){ //x节点为队列的第一个元素的特殊情况
        lQueue->front=lQueue->rear=temp;
    }else{
        //队列不为空，队尾指向x节点
        lQueue->rear->next = temp;
        lQueue->rear = temp;
    }

    return true;
}
bool deLQueue(LQueue *lQueue,int &x){
    /*
     * 队头数据出队
     */
    //队空 没有元素出队
    if(isEmptyLQueue(lQueue))
        return false;
    //出队数据
    x=lQueue->front->data;
    //删除队头节点 并 更新队列信息
    LNode *temp=lQueue->front;
    if(lQueue->rear==lQueue->front){ //队列中只有一个元素的情况
        free(lQueue->front);
        initLQueue(lQueue);
    }else{ //队列中有2个以上元素
        lQueue->front=lQueue->front->next;
        free(temp);
    }
    return true;
}

void testLQueue(){
    /*
     * 测试队列
     */
    //创建队列
    LQueue *lQueue=(LQueue *) malloc(sizeof(LQueue));
    initLQueue(lQueue);
    //元素入队列
    for(int i=0;i<8;i++){
        if(enLQueue(lQueue,i))
            printf("元素:%d 入队成功!!!\n",i);
        else
            printf("元素:%d 入队失败!!!\n",i);
    }

    printf("1---------------------------------------------\n");

    int temp;
    for(int i=0;i<3;i++){
       if(deLQueue(lQueue,temp))
           printf("元素:%d 出队成功!!!\n",temp);
       else
           printf("出队失败!\n");
    }

    printf("2---------------------------------------------\n");

    for(int i=0;i<8;i++){
        if(enLQueue(lQueue,i+1000))
            printf("元素:%d 入队成功!!!\n",i+1000);
        else
            printf("元素:%d 入队失败!!!\n",i+1000);
    }

    printf("3--------------------------------------------\n");

    for(int i=0;i<20;i++){
        if(deLQueue(lQueue,temp))
            printf("元素:%d 出队成功!!!\n",temp);
        else
            printf("出队失败!\n");
    }

    //释放队列
    free(lQueue);
}
