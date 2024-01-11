#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/*
 * ./write 1.txt str1 str2
 * argc    = 2
 * argv[0] = "./open"
 * argv[1] = "1.txt"
 */

int main(int argc, char **argv)
{
    int fd;
    int i;
    int len;

    if(argc <= 3)
    {
        printf("Usage: %s <file> <string1> <string2> ...\n", argv[0]);
        return -1;
    }
    fd = open(argv[1],O_RDWR | O_CREAT , 0644); // 可读可写 | 不存在则创建 
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
    
    printf("lseek to offset 3 from file head\n");
    lseek(fd, 3, SEEK_SET); //从当前位置移动3个字节开始写，会覆盖原来的

    write(fd, "114514", 6);
    close(fd);

    return 0;
}

