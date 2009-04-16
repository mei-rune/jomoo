
# include "pro_config.h"
# include "command_queue.h"

_jingxian_begin

void command_queue::release( ICommand* cmd )
{
	delete cmd;
}

_jingxian_end