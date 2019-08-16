/*
 * Copyright (c) 2015 Fingerprint Cards AB <tech@fingerprints.com>
 *
 * All rights are reserved.
 * Proprietary and confidential.
 * Unauthorized copying of this file, via any medium is strictly prohibited.
 * Any use is subject to an appropriate license granted by Fingerprint Cards AB.
 */

//#include <dirent.h>
#include <fcntl.h>
//#include <poll.h>
//#include <linux/input.h>
#include <sys/types.h>
#include <errno.h>
//#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fpc_log.h"
#include "fpc_types.h"


int fpc_sysfs_path_by_attr(const char *attr, const char *attr_val,
                                 const char *base, char *path, int path_max)
{
    return 1;
}

int fpc_sysfs_node_write(int base_fd, const char* name, const char* value)
{
    return 1;
}
