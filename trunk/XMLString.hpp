

#if !defined(XMLSTRING_HPP)
#define XMLSTRING_HPP

#include <framework/XMLBuffer.hpp>
#include <framework/MemoryManager.hpp>
#include <string.h>

namespace XML
{

class XMLLCPTranscoder;


class XMLString
{
public:

	


	/**
	 * �����ַ���,��src�ַ�����ӵ�target�ַ���δβ
	 * @param[ in/out ] target ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] src ��"\0"��β��Դ�ַ���
	 * @remarks ע�⣬���뱣֤target�ַ������ڴ���й���
	 */
    static void catString
    (
                char* const     target
        , const char* const     src
    );

	/**
	 * �����ַ���,��src�ַ�����ӵ�target�ַ���δβ
	 * @param[ in/out ] target ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] src ��"\0"��β��Դ�ַ���
	 * @remarks ע�⣬���뱣֤target�ַ������ڴ���й���
	 */
    static void catString
    (
                XMLCh* const    target
        , const XMLCh* const    src
    );


	/**
	 * ���Դ�Сд�Ƚ��ַ�����
	 * @param[ in ] str1 ��"\0"��β���ַ���
	 * @param[ in ] str2 ��"\0"��β���ַ���
	 * @return ���ڷ���>0�����ڷ���0��С�ڷ���<0
	 * @remarks ע�⣬���Ǻ��Դ�С��
	 */
    static int compareIString
    (
        const   char* const     str1
        , const char* const     str2
    );

	/**
	 * ���Դ�Сд�Ƚ��ַ�����
	 * @param[ in ] str1 ��"\0"��β���ַ���
	 * @param[ in ] str2 ��"\0"��β���ַ���
	 * @return ���ڷ���>0�����ڷ���0��С�ڷ���<0
	 * @remarks ע�⣬���Ǻ��Դ�С��
	 */
    static int compareIString
    (
        const   XMLCh* const    str1
        , const XMLCh* const    str2
    );

	/**
	 * �Ƚ������ַ�����ǰn���ַ���
	 * @param[ in ] str1 ��"\0"��β���ַ���
	 * @param[ in ] str2 ��"\0"��β���ַ���
	 * @param[ in ] count �Ƚϵ��ַ�����
	 * @return ���ڷ���>0�����ڷ���0��С�ڷ���<0
	 */
    static int compareNString
    (
        const   char* const     str1
        , const char* const     str2
        , const unsigned int    count
    );


	/**
	 * �Ƚ������ַ�����ǰn���ַ���
	 * @param[ in ] str1 ��"\0"��β���ַ���
	 * @param[ in ] str2 ��"\0"��β���ַ���
	 * @param[ in ] count �Ƚϵ��ַ�����
	 * @return ���ڷ���>0�����ڷ���0��С�ڷ���<0
	 */
    static int compareNString
    (
        const   XMLCh* const    str1
        , const XMLCh* const    str2
        , const unsigned int    count
    );

	/**
	 * ���Դ�С�Ƚ������ַ�����ǰn���ַ���
	 * @param[ in ] str1 ��"\0"��β���ַ���
	 * @param[ in ] str2 ��"\0"��β���ַ���
	 * @param[ in ] count �Ƚϵ��ַ�����
	 * @return ���ڷ���>0�����ڷ���0��С�ڷ���<0
	 * @remarks ע�⣬���Ǻ��Դ�С��
	 */
    static int compareNIString
    (
        const   char* const     str1
        , const char* const     str2
        , const unsigned int    count
    );

	/**
	 * ���Դ�С�Ƚ������ַ�����ǰn���ַ���
	 * @param[ in ] str1 ��"\0"��β���ַ���
	 * @param[ in ] str2 ��"\0"��β���ַ���
	 * @param[ in ] count �Ƚϵ��ַ�����
	 * @return ���ڷ���>0�����ڷ���0��С�ڷ���<0
	 * @remarks ע�⣬���Ǻ��Դ�С��
	 */
    static int compareNIString
    (
        const   XMLCh* const    str1
        , const XMLCh* const    str2
        , const unsigned int    count
    );

    /**
	 * �Ƚ������ַ�����
	 * @param[ in ] str1 ��"\0"��β���ַ���
	 * @param[ in ] str2 ��"\0"��β���ַ���
	 * @return ���ڷ���>0�����ڷ���0��С�ڷ���<0
	 */
    static int compareString
    (
        const   char* const     str1
        , const char* const     str2
    );

    /**
	 * �Ƚ������ַ�����
	 * @param[ in ] str1 ��"\0"��β���ַ���
	 * @param[ in ] str2 ��"\0"��β���ַ���
	 * @return ���ڷ���>0�����ڷ���0��С�ڷ���<0
	 */
    static int compareString
    (
        const   XMLCh* const    str1
        , const XMLCh* const    str2
    );

     /**
	 * �Ƚ������ַ����Ƿ���ȡ�
	 * @param[ in ] str1 ��"\0"��β���ַ���
	 * @param[ in ] str2 ��"\0"��β���ַ���
	 * @return ���ڷ���true��С�ڷ���false
	 */
    static bool equals
    (
          const XMLCh* const    str1
        , const XMLCh* const    str2
    );

