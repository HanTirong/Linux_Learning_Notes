# 第5章 Framebuffer应用编程

## [5-1] Framebuffer应用编程
1. 当应用程序想要去显示某个像素点的颜色时，首先要获取LCD的参数例如分辨率，bpp
通过bpp可以在知道像素的格式，根据像素的xy坐标，找到Framebuffer中对应的地址，在其中填充数据
2. [代码](../../source/LinuxAppDevBasic/source/07_framebuffer/show_pixel.c)
3. `ioct()` 用来提取或写入LCD的参数信息
4. `munmap()` 重映射

