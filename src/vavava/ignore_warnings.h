
#ifndef _IGNORE_WARNINGS_H__
#define _IGNORE_WARNINGS_H__



#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif


#ifndef BOOST_DISABLE_ABI_HEADERS
#define BOOST_DISABLE_ABI_HEADERS
#endif


#if defined (BOOST_WINDOWS) && BOOST_WINDOWS

#ifndef NOMINMAX
#   define NOMINMAX    // ignore min, max defined in windows.h 
#endif
#ifndef _WIN32_WINNT
#   define _WIN32_WINNT 0x0501
#endif

#endif

#endif
