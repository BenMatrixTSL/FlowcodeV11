// CRC: 876150128DE39CBB738C8B441E478605FF8619720F3C9ECA02C246EC0B5408284DD7FBE47A08ABF4FA55D2932F1B1F547D585A9035156049CC803DDC48541E528F448265AF6BB5A509E70F2D8676ACFC60EAFD3EAF9BF76100AD792AFF755F7C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF50903CD3E33B5A782060486F7EC0E3FF9B67EBC7A8F8CB73F9292DBFCF396F286EA085076FEEBA0FE4BD613DAE0DC752FBCC64FBD490A51C0F4A0600F3B6892A90A24B5A04DC0BF15CE8E22B737D8ADB432ABD86F69D29E03549D34A0D5AD11F35C43103AF5258BF46B811B6FFF847961E0D5511B17A33A80A3608A0B0CE69F969622A912E6E6A2FB
// REVISION: 1.0
// GUID: 467369E3-396A-4192-B8E6-33BFFE07F03A
// DATE: 08\08\2022
// DIR: CAL\LIB\libhydrogen-master\impl\random\unix.h
#include <errno.h>
#include <fcntl.h>
#ifdef __linux__
#include <poll.h>
#endif
#include <sys/types.h>
#include <unistd.h>

#ifdef __linux__
static int
hydro_random_block_on_dev_random(void)
{
    struct pollfd pfd;
    int           fd;
    int           pret;

    fd = open("/dev/random", O_RDONLY);
    if (fd == -1) {
        return 0;
    }
    pfd.fd      = fd;
    pfd.events  = POLLIN;
    pfd.revents = 0;
    do {
        pret = poll(&pfd, 1, -1);
    } while (pret < 0 && (errno == EINTR || errno == EAGAIN));
    if (pret != 1) {
        (void) close(fd);
        errno = EIO;
        return -1;
    }
    return close(fd);
}
#endif

static ssize_t
hydro_random_safe_read(const int fd, void *const buf_, size_t len)
{
    unsigned char *buf = (unsigned char *) buf_;
    ssize_t        readnb;

    do {
        while ((readnb = read(fd, buf, len)) < (ssize_t) 0 && (errno == EINTR || errno == EAGAIN)) {
        }
        if (readnb < (ssize_t) 0) {
            return readnb;
        }
        if (readnb == (ssize_t) 0) {
            break;
        }
        len -= (size_t) readnb;
        buf += readnb;
    } while (len > (ssize_t) 0);

    return (ssize_t) (buf - (unsigned char *) buf_);
}

static int
hydro_random_init(void)
{
    uint8_t tmp[gimli_BLOCKBYTES + 8];
    int     fd;
    int     ret = -1;

#ifdef __linux__
    if (hydro_random_block_on_dev_random() != 0) {
        return -1;
    }
#endif
    do {
        fd = open("/dev/urandom", O_RDONLY);
        if (fd == -1 && errno != EINTR) {
            return -1;
        }
    } while (fd == -1);
    if (hydro_random_safe_read(fd, tmp, sizeof tmp) == (ssize_t) sizeof tmp) {
        memcpy(hydro_random_context.state, tmp, gimli_BLOCKBYTES);
        memcpy(&hydro_random_context.counter, tmp + gimli_BLOCKBYTES, 8);
        hydro_memzero(tmp, sizeof tmp);
        ret = 0;
    }
    ret |= close(fd);

    return ret;
}
