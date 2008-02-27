
// -*- C++ -*-
// Service_Config_DLL_Export.h,v 4.1 2001/07/30 06:21:41 othman Exp
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl
// ------------------------------
#ifndef _Hazel_CONFIG_DLL_EXPORT_H
#define _Hazel_CONFIG_DLL_EXPORT_H





//#include "ace/config-all.h"

#if !defined (SERVICE_CONFIG_DLL_HAS_DLL)
#  define SERVICE_CONFIG_DLL_HAS_DLL 1
#endif /* ! TEST_HAS_DLL */

#define SERVICE_CONFIG_DLL_BUILD_DLL

#if defined (SERVICE_CONFIG_DLL_HAS_DLL) && (SERVICE_CONFIG_DLL_HAS_DLL == 1)
#  if defined (SERVICE_CONFIG_DLL_BUILD_DLL)
#    define BT_Export  __declspec (dllexport)
#    define BT_Export_C extern "C"  __declspec (dllexport)
#    define Hazel_Export  __declspec (dllexport)
#    define Hazel_Export_C extern "C"  __declspec (dllexport)
#    define  BT_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define  BT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* SERVICE_CONFIG_DLL_BUILD_DLL */
#    define BT_Export  __declspec (dllimport)
#    define BT_Export_C extern "C"  __declspec (dllimport)
#    define Hazel_Export  __declspec (dllimport)
#    define Hazel_Export_C extern "C"  __declspec (dllimport)
#    define  BT_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define  BT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* SERVICE_CONFIG_DLL_BUILD_DLL */
#else /* SERVICE_CONFIG_DLL_HAS_DLL == 1 */
#  define BT_Export
#  define BT_Export_C
#  define Hazel_Export
#  define Hazel_Export_C
#  define  BT_SINGLETON_DECLARATION(T)
#  define  BT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* SERVICE_CONFIG_DLL_HAS_DLL == 1 */

#endif /* _BTNM_CONFIG_DLL_EXPORT_H */

// End of auto generated file.