     /**
	 * �Ƚ������ַ����Ƿ���ȡ�
	 * @param[ in ] str1 ��"\0"��β���ַ���
	 * @param[ in ] str2 ��"\0"��β���ַ���
	 * @return ���ڷ���true��С�ڷ���false
	 */
    static bool equals
    (
          const char* const    str1
        , const char* const    str2
    );

	/**
	 * �Ƚ������ַ�����nλ���ǰn���ַ��Ƿ���ȣ�
	 * @param[ in ] str1 ��"\0"��β���ַ���
	 * @param[ in ] offset1 �ַ�1��ƫ��
	 * @param[ in ] str2 ��"\0"��β���ַ���
	 * @param[ in ] offset2 �ַ�2��ƫ��
	 * @param[ in ] charCount �Ƚϵ��ַ�����
	 * @return ���ڷ���true��С�ڷ���false
	 * @remarks ע�⣬���offset1��offset2С��0������false	 
	 */
    static bool regionMatches
    (
        const   XMLCh* const    str1
		, const	int				offset1
        , const XMLCh* const    str2
		, const int				offset2
		, const unsigned int	charCount
    );

	/**
	 * ���Դ�С�Ƚ������ַ�����nλ���ǰn���ַ��Ƿ���ȣ�
	 * @param[ in ] str1 ��"\0"��β���ַ���
	 * @param[ in ] offset1 �ַ�1��ƫ��
	 * @param[ in ] str2 ��"\0"��β���ַ���
	 * @param[ in ] offset2 �ַ�2��ƫ��
	 * @param[ in ] charCount �Ƚϵ��ַ�����
	 * @return ���ڷ���true��С�ڷ���false
	 * @remarks ע�⣬���offset1��offset2С��0������false	 
	 */
    static bool regionIMatches
    (
        const   XMLCh* const    str1
		, const	int				offset1
        , const XMLCh* const    str2
		, const int				offset2
		, const unsigned int	charCount
    );
    
	/**
	 * �����ַ���,��src�ַ���������target�ַ������ڴ��У�
	 * @param[ in/out ] target ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] src ��"\0"��β��Դ�ַ���
	 * @remarks ע�⣬���뱣֤target�ַ������ڴ���й��󣬽�����ԭ�����ַ���
	 */
    static void copyString
    (
                char* const     target
        , const char* const     src
    );

    /**
	 * �����ַ���,��src�ַ���������target�ַ������ڴ��У�
	 * @param[ in/out ] target ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] src ��"\0"��β��Դ�ַ���
	 * @remarks ע�⣬���뱣֤target�ַ������ڴ���й��󣬽�����ԭ�����ַ���
	 */
    static void copyString
    (
                XMLCh* const    target
        , const XMLCh* const    src
    );

    /**
	 * �����ַ���,��src�ַ�����ǰ�����ַ�������target�ַ������ڴ��У�
	 * @param[ in/out ] target ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] src ��"\0"��β��Դ�ַ���
	 * @remarks ע�⣬���뱣֤target�ַ������ڴ���й��󣬽�����ԭ�����ַ���
	 */
    static bool copyNString
    (
                XMLCh* const    target
        , const XMLCh* const    src
        , const unsigned int    maxChars
    );
    
    //static unsigned int hash
    //(
    //    const   char* const     toHash
    //    , const unsigned int    hashModulus
    //    , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
    //);

    //
    //static unsigned int hash
    //(
    //    const   XMLCh* const    toHash
    //    , const unsigned int    hashModulus
    //    , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
    //);

    //
    //static unsigned int hashN
    //(
    //    const   XMLCh* const    toHash
    //    , const unsigned int    numChars
    //    , const unsigned int    hashModulus
    //    , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    //);

    /**
	 * ��ָ�����ַ�����Ѱ��ָ�����ַ���λ��
	 * @param[ in ] toSearch ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] ch Ҫ���ҵ��ַ�
	 * @return �ҵ���������λ�ã����򷵻�-1
	 * @remarks ע�⣬���ص�λ���Ǵ�0��ʼ��
	 */
    static int indexOf(const char* const toSearch, const char ch);

    /**
	 * ��ָ�����ַ�����Ѱ��ָ�����ַ���λ��
	 * @param[ in ] toSearch ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] ch Ҫ���ҵ��ַ�
	 * @return �ҵ���������λ�ã����򷵻�-1
	 * @remarks ע�⣬���ص�λ���Ǵ�0��ʼ��
	 */
    static int indexOf(const XMLCh* const toSearch, const XMLCh ch);

	/**
	 * ��ָ�����ַ���ָ����λ�ÿ�ʼѰ��ָ�����ַ���λ��
	 * @param[ in ] toSearch ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] chToFind Ҫ���ҵ��ַ�
	 * @param[ in ] fromIndex �ַ�����ƫ��λ��
	 * @return �ҵ���������λ�ã����򷵻�-1
	 * @remarks ע�⣬���ص�λ���Ǵ�0��ʼ�ģ����fromIndex�����ַ������Ȼ�
	 * ����ArrayIndexOutOfBoundsException�쳣
	 */
    static int indexOf
    (
        const   char* const     toSearch
        , const char            chToFind
        , const unsigned int    fromIndex
    );

