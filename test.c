#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("test.s", O_RDONLY);
    unsigned char bytes[33];

    read(fd, bytes, 32);
    bytes[32] = '\0';
    printf("-- hexdump --\n");
    for (int i = 0; i < 32; i++)
      printf("[%d] = %X\n", i, bytes[i]);
    return (0);
}
