#include <array>
#include <iostream>
#include <intrin.h>

using std::array;
using std::cout;
using std::endl;

int main() {
  bool avx = false, avx2 = false, avx512 = false;
  uint32_t max_cpuid;
  
  array<uint32_t, 4> regs;
  
  // CPUID 0: get max CPUID
  __cpuid(reinterpret_cast<int*>(&regs[0]), 1);
  max_cpuid = regs[0];
  
  // CPUID 1: feature flags, AVX: ECX[28]
  if (max_cpuid >= 1) {
    __cpuid(reinterpret_cast<int*>(&regs[0]), 1);
    avx = regs[2] & (1 << 28);
  }
  
  // CPUID (7, 0): more feature flags, AVX2: EBX[5], AVX-512F: EBX[16]
  // AVX512F is supported by all AVX512 processors.
  if (max_cpuid >= 7) {
    __cpuidex(reinterpret_cast<int*>(&regs[0]), 7, 0);
    avx2 = regs[1] & (1 << 5);
    avx512 = regs[1] & (1 << 16);
  }
  
  // Output
  if (avx512) {
    cout << "/arch:AVX512" << endl;
  }
  else if (avx2) {
    cout << "/arch:AVX2" << endl;
  }
  else if (avx) {
    cout << "/arch:AVX" << endl;
  }
}