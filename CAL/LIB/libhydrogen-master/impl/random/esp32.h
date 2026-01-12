// CRC: 876150128DE39CBB738C8B441E478605FF8619720F3C9ECA02C246EC0B5408284DD7FBE47A08ABF4FA55D2932F1B1F547D585A9035156049CC803DDC48541E525B2C39186A4808247C2B19911810BD2B6ADDC588B497F5964C2D4AB8CA1E85CA9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF544DEF47B5622ACD805123E09F73B95DE92BB3A04E8EA85E837E34513B0A564A488DA2B2301F69601F7DDFF16CA5C49F1280DFED5A64FB6A43F400C4D97612C56BD54BEFBA3BE67E9262C37A9C13CEFB8A61930F97993E62D549D34A0D5AD11F3639E9F8E713DD769BEB2C27F8793C81498D23448D436A899E00AF8598B7CA62D1079227E43D7E189
// REVISION: 1.0
// GUID: DCEA25FE-D02B-49B7-964E-A3DE6467E7E7
// DATE: 08\08\2022
// DIR: CAL\LIB\libhydrogen-master\impl\random\esp32.h
// Important: RF *must* be activated on ESP board
// https://techtutorialsx.com/2017/12/22/esp32-arduino-random-number-generation/
#ifdef ESP32
#include <esp_system.h>
#endif

#ifdef ARDUINO
#include <Arduino.h>
#endif

static int
hydro_random_init(void)
{
    const char       ctx[hydro_hash_CONTEXTBYTES] = { 'h', 'y', 'd', 'r', 'o', 'P', 'R', 'G' };
    hydro_hash_state st;
    uint16_t         ebits = 0;

    hydro_hash_init(&st, ctx, NULL);

    while (ebits < 256) {
        uint32_t r = esp_random();

        delay(10);
        hydro_hash_update(&st, (const uint32_t *) &r, sizeof r);
        ebits += 32;
    }

    hydro_hash_final(&st, hydro_random_context.state, sizeof hydro_random_context.state);
    hydro_random_context.counter = ~LOAD64_LE(hydro_random_context.state);

    return 0;
}
