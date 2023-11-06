/* t_setxattr.c

   Demonstrate the use of setxattr() to set a file extended attribute.

   This program is Linux (2.6 and later) specific.

   See also view_xattr.c.
*/
#include <sys/xattr.h>
#include "tlpi_hdr.h"
int
main(int argc, char *argv[])
{
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    char *value = "The past is not dead.";
    if (setxattr(argv[1], "user.x", value, strlen(value), 0) == -1)
        errExit("setxattr");

    value = "In fact, it's not even past.";
    if (setxattr(argv[1], "user.y", value, strlen(value), 0) == -1)
        errExit("setxattr");

    exit(EXIT_SUCCESS);
}
