#include <stdio.h>
int main()
{
    printf("****TIME****\n1.morning\n2.afternoon\n2.afternoon\n3.night\n");
    printf("Please enter your choice:\n");
    int choose;
    scanf("%d", &choose);
    switch (choose)
    {
    case 1:
        printf("Good morning\n");
        break;
    case 2:
        printf("Good afternoon\n");
        break;
    case 3:
        printf("Good night\n");
        break;
    default:
        printf("Selection wrong\n");
        break;
    }
}