	/**
	 * ��ָ�����ַ���ָ����λ�ÿ�ʼѰ��ָ�����ַ���λ��
	 * @param[ in ] toSearch ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] chToFind Ҫ���ҵ��ַ�
	 * @param[ in ] fromIndex �ַ�����ƫ��λ��
	 * @return �ҵ���������λ�ã����򷵻�-1
	 * @remarks ע�⣬���ص�λ���Ǵ�0��ʼ�ģ����fromIndex�����ַ������Ȼ�
	 * ����ArrayIndexOutOfBoundsException�쳣
	 */
    static int indexOf
    (
        const   XMLCh* const    toSearch
        , const XMLCh           chToFind
        , const unsigned int    fromIndex
    );

    /**
	 * ��ָ�����ַ�����Ѱ��ָ�����ַ������ֵ�λ��
	 * @param[ in ] toSearch ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] ch Ҫ���ҵ��ַ�
	 * @return �ҵ���������λ�ã����򷵻�-1
	 * @remarks ע�⣬���ص�λ���Ǵ�0��ʼ��
	 */
    static int lastIndexOf(const char* const toSearch, const char ch);

    /**
	 * ��ָ�����ַ�����Ѱ��ָ�����ַ������ֵ�λ��
	 * @param[ in ] toSearch ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] ch Ҫ���ҵ��ַ�
	 * @return �ҵ���������λ�ã����򷵻�-1
	 * @remarks ע�⣬���ص�λ���Ǵ�0��ʼ��
	 */
    static int lastIndexOf(const XMLCh* const toSearch, const XMLCh ch);

    /**
	 * ��ָ�����ȵ��ַ�����Ѱ��ָ�����ַ������ֵ�λ��
	 * @param[ in ] ch Ҫ���ҵ��ַ�
	 * @param[ in ] toSearch Ŀ���ַ���
	 * @param[ in ] toSearchLen Ŀ���ַ����ĳ���
	 * @return �ҵ���������λ�ã����򷵻�-1
	 * @remarks ע�⣬���ص�λ���Ǵ�0��ʼ�ģ�Ŀ���ַ�Ҳ��һ������"0"��β��
	 */
    static int lastIndexOf
    (
        const XMLCh ch
        , const XMLCh* const toSearch
        , const unsigned int toSearchLen
    );

    /**
	 * ��ָ�����ȵ��ַ�����Ѱ��ָ�����ַ������ֵ�λ��
	 * @param[ in ] toSearch ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] chToFind Ҫ���ҵ��ַ�
	 * @param[ in ] fromIndex �ַ�����ƫ��λ��
	 * @return �ҵ���������λ�ã����򷵻�-1
	 * @remarks ע�⣬���ص�λ���Ǵ�0��ʼ�ģ����fromIndex�����ַ������Ȼ�
	 * ����ArrayIndexOutOfBoundsException�쳣
	 */
    static int lastIndexOf
    (
        const   char* const     toSearch
        , const char            chToFind
        , const unsigned int    fromIndex
    );

  //  /**
	 //* ��ָ�����ȵ��ַ�����Ѱ��ָ�����ַ������ֵ�λ��
	 //* @param[ in ] toSearch ��"\0"��β��Ŀ���ַ���
	 //* @param[ in ] ch Ҫ���ҵ��ַ�
	 //* @param[ in ] fromIndex �ַ�����ƫ��λ��
	 //* @return �ҵ���������λ�ã����򷵻�-1
	 //* @remarks ע�⣬���ص�λ���Ǵ�0��ʼ�ģ����fromIndex�����ַ������Ȼ�
	 //* ����ArrayIndexOutOfBoundsException�쳣
	 //*/
  //  static int lastIndexOf
  //  (
  //      const   XMLCh* const    toSearch
  //      , const XMLCh           ch
  //      , const unsigned int    fromIndex
  //  );
    
	/**
	 * ��Դ�ַ�������n���ַ���Ŀ���ַ�����ȥ
 	 * @param[ in/out ] targetStr ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] srcStr ��"\0"��β��Դ�ַ���
	 * @param[ in ] count ��Ҫ�������ַ�����
	 * @remarks ע�⣬���뱣֤targetStr�ַ������ڴ���й���
	 */
    static void moveChars
    (
                XMLCh* const    targetStr
        , const XMLCh* const    srcStr
        , const unsigned int    count
    );

   /**
	 * ��Դ�ַ�����ָ����ƫ�ƿ�ʼ����n���ַ���Ŀ���ַ�����ȥ
 	 * @param[ in/out ] targetStr ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] srcStr ��"\0"��β��Դ�ַ���
	 * @param[ in ] startIndex ��Ҫ������Դ�ַ�������ʼƫ����,��0��ʼ��
	 * @param[ in ] endIndex ��Ҫ������Դ�ַ����Ľ���ƫ��������0��ʼ��
	 * @remarks ע�⣬���뱣֤targetStr�ַ������ڴ���й���endIndex��
	 * startIndex������Ч�����������ӳ��쳣
	 */
    static void subString
    (
                char* const    targetStr
        , const char* const    srcStr
        , const int            startIndex
        , const int            endIndex
    );

