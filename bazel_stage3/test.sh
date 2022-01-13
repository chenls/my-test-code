# /usr/bin/gcc -U_FORTIFY_SOURCE -fstack-protector -Wall -Wunused-but-set-parameter -Wno-free-nonheap-object -fno-omit-frame-pointer -std=c++0x -MD -MF bazel-out/k8-fastbuild/bin/main/_objs/hello-world/hello-world.pic.d -frandom-seed=bazel-out/k8-fastbuild/bin/main/_objs/hello-world/hello-world.pic.o -fPIC -iquote . -iquote bazel-out/k8-fastbuild/bin -iquote external/bazel_tools -iquote bazel-out/k8-fastbuild/bin/external/bazel_tools -fno-canonical-system-headers -Wno-builtin-macro-redefined -D__DATE__=\"redacted\" -D__TIMESTAMP__=\"redacted\" -D__TIME__=\"redacted\" -c main/hello-world.cc -o bazel-out/k8-fastbuild/bin/main/_objs/hello-world/hello-world.pic.o

/data/arm-toolchains/clang+llvm-9.0.0-linux-x86_64-ubuntu16.04/bin/clang++ \
-S -emit-llvm -I. main/hello-world.cc -o - | opt -analyze -std-link-opts -dot-callgraph
cat callgraph.dot |
    c++filt |
    sed 's,>,\\>,g; s,-\\>,->,g; s,<,\\<,g' |
    gawk '/external node/{id=$1} $1 != id' |
    dot -Tpng -ocallgraph.png

cat callgraph.dot |
    c++filt |
    sed 's,>,\\>,g; s,-\\>,->,g; s,<,\\<,g' |
    gawk '/external node/{id=$1} $1 != id' >callgraph2.dot
