# coding=utf-8

import re
import os
import sys
import subprocess
import shutil
reload(sys).setdefaultencoding("utf8")

ABS_PATH = os.path.abspath
PJOIN = os.path.join

_root_path = ABS_PATH("./")
_proto_path = _root_path
_dst_dir_py = ABS_PATH(PJOIN(_root_path, "../messages"))
_tmp_dir_cpp = ABS_PATH(PJOIN(_root_path, "cpp"))
_tmp_dir_py = ABS_PATH(PJOIN(_root_path, "py"))
_protoc_bin = ABS_PATH(PJOIN(_root_path, "protoc"))
_out_put_file = ABS_PATH(PJOIN(_root_path, "PBMessageID.proto"))


ENUM_STR = """
// create by script, do not change
enum MESSAGE_IDS
{
%s
}
"""


class PBProto:
    def __init__(self, file_name):
        self.file_name_ = file_name
        self.package_ = ""
        self.messages = []
        self.message_string_list = []

    def parse(self):
        lines = []
        with open(self.file_name_) as f:
            lines = f.readlines()
        lines = [line.strip() for line in lines]
        lines = [line for line in lines if not line.startswith ('//')]
        lines = [line for line in lines if len(line) > 0]

        reg_package = re.compile("package\s+([^;]+)\s*")
        reg_message = re.compile("message\s+([^\s]+)\s*")
        nested = 0
        for line in lines:
            if line.startswith('{'):
                nested += 1
            elif line.startswith ('}'):
                nested -= 1
            elif line.startswith ("package"):
                self.package_ = reg_package.match (line).groups ()[0]
            elif line.startswith ('message'):
                if nested is 0:
                    self.messages.append (reg_message.match (line).groups ()[0])
        prefix = self.package_.replace('.', '_')
        for message in self.messages:
            self.message_string_list.append("%s_%s" % (prefix, message))


def make_pbmessage_id_proto(proto_files, output_file):
    protoObjs = []
    # 读文件
    for proto in proto_files:
        protoObjs.append(PBProto(proto))
    # 解析
    for proto in protoObjs:
        try:
            proto.parse ()
        except:
            raise "err: proto file %s" % (proto.file_name_)
    # 组合
    counter_base = 0
    messages_id_string = ""
    for proto in protoObjs:
        counter_base += 1000
        counter = counter_base
        messages_id_string += "// %d from %s \n" % (len(proto.message_string_list), proto.file_name_)
        for msg_string in proto.message_string_list:
            counter += 1
            messages_id_string += "%s = %d;\n" % (msg_string, counter)
            if counter > counter_base + 1000:
                raise "message overflow in one proto file, more then 1000!!!"
    outputstring = ENUM_STR % (messages_id_string)
    # 输出
    with open (output_file, "w") as f:
        f.write (outputstring)


def main():
    pb = PBProto("PlayerDBMsg.proto")
    pb.parse()

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print e
    # os.system("pause")
