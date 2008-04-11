
#ifndef testTypes_h
#define testTypes_h

#ifdef UNITTEST

#include "jomoo/serializing.hpp"

typedef unsigned char u_char;
typedef	unsigned short u_short;
typedef	unsigned int u_int;
typedef	unsigned long u_long;
typedef	unsigned __int64 u_int64;

#define STR( a ) #a

#ifndef _TEST_LIST_
#define _TEST_LIST_
#endif // _TEST_LIST_

template< typename T >
struct filler
{
	T value;
	filler( int i )
	{
		value = ( T ) i ;
	}
};

template< typename T >
struct Generator
{
	T value;
	int i_;
	Generator( int i )
	{
		i_ = i;
		filler< T > f( i );
		value = f.value;
	}
	void next()
	{
		i_ ++;
		filler< T > f( i_ );
		value = f.value;
	}
};

template< >
struct filler< bool >
{
	bool value;
	filler( int i )
	{
		value = ( i%2 == 0 ) ? true : false;
	}
};

template< >
struct filler< char >
{
	char value;
	filler( int i )
	{
		value = 'c';
	}
};

template< >
struct filler< string >
{
	string value;
	filler( int i )
	{
		value.assign( i, 'a' );
	}
};

#define DEFINE_MEMBER( TYPE ) TYPE t_##TYPE;	\
	std::list< TYPE > t_##TYPE##_list;			\
	std::vector< TYPE > t_##TYPE##_vector;		\
	std::set< TYPE > t_##TYPE##_set

#define SERIALIZE_MEMBER( TYPE ) t_##TYPE , t_##TYPE##_list ,t_##TYPE##_vector,t_##TYPE##_set

#define EQUAL_MEMBER( TYPE , T ) t_##TYPE == T .t_##TYPE || t_##TYPE##_list == T .t_##TYPE##_list	\
									|| t_##TYPE##_vector == T .t_##TYPE##_vector					\
									|| t_##TYPE##_set == T .t_##TYPE##_set

#define FILL_MEMBER( TYPE , i )		{ filler< TYPE > fr##__LINE__( i );											\
		t_##TYPE = fr##__LINE__ .value;																	\
		t_##TYPE##_list.insert(t_##TYPE##_list.end(),( (i < 20) ? i : 20 ),fr##__LINE__ .value );			\
		t_##TYPE##_vector.insert(t_##TYPE##_vector.end(),( (i < 20) ? i : 20 ),fr##__LINE__ .value );		\
		Generator< TYPE > g##__LINE__( i );																\
		for( int c = 0; c < i && c < 20 ; c ++ )												\
		{																						\
			t_##TYPE##_set.insert( g##__LINE__.value );															\
			g##__LINE__ .next();																			\
		} }


