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
 * 所有组件的接口
 * 每一种组件都有一个唯一的标识符，组件标识用是一个以'/'字符分隔的字符串
 * 如	"SEAL/Kernel/Component/ComponentLoader"
 *		"SEAL/Kernel/ComponentService/ServiceLoader"
 * 其中 SEAL/Kernel/Component 和 SEAL/Kernel/ComponentService 称为类别名
 * 不过注意同类别的接口不一定是从同一个接口继承下来的。
 */
class IComponent	Hazel_INTERFACE( Component )
{
public:

	typedef ContextKey key_type;

	virtual ~IComponent (void){}

	/**
	 * 初始化组件
	 * @param[ in,out ] 初始化上下文
	 * 注意如果发生错误请扔一个异常
	 */
	virtual void initializeComponent( InitializeContext& context ) = 0;

	/**
	 * 销毁组件
	 */
	virtual void finalize( ) = 0;

	/**
	 * 取得组件所在的容器
	 */
    virtual IKernel&		kernel (void) = 0;
	
	/**
	 * 取得组件的Key
	 */
	virtual const key_type&		contextKey (void) const = 0;
	
	/**
	 * 取得组件接口的类型信息
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
