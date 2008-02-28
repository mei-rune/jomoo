#pragma once

#include "../btnm.h"
#include "../btnmlib.h"
#include "../net_address.h"
#include "../os_time.h"
#include "../mac_address.h"

#include "serialize2.h"

_bt_begin

bool inline serialize_ipaddress( unsigned long ip, serialize_ostream_base& stream, const char* name="ipaddress")
{
	return serialize(GetIPString(ip),stream,name);	
}
bool inline deserialize_ipaddress( unsigned long& ip, serialize_istream_base& stream, const char* name="ipaddress")
{
	string ipstr;
	if( !deserialize(ipstr, stream, name) )
		return false;
	Str2IP(ipstr.c_str(), ip);
	return true;
}

bool inline serialize_int32listASstring(const Int32List& I32s, serialize_ostream_base& stream, const char* name="int32listASstring")
{
	string str;
	IntsToString(I32s, str, ",");
	return serialize(str, stream, name);
	
}
bool inline deserialize_int32listASstring( Int32List& I32s, serialize_istream_base& stream, const char* name="int32listASstring")
{
	std::string ipstr = "";//如果读取失败，则转换也会失败
	if( ! deserialize(ipstr, stream, name) )
		return false;
	StringToInts(ipstr, I32s);
	return true;
}
bool inline serialize_macaddress(const unsigned char *mac, serialize_ostream_base& stream, const char* name="macaddress")
{
	return serialize(GetMACString(mac, ' '),stream,name);	
}
bool inline deserialize_macaddress( unsigned char* mac, serialize_istream_base& stream, const char* name="macaddress")
{
	string macstr = "";
	if( !deserialize(macstr, stream, name) )
		return false;
	Str2MAC(macstr.c_str(), mac);
	return true;
}

bool inline serialize_macaddressstring(const std::string& mac, serialize_ostream_base& stream, const char* name="macaddress")
{
	return serialize( mac ,stream,name);	
}

bool inline deserialize_macaddressstring( std::string& mac, serialize_istream_base& stream, const char* name="macaddress")
{
	return deserialize(mac, stream, name);
}

bool inline serialize_time( time_t tm, serialize_ostream_base& stream, const char* name="time")
{
	 return serialize( tm,stream,name);	
}

bool inline deserialize_time( time_t& tm, serialize_istream_base& stream, const char* name="time")
{
	long t = 0;
	if( !deserialize(t, stream, name) )
		return false;
	tm = ( time_t )t;
	return true;
}

bool inline serialize_timestring( time_t Tm, serialize_ostream_base& stream, const char* name="")
{
	 return serialize(GetTimeString(Tm, 1),stream,name);	
}
bool inline deserialize_timestring( time_t& Tm, serialize_istream_base& stream, const char* name="")
{
	std::string macstr;
	if( ! deserialize(macstr, stream, name) )
		return false;
	GetTime(macstr.c_str(), Tm);
	return true;
}

bool inline serialize_net_address(const net_address &ip, serialize_ostream_base& stream, const char* name="")
{
	return serialize( ip.ToString(),stream,name);	
}

bool inline deserialize_net_address( net_address& ip, serialize_istream_base& stream, const char* name="")
{
	string ipstr ;
	if( !deserialize( ipstr, stream, name) )
		return false;
	ip.set( ipstr.c_str() );
	return true;
}

bool inline serialize_os_time(const os_time &time, serialize_ostream_base& stream, const char* name="")
{
	return serialize( time.ToString(),stream,name);	
}

bool inline deserialize_os_time( os_time& time, serialize_istream_base& stream, const char* name="")
{
	string timestr;
	if( !deserialize( timestr, stream, name) )
		return false;
	time.set( timestr.c_str() );
	return true;
}

bool inline serialize_os_time_long(const os_time &time, serialize_ostream_base& stream, const char* name="")
{
	return serialize( ( int32 )time.get(),stream,name);	
}

bool inline deserialize_os_time_long( os_time& time, serialize_istream_base& stream, const char* name="")
{
	time_t time_long;
	if( !deserialize( time_long, stream, name) )
		return false;
	time.set( ( int32 ) time_long );
	return true;
}

_bt_end