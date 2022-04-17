#include<stdio.h>
#include <malloc.h>

const int maxSize=1000;

typedef struct{
    char *data; //maxSize为串所允许的最大长度，则data指向的数组的最大长度为maxSize+1,这也是为了保证在最大存储长度的串时能保存最后一位置'\0'
    int length; //所存储的串的长度(该长度不包含'\0'这最后一位的长度)
}Str;   //串的定义

void initStr(Str *str){
    /*
     * 初始化线性队
     */
    str->length=0;   //所存储的串的长度清零
    if(str->data!=NULL)
        free(str->data);
    str->data=NULL;
}

bool isEmptyStr(Str *str){
    /*
     * 判断串是否空
     */
    return str->length==0;
}

bool isFullStr(Str *str){
    /*
     * 判断串是否满
     */
    return str->length==(maxSize+1);
}

int strLength(Str *str){
    /*
     * 获取串的长度
     */
    return str->length;
}

void strAssign(Str *str,char *otherStr){
    /*
     * 通过otherStr给str赋值
     */
    //将str初始化
    initStr(str);
    //统计otherStr字符串的长度
    int otherStrLength=0;
    while(otherStr[otherStrLength]!='\0')
        otherStrLength++;
    //如果otherStr的长度为0,即未空字符串
    if(otherStrLength==0){
        str->data=NULL;
        str->length=0;
    }else{  //如果otherStr的长度不为0,即不为空字符串
        //创建串的存储空间并存储串
        str->data=(char *)malloc(sizeof(char)*(otherStrLength+1));
        for(int i=0;i<otherStrLength;i++)
            str->data[i]=otherStr[i];
        str->data[otherStrLength]='\0';
        str->length=otherStrLength;
    }
}

char *strGet(Str *str){
    /*
     * 获取str转化成的字符串
     */
    //长度为0,返回一个空字符串
    if(str->length==0) {
        char *result=(char *) malloc(sizeof(char)*1);
        result[0]='\0';
        return result;
    }else {
        char *result = (char *) malloc(sizeof(char) * (str->length+1));
        for (int i = 0; i < str->length; i++)
            result[i] = str->data[i];
        result[str->length]='\0';
        return result;
    }
}

bool strEqual(Str *s1,Str *s2){
    /*
     * 判断两个字符串是相同
     */
    //比较字符串的长度
    if(s1->length!=s2->length)
        return false;
    else {
        //比较字符串中每个元素
        for (int i = 0; i < s1->length; i++)
            if (s1->data[i] != s2->data[i])
                return false;
        return true;
    }
}
void strEmpty(Str *str){
    /*
     * 清空str
     */
    initStr(str);
}
Str *strConcat(Str *str,Str *otherStr){
    /*
     * 链接两个子串
     */
    //合并结果字符串长度
    int  resultLength=str->length+otherStr->length+1;
    //创建合并结果串
    Str *result=(Str *)malloc(sizeof(Str));
    result->data=(char *)malloc(resultLength*sizeof (char));
    result->length=str->length+otherStr->length;
    //开始向结果串填充合并数据
    int posResult=0;
    for(int i=0;i<str->length;i++)
        result->data[posResult++]=str->data[i];
    for(int i=0;i<otherStr->length;i++)
        result->data[posResult++]=otherStr->data[i];
    //设置结束标志位置
    result->data[posResult]='\0';
    //返回结果
    return result;
}

Str *strSubstring(Str *str,int pos,int len){
    /*
     *获取从串str的pos位置开始,往后len个位置的元素的子串
     */
    //创建子串结果串

    //对输入pos与len合规检查
    if(pos<0 || len<0 || len>(str->length-pos))
        return NULL;
    //创建结果子串
    Str *result=(Str *) malloc(sizeof(Str));
    if(len==0){ //处理子串长度为1的特殊情况
        result->data=NULL;
        result->length=0;
    }else{
        result->data=(char *) malloc(sizeof(char)*(len+1)); //len+1,多出来的1为了存储'\0'结束标志位
        result->length=len; //子串长度
        int posStr=pos;
        for(int i=0;i<len;i++){
            result->data[i]=str->data[posStr++];
        }
        //设置结束标志位
        result->data[len+1]='\n';
    }
    //返回结果
    return result;
}

