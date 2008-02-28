/* Copyright (c) 1998, 1999, 2000 Thai Open Source Software Center Ltd
   See the file COPYING for copying permission.
*/

#ifndef XML_EXPAT_H
#define XML_EXPAT_H 1

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "expat.h"
#include "util/BOE_Log_Base.h"

typedef void ( *XML_SetElementDeclHandler_t ) (XML_Parser parser,
                          XML_ElementDeclHandler eldecl);

typedef void (* XML_SetAttlistDeclHandler_t) (XML_Parser parser,
                          XML_AttlistDeclHandler attdecl);

typedef void (*XML_SetXmlDeclHandler_t)(XML_Parser parser,
                      XML_XmlDeclHandler xmldecl);

typedef XML_Parser (*XML_ParserCreate_t)(const XML_Char *encoding);

typedef XML_Parser (*XML_ParserCreateNS_t)(const XML_Char *encoding, XML_Char namespaceSeparator);

typedef XML_Parser (* XML_ParserCreate_MM_t )(const XML_Char *encoding,
                    const XML_Memory_Handling_Suite *memsuite,
                    const XML_Char *namespaceSeparator );

typedef XML_Bool (*XML_ParserReset_t)(XML_Parser parser, const XML_Char *encoding);

typedef void (*XML_SetEntityDeclHandler_t)(XML_Parser parser,
                         XML_EntityDeclHandler handler);

typedef void (*XML_SetElementHandler_t)(XML_Parser parser,
                      XML_StartElementHandler start,
                      XML_EndElementHandler end);

typedef void (*XML_SetStartElementHandler_t)(XML_Parser, XML_StartElementHandler);

typedef void (*XML_SetEndElementHandler_t)(XML_Parser, XML_EndElementHandler);

typedef void (*XML_SetCharacterDataHandler_t)(XML_Parser parser,
                            XML_CharacterDataHandler handler);

typedef void (*XML_SetProcessingInstructionHandler_t)(XML_Parser parser,
                                    XML_ProcessingInstructionHandler handler);
typedef void (*XML_SetCommentHandler_t)(XML_Parser parser,
                      XML_CommentHandler handler);

typedef void (*XML_SetCdataSectionHandler_t)(XML_Parser parser,
                           XML_StartCdataSectionHandler start,
                           XML_EndCdataSectionHandler end);

typedef void (*XML_SetStartCdataSectionHandler_t)(XML_Parser parser,
                                XML_StartCdataSectionHandler start);

typedef void (*XML_SetEndCdataSectionHandler_t)(XML_Parser parser,
                              XML_EndCdataSectionHandler end);

typedef void (*XML_SetDefaultHandler_t)(XML_Parser parser,
                      XML_DefaultHandler handler);

typedef void (*XML_SetDefaultHandlerExpand_t)(XML_Parser parser,
                            XML_DefaultHandler handler);

typedef void (*XML_SetDoctypeDeclHandler_t)(XML_Parser parser,
                          XML_StartDoctypeDeclHandler start,
                          XML_EndDoctypeDeclHandler end);

typedef void (*XML_SetStartDoctypeDeclHandler_t)(XML_Parser parser,
                               XML_StartDoctypeDeclHandler start);

typedef void (*XML_SetEndDoctypeDeclHandler_t)(XML_Parser parser,
                             XML_EndDoctypeDeclHandler end);

typedef void (*XML_SetUnparsedEntityDeclHandler_t)(XML_Parser parser,
                                 XML_UnparsedEntityDeclHandler handler);

typedef void (*XML_SetNotationDeclHandler_t)(XML_Parser parser,
                           XML_NotationDeclHandler handler);

typedef void (*XML_SetNamespaceDeclHandler_t)(XML_Parser parser,
                            XML_StartNamespaceDeclHandler start,
                            XML_EndNamespaceDeclHandler end);

typedef void (*XML_SetStartNamespaceDeclHandler_t)(XML_Parser parser,
                                 XML_StartNamespaceDeclHandler start);

typedef void (*XML_SetEndNamespaceDeclHandler_t)(XML_Parser parser,
                               XML_EndNamespaceDeclHandler end);

typedef void (*XML_SetNotStandaloneHandler_t)(XML_Parser parser,
                            XML_NotStandaloneHandler handler);

typedef void (*XML_SetExternalEntityRefHandler_t)(XML_Parser parser,
                                XML_ExternalEntityRefHandler handler);

typedef void (*XML_SetExternalEntityRefHandlerArg_t)(XML_Parser, void *arg);

