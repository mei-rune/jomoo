
#ifndef __hazel_macro_params__hpp
#define __hazel_macro_params__hpp

#include "macro_repeat.hpp"

#define Hazel_PP_APPEND( x, y ) Hazel_PP_APPEND1(x,y)
#define Hazel_PP_APPEND1( x, y ) y ## x



#define Hazel_PP2_APPEND( x, y1,y2 ) Hazel_PP2_APPEND1(x,y1,y2)
#define Hazel_PP2_APPEND1( x, y1,y2 ) y1 ## x y2 ##x

#define Hazel_MAKE_PARAMS1(n, t)        Hazel_REPEAT( n, Hazel_PP_APPEND , t)
#define Hazel_MAKE_PARAMS2(n, t1, t2)   Hazel_REPEAT2( n, Hazel_PP2_APPEND, t1,t2)


#endif //__macro_params__hpp
