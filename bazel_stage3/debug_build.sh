#!/bin/bash
bazel clean
bazel build -s //main:hello-world -c dbg &> build.log
ln -sf bazel-out/../../../external .
python generate_compile_commands.py build.log compile_commands.json

# bazel query "deps(//main:hello-world)"