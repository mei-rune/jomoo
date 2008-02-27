

#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_IM.h"
#include "MsgConnection.H"
#include <map>

_im_begin

#define  ConnectionManager_ST_1 typename T 
#define  ConnectionManager_ST_2 T 

template< ConnectionManager_ST_1 >
class ConnectionManager
{
public:
	typedef T connection_type;
	typedef typename connection_type::connection_ptr connection_ptr;
	typedef std::map< tstring , connection_ptr > container_type;

	typedef typename container_type::iterator iterator;

	ConnectionManager(void);
	~ConnectionManager(void);

	connection_ptr find( const tstring& addr );
	bool add( const tstring& addr , connection_ptr connection );
	bool remove( const tstring& addr );
	bool remove( const tstring& addr , connection_ptr& connection );
	void clear();

	iterator begin( );
	iterator end( );

	const tstring& toString() const;

private:
	container_type connections_;

	tstring toString_;
};

_im_end

#include "ConnectionManager.Templ"

#endif // CONNECTIONMANAGER_H