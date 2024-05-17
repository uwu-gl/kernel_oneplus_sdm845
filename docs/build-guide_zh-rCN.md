# OOS 内核编译指南

我会在这个教程中帮助你编译内核，并安装到您的6（t）上。

# 编译内核

### 操作系统需求

一个运行 **Linux 64位 (x86_64)** 的电脑，不要太旧。

在这个教程里，我们就用Ubuntu 20.04吧。

### 第一步： 设置编译环境

* 1. 使用apt安装软件包：
        ```bash
        sudo apt update -y
        sudo apt-get install -y git ccache wget automake flex lzop bison gperf build-essential zip curl zlib1g-dev libxml2-utils bzip2 libbz2-dev libbz2-1.0 libghc-bzlib-dev squashfs-tools pngcrush schedtool dpkg-dev liblz4-tool make optipng maven libssl-dev pwgen libswitch-perl policycoreutils minicom libxml-sax-base-perl libxml-simple-perl bc libc6-dev-i386 lib32ncurses5-dev libx11-dev lib32z-dev libgl1-mesa-dev xsltproc unzip device-tree-compiler python2 python3 gcc-9-aarch64-linux-gnu gcc-9-arm-linux-gnueabi gcc-aarch64-linux-gnu gcc-arm-linux-gnueabi
        sudo apt clean
        ```

        **提示： 这一步里我们已经安装好了gcc。**
        
        **R.I.P. Google GCC**



* 2. 然后从aosp下载clang：
        ```bash
        cd ~
        mkdir -p toolchains/clang && cd toolchains/clang
        wget -O clang.tar.gz https://android.googlesource.com/platform//prebuilts/clang/host/linux-x86/+archive/refs/tags/android-14.0.0_r0.78/clang-r416183b.tar.gz 
        tar zxvf clang.tar.gz
        rm -f clang.tar.gz
        cd -
        ```

### 第二步： 同步内核源码

```bash
git clone https://github.com/Grill-Laux/kernel_oneplus_sdm845 ~/android-kernel --recursive --depth=1 -b oos/wip-upstream
```
**警告： 请完全复制粘贴，如果要去掉某个参数，请谨慎！**

### 第三步： 设置path
```bash
CLANG=~/toolchains/clang/bin
PATH=$CLANG:$PATH
export PATH
export ARCH=arm64
export SUBARCH=arm64
export CLANG_TRIPLE=aarch64-linux-gnu-
export CROSS_COMPILE=aarch64-linux-gnu-
export CROSS_COMPILE_ARM32=arm-linux-gnueabi-
```

### 第四步： 开始编译
* 1. 回到内核源码目录
```bash
cd ~/android-kernel
```
* 2. 编译 `defconfig`:
```bash
make O=out sdm845-perf_defconfig
```
* 3. 编译内核
```bash
make -j $(nproc) O=out CC=clang
```

### [可选] 第五步： 制作anykernel3刷机包
```bash
git clone https://github.com/Grill-Laux/AnyKernel3 anykernel -b upstream
cp ~/android-kernel/out/arch/arm64/boot/Image.gz-dtb anykernel
zip -r anykernel3-oos-11.zip * -x .git README.md *placeholder
 ```

### [可选] 第六步： 安装刷机包

现在，将您的设备重启到**TWRP**

接下来，通过**USB 2.0接口**连接到您的设备。

确保您的Linux安装了`adb`：
```bash
sudo apt install adb -y
```

保持连接，在TWRP中点击**高级 -> adb sideload** （**Advanced -> adb sideload**）
```bash
adb sideload path-to-your-package.zip
```
请将`path-to-your-package.zip`替换成您的刷机包路径。

此时设备上的安装应该已经开始。

如果您有任何不理解/没看懂/认为有问题的地方，请打开一个新的issue，谢谢！
