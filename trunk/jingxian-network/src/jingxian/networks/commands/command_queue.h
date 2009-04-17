

#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
#include "jingxian/networks/commands/ICommand.h"

_jingxian_begin

class command_queue
{
public:

	static void release( ICommand* cmd );
};

_jingxian_end

#endif // COMMAND_QUEUE_H
