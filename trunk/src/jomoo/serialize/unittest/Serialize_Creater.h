#pragma once
#ifdef UNITTEST
#include "jomoo/serializing.hpp"

class out_stream
{
public:
	virtual ~out_stream(){}
	virtual bt_o_stream_base& get_o_stream( ) = 0 ;
};

class in_stream
{
public:
	virtual ~in_stream(){}
	virtual bt_i_stream_base& get_i_stream( ) = 0 ;
};

class Serialize_Creater
{
public:
	Serialize_Creater(void);
	~Serialize_Creater(void);

	static out_stream* create_o_stream( const char* file );
	static in_stream* create_i_stream( const char* file );
};
#endif