

#include "ModuleReg.h"

_seal_begin

ModuleReg::ModuleReg ( PluginInfoDOM& dom , 
					  const tstring &file,
					  const tstring &bad)
: dom_( dom ) 
, manager_( dom.manager() )
, m_file (file)
, m_bad (bad == "0")
{
	Hazel_ASSERT ( getLogger(),! file.empty ());
	Hazel_ASSERT ( getLogger(),! bad.empty ());

	toString_ = ModuleRegTag;
	toString_ += BT_TEXT("[");
	toString_ += file;
	toString_ += BT_TEXT("]");
}

ModuleReg::ModuleReg ( PluginInfoDOM& dom , const tstring &file, bool bad)
: dom_( dom ) 
, manager_( dom.manager() )
, m_file (file)
, m_bad (bad)
{
	Hazel_ASSERT ( getLogger(),! file.empty ());

	toString_ = ModuleRegTag;
	toString_ += BT_TEXT("[");
	toString_ += file;
	toString_ += BT_TEXT("]");
}

ModuleReg::~ModuleReg (void)
{
}

const tstring&		ModuleReg::file (void) const
{
	return m_file;
}

bool ModuleReg::bad (void) const
{
	return m_bad;
}

void ModuleReg::bad (bool value)
{
	if (value)
	{
		m_modules.clear ();
	}
	m_bad = value;
}


void ModuleReg::walk( PluginInfoWalker& walker )
{
	walker.onModuleReg( *this );
	for( Iterator it = m_modules.begin()
		; it != m_modules.end()
		; it ++ )
		(*it)->walk( walker );
}

void ModuleReg::add ( IModulePtr module)
{
	Hazel_ASSERT ( getLogger(),! m_bad);
	Hazel_ASSERT ( getLogger(), !is_null(module) );
	m_modules.push_back (module);
}

void ModuleReg::remove (IModulePtr pos)
{
	return m_modules.remove (pos);
}

ModuleDescriptorPtr ModuleReg::cache ( IModuleDescriptorBuilder& Builder )  const
{
	char bad [2] = { m_bad ? '0' : '1', '\0' };
	ModuleDescriptorPtr info = Builder.createDescriptor( ModuleRegTag, tstring (m_file),bad );
	for (ConstIterator i = m_modules.begin (); i != m_modules.end (); ++i)
		info->addChild( (*i)->cache ( Builder ) );
	return info;
}

IPluginManager& ModuleReg::manager()
{
	return manager_;
}

const	tstring& ModuleReg::toString( ) const
{
	return toString_;
}

_seal_end
