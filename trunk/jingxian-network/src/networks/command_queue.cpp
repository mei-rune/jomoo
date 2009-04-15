
# include "pro_config.h"
# include "command_queue.h"

_jingxian_begin

void command_queue::release( command* cmd )
{
	delete cmd;
}

_jingxian_end