typedef void (*XML_SetSkippedEntityHandler_t)(XML_Parser parser,
                            XML_SkippedEntityHandler handler);

typedef void (*XML_SetUnknownEncodingHandler_t)(XML_Parser parser,
                              XML_UnknownEncodingHandler handler,
                              void *encodingHandlerData);

typedef void (*XML_DefaultCurrent_t)(XML_Parser parser);

typedef void (*XML_SetReturnNSTriplet_t)(XML_Parser parser, int do_nst);

typedef void (*XML_SetUserData_t)(XML_Parser parser, void *userData);

typedef XML_Status (*XML_SetEncoding_t)(XML_Parser parser, const XML_Char *encoding);

typedef void (*XML_UseParserAsHandlerArg_t)(XML_Parser parser);

typedef  XML_Error (*XML_UseForeignDTD_t)(XML_Parser parser, XML_Bool useDTD);

typedef XML_Status (*XML_SetBase_t)(XML_Parser parser, const XML_Char *base);

typedef const XML_Char *(*XML_GetBase_t)(XML_Parser parser);

typedef int (*XML_GetSpecifiedAttributeCount_t)(XML_Parser parser);

typedef int (*XML_GetIdAttributeIndex_t)(XML_Parser parser);

typedef XML_Status (*XML_Parse_t)(XML_Parser parser, const char *s, int len, int isFinal);

typedef void *(*XML_GetBuffer_t)(XML_Parser parser, int len);

typedef XML_Status (*XML_ParseBuffer_t)(XML_Parser parser, int len, int isFinal);

typedef XML_Parser (*XML_ExternalEntityParserCreate_t)(XML_Parser parser,
                               const XML_Char *context,
                               const XML_Char *encoding);

typedef int (*XML_SetParamEntityParsing_t)(XML_Parser parser,
                          enum XML_ParamEntityParsing parsing);

typedef XML_Error (*XML_GetErrorCode_t)(XML_Parser parser);

typedef int (*XML_GetCurrentLineNumber_t)(XML_Parser parser);
typedef int (*XML_GetCurrentColumnNumber_t)(XML_Parser parser);
typedef long (*XML_GetCurrentByteIndex_t)(XML_Parser parser);

typedef int (*XML_GetCurrentByteCount_t)(XML_Parser parser);

typedef const char *(*XML_GetInputContext_t)(XML_Parser parser,
                    int *offset,
                    int *size);

typedef void (*XML_FreeContentModel_t)(XML_Parser parser, XML_Content *model);

typedef void * (*XML_MemMalloc_t)(XML_Parser parser, size_t size);

typedef void * (*XML_MemRealloc_t)(XML_Parser parser, void *ptr, size_t size);

typedef void (*XML_MemFree_t)(XML_Parser parser, void *ptr);

typedef void (*XML_ParserFree_t)(XML_Parser parser);

typedef const XML_LChar *(*XML_ErrorString_t)(enum XML_Error code);

typedef const XML_LChar *(*XML_ExpatVersion_t)(void);

typedef XML_Expat_Version (*XML_ExpatVersionInfo_t)(void);

typedef const XML_Feature *(*XML_GetFeatureList_t)(void);


