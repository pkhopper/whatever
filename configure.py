#!/usr/bin/env python
# coding=utf-8

import os
import sys
import subprocess
reload(sys).setdefaultencoding("utf8")

_src_path="src"
_bdbbox_path="src/bdbbox"
_pbbox_path="src/pbbox"
_proto_file_path=os.path.join(_pbbox_path, "proto")
_protoc_bin="vsprojects/pbbox/protoc.exe"
_protoc_cpp_out="--cpp_out=%s" % ("./")

def _exec_bin(*cmd_args):
    subp = subprocess.Popen(cmd_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    while subp.poll() is None:
        stdout =  subp.stdout.readline()
        stderr =  subp.stderr.readline()
        if stdout.strip() is not "":
            print(stdout)
        if stderr.strip() is not "":
            print(stderr)
        sys.stdout.flush()
    return subp.returncode

def _build_cl_proto(src_proto, out_hcpp):
    return _exec_bin(_protoc_bin, src_proto, out_hcpp)

def compile_proto_files():
    print("compile_proto_files:")
    proto_files = [os.path.join(_proto_file_path, f) for f in os.listdir(_proto_file_path) if f.endswith(".proto")]
    count = 0
    for proto in proto_files:
        if _build_cl_proto(proto, _protoc_cpp_out) is 0:
            count += 1
    print("compile_proto_files finish: %d files compiled." % (count))

def main():
    compile_proto_files()

if __name__ == '__main__':
    main()
