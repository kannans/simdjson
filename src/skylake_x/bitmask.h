#ifndef SIMDJSON_SKYLAKE_X_BITMASK_H
#define SIMDJSON_SKYLAKE_X_BITMASK_H

#include "simdjson/portability.h"

#ifdef IS_X86_64

#include "simdjson/common_defs.h"
#include "skylake_x/intrinsics.h"

TARGET_SKYLAKE_X
namespace simdjson::skylake_x {

//
// Perform a "cumulative bitwise xor," flipping bits each time a 1 is encountered.
//
// For example, prefix_xor(00100100) == 00011100
//
really_inline uint64_t prefix_xor(const uint64_t bitmask) {
  // There should be no such thing with a processor supporting avx2
  // but not clmul.
  __m128i all_ones = _mm_set1_epi8('\xFF');
  __m128i result = _mm_clmulepi64_si128(_mm_set_epi64x(0ULL, bitmask), all_ones, 0);
  return _mm_cvtsi128_si64(result);
}

} // namespace simdjson::skylake_x
UNTARGET_REGION

#endif // IS_X86_64
#endif
