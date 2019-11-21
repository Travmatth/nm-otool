#!/usr/bin/python
import sys
import os
import subprocess

if __name__ == "__main__":
    artifacts = os.listdir("./test/artifacts")

    nm_string = "nm test/artifacts/{}"
    nm_executables = [nm_string.format(file).split(" ") for file in artifacts]
    nm_out = "./test/ref/nm_{}.txt"
    nm_outfiles = [nm_out.format(s.split(".")[0]) for s in artifacts]

    otool_string = "otool -t test/artifacts/{}"
    otool_executables = [otool_string.format(file).split(" ") for file in artifacts]
    otool_out = "./test/ref/otool_{}.txt"
    otool_outfiles = [otool_out.format(s.split(".")[0]) for s in artifacts]

    for i in range(len(artifacts)):
        with open(nm_outfiles[i], "w+") as f:
            print("executing: " + " ".join(nm_executables[i]) + " > " + nm_outfiles[i])
            if len(sys.argv) == 1:
                subprocess.call(nm_executables[i], stdout=f, shell=False)
        with open(otool_outfiles[i], "w+") as f:
            print("executing: " + " ".join(otool_executables[i]) + " > " + otool_outfiles[i])
            if len(sys.argv) == 1:
                subprocess.call(otool_executables[i], stdout=f, shell=False)
