// ------------------------------
#ifndef _jingxian_export_h
#define _jingxian_export_h


#if defined (jingxian_has_dll) && (jingxian_has_dll == 1)
#  if defined (jingxian_build_dll)
#    define jingxian_export  __declspec (dllexport)
#    define jingxian_export_c extern "C"  __declspec (dllexport)
#  else /* jingxian_has_dll */
#    define jingxian_export  __declspec (dllimport)
#    define jingxian_export_c extern "C"  __declspec (dllimport)
#  endif /* jingxian_has_dll */
#else /* jingxian_has_dll == 1 */
#  define jingxian_export		
#  define jingxian_export_c	
#endif /* jingxian_has_dll == 1 */

#endif /* _jingxian_export_h */
