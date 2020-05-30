#include "intr_rng.hpp"
namespace SRNG{
__m256i intr_mul_64(__m256i x, __m256i y){
    /* A=a*2(n/2)+b || B=c*2(n/2)+d
     * AB=ac*2^n+(ad+bc)*2^(n/2)+bd
     * � ������ SRNG ��������� �� ������ 2^64, ������� ����� ��������� ������:
     * AB mod 2^n = (ad+bc)*2^(n/2)+ bd
     *
    */
    /* _mm256_add_epi64(32) - �������� �� 64(32) ������ ������
     * _mm256_mul_epi(epu)32 - ��������� ������� 32 ����� 64-�. �����
     *  � ��������� - 64 ������ �����
     * _mm256_sll_epi64 ����� 32-������ �����
     * _mm256_srl_epi64 - ������
     * */
    __m256i t={},t_={},t__={};

    t=_mm256_mul_epu32(x,y);

    t_=_mm256_mul_epu32(_mm256_srli_epi64(x,32),y);
    t__=_mm256_mul_epu32(_mm256_srli_epi64(y,32),x);
    t_=_mm256_slli_epi64(_mm256_add_epi64(t_,t__),32);
    return _mm256_add_epi64(t,t_);
}
__m256i intr_squares(__m256i ctr, __m256i key) {
    /*uint64_t x, y, z;
    y = x = ctr * key;
    z = y + key;
    x = x*x + y;
    x = (x>>32) | (x<<32);
    x = x*x + z;
    x = (x>>32) | (x<<32);
    return (x*x + y) >> 32; */
    __m256i x,y,z;
    x=y=intr_mul_64(ctr,key);
    z=_mm256_add_epi64(y,key);
    x=intr_mul_64(x,x);
    x=_mm256_add_epi64(y,x);
    // >>|<<
    x=_mm256_or_si256(_mm256_srli_epi64(x,32),_mm256_slli_epi64(x,32));

    x=intr_mul_64(x,x);
    x=_mm256_add_epi64(z,x);
    // >>|<<
    x=_mm256_or_si256(_mm256_srli_epi64(x,32),_mm256_slli_epi64(x,32));
    //
    x=intr_mul_64(x,x);
    x=_mm256_add_epi64(y,x);

    return _mm256_srli_epi64(x,32);
}

}
