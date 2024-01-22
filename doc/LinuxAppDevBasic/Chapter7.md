# 第7章 输入系统应用编程

## [7-1] 输入系统框架及调试
1. Linux针对同的设备构造了统一的驱动程序
2. 内核中使用`input_dev`结构体来表示输入设备
3. app如何判断是否得到了完整数据？ 同步事件(code, type ,value全是0)
4. 查看有哪些输入设备
``` shell 
[root@100ask:~] ls /dev/input/* -l
crw-rw----    1 root     input      13,  64 Jan  1 00:00 /dev/input/event0
crw-rw----    1 root     input      13,  65 Jan  1 00:00 /dev/input/event1
crw-rw----    1 root     input      13,  66 Jan  1 00:00 /dev/input/event2
crw-rw----    1 root     input      13,  63 Jan  1 00:00 /dev/input/mice
```
5. 如何判断event对应什么硬件
``` shell
[root@100ask:~] cat /proc/bus/input/devices
I: Bus=0019 Vendor=0000 Product=0000 Version=0000
N: Name="20cc000.snvs:snvs-powerkey"
P: Phys=snvs-pwrkey/input0
S: Sysfs=/devices/soc0/soc/2000000.aips-bus/20cc000.snvs/20cc000.snvs:snvs-powerkey/input/input0
U: Uniq=
H: Handlers=kbd event0 evbug
B: PROP=0
B: EV=3  # 表示支持哪一类事件Event types，即0b101: 支持事件0 EV_SYN，事件1 EV_KEY
B: KEY=100000 0 0 0

I: Bus=0018 Vendor=dead Product=beef Version=28bb
N: Name="goodix-ts"
P: Phys=input/ts
S: Sysfs=/devices/virtual/input/input1
U: Uniq=
H: Handlers=event1 evbug
B: PROP=2
B: EV=b # 表示支持哪一类事件Event types，即0b1011: 支持事件0 EV_SYN，事件1 EV_KEY，事件3 EV_ABS
B: KEY=1c00 0 0 0 0 0 0 0 0 0 0 # 表示支持哪一些KEY的事件
B: ABS=6e18000 0    #表示支持哪一些ABS的事件，注意该值是32位，合并为64位，然后每一bit对应一个事件

I: Bus=0019 Vendor=0001 Product=0001 Version=0100
N: Name="gpio-keys"
P: Phys=gpio-keys/input0
S: Sysfs=/devices/soc0/gpio-keys/input/input2
U: Uniq=
H: Handlers=kbd event2 evbug
B: PROP=0
B: EV=3
B: KEY=c
```

其中 I,N,P,S 对应 input_dev 结构体
## [7-2] 现场编程读取获取输入设备信息
1. app访问硬件的四种方式
- 轮询方式
- 休眠唤醒方式
- poll方式：妈妈陪小孩睡一小会，定个闹钟；要么被小孩吵醒，要么被闹钟吵醒
- 异步通知
2. 内核中 `evdev_do_ioctl()` 函数获取设备相关信息
- 因为各种event被定义在内核的 `input.h` 文件中，所以在写代码的时候需要include工具链提供的
- 进入某个目录，查找某个文件 `find -name input.h`
3. 系统调用`ioctl()`函数来获取设备硬件信息和驱动程序打交道

## [7-3] 查询休眠唤醒方式读取输入数据



## [7-4] POLL SELECT方式读取输入数据



## [7-5] 异步通知方式读取输入数据



## [7-6] 电阻屏和电容屏



## [7-7] tslib框架分析



## [7-8] tslib交叉编译与测试



## [7-9] 编写基于tslib的测试程序


