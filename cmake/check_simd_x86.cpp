#include <cpuid.h>

#include <array>
#include <iostream>
#include <string>

using uint = unsigned int;
// Make sure we're not in any funky architecture
static_assert(sizeof(uint) == 4, "");

struct CPUIDregs {
    uint eax{};
    uint ebx{};
    uint ecx{};
    uint edx{};
};

constexpr uint BIT_SSE = (1 << 25);     // Capability found in edx (eax=1)
constexpr uint BIT_SSE2 = (1 << 26);    // Capability found in edx (eax=1)
constexpr uint BIT_SSE3 = (1 << 0);     // Capability found in ecx (eax=1)
constexpr uint BIT_SSSE3 = (1 << 9);    // Capability found in ecx (eax=1)
constexpr uint BIT_SSE4_1 = (1 << 19);  // Capability found in ecx (eax=1)
constexpr uint BIT_SSE4_2 = (1 << 20);  // Capability found in ecx (eax=1)
constexpr uint BIT_FMA = (1 << 10);     // Capability found in ecx (eax=1)
constexpr uint BIT_AVX = (1 << 28);     // Capability found in ecx (eax=1)
constexpr uint BIT_AVX2 = (1 << 5);     // Capability found in ebx (eax=7,ecx=0)

constexpr uint RETVAL_BIT_SSE = 0;
constexpr uint RETVAL_BIT_SSE2 = 1;
constexpr uint RETVAL_BIT_SSE3 = 2;
constexpr uint RETVAL_BIT_SSSE3 = 3;
constexpr uint RETVAL_BIT_SSE4_1 = 4;
constexpr uint RETVAL_BIT_SSE4_2 = 5;
constexpr uint RETVAL_BIT_FMA = 6;
constexpr uint RETVAL_BIT_AVX = 7;
constexpr uint RETVAL_BIT_AVX2 = 8;

auto main() -> int {
    CPUIDregs regs;
    int ret_val{0x00000000};

    // Get CPU vendor information ----------------------------------------------
    __get_cpuid(0, &regs.eax, &regs.ebx, &regs.ecx, &regs.edx);
    // Assemble data to get vendor string
    std::array<uint, 3> vendor_regs = {regs.ebx, regs.edx, regs.ecx};
    // NOLINTNEXTLINE
    std::string vendor_str(reinterpret_cast<const char*>(vendor_regs.data()),
                           sizeof(uint) * 3);
    // std::cout << "Vendor information: " << vendor_str << '\n';
    //  -------------------------------------------------------------------------

    // Get CPU capabilities ----------------------------------------------------
    __get_cpuid(1, &regs.eax, &regs.ebx, &regs.ecx, &regs.edx);  // eax=1
    const bool HAS_SSE = (regs.edx & BIT_SSE) != 0;
    const bool HAS_SSE2 = (regs.edx & BIT_SSE2) != 0;
    const bool HAS_SSE3 = (regs.ecx & BIT_SSE3) != 0;
    const bool HAS_SSSE3 = (regs.ecx & BIT_SSSE3) != 0;
    const bool HAS_SSE4_1 = (regs.ecx & BIT_SSE4_1) != 0;
    const bool HAS_SSE4_2 = (regs.ecx & BIT_SSE4_2) != 0;
    const bool HAS_FMA = (regs.ecx & BIT_FMA) != 0;
    const bool HAS_AVX = (regs.ecx & BIT_AVX) != 0;
    __get_cpuid_count(7, 0, &regs.eax, &regs.ebx, &regs.ecx, &regs.edx);
    const bool HAS_AVX2 = (regs.ebx & BIT_AVX2) != 0;
    // -------------------------------------------------------------------------

    // Assemble the return value according to our custom info layout -----------
    ret_val |= (HAS_SSE ? 1 : 0) << RETVAL_BIT_SSE;
    ret_val |= (HAS_SSE2 ? 1 : 0) << RETVAL_BIT_SSE2;
    ret_val |= (HAS_SSE3 ? 1 : 0) << RETVAL_BIT_SSE3;
    ret_val |= (HAS_SSSE3 ? 1 : 0) << RETVAL_BIT_SSSE3;
    ret_val |= (HAS_SSE4_1 ? 1 : 0) << RETVAL_BIT_SSE4_1;
    ret_val |= (HAS_SSE4_2 ? 1 : 0) << RETVAL_BIT_SSE4_2;
    ret_val |= (HAS_FMA ? 1 : 0) << RETVAL_BIT_FMA;
    ret_val |= (HAS_AVX ? 1 : 0) << RETVAL_BIT_AVX;
    ret_val |= (HAS_AVX2 ? 1 : 0) << RETVAL_BIT_AVX2;
    // std::cout << "retval: " << ret_val << '\n';
    //  -------------------------------------------------------------------------
    std::cout << ret_val;
    return 0;
}
