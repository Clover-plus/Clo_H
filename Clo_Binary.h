#include "Clo_Math.h"
#ifndef uchar
#define uchar unsigned char
#endif

class Binary {
    private:
        const uchar bit[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
        const uchar fbit[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f}; //fbit = bit ^ 0xFF
        const uint csize = 8;
        uchar *c;
    public:
        uint length;
        Binary(uint Length);
        bool Index(uint sub);
        void Set(uint sub,bool value);
        void Set(uint sub,uchar value);
};

Binary::Binary(uint Length) {
    length = Length;
    c = new uchar[C_Ceil(Length, csize)]; //will crash if Length+7>sizeof(uint)
}
bool Binary::Index(uint sub) {
    return c[sub/csize] & bit[sub%csize];
}
void Binary::Set(uint sub, bool value) {
    if (value) c[sub/csize] |= bit[sub%csize];
    else c[sub/csize] &= fbit[sub%csize];
}
void Binary::Set(uint sub, uchar value) {
    c[sub] = value;
}