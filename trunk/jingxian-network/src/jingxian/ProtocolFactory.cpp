
# include "pro_config.h"
#include "ProtocolFactory.h"

_jingxian_begin

void ProtocolFactory::release( protocol* pr )
{
	delete pr;
}

_jingxian_end