#if !defined _FEATURES_H && !defined __need_uClibc_config_h
# error Never include <bits/uClibc_config.h> directly; use <features.h> instead
#endif

#define __UCLIBC_MAJOR__ 0
#define __UCLIBC_MINOR__ 9
#define __UCLIBC_SUBLEVEL__ 34
/* Automatically generated file; DO NOT EDIT. */
/* uClibc 0.9.34-git C Library Configuration */
#undef __TARGET_alpha__
#undef __TARGET_arc__
#undef __TARGET_arm__
#undef __TARGET_avr32__
#undef __TARGET_bfin__
#undef __TARGET_c6x__
#undef __TARGET_cris__
#undef __TARGET_e1__
#undef __TARGET_frv__
#undef __TARGET_h8300__
#undef __TARGET_hppa__
#undef __TARGET_i386__
#undef __TARGET_i960__
#undef __TARGET_ia64__
#undef __TARGET_m68k__
#undef __TARGET_metag__
#undef __TARGET_microblaze__
#define __TARGET_mips__ 1
#undef __TARGET_nios__
#undef __TARGET_nios2__
#undef __TARGET_powerpc__
#undef __TARGET_sh__
#undef __TARGET_sh64__
#undef __TARGET_sparc__
#undef __TARGET_v850__
#undef __TARGET_vax__
#undef __TARGET_x86_64__
#undef __TARGET_xtensa__

/* Target Architecture Features and Options */
#define __TARGET_ARCH__ "mips"
#define __FORCE_OPTIONS_FOR_ARCH__ 1
#define __CONFIG_MIPS_O32_ABI__ 1
#undef __CONFIG_MIPS_N32_ABI__
#undef __CONFIG_MIPS_N64_ABI__
#undef __CONFIG_MIPS_NAN_LEGACY__
#define __CONFIG_MIPS_NAN_2008__ 1
#undef __CONFIG_MIPS_ISA_1__
#undef __CONFIG_MIPS_ISA_2__
#undef __CONFIG_MIPS_ISA_3__
#undef __CONFIG_MIPS_ISA_4__
#undef __CONFIG_MIPS_ISA_MIPS32__
#define __CONFIG_MIPS_ISA_MIPS32R2__ 1
#undef __CONFIG_MIPS_ISA_MIPS64__
#undef __CONFIG_MIPS_ISA_MIPS64R2__
#define __TARGET_SUBARCH__ ""

/* Using ELF file format */
#define __ARCH_HAS_DEPRECATED_SYSCALLS__ 1
#define __ARCH_ANY_ENDIAN__ 1
#define __ARCH_BIG_ENDIAN__ 1
#define __ARCH_WANTS_BIG_ENDIAN__ 1
#undef __ARCH_WANTS_LITTLE_ENDIAN__
#define __ARCH_HAS_MMU__ 1
#define __ARCH_USE_MMU__ 1
#define __UCLIBC_HAS_FLOATS__ 1
#define __UCLIBC_HAS_FPU__ 1
#undef __DO_C99_MATH__
#undef __DO_XSI_MATH__
#undef __UCLIBC_HAS_FENV__
#define __KERNEL_HEADERS__ ""
#define __HAVE_DOT_CONFIG__ 1

