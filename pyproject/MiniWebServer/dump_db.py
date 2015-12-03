#!/usr/bin/env python
# coding=utf-8


__author__ = 'liletian'


import os
import sys
import subprocess


pjoin = os.path.join
pdirname = os.path.dirname
pabspath = os.path.abspath
plistdir = os.listdir


BASEPATH = r"./"
OUT_DIR = "./"
DBPATH = './DB/'
ENVPATH = './Env/'
BDBUTILPATH = '/home/mrdTomcat/bo/linuxsvr/bdbtools/bin'


def _exec_bin(cmd, *args):
    cmd_args = [cmd]
    for arg in args:
        if isinstance(arg, list):
            cmd_args += arg
        else:
            cmd_args.append(arg)
    print cmd_args
    subp = subprocess.Popen(cmd_args, stdout=sys.stdout, stderr=sys.stderr)
    return subp.returncode


def main():
    cmd = "db_dump" # pjoin(BDBUTILPATH, "db_dump")
    dbfiles = [(pjoin(DBPATH, f), pjoin(OUT_DIR, f + ".txt")) for f in plistdir(DBPATH)]
    for src,f in dbfiles:
        _exec_bin(cmd, "-f", f, "-h", ENVPATH, src)
    print "====================================================\n"
    print "exec %d\n" % (len(dbfiles))


if __name__ == "__main__":
    try:
        if len(sys.argv) < 3:
            print "need base and ouput path"
            exit(0)

        BASEPATH = sys.argv[1]
        OUT_DIR = sys.argv[2]
        if not os.path.isdir(OUT_DIR):
            os.mkdir(OUT_DIR)

        DBPATH = pabspath(pjoin(BASEPATH, DBPATH))
        OUT_DIR = pabspath(OUT_DIR)
        ENVPATH = pabspath(pjoin(BASEPATH, ENVPATH))
        BDBUTILPATH = pabspath(BDBUTILPATH)

        print DBPATH
        print OUT_DIR
        print ENVPATH
        print BDBUTILPATH

        main()

    except KeyboardInterrupt as e:
        print 'stop by user'
    exit(0)
