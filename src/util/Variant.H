

#ifndef _Variant_H_
#define _Variant_H_

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include <boost/variant.hpp>
#include "pTime.H"
#include "util/tstring.h"

_bt_begin

struct Variant_Type { enum Type{ NONE=0, INTEGER,BIGINTEGER, DOUBLE, STRING, TIME, BOOLEAN }; };

typedef boost::variant< int,__int64,double,tstring,ptime, bool > Variant;

class Variant_Int_Visitor
	: public boost::static_visitor<>
{
public:

	Variant_Int_Visitor( int & d )
		: Int_( d )
	{
	}
	void operator()( const int & i) const
	{
		Int_ = i;
	}

	void operator()( const __int64 & i ) const
	{
		Int_ = ( int )i;
	}

	void operator()( const double & d) const
	{
		Int_ = ( int )d;
	}

	void operator()( const tstring & str) const
	{
		Int_ = convertStringToInteger< int >( str );
	}

	void operator()( const ptime & t) const
	{
		//tstring timestr = to_iso_extended_string( t );
		//Int_ = tstrftime( 
	}

	void operator()( const bool & t) const
	{
		Int_ = ( t? 1 : 0 );
	}
private:
	int& Int_;
};

class Variant_Int64_Visitor
	: public boost::static_visitor<>
{
public:

	Variant_Int64_Visitor( __int64 & d )
		: Int_( d )
	{
	}
	void operator()( const int & i) const
	{
		Int_ = i;
	}

	void operator()( const __int64 & i ) const
	{
		Int_ = i;
	}

	void operator()( const double & d) const
	{
		Int_ = ( __int64 )d;
	}

	void operator()( const tstring & str) const
	{
		Int_ = convertStringToInteger< __int64 >( str );
	}

	void operator()( const ptime & t) const
	{
		//tstring timestr = to_iso_extended_string( t );
		//Int_ = tstrftime( 
	}

	void operator()( const bool & t) const
	{
		Int_ = ( t? 1 : 0 );
	}
private:
	__int64& Int_;
};

class Variant_Double_Visitor
	: public boost::static_visitor<>
{
public:

	Variant_Double_Visitor( double & i )
		: Double_( i )
	{
	}
	void operator()( const int & i) const
	{
		Double_ = i;
	}

	void operator()( const __int64 & i ) const
	{
		Double_ = ( double )i;
	}

	void operator()( const double & d) const
	{
		Double_ = d;
	}

	void operator()( const tstring & str) const
	{
		Double_ = convertStringToInteger< double >( str );
	}

	void operator()( const ptime & t) const
	{
		//tstring timestr = to_iso_extended_string( t );
		//Int_ = tstrftime( 
	}

	void operator()( const bool & t) const
	{
		Double_ = ( t? 1.0 : 0.0 );
	}
private:
	double& Double_;
};



class Variant_String_Visitor
	: public boost::static_visitor<>
{
public:

	Variant_String_Visitor( tstring& str )
		: String_( str )
	{
	}
	void operator()( const int & i) const
	{
		String_ = convertIntegerToString( i );
	}

	void operator()( const __int64 & i ) const
	{
		String_ = convertIntegerToString( i );
	}

	void operator()( const double & d) const
	{
		String_ = convertIntegerToString( d );
	}

	void operator()( const tstring & str) const
	{
		String_ = str;
	}

	void operator()( const ptime & t) const
	{
		String_ = boost::posix_time::to_iso_extended_string( t );
	}

	void operator()( const bool & t) const
	{
		String_ = ( t? "true" : "false" );
	}
private:
	tstring& String_;
};

class Variant_Time_Visitor
	: public boost::static_visitor<>
{
public:

	Variant_Time_Visitor( ptime& t )
		: Time_( t )
	{
	}
	void operator()( const int & i) const
	{
		Time_ = boost::posix_time::from_time_t( ( time_t ) i );
	}

		void operator()( const __int64 & i ) const
	{
		Time_ = boost::posix_time::from_time_t( ( time_t ) i );
	}

	void operator()( const double & d) const
	{
		Time_ = boost::posix_time::from_time_t( ( time_t ) d );
	}

	void operator()( const tstring & str) const
	{
		Time_ = boost::posix_time::time_from_string( str );
	}

	void operator()( const ptime & t) const
	{
		Time_ = t;
	}

	void operator()( const bool & t) const
	{
		
	}
private:
	ptime& Time_;
};

class Variant_Bool_Visitor
	: public boost::static_visitor<>
{
public:

	Variant_Bool_Visitor( bool& b )
		: Bool_( b )
	{
	}
	void operator()( const int & i) const
	{
		if( i > 0 )
			Bool_ = true;
		else
			Bool_ = false;
	}

	void operator()( const __int64 & i ) const
	{
		if( i > 0 )
			Bool_ = true;
		else
			Bool_ = false;
	}

	void operator()( const double & d) const
	{
		if( d > 0 )
			Bool_ = true;
		else
			Bool_ = false;
	}

	void operator()( const tstring & str) const
	{
		if( tstrcasencmp( str.c_str(), "true" ) == 0 )
			Bool_ = true;
		else
			Bool_ = false;
	}

	void operator()( const ptime & t) const
	{
		
	}

	void operator()( const bool & t) const
	{
		Bool_ = t;
	}
private:
	bool& Bool_;
};
_bt_end


#endif // _Variant_H_