    /**
	 * ��Դ�ַ�����ָ����ƫ�ƿ�ʼ����n���ַ���Ŀ���ַ�����ȥ
 	 * @param[ in/out ] targetStr ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] srcStr ��"\0"��β��Դ�ַ���
	 * @param[ in ] startIndex ��Ҫ������Դ�ַ�������ʼƫ����,��0��ʼ��
	 * @param[ in ] endIndex ��Ҫ������Դ�ַ����Ľ���ƫ��������0��ʼ��
	 * @remarks ע�⣬���뱣֤targetStr�ַ������ڴ���й���endIndex��
	 * startIndex������Ч�����������ӳ��쳣
	 */
    static void subString
    (
                XMLCh* const    targetStr
        , const XMLCh* const    srcStr
        , const int             startIndex
        , const int             endIndex
    );

    /**
	 * �����ַ���
	 * @param[ in ] toRep ��"\0"��β���ַ���
	 * @return ���ظ����ַ���
	 * @remarks ע�⣬��ʹ���귵�ص��ַ�����һ��Ҫ��release�ͷ�������
	 * ��ᷢ���ڴ�й©.
	 * @see release
	 */
    static char* replicate(const char* const toRep);

    /**
	 * ��ָ�����ڴ�����������ַ���
	 * @param[ in ] toRep ��"\0"��β���ַ���
	 * @param[ in ] manager �ڴ������
	 * @return ���ظ����ַ���
	 * @remarks ע�⣬��ʹ���귵�ص��ַ�����һ��Ҫ���ͷ�������
	 * ��ᷢ���ڴ�й©.
	 */
    static char* replicate(const char* const toRep );

        
	/**
	 * �����ַ���
	 * @param[ in ] toRep ��"\0"��β���ַ���
	 * @return ���ظ����ַ���
	 * @remarks ע�⣬��ʹ���귵�ص��ַ�����һ��Ҫ��release�ͷ�������
	 * ��ᷢ���ڴ�й©.
	 * @see release
	 */
    static XMLCh* replicate(const XMLCh* const toRep);

    /**
	 * ��ָ�����ڴ�����������ַ���
	 * @param[ in ] toRep ��"\0"��β���ַ���
	 * @param[ in ] manager �ڴ������
	 * @return ���ظ����ַ���
	 * @remarks ע�⣬��ʹ���귵�ص��ַ�����һ��Ҫ���ͷ�������
	 * ��ᷢ���ڴ�й©.
	 */
    static XMLCh* replicate(const XMLCh* const toRep );

    /**
	 * �ж�ָ�����ַ����ǲ��Ǵ�ָ����ǰ׺�ַ���Ϊ��ʼ��
	 * @param[ in ] toTest ��"\0"��β���ַ���
	 * @param[ in ] prefix ��"\0"��β��ǰ׺�ַ���
	 * @return ���Ը�ǰ׺�ַ�����ʼ�ķ���true,����false
	 */
    static bool startsWith
    (
        const   char* const     toTest
        , const char* const     prefix
    );

    /**
	 * �ж�ָ�����ַ����ǲ��Ǵ�ָ����ǰ׺�ַ���Ϊ��ʼ��
	 * @param[ in ] toTest ��"\0"��β���ַ���
	 * @param[ in ] prefix ��"\0"��β��ǰ׺�ַ���
	 * @return ���Ը�ǰ׺�ַ�����ʼ�ķ���true,����false
	 */
    static bool startsWith
    (
        const   XMLCh* const    toTest
        , const XMLCh* const    prefix
    );

    /**
	 * �ж�ָ�����ַ����ǲ��Ǵ�ָ����ǰ׺�ַ���Ϊ��ʼ��( ���Դ�Сд )
	 * @param[ in ] toTest ��"\0"��β���ַ���
	 * @param[ in ] prefix ��"\0"��β��ǰ׺�ַ���
	 * @return ���Ը�ǰ׺�ַ�����ʼ�ķ���true,����false
	 */
    static bool startsWithI
    (
        const   char* const     toTest
        , const char* const     prefix
    );

    /**
	 * �ж�ָ�����ַ����ǲ��Ǵ�ָ����ǰ׺�ַ���Ϊ��ʼ��( ���Դ�Сд )
	 * @param[ in ] toTest ��"\0"��β���ַ���
	 * @param[ in ] prefix ��"\0"��β��ǰ׺�ַ���
	 * @return ���Ը�ǰ׺�ַ�����ʼ�ķ���true,����false
	 */
    static bool startsWithI
    (
        const   XMLCh* const    toTest
        , const XMLCh* const    prefix
    );

    /**
	 * �ж�ָ�����ַ����ǲ��Ǵ�ָ���ĺ�׺�ַ���������
	 * @param[ in ] toTest ��"\0"��β���ַ���
	 * @param[ in ] suffix ��"\0"��β�ĺ�׺�ַ���
	 * @return ���Ըú�׺�ַ��������ķ���true,����false
	 */
    static bool endsWith
    (
        const   char* const    toTest
        , const char* const    suffix
    );

