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
        for(int i=0;i<4;i++) benchmark::DoNotOptimize(squares(ctr++,key));


}
void Intrinsic_SRNG(benchmark::State& state)
{
    __m256i ctr={4,3,2,1},key=_mm256_set1_epi64x(state.range());
    __m256i plus={4,4,4,4};
    for(auto _:state){
        benchmark::DoNotOptimize(intr_squares(ctr,key));
        ctr=_mm256_add_epi64(ctr,plus);
    }

}
}
BENCHMARK(Article_SRNG)->Arg(0xf14ad56f254ff2fa);
BENCHMARK(Intrinsic_SRNG)->Arg(0xf14ad56f254ff2fa);
