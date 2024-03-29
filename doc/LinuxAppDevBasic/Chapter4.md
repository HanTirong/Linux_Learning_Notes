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
1. [相关代码1](../../source/LinuxAppDevBasic/source/06_fileio/03_write/write.c)
2. [相关代码2](../../source/LinuxAppDevBasic/source/06_fileio/03_write/write_in_pos.c)
3. 注意： `write()` 如果移动到某个位置开始写，则会覆盖该位置以后的

## [4-5] 使用read函数读文件
1. [相关代码](../../source/LinuxAppDevBasic/source/06_fileio/04_read/read.c)
2. 注意： `read()` 每读一次，pos就会移动到当前位置

## [4-6] 综合实验_处理表格
1. [相关代码](../../source/LinuxAppDevBasic/source/06_fileio/05_process_excel/process_excel.c)
2. `hexdump -C score.csv` :查看score.csv文件内容的16进制形式
3. 一个文件的每一行结尾是回车换行
4. `sscanf()` 从字符串里面按照指定格式提取输入 
5. `sprintf()` 往字符串里面按照格式填写字符串
6. utf-8格式的文件内容开头是0xef,0xbb,0xbf 三个字节代表编码格式


## [4-7] 文件IO系统调用内部机制
1. app和Linux系统之间有一个界限，app通过调用系统接口去访问内核
- app调用系统接口
- 系统接口函数内部会触发异常: 在寄存器里记录异常原因，用汇编指令`swi/SVC`去触发异常
- CPU分辨异常原因并处理异常
2. 运行程序得到的文件句柄如何与具体文件挂钩? 
- 每个进程有自己的文件句柄空间
- 每个进程有自己的任务结构体 `task_struct` -> 成员`files` -> 成员`fdt` -> 数组`fd` -> 数组的每一个项指向 `file`,这个结构体是用来描述文件的-> 当需要读写该文件时 `file` 内部有 `f_pos` 

## [4-9] dup函数的使用
1. 使用`open()`打开同一个文件，则该文件会分别对应多个句柄，每个句柄独立互不影响
2. `dup()` 将新的句柄指向之前的文件
3. `dup2()` 会将现有文件的句柄重定向到新的句柄


