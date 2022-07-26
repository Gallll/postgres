#include<stdio.h>
enum week  
{
    mon = 1,
    tus,
    thd,
    thr,
    fri,
    sat,
    sun,
};

int main()
{
    
    enum week  today = thr;
    enum week  tommorow = fri;
    printf("%d\n", today);
    
}
