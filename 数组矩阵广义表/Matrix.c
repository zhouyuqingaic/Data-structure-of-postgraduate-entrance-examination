#include<stdio.h>
#include <malloc.h>

const int MaxSize=100;

typedef struct{
    int data[MaxSize][MaxSize]; //矩阵的数据空间
    int row; //矩阵的行
    int column; //矩阵的列
}Matrix;

void initMatrix(Matrix *&matrix){
    /*
     * 初始化矩阵
     */
    if(matrix!=NULL)
        free(matrix);
    matrix=NULL;
}

bool createMatrix(Matrix *&matrix,int a[][MaxSize],int rowOfA,int columnOfA){
    /*
     * 通过二维数组创建矩阵
     */
    //对传入数组的尺寸检查
    if(0<rowOfA && rowOfA<=MaxSize && 0<columnOfA && columnOfA <= MaxSize) {
        //创建矩阵
        matrix=(Matrix *)malloc(sizeof(Matrix));
        matrix->row=rowOfA;
        matrix->column=columnOfA;
        for(int i=0;i<rowOfA;i++)
            for(int j=0;j<columnOfA;j++)
                matrix->data[i][j]=a[i][j];
        return true;
    }else
        return false;
}
void showMatrix(Matrix *matrix){
    /*
     * 展示矩阵
     */
    for(int i=0;i<matrix->row;i++){
        for(int j=0;j<matrix->column;j++)
            printf("%8d ",matrix->data[i][j]);
        printf("\n");
    }
}


bool transitionMatrix(Matrix *matrix,Matrix *&resultMatrix){
    /*
     * 对matrix进行转秩
     */
    if(matrix==NULL)
        return false;

    //创建转秩矩阵
    resultMatrix=(Matrix *)malloc(sizeof(Matrix));
    resultMatrix->row=matrix->column;
    resultMatrix->column=matrix->row;
    //填充数据
    for(int i=0;i<matrix->row;i++){
        for(int j=0;j<matrix->column;j++)
            resultMatrix->data[j][i]=matrix->data[i][j];
    }

    return true;
}

bool multiplicationMatrix(Matrix *matrix,Matrix *otherMatrix,Matrix *&resultMatrix){
    /*
     * 对matrix进行相乘的操作
     */
    //对传入矩阵进行检查
    if(matrix==NULL || otherMatrix==NULL || matrix->row!=otherMatrix->column || matrix->column!=otherMatrix->row){
        return false;
    }
    //创建相乘结果矩阵
    resultMatrix=(Matrix *)malloc(sizeof(Matrix));
    resultMatrix->row=matrix->row;
    resultMatrix->column=otherMatrix->column;

    //matrix中的每一行元素乘other中每一列元素
    for(int i=0;i<matrix->row;i++){
        for(int j=0;j<otherMatrix->column;j++){
            resultMatrix->data[i][j]=0;
            for(int tempIndex=0;tempIndex<matrix->column;tempIndex++){
                resultMatrix->data[i][j]+=(
                        matrix->data[i][tempIndex]*otherMatrix->data[tempIndex][j]
                    );
            }
        }
    }

    return true;
}

bool additionMatrix(Matrix *matrix,Matrix *otherMatrix,Matrix *&resultMatrix){
    /*
     * matrix与otherMatrix相加
     */
    //对传入矩阵进行检查
    if(matrix->row!=otherMatrix->row || matrix->column!=otherMatrix->column)
        return false;
    //创建相加结果矩阵
    resultMatrix=(Matrix *)malloc(sizeof(Matrix));
    resultMatrix->row=matrix->row;
    resultMatrix->column=matrix->column;

    //matrix与otherMatrix中的每个元素相加
    for(int i=0;i<matrix->row;i++)
        for(int j=0;j<matrix->column;j++)
            resultMatrix->data[i][j]=matrix->data[i][j]+otherMatrix->data[i][j];

    return true;

}

void testMatrix (){
    int array[][MaxSize]={
    {10,11,12,13},
    {20,21,22,23},
    {30,31,32,33}
    };
    int otherArray[][MaxSize]={
    {100,101,102},
    {200,201,202},
    {300,301,302},
    {400,401,402}
    };

    Matrix *matrix=NULL;
    Matrix *otherMatrix=NULL;
    Matrix *otherMatrix01=NULL;
    Matrix *tempMatrix=NULL;
    initMatrix(matrix);
    initMatrix(otherMatrix);
    initMatrix(otherMatrix01);

    if(
        !createMatrix(matrix,array,3,4) ||
        !createMatrix(otherMatrix,otherArray,4,3) ||
        !createMatrix(otherMatrix01,otherArray,4,3)
    ){
        printf("创建矩阵失败!");
        return;
    }
    printf("matrix矩阵\n");
    showMatrix(matrix);
    printf("otherMatrix矩阵\n");
    showMatrix(otherMatrix);

    //矩阵乘法
    printf("对matrix矩阵与otherMatrix矩阵\n");
    initMatrix(tempMatrix);
    multiplicationMatrix(matrix,otherMatrix,tempMatrix);
    showMatrix(tempMatrix);

    //矩阵转秩
    printf("对matrix矩阵进行转秩\n");
    initMatrix(tempMatrix);
    transitionMatrix(matrix,tempMatrix);
    showMatrix(tempMatrix);

    //矩阵相加
    printf("对matrix矩阵进行相加\n");
    initMatrix(tempMatrix);
    additionMatrix(otherMatrix,otherMatrix01,tempMatrix);
    showMatrix(tempMatrix);

    //释放所有矩阵
    initMatrix(matrix);
    initMatrix(otherMatrix);
    initMatrix(otherMatrix01);
    initMatrix(tempMatrix);

}

int main(){
    testMatrix();
    return 0;
}

