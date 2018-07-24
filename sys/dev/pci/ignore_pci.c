/*-
 * SPDX-License-Identifier: BSD-2-Clause-FreeBSD
 *
 * Copyright (c) 2000 Michael Smith <msmith@freebsd.org>
 * Copyright (c) 2000 BSDi
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

/*
 * 'Ignore' driver - eats devices that show up errnoeously on PCI
 * but shouldn't ever be listed or handled by a driver.
 */

#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/bus.h>

#include <dev/pci/pcivar.h>

static int	ignore_pci_probe(device_t dev);
struct pci_device_table ignore_pci_devs[] = {
	{PCI_DEV(0x1042, 0x1000),
	 PCI_DESCR("ignored")}
};

static device_method_t ignore_pci_methods[] = {
    /* Device interface */
    DEVMETHOD(device_probe,		ignore_pci_probe),
    DEVMETHOD(device_attach,		bus_generic_attach),
    { 0, 0 }
};

static driver_t ignore_pci_driver = {
    "ignore_pci",
    ignore_pci_methods,
    0,
};

static devclass_t ignore_pci_devclass;

DRIVER_MODULE(ignore_pci, pci, ignore_pci_driver, ignore_pci_devclass, 0, 0);
PCI_PNP_INFO(ignore_pci_devs);

static int
ignore_pci_probe(device_t dev)
{
	const struct pci_device_table *ignd;
	
	ignd = PCI_MATCH(dev, ignore_pci_devs);
	if (ignd == NULL)
		return (ENXIO);
	device_set_desc(dev, ignd->descr);
	return (BUS_PROBE_DEFAULT);
}
