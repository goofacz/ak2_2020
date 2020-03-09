#include <unistd.h>

char buffer[] = "Countdown: 0!\n";
int buffer_len = 15;

int main(void)
{
    int i = 10;

    while(i != 0)
    {
        write(1, buffer, buffer_len);
        buffer[11]++;
        i--;
    }

    _exit(0);
}
