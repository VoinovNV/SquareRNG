#include <immintrin.h>
namespace SRNG {


__m256i AVX2_intr_squares(__m256i ctr, __m256i key);
__m128 SSE2_intr_squares(__m128i ctr, __m128i key);
}
