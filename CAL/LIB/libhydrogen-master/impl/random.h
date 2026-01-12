// CRC: 876150128DE39CBB738C8B441E478605FF8619720F3C9ECA02C246EC0B5408284DD7FBE47A08ABF4FA55D2932F1B1F547D585A9035156049CC803DDC48541E5209CDF5531B2970AB56D31B932251C8749A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF51977BE996FF9F144BDD75DEF59BFFCB25BF172BFD991A7BE9D4E3C746D62BE660E070EB03A8E9A5D4F8E179E83CA0DDDC87D00B3D6E8785B0BF9FD62CEEA7D8926CD9C8084E52498544E5065749E9D402C2D21A7CF10EADA549D34A0D5AD11F3AD673CD809E721ED6D96732C696B2E2A36BBB6F8FF892A1F27FDDD94B8F81F9CD157EA94462C8AB8
// REVISION: 1.0
// GUID: E11A66D0-23F0-4AF6-BFD8-477B6925DDC7
// DATE: 08\08\2022
// DIR: CAL\LIB\libhydrogen-master\impl\random.h

static TLS struct {
    _hydro_attr_aligned_(16) uint8_t state[gimli_BLOCKBYTES];
    uint64_t counter;
    uint8_t  initialized;
    uint8_t  available;
} hydro_random_context;


#if defined(_WIN32)
	#include "random/windows.h"

#elif defined MX_CAL_ESP32
	#include "random/esp32.h"
	
#elif ((defined MX_CAL_STARM)&&(defined RNG))
	static int
	hydro_random_init(void)
	{
		const char       ctx[hydro_hash_CONTEXTBYTES] = { 'h', 'y', 'd', 'r', 'o', 'P', 'R', 'G' };
		hydro_hash_state st;
		uint16_t         ebits = 0;
		hydro_hash_init(&st, ctx, NULL);
		__HAL_RCC_RNG_CLK_ENABLE();
		RNG->CR |= RNG_CR_RNGEN;
		while (ebits < 256) {
			while (!(RNG->SR & (RNG_SR_DRDY)));
			uint32_t r = RNG->DR;
			hydro_hash_update(&st, (const uint32_t *) &r, sizeof r);
			ebits += 32;
		}
		RNG->CR &= ~RNG_CR_RNGEN;
		__HAL_RCC_RNG_CLK_DISABLE();
		hydro_hash_final(&st, hydro_random_context.state, sizeof hydro_random_context.state);
		hydro_random_context.counter = ~LOAD64_LE(hydro_random_context.state);
		return 0;
	}

#elif defined MX_CAL_RPI
	static int
	hydro_random_init(void)
	{
		const char       ctx[hydro_hash_CONTEXTBYTES] = { 'h', 'y', 'd', 'r', 'o', 'P', 'R', 'G' };
		hydro_hash_state st;
		uint16_t         ebits = 0;
		uint32_t         r;
		int fd = open( "/dev/urandom", O_RDONLY );
		hydro_hash_init(&st, ctx, NULL);
		if (fd >= 0) {
			while (ebits < 256) {
				read(fd, &r, sizeof r);
				hydro_hash_update(&st, (const uint32_t *) &r, sizeof r);
				ebits += 32;
			}
			close(fd);
		}
		hydro_hash_final(&st, hydro_random_context.state, sizeof hydro_random_context.state);
		hydro_random_context.counter = ~LOAD64_LE(hydro_random_context.state);
		return 0;
	}

#elif defined MX_CAL_PICO
	#include "hardware\structs\rosc.h"
	static int
	hydro_random_init(void)
	{
		const char       ctx[hydro_hash_CONTEXTBYTES] = { 'h', 'y', 'd', 'r', 'o', 'P', 'R', 'G' };
		hydro_hash_state st;
		uint16_t         ebits = 0;
		uint32_t         r;
		uint8_t          n;
		hydro_hash_init(&st, ctx, NULL);
		while (ebits < 256) {
			r = 0;
			for (n=0;n<32;n++) {
				r = r << 1;
				r = r + (1 & rosc_hw->randombit);
			}
			hydro_hash_update(&st, (const uint32_t *) &r, sizeof r);
			ebits += 32;
		}
		hydro_hash_final(&st, hydro_random_context.state, sizeof hydro_random_context.state);
		hydro_random_context.counter = ~LOAD64_LE(hydro_random_context.state);
		return 0;
	}

