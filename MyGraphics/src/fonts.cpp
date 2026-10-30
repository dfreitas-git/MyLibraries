
#include <fonts.h>


//#################################
// Fonts used by graphicsFunctions
//#################################

const uint8_t missingGlyph[7] PROGMEM = {
  0b000000,
  0b111110,
  0b111110,
  0b111110,
  0b111110,
  0b111110,
  0b111110,
};
const uint8_t GLYPH_A[7] PROGMEM = {
  0b000000,
  0b011100,
  0b100010,
  0b111110,
  0b100010,
  0b100010,
  0b100010,
};
const uint8_t GLYPH_B[7] PROGMEM = {
  0b000000,
  0b111100,
  0b100010,
  0b111100,
  0b100010,
  0b100010,
  0b111100,
};
const uint8_t GLYPH_C[7] PROGMEM = {
  0b000000,
  0b011110,
  0b100000,
  0b100000,
  0b100000,
  0b100000,
  0b011110,
};
const uint8_t GLYPH_D[7] PROGMEM = {
  0b000000,
  0b111100,
  0b100010,
  0b100010,
  0b100010,
  0b100010,
  0b111100,
};
const uint8_t GLYPH_E[7] PROGMEM = {
  0b000000,
  0b111110,
  0b100000,
  0b111000,
  0b100000,
  0b100000,
  0b111110,
};
const uint8_t GLYPH_F[7] PROGMEM = {
  0b000000,
  0b111110,
  0b100000,
  0b111100,
  0b100000,
  0b100000,
  0b100000,
};
const uint8_t GLYPH_G[7] PROGMEM = {
  0b000000,
  0b011110,
  0b100000,
  0b111100,
  0b100010,
  0b100010,
  0b011110,
};
const uint8_t GLYPH_H[7] PROGMEM = {
  0b000000,
  0b100010,
  0b100010,
  0b111110,
  0b100010,
  0b100010,
  0b100010,
};
const uint8_t GLYPH_I[7] PROGMEM = {
  0b000000,
  0b111110,
  0b001000,
  0b001000,
  0b001000,
  0b001000,
  0b111110,
};
const uint8_t GLYPH_J[7] PROGMEM = {
  0b000000,
  0b111110,
  0b001000,
  0b001000,
  0b001000,
  0b101000,
  0b010000,
};
const uint8_t GLYPH_K[7] PROGMEM = {
  0b000000,
  0b100100,
  0b101000,
  0b110000,
  0b101000,
  0b100100,
  0b100010,
};
const uint8_t GLYPH_L[7] PROGMEM = {
  0b000000,
  0b100000,
  0b100000,
  0b100000,
  0b100000,
  0b100000,
  0b111110,
};
const uint8_t GLYPH_M[7] PROGMEM = {
  0b000000,
  0b100010,
  0b110110,
  0b101010,
  0b100010,
  0b100010,
  0b100010,
};
const uint8_t GLYPH_N[7] PROGMEM = {
  0b000000,
  0b100010,
  0b110010,
  0b101010,
  0b100110,
  0b100010,
  0b100010,
};
const uint8_t GLYPH_O[7] PROGMEM = {
  0b000000,
  0b111110,
  0b100010,
  0b100010,
  0b100010,
  0b100010,
  0b111110,
};
const uint8_t GLYPH_P[7] PROGMEM = {
  0b000000,
  0b111100,
  0b100010,
  0b111100,
  0b100000,
  0b100000,
  0b100000,
};
const uint8_t GLYPH_Q[7] PROGMEM = {
  0b000000,
  0b011100,
  0b100010,
  0b100010,
  0b100010,
  0b100010,
  0b011010,
};
const uint8_t GLYPH_R[7] PROGMEM = {
  0b000000,
  0b111100,
  0b100010,
  0b111100,
  0b100100,
  0b100010,
  0b100010,
};
const uint8_t GLYPH_S[7] PROGMEM = {
  0b000000,
  0b011110,
  0b100000,
  0b011100,
  0b000010,
  0b000010,
  0b111100,
};
const uint8_t GLYPH_T[7] PROGMEM = {
  0b000000,
  0b111110,
  0b001000,
  0b001000,
  0b001000,
  0b001000,
  0b001000,
};
const uint8_t GLYPH_U[7] PROGMEM = {
  0b000000,
  0b100010,
  0b100010,
  0b100010,
  0b100010,
  0b100010,
  0b011100,
};
const uint8_t GLYPH_V[7] PROGMEM = {
  0b000000,
  0b100010,
  0b100010,
  0b100010,
  0b100010,
  0b010100,
  0b001000,
};
const uint8_t GLYPH_W[7] PROGMEM = {
  0b000000,
  0b100010,
  0b100010,
  0b100010,
  0b101010,
  0b110110,
  0b100010,
};
const uint8_t GLYPH_X[7] PROGMEM = {
  0b000000,
  0b100010,
  0b010100,
  0b001000,
  0b010100,
  0b010010,
  0b100010,
};
const uint8_t GLYPH_Y[7] PROGMEM = {
  0b000000,
  0b100010,
  0b010100,
  0b001000,
  0b001000,
  0b001000,
  0b001000,
};
const uint8_t GLYPH_Z[7] PROGMEM = {
  0b000000,
  0b111110,
  0b000100,
  0b001000,
  0b010000,
  0b100000,
  0b111110,
};
const uint8_t GLYPH_0[7] PROGMEM = {
  0b000000,
  0b011100,
  0b100010,
  0b100010,
  0b100010,
  0b100010,
  0b011100,
};
const uint8_t GLYPH_1[7] PROGMEM = {
  0b000000,
  0b011000,
  0b101000,
  0b001000,
  0b001000,
  0b001000,
  0b011100,
};
const uint8_t GLYPH_2[7] PROGMEM = {
  0b000000,
  0b011100,
  0b000010,
  0b000100,
  0b001000,
  0b010000,
  0b111100,
};
const uint8_t GLYPH_3[7] PROGMEM = {
  0b000000,
  0b011100,
  0b000010,
  0b001110,
  0b000010,
  0b000010,
  0b011100,
};
const uint8_t GLYPH_4[7] PROGMEM = {
  0b000000,
  0b100010,
  0b100010,
  0b111110,
  0b000010,
  0b000010,
  0b000010,
};
const uint8_t GLYPH_5[7] PROGMEM = {
  0b000000,
  0b111110,
  0b100000,
  0b011100,
  0b000010,
  0b000010,
  0b111100,
};
const uint8_t GLYPH_6[7] PROGMEM = {
  0b000000,
  0b011000,
  0b100000,
  0b111100,
  0b100010,
  0b100010,
  0b011100,
};
const uint8_t GLYPH_7[7] PROGMEM = {
  0b000000,
  0b111110,
  0b000010,
  0b000100,
  0b001000,
  0b010000,
  0b100000,
};
const uint8_t GLYPH_8[7] PROGMEM = {
  0b000000,
  0b111110,
  0b100010,
  0b111110,
  0b100010,
  0b100010,
  0b111110,
};
const uint8_t GLYPH_9[7] PROGMEM = {
  0b000000,
  0b111110,
  0b100010,
  0b111110,
  0b000010,
  0b000010,
  0b000010,
};

