#include "../mybfloat16/mybfloat16.h"

extern "C" uint16_t FloatToBFloat16_wrapper(float in) {
  uint16_t out;
  FloatToBFloat16(&in, &out, 1);
  return out;
}

extern "C" float BFloat16ToFloat_wrapper(uint16_t in) {
  float out;
  BFloat16ToFloat(&in, &out, 1);
  return out;
}

extern "C" uint16_t BFloat16Add_wrapper(uint16_t a, uint16_t b) {
  uint16_t out;
  BFloat16Add(&a, &b, &out, 1);
  return out;
}
