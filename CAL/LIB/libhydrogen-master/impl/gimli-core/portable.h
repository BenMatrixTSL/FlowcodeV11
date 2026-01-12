// CRC: 876150128DE39CBB738C8B441E478605FF8619720F3C9ECA02C246EC0B5408284DD7FBE47A08ABF4FA55D2932F1B1F547D585A9035156049CC803DDC48541E529440B604FA73E6547DF2312817327D35A619F78E599797D0529A504E4C1EEE9EAAFBC9F2C9CF6C2E883CC1457C851A6A9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF51F69644C027281B4B05BE375F10B1FA3A7BB85F11D12D4D01935FDC5C855A7F4A96B5023B7C58B97C873518019A22828F87D75592E45FCFBBB46D84E511595CBDEF5AE7EE889F7C06926E58AA8073E305EF239EBD2DAB0AD549D34A0D5AD11F3829DDC5C93C5C95346D829723638AB1ED3E1C9207440ACD6A44501DE8C4E8A8748A9453D8E52754C
// REVISION: 1.0
// GUID: 0748A384-100B-408A-9B7E-8E17EBC41BC3
// DATE: 08\08\2022
// DIR: CAL\LIB\libhydrogen-master\impl\gimli-core\portable.h
static void
gimli_core(uint32_t state[gimli_BLOCKBYTES / 4])
{
    unsigned int round;
    unsigned int column;
    uint32_t     x;
    uint32_t     y;
    uint32_t     z;

    for (round = 24; round > 0; round--) {
        for (column = 0; column < 4; column++) {
            x = ROTL32(state[column], 24);
            y = ROTL32(state[4 + column], 9);
            z = state[8 + column];

            state[8 + column] = x ^ (z << 1) ^ ((y & z) << 2);
            state[4 + column] = y ^ x ^ ((x | z) << 1);
            state[column]     = z ^ y ^ ((x & y) << 3);
        }
        switch (round & 3) {
        case 0:
            x        = state[0];
            state[0] = state[1];
            state[1] = x;
            x        = state[2];
            state[2] = state[3];
            state[3] = x;
            state[0] ^= ((uint32_t) 0x9e377900 | round);
            break;
        case 2:
            x        = state[0];
            state[0] = state[2];
            state[2] = x;
            x        = state[1];
            state[1] = state[3];
            state[3] = x;
        }
    }
}
