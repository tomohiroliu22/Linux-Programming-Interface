/*
Implementing the Linux tee instruction with C.
The additional libray "tlpi_hdr.h" 
can be found on https://man7.org/tlpi/code/online/all_files_by_chapter.html
*/
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "tlpi_hdr.h"
#ifndef BUF_SIZE        
#define BUF_SIZE 1024
#endif
int 
main(int argc, char const *argv[])
{
    // tee code
    int fd, openFlags, opt;
    mode_t filePerms;
    ssize_t numRead, numWritten, numWritten2;
    char buf[BUF_SIZE+1];
    if (argc<2){
        usageErr("Usage: %s [-a] output-filename\n", argv[0]);
    }
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    while ((opt = getopt(argc, argv, ":a")) != -1) {
        switch (opt) {
            case 'a':
                openFlags = O_CREAT | O_WRONLY | O_APPEND;
                break;
            case '?':
                usageErr("Usage: %s [-a] output-filename\n", argv[0]);
        }
    }
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    fd = open(argv[argc-1], openFlags, filePerms);
    if (fd == -1)
        errExit("opening file %s\n", argv[argc-1]);
    while ((numRead= read (STDIN_FILENO, buf, BUF_SIZE)) != 0){
        numWritten = write(fd, buf, numRead);
        numWritten2 = write(STDOUT_FILENO, buf, numRead);
        if (numWritten != numRead)
            errExit("write file %s\n",argv[argc-1]);
        if (numWritten2 != numRead)
            errExit("stdout\n");
    }
    if (close(fd) == -1)
        errExit("close file %s error\n",argv[argc-1]);
    return 0;
}
