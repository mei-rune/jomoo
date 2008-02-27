
#ifndef Message_H
#define Message_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_IM.h"
#include "dataHeader.H"
#include "BOE/IO/IO.H"

_im_begin

class Data_Block
{
public:
	typedef counter_ptr< Data_Block > ptr_type;

	virtual ~Data_Block(){}
	virtual const char* rd_ptr( ) const = 0;
	virtual size_t length( ) const = 0;
};

typedef Data_Block::ptr_type Data_Block_Ptr;

class Data_Buffer : public Data_Block
{
public:
	typedef counter_ptr< Data_Buffer > ptr_type;

	virtual ~Data_Buffer(){}

	virtual void rd_ptr( size_t t ) = 0;

	virtual char* wd_ptr() = 0;
	virtual void wd_ptr( size_t t ) = 0;
	virtual size_t space( ) const = 0;
};

typedef Data_Buffer::ptr_type Data_Buffer_Ptr;

class File_Block
{
public:
	typedef counter_ptr< File_Block > ptr_type;
	virtual ~File_Block( ) = 0;
	virtual iopack* getPacket() = 0;
};

typedef File_Block::ptr_type File_Block_Ptr;


class Data_Buffer_Factory
{
public:
	typedef counter_ptr< Data_Buffer_Factory > ptr_type;
	virtual ~Data_Buffer_Factory(){}
	virtual Data_Block_Ptr createBlock( ) = 0;
	virtual Data_Block_Ptr createBlock( Data_Block_Ptr, size_t begin ) = 0;
	virtual Data_Block_Ptr createBlock( Data_Block_Ptr, size_t begin ,size_t end ) = 0;
	virtual Data_Buffer_Ptr createBuffer( ) = 0;
	virtual File_Block_Ptr createFilePacket( ) = 0;
};


class MessageI
{
public:

	class Visitor
	{
	public:
		virtual ~Visitor() {}
		virtual void accept( MessageI& ) = 0;
	};

	virtual ~MessageI() {}
	virtual const MessageHeader& getMessageHeader() const = 0;
	virtual void setMessageHeader( const MessageHeader& ) = 0;

	virtual bool startEncapsulation( const tstring& name , 
		const std::vector< tstring >& spec = std::vector< tstring >() ) = 0;
	virtual bool endEncapsulation( ) = 0;

	virtual bool read( void* blob, size_t t ) = 0;
	virtual bool read( DataHeader& ) = 0;
	virtual bool read( MessageHeader& ) = 0;
	virtual bool read( Data_Block_Ptr& ptr ) = 0;

	virtual bool write( const void* blob, size_t t ) = 0;
	virtual bool write( const MessageHeader& ) = 0;
	virtual bool write( const DataHeader& ) = 0;
	virtual bool write( Data_Block_Ptr& ptr ) = 0;

	virtual bool read( File_Block_Ptr& ptr ) = 0;
	virtual bool write( File_Block_Ptr& ptr ) = 0;
//
//
//protected:

	virtual void visit( Visitor& v ) = 0;
};

typedef counter_ptr< MessageI > MessageI_Ptr;


class BOE_Message
{
public:

	class Begin
	{
	public:
		Begin( const tstring& name , 
		const std::vector< tstring >& spec = std::vector< tstring >() )
		: name_( name )
		, spec_( spec )
		{
		}

		const tstring& name_;
		const std::vector< tstring >& spec_;
	};

	class End
	{
	public:
	};

	BOE_Message( MessageI_Ptr message )
		: message_( message )
	{
	}

	BOE_Message( MessageI* message )
		: message_( message )
	{
	}

	bool startEncapsulation( const tstring& name , 
		const std::vector< tstring >& spec = std::vector< tstring >() )
	{
		return message_->startEncapsulation( name , spec );
	}

	bool endEncapsulation( )
	{
		return message_->endEncapsulation();
	}

	const MessageHeader& getMessageHeader() const
	{
		return message_->getMessageHeader();
	}

	void setMessageHeader( const MessageHeader& header )
	{
		return message_->setMessageHeader( header );
	}

	bool read( void* blob, size_t l )
	{
		return message_->read( blob, l );
	}

