#include <fstream>
#include <iostream>
#include <string>
#include "messages/mytype.pb.h"


int main(int argc, char* argv[])
{
    MyTypeArray array;
    for (int i=0; i < 10; ++i)
    {
        char buf[128];
        auto ptr = array.add_t();
        ptr->set_id(i);
        ptr->set_longid(i);
        ptr->set_strmessage(itoa(i, buf, 128));
    }
    for (int i=0; i < 10; ++i)
    {
        char buf[128];
        auto ptr = array.add_t1();
        ptr->set_id(i);
        ptr->set_longid(i);
        ptr->set_strmessage(itoa(i, buf, 128));
    }
    for (int i=0; i < 10; ++i)
    {
        char buf[128];
        auto ptr = array.add_t3();
        ptr->set_id(i);
        ptr->set_longid(i);
        ptr->set_strmessage(itoa(i, buf, 128));
    }

    vavava::dump::ByteBuffer buffer;
    vavava::dump::dump_encode(buffer, &array);
    auto ptr = vavava::dump::dump_decode(buffer);
    std::cout << ptr->GetTypeName() << std::endl << ptr->DebugString();
	return 0;
}

