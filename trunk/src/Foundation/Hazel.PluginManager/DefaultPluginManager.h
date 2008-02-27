#ifndef DEFAULT_PLUGIN_MANAGER_PLUGIN_DB_H
# define DEFAULT_PLUGIN_MANAGER_PLUGIN_DB_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "MapUniqueIterator.h"
# include "IPluginManager.H"
# include "PluginInfoDOM.H"
# include "Hazel.Base/Threading/Threading.H"
# include <list>
# include <map>

_seal_begin

class DefaultPluginManager : public IPluginManager
{
public:

	typedef std::list< tstring > SearchPath;
	typedef std::map< FactoryKey , factory_ptr_type > FactoryMap;
	typedef FactoryMap::iterator FactoryIterator;

    ~DefaultPluginManager (void);

	static DefaultPluginManager *get ( const tchar* pa );

	/// �û��ӿ�
    void		addFeedback ( FeedbackCB callback );
    void		removeFeedback ( FeedbackCB callback );
	IPluginFeedback& getFeedback();

	/// �����ӿ�
	factory_ptr_type		findFactory ( const FactoryKey& category );
    void		addFactory ( const FactoryKey& category , factory_ptr_type factory );
    /// ע�⣬ʵ��ɾ��ʱ��Ҫע���Ƿ�����������locateFactoryȡ���������ã��оͲ���ɾ����
	void		removeFactory ( const FactoryKey& category );
	void		walk( PluginInfoWalker& walker );

	LoggerPtr getLogger();
	const tstring& toString() const;

	// cache 
    void		initialize (void);

private:
	DECLARE_NO_COPY_CLASS( DefaultPluginManager );

	DefaultPluginManager ( const SearchPath& path );

	bool		initialized (void);

    SearchPath		m_searchPath;
	PluginFeedback_Group	m_feedbacks;
	PluginInfoDOM dom_;
    FactoryMap		m_factories;

	bool initialize_;
	tstring toString_;

	Hazel_MUTEX_MUTABLE( dom_mutex_ );
	Hazel_MUTEX_MUTABLE( factory_mutex_ );
};

_seal_end

#endif // DEFAULT_PLUGIN_MANAGER_PLUGIN_DB_H
