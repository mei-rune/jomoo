

#ifndef _Config_FileTransfer_H
#define _Config_FileTransfer_H


#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "BOE/Logger.H"
#include "../im.h"
#define _filetransfer_begin
#define _filetransfer_end
#define _filetransfer

#ifndef IMLoggerPtr
#define IMLoggerPtr BOE_Log_Impl*
#endif 


_filetransfer_begin

_filetransfer_end

#endif // _Config_FileTransfer_H