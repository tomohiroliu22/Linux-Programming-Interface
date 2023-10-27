/* t_umount.c

   Demonstrate the use of the umount() system call to unmount a mount point.

   Usage: t_umount mount-point

   This program is Linux-specific.
*/
#include <sys/mount.h>
#include "tlpi_hdr.h"
int
main(int argc, char *argv[])
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s mount-point\n", argv[0]);

    if (umount(argv[1]) == -1)
        errExit("umount");

    exit(EXIT_SUCCESS);
}
