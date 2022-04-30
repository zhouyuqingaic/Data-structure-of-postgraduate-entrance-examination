#include<stdio.h>
#include <malloc.h>

const int MaxSize=100;

typedef struct{
    int data[MaxSize+1][3]; //矩阵的数据空间
}SparseMatrix;

void initSparseMatrix(SparseMatrix *&spareMatrix){
    /*
     * 初始化矩阵
     */
    if(spareMatrix!=NULL)
        free(spareMatrix);
    spareMatrix=NULL;
}

bool createMatrix(SparseMatrix *&spareMatrix,int a[][MaxSize],int rowOfA,int columnOfA){
    /*
     * 通过二维数组创建矩阵
     */
    //特殊元素值
    int specialVal=0;
    //对传入数组的尺寸检查
    if(0<rowOfA && rowOfA<=MaxSize && 0<columnOfA && columnOfA <= MaxSize) {
        //创建矩阵
        spareMatrix=(SparseMatrix *)malloc(sizeof(SparseMatrix));
        int k=1;
        //填充稀疏矩阵
        for(int i=0;i<rowOfA;i++)
            for(int j=0;j<columnOfA;j++)
                //稀疏矩阵中特殊元素的值为0,将非特殊字符填充入数组
                if(a[i][j]!=specialVal) {
                    spareMatrix->data[k][0] = a[i][j];
                    spareMatrix->data[k][1]=i;
                    spareMatrix->data[k][2]=j;
                    k++;
                }
        //设置稀疏矩阵属性
        spareMatrix->data[0][0]=k;
        spareMatrix->data[0][1]=rowOfA;
        spareMatrix->data[0][2]=columnOfA;
        return true;
    }else
        return false;
}

void showSparseMatrix(SparseMatrix *sparseMatrix){
    /*
     * 展示矩阵
     */
    int k=1;
    //特殊元素值
    int specialVal=0;
    for(int i=0;i<sparseMatrix->data[0][1];i++) {
        for (int j = 0; j < sparseMatrix->data[0][2]; j++) {
            //当前元素为非特殊元素，直接打印
            if (i == sparseMatrix->data[k][1] && j == sparseMatrix->data[k][2]) {
                printf("%8d", sparseMatrix->data[k][0]);
                k++;
            } else {
                //当前元素为特殊元素，打印特殊元素
                printf("%8d",specialVal);
            }
        }
        printf("\n");
    }
}


void testSparseMatrix (){
    int array[][MaxSize]={
    {0,11,12,13},
    {20,0,22,23},
    {30,31,0,33}
    };
    int otherArray[][MaxSize]={
    {100,0,0},
    {200,201,0},
    {300,301,302},
    {400,401,402}
    };

    SparseMatrix *sparseMatrix01=NULL;
    SparseMatrix *sparseMatrix02=NULL;
    initSparseMatrix(sparseMatrix01);
    initSparseMatrix(sparseMatrix02);


    if(
        !createMatrix(sparseMatrix01,array,3,4) ||
        !createMatrix(sparseMatrix02,otherArray,4,3)
    ){
        printf("创建矩阵失败!\n");
        return;
    }
    printf("sparseMatrix01矩阵,元素个数:%d,行数:%d,列数:%d\n",
           sparseMatrix01->data[0][0],sparseMatrix01->data[0][1],sparseMatrix01->data[0][2]);
    showSparseMatrix(sparseMatrix01);
    printf("sparseMatrix02矩阵,元素个数:%d,行数:%d,列数:%d\n",
           sparseMatrix02->data[0][0],sparseMatrix02->data[0][1],sparseMatrix02->data[0][2]);
    showSparseMatrix(sparseMatrix02);

    //释放所有矩阵
    initSparseMatrix(sparseMatrix01);
    initSparseMatrix(sparseMatrix02);

}

int main(){
    testSparseMatrix();

    return 0;
}
