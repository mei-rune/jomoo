


#ifndef DTDHANDLER_HPP
#define DTDHANDLER_HPP

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */



/**
 * @Brief DTDHandler 
 * <p>DTDHandler��������κ��ĵ��Ķ�����������ֻ��Ӧ�������͵��¼������������δ����
 * ����ʵ�������¼�</p>
 */
class DTDHandler
{
public:

    /** Destructor */
    virtual ~DTDHandler()
    {
    }

   
    
  /**
    * �����������Ϣ
    * @param[ in ] name ����.
    * @param[ in ] publicId ���ŵĹ�����ʶ�� ����Ϊ��
    * @param[ in ] systemId ���ŵ�ϵͳ��ʶ, ����Ϊ��
    * @remarks ע�⣬�������������
	*          <! NOTATION ISO3116 PUBLIC "ISO/IEC 3166:1933//NOTATION Code
	*                for the Representation of Language//EN" "ie3116" >
	* ������������notationDecl����ʹ������ֵ���źţ�
	* name ISO3116
    * publicId	"ISO/IEC 3166:1933//NOTATION Code
	*                for the Representation of Language//EN"
    * systemId "ie3116"
    * @see #unparsedEntityDecl
    * @see AttributeList#AttributeList
    */
	virtual void notationDecl
    (
        const   XMLCh* const    name
        , const XMLCh* const    publicId
        , const XMLCh* const    systemId
    ) = 0;

  /**
    * ����������ͬ��ĵ�δ����ʵ��������
    * <p><! ENTIRY myVRMLmap PUBLIC "..//Icelad/VRML map" "vrml/Iceland.vrml" NDATA vrml ></p>
    * @param[ in ] name δ����ʵ������.
    * @param[ in ] publicId ���ŵĹ�����ʶ�� ����Ϊ��
    * @param[ in ] systemId ���ŵ�ϵͳ��ʶ, ����Ϊ��
    * @param[ in ] notationName ��صķ�������.
    * @see #notationDecl
    * @see AttributeList#AttributeList
	* @remarks  ע�⣬�����ܵ����������ĸ��ַ�������ʽ���ֵ�--ÿһ���ַ�������һ�����֣���
	* <! NOTATION gif PUBLIC "-//Compuserve Information Service// NOTATION Graphics Interchange Format//EM">
    * <! ENTITY marylin SYSTEM "fabio/marylin.gif" NDATA gif>
	* <p>�����������²�������</p>
    * name marylin.
    * publicId NULL
    * systemId fabio/marylin.gif
    * notationName gif
    */
    virtual void unparsedEntityDecl
    (
        const   XMLCh* const    name
        , const XMLCh* const    publicId
        , const XMLCh* const    systemId
        , const XMLCh* const    notationName
    ) = 0;


    //virtual void resetDocType() = 0;



private :

    DTDHandler(const DTDHandler&);

    DTDHandler& operator=(const DTDHandler&);

};

} ///namespace UTIL

#endif
