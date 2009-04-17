
class OutOfRangeException : public Exception
{
public:

    OutOfRangeException(const   char* const         srcFile
            , size_t        srcLine
			, int length
			, int range )
			: Exception(srcFile, srcLine, _T("������Χ,���ʵ�") + toString( length ) + _T("����ֻ��") + toString( range ) + _T( "��" ) )
    {
	}
	OutOfRangeException(const   char* const         srcFile
            , size_t        srcLine )
			: Exception(srcFile, srcLine, OutOfRangeError )
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

    virtual ~OutOfRangeException() throw()
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