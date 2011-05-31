#ifndef dwg2ansysLibExportH
#define dwg2ansysLibExportH 1

#ifdef WIN32
# if defined(dwg2ansysLib_EXPORTS)
#  define dwg2ansysLib_EXPORT __declspec( dllexport ) 
# else
#  define dwg2ansysLib_EXPORT __declspec( dllimport ) 
# endif
#else
# define dwg2ansysLib_EXPORT
#endif

#endif
