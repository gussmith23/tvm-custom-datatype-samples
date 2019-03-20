#include "mybfloat16.h"

void FloatToBFloat16(const float* src, uint16_t* dst, size_t size) {
  const uint16_t* p = reinterpret_cast<const uint16_t*>(src);
  uint16_t* q = reinterpret_cast<uint16_t*>(dst);
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
  for (; size != 0; p += 2, q++, size--) {
    *q = p[0];
  }
#else
  for (; size != 0; p += 2, q++, size--) {
    *q = p[1];
  }
#endif
}

void BFloat16ToFloat(const uint16_t* src, float* dst, size_t size) {
  const uint16_t* p = reinterpret_cast<const uint16_t*>(src);
  uint16_t* q = reinterpret_cast<uint16_t*>(dst);
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
  for (; size != 0; p++, q += 2, size--) {
    q[0] = *p;
    q[1] = 0;
  }
#else
  for (; size != 0; p++, q += 2, size--) {
    q[0] = 0;
    q[1] = *p;
  }
#endif
}

void BFloat16Add(const uint16_t* a, const uint16_t* b, uint16_t* dst, size_t size) {
  float a_f, b_f;
  BFloat16ToFloat(a, &a_f, 1);
  BFloat16ToFloat(b, &b_f, 1);
  float out_f = a_f + b_f;
  FloatToBFloat16(&out_f, dst, 1);
}