/* General Library Settings */
#define __DOPIC__ 1
#define __ARCH_HAS_UCONTEXT__ 1
#define __HAVE_SHARED__ 1
#undef __FORCE_SHAREABLE_TEXT_SEGMENTS__
#define __LDSO_LDD_SUPPORT__ 1
#define __LDSO_CACHE_SUPPORT__ 1
#define __LDSO_PRELOAD_ENV_SUPPORT__ 1
#undef __LDSO_PRELOAD_FILE_SUPPORT__
#define __LDSO_BASE_FILENAME__ "ld.so"
#undef __LDSO_STANDALONE_SUPPORT__
#undef __LDSO_PRELINK_SUPPORT__
#define __UCLIBC_STATIC_LDCONFIG__ 1
#define __LDSO_RUNPATH__ 1
#define __LDSO_RUNPATH_OF_EXECUTABLE__ 1
#define __LDSO_SAFE_RUNPATH__ 1
#define __LDSO_SEARCH_INTERP_PATH__ 1
#define __LDSO_LD_LIBRARY_PATH__ 1
#undef __LDSO_NO_CLEANUP__
#define __UCLIBC_CTOR_DTOR__ 1
#undef __LDSO_GNU_HASH_SUPPORT__
#undef __HAS_NO_THREADS__
#undef __LINUXTHREADS_OLD__
#undef __LINUXTHREADS_NEW__
#define __UCLIBC_HAS_THREADS_NATIVE__ 1
#define __UCLIBC_HAS_THREADS__ 1
#define __UCLIBC_HAS_TLS__ 1
#undef __PTHREADS_DEBUG_SUPPORT__
#define __UCLIBC_HAS_SYSLOG__ 1
#define __UCLIBC_HAS_LFS__ 1
#undef __MALLOC__
#undef __MALLOC_SIMPLE__
#define __MALLOC_STANDARD__ 1
#undef __MALLOC_GLIBC_COMPAT__
#undef __UCLIBC_HAS_OBSTACK__
#define __UCLIBC_DYNAMIC_ATEXIT__ 1
#undef __COMPAT_ATEXIT__
#undef __UCLIBC_SUSV2_LEGACY__
#undef __UCLIBC_SUSV3_LEGACY__
#undef __UCLIBC_SUSV3_LEGACY_MACROS__
#undef __UCLIBC_SUSV4_LEGACY__
#undef __UCLIBC_STRICT_HEADERS__
#undef __UCLIBC_HAS_STUBS__
#define __UCLIBC_HAS_SHADOW__ 1
#undef __UCLIBC_HAS_PROGRAM_INVOCATION_NAME__
#define __UCLIBC_HAS___PROGNAME__ 1
#define __UCLIBC_HAS_PTY__ 1
#define __ASSUME_DEVPTS__ 1
#define __UNIX98PTY_ONLY__ 1
#undef __UCLIBC_HAS_GETPT__
#undef __UCLIBC_HAS_LIBUTIL__
#define __UCLIBC_HAS_TM_EXTENSIONS__ 1
#define __UCLIBC_HAS_TZ_CACHING__ 1
#define __UCLIBC_HAS_TZ_FILE__ 1
#define __UCLIBC_HAS_TZ_FILE_READ_MANY__ 1
#define __UCLIBC_TZ_FILE_PATH__ "/etc/TZ"
#define __UCLIBC_FALLBACK_TO_ETC_LOCALTIME__ 1

/* Advanced Library Settings */
#define __UCLIBC_PWD_BUFFER_SIZE__ 256
#define __UCLIBC_GRP_BUFFER_SIZE__ 256

/* Support various families of functions */
#define __UCLIBC_LINUX_MODULE_26__ 1
#undef __UCLIBC_LINUX_MODULE_24__
#define __UCLIBC_LINUX_SPECIFIC__ 1
#define __UCLIBC_HAS_GNU_ERROR__ 1
#define __UCLIBC_BSD_SPECIFIC__ 1
#define __UCLIBC_HAS_BSD_ERR__ 1
#undef __UCLIBC_HAS_OBSOLETE_BSD_SIGNAL__
#undef __UCLIBC_HAS_OBSOLETE_SYSV_SIGNAL__
#undef __UCLIBC_NTP_LEGACY__
#undef __UCLIBC_SV4_DEPRECATED__
#define __UCLIBC_HAS_REALTIME__ 1
#define __UCLIBC_HAS_ADVANCED_REALTIME__ 1
#define __UCLIBC_HAS_EPOLL__ 1
#define __UCLIBC_HAS_XATTR__ 1
#define __UCLIBC_HAS_PROFILING__ 1
#define __UCLIBC_HAS_CRYPT_IMPL__ 1
#undef __UCLIBC_HAS_SHA256_CRYPT_IMPL__
#undef __UCLIBC_HAS_SHA512_CRYPT_IMPL__
#define __UCLIBC_HAS_CRYPT__ 1
#define __UCLIBC_HAS_NETWORK_SUPPORT__ 1
#define __UCLIBC_HAS_SOCKET__ 1
#define __UCLIBC_HAS_IPV4__ 1
#undef __UCLIBC_HAS_IPV6__
#undef __UCLIBC_HAS_RPC__
#undef __UCLIBC_USE_NETLINK__
#undef __UCLIBC_HAS_BSD_RES_CLOSE__
#define __UCLIBC_HAS_COMPAT_RES_STATE__ 1
#undef __UCLIBC_HAS_EXTRA_COMPAT_RES_STATE__
#undef __UCLIBC_HAS_RESOLVER_SUPPORT__
#undef __UCLIBC_HAS_LIBRESOLV_STUB__
#undef __UCLIBC_HAS_LIBNSL_STUB__

