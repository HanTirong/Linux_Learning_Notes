### 第一章 HelloWorld
#### [1-1] 交叉编译Hello程序
-  理论
下面是hello.c文件，argc是argument count， 
argv是argument valus

```  CC
#include<stdio.h>


int main(int agrc, char **agrv){
    if(argc >= 2)
        printf("Hello %s!\n", argv[1]);
    else
        printf("hello Linux\n");
    return 0;
}
```

如果在cmd中运行编译好的程序：`./hello ` ，此时argc是1，argv[0] = "main"  
如果在cmd中运行编译好的程序：`./hello Ubuntu` ，此时argc是2，argv[0] = "main", argv[1] = "Ubuntu"  

- 实验：

    1. 进入`book@100ask:~/01_all_series_quickstart/04_嵌入式Linux应用开发基础知识/source/01_hello$` 
    2. 输入`gcc -o hello hello.c` 编译得到hello
    3. 输入 `./hello Ubuntu`，输出 Hello Linux
    4. 输入 `file hello`，查看文件类型是 x86-64,无法在ARM板上运行
    5. 使用交叉编译工具，输入 `arm-buildroot-linux-gnueabihf-gcc -o hello hello.c`,并再次查看编译结果文件类型为ARM
    6. 使用`cp hello /home/book/nfs_rootfs/`命令拷贝到开发板中，可以正常运行

- mount 命令
    1. 格式： mouunt, 某些参数，设备， 板子的目录  `mount -t nfs -o nolock,vers=3 192.168.5.11:/home/book/nfs_rootfs /mnt`

#### [1-2] Hello程序的引申

1. .h 和 .c 文件的差别？  
- 在头文件中声明一个函数，用来说明函数需要什么参数，编译器会通过声明来经检查函数用的对不对  
- 在c文件中，实现函数
2. .h文件在哪？   
    系统目录中 （工具链目录）或者 指定目录（ -I dir）
3. printf在哪？  
    在系统目录的库里面 或 自己指定


