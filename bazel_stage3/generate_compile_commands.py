#!/usr/bin/python3

import sys
import re
import json
import os

if __name__ == "__main__":
    cc_list = []
    command_pattern = re.compile("  (.*\.o)\\)")
    file_patter = re.compile("-c (.*) -o")
    with open(sys.argv[1], "r") as log_file:
        log = log_file.read()
        commands = command_pattern.findall(log)
        for command in commands:
            result_file = file_patter.findall(command)
            cc = {
                "command": command,
                "directory": os.getcwd(),
                "file": result_file.pop(),
            }
            cc_list.append(cc)

    with open(sys.argv[2], "w") as outdb:
        json.dump(cc_list, outdb, indent=2)

    print("DONE")
