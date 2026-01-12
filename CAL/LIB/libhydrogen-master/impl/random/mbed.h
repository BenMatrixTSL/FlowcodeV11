// CRC: 876150128DE39CBB738C8B441E478605FF8619720F3C9ECA02C246EC0B5408284DD7FBE47A08ABF4FA55D2932F1B1F547D585A9035156049CC803DDC48541E526B10B9FCDC9DE4DC2D054B5F94746BE9050237DF488C3410A04E334EB53479619A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF59A28E0D4F7C7BAFA1EB9F4F3CCBAD764502762EB76F309D2FACB9686B08A5A69912646FD0AA46DE93F94F29F7FEF4F3687457ED2566AD181461CE3E057EE8EBFECF1F57BD3EE3BB1F6F90588515EAE24F37A7309679571A6549D34A0D5AD11F385FC4D8486BC5E42C0BCBB9A4AB7D9523A8FCE803D1021C676AD1A7DB9B9D5F43F565616D7803A54
// REVISION: 1.0
// GUID: 66878C5B-B9C7-45AF-96A8-0A701F73DF49
// DATE: 08\08\2022
// DIR: CAL\LIB\libhydrogen-master\impl\random\mbed.h
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/entropy.h>

#if defined(MBEDTLS_ENTROPY_C)

static int
hydro_random_init(void)
{
    mbedtls_entropy_context entropy;
    uint16_t                pos = 0;

    mbedtls_entropy_init(&entropy);

    // Pull data directly out of the entropy pool for the state, as it's small enough.
    if (mbedtls_entropy_func(&entropy, (uint8_t *) &hydro_random_context.counter,
                             sizeof hydro_random_context.counter) != 0) {
        return -1;
    }
    // mbedtls_entropy_func can't provide more than MBEDTLS_ENTROPY_BLOCK_SIZE in one go.
    // This constant depends of mbedTLS configuration (whether the PRNG is backed by SHA256/SHA512
    // at this time) Therefore, if necessary, we get entropy multiple times.

    do {
        const uint8_t dataLeftToConsume = gimli_BLOCKBYTES - pos;
        const uint8_t currentChunkSize  = (dataLeftToConsume > MBEDTLS_ENTROPY_BLOCK_SIZE)
                                              ? MBEDTLS_ENTROPY_BLOCK_SIZE
                                              : dataLeftToConsume;

        // Forces mbedTLS to fetch fresh entropy, then get some to feed libhydrogen.
        if (mbedtls_entropy_gather(&entropy) != 0 ||
            mbedtls_entropy_func(&entropy, &hydro_random_context.state[pos], currentChunkSize) !=
                0) {
            return -1;
        }
        pos += MBEDTLS_ENTROPY_BLOCK_SIZE;
    } while (pos < gimli_BLOCKBYTES);

    mbedtls_entropy_free(&entropy);

    return 0;
}
#else
#error Need an entropy source
#endif
