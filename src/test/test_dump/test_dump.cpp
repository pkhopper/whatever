#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "proto/cpp/mytype.pb.h"
#include <vavava/ByteBuffer.h>
#include "vavava/dump_pb.h"
#include "vavava/TimeInterval.h"
#include "proto/cpp/PlayerDBData.pb.h"

class dddddd
{
public:
    static dddddd& getinstance()
    {
        static dddddd inc;
        return inc;
    }

    MyTypeArray kkkkl;
    pnldb::pbmsg::PBCharacterFullData data;
};

int test_dump(int argc, char* argv[], bool& running)
{
    std::stringstream ss;
    vavava::TimeInterval t;
    MyTypeArray array;
    for (int i=0; i < 10; ++i)
    {
        char buf[128];
        auto ptr = array.add_t();
        ptr->set_id(i);
        ptr->set_longid(i);
        ptr->set_strmessage(_itoa(i, buf, 128));
    }
    for (int i=0; i < 10; ++i)
    {
        char buf[128];
        auto ptr = array.add_t1();
        ptr->set_id(i);
        ptr->set_longid(i);
        ptr->set_strmessage(_itoa(i, buf, 128));
    }
    for (int i=0; i < 10; ++i)
    {
        char buf[128];
        auto ptr = array.add_t3();
        ptr->set_id(i);
        ptr->set_longid(i);
        ptr->set_strmessage(_itoa(i, buf, 128));
    }

    vavava::ByteBuffer buffer;
    t.tick();
    vavava::dump::dump_encode(buffer, &array);
    t.tick();
    ss << "dump_encode=" << t.get_interval();
    t.tick();
    vavava::dump::dump_encode(buffer, &array);
    t.tick();
    ss << "dump_encode=" << t.get_interval();
    
    t.tick();
    auto ptr = vavava::dump::dump_decode(buffer);
    t.tick();
    ss << ", dump_decode=" << t.get_interval();
    
    t.tick();
    std::cout << ptr->GetTypeName() << std::endl << ptr->DebugString();
    t.tick();
    ss << ", print=" << t.get_interval();

    std::cout << ss.str() << std::endl;
    return 0;
}

int test_dump_performance(int argc, char* argv[], bool& running)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    auto kk = dddddd::getinstance();
    pnldb::pbmsg::PBCharacterFullData data;
    std::stringstream ss;
    vavava::TimeInterval t;
    std::string typeName = "pnldb::pbmsg::PBCharacterFullData";

    data.set_dirty(1);
    data.GetTypeName();

    for (int i=0; i < 10; ++i)
    {
        t.tick();
        vavava::ByteBuffer buffer;
        t.tick();
        ss << "buffer=" << t.get_interval() << std::endl;
        t.tick();
        vavava::dump::dump_encode(buffer, &data);
        t.tick();
        ss << "dump_decode=" << t.get_interval() << std::endl;

        t.tick();
        auto ptr = vavava::dump::dump_decode(buffer);
        t.tick();
        ss << "dump_decode=" << t.get_interval() << std::endl;
    }
    std::cout << ss.str() << std::endl;
    std::cout << data.DebugString() << std::endl;
    
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
