//#ifndef Hazel_CONTEXT_H
//# define Hazel_CONTEXT_H
//
//#include "config.h"
//
//#if !defined (Hazel_LACKS_PRAGMA_ONCE)
//# pragma once
//#endif /* Hazel_LACKS_PRAGMA_ONCE */
//
//// Include files
//#include "config_MicroKernel.h"
//#include "ContextKey.h"
//#include "Hazel/exception.hpp"
//# include "Hazel/counter_ptr.hpp"
//
//_micro_kernel_begin
//
//class Component;
////typedef counter_ptr< Component > ComponentPtr;
//
//class INamingSubSystem Hazel_INTERFACE( INamingSubSystem )
//{
//public:
//	virtual ~INamingSubSystem(){}
//
//	virtual ComponentPtr	component ( const ContextKey& index ) = 0;
//	virtual void			put (const ContextKey& index, ComponentPtr component) = 0;
//	virtual void			erase ( const ContextKey& index) = 0;
//	virtual size_t			size (void) const = 0;
//private:
//	DECLARE_NO_COPY_CLASS( ContextImplBase );
//};
//
//class ContextImpl : public ContextImplBase
//{
//public:
//	ContextImpl( ContextKeyManager& km );
//	~ContextImpl();
//	ComponentPtr	component ( const ContextKey& index );
//	void			put (const ContextKey& index, ComponentPtr component);
//	void			erase ( const ContextKey& index);
//	size_t			size (void) const;
//private:
//
//	typedef std::vector< ComponentPtr > Components;
//
//	Components		m_components;	//< Presently recorded components.
//	ContextKeyManager& keymanger_;
//};
//
//class Context
//{
//public:
//
//	Context ( ContextKeyManager& ptr
//		, const tstring& name
//		, Context *parent
//		, std::auto_ptr< ContextImplBase >& impl =  std::auto_ptr< ContextImplBase >() );
//	~Context (void);
//
//	Context *	root (void);
//	const Context *	root (void) const;
//	Context *	parent (void);
//	const Context *	parent (void) const;
//	Context *	child (size_t index) ;
//	const Context *	child (size_t index) const;
//	size_t	children (void) const;
//
//	ComponentPtr	component ( const ContextKey& index );
//	ComponentPtr	component ( const tstring &index );
//	ComponentPtr	component ( const ContextKey& index, Context* &context );
//	ComponentPtr	component ( const tstring &index, Context* &context );
//
//	ComponentPtr	componentLocal ( const tstring &index );
//	ComponentPtr	componentLocal ( const ContextKey &index );
//
//	void		put (const ContextKey& index, ComponentPtr component);
//	void		put (const tstring& index, ComponentPtr component);
//	void		erase ( const ContextKey& index);
//	void		erase ( const tstring& index);
//	size_t  size(void) const;
//
//	ContextKeyManager& manager();
//	const tstring& server() const;
//
//	template <class S>
//		typename S::ptr_type component (void);
//	template <class S>
//		typename S::ptr_type component ( const ContextKey& index);
//	template <class S>
//		typename S::ptr_type component (const tstring &index);
//	template <class S>
//		typename S::ptr_type component ( const ContextKey& index, Context* &context);
//	template <class S>
//		typename S::ptr_type component (const tstring &index, Context* &context);
//	
//	template <class S>
//		typename S::ptr_type componentLocal (void);
//	template <class S>
//		typename S::ptr_type componentLocal ( const ContextKey& index);
//	template <class S>
//		typename S::ptr_type componentLocal (const tstring &index);
//
//	template <class S>
//		void queryLocal (std::vector< typename S::ptr_type > &matches);
//	template <class S>
//		void query (std::vector< typename S::ptr_type > &matches);
//
//	const tstring& toString() const;
//
//private:
//	DECLARE_NO_COPY_CLASS( Context );
//
//	typedef std::vector< Context * > Children;
//
//	void		addChild (Context *child);
//	void		detachChild (Context *child);
//
//	Context		*m_parent_;
//	Children		m_children_;
//	std::auto_ptr< ContextImplBase > m_components_;
//	ContextKeyManager& km_;
//	tstring name_;
//	tstring toString_;
//};
//
//_micro_kernel_end
//
//#include "Context.inl"
//#include "Context.Templ"
//
//#endif // Hazel_CONTEXT_H
