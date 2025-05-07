sf3000_toolchain_v0.1
Usage
Download the mipsel-buildroot-linux-gnu_sdk-buildroot.tar.gz file to /opt
Run relocate-sdk.sh
cd /opt
tar zxvf mipsel-buildroot-linux-gnu_sdk-buildroot.tar.gz
cd mipsel-buildroot-linux-gnu_sdk-buildroot
./relocate-sdk.sh
Define the environment variables to use the toolchain.
For example, create the sf3000-env.sh file and make the contents as shown below.
Define the environment variables with the source ./sf3000-env.sh command
Add the necessary variables depending on the program you are building.
#!/bin/sh

TOOLBIN="/opt/mipsel-buildroot-linux-gnu_sdk-buildroot/bin/mips-mti-linux-gnu-"
export SYSROOT="/opt/mipsel-buildroot-linux-gnu_sdk-buildroot/mipsel-buildroot-linux-gnu/sysroot"
export CROSS_COMPILE="/opt/mipsel-buildroot-linux-gnu_sdk-buildroot/bin/mips-mti-linux-gnu-"
export CC=${TOOLBIN}gcc
export CXX=${TOOLBIN}g++
export LD=${TOOLBIN}ld
export AS=${TOOLBIN}as
export AR=${TOOLBIN}ar
export RANLIB=${TOOLBIN}ranlib
export STRIP=${TOOLBIN}strip
export CFLAGS="-O2 -march=mips32r2"
export CXXFLAGS="-O2 -march=mips32r2"
#export LDFLAGS="-L"
#export CPPFLAGS="-I"
#export PKG_CONFIG_PATH=""
export PATH="${SYSROOT}/bin:$PATH"
export HOST=mipsel-linux-gnu
export TARGET=mipsel-linux-gnu
