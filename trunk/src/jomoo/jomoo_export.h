// ------------------------------
#ifndef _JOMOO_EXPORT_H
#define _JOMOO_EXPORT_H


#if defined (JOMOO_HAS_DLL) && (JOMOO_HAS_DLL == 1)
#  if defined (JOMOO_BUILD_DLL)
#    define JOMOO_Export  __declspec (dllexport)
#    define JOMOO_Export_C extern "C"  __declspec (dllexport)
#  else /* JOMOO_HAS_DLL */
#    define JOMOO_Export  __declspec (dllimport)
#    define JOMOO_Export_C extern "C"  __declspec (dllimport)
#  endif /* JOMOO_HAS_DLL */
#else /* JOMOO_HAS_DLL == 1 */
#  define JOMOO_Export
#  define JOMOO_Export_C
#endif /* JOMOO_HAS_DLL == 1 */

#endif /* _JOMOO_EXPORT_H */
