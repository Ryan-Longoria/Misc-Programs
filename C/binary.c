#include <stdio.h>

void show_bytes(char* start, int len) 
{
    int i;
    for(i = 0; i < len; i++)
        printf("%p\t0x%.2x\n", start + i, *(start + i));
    printf("\n");
}

void show_int(int x)
{
    show_bytes( (char *) &x, sizeof(int));
}

int main()
{
    int x = 12345;
    printf("int x = %d\n", x);
    show_int(x);

    return 0;
}
