
#include <stdio.h>
#include <stdlib.h>

/****************************************
 * 函数指针结构体
 ***************************************/
typedef struct _OP {
    float (*p_add)(float, float); 
    float (*p_sub)(float, float); 
    float (*p_mul)(float, float); 
    float (*p_div)(float, float); 
} OP; 

/****************************************
 * 加减乘除函数
 ***************************************/
float ADD(float a, float b) 
{
    return a + b;
}

float SUB(float a, float b) 
{
    return a - b;
}

float MUL(float a, float b) 
{
    return a * b;
}

float DIV(float a, float b) 
{
    return a / b;
}

/****************************************
 * 初始化函数指针
 ***************************************/
void init_op(OP *op)
{
    op->p_add = ADD;
    op->p_sub = SUB;
    op->p_mul = &MUL;
    op->p_div = &DIV;
}

/****************************************
 * 库函数
 ***************************************/
float add_sub_mul_div(float a, float b, float (*op_func)(float, float))
{
    return (*op_func)(a, b);
}

int main(int argc, char *argv[]) 
{
    OP *op = (OP *)malloc(sizeof(OP)); 
    init_op(op);
    
    /* 直接使用函数指针调用函数 */ 
    printf("ADD = %f, SUB = %f, MUL = %f, DIV = %f\n", 
             op->p_add(1.3, 2.2),         
            (op->p_sub)(1.3, 2.2),  //函数名实际上就是地址,C语言允许(*myFun)(10)和myFun(10)这两种形式的函数调用
            (*op->p_mul)(1.3, 2.2), //->的优先级是最高的，所以(*op->p_mul)实际上是(*(op->p_mul)),这种写法最外面的括号一定需要
            (*op->p_div)(1.3, 2.2));
     
    /* 调用回调函数 */ 
    printf("ADD = %f, SUB = %f, MUL = %f, DIV = %f\n", 
            add_sub_mul_div(1.3, 2.2, ADD), 	//C语言允许(*myFun)(10)和myFun(10)这两种形式的函数调用
            (*add_sub_mul_div)(1.3, 2.2, SUB),  //这种写法最外面的括号一定需要
            add_sub_mul_div(1.3, 2.2, MUL), 
            add_sub_mul_div(1.3, 2.2, DIV));

    return 0; 
}
