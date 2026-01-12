// CRC: 876150128DE39CBB738C8B441E478605FF8619720F3C9ECA02C246EC0B5408284DD7FBE47A08ABF4FA55D2932F1B1F547D585A9035156049CC803DDC48541E52812A61DF4283435F98C3C5842E7F26CB1B18126849B7BB40287D4C9ECF31C2E5622E4A10154D10ED53988D8E819F1E2C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF54F6B1A340B48EB07CB0C26FFBCD2DFD46FE868756AD99A6CB4B1D073784FAF498D4D3244496EB032F90430981AB0B2D4662B3925A55C4F9D55849B9BCA30A0F6C4F15530AE0071859BB987FDD3D6C95332ABD86F69D29E03549D34A0D5AD11F3EC2EB6FEAB8A79D48063604A9980408D0AFBAC211DA0F4F65D2E1919BC6D834D57C406BC4A49D3F1
// REVISION: 1.0
// GUID: 384F98DA-24E4-458B-B233-1D11C32A5D97
// DATE: 08\08\2022
// DIR: CAL\LIB\libhydrogen-master\impl\random\particle.h
// Note: All particle platforms except for the Spark Core have a HW RNG.  Only allow building on
// supported platforms for now. PLATFORM_ID definitions:
// https://github.com/particle-iot/device-os/blob/mesh-develop/hal/shared/platforms.h

#include <Particle.h>

static int
hydro_random_init(void)
{
    const char       ctx[hydro_hash_CONTEXTBYTES] = { 'h', 'y', 'd', 'r', 'o', 'P', 'R', 'G' };
    hydro_hash_state st;
    uint16_t         ebits = 0;

    hydro_hash_init(&st, ctx, NULL);

    while (ebits < 256) {
        uint32_t r = HAL_RNG_GetRandomNumber();
        hydro_hash_update(&st, (const uint32_t *) &r, sizeof r);
        ebits += 32;
    }

    hydro_hash_final(&st, hydro_random_context.state, sizeof hydro_random_context.state);
    hydro_random_context.counter = ~LOAD64_LE(hydro_random_context.state);

    return 0;
}
