/*
** crc.c - calculate CRC
**
** See Copyright Notice in mruby.h
*/

#include <limits.h>
#include <stdint.h>
#include <stddef.h>

#if defined(MRB_CRC_SMALL)
/* Calculate CRC (CRC-16-CCITT)
**
**  0000_0000_0000_0000_0000_0000_0000_0000
**          ^|------- CRC -------|- work --|
**        carry
*/
#define  CRC_16_CCITT       0x11021ul        /* x^16+x^12+x^5+1 */
#define  CRC_XOR_PATTERN    (CRC_16_CCITT << 8)
#define  CRC_CARRY_BIT      (0x01000000)

uint16_t
calc_crc_16_ccitt(const uint8_t *src, size_t nbytes, uint16_t crc)
{
  size_t ibyte;
  uint32_t ibit;
  uint32_t crcwk = crc << 8;

  for (ibyte = 0; ibyte < nbytes; ibyte++) {
    crcwk |= *src++;
    for (ibit = 0; ibit < CHAR_BIT; ibit++) {
      crcwk <<= 1;
      if (crcwk & CRC_CARRY_BIT) {
        crcwk ^= CRC_XOR_PATTERN;
      }
    }
  }
  return (uint16_t)(crcwk >> 8);
}
#else
/* Calculate CRC (CRC-16-CCITT)
**
** This is a combining algorithm the "Half-byte table" and "Slicing by 4/8".
** It implementation is calculated by double 4 bit per iterations.
**
** Table size is 64 bytes (2 rounds and 16 elements of 2 bytes).
**
**             crc state (16 bits)                 next octet
**  +---------+---------+-----------------+   +-----------------+
**  | 1 1 1 1 | 1 1     |                 |   |                 |
**  | 5 4 3 2 | 1 0 9 8 | 7 6 5 4 3 2 1 0 |   | 7 6 5 4 3 2 1 0 |
**  +---------+---------+-----------------+   +-----------------+
**       |         |             |                     |
**       v         v             v                     v
**       |         |        [bit shift]                |
**       |         |             |                     |
**       |         |             `------>  [or] <------'
**       |         |                        v
**       |         `----> [table1] -----> [xor]
**       |                                  v
**       `--------------> [table2] -----> [xor]
**                                          |
**                                          v
**                           +-------------------------------+
**                           |    new crc state (16 bits)    |
**                           +-------------------------------+
*/

# include <mruby/crctable.h>

uint16_t
calc_crc_16_ccitt(const uint8_t *src, size_t nbytes, uint16_t crc)
{
# ifdef MRB_CRC_FAST
  for (; nbytes >= 4; nbytes -= 4) {
    uint8_t a = src[0];
    uint8_t b = src[1];
    uint8_t c = src[2];
    uint8_t d = src[3];
    crc = crctable[7][(uint8_t)(crc >> 12) & 0x0f] ^
          crctable[6][(uint8_t)(crc >>  8) & 0x0f] ^
          crctable[5][(uint8_t)(crc >>  4) & 0x0f] ^
          crctable[4][(uint8_t)(crc >>  0) & 0x0f] ^
          crctable[3][         (a   >>  4) & 0x0f] ^
          crctable[2][         (a   >>  0) & 0x0f] ^
          crctable[1][         (b   >>  4) & 0x0f] ^
          crctable[0][         (b   >>  0) & 0x0f] ^
          ((c << 8) | d);
    src += 4;
  }
# endif /* MRB_CRC_FAST */

  for (; nbytes > 0; nbytes --) {
    crc = crctable[1][(uint8_t)(crc >> 12) & 0x0f] ^
          crctable[0][(uint8_t)(crc >>  8) & 0x0f] ^
          ((crc << 8) | *src ++);
  }

  return crc;
}
#endif /* MRB_CRC_SMALL */
