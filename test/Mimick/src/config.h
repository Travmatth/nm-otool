#ifndef CONFIG_H_IN_
# define CONFIG_H_IN_

#define MMK_ARCH "x86_64"
#define MMK_BITS 64
#define MMK_MANGLING leading-underscore

/* #undef MMK_ARCH_x86 */
#define MMK_ARCH_x86_64 1
/* #undef MMK_ARCH_ARM */
/* #undef MMK_ARCH_ARM64 */

/* #undef MMK_EXE_FMT_ELF */
/* #undef MMK_EXE_FMT_PE */
#define MMK_EXE_FMT_MACH_O 1

/* #undef HAVE__R_DEBUG */
/* #undef HAVE__DYNAMIC */
/* #undef HAVE_ELF_AUXV_T */
/* #undef HAVE_ELF_AUXINFO */
#define HAVE_MMAP 1
#define HAVE_MMAP_MAP_ANONYMOUS 1
#define HAVE_MMAP_MAP_ANON 1
/* #undef HAVE___STDIO_COMMON_VFPRINTF */

#endif /* !CONFIG_H_IN_ */
