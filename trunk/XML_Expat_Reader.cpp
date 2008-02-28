#include "StdAfx.h"
#include "XML_Expat_Reader.h"
#include "XML_expat.H"

void * ____malloc(size_t size)
{
	return malloc( size );
}

void * ____realloc_fcn(void *ptr, size_t size)
{
	return realloc( ptr, size );
}
void  ____free_fcn(void *ptr)
{
	free( ptr );
}


void XML_Expat_StartElementHandler(void *userData,
                                   const XML_Char *name,
                                   const XML_Char **atts)
{
}

void XML_Expat_EndElementHandler(void *userData,
                                 const XML_Char *name);
{
}

void XML_Expat_CharacterDataHandler(void *userData,
                                    const XML_Char *s,
                                    int len)
{
}

void XML_Expat_ProcessingInstructionHandler(void *userData,
                                            const XML_Char *target,
                                            const XML_Char *data)
{
}

void XML_Expat_CommentHandler
void XML_Expat_StartCdataSectionHandler
void XML_Expat_EndCdataSectionHandler
void XML_Expat_CdataSectionHandler
void XML_Expat_DefaultHandler
void XML_Expat_DefaultHandlerExpand
void XML_Expat_ExternalEntityRefHandler
void XML_Expat_ExternalEntityRefHandlerArg
void XML_Expat_SkippedEntityHandler
void XML_Expat_UnknownEncodingHandler
void XML_Expat_StartNamespaceDeclHandler
void XML_Expat_EndNamespaceDeclHandler
void XML_Expat_NamespaceDeclHandler
void XML_Expat_XmlDeclHandler
void XML_Expat_StartDoctypeDeclHandler
void XML_Expat_EndDoctypeDeclHandler
void XML_Expat_DoctypeDeclHandler
void XML_Expat_ElementDeclHandler
void XML_Expat_AttlistDeclHandler
void XML_Expat_EntityDeclHandler
void XML_Expat_UnparsedEntityDeclHandler
void XML_Expat_NotationDeclHandler
void XML_Expat_NotStandaloneHandler





XML_Expat_Reader::XML_Expat_Reader( const XML_Char *encoding, const XML_Char *sep )
: _parser( 0 )
, contenthandler_( 0 )
, dtdhandler_( 0 )
{
	_suite.malloc_fcn = ____malloc;
	_suite.realloc_fcn = ____realloc_fcn;
	_suite.free_fcn = ____free_fcn;

	_parser = EXPAT_INVOKE_MEMBER(  XML_ParserCreateNS )( encoding,&_suite, sep );
	if( _parser == 0 )
		BOE_THROW( BOE_Exception, BT_TEXT( "" ) );

	EXPAT_INVOKE_MEMBER( XML_SetUserData)( _parser, this);

	/// ContentHandler


	EXPAT_INVOKE_MEMBER( XML_SetElementHandler					)( this, XML_Expat_StartElementHandler, XML_Expat_EndElementHandler	);
	EXPAT_INVOKE_MEMBER( XML_SetCharacterDataHandler			)( this , XML_Expat_CharacterDataHandler );
	EXPAT_INVOKE_MEMBER( XML_SetProcessingInstructionHandler	)( this , XML_Expat_ProcessingInstructionHandler );

	EXPAT_INVOKE_MEMBER( XML_SetCommentHandler					)( );
	EXPAT_INVOKE_MEMBER( XML_SetStartCdataSectionHandler		)( );
	EXPAT_INVOKE_MEMBER( XML_SetEndCdataSectionHandler			)( );
	EXPAT_INVOKE_MEMBER( XML_SetCdataSectionHandler				)( );
	EXPAT_INVOKE_MEMBER( XML_SetDefaultHandler					)( );
	EXPAT_INVOKE_MEMBER( XML_SetDefaultHandlerExpand			)( );
	EXPAT_INVOKE_MEMBER( XML_SetExternalEntityRefHandler		)( );
	EXPAT_INVOKE_MEMBER( XML_SetExternalEntityRefHandlerArg		)( );
	EXPAT_INVOKE_MEMBER( XML_SetSkippedEntityHandler			)( );
	EXPAT_INVOKE_MEMBER( XML_SetUnknownEncodingHandler			)( );
	EXPAT_INVOKE_MEMBER( XML_SetStartNamespaceDeclHandler		)( );
	EXPAT_INVOKE_MEMBER( XML_SetEndNamespaceDeclHandler			)( );
	EXPAT_INVOKE_MEMBER( XML_SetNamespaceDeclHandler			)( );
	EXPAT_INVOKE_MEMBER( XML_SetXmlDeclHandler					)( );
	EXPAT_INVOKE_MEMBER( XML_SetStartDoctypeDeclHandler			)( );
	EXPAT_INVOKE_MEMBER( XML_SetEndDoctypeDeclHandler			)( );
	EXPAT_INVOKE_MEMBER( XML_SetDoctypeDeclHandler				)( );
	EXPAT_INVOKE_MEMBER( XML_SetElementDeclHandler				)( );
	EXPAT_INVOKE_MEMBER( XML_SetAttlistDeclHandler				)( );
	EXPAT_INVOKE_MEMBER( XML_SetEntityDeclHandler				)( );
	EXPAT_INVOKE_MEMBER( XML_SetUnparsedEntityDeclHandler		)( );
	EXPAT_INVOKE_MEMBER( XML_SetNotationDeclHandler				)( );
	EXPAT_INVOKE_MEMBER( XML_SetNotStandaloneHandler			)( );

}

