#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
    int *array,i,n;
    scanf("%d",&n);
    array=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;++i)
    {
        scanf("%d",array+i);
    }
    printf("%d\n",array[1]);
    free(array);
    return 0;
}