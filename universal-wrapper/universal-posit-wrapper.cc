#include "../universal/posit/posit.hpp"
#include <cstdint>

sw::unum::posit<16, 1> Uint16ToPosit(uint16_t in) {
  sw::unum::bitblock<16> bb;
  bb = static_cast<unsigned long long>(in);
  return sw::unum::posit<16, 1>().set(bb);
}

uint16_t PositToUint16(sw::unum::posit<16, 1> in) {
  return static_cast<uint16_t>(in.get().to_ullong());
}

extern "C" float Posit16es1ToFloat(uint16_t in) {
  return Uint16ToPosit(in).operator float();
}

extern "C" uint16_t FloatToPosit16es1(float in) {
  auto posit = sw::unum::posit<16, 1>(in);
  return PositToUint16(posit);
}

extern "C" uint16_t Posit16es1Add(uint16_t a, uint16_t b) {
  return PositToUint16(Uint16ToPosit(a) + Uint16ToPosit(b));
}
