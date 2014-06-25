#ifndef _LINUX_SECCOMP_H
#define _LINUX_SECCOMP_H

<<<<<<< HEAD

=======
#include <linux/compiler.h>
#include <linux/types.h>


/* Valid values for seccomp.mode and prctl(PR_SET_SECCOMP, <mode>) */
#define SECCOMP_MODE_DISABLED	0 /* seccomp is not in use. */
#define SECCOMP_MODE_STRICT	1 /* uses hard-coded filter. */
#define SECCOMP_MODE_FILTER	2 /* uses user-supplied filter. */

/* Valid operations for seccomp syscall. */
#define SECCOMP_SET_MODE_STRICT	0
#define SECCOMP_SET_MODE_FILTER	1

/*
 * All BPF programs must return a 32-bit value.
 * The bottom 16-bits are for optional return data.
 * The upper 16-bits are ordered from least permissive values to most.
 *
 * The ordering ensures that a min_t() over composed return values always
 * selects the least permissive choice.
 */
#define SECCOMP_RET_KILL	0x00000000U /* kill the task immediately */
#define SECCOMP_RET_TRAP	0x00030000U /* disallow and force a SIGSYS */
#define SECCOMP_RET_ERRNO	0x00050000U /* returns an errno */
#define SECCOMP_RET_TRACE	0x7ff00000U /* pass to a tracer or disallow */
#define SECCOMP_RET_ALLOW	0x7fff0000U /* allow */

/* Masks for the return value sections. */
#define SECCOMP_RET_ACTION	0x7fff0000U
#define SECCOMP_RET_DATA	0x0000ffffU

/**
 * struct seccomp_data - the format the BPF program executes over.
 * @nr: the system call number
 * @arch: indicates system call convention as an AUDIT_ARCH_* value
 *        as defined in <linux/audit.h>.
 * @instruction_pointer: at the time of the system call.
 * @args: up to 6 system call arguments always stored as 64-bit values
 *        regardless of the architecture.
 */
struct seccomp_data {
	int nr;
	__u32 arch;
	__u64 instruction_pointer;
	__u64 args[6];
};

#ifdef __KERNEL__
>>>>>>> 63fd7fc... seccomp: add "seccomp" syscall
#ifdef CONFIG_SECCOMP

#include <linux/thread_info.h>
#include <asm/seccomp.h>

typedef struct { int mode; } seccomp_t;

extern void __secure_computing(int);
static inline void secure_computing(int this_syscall)
{
	if (unlikely(test_thread_flag(TIF_SECCOMP)))
		__secure_computing(this_syscall);
}

extern long prctl_get_seccomp(void);
extern long prctl_set_seccomp(unsigned long);

static inline int seccomp_mode(seccomp_t *s)
{
	return s->mode;
}

#else /* CONFIG_SECCOMP */

#include <linux/errno.h>

typedef struct { } seccomp_t;

#define secure_computing(x) do { } while (0)

static inline long prctl_get_seccomp(void)
{
	return -EINVAL;
}

static inline long prctl_set_seccomp(unsigned long arg2)
{
	return -EINVAL;
}

static inline int seccomp_mode(seccomp_t *s)
{
	return 0;
}

#endif /* CONFIG_SECCOMP */

#endif /* _LINUX_SECCOMP_H */
