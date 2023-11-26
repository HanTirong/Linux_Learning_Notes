### 第2章 GCC

#### [2-1] GCC编译过程
1. GCC编译流程

``` txt
早期程序：
            纸带打孔        ->  英文助记符      -> 高级语言       
                |                  |                |
                |                  |                |
App<---链接---机器码(.o)<--汇编--汇编码(.S)<---编译----|(.i)<---预处理--- (.c .h)
                |                   |
                |------反汇编------->|

```
2. [代码](../../source/LinuxAppDevBasic/source/02_options/01_hello/hello.c)

3. 输入 `gcc -o hello hello.c -v` 查看详细[编译过程](../../source/LinuxAppDevBasic/source/02_options/01_hello/编译过程.txt)
- `cc1 hello.c  -o /tmp/ccUZibu5.s` 这一步包括了预处理和编译过程
- `as -o /tmp/cc6EeVoL.o /tmp/ccUZibu5.s` 这一步包括了汇编
- `collect2` 将众多.o .so .a文件链接成为一个可执行文件

4. 预处理命令 `gcc -E -o hello.i hello.c`
5. 编译命令 `gcc -S -o hello.s hello.i`
6. 汇编命令 `gcc -c -o hello.o hello.s`
7. 链接命令 `gcc -o hello hello.o`
8. c程序语法错误，在编译过程过发现


#### [2-2] GCC常用选项
1. [代码](../../source/LinuxAppDevBasic/source/02_options/02_multi_files/main.c)
2. 输入 `gcc -o test main.c sub.c` 会将每一个c文件都编译，然后最后进行链接，因此如果多个文件中只有一个文件被修改了，可考虑对被修改的文件单独去编译，然后再和其他文件一起链接
3. `#include "dir"`是在当前目录下查找，`#include <dir>`是从系统工具链指定的目录去查找
4. -I指定头文件目录 `gcc -c -o main.o main.c -v -I ./`
5. 制作、使用静态库
    - `gcc -c -o sub.o sub.c`
    - `ar crs libsub.a sub.o sub2.o(等等多个.o文件)`
    - `gcc -o test main.o libsub.a`
    - 不需要把静态库 libsub.a 放到板子上

6. 制作、使用动态库
    - `gcc -c -o sub.o sub.c`
    - `gcc -shared -o libsub.so sub.o sub2.o(等等多个.o文件)`
    - `gcc -o test main.o -lsub -L /libsub.so/所在目录/`
    - 执行 `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/a` ,目录a表示libsub.so所在的目录，然后才能运行

7. 使用`file test`指令查看是可以在什么平台的运行的

8. 总结
- 头文件 <>
    - 指定的目录查找
    - -I dir
- 库 -lxxx
    - 指定的lib目录
    - -L dir
- 运行 .so
    - 系统工具链指定的目录，如 /lib，/user/lib
    - 自己制定 `LD_LIBRARY_PATH`

