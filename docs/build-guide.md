# OxygenOS kernel build guide

This page will guide you build out OnePlus 6/6T kernel and install on your device.

# Compile kernel

### Operating system requirements

A recent computer that runs **Linux 64-bit (x86_64)**.

In this guide, we will use Ubuntu 20.04.

### Step 1. Set up compile environment

* 1. Using apt to install necessary packages:
        ```bash
        sudo apt update -y
        sudo apt-get install -y git ccache wget automake flex lzop bison gperf build-essential zip curl zlib1g-dev libxml2-utils bzip2 libbz2-dev libbz2-1.0 libghc-bzlib-dev squashfs-tools pngcrush schedtool dpkg-dev liblz4-tool make optipng maven libssl-dev pwgen libswitch-perl policycoreutils minicom libxml-sax-base-perl libxml-simple-perl bc libc6-dev-i386 lib32ncurses5-dev libx11-dev lib32z-dev libgl1-mesa-dev xsltproc unzip device-tree-compiler python2 python3 gcc-9-aarch64-linux-gnu gcc-9-arm-linux-gnueabi gcc-aarch64-linux-gnu gcc-arm-linux-gnueabi
        sudo apt clean
        ```

        **Tips: We have already installed GCC in this step.**



* 2. Then clone clang from aosp:
        ```bash
        cd ~
        mkdir -p toolchains/clang && cd toolchains/clang
        wget -O clang.tar.gz https://android.googlesource.com/platform//prebuilts/clang/host/linux-x86/+archive/refs/tags/android-14.0.0_r0.78/clang-r416183b.tar.gz 
        tar zxvf clang.tar.gz
        rm -f clang.tar.gz
        cd -
        ```

### Step 2. Sync up kernel source

```bash
git clone https://github.com/Grill-Laux/kernel_oneplus_sdm845 ~/android-kernel --recursive --depth=1 -b oos/wip-upstream
```
**Tips: Please take place branch you want.**

### Step 3. Set up PATH
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

### Step 4. Start build
* 1. Back to kernel source folder:
```bash
cd ~/android-kernel
```
* 2. Make `defconfig`:
```bash
make O=out sdm845-perf_defconfig
```
* 3. Compile kernel
```bash
make -j $(nproc) O=out CC=clang
```

### [OPTIONAL] Step 5. Make AnyKernel3 package
```bash
git clone https://github.com/Grill-Laux/AnyKernel3 anykernel -b upstream
cp ~/android-kernel/out/arch/arm64/boot/Image.gz-dtb anykernel
zip -r anykernel3-oos-11.zip * -x .git README.md *placeholder
 ```

### [OPTIONAL] Step 6. Install AnyKernel3 package

Now, reboot your device to **TWRP** recovery mode that support to use **adb sideload** .

Then, connect your device with your PC through **USB 2.0 port**.

Make sure your PC has already installed `adb`:
```bash
sudo apt install adb -y
```

Keep your connection, click **Advanced > adb sideload** on your device, and run command below on your PC:
```bash
adb sideload path-to-your-package.zip
```
Please notice replacing `path-to-your-package.zip` to your path!

On your device, the installation should be started.

If you face any problems, please give an issue or contact me, thanks!
