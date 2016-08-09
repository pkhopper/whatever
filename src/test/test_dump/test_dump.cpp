#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "proto/cpp/mytype.pb.h"
#include <vavava/ByteBuffer.h>
#include "vavava/dump_pb.h"
#include "vavava/TimeInterval.h"


int test_dump(int argc, char* argv[])
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

int test_dump_performance(int argc, char* argv[])
{
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
    vavava::dump::dump_encode(buffer, &array);   buffer.reset();
    return 0;
}
