/* Copyright (C) 2002-2004   Manuel Novoa III    <mjn3@codepoet.org>
 *
 * GNU Library General Public License (LGPL) version 2 or later.
 *
 * Dedicated to Toni.  See uClibc/DEDICATION.mjn3 for details.
 */

#ifndef _STDIO_H
#error Always include <stdio.h> rather than <bits/uClibc_stdio.h>
#endif

/**********************************************************************/

#define __STDIO_BUFFERS
/* ANSI/ISO mandate at least 256. */
#define __STDIO_BUFSIZ		   4096

#define __STDIO_BUILTIN_BUF_SIZE		0

#define __STDIO_HAS_OPENLIST 1

/**********************************************************************/
/**********************************************************************/
/* Currently unimplemented/untested */
/* #define __STDIO_FLEXIBLE_SETVBUF */

#define __STDIO_GETC_MACRO

#define __STDIO_PUTC_MACRO

/**********************************************************************/

#define __STDIO_IOFBF 0		/* Fully buffered.  */
#define __STDIO_IOLBF 1		/* Line buffered.  */
#define __STDIO_IONBF 2		/* No buffering.  */

typedef struct {
	__off_t __pos;
#ifdef __STDIO_MBSTATE
	__mbstate_t __mbstate;
#endif
} __STDIO_fpos_t;

typedef struct {
	__off64_t __pos;
#ifdef __STDIO_MBSTATE
	__mbstate_t __mbstate;
#endif
} __STDIO_fpos64_t;

/**********************************************************************/
typedef __off64_t __offmax_t;		/* TODO -- rename this? */

/**********************************************************************/
/**********************************************************************/

#if defined __UCLIBC_HAS_THREADS__ && !defined __UCLIBC_IO_MUTEX
/* keep this in sync with uClibc_mutex.h */
# ifdef __USE_STDIO_FUTEXES__
#  include <bits/stdio-lock.h>
#  define __UCLIBC_IO_MUTEX(M) _IO_lock_t M
# else
#  include <bits/pthreadtypes.h>
#  define __UCLIBC_IO_MUTEX(M) pthread_mutex_t M
# endif /* __UCLIBC_HAS_THREADS_NATIVE__ */
#endif

struct __STDIO_FILE_STRUCT {
	unsigned short __modeflags;
	/* There could be a hole here, but modeflags is used most.*/
	unsigned char __ungot[2];
	int __filedes;
#ifdef __STDIO_BUFFERS
	unsigned char *__bufstart;	/* pointer to buffer */
	unsigned char *__bufend;	/* pointer to 1 past end of buffer */
	unsigned char *__bufpos;
	unsigned char *__bufread; /* pointer to 1 past last buffered read char */

#ifdef __STDIO_GETC_MACRO
	unsigned char *__bufgetc_u;	/* 1 past last readable by getc_unlocked */
#endif /* __STDIO_GETC_MACRO */
#ifdef __STDIO_PUTC_MACRO
	unsigned char *__bufputc_u;	/* 1 past last writeable by putc_unlocked */
#endif /* __STDIO_PUTC_MACRO */

#endif /* __STDIO_BUFFERS */

#ifdef __STDIO_HAS_OPENLIST
	struct __STDIO_FILE_STRUCT *__nextopen;
#endif
#ifdef __STDIO_MBSTATE
	__mbstate_t __state;
#endif
#ifdef __UCLIBC_HAS_XLOCALE__
	void *__unused;				/* Placeholder for codeset binding. */
#endif
	int __user_locking;
	__UCLIBC_IO_MUTEX(__lock);
/* Everything after this is unimplemented... and may be trashed. */
#if __STDIO_BUILTIN_BUF_SIZE > 0
	unsigned char __builtinbuf[__STDIO_BUILTIN_BUF_SIZE];
#endif /* __STDIO_BUILTIN_BUF_SIZE > 0 */
};


