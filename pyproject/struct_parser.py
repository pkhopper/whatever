#!/usr/bin/env python
# coding=utf-8

import os
import sys
import os.path as pathtool

TYPE_DICT = {
    "int8_t"  : None,
    "int16_t" : None,
    "int32_t" : None,
    "int64_t" : None,
    "uint8_t" : None,
    "uint16_t": None,
    "uint32_t": None,
    "uint64_t": None,
    "char"    : None,
    "float"   : None,
    "double"  : None
}


def get_lines_from_file(file_name):
    if not pathtool.exists(file_name):
        return []
    if not pathtool.isfile(file_name):
        raise ValueError('should be a file, {} is dir not file.'.format(file_name))
    with open(file_name, 'r') as fp:
        results = fp.readlines()
        # del comment
        results = [l[:l.find("//")] if l.find("//") else l for l in results]
        # trim
        results = [l.strip() for l in results]
        # del empty lines
        results = [l for l in results if l != '']
    return results


class CStructType:
    def __init__(self):
        self.name = ""
        self.begin = -1
        self.end = -1
        self.attr = (None, None)

    def parse(self, lines):
        pass


def parse_file(file_name):
    lines = get_lines_from_file(file_name)   # available lines
    return lines


if __name__ == "__main__":
    CStructs = parse_file("test.h")
    print CStructs

