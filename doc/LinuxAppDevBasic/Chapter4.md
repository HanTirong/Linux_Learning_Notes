# 第4章 文件I/O

## [4-1] 文件IO分类
1. Linux操作文件有两套函数：标准IO和系统调用IO
2. 标准IO是在系统调用IO基础上封装的一套函数，两者区别在于标准IO引入一个用户buffer

## [4-2] 使用open函数打开文件
1. `man man` 使用man命令查看man 手册
2. `man 2 open` 查看第二页的open函数
3. [相关代码](../../source/LinuxAppDevBasic/source/06_fileio/01_open/open.c)
4. `./open ./open &` 在后台运行编译后的open，执行后会显示进程号8791
5. `cd /proc/8791/fd | ls -l`,显示如下
```
total 0
lrwx------ 1 book book 64 Jan  9 09:45 0 -> /dev/pts/0
lrwx------ 1 book book 64 Jan  9 09:45 1 -> /dev/pts/0
lrwx------ 1 book book 64 Jan  9 09:45 2 -> /dev/pts/0
lrwx------ 1 book book 64 Jan  9 09:45 3 -> /home/book/01_all_series_quickstart/04_嵌入式Linux应用开发基础知识/source/06_fileio/01_open/open.c
```
显示文件句柄，一共四个表示打开了四个文件，0代表标准输入scanf, 1代表标准输出printf, 2代表错误信息
6. `kill -9 8791`杀掉这个线程

## [4-3] 使用open函数创建文件
1. [相关代码](../../source/LinuxAppDevBasic/source/06_fileio/02_create/create.c)
2. vim 中 搜索某个词则冒号加/加要搜的词如:`/mode`
3. 对一个文件有三种属组owner, group, other，每一组都有rwx权限,每一个权限对应0表示无此权限，1表示有此权限，因此可以用八进制可以表示每一个组的权限，例如: 0666 表示0-110-110-110
4. 对于已经存在的文件无法修改权限，但是对于新建的一个文件可以修改其权限
5. 输入`umask` 返回 0002 表示 000,000,010 创建的文件系统禁止此权限
6. 对于root用户，返回 0022 表示 000, 010, 010

## [4-4] 使用write函数写文件



## [4-5] 使用read函数读文件



## [4-6] 综合实验_处理表格



## [4-7] 文件IO系统调用内部机制



## [4-9] dup函数的使用



