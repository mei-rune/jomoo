

#ifndef SYSTEM_POOL_H
#define SYSTEM_POOL_H

# include "jomoo/config.h"

# if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
# endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_Memory.H"
# include "pool.h"

_jomoo_memory_begin

class SystemPool : public pool
{
public:

	static SystemPool& get();

	void *malloc (size_t nbytes , const char* file=0, size_t line=-1 );

	void free (void *);

	void dump( tostream& Target ) const;

	const tstring& toString() const;

private:
	SystemPool();
	DECLARE_NO_COPY_CLASS( SystemPool );
	tstring toString_;
};

_jomoo_memory_end

#endif //SYSTEM_POOL_H
