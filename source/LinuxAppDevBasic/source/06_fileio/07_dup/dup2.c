#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/*
 * ./dup2 1.txt
 * argc    = 2
 * argv[0] = "./dup2"
 * argv[1] = "1.txt"
 */

int main(int argc, char **argv)
{
    int fd;
    if(argc != 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return -1;
    }
    fd = open(argv[1],O_RDWR | O_CREAT | O_TRUNC, 0666); // 可读可写 | 不存在则创建 | 若存在则截断
    if(fd < 0)
    {
        printf("cant open file %s\n", argv[1]);
        printf("errno = %d\n", errno);
        printf("err: %s\n", strerror(errno));
        perror("open");
    }
    else
    {
        printf("fd = %d\n", fd);
    }

    dup2(fd, 1); /*重定向*/
    printf("<:::::::[]=o\n"); /* 打印到fd=1的文件 */
    return 0;
}