bool strMatch(Str *str,Str *subStr,int &posMatch){
    /*
     * 简单模式串匹配
     */
    //主串长度为0的特殊情况
    if(str->length==0){
        //子串长度的为0
        if(subStr->length==0) {
            posMatch=0;
            return true;
        }else{
            //子串长度不为0，匹配失败
            return false;
        }
    }else{ //子串与主串都不为0的情况
        int mainStrPos=0;
        int currentStr=0;
        int currentSubStr=0;
        //比较主串与子串中的元素
        while(currentStr < str->length && currentSubStr < subStr->length){
            if(str->data[currentStr] == subStr->data[currentSubStr]){
                currentStr++;
                currentSubStr++;
            }else{
                mainStrPos++;
                currentStr=mainStrPos;
                currentSubStr=0;
            }
        }
        //匹配成功
        if(currentSubStr == subStr->length){
            posMatch=mainStrPos;
            return true;
        }else{ //匹配失败
            return false;
        }
    }

}

int *getNext(Str *subStr){
    /*
     * 获取next数组
     */
    //创建next数组
    int *next=(int *)malloc(sizeof(int)*(subStr->length));
    int currentSubStr=0;
    int tempPos=-1;
    next[currentSubStr]=-1;
    while(currentSubStr<subStr->length){
        if(tempPos==-1 || subStr->data[currentSubStr]==subStr->data[tempPos]){
            currentSubStr++;
            tempPos++;
            next[currentSubStr]=tempPos;
        }else{
            tempPos=next[tempPos];
        }
    }
    return next;
}


bool strMatchKMPWithNext(Str *str,Str *subStr,int &posMatch){
    /*
     * 模式串匹配，利用next数组
     */
    //主串长度为0的特殊情况
    if(str->length==0){
        //子串长度的为0
        if(subStr->length==0) {
            posMatch=0;
            return true;
        }else{
            //子串长度不为0，匹配失败
            return false;
        }
    }else { //子串与主串都不为0的情况
        //获取next数组
        int *next= getNext(subStr);
        //利用next数组匹配
        int currentStr=0;
        int currentSubStr=0;
        while(currentStr<str->length && currentSubStr<subStr->length){
            if(currentSubStr==-1 || str->data[currentStr]==subStr->data[currentSubStr] ){
                currentStr++;
                currentSubStr++;
            }else{
                currentSubStr=next[currentSubStr];
            }
        }
        //匹配完毕清空next数组
        free(next);
        //匹配成功
        if(currentSubStr == subStr->length){
            posMatch=currentStr-subStr->length;
            return true;
        }else{ //匹配失败
            return false;
        }

    }
}

bool strMatchKMPWithNextVal(Str *str,Str *subStr,int &posMatch){
    /*
     * 模式串匹配，利用nextVal数组
     */
    //主串长度为0的特殊情况
    if(str->length==0){
        //子串长度的为0
        if(subStr->length==0) {
            posMatch=0;
            return true;
        }else{
            //子串长度不为0，匹配失败
            return false;
        }
    }else { //子串与主串都不为0的情况
    }
}

