#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/* 返回值：n表示读到了一行数据的个数(n>=0)
 *         -1表示读到文件尾部或出错
 */
static int read_line(int fd, unsigned char *buf)
{
    unsigned char c;
    int len;
    int i = 0;
    int err = 0;
    /* 循环读入一个字符*/
    while(1)
    {
        len = read(fd,&c,1); // 每读一次，会记录一次当前位置
        if(len <= 0)
        {
            err = -1;
            break;
        }   
        else
        {
            if(c != '\n' && c != '\r')
            {
                buf[i++] = c;
            }
            else
            {
                /*读到回车换行*/
                err = 0;
                break;
            }
        }
        
    }
    buf[i] = '\0';
    if(err && i == 0)
    {
        /*读取文件尾部并且一个数据没有读到*/
        return -1;
    }
    else
    {
        return i;
    }
}


static int process_data(unsigned char *data_buf, unsigned char *result_buf)
{
    /* 示例1: data_buf = ",语文,数学,英语,总分,评价" 
     *        result_buf = ",语文,数学,英语,总分,评价" 
     * 示例2: data_buf = "张三,90,91,92,," 
     *        result_buf = "张三,90,91,92,273,A+" 
     */
    char name[100];
    int scores[3];
    int sum;
    char *levels[] = {"优","良","中","差"};
    int level ;
    if(data_buf[0] == 0xef)  /*对于UTF-8编码的文件，前三个字符是0xef, 0xbb, 0xbf*/
    {
        strcpy(result_buf, data_buf);
    }
    else
    {
        sscanf(data_buf, "%[^,],%d,%d,%d,",name, &scores[0], &scores[1], &scores[2]);
        sum = scores[0] + scores[1] + scores[2];
        if(sum >= 270)
        {
            level = 0;
        }
        else if(sum < 270 && sum >= 240)
        {
            level = 1;
        }
        else if(sum < 240 && sum >= 180)
        {
            level = 2;
        }
        else
        {
            level = 3;
        }
        sprintf(result_buf, "%s,%d,%d,%d,%d,%s",name, scores[0], scores[1], scores[2], sum, levels[level]);

        //printf("rets: %s\r\n", result_buf);
    }
}

/*
 * ./process_excel data.csv result.csv 
 * argc    = 3
 * argv[0] = "./process_excel"
 * argv[1] = "data.csv"
 * argv[1] = "result.csv"
 */

int main(int argc, char **argv)
{
    int fd_data, fd_result;
    int i;
    int len;
    unsigned char data_buf[1000];
    unsigned char result_buf[1000];

    if(argc != 3)
    {
        printf("Usage: %s <file> <csv file 1> <csv file 2> ...\n", argv[0]);
        return -1;
    }
    fd_data = open(argv[1],O_RDWR, 0644); 
    if(fd_data < 0)
    {
        printf("cant open file %s\n", argv[1]);
        perror("open");
        return -1;
    }
    else
    {
        printf("fd_data = %d\n", fd_data);
    }

    fd_result = open(argv[2],O_RDWR | O_CREAT | O_TRUNC, 0644); // 可读可写 | 不存在则创建 | 若存在则截断
    if(fd_result < 0)
    {
        printf("cant create file %s\n", argv[2]);
        perror("create");
        return -1;
    }
    else
    {
        printf("fd_result = %d\n", fd_result);
    }

    while(1)
    {
        /*从数据文件读取一行*/
        len = read_line(fd_data, data_buf);
        if(len == -1)
        {
            break; 
        }
        //printf("line: %s\r\n", data_buf);
        if(len != 0)
        {
            /*处理数据*/
            process_data(data_buf, result_buf);
            /*写入结果文件*/
            write(fd_result, result_buf,strlen(result_buf)); //写入的数据不包含回车换行
            write(fd_result, "\r\n", 2);
        }
    }

    close(fd_data);
    close(fd_result);
    return 0;
}

