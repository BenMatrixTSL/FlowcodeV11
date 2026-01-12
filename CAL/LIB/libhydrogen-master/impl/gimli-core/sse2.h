// CRC: 876150128DE39CBB738C8B441E478605FF8619720F3C9ECA02C246EC0B5408284DD7FBE47A08ABF4FA55D2932F1B1F547D585A9035156049CC803DDC48541E529440B604FA73E6547DF2312817327D353EB1963D8BA80C959C524C6199A66191622E4A10154D10ED53988D8E819F1E2C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF551D6C43E14F9BA98AC7A59574C2728D59AFE373F04E2B7D3B9519601CC1859E3F39B6CA7353C08BA63BCEABDDFD2175886F7C6B0D9F0C4AFB2BDAD57CFCEA613227B36DBC9A890FD837D68BCA94221E2AAB868E2FD3B9566549D34A0D5AD11F3930C68D4C553F5B38D053A3144DDF497E3B967339E029840
// REVISION: 1.0
// GUID: 2AA21227-A398-468A-BAA9-BED8EBDF43EC
// DATE: 08\08\2022
// DIR: CAL\LIB\libhydrogen-master\impl\gimli-core\sse2.h
#include <emmintrin.h>
#ifdef __SSSE3__
# include <tmmintrin.h>
#endif

#define S 9

static inline __m128i
shift(__m128i x, int bits)
{
    return _mm_slli_epi32(x, bits);
}

static inline __m128i
rotate(__m128i x, int bits)
{
    return _mm_slli_epi32(x, bits) | _mm_srli_epi32(x, 32 - bits);
}

#ifdef __SSSE3__
static inline __m128i
rotate24(__m128i x)
{
    return _mm_shuffle_epi8(x, _mm_set_epi8(12, 15, 14, 13, 8, 11, 10, 9, 4, 7, 6, 5, 0, 3, 2, 1));
}
#else
static inline __m128i
rotate24(__m128i x)
{
    uint8_t _hydro_attr_aligned_(16) x8[16], y8[16];

    _mm_storeu_si128((__m128i *) (void *) x8, x);

    y8[ 0] = x8[ 1]; y8[ 1] = x8[ 2]; y8[ 2] = x8[ 3]; y8[ 3] = x8[ 0];
    y8[ 4] = x8[ 5]; y8[ 5] = x8[ 6]; y8[ 6] = x8[ 7]; y8[ 7] = x8[ 4];
    y8[ 8] = x8[ 9]; y8[ 9] = x8[10]; y8[10] = x8[11]; y8[11] = x8[ 8];
    y8[12] = x8[13]; y8[13] = x8[14]; y8[14] = x8[15]; y8[15] = x8[12];

    return _mm_loadu_si128((const __m128i *) (const void *) y8);
}
#endif

static const uint32_t _hydro_attr_aligned_(16) coeffs[24] = {
    0x9e377904, 0, 0, 0, 0x9e377908, 0, 0, 0, 0x9e37790c, 0, 0, 0,
    0x9e377910, 0, 0, 0, 0x9e377914, 0, 0, 0, 0x9e377918, 0, 0, 0,
};

static void
gimli_core(uint32_t state[gimli_BLOCKBYTES / 4])
{
    __m128i x = _mm_loadu_si128((const __m128i *) (const void *) &state[0]);
    __m128i y = _mm_loadu_si128((const __m128i *) (const void *) &state[4]);
    __m128i z = _mm_loadu_si128((const __m128i *) (const void *) &state[8]);
    __m128i newy;
    __m128i newz;
    int     round;

    for (round = 5; round >= 0; round--) {
        x    = rotate24(x);
        y    = rotate(y, S);
        newz = x ^ shift(z, 1) ^ shift(y & z, 2);
        newy = y ^ x ^ shift(x | z, 1);
        x    = z ^ y ^ shift(x & y, 3);
        y    = newy;
        z    = newz;

        x = _mm_shuffle_epi32(x, _MM_SHUFFLE(2, 3, 0, 1));
        x ^= ((const __m128i *) (const void *) coeffs)[round];

        x    = rotate24(x);
        y    = rotate(y, S);
        newz = x ^ shift(z, 1) ^ shift(y & z, 2);
        newy = y ^ x ^ shift(x | z, 1);
        x    = z ^ y ^ shift(x & y, 3);
        y    = newy;
        z    = newz;

        x    = rotate24(x);
        y    = rotate(y, S);
        newz = x ^ shift(z, 1) ^ shift(y & z, 2);
        newy = y ^ x ^ shift(x | z, 1);
        x    = z ^ y ^ shift(x & y, 3);
        y    = newy;
        z    = newz;

        x = _mm_shuffle_epi32(x, _MM_SHUFFLE(1, 0, 3, 2));

        x    = rotate24(x);
        y    = rotate(y, S);
        newz = x ^ shift(z, 1) ^ shift(y & z, 2);
        newy = y ^ x ^ shift(x | z, 1);
        x    = z ^ y ^ shift(x & y, 3);
        y    = newy;
        z    = newz;
    }

    _mm_storeu_si128((__m128i *) (void *) &state[0], x);
    _mm_storeu_si128((__m128i *) (void *) &state[4], y);
    _mm_storeu_si128((__m128i *) (void *) &state[8], z);
}
