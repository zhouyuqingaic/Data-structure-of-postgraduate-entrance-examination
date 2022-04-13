#include<stdio.h>
#include <malloc.h>

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

//带头节点的双端链表
typedef struct DLNode{
    int data;   //节点数据域
    struct DLNode *prior;   //指向前驱节点
    struct DLNode *next;    //指向后继节点
}DLNode;

void initListDLNode(DLNode *dListHead){
    /*
     * 初始化双链表头结点
     */
    dListHead->data=0;  //节点头的值带表链表的元素个数
    dListHead->prior=NULL; //头节点的上一个元素为空
    dListHead->next=NULL; //头节点暂时无继节点
}
void createListDLNode(DLNode *dListHead,int a[],int lengthOfA) {
    /*
     * 通过数组创建双链表,向头节点dListHead后边添加元素
     */
    insertSort(a, lengthOfA); //对插入数组进行排序
    DLNode *currentDLNode=dListHead;

    for(int i=0;i<lengthOfA;i++){
        //创建存储a[i]的链表节点
        DLNode *temp=(DLNode *) malloc(sizeof (DLNode));
        temp->data=a[i];
        temp->next=NULL;

        //将新节点挂到currentNode当前节点后面
        temp->prior=currentDLNode;
        currentDLNode->next=temp;

        //更新当前节点
        currentDLNode=currentDLNode->next;

        //更新链表元素数
        dListHead->data+=1;
    }
}
void emptyListDLNode(DLNode *dListHead) {
    /*
     * 清空listHead头节点指向的单链表
     */
    DLNode *currentDLNode = dListHead->next;
    while(currentDLNode!=NULL){

        //删除当前节点
        printf("delete currentDLNode:%p 's data is:%d\n",currentDLNode,currentDLNode->data);
        free(currentDLNode);

        //移到下一个结点
        currentDLNode=currentDLNode->next;
    }
    dListHead->data=0; //数据容量为0
}
void printListDLNode(DLNode *dListHead){
    /*
     * 展示dListHead头节点指向的双链表
     */
    DLNode *currentDLNode=dListHead->next;
    while(currentDLNode!=NULL){
        printf("currentDLNode:%p 's data is:%d\n",currentDLNode,currentDLNode->data);
        currentDLNode=currentDLNode->next;
    }
}
DLNode *getElemDataListDLNode(DLNode *dListHead,int e){
    /*
     * 获取双链接表中第一个data为e的节点的指针
     */
    DLNode *currentDLNode=dListHead->next;
    //遍历所有节点直到找到
    while(currentDLNode!=NULL){
        if(currentDLNode->data==e)
            return currentDLNode;
        currentDLNode=currentDLNode->next;
    }
    //没有找到目标节点
    return NULL;
}
DLNode *getElemPositionListDLNode(DLNode *dListHead,int p){
    /*
     * 获取双链表中位置为p上的链表元素的指针(从0开始计数)
     */
    DLNode *currentDLNode=dListHead->next;
    if(p >= dListHead->data || p<0)
        return NULL; //位置索引超过最大范围
    for(int i=0;i<p;i++)
        currentDLNode=currentDLNode->next;
    return currentDLNode;
}

bool insertElemAfterDataListDLNode(DLNode *dListHead,int e,int d){
    /*
     * 在元素e后面插入第一个元素d的元素后面
     */
    DLNode *targetDLNode= getElemDataListDLNode(dListHead,d);
    //值为d的元素不存在
    if(targetDLNode==NULL)
        return false;

    //创建节点e
    DLNode *tempDLNode=(DLNode *) malloc(sizeof (DLNode));
    tempDLNode->data=e;
    //将节点e挂在目标节点后
    tempDLNode->prior=targetDLNode;
    tempDLNode->next=targetDLNode->next;
    if(targetDLNode->next!=NULL)
        targetDLNode->next->prior=tempDLNode;
    targetDLNode->next=tempDLNode;

    //添加成功,元素数量增加1
    dListHead->data+=1;
    return true;
}
bool insertElemAfterPositionListDLNode(DLNode *dListHead,int e,int p){
    /*
     * 将元素e插入位置为p的元素后面
     */
    DLNode *targetDLNode= getElemPositionListDLNode(dListHead,p);
    //p位置上的元素不存在
    if(targetDLNode==NULL)
        return false;

    //创建节点e
    DLNode *tempDLNode=(DLNode *) malloc(sizeof (DLNode));
    tempDLNode->data=e;
    //将节点e挂在目标节点后
    tempDLNode->prior=targetDLNode;
    tempDLNode->next=targetDLNode->next;
    if(targetDLNode->next!=NULL)
        targetDLNode->next->prior=tempDLNode;
    targetDLNode->next=tempDLNode;

    //添加成功,元素数量增加1
    dListHead->data+=1;
    return true;
}
bool deleteElemPositionListDLNode(DLNode *dListHead,int p){
    /*
     * 删除位置为p的节点
     */
    DLNode *targetDLNode= getElemPositionListDLNode(dListHead,p);
    //p位置上的元素不存在
    if(targetDLNode==NULL)
        return false;

    //将目标节点删除
    targetDLNode->prior->next=targetDLNode->next;
    if(targetDLNode->next!=NULL)
        targetDLNode->next->prior=targetDLNode->prior;
    free(targetDLNode);

    //添加成功,元素数量减少1
    dListHead->data-=1;
    return true;

}
bool deleteElemDataListDLNode(DLNode *dListHead,int d){
    /*
     * 删除第一个元素值为d的节点
     */
    DLNode *targetDLNode= getElemDataListDLNode(dListHead,d);
    //值为d的元素不存在
    if(targetDLNode==NULL)
        return false;

    //将目标节点删除
    targetDLNode->prior->next=targetDLNode->next;
    if(targetDLNode->next!=NULL)
        targetDLNode->next->prior=targetDLNode->prior;
    free(targetDLNode);

    //添加成功,元素数量减少1
    dListHead->data-=1;
    return true;
}

void testDListLNode(){
    /*
     * 测试双链表
     */
    DLNode *dlistHead01=(DLNode *) malloc(sizeof (DLNode)); //创建头节点
    //初始化头节点
    initListDLNode(dlistHead01);

    int a1[5]={11,33,22,55,44};

    //通过数组创建链表
    createListDLNode(dlistHead01,a1,5);

    //插入元素
    insertElemAfterPositionListDLNode(dlistHead01,1,2020);
    insertElemAfterPositionListDLNode(dlistHead01,3,2021);
    insertElemAfterPositionListDLNode(dlistHead01,5,2022);

    insertElemAfterPositionListDLNode(dlistHead01,2020,0);
    insertElemAfterPositionListDLNode(dlistHead01,2021,2);
    insertElemAfterPositionListDLNode(dlistHead01,2022,4);

    //展示双链表
    printf("展示双链表-------------------------------------------------------------------------------\n");
    printListDLNode(dlistHead01);

    //删除指定位置上的元素
    deleteElemPositionListDLNode(dlistHead01,2020);
    deleteElemPositionListDLNode(dlistHead01,2021);
    deleteElemPositionListDLNode(dlistHead01,2022);

    deleteElemPositionListDLNode(dlistHead01,1);
    deleteElemPositionListDLNode(dlistHead01,2);
    deleteElemPositionListDLNode(dlistHead01,3);

    //展示双链表
    printf("展示双链表-------------------------------------------------------------------------------\n");
    printListDLNode(dlistHead01);

    printf("结束     -------------------------------------------------------------------------------\n");
    //清空双链表
    emptyListDLNode(dlistHead01);

    //清除双链表头节点
    free(dlistHead01);
}