    /**
	 * �ж�ָ�����ַ����ǲ��Ǵ�ָ���ĺ�׺�ַ���������
	 * @param[ in ] toTest ��"\0"��β���ַ���
	 * @param[ in ] suffix ��"\0"��β�ĺ�׺�ַ���
	 * @return ���Ըú�׺�ַ��������ķ���true,����false
	 */
    static bool endsWith
    (
        const   XMLCh* const    toTest
        , const XMLCh* const    suffix
    );

    /**
	 * �ж�ָ�����ַ����ǲ��Ǵ�ָ���ĺ�׺�ַ���������( ���Դ�Сд )
	 * @param[ in ] toTest ��"\0"��β���ַ���
	 * @param[ in ] suffix ��"\0"��β�ĺ�׺�ַ���
	 * @return ���Ըú�׺�ַ��������ķ���true,����false
	 */
    static bool endsWithI
    (
        const   char* const    toTest
        , const char* const    suffix
    );

    /**
	 * �ж�ָ�����ַ����ǲ��Ǵ�ָ���ĺ�׺�ַ���������( ���Դ�Сд )
	 * @param[ in ] toTest ��"\0"��β���ַ���
	 * @param[ in ] suffix ��"\0"��β�ĺ�׺�ַ���
	 * @return ���Ըú�׺�ַ��������ķ���true,����false
	 */
    static bool endsWithI
    (
        const   XMLCh* const    toTest
        , const XMLCh* const    suffix
    );

    /**
	 * ��ָ�����ַ�����ʼѰ�ҵ���ָ���ַ���������һ���ַ���һ�η��ֵ�λ��
	 * @param[ in ] toSearch ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] searchList ��"\0"��β���ַ����ַ���
	 * @return �ҵ����ص�һ�η��ֵ�λ�õĵ�ַ�����򷵻�0
	 * @remarks ע�⣬���ﷵ�صĲ������������ǵ�ַ���õ�ַ������Ϊ�ַ����е�����һ��
	 */
    static const XMLCh* findAny
    (
        const   XMLCh* const    toSearch
        , const XMLCh* const    searchList
    );

    /**
	 * ��ָ�����ַ�����ʼѰ�ҵ���ָ���ַ���������һ���ַ���һ�η��ֵ�λ��
	 * @param[ in ] toSearch ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] searchList ��"\0"��β���ַ����ַ���
	 * @return �ҵ����ص�һ�η��ֵ�λ�õĵ�ַ�����򷵻�0
	 * @remarks ע�⣬���ﷵ�صĲ������������ǵ�ַ���õ�ַ������Ϊ�ַ����е�����һ��
	 */
    static XMLCh* findAny
    (
                XMLCh* const    toSearch
        , const XMLCh* const    searchList
    );

    /**
	 * ��ָ�����ַ���Ѱ�ҵ���ָ���ַ�����һ�η��ֵ�λ��
	 * @param[ in ] toSearch ��"\0"��β��Ŀ���ַ���
	 * @param[ in ] pattern ��"\0"��β��ƥ���ַ���
	 * @return �ҵ����ص�һ�η��ֵ�λ�ã����򷵻�-1
	 * @remarks ע�⣬��һ����������ܴ�����"aaaaab"��Ѱ��"aaaab"����
	 * ��������ȷ����
	 */
    static int patternMatch
    (
          const XMLCh* const    toSearch
        , const XMLCh* const    pattern
    );

	/**
	 * �����ַ����ĳ���
	 * @param[ in ] src ��"\0"��β��Ŀ���ַ���
	 * @return �����ַ����ĳ���
	 */
    static unsigned int stringLen(const char* const src);

	/**
	 * �����ַ����ĳ���
	 * @param[ in ] src ��"\0"��β��Ŀ���ַ���
	 * @return �����ַ����ĳ���
	 */
    static unsigned int stringLen(const XMLCh* const src);

    
    //static bool isValidNOTATION(const XMLCh*  const name );

    
    //static bool isValidNCName(const XMLCh* const name);

    //
    //static bool isValidName(const XMLCh* const name);

   
    //static bool isValidEncName(const XMLCh* const name);

    //
    //static bool isValidQName(const XMLCh* const name);


	/**
	 * �ж�ָ�����ַ��ǲ���һ����ĸ�ַ�
	 * @param[ in ] theChar �ַ�
	 * @return �Ƿ���true,���Ƿ���һ��false
	 * @remarks ע�����ķ�ΧΪ "a"��"z", "A"��"Z"
	 */
    static bool isAlpha(XMLCh const theChar);

	/**
	 * �ж�ָ�����ַ��ǲ���һ�������ַ�
	 * @param[ in ] theChar �ַ�
	 * @return �Ƿ���true,���Ƿ���һ��false
	 * @remarks ע�����ķ�ΧΪ "0"��"9"
	 */
    static bool isDigit(XMLCh const theChar);

	/**
	 * �ж�ָ�����ַ��ǲ���һ�������ַ���һ����ĸ�ַ�
	 * @param[ in ] theChar �ַ�
	 * @return �Ƿ���true,���Ƿ���һ��false
	 * @remarks ע�����ķ�ΧΪ "a"��"z", "A"��"Z","0"��"9",
	 */
    static bool isAlphaNum(XMLCh const theChar);

