/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   flimits.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 19:57:56 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 20:44:47 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FLIMITS_H
# define FLIMITS_H
# if !defined _LIBC_LIMITS_H_ && !defined _LIMITS_H
#  define CHAR_BIT 8
#  define SCHAR_MIN (-128)
#  define SCHAR_MAX 127
#  define UCHAR_MAX 255
#  define CHAR_MIN SCHAR_MIN
#  define CHAR_MAX SCHAR_MAX
#  define SHRT_MIN (-32768)
#  define SHRT_MAX 32767
#  define USHRT_MAX 65535
#  define INT_MIN (-2147483648)
#  define INT_MAX 2147483647
#  define UINT_MAX 4294967295U
#  define LONG_MIN (-9223372036854775808L)
#  define LONG_MAX 9223372036854775807L
#  define ULONG_MAX 18446744073709551615UL
#  define LLONG_MAX 9223372036854775807LL
#  define LLONG_MIN (-9223372036854775808LL)
#  define ULLONG_MAX 18446744073709551615ULL
# endif
#endif
