/*
 * be_impl.h
 *
 * Copyright (c) 2017 Kyle J. Kneitinger <kyle@kneit.in>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _LIBBE_IMPL_H
#define _LIBBE_IMPL_H

#include <libzfs.h>

#include "be.h"


struct libbe_handle {
	libzfs_handle_t *lzh;
	zpool_handle_t *active_phandle;
	char root[BE_MAXPATHLEN];
	char rootfs[BE_MAXPATHLEN];
	char bootfs[BE_MAXPATHLEN];
	be_error_t error;
	bool print_on_err;
};

struct libbe_deep_clone {
	libbe_handle_t *lbh;
	const char *bename;
	const char *snapname;
	const char *be_root;
};

struct libbe_dccb {
	zfs_handle_t *zhp;
	nvlist_t *props;
};

int set_error(libbe_handle_t *, be_error_t);

#endif  /* _LIBBE_IMPL_H */