	/**
	 * �ж�ָ�����ַ��ǲ���һ��16���Ƶı���
	 * @param[ in ] theChar �ַ�
	 * @return �Ƿ���true,���Ƿ���һ��false
	 * @remarks ע�����ķ�ΧΪ "a"��"f", "A"��"F","0"��"9",
	 */
    static bool isHex(XMLCh const theChar);

	/**
	 * �ж�ָ�����ַ����ǲ���ȫ���ǿհ׷�
	 * @param[ in ] theChar �ַ�
	 * @return �Ƿ���true,���Ƿ���һ��false
	 */
    static bool isAllWhiteSpace(const XMLCh* const toCheck);

    /**
	 * �ж�ָ����ƥ���ַ����ǲ��ǰ�����ָ��Ŀ���ַ�����
	 * @param[ in ] toFind ��"\0"��β��ƥ���ַ���
	 * @param[ in ] enumList ��"\0"��β��Ŀ���ַ���
	 * @return �ҵ����ص�һ�η��ֵ�λ�ã����򷵻�false
	 * @remarks ע�⣬���ܹ���ȷ������"aaaaab"��Ѱ��"aaaab"�����
	 */
    static bool isInList(const XMLCh* const toFind, const XMLCh* const enumList);

    /**
	 * ��ָ���ĵ���ֵת��Ϊһ���ַ���
	 * @param[ in ] toFormat ָ������ֵ
	 * @param[ out ] toFill ת�������Ļ����
	 * @param[ in ] maxChars ���Ļ����Ĵ�С
	 * @param[ in ] radix ת���Ľ���
	 * @remarks ע�⣬����֧��2,8,10,16���Ƶ�ת����
	 */
    static void binToText
    (
        const   unsigned int    toFormat
        ,       char* const     toFill
        , const unsigned int    maxChars
        , const unsigned int    radix
    );

    /**
	 * ��ָ���ĵ���ֵת��Ϊһ���ַ���
	 * @param[ in ] toFormat ָ������ֵ
	 * @param[ out ] toFill ת�������Ļ����
	 * @param[ in ] maxChars ���Ļ����Ĵ�С
	 * @param[ in ] radix ת���Ľ���
	 * @remarks ע�⣬����֧��2,8,10,16���Ƶ�ת����
	 */
    static void binToText
    (
        const   unsigned int    toFormat
        ,       XMLCh* const    toFill
        , const unsigned int    maxChars
        , const unsigned int    radix
    );

    /**
	 * ��ָ���ĵ���ֵת��Ϊһ���ַ���
	 * @param[ in ] toFormat ָ������ֵ
	 * @param[ out ] toFill ת�������Ļ����
	 * @param[ in ] maxChars ���Ļ����Ĵ�С
	 * @param[ in ] radix ת���Ľ���
	 * @remarks ע�⣬����֧��2,8,10,16���Ƶ�ת����
	 */
    static void binToText
    (
        const   unsigned long   toFormat
        ,       char* const     toFill
        , const unsigned int    maxChars
        , const unsigned int    radix
    );

    /**
	 * ��ָ���ĵ���ֵת��Ϊһ���ַ���
	 * @param[ in ] toFormat ָ������ֵ
	 * @param[ out ] toFill ת�������Ļ����
	 * @param[ in ] maxChars ���Ļ����Ĵ�С
	 * @param[ in ] radix ת���Ľ���
	 * @remarks ע�⣬����֧��2,8,10,16���Ƶ�ת����
	 */
    static void binToText
    (
        const   unsigned long   toFormat
        ,       XMLCh* const    toFill
        , const unsigned int    maxChars
        , const unsigned int    radix
    );

    /**
	 * ��ָ���ĵ���ֵת��Ϊһ���ַ���
	 * @param[ in ] toFormat ָ������ֵ
	 * @param[ out ] toFill ת�������Ļ����
	 * @param[ in ] maxChars ���Ļ����Ĵ�С
	 * @param[ in ] radix ת���Ľ���
	 * @remarks ע�⣬����֧��2,8,10,16���Ƶ�ת����
	 */
    static void binToText
    (
        const   long            toFormat
        ,       char* const     toFill
        , const unsigned int    maxChars
        , const unsigned int    radix
    );

    /**
	 * ��ָ���ĵ���ֵת��Ϊһ���ַ���
	 * @param[ in ] toFormat ָ������ֵ
	 * @param[ out ] toFill ת�������Ļ����
	 * @param[ in ] maxChars ���Ļ����Ĵ�С
	 * @param[ in ] radix ת���Ľ���
	 * @remarks ע�⣬����֧��2,8,10,16���Ƶ�ת����
	 */
    static void binToText
    (
        const   long            toFormat
        ,       XMLCh* const    toFill
        , const unsigned int    maxChars
        , const unsigned int    radix
    );

    /**
	 * ��ָ���ĵ���ֵת��Ϊһ���ַ���
	 * @param[ in ] toFormat ָ������ֵ
	 * @param[ out ] toFill ת�������Ļ����
	 * @param[ in ] maxChars ���Ļ����Ĵ�С
	 * @param[ in ] radix ת���Ľ���
	 * @remarks ע�⣬����֧��2,8,10,16���Ƶ�ת����
	 */
    static void binToText
    (
        const   int             toFormat
        ,       char* const     toFill
        , const unsigned int    maxChars
        , const unsigned int    radix
    );

