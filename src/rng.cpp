#include "rng.hpp"
#include <iostream>
namespace SRNG{
uint64_t squares(uint64_t ctr, uint64_t key) {
    uint64_t x, y, z;
    y = x = ctr * key; z = y + key;
    x = x*x + y;
    x = ((x>>32) | (x<<32)); /* round 1 */
    x = x*x + z; x = ((x>>32) | (x<<32)); /* round 2 */
    return (x*x + y) >> 32; /* round 3 */
}
}