/***********************************************************************/
/* Having ungotten characters implies the stream is reading.
 * The scheme used here treats the least significant 2 bits of
 * the stream's modeflags member as follows:
 *   0 0   Not currently reading.
 *   0 1   Reading, but no ungetc() or scanf() push back chars.
 *   1 0   Reading with one ungetc() char (ungot[1] is 1)
 *         or one scanf() pushed back char (ungot[1] is 0).
 *   1 1   Reading with both an ungetc() char and a scanf()
 *         pushed back char.  Note that this must be the result
 *         of a scanf() push back (in ungot[0]) _followed_ by
 *         an ungetc() call (in ungot[1]).
 *
 * Notes:
 *   scanf() can NOT use ungetc() to push back characters.
 *     (See section 7.19.6.2 of the C9X rationale -- WG14/N897.)
 */

#define __MASK_READING		0x0003U /* (0x0001 | 0x0002) */
#define __FLAG_READING		0x0001U
#define __FLAG_UNGOT		0x0002U
#define __FLAG_EOF		0x0004U
#define __FLAG_ERROR		0x0008U
#define __FLAG_WRITEONLY	0x0010U
#define __FLAG_READONLY		0x0020U /* (__FLAG_WRITEONLY << 1) */
#define __FLAG_WRITING		0x0040U
#define __FLAG_NARROW		0x0080U

#define __FLAG_FBF		0x0000U /* must be 0 */
#define __FLAG_LBF		0x0100U
#define __FLAG_NBF		0x0200U /* (__FLAG_LBF << 1) */
#define __MASK_BUFMODE		0x0300U /* (__FLAG_LBF|__FLAG_NBF) */
#define __FLAG_APPEND		0x0400U /* fixed! == O_APPEND for linux */
#define __FLAG_WIDE		0x0800U
/* available slot		0x1000U */
#define __FLAG_FREEFILE		0x2000U
#define __FLAG_FREEBUF		0x4000U
#define __FLAG_LARGEFILE	0x8000U /* fixed! == 0_LARGEFILE for linux */
#define __FLAG_FAILED_FREOPEN	__FLAG_LARGEFILE

/* Note: In no-buffer mode, it would be possible to pack the necessary
 * flags into one byte.  Since we wouldn't be buffering and there would
 * be no support for wchar, the only flags we would need would be:
 *   2 bits : ungot count
 *   2 bits : eof + error
 *   2 bits : readonly + writeonly
 *   1 bit  : freefile
 *   1 bit  : appending
 * So, for a very small system (< 128 files) we might have a
 * 4-byte FILE struct of:
 *   unsigned char flags;
 *   signed char filedes;
 *   unsigned char ungot[2];
 */
/**********************************************************************
 * PROTOTYPES OF INTERNAL FUNCTIONS
 **********************************************************************/
/**********************************************************************/

#define __CLEARERR_UNLOCKED(__stream)					\
	((void)((__stream)->__modeflags &= ~(__FLAG_EOF|__FLAG_ERROR)))
#define __FEOF_UNLOCKED(__stream)	((__stream)->__modeflags & __FLAG_EOF)
#define __FERROR_UNLOCKED(__stream)	((__stream)->__modeflags & __FLAG_ERROR)

# define __CLEARERR(__stream)		(clearerr)(__stream)
# define __FERROR(__stream)		(ferror)(__stream)
# define __FEOF(__stream)		(feof)(__stream)

extern int __fgetc_unlocked(FILE *__stream);
extern int __fputc_unlocked(int __c, FILE *__stream);

/* First define the default definitions.
   They are overridden below as necessary. */
#define __FGETC_UNLOCKED(__stream)		(__fgetc_unlocked)((__stream))
#define __FGETC(__stream)			(fgetc)((__stream))
#define __GETC_UNLOCKED_MACRO(__stream)		(__fgetc_unlocked)((__stream))
#define __GETC_UNLOCKED(__stream)		(__fgetc_unlocked)((__stream))
#define __GETC(__stream)			(fgetc)((__stream))

