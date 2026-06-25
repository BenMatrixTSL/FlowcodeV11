// CRC: D3A5712EBD65B64EC20166ACC65F8397FC2322FE9FE7B5D7EBD046A377DBDFAB7F513EE40AB4316818B9676B8B43CF56A54A2ADCDF3B87E1237188660FCD9BBC2BBB7B1CC80F12CBA9B11F738DF98E15303CB7344801E1CFEF3D684E778C6B7BFB335ADF6A82F3BD9237DD475310E67826FA7504F3F7C2402E2CE9005B6C594029DAA3C36F4262D56051AE80582A001614C8922195D6C0C9D55EC15358C26E6F6AFED223F004AFE0549D34A0D5AD11F3AB993BBE8EF0E197E00C7326F115C4AFF96AA2DFD46C7F5EFFCF1C90B393605E9F32B96E9FC2F3A9
// REVISION: 1.0
// GUID: B0C1D2E3-F4A5-6789-3456-890123456789
// DATE: 25\06\2026
// DIR: FCD\RE\src\syscalls.c
/*
 * Newlib minimal syscalls for Renesas RA targets (bare metal, no OS).
 * Identical to the STARM version - these are architecture-independent.
 */

#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

extern int errno;
extern int __io_putchar(int ch) __attribute__((weak));
extern int __io_getchar(void) __attribute__((weak));

register char * stack_ptr asm("sp");

char *__env[1] = { 0 };
char **environ = __env;

void initialise_monitor_handles(void) {}

int _getpid(void) { return 1; }

int _kill(int pid, int sig)
{
    errno = EINVAL;
    return -1;
}

void _exit(int status)
{
    _kill(status, -1);
    while (1) {}
}

int _read(int file, char *ptr, int len)
{
    int i;
    for (i = 0; i < len; i++)
        *ptr++ = __io_getchar();
    return len;
}

int _write(int file, char *ptr, int len)
{
    int i;
    for (i = 0; i < len; i++)
        __io_putchar(*ptr++);
    return len;
}

caddr_t _sbrk(int incr)
{
    extern char end asm("end");
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0)
        heap_end = &end;

    prev_heap_end = heap_end;
    if (heap_end + incr > stack_ptr) {
        errno = ENOMEM;
        return (caddr_t)-1;
    }
    heap_end += incr;
    return (caddr_t)prev_heap_end;
}

int _close(int file)  { return -1; }
int _fstat(int file, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
int _isatty(int file) { return 1; }
int _lseek(int file, int ptr, int dir) { return 0; }
int _open(char *path, int flags, ...) { return -1; }
int _wait(int *status) { errno = ECHILD; return -1; }
int _unlink(char *name) { errno = ENOENT; return -1; }
int _times(struct tms *buf) { return -1; }
int _stat(char *file, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
int _link(char *old, char *new) { errno = EMLINK; return -1; }
int _fork(void) { errno = EAGAIN; return -1; }
int _execve(char *name, char **argv, char **env) { errno = ENOMEM; return -1; }
