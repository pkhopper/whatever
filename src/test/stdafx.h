#ifndef _TEST_STD_AFX_H_
#define _TEST_STD_AFX_H_


#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif

#ifndef BOOST_DISABLE_ABI_HEADERS
#define BOOST_DISABLE_ABI_HEADERS
#endif

#include <boost/config.hpp>

#if defined(BOOST_WINDOWS) && BOOST_WINDOWS

#    ifndef NOMINMAX
#		define NOMINMAX  // min,max conflicts with: #INCLUDE <windows.h>
#    endif

#    ifndef _WIN32_WINNT
#		define _WIN32_WINNT 0x0501
#    endif

#endif

#    ifndef min
#		undef min
#    endif

#    ifndef max
#		undef max
#    endif

#endif // EOF _TEST_STD_AFX_H_