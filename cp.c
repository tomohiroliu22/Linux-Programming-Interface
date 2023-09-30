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
main(int argc, char *argv[])
{
    // cp code
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];
    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s old-file new-file\n", argv[0]);
        
    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1)
        errExit("opening file %s", argv[1]);
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1)
        errExit("opening file %s", argv[2]);
    unsigned int holeSize = 0;
    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
        for (int count = 0; count < numRead; count++) {
            if (buf[count] == '\0') {
                holeSize++;
            } else if (holeSize > 0) {
                lseek(outputFd, holeSize, SEEK_CUR);
                write(outputFd, &buf[count], 1);
                holeSize = 0;
            } else {
                write(outputFd, &buf[count], 1);
            }
        }
    }
    if(numRead == -1)
        errExit("read");
    if(close(inputFd) == -1)
        errExit("close input");
    if(close(outputFd)== -1)
        errExit("close output");
    return 0;
}
