 /*
  * ass.h -- assert library
  *
  * ass(cond, ...) -- assert true.
  * ass_eq(a, b, ...) -- assert equal.
  */

#ifndef ASS_H
#define ASS_H

#include "arg.h" // arg_get()
#include "any.h" // any_print()

 /*
  * ass(cond, ...)
  *
  * Assert true. If cond evaluates to true, nothing happens.
  * If cond evaluates to false, "assertion failed" message
  * is printed, along with information about assertion:
  *     - file name
  *     - line number
  *     - function name
  *     - assertion argument(s)
  *
  * Example:
  *     double d = read_sensor();
  *     ass(d <= 0);
  *     // main.c:23 main(): assertion failed: 
  *     //     ass(d <= 0) 
  *
  * If more than 1 argument is passed, they will not be
  * evaluated, but will be printed in the message:
  *
  *     main.c:23 main(): assertion failed:
  *         ass(d <= 0, "Submarine submergence depth is negative")
  */
#define ass(...)                                                       \
    (_arg_get_1(__VA_ARGS__) ? ((void)0) :                             \
     (void)printf("%s:%i: %s(): assertion failed: \n"                  \
      "    ass(" #__VA_ARGS__ ")\n", __FILE__, __LINE__, __func__))

 /*
  * ass_eq(val1, val2, ...)
  *
  * GCC-specific.
  *
  * Assert equal. If val1 == val2, nothing happens.
  * Else "assertion failed" message
  * is printed, along with information about assertion:
  *     - file name
  *     - line number
  *     - function name
  *     - assertion arguments
  * 
  * Also, ass_eq() will try to guess it's argument types
  * and print their values using any_print() from "any.h"
  * (GCC-specific).
  *
  * Example:
  *     ass_eq(nwings, 2, "Number of wings");
  *     // main.c:23 main(): assertion failed: 
  *     //     ass_eq(nwings, 2, "Number of wings") 
  *     //     -2147483648 != 2
  */

#define ass_eq(...)                                          \
    ( (arg_get(1, __VA_ARGS__) == arg_get(2, __VA_ARGS__)) ? \
      ((void)0) :                                            \
      (printf("%s:%i: %s(): assertion failed: \n"            \
              "    ass_eq(" #__VA_ARGS__ ")\n    ",          \
              __FILE__, __LINE__, __func__),                 \
       _any_print(v1),                                       \
       printf(" != "),                                       \
       _any_print(v2),                                       \
       printf("\n"),                                         \
       ((void)0)) )


#endif // guard
