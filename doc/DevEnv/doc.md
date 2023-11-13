### 第一章 HelloWorld
#### [1-1] 嵌入式Linux开发环境介绍
1. 在win编辑代码
2. 在服务器编译
3. 在开发板运行






#### [1-2] 配置VMWare使用双网卡
- NAT网卡：保证Ubuntu可以上网  
- 桥接网卡：保证开发板与Ubuntu互通
- 对于VMware:
    - 添加USB网卡,作为桥接网卡
        - vmware 添加桥接网卡
        - vmnet 选择网卡
    - 设置ip
- 对于win：
    - 设置ip
- 对开发板：
    - 设置ip，三者网段一致




#### [1-7] 开发板挂载Ubuntu的NFS目录
- NFS (Net File System)
- 开发板通过该协议与Ubuntu目录建立联系
    - Ubuntu目录要开权限，在 `/etc/exports`指出哪些目录是开放出来让别人挂载的
    - 启动NFS服务
    - 开发板挂载NFS到本地一个目录 `mount`命令
    `mount -t nfs -o nolock,vers=3 192.168.5.11:/home/book/nfs_rootfs /mnt`
    将 “192.168.5.11:/home/book/nfs_rootfs” 挂载到 本地的 “/mnt” 目录下









#### [1-9] 编译替换内核——设备树——驱动
- 驱动程序中头文件来自于内核，所以一个驱动程序依赖于内核，必须要有内核源码并且内核编译过 
- 因此编写驱动程序之前，需要先编译内核，编译好的内核需要放到开发板去运行  
1. 配置编译内核、设备树、其他驱动程序
2. 把以上放到开发板
3. 编译，测试第一个驱动程序







#### [1-10] 开发板的第一个驱动

1. 参考手册






#### [1-11] 使用Buildroot编译整套系统

1. 耗时太久，没有实验，具体步骤参考手册






#### [1-12] 烧写系统
1. 板子设置成USB启动模式，连接OTG线，模拟出一个6ULL的设备
2. 打开烧录软件，点击专业版，点击固件/裸机的运行按钮，会下载uboot，模拟出一个新的download设备
3. 用烧录软件基础版，点击烧写整个系统，会将files文件夹下的固件烧录；烧录完成后切换成EMMC启动，进入 `/etc/init.d/` 下，S05lvgl 是一个启动文件，S99myirhmi2是Qt界面的启动文件





