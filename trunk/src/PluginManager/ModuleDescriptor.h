#ifndef MODULE_DESCRIPTOR_H
# define MODULE_DESCRIPTOR_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "Hazel.Base/counter_ptr.hpp"
# include "IModuleDescriptorBuilder.H"
# include <vector>

_seal_begin

class ModuleDescriptor
{
public:

	typedef ModuleDescriptorPtr ptr_type;
	typedef PluginManagerLoggerPtr LoggerPtr;

	typedef std::vector< ptr_type > child_container_type;
	typedef std::vector<tstring> token_container_type;

	ModuleDescriptor ( IModuleDescriptorBuilder& Builder ,
		const tstring &t1 ,
		const tstring &t2 = "",
		const tstring &t3 = "",
		const tstring &t4 = "",
		const tstring &t5 = "",
		const tstring &t6 = "",
		const tstring &t7 = "",
		const tstring &t8 = "")
		: Builder_( Builder )
	{

		if (! t1.empty ())
			m_tokens.push_back (t1);

		if (! t2.empty ())
		{
			Hazel_ASSERT ( getLogger(), ! t1.empty ());
			m_tokens.push_back (t2);
		}

		if (! t3.empty ())
		{
			Hazel_ASSERT ( getLogger(),! t2.empty ());
			m_tokens.push_back (t3);
		}

		if (! t4.empty ())
		{
			Hazel_ASSERT ( getLogger(),! t3.empty ());
			m_tokens.push_back (t4);
		}

		if (! t5.empty ())
		{
			Hazel_ASSERT (getLogger(),! t4.empty ());
			m_tokens.push_back (t5);
		}

		if (! t6.empty ())
		{
			Hazel_ASSERT (getLogger(),! t5.empty ());
			m_tokens.push_back (t6);
		}

		if (! t7.empty ())
		{
			Hazel_ASSERT (getLogger(),! t7.empty ());
			m_tokens.push_back (t7);
		}

		if (! t8.empty ())
		{
			Hazel_ASSERT (getLogger(),! t8.empty ());
			m_tokens.push_back (t8);
		}
	}

	ModuleDescriptor ( IModuleDescriptorBuilder& Builder ,
		const std::vector<tstring> &tokens)
		: Builder_( Builder )
		, m_tokens (tokens)
	{
	}
	
	size_t				children (void) const
	{ return m_children.size (); }

	ptr_type			child (unsigned index) const
	{ Hazel_ASSERT (getLogger(),index < m_children.size ()); return m_children [index]; }

	void				addChild ( ptr_type child)
	{
		Hazel_ASSERT (getLogger(),child);
		Hazel_ASSERT (getLogger(),std::find (m_children.begin (), m_children.end (), child)
			== m_children.end ());

		m_children.push_back (child);
	}

	size_t				tokens (void) const
	{ return m_tokens.size (); }
	const tstring &			token (size_t index) const
	{ return m_tokens [index]; }

	void				addToken (const tstring &text)
	{ m_tokens.push_back (text); }

	LoggerPtr getLogger() const
	{
		return Builder_.manager().getLogger();
	}

	IModuleDescriptorBuilder& getBuilder()
	{
		return Builder_;
	}

	const token_container_type& getToken() const
	{
		return m_tokens;
	}

	const child_container_type& getChild() const
	{
		return m_children;
	}

private:
	IModuleDescriptorBuilder& Builder_;
	child_container_type	m_children;	//< Down in the tree.
	token_container_type	m_tokens;	//< Tokens.
};

typedef ModuleDescriptor::ptr_type ModuleDescriptorPtr;

_seal_end

#endif // MODULE_DESCRIPTOR_H
 