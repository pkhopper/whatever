# coding=utf-8

import os
import sys
import subprocess
import shutil
reload(sys).setdefaultencoding("utf8")
from parse_proto import make_pbmessage_id_proto

ABS_PATH = os.path.abspath
PJOIN = os.path.join

_root_path = ABS_PATH("./")
_proto_path = _root_path
_dst_dir_py = ABS_PATH(PJOIN(_root_path, "../messages"))
_tmp_dir_cpp = ABS_PATH(PJOIN(_root_path, "cpp"))
_tmp_dir_py = ABS_PATH(PJOIN(_root_path, "py"))
_protoc_bin = ABS_PATH(PJOIN(_root_path, "protoc"))
_pbmessageid_file = ABS_PATH(PJOIN(_root_path, "PBMessageID.proto"))

def _exec_bin(cmd, *args):
    cmd_args = [cmd]	
    for arg in args:
	if isinstance(arg, list):
	    cmd_args += arg
    	else:
	    cmd_args.append(arg)
    subp = subprocess.Popen(cmd_args, stdout=sys.stdout, stderr=sys.stderr)
    return subp.returncode

def compile_proto_files():
    proto_files = [PJOIN(_proto_path, f) for f in os.listdir(_proto_path) if f.endswith(".proto")]
    make_pbmessage_id_proto(proto_files, _pbmessageid_file)
    ret = _exec_bin(
	    _protoc_bin,
	    "--cpp_out=%s" % _tmp_dir_cpp,
	    "--python_out=%s" % _tmp_dir_py,
	    "--proto_path=%s" % (_proto_path),
	    proto_files
		    )

    if ret:
	print("Error, ret=%d" % ret)

    return ret

def cpfiles():
    py_files = [(PJOIN(_tmp_dir_py, f), PJOIN(_dst_dir_py, f)) for f in os.listdir(_tmp_dir_py) if f.endswith(".py")]
    for src, dst in py_files:
	shutil.copyfile(src, dst)

    return


def main():
    for d in[_dst_dir_py, _tmp_dir_cpp, _tmp_dir_py]:
	if not os.path.exists(d):
	    os.mkdir(d)
    ret = compile_proto_files()
    if ret is None:
	cpfiles()
    else:
	print "err", ret
	raise

    return

if __name__ == '__main__':
    try:
	main()
    except Exception as e:
	print e
	os.system("pause")
