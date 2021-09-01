
# megtee makefile分析

- [megtee makefile分析](#megtee-makefile分析)
	- [概述](#概述)
	- [编译LLVM IR](#编译llvm-ir)
		- [LLVM基础架构的组成部分](#llvm基础架构的组成部分)
	- [opt优化](#opt优化)
	- [llc链接](#llc链接)
	- [处理sections](#处理sections)
	- [混淆符号](#混淆符号)

## 概述

此wiki是对[megtee编译流程](https://wiki.jiiov.com/pages/viewpage.action?pageId=8958666)的进一步补充说明。

使用`make -n` 只打印命令配方，不实际执行。在`sdk/megtee/mgb_loader/full_tee_sdk_demo/make_release_arch.sh`中make该行加入`-n`参数，可以查看编译详情。

除了`-n`参数，还有其它参数也可以用于调试，如：`make SHELL='sh -x'`，更多请查看：[How do I force make/GCC to show me the commands](https://stackoverflow.com/questions/5820303/how-do-i-force-make-gcc-to-show-me-the-commands)。

下面是测试代码使用`make -n`的输出和简单的分析。

## 编译LLVM IR

传统的静态编译器分为三个阶段：前端、中端（优化）、后端。

![](https://pic1.zhimg.com/v2-7a8a0c81a49b24601b43a24c28400fe0_b.jpg)

这样支持一种新的编程语言只需重新实现一个前端，支持一种新的目标架构只需重新实现一个后端，前端和后端连接枢纽就是LLVM IR。

LLVM IR本质上一种与源编程语言和目标机器架构无关的通用中间表示，是LLVM项目的核心设计和最大的优势。

LLVM IR有两种等价的格式，一种是.bc(Bitcode)文件，另一种是.ll文件，.ll文件是Human-readable的格式。

```bash
clang -S -emit-llvm factorial.c # factorial.ll
clang -c -emit-llvm factorial.c # factorial.bc
```

### LLVM基础架构的组成部分

1. 前端：将程序源代码转换为LLVM IR的编译器步骤，包括词法分析器、语法分析器、语义分析器、LLVM IR生成器。Clang执行了所有与前端相关的步骤，并提供了一个插件接口和一个单独的静态分析工具来进行更深入的分析
2. 中间表示：LLVM IR可以以可读文本代码和二进制代码两种形式呈现。LLVM库中提供了对IR进行构造、组装和拆卸的接口。LLVM优化器也在IR上进行操作，并在IR上进行了大部分优化。
3. 后端：负责汇编码或机器码生成的步骤，将LLVM IR转换为特定机器架构的汇编代码或而二进制代码，包括寄存器分配、循环转换、窥视孔优化器、特定机器架构的优化和转换等步骤

下面这张图展示了使用LLVM基础架构时各个组件之间的关系

![方式1](https://pic3.zhimg.com/v2-ce0862518431db8d811e841b3946bd42_b.jpg)

除此之外，各个组件之间的协作关系也可以以下面这种方式组织

![方式2](https://pic4.zhimg.com/v2-eb6d98b202e13f30daba74e9595ba54f_b.jpg)

**两种方式不同之处，后面这种方式会先使用LLVM IR 链接器（即llvm-link）将多个bc文件合并成一个，我们的处理方式就是如此。**

参考链接：[LLVM概述——基础架构](https://www.zhihu.com/column/llvm-tutorial)， [A Tour to LLVM IR（上）](https://zhuanlan.zhihu.com/p/66793637)

如下则是先使用`clang -emit-llvm`参数，将.c和.cpp文件转换成.bc文件：

```bash
echo "[c] mylib1.c ..."
mkdir -pv build/qsee-aarch64-O3/./
clang -emit-llvm -O3 --target=aarch64-none-linux-android28 -fvisibility=hidden -fvisibility-inlines-hidden -fomit-frame-pointer -DNDEBUG -Wall -Wextra -Wwrite-strings -D_XOPEN_SOURCE=700 -fPIC -fpie -march=armv8.2-a+fp16+dotprod -DMEGDNN_DISABLE_FLOAT16 -Isrc/sys/include -Isrc -IFingerprintUnlock/tee_sdk/vendor//include/  -DIS_AARCH64 -Ithird-party/musl/arch/aarch64 -Isrc/sys/musl_aarch64/internal -Ithird-party/musl/arch/generic -Ithird-party/install_aarch64/include   -Ilibdebase/include -Ilibdebase/src -Ilibdebase/src/include -MM -MT "build/qsee-aarch64-O3/./mylib1.c.bc" "mylib1.c"  > "build/qsee-aarch64-O3/./mylib1.c.d"
clang -c mylib1.c -o build/qsee-aarch64-O3/./mylib1.c.bc -emit-llvm -O3 --target=aarch64-none-linux-android28 -fvisibility=hidden -fvisibility-inlines-hidden -fomit-frame-pointer -DNDEBUG -Wall -Wextra -Wwrite-strings -D_XOPEN_SOURCE=700 -fPIC -fpie -march=armv8.2-a+fp16+dotprod -DMEGDNN_DISABLE_FLOAT16 -Isrc/sys/include -Isrc -IFingerprintUnlock/tee_sdk/vendor//include/  -DIS_AARCH64 -Ithird-party/musl/arch/aarch64 -Isrc/sys/musl_aarch64/internal -Ithird-party/musl/arch/generic -Ithird-party/install_aarch64/include   -Ilibdebase/include -Ilibdebase/src -Ilibdebase/src/include

echo "[c] mylib2.c ..."
mkdir -pv build/qsee-aarch64-O3/./
clang -emit-llvm -O3 --target=aarch64-none-linux-android28 -fvisibility=hidden -fvisibility-inlines-hidden -fomit-frame-pointer -DNDEBUG -Wall -Wextra -Wwrite-strings -D_XOPEN_SOURCE=700 -fPIC -fpie -march=armv8.2-a+fp16+dotprod -DMEGDNN_DISABLE_FLOAT16 -Isrc/sys/include -Isrc -IFingerprintUnlock/tee_sdk/vendor//include/  -DIS_AARCH64 -Ithird-party/musl/arch/aarch64 -Isrc/sys/musl_aarch64/internal -Ithird-party/musl/arch/generic -Ithird-party/install_aarch64/include   -Ilibdebase/include -Ilibdebase/src -Ilibdebase/src/include -MM -MT "build/qsee-aarch64-O3/./mylib2.c.bc" "mylib2.c"  > "build/qsee-aarch64-O3/./mylib2.c.d"
clang -c mylib2.c -o build/qsee-aarch64-O3/./mylib2.c.bc -emit-llvm -O3 --target=aarch64-none-linux-android28 -fvisibility=hidden -fvisibility-inlines-hidden -fomit-frame-pointer -DNDEBUG -Wall -Wextra -Wwrite-strings -D_XOPEN_SOURCE=700 -fPIC -fpie -march=armv8.2-a+fp16+dotprod -DMEGDNN_DISABLE_FLOAT16 -Isrc/sys/include -Isrc -IFingerprintUnlock/tee_sdk/vendor//include/  -DIS_AARCH64 -Ithird-party/musl/arch/aarch64 -Isrc/sys/musl_aarch64/internal -Ithird-party/musl/arch/generic -Ithird-party/install_aarch64/include   -Ilibdebase/include -Ilibdebase/src -Ilibdebase/src/include
```

使用`llvm-link`命令，将多个.bc文件合并成一个：

```bash
echo "Merging bitcode files ..."
# Combined bc file
llvm-link -o build/qsee-aarch64-O3/merged.bc.nonopt0 build/qsee-aarch64-O3/./mylib1.c.bc build/qsee-aarch64-O3/./mylib2.c.bc
```

## opt优化

opt链接优化这个步骤不是一定需要执行，执行该步骤可以减少二进制文件大小，优化执行速度，参考链接：<https://llvm.org/devmtg/2013-11/slides/Gao-LTO.pdf>

```bash
# opt --help 查看帮助
# -internalize：隐藏全局符号
# -internalize-public-api-list：要保留的符号名称列表
opt -internalize \
 -internalize-public-api-list=mylib1,mylib2,__addtf3,__eqtf2,__extenddftf2,__fixtfsi,__fixunstfsi,__floatsitf,__floatunsitf,__multf3,__netf2,__subtf3,__unordtf2,__getf2,__divtf3,__letf2,__extendsftf2,__trunctfsf2,__trunctfdf2 \
 -o build/qsee-aarch64-O3/merged.bc.nonopt1 build/qsee-aarch64-O3/merged.bc.nonopt0
# -mergefunc：合并函数
# -std-link-opts：包括标准链接时间优化
opt -O3 -relocation-model=pic -thread-model=single -disable-simplify-libcalls -mergefunc -std-link-opts -o build/qsee-aarch64-O3/merged.bc build/qsee-aarch64-O3/merged.bc.nonopt1
```

## llc链接

```bash
echo "Linking ..."
# 将链接得到的IR转成target相关的code
# Run llc to generate combined .o file, llc -filetype=obj -O3
llc -O3 -relocation-model=pic -thread-model=single -disable-simplify-libcalls -filetype=obj -o build/qsee-aarch64-O3/main-orig.o build/qsee-aarch64-O3/merged.bc

# add asm.o
aarch64-linux-gnu-ld -r -d build/qsee-aarch64-O3/main-orig.o  -o build/qsee-aarch64-O3/main-withasm.o
```

## 处理sections

此处的处理为了fix_init_fini，即保证C++的全局静态初始化的调用在tee初始化malloc/free的指针之后

```bash
echo "Fix init/fini array ..."
cp build/qsee-aarch64-O3/main-withasm.o build/qsee-aarch64-O3/main-ia.o.tmp
./elfmanip/prepare_merge.sh build/qsee-aarch64-O3/main-ia.o.tmp
aarch64-linux-gnu-ld -T link-ia.ld -r -d build/qsee-aarch64-O3/main-ia.o.tmp -o build/qsee-aarch64-O3/main-ia.o
./elfmanip/fix_init_fini.sh build/qsee-aarch64-O3/main-ia.o

echo "Merge sections ..."
aarch64-linux-gnu-ld -T link-merge.ld -r -d build/qsee-aarch64-O3/main-ia.o -o build/qsee-aarch64-O3/main.o
```

## 混淆符号

```bash
echo "[objcopy] build/qsee-aarch64-O3/main-pub.o"
aarch64-linux-gnu-objcopy \
	--keep-global-symbol=mylib1 --keep-global-symbol=mylib2 \
	build/qsee-aarch64-O3/main.o build/qsee-aarch64-O3/main-pub.o

echo "Mangling ..."
./elfmanip/mangle_sym.py build/qsee-aarch64-O3/main-pub.o build/qsee-aarch64-O3/main-mangle.o --objcopy aarch64-linux-gnu-objcopy --nm llvm-nm

cp -a build/qsee-aarch64-O3/main-mangle.o anctee__aarch64.o
llvm-nm anctee__aarch64.o | grep ' [A-Z] '
```
