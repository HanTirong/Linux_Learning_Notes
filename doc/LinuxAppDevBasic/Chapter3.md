### 第3章 Makefile的使用

#### [3-1] Makefile要达到的效果



#### [3-2] Makefile的引入及规则
1. 规则：
    目标文件：依赖文件  
    [Tab] 命令
当目标文件不存在 或 某个依赖文件比目标文件新，则执行“命令”  


#### [3-3] Makefile的语法
1. 通配符 `%`
- [代码](../../source/LinuxAppDevBasic/source/04_2018_Makefile/002_syntax/001_patten/Makefile)
    - `$@` 表示目标文件 
    - `$<` 表示第一个依赖文件
    - `$^` 表示所有的依赖文件

2. 假想目标 `.PHONY`
    - 使用`make`指令, `make [目标]`，若没有目标，则默认第1个目标

3. 变量
- 即时变量
    - `A := xxx   # A的值即刻确定，在定义时就确定`
    - `$(A)` 使用变量 
    - `@echo ` 不打印出命令
- 延时变量
    `B = xxx   # B的值在使用到时才确定`

- export

4. 赋值方法
- `:=`  #即时变量  
- `=`   # 延时变量
- `?=`  # 延时变量，如果是第一次定义才起效，如果在前面该变量已定义则忽略这句
- `+=`  # 附加，是即时变量还是延时变量取决于前面的定义 




#### [3-4] Makefile函数
- [代码](../../source/LinuxAppDevBasic/source/04_2018_Makefile/003_example/Makefile)
- `$(foreach var,list,text)` 对于list中的每一个元素var执行一下text语句

- `$(filter pattern...,text)` 在text中取出符合pattern格式的值
- `$(filter-out pattern...,text)` 在text中取出不符合pattern格式的值

- `$(wildcard pattern)` pattern定义了文件名的格式，wildcard取出其中存在的文件

- `$(patsubst pattern,replacement, $(var))` 从列表中取出每一个值，如果符合pattern，则替换为replacement

#### [3-5] Makefile实例
1. 改进：支持头文件依赖
    - `gcc -M a.c`  //打印出a.c的依赖文件
    - `gcc -M -MF a.d a.c`  //打印a.c的依赖文件并存到a.d中
    - `gcc -c -o c.o c.c -MD -MF c.d` // 编译c.o，把依赖写入文件c.d
[代码](../../source/LinuxAppDevBasic/source/04_2018_Makefile/003_example/Makefile)

2. 添加CFLAGS
    - 建议用gcc编译的时候添加  `-Werror`

#### [3-6] 通用Makefile的使用
[点击此处查看](../../source/LinuxAppDevBasic/source/05_general_Makefile/Makefile_and_readme/)


#### [3-7] 通用Makefile的解析