XML_Expat_Reader::~XML_Expat_Reader(void)
{
	EXPAT_INVOKE_MEMBER( XML_ParserFree )( _parser );
}

ContentHandler* XML_Expat_Reader::getContentHandler() const
{
	return contenthandler_;
}

DTDHandler* XML_Expat_Reader::getDTDHandler() const
{
	return dtdhandler_;
}

EntityResolver* XML_Expat_Reader::getEntityResolver() const
{
	return entityresolver_;
}

ErrorHandler* XML_Expat_Reader::getErrorHandler() const
{
	return errorhandler_;
}

bool XML_Expat_Reader::getFeature(const XMLCh* const name) const
{
	return false;
}

void* XML_Expat_Reader::getProperty(const XMLCh* const name) const
{
	return 0;
}

void XML_Expat_Reader::setContentHandler(ContentHandler* const handler)
{
	contenthandler_ = handler;
}

void XML_Expat_Reader::setDTDHandler(DTDHandler* const handler)
{
	dtdhandler_ = handler
}

void XML_Expat_Reader::setEntityResolver(EntityResolver* const resolver)
{
	entityresolver_ = resolver;
}

void XML_Expat_Reader::setErrorHandler(ErrorHandler* const handler)
{
	errorhandler_ = handler;
}

void XML_Expat_Reader::setFeature(const XMLCh* const name, const bool value)
{
	BOE_THROW( BOE_Exception , BT_TEXT( "不支持特性") + tstring( name ) );
}

void XML_Expat_Reader::setProperty(const XMLCh* const name, void* value)
{
	BOE_THROW( BOE_Exception , BT_TEXT( "不支持属性") + tstring( name ) );
}

void XML_Expat_Reader::parse ( const   char* const  buffer , size_t len , bool isfinal )
{
//	XML_Parse(XML_Parser p,
//          const char *s,
//          int len,
//          int isFinal);
//
//enum XML_Status {
//  XML_STATUS_ERROR = 0,
//  XML_STATUS_OK = 1
//};

	if( EXPAT_INVOKE_MEMBER( XML_Parse )( _parser , buffer, len, isfinal ) != XML_STATUS_OK )
		return -1;
	return 0;
}

DeclHandler* XML_Expat_Reader::getDeclarationHandler() const
{
	return declhandler_;
}

LexicalHandler* XML_Expat_Reader::getLexicalHandler() const
{
	return lexicalhandler_;
}

void XML_Expat_Reader::setDeclarationHandler(DeclHandler* const handler)
{
	declhandler_ = handler;
}

void XML_Expat_Reader::setLexicalHandler(LexicalHandler* const handler)
{
	lexicalhandler_ = handler;
}

XMLValidator* XML_Expat_Reader::getValidator() const
{
	return xmlvalidator_;
}

int XML_Expat_Reader::getErrorCount() const
{
	return errorcount_;
}

bool XML_Expat_Reader::getExitOnFirstFatalError() const
{
}

bool XML_Expat_Reader::getValidationConstraintFatal() const
{
}

const XMLCh* XML_Expat_Reader::getURIText(unsigned int uriId) const
{
}

unsigned int XML_Expat_Reader::getSrcOffset() const
{
}

void XML_Expat_Reader::setValidator(XMLValidator* valueToAdopt) 
{
	xmlvalidator_ = valuetoadopt;
}

void XML_Expat_Reader::setValidationConstraintFatal(const bool newState)
{
}

void XML_Expat_Reader::installAdvDocHandler(XMLDocumentHandler* const toInstall)
{
}

bool XML_Expat_Reader::removeAdvDocHandler(XMLDocumentHandler* const toRemove)
{
}