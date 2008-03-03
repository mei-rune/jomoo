

#ifndef Hazel_URL_H
#define Hazel_URL_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Networks.h"
# include "Base/Exception.HPP"
#include "Base/stringOps.H"

class Hazel_Url_Base
{
public:
	virtual ~Hazel_Url_Base(){}
	//Hazel_Url( const tstring& url );
	virtual const tstring& protocol() const = 0;
	virtual const tstring& address() const = 0;
	virtual const tstring& entity() const = 0;
	virtual const tstring& url() const = 0;
	virtual const tstring& toString() const = 0;
};

class Hazel_Url : public Hazel_Url_Base
{
public:
	Hazel_Url( const tstring& url );
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

#endif //Hazel_URL_H