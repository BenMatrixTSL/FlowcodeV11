// CRC: 876150128DE39CBB738C8B441E478605FF8619720F3C9ECA02C246EC0B5408284DD7FBE47A08ABF4FA55D2932F1B1F547D585A9035156049CC803DDC48541E52E9C872C0FA0BC7C9E90DE3E3F27793041A8303C6D45B0FEF1A95D834757D4C57622E4A10154D10ED53988D8E819F1E2C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF58835C3F94A844D2E43D738624D13918DF79E6CD48747F2F7320F6EB50EDA5F38442FBDC56A4109C958576AF557C7D3F90CAE1357315771D84066CF2A5EC170D8A7C97BA3993E0E359AA82A5533C277924581113083D8814E549D34A0D5AD11F3552954F98B5B02CD54F2DDAB7534DAC39EFD3477671C705FE00AF8598B7CA62D1079227E43D7E189
// REVISION: 1.0
// GUID: 79DC1D41-E415-424D-B81B-4D5C89B5683F
// DATE: 08\08\2022
// DIR: CAL\LIB\libhydrogen-master\impl\random\nrf52832.h
// Important: The SoftDevice *must* be activated to enable reading from the RNG
// http://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.nrf52832.ps.v1.1%2Frng.html

#include <nrf_soc.h>

static int
hydro_random_init(void)
{
    const char       ctx[hydro_hash_CONTEXTBYTES] = { 'h', 'y', 'd', 'r', 'o', 'P', 'R', 'G' };
    hydro_hash_state st;
    const uint8_t    total_bytes     = 32;
    uint8_t          remaining_bytes = total_bytes;
    uint8_t          available_bytes;
    uint8_t          rand_buffer[32];

    hydro_hash_init(&st, ctx, NULL);

    for (;;) {
        if (sd_rand_application_bytes_available_get(&available_bytes) != NRF_SUCCESS) {
            return -1;
        }
        if (available_bytes > 0) {
            if (available_bytes > remaining_bytes) {
                available_bytes = remaining_bytes;
            }
            if (sd_rand_application_vector_get(rand_buffer, available_bytes) != NRF_SUCCESS) {
                return -1;
            }
            hydro_hash_update(&st, rand_buffer, total_bytes);
            remaining_bytes -= available_bytes;
        }
        if (remaining_bytes <= 0) {
            break;
        }
        delay(10);
    }
    hydro_hash_final(&st, hydro_random_context.state, sizeof hydro_random_context.state);
    hydro_random_context.counter = ~LOAD64_LE(hydro_random_context.state);

    return 0;
}
