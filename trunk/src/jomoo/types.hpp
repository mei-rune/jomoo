#ifndef __type__h__
# define __type__h__

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files

_jomoo_begin

enum jomoo_type
{
	boolean_type
	int8_type,
	int16_type,
	int32_type,
	int64_type,
	string_type,
	object_type,
	sequence_type,
	dictionary_type
};

_jomoo_end

#endif // __type__h__