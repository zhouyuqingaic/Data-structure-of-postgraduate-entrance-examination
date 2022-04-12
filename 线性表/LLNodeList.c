#include<stdio.h>
#include <malloc.h>

//以下为带头节点的单链表
typedef struct LNode{
    int data;
    struct LNode *next;
}LNode;

void insertSort(int a[],int lengthOfA){
    /*
     * 插入排序，用于将a生序排列
     */
    if(lengthOfA==0||lengthOfA==1) //a为空与a只有一个元素时不必排序
        return;
    int temp,i,j;
    for(i=1;i<lengthOfA;i++){
        temp=a[i]; //待插关键字存入temp
        j=i-1;
        //将待插入位置后的元素全部后移
        while(a[j]>temp&&j>=0){
            a[j+1]=a[j];
            j--;
        }
        //将temp插入待插入位置
        a[j+1]=temp;
    }
}
void initListLNode(LNode *listHead){
    /*
     * 初始化但链表头节点
     */
    listHead->data=0; //头节点的值代表的链表元素个数
    listHead->next=NULL; //头节点后续节点为空
}
void createListLNode(LNode *listHead,int a[],int lengthOfA){
   /*
    * 通过数组创建链表,向头节点listHead后边添加元素
    */
    insertSort(a,lengthOfA); //对插入数组进行排序
    LNode *currentLNode=listHead;
    for(int i=0;i<lengthOfA;i++){
        //创建存储a[i]的链表节点
        LNode *tempLNode=(LNode *) malloc(sizeof (LNode));
        tempLNode->data=a[i];
        tempLNode->next=NULL;
        //将新节点挂到currentNode当前节点后面
        currentLNode->next=tempLNode;
        //更新当前节点
        currentLNode=currentLNode->next;
        //更新链表元素数
        listHead->data+=1;
    }
}
void emptyListLNode(LNode *listHead){
    /*
     * 清空listHead头节点指向的单链表
     */
    LNode *currentLNode=listHead->next;
    initListLNode(listHead); //清空头节点数据
    while(currentLNode!=NULL){
        LNode *tempLNode=currentLNode->next;
        //删除当前节点
//        printf("delete currentLNode:%p 's data is:%d\n",currentLNode,currentLNode->data);
        free(currentLNode);
        //自动移动到下个节点
        currentLNode=tempLNode;
    }
}
void printListLNode(LNode *listHead){
    /*
     * 展示listHead头节点指向的单链表
     */
    LNode *currentLNode=listHead->next;
    while(currentLNode!=NULL){
        printf("currentLNode:%p 's data is:%d\n",currentLNode,currentLNode->data);
        currentLNode=currentLNode->next;
    }
}
int getListLNodeLength(LNode *listHead){
    /*
     * 获取listHead指向的链表数据部分的长度
     */
    return listHead->data;
}
LNode *mergeLNodeList_diminish(LNode *aListHead,LNode *bListHead){
    /*
     * 合并升序链表a与升序链表b,返回和并后的递减结果c
     */
    //创建结果链表头节点
    LNode *listHead=(LNode *) malloc(sizeof (LNode));
    initListLNode(listHead);
    //指向两个链表数据节点的指针
    LNode *currentAListNode=aListHead->next;
    LNode *currentBListNode=bListHead->next;

    while(currentAListNode!=NULL&&currentBListNode!=NULL){
        //将较小数据节点 头插法 挂到结果链表上
        LNode *temp=(LNode *) malloc(sizeof (LNode));
        if(currentAListNode->data < currentBListNode->data){
            temp->data=currentAListNode->data;

            //将数据节点 头插法 挂到结果链表上
            temp->next=listHead->next;
            listHead->next=temp;

            currentAListNode=currentAListNode->next;    //指向A链表下个结点
        }else{
            temp->data=currentBListNode->data;

            //将数据节点 头插法 挂到结果链表上
            temp->next=listHead->next;
            listHead->next=temp;

            currentBListNode=currentBListNode->next;    //指向B链表下个结点
        }
    }
    //处理某个有剩余未处理节点的链表
    while(currentAListNode!=NULL){
        LNode *temp=(LNode *) malloc(sizeof (LNode));
        temp->data=currentAListNode->data;

        //将数据节点 头插法 挂到结果链表上
        temp->next=listHead->next;
        listHead->next=temp;

        currentAListNode=currentAListNode->next;    //指向A链表下个结点
    }
    while(currentBListNode!=NULL){
        LNode *temp=(LNode *) malloc(sizeof (LNode));
        temp->data=currentBListNode->data;

        //将数据节点 头插法 挂到结果链表上
        temp->next=listHead->next;
        listHead->next=temp;

        currentBListNode=currentBListNode->next;    //指向B链表下个结点
   }

    return listHead;

}
LNode *mergeLNodeList_increase(LNode *aListHead,LNode *bListHead){
    /*
     * 合并降序链表a与降序链表b,返回和并后的递减结果c
     */
    //创建结果链表头节点
    LNode *listHead=(LNode *) malloc(sizeof (LNode));
    initListLNode(listHead);
    listHead->data=aListHead->data+bListHead->data; //设置结果链表的数据节点数目
    //指向结果链的指针
    LNode *currentListLNode=listHead;
    //指向两个链表数据节点的指针
    LNode *currentAListNode=aListHead->next;
    LNode *currentBListNode=bListHead->next;

    while(currentAListNode!=NULL&&currentBListNode!=NULL){
        //将较小数据节点挂到结果链表上
        LNode *temp=(LNode *) malloc(sizeof (LNode));
        if(currentAListNode->data < currentBListNode->data){
            temp->data=currentAListNode->data;
            temp->next=NULL;
            currentListLNode->next=temp;

            currentAListNode=currentAListNode->next;    //指向A链表下个结点
        }else{
            temp->data=currentBListNode->data;
            temp->next=NULL;
            currentListLNode->next=temp;

            currentBListNode=currentBListNode->next;    //指向B链表下个结点
        }
        //结果链表指针更新
        currentListLNode=currentListLNode->next;
    }
    //处理某个有剩余未处理节点的链表
    while(currentAListNode!=NULL){
        LNode *temp=(LNode *) malloc(sizeof (LNode));
        temp->data=currentAListNode->data;
        temp->next=NULL;
        currentListLNode->next=temp;

        currentAListNode=currentAListNode->next;    //指向A链表下个结点

        //结果链表指针更新
        currentListLNode=currentListLNode->next;
    }
    while(currentBListNode!=NULL){
        LNode *temp=(LNode *) malloc(sizeof (LNode));
        temp->data=currentBListNode->data;
        temp->next=NULL;
        currentListLNode->next=temp;

        currentBListNode=currentBListNode->next;    //指向B链表下个结点
        //结果链表指针更新
        currentListLNode=currentListLNode->next;
    }

    return listHead;
}

