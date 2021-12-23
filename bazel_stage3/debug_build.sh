#!/bin/bash

# bazel query "deps(//main:hello-world)"

# bazel clean
# bazel build -s //main:hello-world -c dbg &> build.log
# ln -sf bazel-out/../../../external .
# python generate_compile_commands.py build.log compile_commands.json


if [ ! -f "tools/actions/BUILD" ]; then
    sh ./Bazel_and_CompileCommands/setup_compile_commands.sh
fi
sh ./Bazel_and_CompileCommands/create_compile_commands.sh //main:hello-world
ln -sf bazel-out/../../../external .
