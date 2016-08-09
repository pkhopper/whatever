
#ifndef _VAVAVA_DUMP_FILE_H__
#define _VAVAVA_DUMP_FILE_H__


#include <assert.h>
#include <cstdint>
#include <string>
#include <vector>
#include <xutility>


namespace vavava
{
    namespace dump
    {

        class DumpFile
        {
        public:
            DumpFile();
            ~DumpFile();
            bool open(const std::string& filename, const std::string& flag="ae");
            int writeall(const char* ptr, int len);
            int readall(char* ptr, int* pSize);
            void flush();
            int close();
            bool is_open();
            std::string& name();
        protected:
            std::string  name_;
            FILE  *fp_;
        };

    }
}

#endif
