// CRC: 876150128DE39CBB738C8B441E478605FF8619720F3C9ECA02C246EC0B5408284DD7FBE47A08ABF4FA55D2932F1B1F547D585A9035156049CC803DDC48541E52641F32BB4AEC16FEB0067CC9DF2E45C3FA77608910F902FD0C34883AC2567D199A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5C472587870799752226F569CD8DD81F175113422241232B516B43CDDA02C48E3397B5B86FEE21AAC8F19F9ACB8B95CF75006195B08D5BF0A75BBF60D60718BC31CCE3BDFBEAF0C85ECE62C0E44F2FE221BB7874C60A8CA6C549D34A0D5AD11F31D6CF939083D58F5D3332FCEB75D8D8EAA1358A150171E0A6C38C782664ADBC14BD5B47FBC6A6D19
// REVISION: 1.0
// GUID: 2F73B372-3B01-478D-A9F4-2169AE27F7E4
// DATE: 08\08\2022
// DIR: CAL\LIB\libhydrogen-master\impl\hydrogen_p.h
static int hydro_random_init(void);

/* ---------------- */

#define gimli_BLOCKBYTES 48
#define gimli_CAPACITY   32
#define gimli_RATE       16

#define gimli_TAG_HEADER  0x01
#define gimli_TAG_PAYLOAD 0x02
#define gimli_TAG_FINAL   0x08
#define gimli_TAG_FINAL0  0xf8
#define gimli_TAG_KEY0    0xfe
#define gimli_TAG_KEY     0xff

#define gimli_DOMAIN_AEAD 0x0
#define gimli_DOMAIN_XOF  0xf

static void gimli_core_u8(uint8_t state_u8[gimli_BLOCKBYTES], uint8_t tag);

static inline void
gimli_pad_u8(uint8_t buf[gimli_BLOCKBYTES], size_t pos, uint8_t domain)
{
    buf[pos] ^= (domain << 1) | 1;
    buf[gimli_RATE - 1] ^= 0x80;
}

static inline void
hydro_mem_ct_zero_u32(uint32_t *dst_, size_t n)
{
    volatile uint32_t *volatile dst = (volatile uint32_t *volatile) (void *) dst_;
    size_t i;

    for (i = 0; i < n; i++) {
        dst[i] = 0;
    }
}

static inline uint32_t hydro_mem_ct_cmp_u32(const uint32_t *b1_, const uint32_t *b2,
                                            size_t n) _hydro_attr_warn_unused_result_;

static inline uint32_t
hydro_mem_ct_cmp_u32(const uint32_t *b1_, const uint32_t *b2, size_t n)
{
    const volatile uint32_t *volatile b1 = (const volatile uint32_t *volatile) (const void *) b1_;
    size_t   i;
    uint32_t cv = 0;

    for (i = 0; i < n; i++) {
        cv |= b1[i] ^ b2[i];
    }
    return cv;
}

/* ---------------- */

static int hydro_hash_init_with_tweak(hydro_hash_state *state,
                                      const char ctx[hydro_hash_CONTEXTBYTES], uint64_t tweak,
                                      const uint8_t key[hydro_hash_KEYBYTES]);

/* ---------------- */

#define hydro_secretbox_NONCEBYTES 20
#define hydro_secretbox_MACBYTES   16

/* ---------------- */

#define hydro_x25519_BYTES          32
#define hydro_x25519_PUBLICKEYBYTES 32
#define hydro_x25519_SECRETKEYBYTES 32

static int hydro_x25519_scalarmult(uint8_t       out[hydro_x25519_BYTES],
                                   const uint8_t scalar[hydro_x25519_SECRETKEYBYTES],
                                   const uint8_t x1[hydro_x25519_PUBLICKEYBYTES],
                                   bool          clamp) _hydro_attr_warn_unused_result_;

static inline int hydro_x25519_scalarmult_base(uint8_t       pk[hydro_x25519_PUBLICKEYBYTES],
                                               const uint8_t sk[hydro_x25519_SECRETKEYBYTES])
    _hydro_attr_warn_unused_result_;

static inline void
hydro_x25519_scalarmult_base_uniform(uint8_t       pk[hydro_x25519_PUBLICKEYBYTES],
                                     const uint8_t sk[hydro_x25519_SECRETKEYBYTES]);
