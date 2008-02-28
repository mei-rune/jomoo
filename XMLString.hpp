

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
	 * 连接字符串,将src字符串添加到target字符串未尾
	 * @param[ in/out ] target 以"\0"结尾的目标字符串
	 * @param[ in ] src 以"\0"结尾的源字符串
	 * @remarks 注意，必须保证target字符串的内存块中够大
	 */
    static void catString
    (
                char* const     target
        , const char* const     src
    );

	/**
	 * 连接字符串,将src字符串添加到target字符串未尾
	 * @param[ in/out ] target 以"\0"结尾的目标字符串
	 * @param[ in ] src 以"\0"结尾的源字符串
	 * @remarks 注意，必须保证target字符串的内存块中够大
	 */
    static void catString
    (
                XMLCh* const    target
        , const XMLCh* const    src
    );


	/**
	 * 忽略大小写比较字符串，
	 * @param[ in ] str1 以"\0"结尾的字符串
	 * @param[ in ] str2 以"\0"结尾的字符串
	 * @return 大于返回>0，等于返回0，小于返回<0
	 * @remarks 注意，它是忽略大小的
	 */
    static int compareIString
    (
        const   char* const     str1
        , const char* const     str2
    );

	/**
	 * 忽略大小写比较字符串，
	 * @param[ in ] str1 以"\0"结尾的字符串
	 * @param[ in ] str2 以"\0"结尾的字符串
	 * @return 大于返回>0，等于返回0，小于返回<0
	 * @remarks 注意，它是忽略大小的
	 */
    static int compareIString
    (
        const   XMLCh* const    str1
        , const XMLCh* const    str2
    );

	/**
	 * 比较两个字符串的前n个字符，
	 * @param[ in ] str1 以"\0"结尾的字符串
	 * @param[ in ] str2 以"\0"结尾的字符串
	 * @param[ in ] count 比较的字符个数
	 * @return 大于返回>0，等于返回0，小于返回<0
	 */
    static int compareNString
    (
        const   char* const     str1
        , const char* const     str2
        , const unsigned int    count
    );


	/**
	 * 比较两个字符串的前n个字符，
	 * @param[ in ] str1 以"\0"结尾的字符串
	 * @param[ in ] str2 以"\0"结尾的字符串
	 * @param[ in ] count 比较的字符个数
	 * @return 大于返回>0，等于返回0，小于返回<0
	 */
    static int compareNString
    (
        const   XMLCh* const    str1
        , const XMLCh* const    str2
        , const unsigned int    count
    );

	/**
	 * 忽略大小比较两个字符串的前n个字符，
	 * @param[ in ] str1 以"\0"结尾的字符串
	 * @param[ in ] str2 以"\0"结尾的字符串
	 * @param[ in ] count 比较的字符个数
	 * @return 大于返回>0，等于返回0，小于返回<0
	 * @remarks 注意，它是忽略大小的
	 */
    static int compareNIString
    (
        const   char* const     str1
        , const char* const     str2
        , const unsigned int    count
    );

	/**
	 * 忽略大小比较两个字符串的前n个字符，
	 * @param[ in ] str1 以"\0"结尾的字符串
	 * @param[ in ] str2 以"\0"结尾的字符串
	 * @param[ in ] count 比较的字符个数
	 * @return 大于返回>0，等于返回0，小于返回<0
	 * @remarks 注意，它是忽略大小的
	 */
    static int compareNIString
    (
        const   XMLCh* const    str1
        , const XMLCh* const    str2
        , const unsigned int    count
    );

    /**
	 * 比较两个字符串。
	 * @param[ in ] str1 以"\0"结尾的字符串
	 * @param[ in ] str2 以"\0"结尾的字符串
	 * @return 大于返回>0，等于返回0，小于返回<0
	 */
    static int compareString
    (
        const   char* const     str1
        , const char* const     str2
    );

    /**
	 * 比较两个字符串。
	 * @param[ in ] str1 以"\0"结尾的字符串
	 * @param[ in ] str2 以"\0"结尾的字符串
	 * @return 大于返回>0，等于返回0，小于返回<0
	 */
    static int compareString
    (
        const   XMLCh* const    str1
        , const XMLCh* const    str2
    );

     /**
	 * 比较两个字符串是否相等。
	 * @param[ in ] str1 以"\0"结尾的字符串
	 * @param[ in ] str2 以"\0"结尾的字符串
	 * @return 等于返回true，小于返回false
	 */
    static bool equals
    (
          const XMLCh* const    str1
        , const XMLCh* const    str2
    );

     /**
	 * 比较两个字符串是否相等。
	 * @param[ in ] str1 以"\0"结尾的字符串
	 * @param[ in ] str2 以"\0"结尾的字符串
	 * @return 等于返回true，小于返回false
	 */
    static bool equals
    (
          const char* const    str1
        , const char* const    str2
    );

	/**
	 * 比较两个字符串从n位起的前n个字符是否相等，
	 * @param[ in ] str1 以"\0"结尾的字符串
	 * @param[ in ] offset1 字符1的偏移
	 * @param[ in ] str2 以"\0"结尾的字符串
	 * @param[ in ] offset2 字符2的偏移
	 * @param[ in ] charCount 比较的字符个数
	 * @return 等于返回true，小于返回false
	 * @remarks 注意，如果offset1和offset2小于0，返回false	 
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
	 * 忽略大小比较两个字符串从n位起的前n个字符是否相等，
	 * @param[ in ] str1 以"\0"结尾的字符串
	 * @param[ in ] offset1 字符1的偏移
	 * @param[ in ] str2 以"\0"结尾的字符串
	 * @param[ in ] offset2 字符2的偏移
	 * @param[ in ] charCount 比较的字符个数
	 * @return 等于返回true，小于返回false
	 * @remarks 注意，如果offset1和offset2小于0，返回false	 
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
	 * 拷贝字符串,将src字符串拷贝到target字符串的内存中，
	 * @param[ in/out ] target 以"\0"结尾的目标字符串
	 * @param[ in ] src 以"\0"结尾的源字符串
	 * @remarks 注意，必须保证target字符串的内存块中够大，将覆盖原来的字符。
	 */
    static void copyString
    (
                char* const     target
        , const char* const     src
    );

    /**
	 * 拷贝字符串,将src字符串拷贝到target字符串的内存中，
	 * @param[ in/out ] target 以"\0"结尾的目标字符串
	 * @param[ in ] src 以"\0"结尾的源字符串
	 * @remarks 注意，必须保证target字符串的内存块中够大，将覆盖原来的字符。
	 */
    static void copyString
    (
                XMLCh* const    target
        , const XMLCh* const    src
    );

    /**
	 * 拷贝字符串,将src字符串的前几个字符拷贝到target字符串的内存中，
	 * @param[ in/out ] target 以"\0"结尾的目标字符串
	 * @param[ in ] src 以"\0"结尾的源字符串
	 * @remarks 注意，必须保证target字符串的内存块中够大，将覆盖原来的字符。
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
	 * 在指定的字符串中寻找指定的字符的位置
	 * @param[ in ] toSearch 以"\0"结尾的目标字符串
	 * @param[ in ] ch 要查找的字符
	 * @return 找到返回它的位置，否则返回-1
	 * @remarks 注意，返回的位置是从0开始的
	 */
    static int indexOf(const char* const toSearch, const char ch);

    /**
	 * 在指定的字符串中寻找指定的字符的位置
	 * @param[ in ] toSearch 以"\0"结尾的目标字符串
	 * @param[ in ] ch 要查找的字符
	 * @return 找到返回它的位置，否则返回-1
	 * @remarks 注意，返回的位置是从0开始的
	 */
    static int indexOf(const XMLCh* const toSearch, const XMLCh ch);

	/**
	 * 从指定的字符串指定的位置开始寻找指定的字符的位置
	 * @param[ in ] toSearch 以"\0"结尾的目标字符串
	 * @param[ in ] chToFind 要查找的字符
	 * @param[ in ] fromIndex 字符串的偏移位置
	 * @return 找到返回它的位置，否则返回-1
	 * @remarks 注意，返回的位置是从0开始的，如果fromIndex大于字符串长度会
	 * 发生ArrayIndexOutOfBoundsException异常
	 */
    static int indexOf
    (
        const   char* const     toSearch
        , const char            chToFind
        , const unsigned int    fromIndex
    );

	/**
	 * 从指定的字符串指定的位置开始寻找指定的字符的位置
	 * @param[ in ] toSearch 以"\0"结尾的目标字符串
	 * @param[ in ] chToFind 要查找的字符
	 * @param[ in ] fromIndex 字符串的偏移位置
	 * @return 找到返回它的位置，否则返回-1
	 * @remarks 注意，返回的位置是从0开始的，如果fromIndex大于字符串长度会
	 * 发生ArrayIndexOutOfBoundsException异常
	 */
    static int indexOf
    (
        const   XMLCh* const    toSearch
        , const XMLCh           chToFind
        , const unsigned int    fromIndex
    );

    /**
	 * 从指定的字符串中寻找指定的字符最后出现的位置
	 * @param[ in ] toSearch 以"\0"结尾的目标字符串
	 * @param[ in ] ch 要查找的字符
	 * @return 找到返回它的位置，否则返回-1
	 * @remarks 注意，返回的位置是从0开始的
	 */
    static int lastIndexOf(const char* const toSearch, const char ch);

    /**
	 * 从指定的字符串中寻找指定的字符最后出现的位置
	 * @param[ in ] toSearch 以"\0"结尾的目标字符串
	 * @param[ in ] ch 要查找的字符
	 * @return 找到返回它的位置，否则返回-1
	 * @remarks 注意，返回的位置是从0开始的
	 */
    static int lastIndexOf(const XMLCh* const toSearch, const XMLCh ch);

    /**
	 * 从指定长度的字符串中寻找指定的字符最后出现的位置
	 * @param[ in ] ch 要查找的字符
	 * @param[ in ] toSearch 目标字符串
	 * @param[ in ] toSearchLen 目标字符串的长度
	 * @return 找到返回它的位置，否则返回-1
	 * @remarks 注意，返回的位置是从0开始的，目标字符也不一定是以"0"结尾的
	 */
    static int lastIndexOf
    (
        const XMLCh ch
        , const XMLCh* const toSearch
        , const unsigned int toSearchLen
    );

    /**
	 * 从指定长度的字符串中寻找指定的字符最后出现的位置
	 * @param[ in ] toSearch 以"\0"结尾的目标字符串
	 * @param[ in ] chToFind 要查找的字符
	 * @param[ in ] fromIndex 字符串的偏移位置
	 * @return 找到返回它的位置，否则返回-1
	 * @remarks 注意，返回的位置是从0开始的，如果fromIndex大于字符串长度会
	 * 发生ArrayIndexOutOfBoundsException异常
	 */
    static int lastIndexOf
    (
        const   char* const     toSearch
        , const char            chToFind
        , const unsigned int    fromIndex
    );

  //  /**
	 //* 从指定长度的字符串中寻找指定的字符最后出现的位置
	 //* @param[ in ] toSearch 以"\0"结尾的目标字符串
	 //* @param[ in ] ch 要查找的字符
	 //* @param[ in ] fromIndex 字符串的偏移位置
	 //* @return 找到返回它的位置，否则返回-1
	 //* @remarks 注意，返回的位置是从0开始的，如果fromIndex大于字符串长度会
	 //* 发生ArrayIndexOutOfBoundsException异常
	 //*/
  //  static int lastIndexOf
  //  (
  //      const   XMLCh* const    toSearch
  //      , const XMLCh           ch
  //      , const unsigned int    fromIndex
  //  );
    
	/**
	 * 将源字符串拷贝n个字符到目标字符串中去
 	 * @param[ in/out ] targetStr 以"\0"结尾的目标字符串
	 * @param[ in ] srcStr 以"\0"结尾的源字符串
	 * @param[ in ] count 需要拷贝的字符个数
	 * @remarks 注意，必须保证targetStr字符串的内存块中够大
	 */
    static void moveChars
    (
                XMLCh* const    targetStr
        , const XMLCh* const    srcStr
        , const unsigned int    count
    );

   /**
	 * 将源字符串从指定的偏移开始拷贝n个字符到目标字符串中去
 	 * @param[ in/out ] targetStr 以"\0"结尾的目标字符串
	 * @param[ in ] srcStr 以"\0"结尾的源字符串
	 * @param[ in ] startIndex 需要拷贝的源字符串的起始偏移量,从0开始的
	 * @param[ in ] endIndex 需要拷贝的源字符串的结束偏移量，从0开始的
	 * @remarks 注意，必须保证targetStr字符串的内存块中够大，endIndex和
	 * startIndex必须有效，否则它将扔出异常
	 */
    static void subString
    (
                char* const    targetStr
        , const char* const    srcStr
        , const int            startIndex
        , const int            endIndex
    );

    /**
	 * 将源字符串从指定的偏移开始拷贝n个字符到目标字符串中去
 	 * @param[ in/out ] targetStr 以"\0"结尾的目标字符串
	 * @param[ in ] srcStr 以"\0"结尾的源字符串
	 * @param[ in ] startIndex 需要拷贝的源字符串的起始偏移量,从0开始的
	 * @param[ in ] endIndex 需要拷贝的源字符串的结束偏移量，从0开始的
	 * @remarks 注意，必须保证targetStr字符串的内存块中够大，endIndex和
	 * startIndex必须有效，否则它将扔出异常
	 */
    static void subString
    (
                XMLCh* const    targetStr
        , const XMLCh* const    srcStr
        , const int             startIndex
        , const int             endIndex
    );

    /**
	 * 复制字符串
	 * @param[ in ] toRep 以"\0"结尾的字符串
	 * @return 返回复制字符串
	 * @remarks 注意，在使用完返回的字符串后，一定要用release释放它，否
	 * 则会发生内存泄漏.
	 * @see release
	 */
    static char* replicate(const char* const toRep);

    /**
	 * 用指定的内存分配器复制字符串
	 * @param[ in ] toRep 以"\0"结尾的字符串
	 * @param[ in ] manager 内存分配器
	 * @return 返回复制字符串
	 * @remarks 注意，在使用完返回的字符串后，一定要用释放它，否
	 * 则会发生内存泄漏.
	 */
    static char* replicate(const char* const toRep );

        
	/**
	 * 复制字符串
	 * @param[ in ] toRep 以"\0"结尾的字符串
	 * @return 返回复制字符串
	 * @remarks 注意，在使用完返回的字符串后，一定要用release释放它，否
	 * 则会发生内存泄漏.
	 * @see release
	 */
    static XMLCh* replicate(const XMLCh* const toRep);

    /**
	 * 用指定的内存分配器复制字符串
	 * @param[ in ] toRep 以"\0"结尾的字符串
	 * @param[ in ] manager 内存分配器
	 * @return 返回复制字符串
	 * @remarks 注意，在使用完返回的字符串后，一定要用释放它，否
	 * 则会发生内存泄漏.
	 */
    static XMLCh* replicate(const XMLCh* const toRep );

    /**
	 * 判断指定的字符串是不是从指定的前缀字符串为开始的
	 * @param[ in ] toTest 以"\0"结尾的字符串
	 * @param[ in ] prefix 以"\0"结尾的前缀字符串
	 * @return 是以该前缀字符串开始的返回true,否则返false
	 */
    static bool startsWith
    (
        const   char* const     toTest
        , const char* const     prefix
    );

    /**
	 * 判断指定的字符串是不是从指定的前缀字符串为开始的
	 * @param[ in ] toTest 以"\0"结尾的字符串
	 * @param[ in ] prefix 以"\0"结尾的前缀字符串
	 * @return 是以该前缀字符串开始的返回true,否则返false
	 */
    static bool startsWith
    (
        const   XMLCh* const    toTest
        , const XMLCh* const    prefix
    );

    /**
	 * 判断指定的字符串是不是从指定的前缀字符串为开始的( 忽略大小写 )
	 * @param[ in ] toTest 以"\0"结尾的字符串
	 * @param[ in ] prefix 以"\0"结尾的前缀字符串
	 * @return 是以该前缀字符串开始的返回true,否则返false
	 */
    static bool startsWithI
    (
        const   char* const     toTest
        , const char* const     prefix
    );

    /**
	 * 判断指定的字符串是不是从指定的前缀字符串为开始的( 忽略大小写 )
	 * @param[ in ] toTest 以"\0"结尾的字符串
	 * @param[ in ] prefix 以"\0"结尾的前缀字符串
	 * @return 是以该前缀字符串开始的返回true,否则返false
	 */
    static bool startsWithI
    (
        const   XMLCh* const    toTest
        , const XMLCh* const    prefix
    );

    /**
	 * 判断指定的字符串是不是从指定的后缀字符串结束的
	 * @param[ in ] toTest 以"\0"结尾的字符串
	 * @param[ in ] suffix 以"\0"结尾的后缀字符串
	 * @return 是以该后缀字符串结束的返回true,否则返false
	 */
    static bool endsWith
    (
        const   char* const    toTest
        , const char* const    suffix
    );

    /**
	 * 判断指定的字符串是不是从指定的后缀字符串结束的
	 * @param[ in ] toTest 以"\0"结尾的字符串
	 * @param[ in ] suffix 以"\0"结尾的后缀字符串
	 * @return 是以该后缀字符串结束的返回true,否则返false
	 */
    static bool endsWith
    (
        const   XMLCh* const    toTest
        , const XMLCh* const    suffix
    );

    /**
	 * 判断指定的字符串是不是从指定的后缀字符串结束的( 忽略大小写 )
	 * @param[ in ] toTest 以"\0"结尾的字符串
	 * @param[ in ] suffix 以"\0"结尾的后缀字符串
	 * @return 是以该后缀字符串结束的返回true,否则返false
	 */
    static bool endsWithI
    (
        const   char* const    toTest
        , const char* const    suffix
    );

    /**
	 * 判断指定的字符串是不是从指定的后缀字符串结束的( 忽略大小写 )
	 * @param[ in ] toTest 以"\0"结尾的字符串
	 * @param[ in ] suffix 以"\0"结尾的后缀字符串
	 * @return 是以该后缀字符串结束的返回true,否则返false
	 */
    static bool endsWithI
    (
        const   XMLCh* const    toTest
        , const XMLCh* const    suffix
    );

    /**
	 * 从指定的字符串开始寻找等于指定字符集中任意一个字符第一次发现的位置
	 * @param[ in ] toSearch 以"\0"结尾的目标字符串
	 * @param[ in ] searchList 以"\0"结尾的字符集字符串
	 * @return 找到返回第一次发现的位置的地址，否则返回0
	 * @remarks 注意，这里返回的不是索引，而是地址，该地址的内容为字符集中的其中一个
	 */
    static const XMLCh* findAny
    (
        const   XMLCh* const    toSearch
        , const XMLCh* const    searchList
    );

    /**
	 * 从指定的字符串开始寻找等于指定字符集中任意一个字符第一次发现的位置
	 * @param[ in ] toSearch 以"\0"结尾的目标字符串
	 * @param[ in ] searchList 以"\0"结尾的字符集字符串
	 * @return 找到返回第一次发现的位置的地址，否则返回0
	 * @remarks 注意，这里返回的不是索引，而是地址，该地址的内容为字符集中的其中一个
	 */
    static XMLCh* findAny
    (
                XMLCh* const    toSearch
        , const XMLCh* const    searchList
    );

    /**
	 * 在指定的字符串寻找等于指定字符串第一次发现的位置
	 * @param[ in ] toSearch 以"\0"结尾的目标字符串
	 * @param[ in ] pattern 以"\0"结尾的匹配字符串
	 * @return 找到返回第一次发现的位置，否则返回-1
	 * @remarks 注意，有一种情况它不能处理，如"aaaaab"中寻找"aaaab"，它
	 * 并不能正确处理。
	 */
    static int patternMatch
    (
          const XMLCh* const    toSearch
        , const XMLCh* const    pattern
    );

	/**
	 * 计算字符串的长度
	 * @param[ in ] src 以"\0"结尾的目标字符串
	 * @return 返回字符串的长度
	 */
    static unsigned int stringLen(const char* const src);

	/**
	 * 计算字符串的长度
	 * @param[ in ] src 以"\0"结尾的目标字符串
	 * @return 返回字符串的长度
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
	 * 判断指定的字符是不是一个字母字符
	 * @param[ in ] theChar 字符
	 * @return 是返回true,不是返回一个false
	 * @remarks 注意它的范围为 "a"到"z", "A"到"Z"
	 */
    static bool isAlpha(XMLCh const theChar);

	/**
	 * 判断指定的字符是不是一个数字字符
	 * @param[ in ] theChar 字符
	 * @return 是返回true,不是返回一个false
	 * @remarks 注意它的范围为 "0"到"9"
	 */
    static bool isDigit(XMLCh const theChar);

	/**
	 * 判断指定的字符是不是一个数字字符或一个字母字符
	 * @param[ in ] theChar 字符
	 * @return 是返回true,不是返回一个false
	 * @remarks 注意它的范围为 "a"到"z", "A"到"Z","0"到"9",
	 */
    static bool isAlphaNum(XMLCh const theChar);

	/**
	 * 判断指定的字符是不是一个16进制的编码
	 * @param[ in ] theChar 字符
	 * @return 是返回true,不是返回一个false
	 * @remarks 注意它的范围为 "a"到"f", "A"到"F","0"到"9",
	 */
    static bool isHex(XMLCh const theChar);

	/**
	 * 判断指定的字符串是不是全部是空白符
	 * @param[ in ] theChar 字符
	 * @return 是返回true,不是返回一个false
	 */
    static bool isAllWhiteSpace(const XMLCh* const toCheck);

    /**
	 * 判断指定的匹配字符串是不是包含在指定目标字符串中
	 * @param[ in ] toFind 以"\0"结尾的匹配字符串
	 * @param[ in ] enumList 以"\0"结尾的目标字符串
	 * @return 找到返回第一次发现的位置，否则返回false
	 * @remarks 注意，它能够正确处理如"aaaaab"中寻找"aaaab"的情况
	 */
    static bool isInList(const XMLCh* const toFind, const XMLCh* const enumList);

    /**
	 * 将指定的的数值转换为一个字符串
	 * @param[ in ] toFormat 指定的数值
	 * @param[ out ] toFill 转换后填充的缓冲块
	 * @param[ in ] maxChars 填充的缓冲块的大小
	 * @param[ in ] radix 转换的进制
	 * @remarks 注意，它仅支持2,8,10,16进制的转换。
	 */
    static void binToText
    (
        const   unsigned int    toFormat
        ,       char* const     toFill
        , const unsigned int    maxChars
        , const unsigned int    radix
    );

    /**
	 * 将指定的的数值转换为一个字符串
	 * @param[ in ] toFormat 指定的数值
	 * @param[ out ] toFill 转换后填充的缓冲块
	 * @param[ in ] maxChars 填充的缓冲块的大小
	 * @param[ in ] radix 转换的进制
	 * @remarks 注意，它仅支持2,8,10,16进制的转换。
	 */
    static void binToText
    (
        const   unsigned int    toFormat
        ,       XMLCh* const    toFill
        , const unsigned int    maxChars
        , const unsigned int    radix
    );

    /**
	 * 将指定的的数值转换为一个字符串
	 * @param[ in ] toFormat 指定的数值
	 * @param[ out ] toFill 转换后填充的缓冲块
	 * @param[ in ] maxChars 填充的缓冲块的大小
	 * @param[ in ] radix 转换的进制
	 * @remarks 注意，它仅支持2,8,10,16进制的转换。
	 */
    static void binToText
    (
        const   unsigned long   toFormat
        ,       char* const     toFill
        , const unsigned int    maxChars
        , const unsigned int    radix
    );

    /**
	 * 将指定的的数值转换为一个字符串
	 * @param[ in ] toFormat 指定的数值
	 * @param[ out ] toFill 转换后填充的缓冲块
	 * @param[ in ] maxChars 填充的缓冲块的大小
	 * @param[ in ] radix 转换的进制
	 * @remarks 注意，它仅支持2,8,10,16进制的转换。
	 */
    static void binToText
    (
        const   unsigned long   toFormat
        ,       XMLCh* const    toFill
        , const unsigned int    maxChars
        , const unsigned int    radix
    );

    /**
	 * 将指定的的数值转换为一个字符串
	 * @param[ in ] toFormat 指定的数值
	 * @param[ out ] toFill 转换后填充的缓冲块
	 * @param[ in ] maxChars 填充的缓冲块的大小
	 * @param[ in ] radix 转换的进制
	 * @remarks 注意，它仅支持2,8,10,16进制的转换。
	 */
    static void binToText
    (
        const   long            toFormat
        ,       char* const     toFill
        , const unsigned int    maxChars
        , const unsigned int    radix
    );

    /**
	 * 将指定的的数值转换为一个字符串
	 * @param[ in ] toFormat 指定的数值
	 * @param[ out ] toFill 转换后填充的缓冲块
	 * @param[ in ] maxChars 填充的缓冲块的大小
	 * @param[ in ] radix 转换的进制
	 * @remarks 注意，它仅支持2,8,10,16进制的转换。
	 */
    static void binToText
    (
        const   long            toFormat
        ,       XMLCh* const    toFill
        , const unsigned int    maxChars
        , const unsigned int    radix
    );

    /**
	 * 将指定的的数值转换为一个字符串
	 * @param[ in ] toFormat 指定的数值
	 * @param[ out ] toFill 转换后填充的缓冲块
	 * @param[ in ] maxChars 填充的缓冲块的大小
	 * @param[ in ] radix 转换的进制
	 * @remarks 注意，它仅支持2,8,10,16进制的转换。
	 */
    static void binToText
    (
        const   int             toFormat
        ,       char* const     toFill
        , const unsigned int    maxChars
        , const unsigned int    radix
    );

    /**
	 * 将指定的的数值转换为一个字符串
	 * @param[ in ] toFormat 指定的数值
	 * @param[ out ] toFill 转换后填充的缓冲块
	 * @param[ in ] maxChars 填充的缓冲块的大小
	 * @param[ in ] radix 转换的进制
	 * @remarks 注意，它仅支持2,8,10,16进制的转换。
	 */
    static void binToText
    (
        const   int             toFormat
        ,       XMLCh* const    toFill
        , const unsigned int    maxChars
        , const unsigned int    radix
    );

    /**
	 * 将指定的的字符串转换为一个数值
	 * @param[ in ] toConvert 指定的以"\0"结尾的字符串
	 * @param[ out ] toFill 转换后数值
	 * @return 成功返回true,否则返回false 
	 * @remarks 注意，它仅支持10进制的转换。
	 */
    static bool textToBin
    (
        const   XMLCh* const    toConvert
        ,       unsigned int&   toFill
    );

    /**
	 * 将指定的的字符串转换为一个数值
	 * @param[ in ] toConvert 指定的以"\0"结尾的字符串
	 * @return 返回转换后数值
	 * @remarks 注意，它仅支持10进制的转换,如果失败它将扔出一个异常。
	 */
    static int parseInt
    (
        const   XMLCh* const    toConvert
    );

    /**
	 * 将指定的字符串前n个字符删除，将后面的字符串移动到前面
	 * @param[ in ] toCutFrom 指定的以"\0"结尾的字符串
	 * @param[ in ] count 指定的字符个数
	 * @return 它的功能类似于
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
	 * 去掉字符中两边的空格
	 * @param[ in ] toTrim 以"\0"结尾的字符串
	 */
    static void trim(char* const toTrim);

    /**
	 * 去掉字符中两边的空格
	 * @param[ in ] toTrim 以"\0"结尾的字符串
	 */
    static void trim(XMLCh* const toTrim);

    
    static BaseRefVectorOf<XMLCh>* tokenizeString(const XMLCh* const tokenizeSrc );

    
    static XMLCh* makeUName
    (
        const   XMLCh* const    pszURI
        , const XMLCh* const    pszName      
    );

    /**
	 * 将maxChars中的{0}，{1，}{2}或{3}字符串替换成text1，text2，text3和text4
	 * @param[ in/out ] errText 以"\0"结尾的待替换的字符串
	 * @param[ in ] maxChars errText内存块的大小
	 * @param[ in ] text1 以"\0"结尾的字符串
	 * @param[ in ] text2 以"\0"结尾的字符串
	 * @param[ in ] text3 以"\0"结尾的字符串
	 * @param[ in ] text4 以"\0"结尾的字符串
	 * @return 返回新字符串的大小
	 * @remarks 如果errText太小，就可能会被替换部分
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
	 * 释放指定的字符串空间
	 * @param[ in ] buf 字符串空间
	 */
    static void release(char** buf);

	/**
	 * 释放指定的字符串空间
	 * @param[ in ] buf 字符串空间
	 */
    static void release(XMLCh** buf);

	/**
	 * 释放指定的字符串空间
	 * @param[ in ] buf 字符串空间
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
