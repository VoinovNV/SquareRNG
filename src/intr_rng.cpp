#include "intr_rng.hpp"
namespace SRNG{
__m256i intr_mul_64(__m256i x, __m256i y){

    __m256i t={},t_={},t__={};

    t=_mm256_mul_epu32(x,y);

    t_=_mm256_mul_epu32(_mm256_srli_epi64(x,32),y);
    t__=_mm256_mul_epu32(_mm256_srli_epi64(y,32),x);
    t_=_mm256_slli_epi64(_mm256_add_epi64(t_,t__),32);
    return _mm256_add_epi64(t,t_);
}
__m256i intr_squares(__m256i ctr, __m256i key) {
    __m256i x,y,z;
    x=y=intr_mul_64(ctr,key);
    z=_mm256_add_epi64(y,key);
    x=intr_mul_64(x,x);
    x=_mm256_add_epi64(y,x);
    x=_mm256_shuffle_epi32(x,0b10110001);
    x=intr_mul_64(x,x);
    x=_mm256_add_epi64(z,x);
    x=_mm256_shuffle_epi32(x,0b10110001);
    x=intr_mul_64(x,x);
    x=_mm256_add_epi64(y,x);

    return _mm256_srli_epi64(x,32);
}

}
