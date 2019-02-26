/* wrmsr.c - Write CPU model-specific registers */
/*
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 2019  Free Software Foundation, Inc.
 *  Based on gcc/gcc/config/i386/driver-i386.c
 *
 *  GRUB is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  GRUB is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GRUB.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <grub/dl.h>
#include <grub/misc.h>
#include <grub/mm.h>
#include <grub/env.h>
#include <grub/command.h>
#include <grub/extcmd.h>
#include <grub/i386/wrmsr.h>
#include <grub/i18n.h>

GRUB_MOD_LICENSE("GPLv3+");

static grub_command_t cmd_write;

static grub_err_t
grub_cmd_msr_write (grub_command_t cmd __attribute__ ((unused)), int argc, char **argv)
{
    grub_uint64_t addr, value;

    if (argc != 2)
        return grub_error (GRUB_ERR_BAD_ARGUMENT, N_("two arguments expected"));

    addr = grub_strtoul (argv[0], 0, 0);

    value = grub_strtoul (argv[1], 0, 0);

    grub_msr_write (addr, value);

    return GRUB_ERR_NONE;
}

GRUB_MOD_INIT(wrmsr)
{
    cmd_write = grub_register_command ("wrmsr", grub_cmd_msr_write,
                                      N_("ADDR VALUE"),
                                      N_("Write a value to a CPU model specific register."));
}

GRUB_MOD_FINI(wrmsr)
{
    grub_unregister_command (cmd_write);
}