#ifndef _VAVAVA_UTILITIES_PROTOBUF_HELPER_H__
#define _VAVAVA_UTILITIES_PROTOBUF_HELPER_H__

#include "ignore_warnings.h"
#include <stdio.h>
#include <string>
#include <cstdint>
#include <climits>
#include <google/protobuf/message.h>
#include "util.h"
#include "Random.h"


namespace vavava {


struct ProtobufHelper_Config
{
    int repeated_count_max;
    int int_min;
    int int_max;
    float float_min;
    float float_max;
    int msg_count;

    ProtobufHelper_Config()
    {
        repeated_count_max = 1000;
        int_min = INT_MIN;
        int_max = INT_MAX;
        float_min = 0.0f;
        float_max = 999999999.99f;
    }

    int32_t random_int32()
    {
        return vavava::random::Random::Inst().rand_int<int32_t>(int_min, int_max);
    }
    uint32_t random_uint32()
    {
        return vavava::random::Random::Inst().rand_int<uint32_t>(0, int_max);
    }
    int64_t random_int64()
    {
        return vavava::random::Random::Inst().rand_int<int64_t>(int_min, int_max);
    }
    uint64_t random_uint64()
    {
        return vavava::random::Random::Inst().rand_int<uint64_t>(0, int_max);
    }
    float random_float()
    {
        return vavava::random::Random::Inst().rand_double(float_min, float_max);
    }
    double random_double()
    {
        return random_float();
    }
    bool random_bool()
    {
        return vavava::random::Random::Inst().rand_int<int>(0, 1) == 0;
    }
    std::string random_string()
    {
        char buf[1024];
        memset(buf, 0, 1024);
        sprintf_s(buf, "str_%d", random_uint32());
        return "this-is-a-string-field";
    }
    int ramdom_repeated_count()
    {
        return vavava::random::Random::Inst().rand_int<int32_t>(1, repeated_count_max);
    }
};

class ProtobufHelper
{
public:
    ProtobufHelper_Config& cfg()
    {
        return cfg_;
    }

    void fill(google::protobuf::Message& msg)
    {
        const google::protobuf::Descriptor* descriptor = msg.GetDescriptor();
        const google::protobuf::Reflection* reflection = msg.GetReflection();
        int field_count = descriptor->field_count();
        for (int field_index=0; field_index < field_count; ++field_index)
        {
            const google::protobuf::FieldDescriptor* field = descriptor->field(field_index);

            switch (field->cpp_type()) 
            {
            case google::protobuf::FieldDescriptor::CPPTYPE_INT32    :    // TYPE_INT32, TYPE_SINT32, TYPE_SFIXED32
                {
                    if (field->is_repeated())
                    {
                        for (int i=0; i < cfg().ramdom_repeated_count(); ++i)
                        {
                            reflection->AddInt32(&msg, field, cfg().random_int32());
                        }
                    }
                    else
                    {
                        reflection->SetInt32(&msg, field, cfg().random_int32());
                    }
                    break;
                }   
            case google::protobuf::FieldDescriptor::CPPTYPE_INT64    :    // TYPE_INT64, TYPE_SINT64, TYPE_SFIXED64
                {
                    if (field->is_repeated())
                    {
                        for (int i=0; i < cfg().ramdom_repeated_count(); ++i)
                        {
                            reflection->AddInt64(&msg, field, cfg().random_int64());
                        }
                    }
                    else
                    {
                        reflection->SetInt64(&msg, field, cfg().random_int64());
                    }
                    break;
                }   
            case google::protobuf::FieldDescriptor::CPPTYPE_UINT32   :    // TYPE_UINT32, TYPE_FIXED32
                {
                    if (field->is_repeated())
                    {
                        for (int i=0; i < cfg().ramdom_repeated_count(); ++i)
                        {
                            reflection->AddUInt32(&msg, field, cfg().random_uint32());
                        }
                    }
                    else
                    {
                        reflection->SetUInt32(&msg, field, cfg().random_uint32());
                    }
                    break;
                }   
            case google::protobuf::FieldDescriptor::CPPTYPE_UINT64   :    // TYPE_UINT64, TYPE_FIXED64
                {
                    if (field->is_repeated())
                    {
                        for (int i=0; i < cfg().ramdom_repeated_count(); ++i)
                        {
                            reflection->AddUInt64(&msg, field, cfg().random_uint64());
                        }
                    }
                    else
                    {
                        reflection->SetUInt64(&msg, field, cfg().random_uint64());
                    }
                    break;
                }   
            case google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE   :    // TYPE_DOUBLE
                {
                    if (field->is_repeated())
                    {
                        for (int i=0; i < cfg().ramdom_repeated_count(); ++i)
                        {
                            reflection->AddDouble(&msg, field, cfg().random_double());
                        }
                    }
                    else
                    {
                        reflection->SetDouble(&msg, field, cfg().random_double());
                    }
                    break;
                }   
            case google::protobuf::FieldDescriptor::CPPTYPE_FLOAT    :    // TYPE_FLOAT
                {
                    if (field->is_repeated())
                    {
                        for (int i=0; i < cfg().ramdom_repeated_count(); ++i)
                        {
                            reflection->AddFloat(&msg, field, cfg().random_float());
                        }
                    }
                    else
                    {
                        reflection->SetFloat(&msg, field, cfg().random_float());
                    }
                    break;
                }   
            case google::protobuf::FieldDescriptor::CPPTYPE_BOOL     :    // TYPE_BOOL
                {
                    if (field->is_repeated())
                    {
                        for (int i=0; i < cfg().ramdom_repeated_count(); ++i)
                        {
                            reflection->AddBool(&msg, field, cfg().random_bool());
                        }
                    }
                    else
                    {
                        reflection->SetBool(&msg, field, cfg().random_bool());
                    }
                    break;
                }   
            case google::protobuf::FieldDescriptor::CPPTYPE_ENUM     :    // TYPE_ENUM
                {
                    if (field->is_repeated())
                    {
                        for (int i=0; i < cfg().ramdom_repeated_count(); ++i)
                        {
                            auto enumDesc = reflection->GetEnum(msg, field);
                            reflection->AddEnum(&msg, field, enumDesc);
                        }
                    }
                    else
                    {
                        auto enumDesc = reflection->GetEnum(msg, field);
                        reflection->SetEnum(&msg, field, enumDesc);
                    }
                    break;
                }   
            case google::protobuf::FieldDescriptor::CPPTYPE_STRING   :    // TYPE_STRING, TYPE_BYTES
                {
                    if (field->is_repeated())
                    {
                        for (int i=0; i < cfg().ramdom_repeated_count(); ++i)
                        {
                            std::string tmp;
                            tmp = "this-is-a-string-field";
                            reflection->AddString(&msg, field, tmp);
                        }
                    }
                    else
                    {
                        std::string tmp;
                        tmp = "this-is-a-string-field";
                        reflection->SetString(&msg, field, tmp);
                    }
                    break;
                }   
            case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE  :    // TYPE_MESSAGE, TYPE_GROUP
                {
                    if (field->is_repeated())
                    {
                        for (int i=0; i < cfg().ramdom_repeated_count(); ++i)
                        {
                            auto subMsg = reflection->AddMessage(&msg, field);
                            fill(*subMsg);
                        }
                    }
                    else
                    {
                        auto subMsg = reflection->MutableMessage(&msg, field);
                        fill(*subMsg);
                    }
                    break;
                }   
            default:
                assert(0);
            }
        }
        return;
    }

protected:
    ProtobufHelper_Config cfg_;
};


} // vavava

#endif
