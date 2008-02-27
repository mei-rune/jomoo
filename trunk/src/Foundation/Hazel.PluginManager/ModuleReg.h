#ifndef PLUGIN_MANAGER_MODULE_REG_H
# define PLUGIN_MANAGER_MODULE_REG_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "IModuleReg.H"
# include "PluginInfoDOM.H"

_seal_begin

/// 每一个ModuleReg对应一个reg文件
class ModuleReg : public IModuleReg
{
public:
    ModuleReg (PluginInfoDOM& dom
		, const tstring &regfile
		, bool bad);
    ModuleReg (PluginInfoDOM& dom
		, const tstring &regfile
		, const std::string &bad );
    virtual ~ModuleReg (void);

    const tstring&		file (void) const;
    bool		bad (void) const;
    void		bad (bool value);

	void walk( PluginInfoWalker& walker );
	void add( IModulePtr );
	void remove( IModulePtr );
    ModuleDescriptorPtr	cache ( IModuleDescriptorBuilder& ) const ;
	IPluginManager& manager() ;
	const	tstring& toString( ) const ;

	LoggerPtr getLogger()
	{
		return manager().getLogger();
	}

private:
	PluginInfoDOM& dom_;
    IPluginManager&	manager_;

    tstring		m_file;
    bool		m_bad;

	typedef std::list<IModulePtr>::iterator Iterator;
	typedef std::list<IModulePtr>::const_iterator ConstIterator;
    std::list<IModulePtr>	m_modules;

	tstring toString_;

};


_seal_end

#endif // PLUGIN_MANAGER_MODULE_REG_H
