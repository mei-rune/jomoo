


#ifndef _args_define_h_
#define _args_define_h_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "macro_misc.hpp"

#define PP_JOIN(X, Y)       PP_DO_JOIN(X, Y)
#define PP_DO_JOIN(X, Y)    PP_DO_JOIN2(X, Y)
#define PP_DO_JOIN2(X, Y)   X##Y

#define PP_MAKE_PARAMS1_0(t)    
#define PP_MAKE_PARAMS1_1(t)    t##1
#define PP_MAKE_PARAMS1_2(t)    PP_MAKE_PARAMS1_1(t), ##t##2
#define PP_MAKE_PARAMS1_3(t)    PP_MAKE_PARAMS1_2(t), ##t##3
#define PP_MAKE_PARAMS1_4(t)    PP_MAKE_PARAMS1_3(t), ##t##4
#define PP_MAKE_PARAMS1_5(t)    t##1, ##t##2, ##t##3, ##t##4, ##t##5
#define PP_MAKE_PARAMS1_6(t)    t##1, ##t##2, ##t##3, ##t##4, ##t##5, ##t##6
#define PP_MAKE_PARAMS1_7(t)    t##1, ##t##2, ##t##3, ##t##4, ##t##5, ##t##6, ##t##7
#define PP_MAKE_PARAMS1_8(t)    t##1, ##t##2, ##t##3, ##t##4, ##t##5, ##t##6, ##t##7, ##t##8
#define PP_MAKE_PARAMS1_9(t)    t##1, ##t##2, ##t##3, ##t##4, ##t##5, ##t##6, ##t##7, ##t##8, ##t##9
#define PP_MAKE_PARAMS1_10(t)    t##1, ##t##2, ##t##3, ##t##4, ##t##5, ##t##6, ##t##7, ##t##8, ##t##9, ##t##10
#define PP_MAKE_PARAMS1_11(t)    t##1, ##t##2, ##t##3, ##t##4, ##t##5, ##t##6, ##t##7, ##t##8, ##t##9, ##t##10, t##11
#define PP_MAKE_PARAMS1_12(t)    t##1, ##t##2, ##t##3, ##t##4, ##t##5, ##t##6, ##t##7, ##t##8, ##t##9, ##t##10, t##11, ##t##12
#define PP_MAKE_PARAMS1_13(t)    t##1, ##t##2, ##t##3, ##t##4, ##t##5, ##t##6, ##t##7, ##t##8, ##t##9, ##t##10, t##11, ##t##12, ##t##13
#define PP_MAKE_PARAMS1_14(t)    t##1, ##t##2, ##t##3, ##t##4, ##t##5, ##t##6, ##t##7, ##t##8, ##t##9, ##t##10, t##11, ##t##12, ##t##13, ##t##14
#define PP_MAKE_PARAMS1_15(t)    t##1, ##t##2, ##t##3, ##t##4, ##t##5, ##t##6, ##t##7, ##t##8, ##t##9, ##t##10, t##11, ##t##12, ##t##13, ##t##14, ##t##15
#define PP_MAKE_PARAMS1_16(t)    t##1, ##t##2, ##t##3, ##t##4, ##t##5, ##t##6, ##t##7, ##t##8, ##t##9, ##t##10, t##11, ##t##12, ##t##13, ##t##14, ##t##15, ##t##16
#define PP_MAKE_PARAMS1_17(t)    t##1, ##t##2, ##t##3, ##t##4, ##t##5, ##t##6, ##t##7, ##t##8, ##t##9, ##t##10, t##11, ##t##12, ##t##13, ##t##14, ##t##15, ##t##16, ##t##17
#define PP_MAKE_PARAMS1_18(t)    t##1, ##t##2, ##t##3, ##t##4, ##t##5, ##t##6, ##t##7, ##t##8, ##t##9, ##t##10, t##11, ##t##12, ##t##13, ##t##14, ##t##15, ##t##16, ##t##17, ##t##18
#define PP_MAKE_PARAMS1_19(t)    t##1, ##t##2, ##t##3, ##t##4, ##t##5, ##t##6, ##t##7, ##t##8, ##t##9, ##t##10, t##11, ##t##12, ##t##13, ##t##14, ##t##15, ##t##16, ##t##17, ##t##18, ##t##19

