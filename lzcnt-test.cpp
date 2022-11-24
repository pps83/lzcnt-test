#include <stdio.h>
#include <intrin.h>

static int clz_bmi(unsigned x)
{
    return (int)__lzcnt(x);
}

static int clz_bsr(unsigned x)
{
    if (!x)
        return 32;
    unsigned long ret;
    _BitScanReverse(&ret, x);
    return (int)(31 ^ ret);
}

static bool has_bmi()
{
    int info[4] = {};
    __cpuidex(info, 7, 0);
    int ebx = info[1];
    return !!(ebx & (1 << 3));
}

int clz(unsigned x)
{
    const static bool bmi = has_bmi();
    return bmi ? clz_bmi(x) : clz_bsr(x);
}

int main()
{
    printf("clz 1 => %u\n", clz(1));
    printf("clz 0 => %u\n", clz(0));
}
