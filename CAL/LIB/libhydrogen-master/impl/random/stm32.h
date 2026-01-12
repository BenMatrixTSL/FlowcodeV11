// CRC: 876150128DE39CBB738C8B441E478605FF8619720F3C9ECA02C246EC0B5408284DD7FBE47A08ABF4FA55D2932F1B1F547D585A9035156049CC803DDC48541E52907A52E1C425C29628259909CF353393B5DA8143F7544504E81B888E622DA17B9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF592962C6E50C476C2136C2E295EE32FD315E780050BC49C02C56F5C98555362DF6DC1EA91BC1B9C6213E5A8EEE0558E867D3190EA6B890D3E928682AB4353A91DDE00702AE9E9457E491618CC6F44D79AE2A9F7840D9199D9549D34A0D5AD11F3B7422806609A5FAE8AD554117DDB59726F774A397E26E4CBA44501DE8C4E8A8748A9453D8E52754C
// REVISION: 1.0
// GUID: 5B70BD7B-EED1-4566-BBA2-1B465A5037B5
// DATE: 08\08\2022
// DIR: CAL\LIB\libhydrogen-master\impl\random\stm32.h

// Use hardware RNG peripheral
// Working with HAL, LL Driver (untested)

#ifdef STM32F4

#include "stm32f4xx.h"

static int
hydro_random_init(void)
{
    const char       ctx[hydro_hash_CONTEXTBYTES] = { 'h', 'y', 'd', 'r', 'o', 'P', 'R', 'G' };
    hydro_hash_state st;
    uint16_t         ebits = 0;

    __IO uint32_t tmpreg;

    // Enable RNG clock source
    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN);

    // Delay after an RCC peripheral clock enabling
    tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN);
    UNUSED(tmpreg);

    // RNG Peripheral enable
    SET_BIT(RNG->CR, RNG_CR_RNGEN);

    hydro_hash_init(&st, ctx, NULL);

    while (ebits < 256) {
        while (!(READ_BIT(RNG->SR, RNG_SR_DRDY))) {
        }

        uint32_t r = RNG->DR;
        hydro_hash_update(&st, (const uint32_t*) &r, sizeof r);
        ebits += 32;
    }

    hydro_hash_final(&st, hydro_random_context.state, sizeof hydro_random_context.state);
    hydro_random_context.counter = ~LOAD64_LE(hydro_random_context.state);

    return 0;
}

#else
# error SMT32 implementation missing!
#endif