#define PP_MAKE_PARAMS2_0(t1, t2)   
#define PP_MAKE_PARAMS2_1(t1, t2)   t1##1 t2##1
#define PP_MAKE_PARAMS2_2(t1, t2)   t1##1 t2##1, t1##2 t2##2
#define PP_MAKE_PARAMS2_3(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3
#define PP_MAKE_PARAMS2_4(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4
#define PP_MAKE_PARAMS2_5(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4, t1##5 t2##5
#define PP_MAKE_PARAMS2_6(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4, t1##5 t2##5, t1##6 t2##6
#define PP_MAKE_PARAMS2_7(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4, t1##5 t2##5, t1##6 t2##6, t1##7 t2##7
#define PP_MAKE_PARAMS2_8(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4, t1##5 t2##5, t1##6 t2##6, t1##7 t2##7, t1##8 t2##8
#define PP_MAKE_PARAMS2_9(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4, t1##5 t2##5, t1##6 t2##6, t1##7 t2##7, t1##8 t2##8, t1##9 t2##9
#define PP_MAKE_PARAMS2_10(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4, t1##5 t2##5, t1##6 t2##6, t1##7 t2##7, t1##8 t2##8, t1##10 t2##10
#define PP_MAKE_PARAMS2_11(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4, t1##5 t2##5, t1##6 t2##6, t1##7 t2##7, t1##8 t2##8, t1##10 t2##10, t1##11 t2##11
#define PP_MAKE_PARAMS2_12(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4, t1##5 t2##5, t1##6 t2##6, t1##7 t2##7, t1##8 t2##8, t1##10 t2##10, t1##11 t2##11, t1##12 t2##12
#define PP_MAKE_PARAMS2_13(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4, t1##5 t2##5, t1##6 t2##6, t1##7 t2##7, t1##8 t2##8, t1##10 t2##10, t1##11 t2##11, t1##12 t2##12, t1##13 t2##13
#define PP_MAKE_PARAMS2_14(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4, t1##5 t2##5, t1##6 t2##6, t1##7 t2##7, t1##8 t2##8, t1##10 t2##10, t1##11 t2##11, t1##12 t2##12, t1##13 t2##13, t1##14 t2##14
#define PP_MAKE_PARAMS2_15(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4, t1##5 t2##5, t1##6 t2##6, t1##7 t2##7, t1##8 t2##8, t1##10 t2##10, t1##11 t2##11, t1##12 t2##12, t1##13 t2##13, t1##14 t2##14, t1##5 t2##15
#define PP_MAKE_PARAMS2_16(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4, t1##5 t2##5, t1##6 t2##6, t1##7 t2##7, t1##8 t2##8, t1##10 t2##10, t1##11 t2##11, t1##12 t2##12, t1##13 t2##13, t1##14 t2##14, t1##5 t2##15, t1##16 t2##16
#define PP_MAKE_PARAMS2_17(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4, t1##5 t2##5, t1##6 t2##6, t1##7 t2##7, t1##8 t2##8, t1##10 t2##10, t1##11 t2##11, t1##12 t2##12, t1##13 t2##13, t1##14 t2##14, t1##5 t2##15, t1##16 t2##16, t1##17 t2##17
#define PP_MAKE_PARAMS2_18(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4, t1##5 t2##5, t1##6 t2##6, t1##7 t2##7, t1##8 t2##8, t1##10 t2##10, t1##11 t2##11, t1##12 t2##12, t1##13 t2##13, t1##14 t2##14, t1##5 t2##15, t1##16 t2##16, t1##17 t2##17, t1##18 t2##18
#define PP_MAKE_PARAMS2_19(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4, t1##5 t2##5, t1##6 t2##6, t1##7 t2##7, t1##8 t2##8, t1##10 t2##10, t1##11 t2##11, t1##12 t2##12, t1##13 t2##13, t1##14 t2##14, t1##5 t2##15, t1##16 t2##16, t1##17 t2##17, t1##18 t2##18, t1##19 t2##19

#define PP_MAKE_PARAMS1(n, t)         PP_JOIN(PP_MAKE_PARAMS1_, n) (t)
#define PP_MAKE_PARAMS2(n, t1, t2)    PP_JOIN(PP_MAKE_PARAMS2_, n) (t1, t2)


#endif // _args_define_h_

