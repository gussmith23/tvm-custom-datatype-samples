#ifndef MYBFLOAT16_H
#define MYBFLOAT16_H

#include <cstdint>
#include <cstddef>

void FloatToBFloat16(const float* src, uint16_t* dst, size_t size);
void BFloat16ToFloat(const uint16_t* src, float* dst, size_t size);
void BFloat16Add(const uint16_t* a, const uint16_t* b, uint16_t* dst, size_t size);

#endif
