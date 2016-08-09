#include "DumpFile.h"
#include "dump_pb.h"


using namespace vavava;
using namespace dump;

const uint8_t SYN_CODE = 0x11;

google::protobuf::Message* create_message(const std::string& typeName)
{
    google::protobuf::Message* message = NULL;
    const google::protobuf::Descriptor* descriptor =
        google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(typeName);
    if (descriptor)
    {
        const google::protobuf::Message* prototype =
            google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
        if (prototype)
        {
            message = prototype->New();
        }
    }
    return message;
}

int vavava::dump::dump_encode(ByteBuffer& buffer, ::google::protobuf::Message* pMessage)
{
    // uint8_t  syn
    // uint8_t  name_len
    // char     name[name_len+1]
    // uint32_t size_of_pb_bin
    // binary_data
    assert(pMessage);
    assert(pMessage->IsInitialized());
    std::string typeName = pMessage->GetTypeName();
    //std::string typeName = "MyTypeArray";
    buffer.reset();
    buffer.append8(SYN_CODE);
    buffer.append8(typeName.length() + 1);
    buffer.append(typeName.c_str(), typeName.length());
    buffer.append8('\0');
    auto total_len_ptr = reinterpret_cast<uint32_t*>(buffer.write_ptr());
    buffer.append32(0);
    if (pMessage->SerializeToArray(buffer.write_ptr(), buffer.writeable()))
    {
        *total_len_ptr = pMessage->ByteSize();
        buffer.has_written(*total_len_ptr);
        return true;
    }
    return false;
}

message_shared_ptr_t vavava::dump::dump_decode(const ByteBuffer& buffer)
{
    message_shared_ptr_t data;
    uint32_t offset = 0;
    assert(buffer.peek8(offset) == SYN_CODE);
    if (buffer.peek8(offset++) == SYN_CODE)
    {
        int name_len = buffer.peek8(offset++);
        std::string typeName = buffer.begin() + offset;
        assert(name_len == typeName.length() + 1);
        offset += typeName.length() + 1;
        data.reset(create_message(typeName));
        if (data)
        {
            auto len = buffer.peek32(offset);
            offset += 4;
            auto pProtoBuf = buffer.begin() + offset;
            if (data->ParseFromArray(pProtoBuf, len))
            {
                return data;
            }
        }        
    }
    return data;
}

int vavava::dump::dump_encode(const std::string& fullpath, ::google::protobuf::Message* ptr)
{
    assert(ptr);
    if (ptr)
    {
        ByteBuffer buffer;
        vavava::dump::DumpFile pbfile;
        pbfile.open(fullpath);
        if (pbfile.is_open())
        {
            if (dump_encode(buffer, ptr))
            {
                return pbfile.writeall(buffer.begin(), buffer.readable());
            }
        }
    }
    return -1;
}

message_shared_ptr_t vavava::dump::dump_decode(const std::string& fullpath)
{
    ByteBuffer buffer;
    vavava::dump::DumpFile pbfile;
    pbfile.open(fullpath);
    if (pbfile.is_open())
    {
        int size = buffer.capacity();
        if (pbfile.readall(buffer.write_ptr(), &size))
        {
            buffer.has_written(size);
            return dump_decode(buffer);
        }
    }
    return message_shared_ptr_t();
}

int check(const std::string& fullpath)
{
    return 0;
}

std::string debug_string(std::string tag)
{
    return 0;
}

