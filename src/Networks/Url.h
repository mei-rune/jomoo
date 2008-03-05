

#ifndef JOMOO_URL_H
#define JOMOO_URL_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_Networks.h"
# include "base/exception.HPP"
# include "base/stringOps.H"

class JOMOO_Url_Base
{
public:
	virtual ~JOMOO_Url_Base(){}
	//JOMOO_Url( const tstring& url );
	virtual const tstring& protocol() const = 0;
	virtual const tstring& address() const = 0;
	virtual const tstring& entity() const = 0;
	virtual const tstring& url() const = 0;
	virtual const tstring& toString() const = 0;
};

class JOMOO_Url : public JOMOO_Url_Base
{
public:
	JOMOO_Url( const tstring& url );
	const tstring& protocol() const;
	const tstring& address() const;
	const tstring& entity() const;
	const tstring& url() const;
	const tstring& toString() const;
private:
	tstring url_;
	tstring protocol_;
	tstring address_;
	tstring entity_;
	tstring toString_;
};

#endif //JOMOO_URL_H