// 7x7 packed for all 95 printable ASCII characters.  If we have not populated a given
// character, we use nullptr and getGlyph subs in a not-available symbol (Solid box)
const uint8_t* font6x7[95] = {
    nullptr,       // space
    nullptr,       // !
    nullptr,       // "
    nullptr,       // #
    nullptr,       // $
    nullptr,       // %
    nullptr,       // &
    nullptr,       // '
    nullptr,       // (
    nullptr,       // )
    nullptr,       // *
    nullptr,       // +
    nullptr,       // ,
    nullptr,       // -
    nullptr,       // .
    nullptr,       // /
    GLYPH_0,       // 0
    GLYPH_1,       // 1
    GLYPH_2,       // 2
    GLYPH_3,       // 3
    GLYPH_4,       // 4
    GLYPH_5,       // 5
    GLYPH_6,       // 6
    GLYPH_7,       // 7
    GLYPH_8,       // 8
    GLYPH_9,       // 9
    nullptr,       // :
    nullptr,       // ;
    nullptr,       // <
    nullptr,       // =
    nullptr,       // >
    nullptr,       // ?
    nullptr,       // @
    GLYPH_A,       // A
    GLYPH_B,       // B
    GLYPH_C,       // C
    GLYPH_D,       // D
    GLYPH_E,       // E
    GLYPH_F,       // F
    GLYPH_G,       // G
    GLYPH_H,       // H
    GLYPH_I,       // I
    GLYPH_J,       // J
    GLYPH_K,       // K
    GLYPH_L,       // L
    GLYPH_M,       // M
    GLYPH_N,       // N
    GLYPH_O,       // O
    GLYPH_P,       // P
    GLYPH_Q,       // Q
    GLYPH_R,       // R
    GLYPH_S,       // S
    GLYPH_T,       // T
    GLYPH_U,       // U
    GLYPH_V,       // V
    GLYPH_W,       // W
    GLYPH_X,       // X
    GLYPH_Y,       // Y
    GLYPH_Z,       // Z
    nullptr,       // [
    nullptr,       // \
    nullptr,       // ]
    nullptr,       // ^
    nullptr,       // _
    nullptr,       // `
    nullptr,       // a
    nullptr,       // b
    nullptr,       // c
    nullptr,       // d
    nullptr,       // e
    nullptr,       // f
    nullptr,       // g
    nullptr,       // h
    nullptr,       // i
    nullptr,       // j
    nullptr,       // k
    nullptr,       // l
    nullptr,       // m
    nullptr,       // n
    nullptr,       // o
    nullptr,       // p
    nullptr,       // q
    nullptr,       // r
    nullptr,       // s
    nullptr,       // t
    nullptr,       // u
    nullptr,       // v
    nullptr,       // w
    nullptr,       // x
    nullptr,       // y
    nullptr,       // z
    nullptr,       // {
    nullptr,       // |
    nullptr,       // }
};


// Function to read the glyph table and return a pointer to the specified character
// We pass the ascii index (i.e. for A that would be 65)
// If a character wasn't defined, return a solid-1 bitmap to indicate error
const uint8_t* getGlyph(char c) {
    if(c < 32 || c > 126)
        return missingGlyph;

    const uint8_t* glyph = font6x7[c - 32];

    if(glyph == nullptr)
        return missingGlyph;

    return glyph;
}