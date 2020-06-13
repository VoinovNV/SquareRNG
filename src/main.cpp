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
void SSE2_Intrinsic_SRNG(benchmark::State& state){
    __m128i ctr=_mm_set_epi64x(2,1),key=_mm_set1_epi64x(state.range());
    __m128i plus=_mm_set_epi64x(2,2);
    for(auto _:state){
        benchmark::DoNotOptimize(SSE2_intr_squares(ctr,key));
        ctr=_mm_add_epi64(ctr,plus);
    }
    state.counters["byte/s"] = benchmark::Counter{double(8), benchmark::Counter::kIsIterationInvariantRate};

}
}
BENCHMARK(Article_SRNG)->Arg(0xf14ad56f254ff2fa);
BENCHMARK(AVX2_Intrinsic_SRNG)->Arg(0xf14ad56f254ff2fa);
BENCHMARK(SSE2_Intrinsic_SRNG)->Arg(0xf14ad56f254ff2fa);
