#include <immintrin.h>
namespace SRNG {


__m256i AVX2_intr_squares(__m256i ctr, __m256i key);
__m128i SSE2_intr_squares(__m128i ctr, __m128i key);
#if defined(__AVX512F__)
__m512i  AVX512_intr_squares(__m512i ctr, __m512i key);
#endif
}
