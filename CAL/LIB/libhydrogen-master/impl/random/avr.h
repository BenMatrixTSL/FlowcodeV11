// CRC: 876150128DE39CBB738C8B441E478605FF8619720F3C9ECA02C246EC0B5408284DD7FBE47A08ABF4FA55D2932F1B1F547D585A9035156049CC803DDC48541E52F9863C3C2295D00D68FCDEA1D766A6A5D9D92F405F4D9CF0ED5D450DFD95A9C39A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF546FC3E834C350B197A2A4552246DA94B79EB80486FCA7C4FD1BB0969A0BB9DDE77E92E1EBAFFCC8A92EF9BE19A5ABC076A05F8A064F45536EDC98AC0430CB84DBA647205B3E92529D7728CD406BD4FD779CE93A87C33DEAD549D34A0D5AD11F3B1E9F5C1EF7ED7A4FE086D16B56707ACEEBB7E5BC318B7A404789BB7D1BE12C9008FFBF4203128CD
// REVISION: 1.0
// GUID: 1F1A886A-222E-449C-AEF1-5B6164506AEE
// DATE: 08\08\2022
// DIR: CAL\LIB\libhydrogen-master\impl\random\avr.h
#include <Arduino.h>

static bool
hydro_random_rbit(uint16_t x)
{
    uint8_t x8;

    x8 = ((uint8_t) (x >> 8)) ^ (uint8_t) x;
    x8 = (x8 >> 4) ^ (x8 & 0xf);
    x8 = (x8 >> 2) ^ (x8 & 0x3);
    x8 = (x8 >> 1) ^ x8;

    return (bool) (x8 & 1);
}

static int
hydro_random_init(void)
{
    const char       ctx[hydro_hash_CONTEXTBYTES] = { 'h', 'y', 'd', 'r', 'o', 'P', 'R', 'G' };
    hydro_hash_state st;
    uint16_t         ebits = 0;
    uint16_t         tc;
    bool             a, b;

    cli();
    MCUSR = 0;
    WDTCSR |= _BV(WDCE) | _BV(WDE);
    WDTCSR = _BV(WDIE);
    sei();

    hydro_hash_init(&st, ctx, NULL);

    while (ebits < 256) {
        delay(1);
        tc = TCNT1;
        hydro_hash_update(&st, (const uint8_t *) &tc, sizeof tc);
        a = hydro_random_rbit(tc);
        delay(1);
        tc = TCNT1;
        b  = hydro_random_rbit(tc);
        hydro_hash_update(&st, (const uint8_t *) &tc, sizeof tc);
        if (a == b) {
            continue;
        }
        hydro_hash_update(&st, (const uint8_t *) &b, sizeof b);
        ebits++;
    }

    cli();
    MCUSR = 0;
    WDTCSR |= _BV(WDCE) | _BV(WDE);
    WDTCSR = 0;
    sei();

    hydro_hash_final(&st, hydro_random_context.state, sizeof hydro_random_context.state);
    hydro_random_context.counter = ~LOAD64_LE(hydro_random_context.state);

    return 0;
}

ISR(WDT_vect) { }