/**
#elif ((defined MX_CAL_AVR)||(defined MX_CAL_ARD))
#elif defined MX_CAL_ARM
#elif defined MX_CAL_PIC
#elif defined MX_CAL_PIC16
#elif defined MX_CAL_PIC32
**/
#else
	#warning This device does not have an RNG, a constant will be used as the seed.
	static int
	hydro_random_init(void)
	{
		const char       ctx[hydro_hash_CONTEXTBYTES] = { 'h', 'y', 'd', 'r', 'o', 'P', 'R', 'G' };
		const uint8_t    seed[32] = { 0x34,0xD0,0x64,0xF3,0x7B,0x18,0x93,0xC4,0xE1,0x05,0x6F,0x7A,0x48,0x82,0x31,0x6B,
									  0x54,0x8D,0x67,0x1D,0xD4,0x5B,0x2F,0x71,0x63,0xD8,0x83,0x5B,0x26,0x74,0xA4,0xB4 };
		hydro_hash_state st;
		uint8_t          tc;
		uint8_t          n = 0;
		hydro_hash_init(&st, ctx, NULL);
		while (n < 32) {
			tc = seed[n++];
			hydro_hash_update(&st, (const uint8_t *) &tc, sizeof tc);
		}
		hydro_hash_final(&st, hydro_random_context.state, sizeof hydro_random_context.state);
		hydro_random_context.counter = ~LOAD64_LE(hydro_random_context.state);
		return 0;
	}

#endif
  
static void
hydro_random_ensure_initialized(void)
{
    if (hydro_random_context.initialized == 0) {
        if (hydro_random_init() != 0) {
            abort();
        }
        gimli_core_u8(hydro_random_context.state, 0);
        hydro_random_ratchet();
        hydro_random_context.initialized = 1;
    }
}

void
hydro_random_ratchet(void)
{
    mem_zero(hydro_random_context.state, gimli_RATE);
    STORE64_LE(hydro_random_context.state, hydro_random_context.counter);
    hydro_random_context.counter++;
    gimli_core_u8(hydro_random_context.state, 0);
    hydro_random_context.available = gimli_RATE;
}

uint32_t
hydro_random_u32(void)
{
    uint32_t v;

    hydro_random_ensure_initialized();
    if (hydro_random_context.available < 4) {
        hydro_random_ratchet();
    }
    memcpy(&v, &hydro_random_context.state[gimli_RATE - hydro_random_context.available], 4);
    hydro_random_context.available -= 4;

    return v;
}

uint32_t
hydro_random_uniform(const uint32_t upper_bound)
{
    uint32_t min;
    uint32_t r;

    if (upper_bound < 2U) {
        return 0;
    }
    min = (1U + ~upper_bound) % upper_bound; /* = 2**32 mod upper_bound */
    do {
        r = hydro_random_u32();
    } while (r < min);
    /* r is now clamped to a set whose size mod upper_bound == 0
     * the worst case (2**31+1) requires 2 attempts on average */

    return r % upper_bound;
}

void
hydro_random_buf(void *out, size_t out_len)
{
    uint8_t *p = (uint8_t *) out;
    size_t   i;
    size_t   leftover;

    hydro_random_ensure_initialized();
    for (i = 0; i < out_len / gimli_RATE; i++) {
        gimli_core_u8(hydro_random_context.state, 0);
        memcpy(p + i * gimli_RATE, hydro_random_context.state, gimli_RATE);
    }
    leftover = out_len % gimli_RATE;
    if (leftover != 0) {
        gimli_core_u8(hydro_random_context.state, 0);
        mem_cpy(p + i * gimli_RATE, hydro_random_context.state, leftover);
    }
    hydro_random_ratchet();
}

void
hydro_random_buf_deterministic(void *out, size_t out_len,
                               const uint8_t seed[hydro_random_SEEDBYTES])
{
    static const uint8_t             prefix[] = { 7, 'd', 'r', 'b', 'g', '2', '5', '6' };
    _hydro_attr_aligned_(16) uint8_t state[gimli_BLOCKBYTES];
    uint8_t *                        p = (uint8_t *) out;
    size_t                           i;
    size_t                           leftover;

    mem_zero(state, gimli_BLOCKBYTES);
    COMPILER_ASSERT(sizeof prefix + 8 <= gimli_RATE);
    memcpy(state, prefix, sizeof prefix);
    STORE64_LE(state + sizeof prefix, (uint64_t) out_len);
    gimli_core_u8(state, 1);
    COMPILER_ASSERT(hydro_random_SEEDBYTES == gimli_RATE * 2);
    mem_xor(state, seed, gimli_RATE);
    gimli_core_u8(state, 2);
    mem_xor(state, seed + gimli_RATE, gimli_RATE);
    gimli_core_u8(state, 2);
    for (i = 0; i < out_len / gimli_RATE; i++) {
        gimli_core_u8(state, 0);
        memcpy(p + i * gimli_RATE, state, gimli_RATE);
    }
    leftover = out_len % gimli_RATE;
    if (leftover != 0) {
        gimli_core_u8(state, 0);
        mem_cpy(p + i * gimli_RATE, state, leftover);
    }
}

void
hydro_random_reseed(void)
{
    hydro_random_context.initialized = 0;
    hydro_random_ensure_initialized();
}
