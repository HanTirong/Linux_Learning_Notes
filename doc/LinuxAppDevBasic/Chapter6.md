# 第6章 文字显示及图象显示

## [6-1] 字符的编码方式
1. ASCII: 用一个字节的7位来表示，最高位一直为0
2. ANSI：对某个值在不同字符集下会显示不同值，即一个额值对应多个字符
3. Unicode: 每一个字符对应一个编码格式

## [6-2] ASCII字符的点阵显示
1. 常用的是8*16的点阵，表示x方向8个像素(1字节)，y方向16个像素(16行)
2. [代码](../../source/LinuxAppDevBasic/source/08_show_ascii/show_ascii.c)

## [6-3] 中文字符的点阵显示
1. 中文字符的编码一般不使用UTF-16来表示，因为该方式下ASCII字符也是用2字节来表示，而其中一个字节是0，C语言中0表示字符串的结束符，会引起误会。
- 编写程序时，可以使用ASCII编码，也可以使用utf-8编码
- 编译时们可以通过以下选项告诉编译器，如果不指定，默认编码方式为utf-8
``` txt
-finput-charset=GB2312
-finput-charset=UTF-8
```
- 编译好的可执行文件，可以指定其里面的字符是以什么格式编码;如果不指定，默认编码方式为utf-8
``` txt
-fexec-charset=GB2312
-fexec-charset=UTF-8
```

2. 汉字区位码，如HZK16文件，16*16的点阵，每个汉字用32字节来表示
- 以汉字"中"举例，其GB2312编码是d6 d0；d6是区码，每个区有94个汉字；d0是位码，表示该区内第几个汉字
- 因此是HZK16的第“(0xd6 - 0xa1)*94+(0xd0 - 0xa1)”个汉字
3. [代码](../../source/LinuxAppDevBasic/source/09_show_chinese/show_chinese.c)

## [6-4] 交叉编译程序的万能命令_以freetype为例
1. 编译程序时去哪找头文件？
- 系统目录，交叉工具链的某个include目录
- 编译时，使用命令 "-I dir" 来指定

2. 链接时去哪找库文件？
- 系统目录，交叉工具链的某个lib目录
- 编译时，使用命令 "-L dir" 来指定

3. 运行时去哪找库文件？
- 系统目录，板子上的/lib, /usr/lib目录
- 自己指定，运行程序用环境变量 `LD_LIBRAY_PATH` 来指定

4. 如何确定系统目录？
- `echo 'main(){}' | arm-linux-gcc -E -v -`

5. 万能编译命令，结果存在当前目录下的/tmp目录下
- `./configure --host=arm-linux --prefix=$PWD/tmp` 
- `make`
- `make install`


## [6-5] 使用freetype显示单个文字
1. 使用点阵显示是，字符大小固定，如果放大或缩小则会模糊甚至有锯齿出现，因此引入矢量字体
2. [代码](../../source/LinuxAppDevBasic/source/10_freetype/02_freetype_show_font/freetype_show_font.c)


## [6-6] 使用freetype显示一行文字
1. [代码](../../source/LinuxAppDevBasic/source/10_freetype/04_show_line/show_line.c)
2. freetype的几个重要数据结构
- FT_Library : 使用freetype之前要先调用以下代码
``` C
FT_Library library;
error = FT_Init_FreeType(&library); /*初始化freetype库*/
```

- FT_Face: 对应一个矢量字体文件
``` C
error = FT_New_Face(libray, font_file, 0, &face); /*加载字体文件*/
```

- FT_GlyphSlot: 插槽，用来存放字符的处理结果（如：位图、边框、位置信息等），注意只能存一次，下一次的存入会覆盖前一次的结果

- FT_Glyph: 字体文件中保存字符的原始关键点信息，使用freetype的函数可以进行放大、缩小、旋转，处理后新的关键点也保存在插槽里
``` C
error = FT_Get_Glyph(slot, &glyph);
```

- FT_BBox: 表示一个字符的外框
``` C
FT_Glyph_Get_Box(glyph, FT_GLYPH_BBOX_TRUNATE, &bbox);
```
