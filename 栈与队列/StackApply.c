#include<stdio.h>
#include<string.h>
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

bool match(char *exp) {
    /*
     * 判断表达式中的括号匹配
     */
    //创建工 具栈
    SqStack *sqStack = (SqStack *) malloc(sizeof(SqStack));
    initSqStack(sqStack);
    //处理表达式中的每个字符
    int temp;
    for (int i = 0; i < strlen(exp); i++) {
        //遇到'('入栈
        if (exp[i] == '(')
            pushSqStack(sqStack, exp[i]);
        //遇到')'出栈
        if (exp[i] == ')') {
            //如果出栈失败，则')'的数目比'('的数目多
            if(!popSqStack(sqStack, temp)){
                //回收工具栈
                free(sqStack);
                return false;
            }
        }
    }

    //栈为空则符合括号标准
    if (isEmptySqStack(sqStack)){
        //回收工具栈
        free(sqStack);
        return true;
    }else{ //栈不空'('的数目比')'多
        //回收工具栈
        free(sqStack);
        return false;
    }
}


int calc(int a,char op,int b){
    /*
     * 四则运算函数
     */
    int result=-99999;
    switch (op) {
        case '+':
            result=a+b;
            break;
        case '-':
            result=a-b;
            break;
        case '*':
            result=a*b;
            break;
        case '/':
            if(b==0)
                printf("除数不能为0!\n");
            else
                result = a / b;
            break;
        default:
            printf("输入运算操作符号有误!\n");
    }
    return result;
}
int evalutatesSuffixExpression(char *exp){
    /*
     * 后缀表达式求值
     */
    //创建工具栈
    SqStack *sqStack = (SqStack *) malloc(sizeof(SqStack));
    initSqStack(sqStack);

    //处理表达式中每个字符
    int arg1,arg2,result;
    for(int i=0;i<strlen(exp);i++){
        //将遇到的数组入栈
        if('+'!=exp[i] && '-'!=exp[i] && '*'!=exp[i] && '/'!=exp[i])
            pushSqStack(sqStack,exp[i]-'0');
        else{
            //遇到运算符进行计算
            char ope=exp[i];
            //出栈两个操作数
            popSqStack(sqStack,arg1);
            popSqStack(sqStack,arg2);
            //运算并将结果入栈
            pushSqStack(sqStack,calc(arg1,ope,arg2));
        }
    }
    //栈顶元素为运算结果
    popSqStack(sqStack,result);
    //释放栈并返回值
    free(sqStack);
    return result;
}


int testMatch(){
    /*
     * 测试match函数
     */
    char *exp1="(a+b)*c+d)";
    char *exp2="((a+b)*c+d";
    char *exp3="((a+b)*c+d)";
    char *exp4="fdsafa";
    char *exp5="(";
    char *exp6=")";


    char *exps[]={exp1,exp2,exp3,exp4,exp5,exp6};
    for(int i=0;i<sizeof(exps)/sizeof(char *);i++)
        if(match(exps[i]))
            printf("%s  匹配成功!\n",exps[i]);
        else
            printf("%s  匹配失败!\n",exps[i]);


    return 0;
}

int testEvalutatesSuffixExpression(){

    printf("312+* = %d\n",evalutatesSuffixExpression("312+*"));
    printf("4312+*- = %d\n",evalutatesSuffixExpression("4312+*-"));

    return 0;
}

int main(){
    testMatch();
    printf("-------------------------------------------\n");
    testEvalutatesSuffixExpression();
    return 0;
}
