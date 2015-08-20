#ifndef _TEST_TEST_COMMAND_H_
#define _TEST_TEST_COMMAND_H_

#include "stdafx.h"
#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
#include "time_interval.h"


namespace testtools
{

    template<typename _T,unsigned int _Count,bool _OverWrite=false>
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
            memset(_list, 0, (_Count)*sizeof(_T));
        }

        _T *push(_T &data)
        {
            if (!_OverWrite && _r + 1 == _f)
            {
                return NULL;
            }
            auto ptr = _list + _r;
            _r = (_r + 1) % (_Count);
            if (_r == _f)
            {
                _f = (_f + 1) % (_Count);
            }
            *ptr = data;
            return ptr;
        }

        _T *pop()
        {
            if(count() == 0)
            {
                return NULL;
            }
            auto ptr = _list + _f;
            _f = (_f + 1) % (_Count);
            return ptr;
        }

        const int count() const
        {
            //if (_f == -1)
            //{
            //    return 0;
            //}
            if (_r >= _f)
            {
                return _r - _f;
            }
            else
            {
                return _Count - (_f - _r);
            }
        }

        const _T *get(int index) const
        {
            if (count() > index)
            {
                return _list + (_f + index) % (_Count);
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
        _T  _list[_Count];
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