/* t_dirbasename.c

   Demonstrate the use of dirname() and basename() to break a pathname
   into directory and filename components.

   Usage: t_dirbasename path...

   The program calls dirname() and basename() for each of the pathnames
   supplied on the command-line.
*/
#include <libgen.h>
#include "tlpi_hdr.h"
int
main(int argc, char *argv[])
{
    char *t1, *t2;
    int j;

    for (j = 1; j < argc; j++)  {
        t1 = strdup(argv[j]);
        if (t1 == NULL)
            errExit("strdup");
        t2 = strdup(argv[j]);
        if (t2 == NULL)
            errExit("strdup");

        printf("%s ==> %s + %s\n", argv[j], dirname(t1), basename(t2));

        free(t1);
        free(t2);
    }

    exit(EXIT_SUCCESS);
}