	bool read( DataHeader& header )
	{
		return message_->read( header );
	}

	bool read( MessageHeader& header )
	{
		return message_->read( header );
	}

	bool read( Data_Block_Ptr& ptr )
	{
		return message_->read( ptr );
	}


	bool write( const void* blob, size_t l )
	{
		return message_->write( blob, l );
	}

	bool write( const MessageHeader& header )
	{
		return message_->write( header );
	}

	bool write( const DataHeader& header )
	{
		return message_->write( header );
	}

	bool write( Data_Block_Ptr& ptr )
	{
		return message_->write( ptr );
	}
	
	bool read( File_Block_Ptr& ptr )
	{
		return message_->read( ptr );
	}

	bool write( File_Block_Ptr& ptr )
	{
		return message_->write( ptr );
	}

	void visit( MessageI::Visitor& v )
	{
		message_->visit( v );
	}
private:

	MessageI_Ptr message_;
};


inline BOE_Message& operator<<( BOE_Message& stream, const BOE_Message::Begin&  v )
{
	stream.startEncapsulation( v.name_,v.spec_ );
	return stream;
}
inline BOE_Message& operator<<( BOE_Message& stream, const BOE_Message::End&  v )
{
	stream.endEncapsulation( );
	return stream;
}

inline BOE_Message& operator<<( BOE_Message& stream, int8_t v )
{
	stream.write( &v, sizeof( int8_t ) );
	return stream;
}
inline BOE_Message& operator>>( BOE_Message& stream, int8_t& v )
{
	stream.read( &v, sizeof( int8_t ) );
	return stream;
}
inline BOE_Message& operator<<( BOE_Message& stream, int16_t v )
{
	stream.write( &v, sizeof( int16_t ) );
	return stream;
}
inline BOE_Message& operator>>( BOE_Message& stream, int16_t& v )
{
	stream.read( &v, sizeof( int16_t ) );
	return stream;
}
inline BOE_Message& operator<<( BOE_Message& stream, int32_t v )
{
	stream.write( &v, sizeof( int32_t ) );
	return stream;
}
inline BOE_Message& operator>>( BOE_Message& stream, int32_t& v )
{
	stream.read( &v, sizeof( int32_t ) );
	return stream;
}
inline BOE_Message& operator<<( BOE_Message& stream, int64_t v )
{
	stream.write( &v, sizeof( int64_t ) );
	return stream;
}
inline BOE_Message& operator>>( BOE_Message& stream, int64_t& v )
{
	stream.read( &v, sizeof( int64_t ) );
	return stream;
}

inline BOE_Message& operator<<( BOE_Message& stream, u_int8_t v )
{
	stream.write( &v, sizeof( u_int8_t ) );
	return stream;
}
inline BOE_Message& operator>>( BOE_Message& stream, u_int8_t& v )
{
	stream.read( &v, sizeof( u_int8_t ) );
	return stream;
}
inline BOE_Message& operator<<( BOE_Message& stream, u_int16_t v )
{
	stream.write( &v, sizeof( u_int16_t ) );
	return stream;
}
inline BOE_Message& operator>>( BOE_Message& stream, u_int16_t& v )
{
	stream.read( &v, sizeof( u_int16_t ) );
	return stream;
}
inline BOE_Message& operator<<( BOE_Message& stream, u_int32_t v )
{
	stream.write( &v, sizeof( u_int32_t ) );
	return stream;
}
inline BOE_Message& operator>>( BOE_Message& stream, u_int32_t& v )
{
	stream.read( &v, sizeof( u_int32_t ) );
	return stream;
}

inline BOE_Message& operator<<( BOE_Message& stream, u_int64_t v )
{
	stream.write( &v, sizeof( u_int64_t ) );
	return stream;
}

inline BOE_Message& operator>>( BOE_Message& stream, u_int64_t& v )
{
	stream.read( &v, sizeof( u_int64_t ) );
	return stream;
}

inline BOE_Message& operator<<( BOE_Message& stream, File_Block_Ptr v )
{
	stream.write( v );
	return stream;
}

inline BOE_Message& operator>>( BOE_Message& stream, File_Block_Ptr& v )
{
	stream.read( v );
	return stream;
}

_im_end

#endif // Message_H

