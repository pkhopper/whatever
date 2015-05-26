#ifndef _TEST_TEST_COMMAND_H_
#define _TEST_TEST_COMMAND_H_

#include "stdafx.h"
#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
#include "time_interval.h"


namespace testtools
{

    template<typename _T,unsigned int _Count>
    class StaticCircularQueue
    {
    public:
        StaticCircularQueue()
        {
            clear();
        }

        void clear()
        {
            _f = 0; 
            _r = 0;
            memset(_list, 0, (_Count+1)*sizeof(_T));
        }

        void push(_T &data)
        {
            *(_list + _r) = data;
            _r = (_r + 1) % (_Count + 1);
            if (_r == _f)
            {
                _f = (_f + 1) % (_Count + 1);
            }
        }

        _T pop()
        {
            _T *ptr = _list + _f;
            _f = (_f + 1) % (_Count + 1);
            return *ptr;
        }

        const int count() const
        {
            if (_r >= _f)
            {
                return _r - _f;
            }
            else
            {
                return _Count + 1 - (_f - _r);
            }
        }

        const _T *get(int index) const
        {
            if (count() > index)
            {
                return _list + (_f + index) % (_Count + 1);
            }
            return NULL;
        }

        const unsigned int capacity()
        {
            return _Count;
        }
    protected:
        int _f;
        int _r;
        _T  _list[_Count + 1];
    };

    class TestCommandBase
    {
    public:

        bool Loads(std::string &txt)
        {
            _full_cmd = txt;
            int pos = txt.find('(');
            if (pos > 0)
            {
                _name = txt.substr(0, pos);
                boost::split(this->_params, txt.substr(pos+1, txt.length()-pos-2), boost::is_any_of(","));
            }
            else
            {
                this->_name = txt;
            }
            return true;
        }

        std::string                _full_cmd;
        std::string                _name;
        std::vector<std::string>   _params;
        TimeInterval               _time_interval;
    };


    template<typename T>
    class TestCommand : public TestCommandBase
    {
    public:

    protected:

    };




















}









#endif