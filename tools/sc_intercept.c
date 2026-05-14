/*
 * sc_intercept.c — LD_PRELOAD ioctl interceptor for cmd_sc SC_CMD_VERIFY
 * No libc dependency: raw MIPS O32 syscalls only.
 * $v0-direct macro: returns $v0 directly; kernel errors are large positive
 * values (errno), which fds never are, so `if (fd > 2)` guards work.
 */

#define SC_CMD_VERIFY 0xc0047300UL
#define BUF_SIZE      0x800

#define SYS_write   4004
#define SYS_open    4005
#define SYS_close   4006
#define SYS_ioctl   4054

#define O_WRONLY    0x1
#define O_CREAT     0x40
#define O_TRUNC     0x200

#define __sc3(n, a, b, c) ({                                    \
    register long __v0 __asm__("$v0") = (long)(n);             \
    register long __a0 __asm__("$a0") = (long)(a);             \
    register long __a1 __asm__("$a1") = (long)(b);             \
    register long __a2 __asm__("$a2") = (long)(c);             \
    __asm__ __volatile__("syscall"                              \
        : "+r"(__v0) : "r"(__a0), "r"(__a1), "r"(__a2)        \
        : "$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7",    \
          "$t8","$t9","$at","$a3","memory");                    \
    __v0; })

static long _open(const char *p, int f, int m) { return __sc3(SYS_open, p, f, m); }
static long _write(int fd, const void *b, long n) { return __sc3(SYS_write, fd, b, n); }
static long _close(int fd) { return __sc3(SYS_close, fd, 0, 0); }
static long _ioctl(int fd, unsigned long r, void *a) { return __sc3(SYS_ioctl, fd, r, a); }

static void whex(int fd, unsigned long v) {
    char b[10] = "0x";
    int i;
    for (i = 7; i >= 2; i--) {
        int n = v & 0xf;
        b[i] = n < 10 ? '0'+n : 'a'+n-10;
        v >>= 4;
    }
    b[8] = '\n'; _write(fd, b, 9);
}
static void wstr(int fd, const char *s) {
    int n = 0; while (s[n]) n++;
    _write(fd, s, n);
}

__attribute__((constructor))
static void _init(void) { _write(2, "sc_intercept: loaded\n", 21); }

int ioctl(int fd, unsigned long request, void *arg) {
    if (request == SC_CMD_VERIFY) {
        unsigned char **sc = (unsigned char **)arg;
        unsigned char  *data = sc[0];
        unsigned char  *out  = sc[1];

        /* Build path on stack — avoids GOT-relative addressing issues */
        char pbin[] = {'/','t','m','p','/','s','c','.','b','i','n',0};
        char plog[] = {'/','t','m','p','/','s','c','.','l','o','g',0};

        /* Confirm path is accessible */
        _write(2, "path=", 5); _write(2, pbin, 11); _write(2, "\n", 1);

        /* Save raw 2048-byte SCBT input buffer */
        long fbin = _open(pbin, O_WRONLY|O_TRUNC, 0);
        if (fbin > 2) { _write(fbin, data, BUF_SIZE); _close(fbin); }

        long ret = _ioctl(fd, request, arg);

        /* Log result */
        long flog = _open(plog, O_WRONLY|O_TRUNC, 0);
        if (flog > 2) {
            unsigned long phys, sz, m0;
            __builtin_memcpy(&phys, data+0x200, 4);
            __builtin_memcpy(&sz,   data+0x208, 4);
            __builtin_memcpy(&m0,   data+0x300, 4);
            wstr(flog, "ret=");   whex(flog, (unsigned long)ret);
            wstr(flog, "phys=");  whex(flog, phys);
            wstr(flog, "size=");  whex(flog, sz);
            wstr(flog, "mod0=");  whex(flog, m0);
            if (out) {
                unsigned long ov; __builtin_memcpy(&ov, out, 4);
                wstr(flog, "out="); whex(flog, ov);
            }
            _close(flog);
        }

        /* Debug to stderr */
        _write(2, "SC_CMD_VERIFY ret=", 18); whex(2, (unsigned long)ret);
        _write(2, "fbin=", 5); whex(2, (unsigned long)fbin);
        _write(2, "flog=", 5); whex(2, (unsigned long)flog);

        return (int)ret;
    }
    return (int)_ioctl(fd, request, arg);
}