    /**
	 * ��ָ���ĵ���ֵת��Ϊһ���ַ���
	 * @param[ in ] toFormat ָ������ֵ
	 * @param[ out ] toFill ת�������Ļ����
	 * @param[ in ] maxChars ���Ļ����Ĵ�С
	 * @param[ in ] radix ת���Ľ���
	 * @remarks ע�⣬����֧��2,8,10,16���Ƶ�ת����
	 */
    static void binToText
    (
        const   int             toFormat
        ,       XMLCh* const    toFill
        , const unsigned int    maxChars
        , const unsigned int    radix
    );

    /**
	 * ��ָ���ĵ��ַ���ת��Ϊһ����ֵ
	 * @param[ in ] toConvert ָ������"\0"��β���ַ���
	 * @param[ out ] toFill ת������ֵ
	 * @return �ɹ�����true,���򷵻�false 
	 * @remarks ע�⣬����֧��10���Ƶ�ת����
	 */
    static bool textToBin
    (
        const   XMLCh* const    toConvert
        ,       unsigned int&   toFill
    );

    /**
	 * ��ָ���ĵ��ַ���ת��Ϊһ����ֵ
	 * @param[ in ] toConvert ָ������"\0"��β���ַ���
	 * @return ����ת������ֵ
	 * @remarks ע�⣬����֧��10���Ƶ�ת��,���ʧ�������ӳ�һ���쳣��
	 */
    static int parseInt
    (
        const   XMLCh* const    toConvert
    );

    /**
	 * ��ָ�����ַ���ǰn���ַ�ɾ������������ַ����ƶ���ǰ��
	 * @param[ in ] toCutFrom ָ������"\0"��β���ַ���
	 * @param[ in ] count ָ�����ַ�����
	 * @return ���Ĺ���������
	 */
    static void cut
    (
                XMLCh* const    toCutFrom
        , const unsigned int    count
    );

    
    static char* transcode
    (
        const   XMLCh* const    toTranscode
    );
    static char* transcode
    (
        const   XMLCh* const         toTranscode
        ,       MemoryManager* const manager
    );

    
    static bool transcode
    (
        const   XMLCh* const    toTranscode
        ,       char* const     toFill
        , const unsigned int    maxChars
    );

    
    static XMLCh* transcode
    (
        const   char* const     toTranscode
    );
    static XMLCh* transcode
    (
        const   char* const          toTranscode
    );

    
    static bool transcode
    (
        const   char* const     toTranscode
        ,       XMLCh* const    toFill
        , const unsigned int    maxChars
    );

    /**
	 * ȥ���ַ������ߵĿո�
	 * @param[ in ] toTrim ��"\0"��β���ַ���
	 */
    static void trim(char* const toTrim);

    /**
	 * ȥ���ַ������ߵĿո�
	 * @param[ in ] toTrim ��"\0"��β���ַ���
	 */
    static void trim(XMLCh* const toTrim);

    
    static BaseRefVectorOf<XMLCh>* tokenizeString(const XMLCh* const tokenizeSrc );

    
    static XMLCh* makeUName
    (
        const   XMLCh* const    pszURI
        , const XMLCh* const    pszName      
    );

    /**
	 * ��maxChars�е�{0}��{1��}{2}��{3}�ַ����滻��text1��text2��text3��text4
	 * @param[ in/out ] errText ��"\0"��β�Ĵ��滻���ַ���
	 * @param[ in ] maxChars errText�ڴ��Ĵ�С
	 * @param[ in ] text1 ��"\0"��β���ַ���
	 * @param[ in ] text2 ��"\0"��β���ַ���
	 * @param[ in ] text3 ��"\0"��β���ַ���
	 * @param[ in ] text4 ��"\0"��β���ַ���
	 * @return �������ַ����Ĵ�С
	 * @remarks ���errText̫С���Ϳ��ܻᱻ�滻����
	 */
    static size_t replaceTokens
    (
                XMLCh* const    errText
        , size_t    maxChars
        , const XMLCh* const    text1
        , const XMLCh* const    text2
        , const XMLCh* const    text3
        , const XMLCh* const    text4
	);

    
    static void upperCase(XMLCh* const toUpperCase);

	
    static void lowerCase(XMLCh* const toLowerCase);

	
    static bool isWSReplaced(const XMLCh* const toCheck);

	
    static bool isWSCollapsed(const XMLCh* const toCheck);

	
    static void replaceWS(XMLCh* const toConvert
		);

	
    static void collapseWS(XMLCh* const toConvert
		);

    
    static void removeWS(XMLCh* const toConvert);


    
    static void removeChar(const XMLCh*     const srcString
                         , const XMLCh&           toRemove
                         ,       XMLBuffer&       dstBuffer);

    
    static void fixURI(const XMLCh* const str, XMLCh* const target);

    
	/**
	 * �ͷ�ָ�����ַ����ռ�
	 * @param[ in ] buf �ַ����ռ�
	 */
    static void release(char** buf);

