
#include "pro_config.h"
#include "jingxian/message_block.h"

_jingxian_begin

data_block::data_block( size_t len  )
: cur_size_( 0 )
, max_size_( len )
, base_( 0 )
, flags_( USER_FLAGS )
{

	base_ = static_cast<char*>(::calloc( len , sizeof(char) ) );
	if( base_ == 0 )
		throw std::runtime_error( "data_block ÄÚ´æ·ÖÅäÊ§°Ü" ); 
	memset( base_, 0 , max_size_ );
}

data_block::data_block( char* msg_data, size_t len , MessageFlags flag  )
: cur_size_( len )
, max_size_( len )
, base_( msg_data )
, flags_( flag )
{
}

data_block::~data_block()
{
	if( flags_ == USER_FLAGS && base_ != 0 )
	{
		free( base_ );
		base_ = NULL;
	}
}

char *data_block::base (void)
{
	return base_;
}

const char *data_block::base (void) const
{
	return base_;
}

char *data_block::end (void)
{
	return base_ + cur_size_;
}

const char *data_block::end (void) const
{
	return base_ + cur_size_;
}

size_t data_block::size (void) const
{
	return cur_size_;
}

int data_block::size (size_t length)
{
	if( length > max_size_ )
		return -1;
	cur_size_ = length ;
	return  0;
}

char* data_block::reset( size_t size )
{
	if( max_size_ >= size )
		return base_;
	char* new_buf =static_cast<char*>( calloc( size , sizeof(char) ) );
	if( new_buf == 0 )
		return 0;
	memcpy( new_buf, base_, cur_size_ );
	if( flags_ == USER_FLAGS && base_ != 0 )
			free( base_ );
	
	base_ = new_buf;
	max_size_ = size;
	return base_;
}

size_t data_block::capacity (void) const
{
	return max_size_;
}

message_block::message_block( size_t len  )
: data_block_( 0 )
, rd_size_( 0 )
, flags_( USER_FLAGS )
{
	data_block_ = new data_block( len );

	if( data_block_ == 0 )
		throw std::runtime_error( "message_block ÄÚ´æ·ÖÅäÊ§°Ü" ); 
}

message_block::message_block(  char* msg_data, size_t len , MessageFlags flag )
: data_block_( 0 )
, rd_size_( 0 )
, flags_( USER_FLAGS )
{
	data_block_ = new data_block( msg_data,len,flag );
	if( data_block_ == 0 )
		throw std::runtime_error( "message_block ÄÚ´æ·ÖÅäÊ§°Ü" );
}

message_block::message_block( data_block* data , MessageFlags flag )
: data_block_( data )
, rd_size_( 0 )
, flags_( flag )
{
}

message_block::~message_block( )
{
	if( flags_ == USER_FLAGS && data_block_ != 0 )
	{
		delete data_block_;
        data_block_ = NULL;
	}
}

char* message_block::reset( size_t size )
{
	return data_block_->reset( size );
}

const char* message_block::rd_ptr( size_t size )
{
	if( data_block_->size() < ( rd_size_ + size ) )
		return 0;
	rd_size_ += size;
	return data_block_->base() + rd_size_;
}

const char* message_block::rd_ptr() const
{
	return data_block_->base() + rd_size_;
}

size_t message_block::length() const
{
	return data_block_->size() - rd_size_;
}

char* message_block::wr_ptr()
{
	return data_block_->end();
}

char* message_block::wr_ptr( size_t size )
{
	if( data_block_->size( data_block_->size() + size ) >= 0 )
		return data_block_->end();
	return 0;
}

size_t message_block::space() const
{
	return data_block_->capacity() - data_block_->size();
}

size_t message_block::copy( const char* buf, size_t len )
{
	if( data_block_->base() == 0 )
		return ERR_BAD_BUF;
	if( space() < len )
		return ERR_BAD_BUF_LEN;
	memcpy( wr_ptr(),buf,len );
	wr_ptr( len );
	return len; 
}

const char* message_block::crunch( )
{
	char* buf =( char* ) memmove( data_block_->base(), rd_ptr(), length() );
	if( buf == 0 )
		return 0;
	
	data_block_->size( length() );
	rd_size_ = 0;

	return rd_ptr();
}

size_t message_block::capacity( )
{
	return data_block_->capacity();
}

_jingxian_end