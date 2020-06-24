#include <iostream>
#include <time.h>

using namespace std;

// Well Random Number Generator 
// F. Panneton, P. L'Ecuyer and M. Matsumoto, "Improved Long-Period Generators Based on Linear Recurrences Modulo 2", submitted to ACM TOMS.

namespace Well512 {

    unsigned long state[16];
    unsigned int index = 0;

    // seed 값
    void init(unsigned long seed) {
        for (int i = 0; i < 16; ++i) {
            state[i] = seed;
        }
    }
    unsigned long get() {

        // http://www.iro.umontreal.ca/~panneton/WELLRNG.html 참조
        unsigned long a, b, c, d;
        a = state[index];
        c = state[(index + 13) & 15];
        b = a ^ c ^ (a << 16) ^ (c << 15);
        c = state[(index + 9) & 15];
        c ^= (c >> 11);
        a = state[index] = b ^ c;
        d = a ^ ((a << 5) & 0xDA442D20UL);
        index = (index + 15) & 15;
        a = state[index];
        state[index] = a ^ b ^ d ^ (a << 2) ^ (b << 18) ^ (c << 28);
        return state[index];
    }

    int segment(int start, int end) {
        return int(get() % end) + start;
    }
}

void main()
{
    // time.h를 사용한 초기화
    Well512::init((unsigned long)time(NULL));

    // 난수 100개 생성
    for (int i = 1; i < 100; ++i) {
        cout << Well512::segment(0, 10000) << endl; // 0 ~ 10000 범위 난수 생성
    }
}