/* String and Stdio Support */
#define __UCLIBC_HAS_STRING_GENERIC_OPT__ 1
#define __UCLIBC_HAS_STRING_ARCH_OPT__ 1
#define __UCLIBC_HAS_STDIO_FUTEXES__ 1
#define __UCLIBC_HAS_CTYPE_TABLES__ 1
#define __UCLIBC_HAS_CTYPE_SIGNED__ 1
#define __UCLIBC_HAS_CTYPE_UNSAFE__ 1
#undef __UCLIBC_HAS_CTYPE_CHECKED__
#undef __UCLIBC_HAS_CTYPE_ENFORCED__
#undef __UCLIBC_HAS_WCHAR__
#undef __UCLIBC_HAS_LOCALE__
#undef __UCLIBC_HAS_HEXADECIMAL_FLOATS__
#undef __UCLIBC_HAS_GLIBC_CUSTOM_PRINTF__
#undef __USE_OLD_VFPRINTF__
#define __UCLIBC_PRINTF_SCANF_POSITIONAL_ARGS__ 9
#undef __UCLIBC_HAS_STDIO_BUFSIZ_NONE__
#undef __UCLIBC_HAS_STDIO_BUFSIZ_256__
#undef __UCLIBC_HAS_STDIO_BUFSIZ_512__
#undef __UCLIBC_HAS_STDIO_BUFSIZ_1024__
#undef __UCLIBC_HAS_STDIO_BUFSIZ_2048__
#define __UCLIBC_HAS_STDIO_BUFSIZ_4096__ 1
#undef __UCLIBC_HAS_STDIO_BUFSIZ_8192__
#define __UCLIBC_HAS_STDIO_BUILTIN_BUFFER_NONE__ 1
#undef __UCLIBC_HAS_STDIO_BUILTIN_BUFFER_4__
#undef __UCLIBC_HAS_STDIO_BUILTIN_BUFFER_8__
#undef __UCLIBC_HAS_STDIO_SHUTDOWN_ON_ABORT__
#define __UCLIBC_HAS_STDIO_GETC_MACRO__ 1
#define __UCLIBC_HAS_STDIO_PUTC_MACRO__ 1
#define __UCLIBC_HAS_STDIO_AUTO_RW_TRANSITION__ 1
#undef __UCLIBC_HAS_FOPEN_LARGEFILE_MODE__
#undef __UCLIBC_HAS_FOPEN_EXCLUSIVE_MODE__
#undef __UCLIBC_HAS_FOPEN_CLOSEEXEC_MODE__
#undef __UCLIBC_HAS_GLIBC_CUSTOM_STREAMS__
#undef __UCLIBC_HAS_PRINTF_M_SPEC__
#define __UCLIBC_HAS_ERRNO_MESSAGES__ 1
#undef __UCLIBC_HAS_SYS_ERRLIST__
#define __UCLIBC_HAS_SIGNUM_MESSAGES__ 1
#undef __UCLIBC_HAS_SYS_SIGLIST__
#define __UCLIBC_HAS_GNU_GETOPT__ 1
#define __UCLIBC_HAS_GETOPT_LONG__ 1
#define __UCLIBC_HAS_GNU_GETSUBOPT__ 1

/* Big and Tall */
#define __UCLIBC_HAS_REGEX__ 1
#define __UCLIBC_HAS_REGEX_OLD__ 1
#define __UCLIBC_HAS_FNMATCH__ 1
#define __UCLIBC_HAS_FNMATCH_OLD__ 1
#undef __UCLIBC_HAS_WORDEXP__
#undef __UCLIBC_HAS_NFTW__
#undef __UCLIBC_HAS_FTS__
#define __UCLIBC_HAS_GLOB__ 1
#undef __UCLIBC_HAS_GNU_GLOB__
#undef __UCLIBC_HAS_UTMPX__

/* Library Installation Options */
#define __RUNTIME_PREFIX__ "/usr/$(TARGET_ARCH)-linux-uclibc/"
#define __DEVEL_PREFIX__ "/usr/$(TARGET_ARCH)-linux-uclibc/usr/"
#define __MULTILIB_DIR__ "lib"
#define __HARDWIRED_ABSPATH__ 1

/* Security options */
#undef __UCLIBC_BUILD_PIE__
#undef __UCLIBC_HAS_ARC4RANDOM__
#undef __UCLIBC_HAS_SSP__
#define __UCLIBC_BUILD_RELRO__ 1
#undef __UCLIBC_BUILD_NOW__
#define __UCLIBC_BUILD_NOEXECSTACK__ 1

/* Development/debugging options */
#define __CROSS_COMPILER_PREFIX__ ""
#define __UCLIBC_EXTRA_CFLAGS__ "-EB -mfp32"
#undef __DODEBUG__
#define __DOSTRIP__ 1
#undef __DOASSERTS__
#undef __SUPPORT_LD_DEBUG__
#undef __SUPPORT_LD_DEBUG_EARLY__
#undef __UCLIBC_MALLOC_DEBUGGING__
#undef __UCLIBC_HAS_BACKTRACE__
#define __WARNINGS__ "-Wall"
#undef __EXTRA_WARNINGS__
#undef __DOMULTI__
#undef __UCLIBC_MJN3_ONLY__
