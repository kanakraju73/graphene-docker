/* Copyright (C) 2003-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@redhat.com>, 2003.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <sched.h>
#include <signal.h>
#include <sysdep.h>
#include <tls.h>

/* In Graphene, we prefer to call fork system call directly than clone */
#if USE_clone_FOR_fork
# define ARCH_FORK() \
  INLINE_SYSCALL (clone, 4,						      \
		  CLONE_CHILD_SETTID | CLONE_CHILD_CLEARTID | SIGCHLD, 0,     \
		  NULL, &THREAD_SELF->tid)
#else
# define ARCH_FORK() \
 ({ unsigned long ret = INLINE_SYSCALL (fork, 0);	\
    if (!ret) {						\
	pid_t pid = INLINE_SYSCALL (getpid, 0);		\
	THREAD_SETMEM (THREAD_SELF, pid, pid);		\
	THREAD_SETMEM (THREAD_SELF, tid, pid);		\
    } ret; })
#endif

#include "../fork.c"