#define __FPUTC_UNLOCKED(__c, __stream)		(__fputc_unlocked)((__c),(__stream))
#define __FPUTC(__c, __stream)			(fputc)((__c),(__stream))
#define __PUTC_UNLOCKED_MACRO(__c, __stream)	(__fputc_unlocked)((__c),(__stream))
#define __PUTC_UNLOCKED(__c, __stream)		(__fputc_unlocked)((__c),(__stream))
#define __PUTC(__c, __stream)			(fputc)((__c),(__stream))


#ifdef __STDIO_GETC_MACRO

extern FILE *__stdin;			/* For getchar() macro. */

# undef  __GETC_UNLOCKED_MACRO
# define __GETC_UNLOCKED_MACRO(__stream)				\
		( ((__stream)->__bufpos < (__stream)->__bufgetc_u)	\
		  ? (*(__stream)->__bufpos++)				\
		  : __fgetc_unlocked(__stream) )

# if 0
	/* Classic macro approach.  getc{_unlocked} can have side effects. */
#  undef  __GETC_UNLOCKED
#  define __GETC_UNLOCKED(__stream)		__GETC_UNLOCKED_MACRO((__stream))

# else
	/* Using gcc extension for safety and additional inlining. */
#  undef  __FGETC_UNLOCKED
#  define __FGETC_UNLOCKED(__stream)					\
		(__extension__ ({					\
			FILE *__S = (__stream);				\
			__GETC_UNLOCKED_MACRO(__S);			\
		}) )

#  undef  __GETC_UNLOCKED
#  define __GETC_UNLOCKED(__stream)		__FGETC_UNLOCKED((__stream))

#   undef  __FGETC
#   define __FGETC(__stream)						\
		(__extension__ ({					\
			FILE *__S = (__stream);				\
			((__S->__user_locking )				\
			 ? __GETC_UNLOCKED_MACRO(__S)			\
			 : (fgetc)(__S));				\
		}) )

#   undef  __GETC
#   define __GETC(__stream)			__FGETC((__stream))

# endif

#else

# define __stdin stdin

#endif /* __STDIO_GETC_MACRO */


#ifdef __STDIO_PUTC_MACRO

extern FILE *__stdout;			/* For putchar() macro. */

# undef  __PUTC_UNLOCKED_MACRO
# define __PUTC_UNLOCKED_MACRO(__c, __stream)				\
		( ((__stream)->__bufpos < (__stream)->__bufputc_u)	\
		  ? (*(__stream)->__bufpos++) = (__c)			\
		  : __fputc_unlocked((__c),(__stream)) )

# if 0
	/* Classic macro approach.  putc{_unlocked} can have side effects.*/
#  undef  __PUTC_UNLOCKED
#  define __PUTC_UNLOCKED(__c, __stream)				\
					__PUTC_UNLOCKED_MACRO((__c), (__stream))

# else
	/* Using gcc extension for safety and additional inlining. */

#  undef  __FPUTC_UNLOCKED
#  define __FPUTC_UNLOCKED(__c, __stream)				\
		(__extension__ ({					\
			FILE *__S = (__stream);				\
			__PUTC_UNLOCKED_MACRO((__c),__S);		\
		}) )

#  undef  __PUTC_UNLOCKED
#  define __PUTC_UNLOCKED(__c, __stream)	__FPUTC_UNLOCKED((__c), (__stream))

#   undef  __FPUTC
#   define __FPUTC(__c, __stream)					\
		(__extension__ ({					\
			FILE *__S = (__stream);				\
			((__S->__user_locking)				\
			 ? __PUTC_UNLOCKED_MACRO((__c),__S)		\
			 : (fputc)((__c),__S));				\
		}) )

#   undef  __PUTC
#   define __PUTC(__c, __stream)		__FPUTC((__c), (__stream))

# endif

#else

# define __stdout stdout

#endif /* __STDIO_PUTC_MACRO */