#define XML_DEF_MEMBER( X ) X##_t X_
#define INIT_MEMBER( X ) X##_t X_
struct XML_expat
{
	XML_expat()
	{
	XML_INIT_MEMBER( XML_SetElementDeclHandler                   );
	XML_INIT_MEMBER( XML_SetAttlistDeclHandler                   );
	XML_INIT_MEMBER( XML_SetXmlDeclHandler                       );
	XML_INIT_MEMBER( XML_ParserCreate                            );
	XML_INIT_MEMBER( XML_ParserCreateNS                          );
	XML_INIT_MEMBER( XML_ParserCreate_MM                         );
	XML_INIT_MEMBER( XML_ParserReset                             );  
	XML_INIT_MEMBER( XML_SetEntityDeclHandler                    );
	XML_INIT_MEMBER( XML_SetElementHandler                       );
	XML_INIT_MEMBER( XML_SetStartElementHandler                  );
	XML_INIT_MEMBER( XML_SetEndElementHandler                    );
	XML_INIT_MEMBER( XML_SetCharacterDataHandler                 );
	XML_INIT_MEMBER( XML_SetProcessingInstructionHandler         );
	XML_INIT_MEMBER( XML_SetCommentHandler                       );
	XML_INIT_MEMBER( XML_SetCdataSectionHandler                  );
	XML_INIT_MEMBER( XML_SetStartCdataSectionHandler             );
	XML_INIT_MEMBER( XML_SetEndCdataSectionHandler               );
	XML_INIT_MEMBER( XML_SetDefaultHandler                       );
	XML_INIT_MEMBER( XML_SetDefaultHandlerExpand                 );
	XML_INIT_MEMBER( XML_SetDoctypeDeclHandler                   );
	XML_INIT_MEMBER( XML_SetStartDoctypeDeclHandler              );
	XML_INIT_MEMBER( XML_SetEndDoctypeDeclHandler                );
	XML_INIT_MEMBER( XML_SetUnparsedEntityDeclHandler            );
	XML_INIT_MEMBER( XML_SetNotationDeclHandler                  );
	XML_INIT_MEMBER( XML_SetNamespaceDeclHandler                 );
	XML_INIT_MEMBER( XML_SetStartNamespaceDeclHandler            );
	XML_INIT_MEMBER( XML_SetEndNamespaceDeclHandler              );
	XML_INIT_MEMBER( XML_SetNotStandaloneHandler                 );
	XML_INIT_MEMBER( XML_SetExternalEntityRefHandler             );
	XML_INIT_MEMBER( XML_SetExternalEntityRefHandlerArg          );
	XML_INIT_MEMBER( XML_SetSkippedEntityHandler                 );
	XML_INIT_MEMBER( XML_SetUnknownEncodingHandler               );
	XML_INIT_MEMBER( XML_DefaultCurrent                          );  
	XML_INIT_MEMBER( XML_SetReturnNSTriplet                      );
	XML_INIT_MEMBER( XML_SetUserData                             );  
	XML_INIT_MEMBER( XML_SetEncoding                             );  
	XML_INIT_MEMBER( XML_UseParserAsHandlerArg                   );
	XML_INIT_MEMBER( XML_UseForeignDTD                           );
	XML_INIT_MEMBER( XML_SetBase                                 );    
	XML_INIT_MEMBER( XML_GetBase                                 );    
	XML_INIT_MEMBER( XML_GetSpecifiedAttributeCount              );
	XML_INIT_MEMBER( XML_GetIdAttributeIndex                     );
	XML_INIT_MEMBER( XML_Parse                                   );      
	XML_INIT_MEMBER( XML_GetBuffer                               );    
	XML_INIT_MEMBER( XML_ParseBuffer                             );   
	XML_INIT_MEMBER( XML_ExternalEntityParserCreate              );
	XML_INIT_MEMBER( XML_SetParamEntityParsing                   );
	XML_INIT_MEMBER( XML_GetErrorCode                            ); 
	XML_INIT_MEMBER( XML_GetCurrentLineNumber                    );
	XML_INIT_MEMBER( XML_GetCurrentColumnNumber                  );
	XML_INIT_MEMBER( XML_GetCurrentByteIndex                     );
	XML_INIT_MEMBER( XML_GetCurrentByteCount                     );
	XML_INIT_MEMBER( XML_GetInputContext                         );
	XML_INIT_MEMBER( XML_FreeContentModel                        );
	XML_INIT_MEMBER( XML_MemMalloc                               );  
	XML_INIT_MEMBER( XML_MemRealloc                              );  
	XML_INIT_MEMBER( XML_MemFree                                 );   
	XML_INIT_MEMBER( XML_ParserFree                              );   
	XML_INIT_MEMBER( XML_ErrorString                             );    
	XML_INIT_MEMBER( XML_ExpatVersion                            );  
	XML_INIT_MEMBER( XML_ExpatVersionInfo                        );
	XML_INIT_MEMBER( XML_GetFeatureList                          );
	}
	XML_DEF_MEMBER( XML_SetElementDeclHandler                   );
	XML_DEF_MEMBER( XML_SetAttlistDeclHandler                   );
	XML_DEF_MEMBER( XML_SetXmlDeclHandler                       );
	XML_DEF_MEMBER( XML_ParserCreate                            );
	XML_DEF_MEMBER( XML_ParserCreateNS                          );
	XML_DEF_MEMBER( XML_ParserCreate_MM                         );
	XML_DEF_MEMBER( XML_ParserReset                             );  
	XML_DEF_MEMBER( XML_SetEntityDeclHandler                    );
	XML_DEF_MEMBER( XML_SetElementHandler                       );
	XML_DEF_MEMBER( XML_SetStartElementHandler                  );
	XML_DEF_MEMBER( XML_SetEndElementHandler                    );
	XML_DEF_MEMBER( XML_SetCharacterDataHandler                 );
	XML_DEF_MEMBER( XML_SetProcessingInstructionHandler         );
	XML_DEF_MEMBER( XML_SetCommentHandler                       );
	XML_DEF_MEMBER( XML_SetCdataSectionHandler                  );
	XML_DEF_MEMBER( XML_SetStartCdataSectionHandler             );
	XML_DEF_MEMBER( XML_SetEndCdataSectionHandler               );
	XML_DEF_MEMBER( XML_SetDefaultHandler                       );
	XML_DEF_MEMBER( XML_SetDefaultHandlerExpand                 );
	XML_DEF_MEMBER( XML_SetDoctypeDeclHandler                   );
	XML_DEF_MEMBER( XML_SetStartDoctypeDeclHandler              );
	XML_DEF_MEMBER( XML_SetEndDoctypeDeclHandler                );
	XML_DEF_MEMBER( XML_SetUnparsedEntityDeclHandler            );
	XML_DEF_MEMBER( XML_SetNotationDeclHandler                  );
	XML_DEF_MEMBER( XML_SetNamespaceDeclHandler                 );
	XML_DEF_MEMBER( XML_SetStartNamespaceDeclHandler            );
	XML_DEF_MEMBER( XML_SetEndNamespaceDeclHandler              );
	XML_DEF_MEMBER( XML_SetNotStandaloneHandler                 );
	XML_DEF_MEMBER( XML_SetExternalEntityRefHandler             );
	XML_DEF_MEMBER( XML_SetExternalEntityRefHandlerArg          );
	XML_DEF_MEMBER( XML_SetSkippedEntityHandler                 );
	XML_DEF_MEMBER( XML_SetUnknownEncodingHandler               );
	XML_DEF_MEMBER( XML_DefaultCurrent                          );  
	XML_DEF_MEMBER( XML_SetReturnNSTriplet                      );
	XML_DEF_MEMBER( XML_SetUserData                             );  
	XML_DEF_MEMBER( XML_SetEncoding                             );  
	XML_DEF_MEMBER( XML_UseParserAsHandlerArg                   );
	XML_DEF_MEMBER( XML_UseForeignDTD                           );
	XML_DEF_MEMBER( XML_SetBase                                 );    
	XML_DEF_MEMBER( XML_GetBase                                 );    
	XML_DEF_MEMBER( XML_GetSpecifiedAttributeCount              );
	XML_DEF_MEMBER( XML_GetIdAttributeIndex                     );
	XML_DEF_MEMBER( XML_Parse                                   );      
	XML_DEF_MEMBER( XML_GetBuffer                               );    
	XML_DEF_MEMBER( XML_ParseBuffer                             );   
	XML_DEF_MEMBER( XML_ExternalEntityParserCreate              );
	XML_DEF_MEMBER( XML_SetParamEntityParsing                   );
	XML_DEF_MEMBER( XML_GetErrorCode                            ); 
	XML_DEF_MEMBER( XML_GetCurrentLineNumber                    );
	XML_DEF_MEMBER( XML_GetCurrentColumnNumber                  );
	XML_DEF_MEMBER( XML_GetCurrentByteIndex                     );
	XML_DEF_MEMBER( XML_GetCurrentByteCount                     );
	XML_DEF_MEMBER( XML_GetInputContext                         );
	XML_DEF_MEMBER( XML_FreeContentModel                        );
	XML_DEF_MEMBER( XML_MemMalloc                               );  
	XML_DEF_MEMBER( XML_MemRealloc                              );  
	XML_DEF_MEMBER( XML_MemFree                                 );   
	XML_DEF_MEMBER( XML_ParserFree                              );   
	XML_DEF_MEMBER( XML_ErrorString                             );    
	XML_DEF_MEMBER( XML_ExpatVersion                            );  
	XML_DEF_MEMBER( XML_ExpatVersionInfo                        );
	XML_DEF_MEMBER( XML_GetFeatureList                          );
};


XMLPARSEAPI( XML_expat* ) ____init_expat( const char * n ,BOE_Log_Impl* log );
XMLPARSEAPI( XML_expat* ) ____get_expat( );
XMLPARSEAPI( void ) ____fini_expat( );

#define EXPAT_INVOKE_MEMBER( f ) ( * ( ____get_expat( ) -> f##_ ) )


#endif /* not XML_EXPAT_H */
