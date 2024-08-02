#if !defined(VXMATHPS2_H)
#define VXMATHPS2_H


#include <sys/time.h>
#include <sys/param.h>

#ifndef PATH_MAX
#define PATH_MAX	256
#endif


#ifndef _MAX_PATH
#define _MAX_PATH PATH_MAX
#endif


#ifndef _MAX_DRIVE

#define _MAX_DRIVE 10
#endif

#ifndef _MAX_DIR

#define _MAX_DIR _MAX_PATH
#endif

#ifndef _MAX_EXT

#define _MAX_EXT 10
#endif

#ifndef _MAX_FNAME

#define _MAX_FNAME _MAX_PATH
#endif

#ifndef stricmp 
#define stricmp strcmpi
#endif

#ifndef strnicmp 
#define strnicmp strncmpi
#endif

#define OutputDebugString(x)  printf(x);


int strcmpi(const char *dst, const char *src);
int strncmpi(const char *dst, const char *src,size_t count);


#endif // VXMATHPS2_H
