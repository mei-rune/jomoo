

_jomoo_db_begin

	/**
	 * ����һ����ѯ����
	 */
	 inline DbQuery DbConnection::createQuery()
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		return DbQuery( _connection->createQuery() );
	}

	/**
	 * ����һ��ִ�ж���
	 */
	inline DbCommand DbConnection::createCommand()
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		return DbCommand( _connection->createCommand() );
	}

	/**
	 * ��ʼһ������
	 */
	inline DbTransaction DbConnection::beginTransaction( IsolationLevel level )
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		return DbTransaction( _connection->beginTransaction(level) );
	}

_jomoo_db_end
