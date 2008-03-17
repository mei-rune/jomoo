

#ifndef SYSTEM_POOL_H
#define SYSTEM_POOL_H

# include "config.h"

# if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
# endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_Memory.H"
# include "Memory_Pool.h"

_memory_begin

class SystemPool : public  pool
{
public:

	static SystemPool& get();

	void *malloc (size_t nbytes , const char* file=0, size_t line=-1 );

	void free (void *);

	void dump( std::ostream& Target ) const;

	const tstring& toString() const;

private:
	SystemPool();
	DECLARE_NO_COPY_CLASS( SystemPool );
	tstring toString_;
};

_memory_end

#endif //SYSTEM_POOL_H
