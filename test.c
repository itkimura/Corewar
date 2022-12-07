#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd = open("test.s", O_RDONLY);
    unsigned char bytes[33];

    read(fd, bytes, 32);
    bytes[32] = '\0';
    for (int i = 0; i < 32; i++)
      write(1, &bytes[i], 1);
    return (0);
}
