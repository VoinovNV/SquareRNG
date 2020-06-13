#include <benchmark/benchmark.h>
#include <immintrin.h>
#include <iostream>
#include "intr_rng.hpp"
#include "rng.hpp"
namespace  {
using namespace SRNG;

void Article_SRNG(benchmark::State& state)
{
    uint64_t ctr=1,key=state.range();
    for(auto _:state)
        benchmark::DoNotOptimize(squares(ctr++,key));

    state.counters["byte/s"] = benchmark::Counter{double(4), benchmark::Counter::kIsIterationInvariantRate};


}
#if defined(__AVX2__)
void AVX2_Intrinsic_SRNG(benchmark::State& state)
{
    __m256i ctr={4,3,2,1},key=_mm256_set1_epi64x(state.range());
    __m256i plus={4,4,4,4};
    for(auto _:state){
        benchmark::DoNotOptimize(AVX2_intr_squares(ctr,key));
        ctr=_mm256_add_epi64(ctr,plus);
    }
    state.counters["byte/s"] = benchmark::Counter{double(16), benchmark::Counter::kIsIterationInvariantRate};

}
#endif
#if defined(__SSE2__)
void SSE2_Intrinsic_SRNG(benchmark::State& state){
    __m128i ctr=_mm_set_epi64x(2,1),key=_mm_set1_epi64x(state.range());
    __m128i plus=_mm_set_epi64x(2,2);
    for(auto _:state){
        benchmark::DoNotOptimize(SSE2_intr_squares(ctr,key));
        ctr=_mm_add_epi64(ctr,plus);
    }
    state.counters["byte/s"] = benchmark::Counter{double(8), benchmark::Counter::kIsIterationInvariantRate};

}
#endif
}
void AVX512_Intrinsic_SRNG(benchmark::State& state){
    __m512i ctr=_mm512_set_epi64(8,7,6,5,4,3,2,1),key=_mm512_set1_epi64(state.range());
    __m512i plus=_mm512_set1_epi64(8);
    for(auto _:state){
        benchmark::DoNotOptimize(AVX512_intr_squares(ctr,key));
        ctr=_mm512_add_epi64(ctr,plus);
    }
    state.counters["byte/s"] = benchmark::Counter{double(32), benchmark::Counter::kIsIterationInvariantRate};

}
BENCHMARK(Article_SRNG)->Arg(0xf14ad56f254ff2fa);
#if defined(__SSE2__)
BENCHMARK(SSE2_Intrinsic_SRNG)->Arg(0xf14ad56f254ff2fa);
#endif
#if defined(__AVX2__)
BENCHMARK(AVX2_Intrinsic_SRNG)->Arg(0xf14ad56f254ff2fa);
#endif
#if defined(__AVX512F__)
BENCHMARK(AVX512_Intrinsic_SRNG)->Arg(0xf14ad56f254ff2fa);
#endif
