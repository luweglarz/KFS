
BUILD_DIR=$(cd && pwd)

# Setting up the Cross Compiler Environment
export PREFIX="/opt/cross-compiling-i386"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"
export INSTALL_NUM_CORES=3
export export PWD_BUILD="$BUILD_DIR"

# Install required dependencies
sudo apt update
sudo apt upgrade
sudo apt install -y bridge-utils cpu-checker libvirt-clients libvirt-daemon qemu qemu-kvm xorriso mtools gcc nasm binutils make util-linux grub2-common e2fsprogs fdisk bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo wget

# Create a directory for the cross-compiler and navigate to it
cd 
mkdir -p cross-compiling-build
cd cross-compiling-build

# Download & Extract the latest versions of GCC, binutils, and gdb
wget https://ftp.gnu.org/gnu/binutils/binutils-2.41.tar.gz
tar -xf binutils-2.41.tar.gz
rm binutils-2.41.tar.gz

wget https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.gz
tar -xf gcc-13.2.0.tar.gz
rm gcc-13.2.0.tar.gz

wget https://ftp.gnu.org/gnu/gdb/gdb-13.2.tar.gz
tar -xf gdb-13.2.tar.gz
rm gdb-13.2.tar.gz

# Build Binutils
mkdir build-binutils
cd build-binutils
../binutils-*/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j $INSTALL_NUM_CORES
sudo make install -j $INSTALL_NUM_CORES

# Building GDB (Optional)
cd $PWD_BUILD/cross-compiling-build
mkdir build-gdb
cd build-gdb
../gdb-*/configure --target=$TARGET --prefix="$PREFIX" --disable-werror
make all-gdb -j $INSTALL_NUM_CORES
sudo make install-gdb -j $INSTALL_NUM_CORES

# Building GCC
cd $PWD_BUILD/cross-compiling-build
mkdir build-gcc
cd build-gcc
wget http://ftp.vim.org/ftp/gnu/gmp/gmp-6.3.0.tar.gz
tar -xf gmp-6.3.0.tar.gz
mv -v gmp-6.3.0 ../gcc-13.2.0/gmp
wget http://ftp.vim.org/ftp/gnu/mpc/mpc-1.3.1.tar.gz
tar -xf mpc-1.3.1.tar.gz
mv -v mpc-1.3.1 ../gcc-13.2.0/mpc
wget http://ftp.vim.org/ftp/gnu/mpfr/mpfr-4.2.1.tar.gz
tar -xf mpfr-4.2.1.tar.gz
mv -v mpfr-4.2.1 ../gcc-13.2.0/mpfr
../gcc-*/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
sudo make all-target-libgcc -j $INSTALL_NUM_CORES
sudo make install-gcc -j $INSTALL_NUM_CORES
sudo make install-target-libgcc -j $INSTALL_NUM_CORES

echo "Installation complete."

