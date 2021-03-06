/*
  Code originally from Tensorflow; taken and simplified. Original license:

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at
  http://www.apache.org/licenses/LICENSE-2.0
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
  ==============================================================================*/

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
