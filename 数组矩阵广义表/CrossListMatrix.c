#include<stdio.h>
#include <malloc.h>

const int MaxSize=100;

//十字链表 数据节点
typedef struct OLNode{
    int row,col;    //行号与列号
    struct OLNode *right,*down; //指向当前节点的左边与下方节点的指针
    int data; //节点的值
}OLNode;
//十字链表 头节点
typedef struct{
    OLNode *rhead,*chead; //指向头节点数组的指针
    int row,column,nodes; //矩阵行数,列数,非零节点数
}CrossList;

bool createCrossListMatrix(CrossList *&crossList,int a[][MaxSize],int rowOfA,int columnOfA){
    /*
     * 通过二维数组利用十字链表创建矩阵
     */
    //传入数据合规范检查
    if(0>rowOfA && rowOfA>MaxSize && 0>columnOfA && columnOfA > MaxSize) {
        return false;
    }
    //创建十字链表
    crossList = (CrossList *) malloc(sizeof(CrossList));
    crossList->row=rowOfA;
    crossList->column=columnOfA;
    crossList->nodes=rowOfA*columnOfA;
    //创建 行头节点数组 与 列头节点数组
    crossList->rhead=(OLNode *)malloc(sizeof(OLNode)*crossList->row);
    crossList->chead=(OLNode *)malloc(sizeof(OLNode)*crossList->column);
    //为 头节点数组 赋初始值
    for(int i=0;i<crossList->row;i++) {
        crossList->rhead[i].right=NULL;
        crossList->rhead[i].down=NULL;
    }
    for(int i=0;i<crossList->column;i++){
        crossList->chead[i].right=NULL;
        crossList->chead[i].down=NULL;
    }
    //建立 列辅助指针数组 ,每个元素指向当前列的最后一个节点
    OLNode *columnTemps[MaxSize];
    for(int i=0;i<crossList->column;i++)
        columnTemps[i]=&crossList->chead[i];
    //建立 行辅助指针数组 ,每个元素指向当前行的最后一个节点
    OLNode *rowTemps[MaxSize];
    for(int i=0;i<crossList->row;i++)
        rowTemps[i]=&crossList->rhead[i];

    //填充矩阵
    for(int i=0;i<crossList->row;i++){
        for(int j=0;j<crossList->column;j++){
            if(a[i][j]!=0) {
                //创建数据节点
                OLNode *p = (OLNode *) malloc(sizeof(OLNode));
                //设置节点的行号,列号,值
                p->row=i;
                p->col=j;
                p->data=a[i][j];
                p->down=NULL;
                p->right=NULL;
                //将数据节点挂到当前行
                rowTemps[i]->right=p;
                rowTemps[i]=p;
                //将当前数据节挂当当前列
                columnTemps[j]->down=p;
                columnTemps[j]=p;
            }
        }
    }

    return true;
}

OLNode *getCrossListNode(CrossList *crossList,int i,int j){
    /*
     * 从十字链表取i行 j列的节点
     */
    //创建结果节点
    OLNode *p = (OLNode *) malloc(sizeof(OLNode));
    p->row=i;
    p->col=j;
    //设置默认值0
    p->data=0;
    //获取目标行的第一个节点
    OLNode *targetRowNode=crossList->rhead[i].right;
    while(targetRowNode){
        //如果当前行中有目标节点,赋值并跳出循环
        if(targetRowNode->col==j){
            p->data=targetRowNode->data;
            break;
        }
        targetRowNode=targetRowNode->right; //移动到当前行的下个节点
    }
    //返回结果
    return p;
}

OLNode showCrossListNode(CrossList *crossList){
    /*
     * 展示十字链表矩阵
     */
    OLNode *temp;
    for(int i=0;i<crossList->row;i++) {
        for(int j=0;j<crossList->column;j++){
            //获取当前位置的元素并打印
            temp=getCrossListNode(crossList,i,j);
            printf("%8d",temp->data);
        }
        printf("\n");
    }
}



void testCrossListMatrix (){
    int array[][MaxSize]={
    {99,11,12,13},
    {20,0,22,23},
    {30,31,0,33}
    };
    int otherArray[][MaxSize]={
    {100,0,0},
    {200,201,0},
    {300,301,302},
    {400,401,402}
    };

    CrossList *crossList01=NULL;
    CrossList *crossList02=NULL;

    if(
        !createCrossListMatrix(crossList01,array,3,4) ||
        !createCrossListMatrix(crossList02,otherArray,4,3)
    ){
        printf("创dfs建矩阵失败!\n");
        return;
    }
    printf("sparseMatrix01矩阵,元素个数:%d,行数:%d,列数:%d\n",
           crossList01->nodes,crossList01->row,crossList01->column);
    showCrossListNode(crossList01);
    printf("sparseMatrix02矩阵,元素个数:%d,行数:%d,列数:%d\n",
           crossList01->nodes,crossList01->row,crossList01->column);
    showCrossListNode(crossList02);

}

int main(){
    testCrossListMatrix();

    return 0;
}

