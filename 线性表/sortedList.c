#include<stdio.h>

const int maxSize=1000;

typedef struct Sqlist{
    int data[maxSize];
    int length;
}Sqlist;
void initSqlit(Sqlist &L){
    /*
     * 初始化顺序表
     */
    L.length=0;
}
int findBiggerElem(Sqlist L,int x){
    /*
     * 返回顺序表中第一个比x大的元素的位置
     */
    for(int i=0;i<L.length;i++)
        if(L.data[i]>x)
            return i;
    return L.length;
}
void insetElem(Sqlist &L,int x){
    /*
     * 向顺序表中插入值为x的数据(升序插入)
     */
    int target_index= findBiggerElem(L,x); //找到第一个比x大的元素的下标
    //将下标以及其往后的元素全部后移动
    for(int i=L.length;i>target_index;i--)
        L.data[i]=L.data[i-1];
    L.data[target_index]=x; //x放入目标位置
    L.length+=1; //更新顺序表长度
}
int findElem(Sqlist L,int e){
    /*
     * 返回e元素在线性表中的位置
     */
    for(int i=0;i<L.length;i++)
        if(L.data[i]==e)
            return i;
    return -1; //没有找到目标元素返回-1
}
int printSqlit(Sqlist L){
    /*
     * 展示顺序表中所有元素
     */
    for(int i=0;i<L.length;i++)
        printf("%d ",L.data[i]);
    printf("\n");
}
int deleteElem(Sqlist &L,int x){
    /*
     * 删除x元素
     */
    int target_index=findElem(L,x); //找到x元素的下标
    if(target_index==-1)
        return 0;   //没有找到x元素,返回0表示删除失败
    //将x元素的下标后面的元素前移
    for(int i=target_index+1;i<L.length;i++)
        L.data[i]=L.data[i+1];
    L.length-=1;  //更新顺序表长度
    return 1; //成功删除返回1
}

int testSqlist(){
    /*
     * 测试顺序表功能
     */
    Sqlist sq;
    initSqlit(sq); //初始化顺序表
    printf("findElem(sq,1):%d\n", findElem(sq,1));
    printf("findBiggerElem(sq,1):%d\n", findBiggerElem(sq,1));
    //删除元素
    if(deleteElem(sq,3)) {
        printf("after deleteElem(sq,3) ");
        printSqlit(sq);
    }
    if(deleteElem(sq,1)) {
        printf("after deleteElem(sq,1) ");
        printSqlit(sq);
    }

    //插入元素
    insetElem(sq,8);
    insetElem(sq,1);
    insetElem(sq,22);
    insetElem(sq,13);
    insetElem(sq,5);

    //展示元素
    printSqlit(sq);

    //删除元素
    if(deleteElem(sq,3)) {
        printf("after deleteElem(sq,3) ");
        printSqlit(sq);
    }
    if(deleteElem(sq,1)) {
        printf("after deleteElem(sq,1) ");
        printSqlit(sq);
    }

    return 0;
}