void testStr(){
    /*
     * 测试队列
     */
    //创建串
    Str *str01=(Str *)malloc(sizeof(Str));
    Str *str02=(Str *)malloc(sizeof(Str));
    Str *str03=(Str *)malloc(sizeof(Str));
    initStr(str01);
    initStr(str02);
    initStr(str03);
    //给字符串赋值
    strAssign(str01,"Android");
    strAssign(str02,"Android");
    strAssign(str03,"");

    //测试功能
    printf("strGet(str01):%s\n", strGet(str01));
    printf("strEqual(str01,str02):%d\n", strEqual(str01,str02));
    printf("strEqual(str01,str03):%d\n", strEqual(str01,str03));
    printf("strGet(str03):%s\n", strGet(str03));
    printf("%s:%d %s:%d %s:%d\n", strGet(str01), strLength(str01),strGet(str02), strLength(str02),strGet(str03),strLength(str03));

    strAssign(str01,"Python");
    printf("After strAssign(str01,\"Python\");\n");
    printf("strGet(str01):%s\n", strGet(str01));
    printf("strEqual(str01,str02):%d\n", strEqual(str01,str02));
    printf("strEqual(str01,str03):%d\n", strEqual(str01,str03));
    printf("%s:%d %s:%d %s:%d\n", strGet(str01), strLength(str01),strGet(str02), strLength(str02),strGet(str03),strLength(str03));

    strAssign(str01,"");
    printf("After strAssign(str01,\"\");\n");
    printf("strGet(str01):%s\n", strGet(str01));
    printf("strEqual(str01,str02):%d\n", strEqual(str01,str02));
    printf("strEqual(str01,str03):%d\n", strEqual(str01,str03));
    printf("%s:%d %s:%d %s:%d\n", strGet(str01), strLength(str01),strGet(str02), strLength(str02),strGet(str03),strLength(str03));

    strAssign(str01,"Jetson");
    strAssign(str02," Nano");

    printf("\n\n01-After concat.....\n");
    Str *temp= strConcat(str01,str02);
    printf("strGet(temp):%s  strLength(temp):%d\n", strGet(temp), strLength(temp));
    strEmpty(temp);
    free(temp);

    strAssign(str01,"DiYu");
    strAssign(str02,"");

    printf("\n\n02-After concat.....\n");
    temp= strConcat(str01,str02);
    printf("strGet(temp):%s  strLength(temp):%d\n", strGet(temp), strLength(temp));
    strEmpty(temp);
    free(temp);

    strAssign(str01,"123456");
    printf("\n\n02-After subString.....\n");
    temp= strSubstring(str01,0,3);
    printf("strGet(temp):%s  strLength(temp):%d\n", strGet(temp), strLength(temp));
    strEmpty(temp);
    free(temp);

    strAssign(str01,"123456");
    printf("\n\n04-After subString.....\n");
    temp= strSubstring(str01,5,1);
    if(temp!=NULL){
        printf("strGet(temp):%s  strLength(temp):%d\n", strGet(temp), strLength(temp));
        strEmpty(temp);
        free(temp);
    }else{
        printf("Failed...\n");
    }

    strAssign(str01,"123456");
    printf("\n\n04-After subString.....\n");
    temp= strSubstring(str01,6,1);
    if(temp!=NULL){
        printf("strGet(temp):%s  strLength(temp):%d\n", strGet(temp), strLength(temp));
        strEmpty(temp);
        free(temp);
    }else{
        printf("Failed...\n");
    }

    strAssign(str01,"123456");
    printf("\n\n05-After subString.....\n");
    temp= strSubstring(str01,2,0);
    if(temp!=NULL){
        printf("strGet(temp):%s  strLength(temp):%d\n", strGet(temp), strLength(temp));
        strEmpty(temp);
        free(temp);
    }else{
        printf("Failed...\n");
    }

    strAssign(str01,"1234567");
    strAssign(str02,"7");
    printf("\n\n06-After strMatch.....\n");
    int matchPos=0;
    if(strMatch(str01,str02,matchPos)){
        printf("%s 与 %s 匹配成功,位置为:%d \n", strGet(str01), strGet(str02),matchPos);
    }else{
        printf("%s 与 %s 匹配失败\n",strGet(str01),strGet(str02));
    }

    strAssign(str01,"1234567");
    strAssign(str02,"67");
    printf("\n\n06-After strMatch.....\n");
    matchPos=0;
    if(strMatchKMPWithNext(str01,str02,matchPos)){
        printf("%s 与 %s 匹配成功,位置为:%d \n", strGet(str01), strGet(str02),matchPos);
    }else{
        printf("%s 与 %s 匹配失败\n",strGet(str01),strGet(str02));
    }

    //清空并释放串
    strEmpty(str01);
    strEmpty(str02);
    strEmpty(str03);
    free(str01);
    free(str02);
    free(str03);
}
