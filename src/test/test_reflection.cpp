#include <vavava/ProtobufHelper.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vavava/ByteBuffer.h>
#include <vavava/TimeInterval.h>
#include <vavava/util.h>
#include "test_dump/proto/cpp/mytype.pb.h"


int test_pb_reflection(int argc, char* argv[], bool& running)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    std::stringstream ss;
    vavava::TimeInterval t;

    MyTypeArray pb;

    vavava::ProtobufHelper().fill(pb);
    std::cout << pb.DebugString();

    google::protobuf::ShutdownProtobufLibrary();
    std::cout << ss.str() << std::endl;
    return 0;
}
