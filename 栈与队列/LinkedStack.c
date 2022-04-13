#include<stdio.h>
#include <malloc.h>

typedef struct StackLNode{
    int data; //链栈节点数据域
    struct StackLNode *next; //链栈节点指针域
}StackLNode; //链栈节点

void initStackLNode(StackLNode *stackLNode){
    /*
     * 初始化链栈
     */
    stackLNode->data=0; //栈头节点的data表明栈中元素数
    stackLNode->next=NULL;
}
bool isEmptyStackLLNode(StackLNode *stackLNode){
    /*
     * 判断栈是否为空
     */
    return stackLNode->next==NULL;
}
bool pushStackLLNode(StackLNode *stackLNode,int x){
    /*
     * 数据x进入链接栈(利用头插入法，插入头节点后)
     */
    StackLNode *temp=(StackLNode *) malloc(sizeof (StackLNode));
    if(temp==NULL)
        return false;

    temp->data=x;
    temp->next=stackLNode->next;
    stackLNode->next=temp;

    //入栈成功,栈元素数据减少
    stackLNode->data++;
    return true;
}
bool popStackLLNode(StackLNode *stackLNode,int &x){
    /*
     * 栈定元素出栈
     */
    if(isEmptyStackLLNode(stackLNode))
        return false;
    x=stackLNode->next->data;
    //删除stackLNode后的一个节点
    StackLNode *temp=stackLNode->next;
    stackLNode->next=stackLNode->next->next;
    free(temp);

    //出栈成功,栈元素数据减少
    stackLNode->data--;
    return true;
}
bool peekStackLLNode(StackLNode *stackLNode,int &x){
    /*
     * 访问栈顶数据
     */
    if(isEmptyStackLLNode(stackLNode))
        return false;

    x= stackLNode->next->data;
    return true;
}

void testSqStack(){
    /*
     * 测试顺序栈
     */
    //创建栈并入栈数据
    int a[7]={1,2,3,4,5,6,7};
    StackLNode *stackLNode=(StackLNode *) malloc(sizeof (StackLNode));
    initStackLNode(stackLNode);

    for(int i=0;i<7;i++)
        if(!pushStackLLNode(stackLNode,a[i]))
            printf("失败->插入数据:%d\n",a[i]);

    int x;
    if(peekStackLLNode(stackLNode,x))
        printf("栈顶元素:%d\n",x);

    while(!isEmptyStackLLNode(stackLNode)) {
        if (popStackLLNode(stackLNode, x))
            printf("-----出栈元素:%d\n", x);
        else
            printf("-----出栈元素失败");
    }

    if(peekStackLLNode(stackLNode,x))
        printf("再次获取 栈顶元素:%d\n",x);
    else
        printf("再次获取 栈顶元素失败\n");

    if (popStackLLNode(stackLNode, x))
        printf("再次获取 出栈元素:%d\n", x);
    else
        printf("再次获取 出栈元素失败\n");

    //回收栈
    free(stackLNode);
}
