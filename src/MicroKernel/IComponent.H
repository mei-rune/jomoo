// Hazel


#ifndef __Seal_Component_H__
#define __Seal_Component_H__

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_MicroKernel.h"
# include "DebugAids.H"
# include "ContextKey.H"

_micro_kernel_begin

class IComponentInformation
{
public:
	virtual ~IComponentInformation(){}
	virtual const tstring& name() const = 0;
	virtual const tstring& toString() const = 0;
};

# define DECLARE_SEAL_COMPONENT( COMPONENT , NAME )     \
class ComponentInformation : IComponentInformation		\
{														\
public:													\
	ComponentInformation()								\
		: name_( NAME )									\
	{}													\
	virtual ~ComponentInformation(){}					\
	const tstring& name() const							\
		{ return name_; }								\
	const tstring& toString() const{ return name_; }	\
private:												\
	tstring name_;										\
};

# define DEFINE_SEAL_COMPONENT( COMPONENT )									\
	public:																	\
		const IComponentInformation& componentInformation() const			\
		{return componentInformation_; }									\
	private:																\
		ComponentInformation componentInformation_;

class IKernel;
class InitializeContext;

/**
 * ��������Ľӿ�
 * ÿһ���������һ��Ψһ�ı�ʶ���������ʶ����һ����'/'�ַ��ָ����ַ���
 * ��	"SEAL/Kernel/Component/ComponentLoader"
 *		"SEAL/Kernel/ComponentService/ServiceLoader"
 * ���� SEAL/Kernel/Component �� SEAL/Kernel/ComponentService ��Ϊ�����
 * ����ע��ͬ���Ľӿڲ�һ���Ǵ�ͬһ���ӿڼ̳������ġ�
 */
class IComponent	Hazel_INTERFACE( Component )
{
public:

	typedef ContextKey key_type;

	virtual ~IComponent (void){}

	/**
	 * ��ʼ�����
	 * @param[ in,out ] ��ʼ��������
	 * ע�����������������һ���쳣
	 */
	virtual void initializeComponent( InitializeContext& context ) = 0;

	/**
	 * �������
	 */
	virtual void finalize( ) = 0;

	/**
	 * ȡ��������ڵ�����
	 */
    virtual IKernel&		kernel (void) = 0;
	
	/**
	 * ȡ�������Key
	 */
	virtual const key_type&		contextKey (void) const = 0;
	
	/**
	 * ȡ������ӿڵ�������Ϣ
	 */
	virtual const IComponentInformation&	componentInformation() const = 0;

	virtual const tstring& toString() const = 0;
};

typedef IComponent* ComponentPtr;
typedef const IComponent* ComponentConstPtr;

//<<<<<< INLINE PUBLIC FUNCTIONS                                        >>>>>>
//<<<<<< INLINE MEMBER FUNCTIONS                                        >>>>>>
//
//inline Component::Component (Context& context, ContextKey key)
//    : m_context (context)
//	, m_key ( key )
//{
//  COMPONENT_ASSERT ( m_key != ContextKey::KEY_NONE);
//  m_context.put (m_key, ComponentPtr( this ) );
//}
//
//inline Component::Component (Context& context, const std::string &key)
//    : m_context (context)
//	, m_key ( context.manager() , key )
//{
//  COMPONENT_ASSERT ( m_key != ContextKey::KEY_NONE);
//  m_context.put (m_key, ComponentPtr( this ) );
//}
//
//inline Component::~Component (void)
//{
//  COMPONENT_ASSERT ( m_key != ContextKey::KEY_NONE);
//}
//
//inline Context& Component::context (void) const
//{ return m_context; }
//
//inline const ContextKey& Component::contextKey (void) const
//{ return m_key; }

_micro_kernel_end

#endif // __Seal_Component_H__