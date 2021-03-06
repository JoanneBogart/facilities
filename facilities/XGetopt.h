/// Found on the web http://www.codeproject.com/cpp/xgetopt.asp
/// Provides a windows version of getopt
/// Introduced into facilities by Heather Kelly heather625@gmail.com

// XGetopt.h  Version 1.2
//
// Author:  Hans Dietrich
//          hdietrich2@hotmail.com
//
// This software is released into the public domain.
// You are free to use it in any way you like.
//
// This software is provided "as is" with no expressed
// or implied warranty.  I accept no liability for any
// damage or loss of business that this software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef XGETOPT_H
#define XGETOPT_H

#ifdef WIN32
#include <tchar.h>
extern int optind, opterr;
extern TCHAR *optarg;

namespace facilities {
    int getopt(int argc, TCHAR *argv[], TCHAR *optstring);

} // end namespace

#endif

#endif //XGETOPT_H