	/**
	 * �ͷ�ָ�����ַ����ռ�
	 * @param[ in ] buf �ַ����ռ�
	 */
    static void release(XMLCh** buf);

	/**
	 * �ͷ�ָ�����ַ����ռ�
	 * @param[ in ] buf �ַ����ռ�
	 */
    static void release(XMLByte** buf);

private :

    XMLString();

    ~XMLString();
    
    static void initString(XMLLCPTranscoder* const defToUse,
                           MemoryManager* const manager);
    static void termString();
    
	static bool validateRegion(const XMLCh* const str1, const int offset1,
						const XMLCh* const str2, const int offset2,
						const unsigned int charCount);

    static MemoryManager* fgMemoryManager;

    friend class XMLPlatformUtils;
};


inline void XMLString::moveChars(       XMLCh* const targetStr
                                , const XMLCh* const srcStr
                                , const unsigned int count)
{
    memcpy(targetStr, srcStr, count * sizeof(XMLCh));
}

inline unsigned int XMLString::stringLen(const XMLCh* const src)
{
    if (src == 0 || *src == 0)
    {
        return 0;
   }
    else
   {
        const XMLCh* pszTmp = src + 1;

        while (*pszTmp)
            ++pszTmp;

        return (unsigned int)(pszTmp - src);
    }
}

inline XMLCh* XMLString::replicate(const XMLCh* const toRep,
                                   MemoryManager* const manager)
{
    // If a null string, return a null string!
    XMLCh* ret = 0;
    if (toRep)
    {
        const unsigned int len = stringLen(toRep);
        ret = (XMLCh*) manager->allocate((len+1) * sizeof(XMLCh)); //new XMLCh[len + 1];
        memcpy(ret, toRep, (len + 1) * sizeof(XMLCh));
    }
    return ret;
}

inline bool XMLString::startsWith(  const   XMLCh* const    toTest
                                    , const XMLCh* const    prefix)
{
    return (compareNString(toTest, prefix, stringLen(prefix)) == 0);
}

inline bool XMLString::startsWithI( const   XMLCh* const    toTest
                                    , const XMLCh* const    prefix)
{
    return (compareNIString(toTest, prefix, stringLen(prefix)) == 0);
}

inline bool XMLString::endsWith(const char* const toTest,
                                const char* const suffix)
{

    unsigned int suffixLen = XMLString::stringLen(suffix);

    return regionMatches(toTest, XMLString::stringLen(toTest) - suffixLen,
                         suffix, 0, suffixLen);
}

inline bool XMLString::endsWith(const XMLCh* const toTest,
                                const XMLCh* const suffix)
{

    unsigned int suffixLen = XMLString::stringLen(suffix);

    return regionMatches(toTest, XMLString::stringLen(toTest) - suffixLen,
                         suffix, 0, suffixLen);
}

inline bool XMLString::endsWithI(const char* const toTest,
                                const char* const suffix)
{

    unsigned int suffixLen = XMLString::stringLen(suffix);

    return regionIMatches(toTest, XMLString::stringLen(toTest) - suffixLen,
                         suffix, 0, suffixLen);
}

inline bool XMLString::endsWithI(const XMLCh* const toTest,
                                const XMLCh* const suffix)
{

    unsigned int suffixLen = XMLString::stringLen(suffix);

    return regionIMatches(toTest, XMLString::stringLen(toTest) - suffixLen,
                         suffix, 0, suffixLen);
}

inline bool XMLString::validateRegion(const XMLCh* const str1,
									  const int offset1,
									  const XMLCh* const str2,
									  const int offset2,
									  const unsigned int charCount)
{

	if (offset1 < 0 || offset2 < 0 ||
		(offset1 + charCount) > XMLString::stringLen(str1) ||
		(offset2 + charCount) > XMLString::stringLen(str2) )
		return false;

	return true;
}

inline bool XMLString::equals(   const XMLCh* const    str1
                               , const XMLCh* const    str2)
{
    const XMLCh* psz1 = str1;
    const XMLCh* psz2 = str2;

    if (psz1 == 0 || psz2 == 0) {
        if ((psz1 != 0 && *psz1) || (psz2 != 0 && *psz2))
            return false;
        else
            return true;
    }

    while (*psz1 == *psz2)
    {
        // If either has ended, then they both ended, so equal
        if (!*psz1)
            return true;

        // Move upwards for the next round
        psz1++;
        psz2++;
    }
    return false;
}

inline bool XMLString::equals(   const char* const    str1
                               , const char* const    str2)
{
    const char* psz1 = str1;
    const char* psz2 = str2;

    if (psz1 == 0 || psz2 == 0) {
        if ((psz1 != 0 && *psz1) || (psz2 != 0 && *psz2))
            return false;
        else
            return true;
    }

    while (*psz1 == *psz2)
    {
        // If either has ended, then they both ended, so equal
        if (!*psz1)
            return true;

        // Move upwards for the next round
        psz1++;
        psz2++;
    }
    return false;
}

inline int XMLString::lastIndexOf(const XMLCh* const toSearch, const XMLCh ch)
{
    return XMLString::lastIndexOf(ch, toSearch, stringLen(toSearch));
}

} ///namespace UTIL

#endif
