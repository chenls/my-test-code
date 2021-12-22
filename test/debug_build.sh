#!/bin/bash
./bazel clean
./bazel build -s //sdk/megfinger:tee_sdk_demo_vendor
ln -sf bazel-out/../../../external .
python ../generate_compile_commands.py ../build.log ../compile_commands.json
