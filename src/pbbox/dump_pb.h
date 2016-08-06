
#ifndef _VAVAVA_PROTOBUF_DUMP_H__
#define _VAVAVA_PROTOBUF_DUMP_H__


#include <cstdint>
#include <string>
#include <google/protobuf/message.h>
#include "ByteBuffer.h"
#include "boost/smart_ptr/shared_ptr.hpp"


namespace vavava
{
    namespace dump
    {

        int dump_encode(ByteBuffer&, ::google::protobuf::Message*);
        int dump_encode(const std::string&, ::google::protobuf::Message*);

        typedef boost::shared_ptr<google::protobuf::Message> MessagePtr;
        MessagePtr dump_decode(const ByteBuffer&);
        MessagePtr dump_decode(const std::string&);

    }
}

#endif
