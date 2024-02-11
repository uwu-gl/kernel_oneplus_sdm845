# Kernel for OnePlus 6/6t
# Introduction
This kernel based on OnePlusOSS's kernel, and added some commits to build.  
Already supported KernelSU, LXC, docker.
# Build
1. Parpare for environment  
  [!] DO NOT RUN BUILD AS ROOT!!  
    <1> Back to user space  
      `$ cd ~`
  
    <2> Download packages  
      `$ sudo apt-get install git ccache automake flex lzop bison gperf build-essential zip curl gcc-aarch64-linux-gnu zlib1g-dev g++-multilib libxml2-utils bzip2 libbz2-dev libbz2-1.0 libghc-bzlib-dev squashfs-tools pngcrush schedtool dpkg-dev liblz4-tool make optipng maven libssl-dev pwgen libswitch-perl policycoreutils minicom libxml-sax-base-perl libxml-simple-perl bc libc6-dev-i386 lib32ncurses5-dev libx11-dev lib32z-dev libgl1-mesa-dev xsltproc unzip device-tree-compiler python2 python3`  
  
    <3> Download Clang  
      [!] Please use this clang, or you will maybe face troubles!  
      `$ mkdir -p ~/toolchains`  
      `$ git clone https://github.com/Grill-Laux/proton-clang.git --depth=1 ~/toolchains/clang`  
  
    <4> Download GCC  
      `$ git clone https://android.googlesource.com/platform/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9 -b android-10.0.0_r47 --depth=1 --single-branch --no-tags ~/toolchains/aarch64-linux-android-4.9`  
      `$ git clone https://android.googlesource.com/platform/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.9 -b android-10.0.0_r47 --depth=1 --single-branch --no-tags ~/toolchains/arm-linux-androideabi-4.9`  
  
    <5> Download kernel source  
      `$ git clone https://github.com/Grill-Laux/oos_kernel_oneplus_sdm845 android-kernel --recursive --depth=3`  
      `$ cd android-kernel`  
  
    <6> Now, let's setup path  
    First, set build path:  
      `$ export PATH=~/toolchains/clang/bin/:$PATH && export CC=clang && CLANG=~/toolchains/clang/bin && GCC32=~/toolchains/arm-linux-androideabi-4.9/bin && GCC64=~/toolchains/aarch64-linux-android-4.9/bin && PATH=$CLANG:$GCC64:$GCC32:$PATH && export PATH && export ARCH=arm64 && export CLANG_TRIPLE=aarch64-linux-gnu && export CROSS_COMPILE=aarch64-linux-android- && export CROSS_COMPILE_ARM32=arm-linux-androideabi-`  
    Second, set dtc:  
      `$ chmod +x dtc/dtc`  
      `$ export DTC_EXT=dtc/dtc`  
  
2. Start building!  
    Build defconfig:  
      `make ARCH=arm64 O=out CC="ccache clang" sdm845-perf_defconfig`  
    Build kernel:  
      `make ARCH=arm64 O=out CC=clang -j$(nproc --all) 2>&1 | tee kernel_log.txt`  
   The build target will in: {out/arch/arm64/boot/Image.gz-dtb}
  
# Face any problems?
Upload log in your source to issue page, and someone(me?) will give you help.
