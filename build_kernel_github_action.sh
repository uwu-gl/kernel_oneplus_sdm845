#!/bin/bash

echo "[ i ]  Parparing Environment..."
cd $GITHUB_WORKSPACE/android-kernel
# 交叉编译器路径
echo "[ i ]  Setting up PATH..."
export PATH=~/toolchains/clang/bin/:$PATH
export CC=clang
export CLANG_TRIPLE=aarch64-linux-gnu-
export CROSS_COMPILE=aarch64-linux-gnu-
export CROSS_COMPILE_ARM32=arm-linux-gnueabi-
# export CONFIG_BUILD_ARM64_DT_OVERLAY=y

echo "[ i ]  Setting up ARCH..."
export ARCH=arm64
export SUBARCH=arm64
# export DTC_EXT=dtc

if [ ! -d "out" ]; then
	mkdir out
fi

echo "[ i ]  Making kernel config..."
make ARCH=arm64 O=out CC="ccache clang" sdm845-perf_ksu_defconfig
# make ARCH=arm64 O=out CC=clang oldconfig

echo "[ i ]  Making kernel...(This may take long time)"
make ARCH=arm64 O=out CC=clang -j$(nproc --all) 2>&1 | tee kernel_log-${start_time}.txt


if [ -f out/arch/arm64/boot/Image.gz-dtb ]; then
	echo "[ i ]  Finished kernel building!"
	echo "[ i ]  Exiting script..."
	exit 0
else
	echo " "
	echo "[ x ]  Kernel building failed!"
	exit 0
fi
