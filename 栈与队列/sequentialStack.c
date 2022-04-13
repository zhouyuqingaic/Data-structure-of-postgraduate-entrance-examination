#include<stdio.h>
#include <malloc.h>

const int maxSize=5;
typedef struct{
    int data[maxSize]; //顺序栈存储空间
    int top; //栈顶指针
}SqStack;

void initSqStack(SqStack *sqStack){
    /*
     * 初始化顺序栈
     */
    sqStack->top=-1;
}
bool isEmptySqStack(SqStack *sqStack){
    /*
     * 判断栈是否为空
     */
    return sqStack->top==-1;
}
bool pushSqStack(SqStack *sqStack,int x){
    /*
     * 数据x进入顺序栈
     */
    if(sqStack->top>=maxSize-1)
        return false;
    sqStack->data[++sqStack->top]=x;
    return true;
}
bool popSqStack(SqStack *sqStack,int &x){
    /*
     * 栈定元素出栈
     */
    if(isEmptySqStack(sqStack))
        return false;
    x=sqStack->data[sqStack->top--];
    return true;
}
bool peekSqStack(SqStack *sqStack,int &x){
    /*
     * 访问栈顶数据
     */
    if(isEmptySqStack(sqStack))
        return false;
    x=sqStack->data[sqStack->top];
    return true;
}

void testSqStack(){
    /*
     * 测试顺序栈
     */
    //创建栈并入栈数据
    int a[7]={1,2,3,4,5,6,7};
    SqStack *sqStack=(SqStack *) malloc(sizeof (SqStack));
    initSqStack(sqStack);
    for(int i=0;i<7;i++)
        if(!pushSqStack(sqStack,a[i]))
            printf("失败->插入数据:%d\n",a[i]);

    int x;
    if(peekSqStack(sqStack,x))
        printf("栈顶元素:%d\n",x);

    while(!isEmptySqStack(sqStack)) {
        if (popSqStack(sqStack, x))
            printf("-----出栈元素:%d\n", x);
        else
            printf("-----出栈元素失败");
    }

    if(peekSqStack(sqStack,x))
        printf("再次获取 栈顶元素:%d\n",x);
    else
        printf("再次获取 栈顶元素失败\n");

    if (popSqStack(sqStack, x))
        printf("再次获取 出栈元素:%d\n", x);
    else
        printf("再次获取 出栈元素失败\n");

    //回收栈
    free(sqStack);
};
