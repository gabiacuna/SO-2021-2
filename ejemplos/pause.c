#include <stdio.h>
#include <unistd.h>

int main(void)
{
        int ret = 0;
        ret = pause();
        printf("Pause returned with %d\n", ret);
        return 0;
}