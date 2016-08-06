#include <fstream>
#include <iostream>
#include <string>
#include "messages/mytype.pb.h"
#include "dump_pb.h"


int main(int argc, char* argv[])
{
    MyType1 data;
    data.set_id(123);
    data.set_longid(1234);
    data.set_strmessage("pascal4");
    vavava::dump::ByteBuffer buffer;
    vavava::dump::dump_encode(buffer, &data);
    auto ptr = vavava::dump::dump_decode(buffer);
    std::cout << ptr->GetTypeName() << std::endl << ptr->DebugString();
	return 0;
}

