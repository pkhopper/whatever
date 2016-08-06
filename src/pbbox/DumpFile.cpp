#include <io.h>
#include "DumpFile.h"


using namespace vavava;
using namespace dump;


DumpFile::DumpFile() : fp_(NULL)
{

}

DumpFile::~DumpFile()
{
    close();
}

bool DumpFile::open(const std::string& filename, const std::string& flag)
{
    if (!is_open())
    {
        name_ = filename;
        fp_ = ::fopen(name().c_str(), flag.c_str());
        if (fp_)
        {
            return true;
        }
    }
    return false;
}

bool DumpFile::is_open()
{
    return fp_ >= 0;
}

int DumpFile::readall(char* ptr, int* pSize)
{
    int err = -1;
    if (pSize)
    {
        return -1;
    }
    if (is_open())
    {
        int n = ::fread(ptr, *pSize, 1, fp_);
        if (n >= 0)
        {
            if (pSize)
            {
                *pSize = n;
            }
        }
        else
        {
            err = errno;
        }
    }
    return err;
}

int DumpFile::writeall(const char* ptr, int len)
{
    if (!fp_)
    {
        return -1;
    }
    size_t n = fwrite(ptr, len, 1, fp_);
    size_t remain = len - n;
    while (remain > 0)
    {
        size_t x = fwrite(ptr + n, remain, 1, fp_);
        if (x == 0)
        {
            return ferror(fp_);
        }
        n += x;
        remain = len - n; // remain -= x
    }
    return len;
}

void DumpFile::flush()
{
    if (fp_)
    {
        ::fflush(fp_);
    }
}

int DumpFile::close()
{
    int ret = -1;
    if (fp_)
    {
        ret = fclose(fp_);
        fp_ = NULL;
    }
    return ret;
}

std::string& DumpFile::name()
{
    return name_;
}
