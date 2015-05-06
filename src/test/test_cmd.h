#ifndef _TEST_TEST_COMMAND_H_
#define _TEST_TEST_COMMAND_H_

#include "stdafx.h"
#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
#include "time_interval.h"


namespace testtools
{


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