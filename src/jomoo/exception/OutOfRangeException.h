
class OutOfRangeException : public Exception
{
public:
 
    OutOfRangeException(const   char* const         srcFile
            , size_t        srcLine
			, int lenght
			, int range )
			: Exception(srcFile, srcLine, _T("超出范围,访问第") + toString( length ) + _T("个但只有") + toString( range ) + _T( "个" ) )
    {
	}
	OutOfRangeException(const   char* const         srcFile
            , size_t        srcLine )
			: Exception(srcFile, srcLine, msg )
    {
	}

	OutOfRangeException( )
		: Exception( OutOfRangeError )
	{
	}

	OutOfRangeException( const tstring & m	)
		: Exception( m )
	{
	}

	OutOfRangeException( const OutOfRangeException& e	)
		: Exception( e )
	{
	}

    virtual ~OutOfRangeException()
	{}
	
	virtual Exception* clone()
	{						
		return new OutOfRangeException( *this );
	}
	virtual void rethrow()
	{
		Raise( *this );
	}
	virtual void print(tostream& Target ) const
	{										
			Target << _T("OutOfRangeException")
			<< what()
			<< std::endl;
			dumpFile( Target );
	}
};
