#ifndef PLUGIN_MANAGAER_CODES_H
# define PLUGIN_MANAGAER_CODES_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "Hazel.Base/string.hpp"
# include "Hazel.Base/Exception.HPP"

_seal_begin

static const char SAFE [] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"01234567890.,/_-" };
static const char HEX [] = { "0123456789abcdef" };
Hazel_NAMESPACE_INLINE_FUNCTION
tstring encode (const tstring &input);

Hazel_NAMESPACE_INLINE_FUNCTION
tstring decode (const tstring &input);

# if defined (OS_HAS_INLINED)
#   include "codes.inl"
# endif /* Hazel_HAS_INLINED_OSCALLS */

_seal_end

#endif // PLUGIN_MANAGAER_CODES_H
