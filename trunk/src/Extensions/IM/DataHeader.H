

#ifndef DATAHEADER_H
#define DATAHEADER_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_IM.h"
#include "BOE/BOE_Buffer.H"


_im_begin

enum IM_messageType
{
	  im_message
	, im_present
	, im_iq
	, im_x
	, im_error
};

const char BOEP[] = { 'B','O','E','P' };
#define BOEPVALUE ( *( int*)BOEP )

/**
 */
struct DataHeader
{
	int magic;
	int messageSize;
	char protocolMajor;
	char protocolMinor;
	char encodingMajor;
	char encodingMinor;
	char messageType;			// IM_messageType
	char compressionStatus;
	char reserve1;
	char reserve2;

	DataHeader()
	{
		memset( this, 0,sizeof( DataHeader ) );
		magic = BOEPVALUE;
		protocolMinor = 1;
		encodingMinor = 1;
	}
};

inline bool isValidMagic( const DataHeader& h )
{
	return ( h.magic == BOEPVALUE );
}

struct MessageHeader
{
	int type;
	tstring from;
	tstring to;
	tstring id;
};

enum IM_message_Type
{
	  Message_chat
	, Message_error 
	, Message_groupchat
	, Message_headline
	, Message_normal 
};

enum IM_present_type
{
	  Present_unavailable
	, Present_subscribe
	, Present_subscribed
	, Present_unsubscribe
	, Present_unsubscribed
	, Present_probe
	, Present_error
};

enum IM_IQ_type
{
	   IQ_get
	 , IQ_set
	 , IQ_result
	 , IQ_error
};

#define ERR_IM_PROTOCOL -6001
#define ERR_IM_TYPE		-6002
#define ERR_IM_LENGTH	-6003
#define ERR_IM_SENDER	-6004

_im_end

#endif // DATAHEADER_H