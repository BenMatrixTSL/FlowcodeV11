// CRC: 876150128DE39CBB738C8B441E478605FF8619720F3C9ECA02C246EC0B5408284DD7FBE47A08ABF4FA55D2932F1B1F547D585A9035156049CC803DDC48541E521A3EF09F4FD474FC798F4546DA9EFE05246FFFBA283285F84A53B6502F28F54C622E4A10154D10ED53988D8E819F1E2C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5E388E1D3913DAE11A482FB759CAEF6281D642A9AD0966CE6AA7AF76FBD0272690AF8E06DD444E8600223CD2E1682608CBE741F7E8B8B9E801ABD134AD71B1E8ADA2461690CF91A29BF46E1CD0E03FF374D57A5A1904C629E549D34A0D5AD11F34847AEE64B6E84A24429A00AEA0F8A1BF0E16600E4FC7F8DC7ABCD5CF34FF6593854791B315FCCEE
// REVISION: 1.0
// GUID: 15D31795-372C-4503-AA03-0040D62136AA
// DATE: 08\08\2022
// DIR: CAL\LIB\libhydrogen-master\impl\random\rtthread.h
#include <rtthread.h>
#include <hw_rng.h>

#define DBG_TAG "libhydrogen"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

static int
hydrogen_init(void) {
    if (hydro_init() != 0) {
        abort();
    }
    LOG_I("libhydrogen initialized");
    return 0;
}
INIT_APP_EXPORT(hydrogen_init);

static int
hydro_random_init(void)
{
    const char       ctx[hydro_hash_CONTEXTBYTES] = { 'h', 'y', 'd', 'r', 'o', 'P', 'R', 'G' };
    hydro_hash_state st;
    uint16_t         ebits = 0;

    hydro_hash_init(&st, ctx, NULL);

    while (ebits < 256) {
        uint32_t r = rt_hwcrypto_rng_update();
        hydro_hash_update(&st, (const uint32_t *) &r, sizeof r);
        ebits += 32;
    }

    hydro_hash_final(&st, hydro_random_context.state, sizeof hydro_random_context.state);
    hydro_random_context.counter = ~LOAD64_LE(hydro_random_context.state);

    return 0;
}
