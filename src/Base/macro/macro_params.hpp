
#ifndef __JOMOO_macro_params__hpp
#define __JOMOO_macro_params__hpp

#include "macro_repeat.hpp"

#define JOMOO_PP_APPEND( x, y ) JOMOO_PP_APPEND1(x,y)
#define JOMOO_PP_APPEND1( x, y ) y ## x



#define JOMOO_PP2_APPEND( x, y1,y2 ) JOMOO_PP2_APPEND1(x,y1,y2)
#define JOMOO_PP2_APPEND1( x, y1,y2 ) y1 ## x y2 ##x

#define JOMOO_MAKE_PARAMS1(n, t)        JOMOO_REPEAT( n, JOMOO_PP_APPEND , t)
#define JOMOO_MAKE_PARAMS2(n, t1, t2)   JOMOO_REPEAT2( n, JOMOO_PP2_APPEND, t1,t2)


#endif //__macro_params__hpp
