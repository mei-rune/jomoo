#include "stdafx.h"

#include "XML_expat.H"
#include "util/share_library.h"

XML_expat expat_;
Share_Library expat_lib_;

#define XML_LOAD_MEMBER( expat_ , log ,fn )  fn##_ = ( fn##_t ) expat_lib_.symbol( fn );	\
	if( fn##_ == NULL )																		\
	BT_LOG_ERROR_RETURN( log, BT_TEXT("‘ÿ»ÎAPI [ ") << #fn									\
		<< BT_TEXT("] ß∞‹£¨[") << expat_lib_.error() << BT_TEXT( "]" ) , 0 );




XMLPARSEAPI( XML_expat* ) ____init_expat( const char * n ,BOE_Log_Impl* log )
{
	if( expat_lib_.open( n, 0 ) != 0)
		BT_LOG_ERROR_RETURN( log, BT_TEXT("‘ÿ»Îdll ß∞‹£¨[") << expat_lib_.error() << BT_TEXT( "]" ) , 0 );


	XML_LOAD_MEMBER( expat_ , log , XML_SetElementDeclHandler                   );
	XML_LOAD_MEMBER( expat_ , log , XML_SetAttlistDeclHandler                   );
	XML_LOAD_MEMBER( expat_ , log , XML_SetXmlDeclHandler                       );
	XML_LOAD_MEMBER( expat_ , log , XML_ParserCreate                            );
	XML_LOAD_MEMBER( expat_ , log , XML_ParserCreateNS                          );
	XML_LOAD_MEMBER( expat_ , log , XML_ParserCreate_MM                         );
	XML_LOAD_MEMBER( expat_ , log , XML_ParserReset                             );  
	XML_LOAD_MEMBER( expat_ , log , XML_SetEntityDeclHandler                    );
	XML_LOAD_MEMBER( expat_ , log , XML_SetElementHandler                       );
	XML_LOAD_MEMBER( expat_ , log , XML_SetStartElementHandler                  );
	XML_LOAD_MEMBER( expat_ , log , XML_SetEndElementHandler                    );
	XML_LOAD_MEMBER( expat_ , log , XML_SetCharacterDataHandler                 );
	XML_LOAD_MEMBER( expat_ , log , XML_SetProcessingInstructionHandler         );
	XML_LOAD_MEMBER( expat_ , log , XML_SetCommentHandler                       );
	XML_LOAD_MEMBER( expat_ , log , XML_SetCdataSectionHandler                  );
	XML_LOAD_MEMBER( expat_ , log , XML_SetStartCdataSectionHandler             );
	XML_LOAD_MEMBER( expat_ , log , XML_SetEndCdataSectionHandler               );
	XML_LOAD_MEMBER( expat_ , log , XML_SetDefaultHandler                       );
	XML_LOAD_MEMBER( expat_ , log , XML_SetDefaultHandlerExpand                 );
	XML_LOAD_MEMBER( expat_ , log , XML_SetDoctypeDeclHandler                   );
	XML_LOAD_MEMBER( expat_ , log , XML_SetStartDoctypeDeclHandler              );
	XML_LOAD_MEMBER( expat_ , log , XML_SetEndDoctypeDeclHandler                );
	XML_LOAD_MEMBER( expat_ , log , XML_SetUnparsedEntityDeclHandler            );
	XML_LOAD_MEMBER( expat_ , log , XML_SetNotationDeclHandler                  );
	XML_LOAD_MEMBER( expat_ , log , XML_SetNamespaceDeclHandler                 );
	XML_LOAD_MEMBER( expat_ , log , XML_SetStartNamespaceDeclHandler            );
	XML_LOAD_MEMBER( expat_ , log , XML_SetEndNamespaceDeclHandler              );
	XML_LOAD_MEMBER( expat_ , log , XML_SetNotStandaloneHandler                 );
	XML_LOAD_MEMBER( expat_ , log , XML_SetExternalEntityRefHandler             );
	XML_LOAD_MEMBER( expat_ , log , XML_SetExternalEntityRefHandlerArg          );
	XML_LOAD_MEMBER( expat_ , log , XML_SetSkippedEntityHandler                 );
	XML_LOAD_MEMBER( expat_ , log , XML_SetUnknownEncodingHandler               );
	XML_LOAD_MEMBER( expat_ , log , XML_DefaultCurrent                          );  
	XML_LOAD_MEMBER( expat_ , log , XML_SetReturnNSTriplet                      );
	XML_LOAD_MEMBER( expat_ , log , XML_SetUserData                             );  
	XML_LOAD_MEMBER( expat_ , log , XML_SetEncoding                             );  
	XML_LOAD_MEMBER( expat_ , log , XML_UseParserAsHandlerArg                   );
	XML_LOAD_MEMBER( expat_ , log , XML_UseForeignDTD                           );
	XML_LOAD_MEMBER( expat_ , log , XML_SetBase                                 );    
	XML_LOAD_MEMBER( expat_ , log , XML_GetBase                                 );    
	XML_LOAD_MEMBER( expat_ , log , XML_GetSpecifiedAttributeCount              );
	XML_LOAD_MEMBER( expat_ , log , XML_GetIdAttributeIndex                     );
	XML_LOAD_MEMBER( expat_ , log , XML_Parse                                   );      
	XML_LOAD_MEMBER( expat_ , log , XML_GetBuffer                               );    
	XML_LOAD_MEMBER( expat_ , log , XML_ParseBuffer                             );   
	XML_LOAD_MEMBER( expat_ , log , XML_ExternalEntityParserCreate              );
	XML_LOAD_MEMBER( expat_ , log , XML_SetParamEntityParsing                   );
	XML_LOAD_MEMBER( expat_ , log , XML_GetErrorCode                            ); 
	XML_LOAD_MEMBER( expat_ , log , XML_GetCurrentLineNumber                    );
	XML_LOAD_MEMBER( expat_ , log , XML_GetCurrentColumnNumber                  );
	XML_LOAD_MEMBER( expat_ , log , XML_GetCurrentByteIndex                     );
	XML_LOAD_MEMBER( expat_ , log , XML_GetCurrentByteCount                     );
	XML_LOAD_MEMBER( expat_ , log , XML_GetInputContext                         );
	XML_LOAD_MEMBER( expat_ , log , XML_FreeContentModel                        );
	XML_LOAD_MEMBER( expat_ , log , XML_MemMalloc                               );  
	XML_LOAD_MEMBER( expat_ , log , XML_MemRealloc                              );  
	XML_LOAD_MEMBER( expat_ , log , XML_MemFree                                 );   
	XML_LOAD_MEMBER( expat_ , log , XML_ParserFree                              );   
	XML_LOAD_MEMBER( expat_ , log , XML_ErrorString                             );    
	XML_LOAD_MEMBER( expat_ , log , XML_ExpatVersion                            );  
	XML_LOAD_MEMBER( expat_ , log , XML_ExpatVersionInfo                        );
	XML_LOAD_MEMBER( expat_ , log , XML_GetFeatureList                          );

	return &expat_;
}

XMLPARSEAPI( XML_expat* ) ____get_expat( )
{
	return &expat_;
}

XMLPARSEAPI( void ) ____fini_expat( )
{
}