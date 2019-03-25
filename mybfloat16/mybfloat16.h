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

#ifndef MYBFLOAT16_H
#define MYBFLOAT16_H

#include <cstddef>
#include <cstdint>

void FloatToBFloat16(const float *src, uint16_t *dst, size_t size);
void BFloat16ToFloat(const uint16_t *src, float *dst, size_t size);
void BFloat16Add(const uint16_t *a, const uint16_t *b, uint16_t *dst,
                 size_t size);

#endif
