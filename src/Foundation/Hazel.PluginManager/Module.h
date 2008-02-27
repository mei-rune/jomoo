
#ifndef MODULE_H
#define MODULE_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "IModuleDef.H"
# include "IModule.H"
# include "PluginInfoDOM.H"
# include "Hazel.Base/UTIL/Shared_Library.h"

extern "C" { typedef _seal IModuleDef *(*ModuleEntry) (void); }
extern "C" { typedef const char * (*MODULE_VERSION_ENTRY) (void); }


_seal_begin

class Module : public IModule
{
public:
    //typedef InfoList::const_iterator	InfoIterator;
    //typedef std::set< PluginInfoBase *>	InfoList;

	typedef std::list< ModuleDescriptorPtr > DescriptorList;

    Module ( PluginInfoDOM& dom , const tstring &libraryName );
    virtual ~Module (void);

    const tstring&	libraryName (void) const;
	void	attach (void);
    void	detach (void);
    void	query (void);

	void	walk( PluginInfoWalker& walker );
    void	add ( ModuleDescriptorPtr info );
    void	remove ( ModuleDescriptorPtr info ) ;
    ModuleDescriptorPtr	cache ( IModuleDescriptorBuilder& ) const;
	IPluginManager& manager();
	const	tstring& toString( ) const ;

private:
    ModuleEntry		moduleEntryPoint (void);
    _util Share_Library&	library (void)
	{
		return m_library;
	}

    void	load_i (void);
    void	unload_i (void);
    bool	loaded_i (void) const;
	void	attach_i (void);
    void	detach_i (void);
	bool	attached_i (void);
    void	query_i (void);

	void	walk_i( PluginInfoWalker& walker );
    void	add_i ( ModuleDescriptorPtr info );
    void	remove_i ( ModuleDescriptorPtr info ) ;
    ModuleDescriptorPtr	cache_i ( IModuleDescriptorBuilder& ) const;

	LoggerPtr getLogger();


	PluginInfoDOM& dom_;
    IPluginManager&	manager_;

    tstring		m_libraryName;
    _util Share_Library m_library;
	ModuleEntry	entry_;

	bool attached_;
	
	DescriptorList descriptors_	;


	tstring toString_;

    static const char	s_modEntryPoint [];//模块入口函数名
	static const char	s_modVersionEntryPoint[];
};

_seal_end

#endif // MODULE_H
