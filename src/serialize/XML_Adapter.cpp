#include "StdAfx.h"
#include "xml_adapter.h"

_bt_serialize_begin

TBinInputStreamInputStream::TBinInputStreamInputStream( bt_istream& stream)
: stream_( stream )
, pos_( 0 )
{
}

TBinInputStreamInputStream::~TBinInputStreamInputStream()
{
}

unsigned int TBinInputStreamInputStream::curPos() const
{
	return (u_int_t) pos_;
}

unsigned int TBinInputStreamInputStream::readBytes(XMLByte *const toFill, const unsigned int maxToRead)
{
	size_t c = stream_.read( toFill, maxToRead );
	if( c != -1 )
		pos_ += c;
	return (u_int_t)c;
}



TInputStreamInputSource::TInputStreamInputSource(bt_istream& stream) : stream_(stream)
{
}

/////////////////////////////////////////////////////////////////////////////
TInputStreamInputSource::~TInputStreamInputSource()
{
}

/////////////////////////////////////////////////////////////////////////////
XERCES_CPP_NAMESPACE_QUALIFIER BinInputStream* TInputStreamInputSource::makeStream() const
{
    // will the returned point be freed by xecers?
    return new TBinInputStreamInputStream(stream_);

}



TBinOutputStream::TBinOutputStream( bt_ostream& stream )
: stream_( stream )
{
}

void TBinOutputStream::writeChars
    (
          const XMLByte* const      toWrite
        , const unsigned int        count
        ,       XERCES_CPP_NAMESPACE_QUALIFIER XMLFormatter* const formatter
    )
{
	stream_.write( toWrite, count );
}

_bt_serialize_end
