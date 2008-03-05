
#include "Url.H"

JOMOO_Url::JOMOO_Url( const tstring& url )
: url_( url )
, toString_( BT_TEXT("JOMOO_Url[ ") )
{
	toString_ += url_;
	toString_ += BT_TEXT(" ]");

    const tstring delim = BT_TEXT(" \t\n\r");

    tstring::size_type beg = url_.find_first_not_of(delim);
    if(beg == tstring::npos)
    {
        ThrowException1( URLException , BT_TEXT("£¬Îª¿Õ°×·û") );
    }

	tstring::size_type end = url_.find( "://", beg);
    if(end == tstring::npos)
    {
        end = url_.length();
    }

	protocol_ = url_.substr(beg, end - beg);
    if(protocol_ == BT_TEXT("default"))
    {
        protocol_ = BT_TEXT("tcp");
    }

	beg += 3;
	end = url_.find( "/", beg);
    if(end == tstring::npos)
    {
        end = url_.length();
		address_ = url_.substr(beg, end - beg);
		return ;
    }

	beg ++;
	end = url_.length();
	entity_ = url_.substr(beg, end - beg);

}

const tstring& JOMOO_Url::protocol() const
{
	return protocol_;
}

const tstring& JOMOO_Url::address() const
{
	return address_;
}

const tstring& JOMOO_Url::entity() const
{
	return entity_;
}

const tstring& JOMOO_Url::url() const
{
	return url_;
}

const tstring& JOMOO_Url::toString() const
{
	return toString_;
}
