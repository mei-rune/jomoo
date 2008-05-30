

_jomoo_db_begin

	/**
	 * 创建一个查询对象
	 */
	 inline DbQuery DbConnection::createQuery()
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		return DbQuery( _connection->createQuery() );
	}

	/**
	 * 创建一个执行对象
	 */
	inline DbCommand DbConnection::createCommand()
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		return DbCommand( _connection->createCommand() );
	}

	/**
	 * 开始一个事务
	 */
	inline DbTransaction DbConnection::beginTransaction( IsolationLevel level )
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		return DbTransaction( _connection->beginTransaction(level) );
	}

_jomoo_db_end
