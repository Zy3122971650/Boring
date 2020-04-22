#include <iostream>

int main(){
    int a,flag,result;
    while (1){
        printf("输入一个整数，我来计算它的阶乘\n");
        flag = scanf("%d",&a);
        if (flag == 1 && a <= a ){
            break;
        }
    }
    result = factorial(a);
    printf("%d",result);
};

int factorial(int num){
    int total;
    if (num == 0){
        return 1;
    }
    else if (num == 1){
        return 1;
    }
    else
    {
        total = num*factorial(num-1);
        return total;
    }
}