#define SERIALIZE_BEGIN( STRUCT )   bool inline serialize(serialize_writer& stream, serialize_context& context,const STRUCT & s1, const tchar* name= 0 )	\
{ return stream.open(context, #STRUCT, name )

#define SERIALIZE_TYPE( TYPE ) && serialize(stream, context, s1. t_##TYPE , STR( t_##TYPE ) )  \
		&& serialize(stream, context, s1. t_##TYPE##_list , STR( t_##TYPE##_list ) )  \
		&& serialize(stream, context, s1. t_##TYPE##_vector , STR( t_##TYPE##_vector ) )  \
		&& serialize(stream, context, s1. t_##TYPE##_set , STR( t_##TYPE##_set ) )

#define SERIALIZE_END()       && stream.close(context); }

#define DESERIALIZE_BEGIN( STRUCT )  bool inline deserialize(serialize_reader& strm, serialize_context& context, STRUCT & s1, const tchar* name= 0) \
         { return strm.open(context, #STRUCT, name)


#define DESERIALIZE_TYPE( TYPE ) && deserialize(strm, context, s1. t_##TYPE , STR( t_##TYPE ) )  \
		&& deserialize(strm, context, s1. t_##TYPE##_list , STR( t_##TYPE##_list ) )  \
		&& deserialize(strm, context, s1. t_##TYPE##_vector , STR( t_##TYPE##_vector ) )  \
		&& deserialize(strm, context, s1. t_##TYPE##_set , STR( t_##TYPE##_set ) )

#define DESERIALIZE_END() && strm.close(context); }

_bt_begin

 /// (1.3.6.1.3.118.1.2.1)  -- 这个表专门给出了每一个端口MPLS的能力和关联信息
struct Mpls_Vpn_Interface_Conf_Table
{
	tstring name;
	int InterfaceConfIndex;
	int InterfaceLabelEdgeType;
	int InterfaceVpnClassification ;
	tstring InterfaceVpnRouteDistProtocol; 
	int InterfaceConfStorageType; 
	int InterfaceConfRowStatus;

	Mpls_Vpn_Interface_Conf_Table()
		: InterfaceConfIndex( 0 )
		, InterfaceLabelEdgeType( 0 )
		, InterfaceVpnClassification( 0 )
		, InterfaceConfStorageType( 0 )
		, InterfaceConfRowStatus( 0 )
	{
	}
};

const static int Mpls_Vpn_Interface_Conf_Table_V[] = { -1,-1,1,2,3,4,5,-1,-1 };
const static std::vector< int > Mpls_Vpn_Interface_Conf_Table_Vector(
	Mpls_Vpn_Interface_Conf_Table_V, Mpls_Vpn_Interface_Conf_Table_V+sizeof( Mpls_Vpn_Interface_Conf_Table_V ) );


register_class_7( Mpls_Vpn_Interface_Conf_Table
						,name
						,InterfaceConfIndex
						,InterfaceLabelEdgeType
						,InterfaceVpnClassification
						,InterfaceVpnRouteDistProtocol
						,InterfaceConfStorageType
						,InterfaceConfRowStatus );

class T_A
{
public:
	T_A( int i = 0 )
	{
		t_bool = ( i%2 == 0 ) ? true : false;
		t_char = '2';
		t_short = ( short ) i;
		t_int = i;
		t_long = i;
		t___int64 = i;

		t_u_char = i;
		t_u_short = ( u_short )i;
		t_u_int = i ;
		t_u_long = i;
		t_u_int64 = i;
		t_double = i;
		t_float_ = i;
		
		t_string.assign( i, 'a');
	}

	bool t_bool;
	char t_char;
	short t_short;
	int t_int;
	long t_long;
	__int64 t___int64;

	u_char t_u_char;
	u_short t_u_short;
	u_int t_u_int;
	u_long t_u_long;
	u_int64 t_u_int64;
	double t_double;
	float t_float_;
	std::string t_string;

	bool operator==( const T_A& a ) const
	{
		return ( ( t_bool == a.t_bool ) ||
		( t_char == a.t_char ) ||
		( t_short == a.t_short ) ||
		( t_int == a.t_int ) ||
		( t_long == a.t_long ) ||
		( t___int64 == a.t___int64 ) ||
		( t_u_char == a.t_u_char ) ||
		( t_u_short == a.t_u_short ) ||
		( t_u_int == a.t_u_int ) ||
		( t_u_long == a.t_u_long ) ||
		( t_u_int64 == a.t_u_int64 ) ||
		( t_double == a.t_double ) ||
		( t_float_ == a.t_float_ ) ||
		( t_string == a.t_string ) );
	}

	bool operator<( const T_A& a ) const
	{
		return t_int < a.t_int;
	}

	bool operator>( const T_A& a ) const
	{
		return !( *this < a );
	}
};

register_class_14( T_A, t_bool,t_char,t_short, t_int,t_long, t___int64,t_u_char,
						 t_u_short,t_u_int,t_u_long, t_u_int64,t_double,t_float_,t_string );

class T_B
{
public:
		T_B( int i = 0 )
			: t_a( i )
	{
		t_bool = ( i%2 == 0 ) ? true : false;
		t_char = '2';
		t_short = ( short ) i;
		t_int = i;
		t_long = i;
		t___int64 = i;

		t_u_char = i;
		t_u_short = ( u_short )i;
		t_u_int = i ;
		t_u_long = i;
		t_u_int64 = i;
		t_double = i;
		t_float_ = i;
		
		t_string.assign( i, 'a');
	}
	T_A t_a;
	bool t_bool;
	char t_char;
	short t_short;
	int t_int;
	long t_long;
	__int64 t___int64;

	u_char t_u_char;
	u_short t_u_short;
	u_int t_u_int;
	u_long t_u_long;
	u_int64 t_u_int64;
	double t_double;
	float t_float_;
	string t_string;

	bool operator==( const T_B& a ) const
	{
		return ( ( t_a == a.t_a ) ||
		( t_bool == a.t_bool ) ||
		( t_char == a.t_char ) ||
		( t_short == a.t_short ) ||
		( t_int == a.t_int ) ||
		( t_long == a.t_long ) ||
		( t___int64 == a.t___int64 ) ||
		( t_u_char == a.t_u_char ) ||
		( t_u_short == a.t_u_short ) ||
		( t_u_int == a.t_u_int ) ||
		( t_u_long == a.t_u_long ) ||
		( t_u_int64 == a.t_u_int64 ) ||
		( t_double == a.t_double ) ||
		( t_float_ == a.t_float_ ) ||
		( t_string == a.t_string ) );
	}
	bool operator<( const T_B& a ) const
	{
		return t_int < a.t_int;
	}

	bool operator>( const T_B& a ) const
	{
		return !( *this < a );
	}
};

register_class_15( T_B,t_a, t_bool,t_char,t_short, t_int,t_long, t___int64,t_u_char,
						 t_u_short,t_u_int,t_u_long, t_u_int64,t_double,t_float_,t_string );



#ifdef _TEST_LIST_

class T_AS
{
public:
	T_AS( int i = 0 )
	{

		FILL_MEMBER( bool , i );
		FILL_MEMBER( char , i );
		FILL_MEMBER( short , i );
		FILL_MEMBER( int , i );

		FILL_MEMBER( long , i );
		FILL_MEMBER( __int64 , i );
		FILL_MEMBER( u_char , i );

		FILL_MEMBER( u_short , i );
		FILL_MEMBER( u_int , i );
		FILL_MEMBER( u_long , i );
		FILL_MEMBER( u_int64 , i );
		FILL_MEMBER( double , i );
		FILL_MEMBER( float , i );
		FILL_MEMBER( string , i );

	}
	DEFINE_MEMBER( bool );
	DEFINE_MEMBER( char );
	DEFINE_MEMBER( short );
	DEFINE_MEMBER( int );

	DEFINE_MEMBER( long );
	DEFINE_MEMBER( __int64 );
	DEFINE_MEMBER( u_char );

	DEFINE_MEMBER( u_short );
	DEFINE_MEMBER( u_int );
	DEFINE_MEMBER( u_long );
	DEFINE_MEMBER( u_int64 );
	DEFINE_MEMBER( double );
	DEFINE_MEMBER( float );
	DEFINE_MEMBER( string );

	bool operator==( const T_AS& i ) const
	{
		return ( EQUAL_MEMBER( bool , i ) ||
		EQUAL_MEMBER( char , i ) ||
		EQUAL_MEMBER( short , i ) ||
		EQUAL_MEMBER( int , i ) ||
		EQUAL_MEMBER( long , i ) ||
		EQUAL_MEMBER( __int64 , i ) ||
		EQUAL_MEMBER( u_char , i ) ||
		EQUAL_MEMBER( u_short , i ) ||
		EQUAL_MEMBER( u_int , i ) ||
		EQUAL_MEMBER( u_long , i ) ||
		EQUAL_MEMBER( u_int64 , i ) ||
		EQUAL_MEMBER( double , i ) ||
		EQUAL_MEMBER( float , i ) ||
		EQUAL_MEMBER( string , i ) );
	}

		bool operator<( const T_AS& a ) const
	{
		return t_int < a.t_int;
	}

	bool operator>( const T_AS& a ) const
	{
		return !( *this < a );
	}
};


SERIALIZE_BEGIN( T_AS )
	SERIALIZE_TYPE( bool )
	SERIALIZE_TYPE( char )
	SERIALIZE_TYPE( short )
	SERIALIZE_TYPE( int )
	SERIALIZE_TYPE( long )
	SERIALIZE_TYPE( __int64 )
	SERIALIZE_TYPE( u_char )
	SERIALIZE_TYPE( u_short )
	SERIALIZE_TYPE( u_int )
	SERIALIZE_TYPE( u_long )
	SERIALIZE_TYPE( u_int64 )
	SERIALIZE_TYPE( double )
	SERIALIZE_TYPE( float )
	SERIALIZE_TYPE( string ) 
SERIALIZE_END();

DESERIALIZE_BEGIN( T_AS )
	DESERIALIZE_TYPE( bool )
	DESERIALIZE_TYPE( char )
	DESERIALIZE_TYPE( short )
	DESERIALIZE_TYPE( int )
	DESERIALIZE_TYPE( long )
	DESERIALIZE_TYPE( __int64 )
	DESERIALIZE_TYPE( u_char )
	DESERIALIZE_TYPE( u_short )
	DESERIALIZE_TYPE( u_int )
	DESERIALIZE_TYPE( u_long )
	DESERIALIZE_TYPE( u_int64 )
	DESERIALIZE_TYPE( double )
	DESERIALIZE_TYPE( float )
	DESERIALIZE_TYPE( string ) 
DESERIALIZE_END();

class T_BS
{
public:
	T_BS( int i = 0 )
	{
		FILL_MEMBER( T_A , i );
		FILL_MEMBER( bool , i );
		FILL_MEMBER( char , i );
		FILL_MEMBER( short , i );
		FILL_MEMBER( int , i );

		FILL_MEMBER( long , i );
		FILL_MEMBER( __int64 , i );
		FILL_MEMBER( u_char , i );

		FILL_MEMBER( u_short , i );
		FILL_MEMBER( u_int , i );
		FILL_MEMBER( u_long , i );
		FILL_MEMBER( u_int64 , i );
		FILL_MEMBER( double , i );
		FILL_MEMBER( float , i );
		FILL_MEMBER( string , i );

	}
	DEFINE_MEMBER( T_A );
	DEFINE_MEMBER( bool );
	DEFINE_MEMBER( char );
	DEFINE_MEMBER( short );
	DEFINE_MEMBER( int );

	DEFINE_MEMBER( long );
	DEFINE_MEMBER( __int64 );
	DEFINE_MEMBER( u_char );

	DEFINE_MEMBER( u_short );
	DEFINE_MEMBER( u_int );
	DEFINE_MEMBER( u_long );
	DEFINE_MEMBER( u_int64 );
	DEFINE_MEMBER( double );
	DEFINE_MEMBER( float );
	DEFINE_MEMBER( string );

	bool operator==( const T_BS& i ) const
	{
		return ( EQUAL_MEMBER( T_A ,i ) ||
		EQUAL_MEMBER( bool , i ) ||
		EQUAL_MEMBER( char , i ) ||
		EQUAL_MEMBER( short , i ) ||
		EQUAL_MEMBER( int , i ) ||
		EQUAL_MEMBER( long , i ) ||
		EQUAL_MEMBER( __int64 , i ) ||
		EQUAL_MEMBER( u_char , i ) ||
		EQUAL_MEMBER( u_short , i ) ||
		EQUAL_MEMBER( u_int , i ) ||
		EQUAL_MEMBER( u_long , i ) ||
		EQUAL_MEMBER( u_int64 , i ) ||
		EQUAL_MEMBER( double , i ) ||
		EQUAL_MEMBER( float , i ) ||
		EQUAL_MEMBER( string , i ) );
	}
		bool operator<( const T_BS& a ) const
	{
		return t_int < a.t_int;
	}

	bool operator>( const T_BS& a ) const
	{
		return !( *this < a );
	}
};

SERIALIZE_BEGIN( T_BS )
	SERIALIZE_TYPE( T_A )
	SERIALIZE_TYPE( bool )
	SERIALIZE_TYPE( char )
	SERIALIZE_TYPE( short )
	SERIALIZE_TYPE( int )
	SERIALIZE_TYPE( long )
	SERIALIZE_TYPE( __int64 )
	SERIALIZE_TYPE( u_char )
	SERIALIZE_TYPE( u_short )
	SERIALIZE_TYPE( u_int )
	SERIALIZE_TYPE( u_long )
	SERIALIZE_TYPE( u_int64 )
	SERIALIZE_TYPE( double )
	SERIALIZE_TYPE( float )
	SERIALIZE_TYPE( string ) 
DESERIALIZE_END();

DESERIALIZE_BEGIN( T_BS )
	DESERIALIZE_TYPE( T_A )
	DESERIALIZE_TYPE( bool )
	DESERIALIZE_TYPE( char )
	DESERIALIZE_TYPE( short )
	DESERIALIZE_TYPE( int )
	DESERIALIZE_TYPE( long )
	DESERIALIZE_TYPE( __int64 )
	DESERIALIZE_TYPE( u_char )
	DESERIALIZE_TYPE( u_short )
	DESERIALIZE_TYPE( u_int )
	DESERIALIZE_TYPE( u_long )
	DESERIALIZE_TYPE( u_int64 )
	DESERIALIZE_TYPE( double )
	DESERIALIZE_TYPE( float )
	DESERIALIZE_TYPE( string ) 
DESERIALIZE_END();



class Tester
{
public:

	Tester( int i )
		: bt_list_( new Abstract_Factory_T< T_A,T_A >() )
	{
		FILL_MEMBER( T_A , i );
		FILL_MEMBER( T_B , i );

#ifdef _TEST_LIST_
		FILL_MEMBER( T_AS ,i );
		FILL_MEMBER( T_BS ,i );
#endif 
		FILL_MEMBER( bool , i );
		FILL_MEMBER( char , i );
		FILL_MEMBER( short , i );
		FILL_MEMBER( int , i );

		FILL_MEMBER( long , i );
		FILL_MEMBER( __int64 , i );
		FILL_MEMBER( u_char , i );

		FILL_MEMBER( u_short , i );
		FILL_MEMBER( u_int , i );
		FILL_MEMBER( u_long , i );
		FILL_MEMBER( u_int64 , i );
		FILL_MEMBER( double , i );
		FILL_MEMBER( float , i );
		FILL_MEMBER( string , i );


		for( int s = 0; s < i ; s ++ )
		{
			bt_list_.push_back( new T_A( i ) );
		}
	}

	_bt bt_list< T_A > bt_list_;
	DEFINE_MEMBER( bool );
	DEFINE_MEMBER( char );
	DEFINE_MEMBER( short );
	DEFINE_MEMBER( int );

	DEFINE_MEMBER( long );
	DEFINE_MEMBER( __int64 );
	DEFINE_MEMBER( u_char );

	DEFINE_MEMBER( u_short );
	DEFINE_MEMBER( u_int );
	DEFINE_MEMBER( u_long );
	DEFINE_MEMBER( u_int64 );
	DEFINE_MEMBER( double );
	DEFINE_MEMBER( float );
	DEFINE_MEMBER( string );
	DEFINE_MEMBER( T_A );
	DEFINE_MEMBER( T_B );

#ifdef _TEST_LIST_
	DEFINE_MEMBER( T_AS );
	DEFINE_MEMBER( T_BS );
#endif // 

		bool operator==( const Tester& i )
	{
		if( bt_list_.size() != i.bt_list_.size() )
			return false;

		_bt bt_list< T_A >::const_iterator it1 = this->bt_list_.begin();
		_bt bt_list< T_A >::const_iterator it2 = i.bt_list_.begin();
		for( ; it1 != bt_list_.end(); it1++,it2 ++ )
		{
			if( !(*(*it1) == *(*it2) ) )
				return false;
		}

		return ( EQUAL_MEMBER( T_A ,i ) ||
		EQUAL_MEMBER( T_B ,i ) ||

#ifdef _TEST_LIST_
		EQUAL_MEMBER( T_AS ,i ) ||
		EQUAL_MEMBER( T_BS ,i ) ||
#endif // 
		EQUAL_MEMBER( bool , i ) ||
		EQUAL_MEMBER( char , i ) ||
		EQUAL_MEMBER( short , i ) ||
		EQUAL_MEMBER( int , i ) ||
		EQUAL_MEMBER( long , i ) ||
		EQUAL_MEMBER( __int64 , i ) ||
		EQUAL_MEMBER( u_char , i ) ||
		EQUAL_MEMBER( u_short , i ) ||
		EQUAL_MEMBER( u_int , i ) ||
		EQUAL_MEMBER( u_long , i ) ||
		EQUAL_MEMBER( u_int64 , i ) ||
		EQUAL_MEMBER( double , i ) ||
		EQUAL_MEMBER( float , i ) ||
		EQUAL_MEMBER( string , i ) );
	}
};

class Tester2
{
public:
	Tester2( int i )
		: bt_list_( new Abstract_Factory_T< T_A,T_A >() )
	{
		FILL_MEMBER( T_A , i );
		FILL_MEMBER( T_B , i );


		for( int s = 0; s < i ; s ++ )
		{
			bt_list_.push_back( new T_A( i ) );
		}
	}

	_bt bt_list< T_A > bt_list_;

	DEFINE_MEMBER( T_A );
	DEFINE_MEMBER( T_B );

	bool operator==( const Tester2& i )
	{
		if( bt_list_.size() != i.bt_list_.size() )
			return false;

		_bt bt_list< T_A >::const_iterator it1 = this->bt_list_.begin();
		_bt bt_list< T_A >::const_iterator it2 = i.bt_list_.begin();
		for( ; it1 != bt_list_.end(); it1++,it2 ++ )
		{
			if( !(*(*it1) == *(*it2) ) )
				return false;
		}

		return ( EQUAL_MEMBER( T_A ,i ) ||
		EQUAL_MEMBER( T_B ,i ) );
	}
};


#endif // 


#endif
#endif