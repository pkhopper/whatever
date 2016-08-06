
#ifndef _VAVAVA_DUMP_BYTE_STREAM_H__
#define _VAVAVA_DUMP_BYTE_STREAM_H__


#include <assert.h>
#include <cstdint>
#include <string>
#include <vector>


namespace vavava
{
    namespace dump
    {

        class ByteBuffer
        {
            const static int DEFAULT_CAPACITY = 1024 * 1024;
        public:
            explicit ByteBuffer(int size=DEFAULT_CAPACITY): woffset_(0)
            {
                resize(size);
            }

            char* begin()
            { 
                return buffer_.data(); 
            }

            const char* begin() const
            { 
                return buffer_.data(); 
            }

            char* write_ptr()
            {
                return begin() + woffset_;
            }

            std::size_t capacity() const
            {
                return buffer_.capacity();
            }

            std::size_t readable() const
            {
                return woffset_;
            }

            std::size_t writeable() const
            {
                assert(capacity() -  woffset_ >= 0);
                return capacity() -  woffset_;
            }

            bool make_writeable_space(std::size_t len)
            {
                if (writeable() < len)
                {
                    return resize(woffset_ + len + 1);
                }
                return true;
            }

            bool ensure_writable(std::size_t len)
            {
                if (len <= writeable())
                {
                    return true;
                }
                return make_writeable_space(len);
            }

            void has_written(std::size_t len)
            {
                assert(len <= writeable());
                woffset_ += len;
            }

            void append(const char* ptr, uint32_t len)
            {
                if (ensure_writable(len))
                {
                    memcpy(write_ptr(), ptr, len);
                    has_written(len);
                }
            }

            template<typename T>
            void append(const T data)
            {
                append(reinterpret_cast<const char*>(&data), sizeof(data));
            }

            void append8(uint8_t data)
            {
                append(data);
            }

            void append16(uint16_t data)
            {
                append(data);
            }

            void append32(uint32_t data)
            {
                append(data);
            }

            void append64(uint8_t data)
            {
                append(data);
            }

            void peek(uint32_t offset, uint32_t size, void* out) const
            {
                assert(out);
                assert(offset + size <= readable());
                if (offset + size <= readable())
                {
                    memcpy(out, begin() + offset, size);
                }
            }

            template<typename T>
            const T& peek(uint32_t offset) const
            {
                return *reinterpret_cast<const T*>(begin() + offset);
            }

            const uint8_t& peek8(uint32_t offset) const
            {
                return peek<uint8_t>(offset);
            }

            const uint16_t& peek16(uint32_t offset) const
            {
                return peek<uint16_t>(offset);
            }

            const uint32_t& peek32(uint32_t offset) const
            {
                return peek<uint32_t>(offset);
            }

            const long long& peek64(uint32_t offset) const
            {
                return peek<long long>(offset);
            }

            void reset(uint32_t maxlen = 0)
            {
                woffset_ = 0;
                buffer_.clear();
                if (maxlen > 0)
                {
                    buffer_.reserve(maxlen);
                }
            }

            bool resize(uint32_t size)
            {
                if (size < woffset_)
                {
                    woffset_ = size;
                }
                buffer_.resize(size);
                return true;
            }
            
            static void test(ByteBuffer& buffer);

        protected:
            std::vector<char> buffer_;
            uint32_t woffset_;
        };

    } // dump
} // vavava

#endif
