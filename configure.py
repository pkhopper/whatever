#!/usr/bin/env python
# coding=utf-8

import os
import sys
import subprocess
reload(sys).setdefaultencoding("utf8")

pabspath = os.path.abspath
pjoin = os.path.join

_src_path = pabspath("src")
_bdbbox_path = pabspath("src/bdbbox")
_pbbox_path = pabspath("src/pbbox")
_protoc_bin = pabspath("vsprojects/pbbox/protoc.exe")
_protoc_cpp_out = "--cpp_out=%s" % (pabspath("./"))
_protoc_proto_path = pabspath(pjoin(_pbbox_path, "proto"))

def _exec_bin(*cmd_args):
    print cmd_args
    subp = subprocess.Popen(cmd_args, stdout=sys.stdout, stderr=sys.stderr)
    return subp.returncode

def compile_proto_files():
    print("compile_proto_files:")
    proto_files = [pjoin(_protoc_proto_path, f) for f in os.listdir(_protoc_proto_path) if f.endswith(".proto")]
    _exec_bin(_protoc_bin, _protoc_cpp_out, proto_files)
    print("compile_proto_files finish: %d files compiled." % (len(proto_files)))

def main():
    compile_proto_files()

if __name__ == '__main__':
        main()