void testListLNode(){
    /*
     * 测试单链表
     */
    LNode *listHead01=(LNode *) malloc(sizeof (LNode)); //创建头节点
    LNode *listHead02=(LNode *) malloc(sizeof (LNode)); //创建头节点
    int a1[5]={33,66,88,55,44};
    int a2[4]={99,11,77,22};
    //初始化头节点
    initListLNode(listHead01);
    initListLNode(listHead02);
    //通过数组创建链表
    createListLNode(listHead01,a1,5);
    createListLNode(listHead02,a2,4);



    //展示链表数据
    printf("开始展示链表数据------------------------------------\n");
    printListLNode(listHead01);
    printf(">>>----------------<<<\n");
    printListLNode(listHead02);
    printf("展示链表数据结束------------------------------------\n");

    //生序和并两个链表
    printf("生序和并两个链表结果---------------------------------\n");
    LNode *mergeListHead_increase= mergeLNodeList_increase(listHead01,listHead02);
    printListLNode(mergeListHead_increase);

    //降序和并两个链表
    printf("降序和并两个链表结果---------------------------------\n");
    LNode *mergeListHead_diminish= mergeLNodeList_diminish(listHead01,listHead02);
    printListLNode(mergeListHead_diminish);


    //清空链表
    emptyListLNode(listHead01);
    emptyListLNode(listHead02);
    emptyListLNode(mergeListHead_increase);
    emptyListLNode(mergeListHead_diminish);

    //清除头节点
    free(listHead01);
    free(listHead02);
    free(mergeListHead_increase);
}
