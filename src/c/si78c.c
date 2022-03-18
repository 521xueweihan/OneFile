//
// Space Invaders 1978 in C
// Jason McSweeney

#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ucontext.h>
#include <stdint.h>
#include <assert.h>
#include <SDL.h>
#include <assert.h>
#include <string.h>

#define  OP_BLEND         0
#define  OP_ERASE         1
#define  OP_COLLIDE       2
#define  OP_BLIT          3

#define  SHOT_ACTIVE      0x80
#define  SHOT_BLOWUP      0x1

#define  BEAM_VBLANK      0x80
#define  BEAM_MIDDLE      0x00
#define  XR_MID           0x80

#define  DIP3_SHIPS1      0x1
#define  DIP5_SHIPS2      0x2
#define  DIP6_BONUS       0x8
#define  DIP7_COININFO    0x80

#define  TILT_BIT         0x4
#define  COIN_BIT         0x1

#define  INIT             1
#define  PROMPT           2
#define  SHIELDS          4

#define  ROL_SHOT_PICEND  0xf9
#define  PLU_SHOT_PICEND  0xed
#define  SQU_SHOT_PICEND  0xdb

#define  PLAYER_ADDR            0x2010
#define  PLAYER_SIZE            16
#define  PLAYER_SHOT_ADDR       0x2020
#define  PLAYER_SHOT_DATA_ADDR  0x2025
#define  PLAYER_SHOT_DATA_SIZE  7
#define  ROLLING_SHOT_ADDR      0x2030
#define  ROLLING_SHOT_SIZE      16
#define  PLUNGER_SHOT_ADDR      0x2040
#define  PLUNGER_SHOT_SIZE      16
#define  SQUIGGLY_SHOT_ADDR     0x2050
#define  SQUIGGLY_SHOT_SIZE     16
#define  SAUCER_ADDR            0x2083
#define  SAUCER_SIZE            10
#define  P1_ADDR                0x2100
#define  P2_ADDR                0x2200
#define  SPLASH_DESC_ADDR       0x20c5

#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
#error "This code is Little Endian only."
#endif

struct Word
{
    union {

        uint16_t u16;
        struct {
            uint8_t l;
            uint8_t h;
        };

        struct {
            uint8_t y;
            uint8_t x;
        };

    };
} __attribute__ ((packed)); // 4

typedef struct Word Word;

struct SprDesc
{
    Word spr;

    union {
        Word pos;    // pixel position
        Word sc;     // screen address
    };

    uint8_t  n;

} __attribute__ ((packed)); // 5

typedef struct SprDesc SprDesc;

struct GameObjHeader
{
    uint8_t TimerMSB;
    uint8_t TimerLSB;
    uint8_t TimerExtra;
    Word Handler;

} __attribute__ ((packed)); // 5

typedef struct GameObjHeader GameObjHeader;

struct AShot
{
    uint8_t      Status;
    uint8_t      StepCnt;
    uint8_t      Track;
    Word         CFir;
    uint8_t      BlowCnt;
    SprDesc      Desc;

} __attribute__ ((packed)); // 11

typedef struct AShot AShot;

struct Mem {

uint8_t        pad_01[3063];                          //  0x0000
uint8_t        MSG_TAITO_COP[9];                      //  0x0bf7
uint8_t        pad_02[3601];                          //  0x0c00
uint8_t        soundDelayKey[16];                     //  0x1a11
uint8_t        soundDelayValue[16];                   //  0x1a21
uint8_t        pad_03[112];                           //  0x1a31
uint8_t        ShotReloadRate[5];                     //  0x1aa1
uint8_t        MSG_GAME_OVER__PLAYER___[20];          //  0x1aa6
uint8_t        MSG_1_OR_2PLAYERS_BUTTON[20];          //  0x1aba
uint8_t        pad_04;                                //  0x1ace
uint8_t        MSG_ONLY_1PLAYER__BUTTON[20];          //  0x1acf
uint8_t        pad_05;                                //  0x1ae3
uint8_t        MSG__SCORE_1__HI_SCORE_SCORE_2__[28];  //  0x1ae4
uint8_t        pad_06[112];                           //  0x1b00
uint8_t        MSG_PLAY_PLAYER_1_[14];                //  0x1b70
uint8_t        pad_07[66];                            //  0x1b7e
uint8_t        SPLASH_SHOT_OBJDATA[16];               //  0x1bc0
uint8_t        pad_08[144];                           //  0x1bd0
uint8_t        PLAYER_SPRITES[48];                    //  0x1c60
uint8_t        pad_09[9];                             //  0x1c90
uint8_t        MSG__10_POINTS[10];                    //  0x1c99
uint8_t        MSG__SCORE_ADVANCE_TABLE_[21];         //  0x1ca3
uint8_t        AReloadScoreTab[4];                    //  0x1cb8
uint8_t        MSG_TILT[4];                           //  0x1cbc
uint8_t        pad_10[28];                            //  0x1cc0
uint8_t        AlienShotExplodingSprite[6];           //  0x1cdc
uint8_t        pad_11[24];                            //  0x1ce2
uint8_t        MSG_PLAY2[5];                          //  0x1cfa
uint8_t        pad_12[33];                            //  0x1cff
uint8_t        SHIELD_SPRITE[44];                     //  0x1d20
uint8_t        SauScrValueTab[4];                     //  0x1d4c
uint8_t        SauScrStrTab[4];                       //  0x1d50
uint8_t        pad_13[40];                            //  0x1d54
uint8_t        SpriteSaucerExp[24];                   //  0x1d7c
uint8_t        MSG__50[3];                            //  0x1d94
uint8_t        MSG_100[3];                            //  0x1d97
uint8_t        MSG_150[3];                            //  0x1d9a
uint8_t        MSG_300[3];                            //  0x1d9d
uint8_t        AlienScores[3];                        //  0x1da0
uint8_t        AlienStartTable[8];                    //  0x1da3
uint8_t        MSG_PLAY[4];                           //  0x1dab
uint8_t        MSG_SPACE__INVADERS[15];               //  0x1daf
uint8_t        SCORE_ADV_SPRITE_LIST[17];             //  0x1dbe
uint8_t        SCORE_ADV_MSG_LIST[17];                //  0x1dcf
uint8_t        MSG____MYSTERY[10];                    //  0x1de0
uint8_t        MSG__30_POINTS[10];                    //  0x1dea
uint8_t        MSG__20_POINTS[10];                    //  0x1df4
uint8_t        pad_14[338];                           //  0x1dfe
uint8_t        MSG__1_OR_2_PLAYERS___[18];            //  0x1f50
uint8_t        pad_15[46];                            //  0x1f62
uint8_t        MSG_INSERT__COIN[12];                  //  0x1f90
uint8_t        CREDIT_TABLE[4];                       //  0x1f9c
uint8_t        CREDIT_TABLE_COINS[9];                 //  0x1fa0
uint8_t        MSG_CREDIT_[7];                        //  0x1fa9
uint8_t        pad_16[67];                            //  0x1fb0
uint8_t        MSG_PUSH[4];                           //  0x1ff3
uint8_t        pad_17[9];                             //  0x1ff7

// start of ram mirror

uint8_t        waitOnDraw;                            //  0x2000
uint8_t        pad_18;                                //  0x2001
uint8_t        alienIsExploding;                      //  0x2002
uint8_t        expAlienTimer;                         //  0x2003
uint8_t        alienRow;                              //  0x2004
uint8_t        alienFrame;                            //  0x2005
uint8_t        alienCurIndex;                         //  0x2006
Word           refAlienDelta;                         //  0x2007
Word           refAlienPos;                           //  0x2009
Word           alienPos;                              //  0x200b
uint8_t        rackDirection;                         //  0x200d
uint8_t        rackDownDelta;                         //  0x200e
uint8_t        pad_19;                                //  0x200f
GameObjHeader  playerHeader;                          //  0x2010
uint8_t        playerAlive;                           //  0x2015
uint8_t        expAnimateTimer;                       //  0x2016
uint8_t        expAnimateCnt;                         //  0x2017
SprDesc        playerDesc;                            //  0x2018
uint8_t        nextDemoCmd;                           //  0x201d
uint8_t        hidMessSeq;                            //  0x201e
uint8_t        pad_20;                                //  0x201f
GameObjHeader  plyrShotHeader;                        //  0x2020
uint8_t        plyrShotStatus;                        //  0x2025
uint8_t        blowUpTimer;                           //  0x2026
SprDesc        playerShotDesc;                        //  0x2027
uint8_t        shotDeltaYr;                           //  0x202c
uint8_t        fireBounce;                            //  0x202d
uint8_t        pad_21[2];                             //  0x202e
GameObjHeader  rolShotHeader;                         //  0x2030
AShot          rolShotData;                           //  0x2035
GameObjHeader  pluShotHeader;                         //  0x2040
AShot          pluShotData;                           //  0x2045
GameObjHeader  squShotHeader;                         //  0x2050
AShot          squShotData;                           //  0x2055
uint8_t        pad_22;                                //  0x2060
uint8_t        collision;                             //  0x2061
SprDesc        expAlien;                              //  0x2062
uint8_t        playerDataMSB;                         //  0x2067
uint8_t        playerOK;                              //  0x2068
uint8_t        enableAlienFire;                       //  0x2069
uint8_t        alienFireDelay;                        //  0x206a
uint8_t        pad_23;                                //  0x206b
uint8_t        temp206C;                              //  0x206c
uint8_t        invaded;                               //  0x206d
uint8_t        skipPlunger;                           //  0x206e
uint8_t        pad_24;                                //  0x206f
uint8_t        otherShot1;                            //  0x2070
uint8_t        otherShot2;                            //  0x2071
uint8_t        vblankStatus;                          //  0x2072
AShot          aShot;                                 //  0x2073
uint8_t        alienShotDelta;                        //  0x207e
uint8_t        shotPicEnd;                            //  0x207f
uint8_t        shotSync;                              //  0x2080
uint8_t        tmp2081;                               //  0x2081
uint8_t        numAliens;                             //  0x2082
uint8_t        saucerStart;                           //  0x2083
uint8_t        saucerActive;                          //  0x2084
uint8_t        saucerHit;                             //  0x2085
uint8_t        saucerHitTime;                         //  0x2086
SprDesc        saucerDesc;                            //  0x2087
uint8_t        saucerDXr;                             //  0x208c
Word           sauScore;                              //  0x208d
Word           shotCount;                             //  0x208f
Word           saucerTimer;                           //  0x2091
uint8_t        waitStartLoop;                         //  0x2093
uint8_t        soundPort3;                            //  0x2094
uint8_t        changeFleetSnd;                        //  0x2095
uint8_t        fleetSndCnt;                           //  0x2096
uint8_t        fleetSndReload;                        //  0x2097
uint8_t        soundPort5;                            //  0x2098
uint8_t        extraHold;                             //  0x2099
uint8_t        tilt;                                  //  0x209a
uint8_t        fleetSndHold;                          //  0x209b
uint8_t        pad_25[36];                            //  0x209c

// end of partial ram restore at 0x20c0

uint8_t        isrDelay;                              //  0x20c0
uint8_t        isrSplashTask;                         //  0x20c1
uint8_t        splashAnForm;                          //  0x20c2
Word           splashDelta;                           //  0x20c3
Word           splashPos;                             //  0x20c5
Word           splashPic;                             //  0x20c7
uint8_t        splashPicSize;                         //  0x20c9
uint8_t        splashTargetX;                         //  0x20ca
uint8_t        splashReached;                         //  0x20cb
Word           splashImRest;                          //  0x20cc
uint8_t        twoPlayers;                            //  0x20ce
uint8_t        aShotReloadRate;                       //  0x20cf
uint8_t        pad_26[21];                            //  0x20d0
Word           playerExtras;                          //  0x20e5
Word           playerStates;                          //  0x20e7
uint8_t        gameTasksRunning;                      //  0x20e9
uint8_t        coinSwitch;                            //  0x20ea
uint8_t        numCoins;                              //  0x20eb
uint8_t        splashAnimate;                         //  0x20ec
Word           demoCmdPtr;                            //  0x20ed
uint8_t        gameMode;                              //  0x20ef
uint8_t        pad_27;                                //  0x20f0
uint8_t        adjustScore;                           //  0x20f1
Word           scoreDelta;                            //  0x20f2
Word           HiScor;                                //  0x20f4
uint8_t        pad_28[2];                             //  0x20f6
Word           P1Scor;                                //  0x20f8
uint8_t        pad_29[2];                             //  0x20fa
Word           P2Scor;                                //  0x20fc
uint8_t        pad_30[68];                            //  0x20fe

// end of ram mirror at 0x2100

uint8_t        p1ShieldBuffer[176];                   //  0x2142
uint8_t        pad_31[9];                             //  0x21f2
uint8_t        p1RefAlienDX;                          //  0x21fb
Word           p1RefAlienPos;                         //  0x21fc
uint8_t        p1RackCnt;                             //  0x21fe
uint8_t        p1ShipsRem;                            //  0x21ff
uint8_t        pad_32[66];                            //  0x2200
uint8_t        p2ShieldBuffer[176];                   //  0x2242
uint8_t        pad_33[9];                             //  0x22f2
uint8_t        p2RefAlienDX;                          //  0x22fb
Word           p2RefAlienPos;                         //  0x22fc
uint8_t        p2RackCnt;                             //  0x22fe
uint8_t        p2ShipsRem;                            //  0x22ff
uint8_t        pad_34[256];                           //  0x2300
uint8_t        vram[7168];                            //  0x2400

// Technically the region below is supposed to be a mirror, but AFAICT,
// that property is not used by the SI code.
//
// The 'PLAy' animation does do some oob writes during DrawSprite,
// which effectively do nothing because they end up trying to write to ROM
//
// So, as a catchall, we just reserve this area up to the end of the address space.

uint8_t        oob[49152];                            //  0x4000

} __attribute  ((packed));

typedef struct Mem Mem;

typedef struct PriCursor
{
    uint8_t* src;
    Word sc;
    uint8_t* obj;
} PriCursor;

typedef struct ShieldBufferCursor
{
    Word sc;
    uint8_t* iter;
} ShieldBufferCursor;

typedef enum YieldReason
{
    YIELD_INIT = 0,
    YIELD_TIMESLICE,
    YIELD_INTFIN,
    YIELD_WAIT_FOR_START,
    YIELD_PLAYER_DEATH,
    YIELD_INVADED,
    YIELD_TILT,
    YIELD_UNKNOWN,
} YieldReason;

enum Keys {
    KEYS_LEFT      =  1,
    KEYS_RIGHT     =  2,
    KEYS_START     =  4,
    KEYS_START2    =  8,
    KEYS_FIRE      =  16,
    KEYS_COIN      =  32,
    KEYS_TILT      =  64,
    KEYS_DIP6      =  128,
    KEYS_DIP7      =  256,
    KEYS_SPECIAL1  =  512,
    KEYS_SPECIAL2  =  1024,
    KEYS_QUIT      =  2048
};

#define KEY_LIST \
    KEY_MAP('a', KEYS_LEFT); \
    KEY_MAP('d', KEYS_RIGHT); \
    KEY_MAP('1', KEYS_START); \
    KEY_MAP('2', KEYS_START2); \
    KEY_MAP('j', KEYS_FIRE); \
    KEY_MAP('5', KEYS_COIN); \
    KEY_MAP('t', KEYS_TILT); \
    KEY_MAP('6', KEYS_DIP6); \
    KEY_MAP('7', KEYS_DIP7); \
    KEY_MAP('z', KEYS_SPECIAL1); \
    KEY_MAP('x', KEYS_SPECIAL2); \
    KEY_MAP(SDLK_ESCAPE, KEYS_QUIT);

#define TRUE 1
#define FALSE 0

static void do_logprintf(const char *file, unsigned line, const char* format, ...);
#define logprintf(...) { do_logprintf(__FILE__, __LINE__, __VA_ARGS__); }

#include "si78c_proto.h"

// Coordinate Systems
// ------------------
//
// Natural Units
// -------------
//
// For readability, this codebase uses the following coordinate system
// where possible.
//
// The origin is at the bottom left corner.
//
// X goes +ve towards the rhs of the screen.
// Y goes +ve towards the top of the screen.
//
//  (0,256)
//    ^
//    |
//  y |
//    |
//    |----------> (224,0)
//  (0,0)  x
//
// Game Units
// -------------
//
// The game uses two different coordinate systems, both of which
// fit into a 16-bit word, and come with an offset.
//
// pix  - Pixel positions between 0x2000 and 0xffff
// sc   - Screen RAM addresses between 0x2400 and 0x3fff
//
// pix coordinates are used to move and draw objects that require per pixel shifting,
// like the aliens and the bullets.
//
// sc coordinates are used for drawing text and other simple sprites, and also when
// blitting sprites after they have been shifted.
//
// The following macros are used to convert between natural units and game units.

#define xysc(x, y)     ((x)*32 + (y)/8)
#define xytosc(x, y)   u16_to_word(0x2400 + xysc((x),(y)))
#define xpix(x)        ((x)+32)
#define xytopix(x, y)  u16_to_word((xpix((x)) << 8) | (y))

#define STACK_SIZE 65536

#define CRED1 17152
#define CRED2 16384

static Mem m;
static uint8_t *rawmem = (uint8_t*) &m;

static int64_t ticks;
static int im;
static int irq_state;
static int irq_vector;

static uint16_t shift_data;
static uint8_t shift_count;

static ucontext_t frontend_ctx;
static ucontext_t main_ctx;
static ucontext_t int_ctx;

static ucontext_t *prev_ctx;
static ucontext_t *curr_ctx;

static uint8_t main_ctx_stack[STACK_SIZE];
static uint8_t int_ctx_stack[STACK_SIZE];

static YieldReason yield_reason;

static SDL_Window *window;
static SDL_Renderer *renderer;

static const int renderscale = 2;

static uint64_t keystate;

static int exited;

static uint8_t port1;
static uint8_t port2;

int main(int argc, char **argv)
{
    init_renderer();
    init_game();

    int credit = 0;
    size_t frame = -1;

    while (1)
    {
        frame++;
        input();

        if (exited) break;

        // preserves timing compatibility with MAME
        if (frame == 1)
            credit--;

        // up to mid

        credit += CRED1;
        loop_core(&credit);
        irq(0xcf);

        // up to vblank

        credit += CRED2;
        loop_core(&credit);
        irq(0xd7);

        render();
    }

    fini_game();
    fini_renderer();

    return 0;
}

static void input()
{
    SDL_Event event_buffer[64];
    size_t num = 0;

    while (num < 64)
    {
        int has = SDL_PollEvent(&event_buffer[num]);
        if (!has) break;
        num++;
    }

    for (size_t i = 0; i < num; ++i)
    {
        SDL_Event e = event_buffer[i];

        if (e.type == SDL_QUIT)
        {
            e.type = SDL_KEYDOWN;
            e.key.keysym.sym = SDLK_ESCAPE;
        }

        if (! (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)) continue;

        uint64_t mask = 0;
        uint64_t f = e.type == SDL_KEYDOWN;

        switch (e.key.keysym.sym)
        {
#define KEY_MAP(x, y) case x: mask = y; break;
            KEY_LIST
#undef KEY_MAP
        }

        keystate = (keystate & ~mask) | (-f & mask);
    }

#define BIT(x) (!!(keystate & (x)))

    port1 = (BIT(KEYS_RIGHT) << 6) |
            (BIT(KEYS_LEFT) << 5) |
            (BIT(KEYS_FIRE) << 4) |
            (1 << 3) |
            (BIT(KEYS_START) << 2) |
            (BIT(KEYS_START2) << 1) |
            (BIT(KEYS_COIN) << 0);

    port2 = (BIT(KEYS_DIP7) << 7) |
            (BIT(KEYS_RIGHT) << 6) |
            (BIT(KEYS_LEFT) << 5) |
            (BIT(KEYS_FIRE) << 4) |
            (BIT(KEYS_DIP6) << 3) |
            (BIT(KEYS_TILT) << 2);

    exited = BIT(KEYS_QUIT);
}

static void init_renderer()
{
    int rc = SDL_Init(SDL_INIT_EVERYTHING);
    assert(rc == 0);

    window = SDL_CreateWindow("si78c", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            224 * renderscale, 256 * renderscale, 0);
    assert(window);

    SDL_ShowCursor(SDL_DISABLE);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    assert(renderer);
}

static void fini_renderer()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

static void render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    const uint8_t *iter = rawmem + 0x2400;

    for (int y = 0; y < 224; ++y)
    {
        for (int xi = 0; xi < 32; ++xi)
        {
            uint8_t byte = *iter++;

            for (int i = 0; i < 8; ++i)
            {
                int x = xi * 8 + i;
                int on = (byte >> i) & 0x1;

                if (on)
                {
                    SDL_Rect rect;
                    rect.x = y * renderscale;
                    rect.y = (256 - x - 1) * renderscale;
                    rect.w = renderscale;
                    rect.h = renderscale;

                    SDL_RenderDrawRect(renderer, &rect);
                }
            }
        }
    }

    SDL_RenderPresent(renderer);
}

static void loop_core(int *credit)
{
    int allowed = 1;

    while (*credit > 0)
        *credit -= execute(allowed);
}

static void init_game()
{
    assert(sizeof(m) == 0x10000);
    load_rom(&m);

    assert(checksum(&m) == 0x6dfbd7cc);
    init_threads(YIELD_INIT);
}

static void fini_game()
{
}

static void init_threads(YieldReason entry_point)
{
    int rc = getcontext(&main_ctx);
    assert(rc == 0);

    main_ctx.uc_stack.ss_sp = main_ctx_stack;
    main_ctx.uc_stack.ss_size = STACK_SIZE;
    main_ctx.uc_link = &frontend_ctx;

    makecontext(&main_ctx, (void (*)()) run_main_ctx, 1, entry_point);

    rc = getcontext(&int_ctx);

    int_ctx.uc_stack.ss_sp = &int_ctx_stack;
    int_ctx.uc_stack.ss_size = STACK_SIZE;
    int_ctx.uc_link = &frontend_ctx;

    makecontext(&int_ctx, run_int_ctx, 0);
    prev_ctx = &main_ctx;
    curr_ctx = &frontend_ctx;
}

static void run_main_ctx(YieldReason entry)
{
    switch(entry)
    {
        case YIELD_INIT:           reset(); break;
        case YIELD_WAIT_FOR_START: WaitForStart(); break;
        case YIELD_PLAYER_DEATH:   player_death(0); break;
        case YIELD_INVADED:        on_invaded(); break;
        case YIELD_TILT:           on_tilt(); break;
        default: assert(FALSE);
    }
}

static void run_int_ctx()
{
    while (1)
    {
        // 0xcf = RST 1 opcode (call 0x8)
        // 0xd7 = RST 2 opcode (call 0x16)

        if (irq_vector == 0xcf)
            midscreen_int();
        else if (irq_vector == 0xd7)
            vblank_int();

        enable_interrupts();
        yield(YIELD_INTFIN);
    }
}

static unsigned checksum(Mem *m)
{
    assert(sizeof(*m) == 0x10000);
    assert((uintptr_t) m % 4 == 0);
    unsigned *ptr = (unsigned*) m;
    size_t n = sizeof(*m) / 4;

    unsigned sum = 0;

    for (size_t i = 0; i < n; ++i)
        sum += ptr[i];

    return sum;
}

static void rom_load(void *mem, const char* name, size_t offset, size_t len)
{
    char fbuf[256]; sprintf(fbuf, "inv1/%s", name);

    FILE *romfile = fopen(fbuf, "r");
    assert(romfile);

    ssize_t rn = fread((char*) mem + offset, 1, len, romfile);
    assert((size_t) rn == len);
    fclose(romfile);
}

static void load_rom(void *mem)
{
    rom_load(mem, "invaders.h", 0x0000, 0x0800);
    rom_load(mem, "invaders.g", 0x0800, 0x0800);
    rom_load(mem, "invaders.f", 0x1000, 0x0800);
    rom_load(mem, "invaders.e", 0x1800, 0x0800);
}

static int execute(int allowed)
{
    int64_t start = ticks;

    ucontext_t *next = NULL;

    switch (yield_reason)
    {
        case YIELD_INIT:
        case YIELD_TIMESLICE:
            next = prev_ctx;
            break;
        case YIELD_INTFIN:
            next = &main_ctx;
            break;
        case YIELD_PLAYER_DEATH:
        case YIELD_WAIT_FOR_START:
        case YIELD_INVADED:
            init_threads(yield_reason);
            enable_interrupts();
            next = &main_ctx;
            break;
        case YIELD_TILT:
            init_threads(yield_reason);
            next = &main_ctx;
            break;
        default:
            assert(FALSE);
    }

    yield_reason = YIELD_UNKNOWN;

    if (allowed && interrupted())
    {
        next = &int_ctx;
    }

    switch_to(next);

    return ticks - start;
}

static void switch_to(ucontext_t *to)
{
    co_switch(curr_ctx, to);
}

static void co_switch(ucontext_t *prev, ucontext_t *next)
{
    prev_ctx = prev;
    curr_ctx = next;

    swapcontext(prev, next);
}

static void timeslice()
{
    ticks += 30;

    yield(YIELD_TIMESLICE);
}

static void yield(YieldReason reason)
{
    yield_reason = reason;
    switch_to(&frontend_ctx);
}

static uint8_t get_input(int64_t ticks, uint8_t port)
{
    if (port == 1)
        return port1;

    if (port == 2)
        return port2;

    fatalerror("unknown port %d\n", port);
    return 0;
}

static uint8_t read_port(uint8_t port)
{
    if (port == 3)
        return (shift_data << shift_count) >> 8;

    uint8_t val = get_input(ticks, port);
    return val;
}

static void write_port(uint16_t port, uint8_t v)
{
    if (port == 2)
    {
        shift_count = v & 0x7;
    }
    else if (port == 4)
    {
        shift_data = (v << 8) | (shift_data >> 8);
    }

    timeslice();
}

static void enable_interrupts()
{
    im = 1;
}

static void irq(uint8_t v)
{
    irq_vector = v;
    irq_state = 1;
}

static int interrupted()
{
    // The two interrupts correspond to midscreen, and start of vblank.
    // 0xcf = RST 1 opcode (call 0x8)
    // 0xd7 = RST 2 opcode (call 0x16)

    if (irq_state && im)
    {
        assert(irq_vector == 0xcf || irq_vector == 0xd7);

        irq_state = 0;
        im = 0;
        return TRUE;
    }

    return FALSE;
}

static void fatalerror(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    vfprintf(stdout, format, ap);
    va_end(ap);

    fflush(stdout);
    fflush(stderr);

    exit(1);
}

static inline Word u16_to_word(uint16_t u)
{
    Word w; w.u16 = u; return w;
}

static inline Word u8_u8_to_word(uint8_t h, uint8_t l)
{
    return u16_to_word((h << 8) | l);
}

static inline uint16_t ptr_to_u16(uint8_t *ptr)
{
    return (uint16_t) (ptr - (uint8_t*) &m);
}

static inline Word ptr_to_word(uint8_t *ptr)
{
    return u16_to_word(ptr_to_u16(ptr));
}

static inline uint8_t* u16_to_ptr(uint16_t u)
{
    return ((uint8_t*) &m) + u;
}

static inline uint8_t* word_to_ptr(Word w)
{
    return u16_to_ptr(w.u16);
}

static int is_godmode()
{
    uint16_t addr = 0x060f;
    uint8_t nops[] = {0,0,0};

    return memcmp(((uint8_t*) &m) + addr, nops, 3) == 0;
}

static uint8_t* rompos(uint8_t* ram)
{
    return ram - 0x500;
}

static uint8_t bcd_add(uint8_t bcd, uint8_t a, uint8_t *carry)
{
    // Add the given number to the given bcd value, as per ADI / ADDB etc
    int q = bcd + a + *carry;
    *carry = (q >> 8) & 0x1;
    int aux = (bcd ^ q ^ a) & 0x10;
    bcd = q;

    // Adjust the result back into bcd as per DAA
    uint8_t w = bcd;

    if (aux || ((bcd & 0xf) > 9)) w += 6;
    if ((*carry) || (bcd > 0x99)) w += 0x60;
    *carry |= bcd > 0x99;
    bcd = w;

    return bcd;
}

static void do_logprintf(const char *file, unsigned line, const char* format, ...)
{
    fprintf(stdout, "%s:%d: ", file, line);

    va_list ap;
    va_start(ap, format);
    vfprintf(stdout, format, ap);
    va_end(ap);

    fflush(stdout);
}

static void DebugMessage(Word sc, uint8_t* msg, uint8_t n)
{
    uint16_t raw = sc.u16 - 0x2400;

    uint16_t x = raw / 32;
    uint16_t y = (raw % 32) * 8;
    static const char *alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789<> =*...............?......-";

    char sbuf[256];

    for (size_t i = 0; i < n; ++i)
        sbuf[i] = alpha[msg[i]];

    sbuf[n] = '\0';

    logprintf("Print Message %04x %d (%d,%d) \"%s\"\n", ptr_to_word(msg).u16, n, x, y, sbuf);
}

// GAMECODE START

// The entry point on reset or power up
static void reset()
{
    // xref 0000
    main_init(0);
}

// Executed via interrupt when the beam hits the middle of the screen
static void midscreen_int()
{
    // xref 0008
    // xref 008c
    m.vblankStatus = BEAM_MIDDLE;

    if (m.gameTasksRunning == 0) return;
    if (!m.gameMode && !(m.isrSplashTask & 0x1)) return;

    // xref 00a5
    // Run game objects but skip over first entry (player)

    RunGameObjs(u16_to_ptr(PLAYER_SHOT_ADDR));
    CursorNextAlien();
}

// Executed via interrupt when the beam hits the end of the screen
static void vblank_int()
{
    // xref 0010
    m.vblankStatus = BEAM_VBLANK;
    m.isrDelay--;
    CheckHandleTilt();
    vblank_coins();

    if (m.gameTasksRunning == 0)
        return;

    if (m.gameMode)
    {
        // xref 006f
        TimeFleetSound();
        m.shotSync = m.rolShotHeader.TimerExtra;
        DrawAlien();
        RunGameObjs(u16_to_ptr(PLAYER_ADDR));
        TimeToSaucer();
        return;
    }

    if (m.numCoins != 0)
    {
        // xref 005d
        if (m.waitStartLoop) return;

        m.waitStartLoop = 1;
        yield(YIELD_WAIT_FOR_START);
        assert(FALSE);
    }

    ISRSplTasks();
}

// Read coin input and handle debouncing
static void vblank_coins()
{
    // xref 0020

    if (read_port(1) & COIN_BIT)
    {
        // xref 0067
        m.coinSwitch = 1; // Remember switch state for debounce

        // xref 003f
        // useless update
        m.coinSwitch = 1;
        return;
    }

    // xref 0026
    // Skip registering the credit if prev and current states were both zero
    if (m.coinSwitch == 0)
        return;

    uint8_t bcd = m.numCoins;

    // Add credit if it won't cause a rollover
    if (bcd != 0x99)
    {
        uint8_t carry = 0;
        m.numCoins = bcd_add(bcd, 1, &carry);
        DrawNumCredits();
    }

    m.coinSwitch = 0;
}

// Initialize the alien rack speed and position using the current player's alien rack data
static void InitRack()
{
    // xref 00b1

    uint8_t* al_ref_ptr = GetAlRefPtr();

    Word refpos;
    refpos.y = *(al_ref_ptr);
    refpos.x = *(al_ref_ptr + 1);

    m.refAlienPos = refpos;
    m.alienPos = refpos;

    uint8_t dxr = *(al_ref_ptr - 1);

    if (dxr == 3)
        --dxr;

    m.refAlienDelta.x = dxr;
    m.rackDirection = (dxr == (uint8_t) -2) ? 1 : 0;
}

// Set up P1 and P2 Rack data
static void InitAlienRacks()
{
    // xref 00d7

    // Added for si78c testing infrastructure
    // In normal operation, dx is hardcoded to 2
    uint8_t dx = ((uint8_t*) &m)[0x00d8];

    m.p1RefAlienDX = dx;
    m.p2RefAlienDX = dx;

    // xref 08e4
    if (m.twoPlayers)
        return;

    ClearSmallSprite(xytosc(168, 224), 32, 0);
}

// Draw the alien, called via vblank_int()
// Only one alien is ever drawn per frame, causing a ripple effect.
// This also somewhat determines the game speed.
//
// The alien rack is effectively moving at
// (2.0 / num_aliens) pixels per frame
//
// If 55 aliens are alive, then it will take almost one second to move all the aliens by 2 pixels.
// If  1 alien is alive, then it will only take one frame to move 2 pixels.
static void DrawAlien()
{
    // xref 0100

    if (m.alienIsExploding)
    {
        if (--m.expAlienTimer) return;

        EraseSimpleSprite(m.expAlien.pos, 16);

        m.plyrShotStatus = 4;
        m.alienIsExploding = 0;
        SoundBits3Off(0xf7);
        return;
    }

    uint8_t ai = m.alienCurIndex;
    uint8_t* alienptr = u16_to_ptr(m.playerDataMSB << 8 | ai);

    if (*alienptr == 0)
    {
        // The alien is dead, so skip it and tell CursorNextAlien to advance.
        m.waitOnDraw = 0;
        return;
    }

    // Look up the correct alien sprite based on row and anim frame

    uint8_t row = m.alienRow;
    static const uint8_t mul[] = {0,0,16,16,32};
    uint8_t* sprite = u16_to_ptr(0x1c00 + mul[row] + m.alienFrame * 48);

    SprDesc desc;
    desc.pos = m.alienPos;
    desc.spr = ptr_to_word(sprite);
    desc.n = 16;

    DrawSprite(&desc);
    m.waitOnDraw = 0; // This flag is synced with CursorNextAlien
}

// Find the next live alien to draw. Also detects whether rack has reached the bottom.
static void CursorNextAlien()
{
    // xref 0141

    if (m.playerOK == 0) return;
    if (m.waitOnDraw != 0) return;

    Word ai;
    ai.h = m.playerDataMSB;
    ai.l = m.alienCurIndex;
    uint8_t movecnt = 0x02; // limits MoveRefAlien to be called once

    // Advance the cursor until we find a live alien to draw.
    // If the cursor reaches the end, move ref alien, flip anim and reset cursor to zero.
    while (TRUE)
    {
        timeslice();
        ++ai.l;

        // inlined MoveRefAlien
        if (ai.l == 55)
        {
            if (--movecnt == 0) return;

            m.alienCurIndex = 0;
            ai.l = 0;

            uint8_t dy = m.refAlienDelta.y;
            m.refAlienDelta.y = 0;
            AddDelta(&m.refAlienDelta.y, dy);

            m.alienFrame = !m.alienFrame;
            (void) (uint8_t) (m.playerDataMSB); // unused
        }

        // If we found live alien to draw, then break
        if (*word_to_ptr(ai)) break;
    }

    m.alienCurIndex = ai.l;

    uint8_t row = 0;
    Word pixnum = GetAlienCoords(&row, ai.l);
    m.alienPos = pixnum;

    if (pixnum.y < 40)
    {
        // xref 1971
        // kill the player due to invasion

        m.invaded = 1;
        yield(YIELD_INVADED);
        assert(FALSE);
    }

    m.alienRow = row;
    m.waitOnDraw = 1;
}

// Given alien index k, return alien position and row
static Word GetAlienCoords(uint8_t *rowout, uint8_t k)
{
    // xref 017a

    uint8_t row = k / 11;
    uint8_t col = k % 11;

    uint8_t y = m.refAlienPos.y + 16 * row;
    uint8_t x = m.refAlienPos.x + 16 * col;

    *rowout = row;
    return u8_u8_to_word(x, y);
}

// Init all the aliens at dest to alive
static void InitAliensSub(uint8_t* dest)
{
    // xref 01c0
    for (int i = 0; i < 55; ++i)
        *dest++ = 1;
}

// Init all the aliens for P1
static void InitAliensP1()
{
    // xref 01c0
    InitAliensSub(u16_to_ptr(P1_ADDR));
}

// Draw a one pixel (leftmost/bottommost in byte) stripe across the screen (224 pix wide)
// 16 pixels above the origin.
static void DrawBottomLine()
{
    // xref 01cf
    ClearSmallSprite(xytosc(0,16), 224, 1);
}

// Given four bytes at vecptr treat them as two vecs - dy dx, y x
// and do this:
//
//     (y,x) += (c, dx)
//
// Used to move objects
static uint8_t AddDelta(uint8_t* vecptr, uint8_t c)
{
    vecptr++; // skip dy

    uint8_t dy = c;
    uint8_t dx = *vecptr++;

    uint8_t y = *vecptr + dy;
    *vecptr++ = y;

    uint8_t x = *vecptr + dx;
    *vecptr++ = x;

    return x;
}

// Restore into RAM mirror (addr, n) from ROM
static void RestoreFromROM(uint8_t* addr, size_t n)
{
    BlockCopy(addr, rompos(addr), n);
}

// Restore the entire RAM mirror (256 bytes), used at startup
static void CopyRomtoRam()
{
    // xref 01e6
    RestoreFromROM(u16_to_ptr(0x2000), 256);
}

// Partially restore the RAM mirror (first 192 bytes)
// The last 64 bytes are managed elsewhere, and some are
// persistent across games (hi scores etc)
static void CopyRAMMirror()
{
    // xref 01e4
    RestoreFromROM(u16_to_ptr(0x2000), 192);
}

// Initialize P1 shields into off screen buffer
static void DrawShieldP1()
{
    // xref 01ef
    DrawShieldCommon(m.p1ShieldBuffer);
}

// Initialize P2 shields into off screen buffer
static void DrawShieldP2()
{
    // xref 01f5
    DrawShieldCommon(m.p2ShieldBuffer);
}

// Initialize shields into given buffer
static void DrawShieldCommon(uint8_t* dest)
{
    // xref 01f8
    size_t n = 44;

    for (int i = 0; i < 4; ++i, dest += n)
        BlockCopy(dest, m.SHIELD_SPRITE, n);
}

// Copy on screen shields into P1 off screen buffer to remember damage
static void RememberShieldsP1()
{
    // xref 0209
    CopyShields(1, m.p1ShieldBuffer);
}

// Copy on screen shields into P2 off screen buffer to remember damage
static void RememberShieldsP2()
{
    // xref 020e
    CopyShields(1, m.p2ShieldBuffer);
}

// Copy off screen shields from P2 buffer back to screen
static void RestoreShieldsP2()
{
    // xref 0213
    CopyShields(0, m.p2ShieldBuffer);
}

// Copy off screen shields from P1 buffer back to screen
static void RestoreShieldsP1()
{
    // xref 021a
    CopyShields(0, m.p1ShieldBuffer);
}

// Generic shield copy routine. Copy into or out of given buffer.
// dir = 0 - buffer to screen
// dir = 1 - screen to buffer
static void CopyShields(uint8_t dir, uint8_t* sprbuf)
{
    // xref 021e
    m.tmp2081 = dir;

    Word sprsz = u8_u8_to_word(22, 2); // 22 rows, 2 bytes per row

    ShieldBufferCursor cursor;
    cursor.sc = xytosc(32, 48);
    cursor.iter = sprbuf;

    for (int i = 0; i < 4; ++i)
    {
        uint8_t unused = m.tmp2081;
        (void) (unused);

        CopyShieldBuffer(&cursor, sprsz, dir);

        cursor.sc.u16 += xysc(23, 0);
    }
}

// Do the generic (base class) handling for the 5 game objects.
// Checks the timer flags to see if object is ready to run, and if so
// finds the appropriate subclass handler and calls it.
static void RunGameObjs(uint8_t* ptr)
{
    // xref 0248

    for ( ; ; ptr += 16)
    {
        GameObjHeader* obj = (GameObjHeader*)(ptr);
        uint8_t timer_hi = obj->TimerMSB;

        // end of list check
        if (timer_hi == 0xff) return;

        // object skip check
        if (timer_hi == 0xfe) continue;

        uint8_t timer_lo = obj->TimerLSB;

        // decrement timer if its not zero
        if (timer_hi | timer_lo)
        {
            // xref 0277
            // timers are big endian for some reason.

            if (timer_lo == 0) --timer_hi;   // decrement msb if necc
            --timer_lo;                      // decrement lsb

            obj->TimerLSB = timer_lo;
            obj->TimerMSB = timer_hi;

            continue;
        }

        uint8_t timer_extra = obj->TimerExtra;

        if (timer_extra != 0)
        {
            // xref 0288
            obj->TimerExtra--;
            continue;
        }

        // The object is ready to run, so grab the handler and run it

        uint16_t fnlo = obj->Handler.l;
        uint16_t fnhi = obj->Handler.h;
        uint16_t fn = fnhi << 8 | fnlo;

        uint8_t* data = (ptr + sizeof(GameObjHeader));

        switch(fn)
        {
            case 0x028e: GameObj0(data); break;
            case 0x03bb: GameObj1(data); break;
            case 0x0476: GameObj2(data); break;
            case 0x04b6: GameObj3(data); break;
            case 0x0682: GameObj4(data); break;
            case 0x050e: ProcessSquigglyShot(); break; // splash anim
            default:
                 assert(FALSE);
                 break;
        }
    }
}

// Handles player movement and rendering
// Unlike other game objects, this is only run during the vblank interrupt, and
// runs on each vblank interrupt
static void GameObj0(uint8_t* unused)
{
    // xref 028e
    uint8_t pstate = m.playerAlive;

    if (pstate != 0xff) // 0xff means player is alive
    {
        HandleBlowingUpPlayer(pstate);
        return;
    }

    // xref 033b
    m.playerOK = 1;

    // xref 03b0
    if (m.enableAlienFire == 0)
    {
        // xref 03b3

        if (--m.alienFireDelay == 0)
            m.enableAlienFire = 1;
    }

    // xref 034a
    uint8_t x = m.playerDesc.pos.x;
    uint8_t input = 0;

    if (m.gameMode == 0)
    {
        input = m.nextDemoCmd;
    }
    else
    {
        input = ReadInputs();

        // Map joystick controls into the same domain as the demo commands
        if ((input >> 6) & 0x1)
            input = 1;
        else if ((input >> 5) & 0x1)
            input = 2;
        else
            input = 0;
    }

    if (input == 0)
    {
        // Do nothing
    }
    else if (input == 1)
    {
        // Move player to the right
        if (x != xpix(185))
        {
            ++x;
            m.playerDesc.pos.x = x;
        }
    }
    else if (input == 2)
    {
        // Move player to the left
        if (x != xpix(16))
        {
            --x;
            m.playerDesc.pos.x = x;
        }
    }
    else
    {
        assert(FALSE);
    }

    DrawPlayer();
}

// Handle the player's death animation. Resets the stack once complete,
// and re-entry is through player_death(0)
static void HandleBlowingUpPlayer(uint8_t anim)
{
    // xref 0296
    if (--m.expAnimateTimer != 0)
        return;

    m.playerOK = 0;
    m.enableAlienFire = 0;
    m.alienFireDelay = 48;
    m.expAnimateTimer = 5;

    if (--m.expAnimateCnt != 0)
    {
        // Still animating the explosion
        anim = !anim;
        m.playerAlive = anim;

        m.playerDesc.spr = ptr_to_word((m.PLAYER_SPRITES + (anim+1) * 16));
        DrawPlayer();
        return;
    }

    EraseSimpleSprite(m.playerDesc.pos, 16);
    RestoreFromROM(u16_to_ptr(PLAYER_ADDR), PLAYER_SIZE);

    SoundBits3Off(0);

    if (m.invaded)
        return;

    // Return to splash screens in demo mode
    if (m.gameMode == 0)
        return;

    yield(YIELD_PLAYER_DEATH);
    assert(FALSE);
}

// Handle cleanup tasks related to player dying, such as lives and score adjustment,
// switching players and calling GameOver if necessary.
// If invaded is one, the player loses the game, regardless of number of lives left.
// This routine is called after a stack reset, see on_invaded() and HandleBlowingUpPlayer()
static void player_death(int invaded)
{
    // xref 02d4
    int switch_players = player_death_sub(invaded);

    if (!switch_players)
    {
        if (!*(GetOtherPlayerAliveFlag()) || !m.twoPlayers)
        {
            RemoveShip();
            NewGame(0, 0, INIT | PROMPT | SHIELDS);
        }
    }

    uint8_t pnum = m.playerDataMSB;

    if (pnum & 0x1)
        RememberShieldsP1();
    else
        RememberShieldsP2();

    uint8_t adx = 0;
    Word apos;
    uint8_t* aref = GetRefAlienInfo(&adx, &apos);

    *aref = apos.y;
    *(aref+1) = apos.x;

    *(aref-1) = adx;

    // about to switch players.
    CopyRAMMirror();

    uint8_t carry = pnum & 0x1;
    uint8_t pmsb = 0x21; // p1
    uint8_t cbit = 0;

    if (carry)
    {
        cbit = 0x20; // cocktail bit=1
        pmsb = 0x22;
    }

    m.playerDataMSB = pmsb; // change players
    TwoSecDelay();

    m.playerHeader.TimerLSB = 0; // clear player object timer
    write_port(5, cbit);

    m.soundPort5 = (cbit + 1);
    ClearPlayField();
    RemoveShip();

    // jmp to 079b. (newgame + skip)
    NewGame(0, 0, INIT);
}

// Player death cleanup subroutine. Game is lost immediately if invaded=1
// Returns true if caller should switch players, false otherwise
// This subroutine will not return if all players have lost the game, instead it
// will call through to GameOver, which will start a new game
static int player_death_sub(int invaded)
{
    if (!invaded)
    {
        DsableGameTasks();

        uint8_t* unused;

        // still got some ships, keep going
        if (GetNumberOfShips(&unused) != 0)
            return FALSE;

        PrintNumShips(0);
    }

    // handle losing the game

    *CurPlyAlive() = 0;

    uint8_t* sc = GetScoreDescriptor();
    sc++;

    uint8_t* hi = &m.HiScor.h;

    uint8_t hi_score_msb = *(hi);
    uint8_t pl_score_msb = *(sc);

    hi--;
    sc--;

    uint8_t hi_score_lsb = *(hi);
    uint8_t pl_score_lsb = 0;

    int higher = FALSE;

    if (hi_score_msb == pl_score_msb)
    {
        // same msb, must check lower
        pl_score_lsb = *(sc);
        higher = pl_score_lsb > hi_score_lsb;
    }
    else
    {
        higher = pl_score_msb > hi_score_msb;
    }

    if (higher)
    {
        *hi++ = *sc++;
        *hi = *sc;
        PrintHiScore();
    }

    // xref 1698
    if (m.twoPlayers)
    {
        // Game over player<n>
        Word sc = xytosc(32, 24);
        sc = PrintMessageDel(sc, m.MSG_GAME_OVER__PLAYER___, 0x14);

        sc.u16 -= xysc(16, 0); // back up to player indicator
        uint8_t b = (m.playerDataMSB & 0x1) ? 0x1b : 0x1c;

        sc = DrawChar(sc, b);  // print player num
        OneSecDelay();

        if (*(GetOtherPlayerAliveFlag()) == 0)
        {
            GameOver();     // won't return.
            assert(FALSE);
        }

        // switch players
        return TRUE;
    }
    else
    {
        GameOver(); // won't return
        assert(FALSE);
    }

    return FALSE;
}

// Generic player shot drawing routine, originally multiple small fragments
static void DrawPlayerShot(int op)
{
    // xref 0404
    // xref 03f4
    SprDesc plyshot = ReadPlyShot();

    if (op == OP_BLEND)
        DrawShiftedSprite(&plyshot);
    else if (op == OP_ERASE)
        EraseShifted(&plyshot);
    else
        assert(FALSE);
}

// Handles player bullet movement, collision detection and rendering.
// At the end of the routine, the player's shot count is used to
// set up the next saucer direction and score.
static void GameObj1(uint8_t* unused)
{
    // xref 03bb
    //
    // Shot states:
    //
    // :Available(0), :Initiated(1), :Moving(2), :HitNotAlien(3),
    // :AlienExploded(4), :AlienExploding(5)

    if (!CompXrToBeam(&m.playerShotDesc.pos.x))
        return;

    uint8_t status = m.plyrShotStatus;

    if (status == 0)
        return;

    if (status == 1)
    {
        // xref 03fa InitPlyShot
        m.plyrShotStatus = 2;
        m.playerShotDesc.pos.x = m.playerDesc.pos.x + 8;
        DrawPlayerShot(OP_BLEND);
        return;
    }
    else if (status == 2)
    {
        // xref 040a MovePlyShot
        SprDesc copy = ReadPlyShot();
        EraseShifted(&copy);

        copy.pos.y += m.shotDeltaYr;
        m.playerShotDesc.pos.y = copy.pos.y;

        DrawSprCollision(&copy);
        uint8_t collided = m.collision;

        if (!collided) return;

        m.alienIsExploding = collided;
        return;
    }

    if (status != 3)
    {
        // xref 042a
        if (status == 5) return;

        // continues at EndOfBlowup
    }
    else
    {
        // xref 03d7
        if (--m.blowUpTimer != 0)
        {
            // The shot is blowing up
            if (m.blowUpTimer != 0x0f) return;

            // Draw the explosion the first time through
            // xref 03df
            DrawPlayerShot(OP_ERASE);

            // Change the shot sprite to the explosion.
            m.playerShotDesc.spr.l++;

            // Modify the coords slightly for the explosion
            m.playerShotDesc.pos.y--; // y -= 2
            m.playerShotDesc.pos.y--;

            m.playerShotDesc.pos.x--; // x -= 3
            m.playerShotDesc.pos.x--;
            m.playerShotDesc.pos.x--;

            m.playerShotDesc.n = 8;
            DrawPlayerShot(OP_BLEND);
            return;
        }
    }

    // xref 0436 EndOfBlowup
    DrawPlayerShot(OP_ERASE);

    // xref 0444
    // reset the shot
    RestoreFromROM(u16_to_ptr(PLAYER_SHOT_DATA_ADDR), PLAYER_SHOT_DATA_SIZE);

    // The remaining code in GameObj0 is to do with adjusting the saucer bonus and
    // direction, which is changed up on every player shot fired.

    // Adjust the saucer bonus.
    {
        Word table = m.sauScore;

        table.l++;

        if (table.l >= 0x63)
            table.l = 0x54;

        m.sauScore = table;
    }

    Word shots = m.shotCount;

    shots.l++;
    m.shotCount = shots;

    // xref 0461
    // If saucer still on screen, don't reset the direction.
    if (m.saucerActive)
        return;

    // xref 0462
    //
    // This code is using the shot counter as an index into the ROM
    // (where some code resides), for the purposes of random number generation.
    //
    // For the saucer direction logic, only bit 0 of each bytecode is used.
    //
    // The 256 bytes used reside at 0800 -> 08FF
    //
    // If you check bit 0 of each byte in that ROM section, you will find that there is no bias,
    // and there are exactly 128 0's and 128 1's.
    //
    // It seems unlikely that this was an accident, I think Nishikado deliberately constructed
    // the ROM this way, and used some well placed NOPs to achieve fair balance.
    //
    // E.g. these NOPs
    //
    // 0854: 00 00 00
    // 0883: 00 00 00

    // This information can be exploited to the player's advantage.
    //
    // If using the shot counting trick to get high scores, the
    // expected saucer direction for the first 6 saucers (if counting),
    // will be as follows:
    //
    // [22,37,52,67,82,97]
    // [0, 1, 1, 0, 1, 1]
    // [L, R, R, L, R, R]

    uint8_t v = *(word_to_ptr(shots));

    // if lo bit of res is 0, then delta = -2, x = 192 (moving left from rhs)
    // if lo bit of res is 1, then delta = +2, x = 9   (moving right from lhs)

    uint8_t delta = -2;
    uint8_t     x = xpix(192);

    if (v & 0x1)
    {
        delta = 2;
        x     = xpix(9);
    }

    m.saucerDesc.pos.x = x;
    m.saucerDXr = delta;
}

// Return a copy of the player shot sprite descriptor
static SprDesc ReadPlyShot()
{
    // xref 0430
    return ReadDesc(&m.playerShotDesc);
}

// Handles alien rolling shot firing, movement, collision detection and rendering.
// This is the shot that specifically targets the player.
// Most of the logic is shared between the 3 types inside HandleAlienShot.
static void GameObj2(uint8_t* unused1)
{
    // xref 0476
    RestoreFromROM(&m.rolShotHeader.TimerExtra, 1);

    if (m.rolShotData.CFir.u16 == 0)
    {
        // The rolling shot doesn't use a firing table to choose a column to fire
        // from, because it specifically targets the player.
        //
        // It just uses this member as a flag to delay firing the first rolling shot
        m.rolShotData.CFir.u16 = 0xffff;
        return;
    }

    ToShotStruct(&m.rolShotData, ROL_SHOT_PICEND);

    m.otherShot1 = m.pluShotData.StepCnt;
    m.otherShot2 = m.squShotData.StepCnt;

    HandleAlienShot();

    if (m.aShot.BlowCnt != 0)
    {
        // shot still running, copy updated data from active -> rolling and return.
        FromShotStruct(&m.rolShotData);
        return;
    }

    RestoreFromROM(u16_to_ptr(ROLLING_SHOT_ADDR), ROLLING_SHOT_SIZE);
}

// Handles alien plunger shot firing, movement, collision detection and rendering.
static void GameObj3(uint8_t* unused)
{
    // xref 04b6
    if (m.skipPlunger) return;
    if (m.shotSync != 1) return;

    ToShotStruct(&m.pluShotData, PLU_SHOT_PICEND);

    m.otherShot1 = m.rolShotData.StepCnt;
    m.otherShot2 = m.squShotData.StepCnt;

    HandleAlienShot();

    if (m.aShot.CFir.l >= 16)
    {
        m.aShot.CFir.l = *(rompos(&m.pluShotData.CFir.l));
    }

    if (m.aShot.BlowCnt)
    {
        FromShotStruct(&m.pluShotData);
        return;
    }

    RestoreFromROM(u16_to_ptr(PLUNGER_SHOT_ADDR), PLUNGER_SHOT_SIZE);

    if (m.numAliens == 1)
        m.skipPlunger = 1;

    m.pluShotData.CFir = m.aShot.CFir;
}

// Handles alien squiggly shot firing, movement, collision detection and rendering.
// This is very similar logic to the plunger shot except the column firing table
// is different.
static void ProcessSquigglyShot()
{
    // xref 050f
    ToShotStruct(&m.squShotData, SQU_SHOT_PICEND);

    m.otherShot1 = m.pluShotData.StepCnt;
    m.otherShot2 = m.rolShotData.StepCnt;

    HandleAlienShot();

    if (m.aShot.CFir.l >= 21)
    {
        // Restores to the rom lsb values of '6'
        m.aShot.CFir.l = *(rompos(&m.squShotData.CFir.l));
    }

    if (m.aShot.BlowCnt)
    {
        FromShotStruct(&m.squShotData);
        return;
    }

    RestoreFromROM(u16_to_ptr(SQUIGGLY_SHOT_ADDR), SQUIGGLY_SHOT_SIZE);
    m.squShotData.CFir = m.aShot.CFir;
}

// Copy an alien shot structure from src into the active alien shot structure,
// and configure the shot animation.
static void ToShotStruct(AShot* src, uint8_t picend)
{
    // xref 0550
    m.shotPicEnd = picend;
    BlockCopy(&m.aShot, src, 11);
}

// Copy the active alien shot structure into dest
static void FromShotStruct(AShot* dest)
{
    // xref 055b
    BlockCopy( dest,  &m.aShot, 11);
}

// This logic is shared between the 3 shot types.
// Handles shot firing, movement, collision detection and rendering.
static void HandleAlienShot()
{
    // xref 0563
    if ((m.aShot.Status & SHOT_ACTIVE) != 0)
    {
        HandleAlienShotMove();
        return;
    }

    uint8_t shooting_c = (m.isrSplashTask == 0x04);
    uint8_t fire_enabled = m.enableAlienFire;

    if (shooting_c)
    {
        // Special case for the splash animation
        m.aShot.Status |= SHOT_ACTIVE;
        m.aShot.StepCnt++;

        return;
    }

    if (!fire_enabled)
        return;

    m.aShot.StepCnt = 0;

    {
        uint8_t steps = m.otherShot1;
        if (steps && steps <= m.aShotReloadRate) return;
    }

    {
        uint8_t steps = m.otherShot2;
        if (steps && steps <= m.aShotReloadRate) return;
    }

    uint8_t col = 0;

    if (m.aShot.Track == 0)
    {
        // xref 061b
        // Make a tracking shot, by finding the column that is above the player

        Word res = FindColumn(m.playerDesc.pos.x + 8); // find column over centre of player
        col = res.h; // res.l unused

        if (col >= 12)
            col = 11;
    }
    else
    {
        // xref 059c
        // Use the firing table pointer to pick the column, and advance it
        uint8_t* hl = word_to_ptr(m.aShot.CFir);
        col = *hl++;
        m.aShot.CFir = ptr_to_word(hl);
    }

    // xref 05a5
    uint8_t k = 0;
    uint8_t found = FindInColumn(&k, col);

    if (!found)
        return;

    uint8_t row_unused = 0;
    Word pixnum = GetAlienCoords(&row_unused, k);

    pixnum.x += 7;
    pixnum.y -= 10;

    m.aShot.Desc.pos = pixnum;
    m.aShot.Status |= SHOT_ACTIVE;
    m.aShot.StepCnt++;

    return;
}

// Handle moving the alien shot and some collision detection response.
// Returns 1 if shot status needs to be set to blowing up, 0 if not.
static int DoHandleAlienShotMove()
{
    if (!CompXrToBeam(&m.aShot.Desc.pos.x))
        return 0;

    if (m.aShot.Status & SHOT_BLOWUP)
    {
        ShotBlowingUp();
        return 0;
    }

    // xref 05cf
    m.aShot.StepCnt++;
    EraseAlienShot();

    // Animate the shot
    uint8_t shotpic = m.aShot.Desc.spr.l + 3;

    if (shotpic > m.shotPicEnd)
        shotpic -= 12;

    m.aShot.Desc.spr.l = shotpic;
    m.aShot.Desc.pos.y = m.aShot.Desc.pos.y + m.alienShotDelta;
    DrawAlienShot();

    // xref 05f3
    uint8_t y = m.aShot.Desc.pos.y;

    if (y < 21)
        return 1;

    if (!m.collision)
        return 0;

    y = m.aShot.Desc.pos.y;

    // below or above players area ?
    if (y < 30 || y >= 39)
        return 1;

    if (!is_godmode())
        m.playerAlive = 0;

    return 1;
}

// Handle moving the alien shot and some collision detection response.
static void HandleAlienShotMove()
{
    // xref 05c1
    int exploded = DoHandleAlienShotMove();

    if (exploded)
        m.aShot.Status |= SHOT_BLOWUP;
}

// Find a live alien in the given column.
static uint8_t FindInColumn(uint8_t *out, uint8_t col)
{
    // xref 062f
    Word hl;

    hl.h = m.playerDataMSB;
    hl.l = col - 1;

    int found = 0;

    for (int i = 0; i < 5; ++i)
    {
        if (*word_to_ptr(hl))
        {
            found = 1;
            break;
        }

        hl.l += 11;
    }

    *out = hl.l;
    return found;
}

// Handle alien shot explosion animation
static void ShotBlowingUp()
{
    // xref 0644
    m.aShot.BlowCnt--;

    uint8_t blowcnt = m.aShot.BlowCnt;

    if (blowcnt == 3)
    {
        EraseAlienShot();
        m.aShot.Desc.spr = ptr_to_word(m.AlienShotExplodingSprite);

        // Offset the explision sprite from the shot by (-2,-2)

        m.aShot.Desc.pos.x--;
        m.aShot.Desc.pos.x--;

        m.aShot.Desc.pos.y--;
        m.aShot.Desc.pos.y--;

        m.aShot.Desc.n = 6;

        DrawAlienShot();
        return;
    }

    if (blowcnt)
        return;

    EraseAlienShot();
}

// Draw the active alien shot and do collision detection
static void DrawAlienShot()
{
    // xref 066c
    SprDesc desc = ReadDesc(&m.aShot.Desc);
    DrawSprCollision(&desc);
    return;
}

// Erase the active alien shot
static void EraseAlienShot()
{
    // xref 0675
    SprDesc desc = ReadDesc(&m.aShot.Desc);
    EraseShifted(&desc);
    return;
}

// Handles either the Squiggly shot or the Saucer, depending on the saucer timer.
// See ProcessSquigglyShot for squiggly shot logic.
// The bulk of this routine handles saucer movement, collision response, rendering
// and scoring.
static void GameObj4(uint8_t* unused)
{
    // xref 0682
    if (m.shotSync != 2) return;

    if (m.saucerStart == 0)
    {
        ProcessSquigglyShot();
        return;
    }

    if (m.squShotData.StepCnt)
    {
        ProcessSquigglyShot();
        return;
    }

    if (!m.saucerActive)
    {
        if (m.numAliens < 8)
        {
            ProcessSquigglyShot();
            return;
        }

        m.saucerActive = 1;
        DrawSaucer();
    }

    uint8_t carry = CompXrToBeam(&m.saucerDesc.pos.x);

    if (!carry)
        return;

    if (!m.saucerHit)
    {
        uint8_t x  = m.saucerDesc.pos.x;
        uint8_t dx = m.saucerDXr;

        m.saucerDesc.pos.x = x + dx;
        DrawSaucer();

        x = m.saucerDesc.pos.x;

        // check edges
        if (x < xpix(8))
        {
            RemoveSaucer();
            return;
        }

        if (x >= xpix(193))
        {
            RemoveSaucer();
            return;
        }

        return;
    }

    SoundBits3Off(0xfe); // turn off saucer sound

    m.saucerHitTime--;
    uint8_t timer = m.saucerHitTime;

    if (timer == 31)
    {
        // xref 074b
        // Turn on the sound and draw the saucer explosion
        uint8_t snd = m.soundPort5 | 16;
        m.soundPort5 = snd;
        SetSoundWithoutFleet(snd);

        m.saucerDesc.spr = ptr_to_word(m.SpriteSaucerExp);
        DrawSaucer();

        return;
    }

    if (timer == 24)
    {
        // xref 070c
        m.adjustScore = 1;

        // Get the score for the saucer which is set based on shots fired in GameObj0
        uint8_t score = *(word_to_ptr(m.sauScore));

        // Find the index of the score in the table
        int i = 0;
        for (i = 0; i < 4; ++i)
        {
            if (m.SauScrValueTab[i] == score)
                break;
        }

        // Use it to find the matching LSB for the score text, and set it in saucerDesc
        m.saucerDesc.spr.l = m.SauScrStrTab[i];

        // Multiply the score by 16 (i.e. bcd shift left one digit), to get 50,100,150,300 in BCD
        m.scoreDelta.u16 = score * 16;

        // Print the bonus score message, using pointer set in saucerDesc.spr above
        SprDesc desc = GetSaucerInfo();
        PrintMessage(desc.sc, word_to_ptr(desc.spr), 3);

        return;
    }

    // xref 06e8
    if (timer != 0)
        return;

    uint8_t snd = m.soundPort5 & 0xef;
    m.soundPort5 = snd;
    write_port(5, snd & 0x20);

    RemoveSaucer();
}

// Saucer cleanup tasks
static void RemoveSaucer()
{
    // xref 06f9
    SprDesc desc = ReadDesc(&m.saucerDesc);
    ClearSmallSprite(ConvToScr(desc.pos), desc.n, 0);
    RestoreFromROM(u16_to_ptr(SAUCER_ADDR), SAUCER_SIZE);
    SoundBits3Off(0xfe);
}

// Grab a copy of the saucer sprite descriptor, and set it up
// for rendering before returning it.
static SprDesc GetSaucerInfo()
{
    // xref 0742
    SprDesc desc = ReadDesc(&m.saucerDesc);
    desc.sc = ConvToScr(desc.pos);
    return desc;
}

// Draw the player sprite
static void DrawPlayer()
{
    // xref 036f
    SprDesc desc = ReadDesc(&m.playerDesc);

    desc.sc = ConvToScr(desc.pos);
    DrawSimpSprite(&desc);

    m.playerHeader.TimerExtra = 0;
}

// Draw the saucer sprite
static void DrawSaucer()
{
    // xref 073c
    // xref 0742
    SprDesc desc = GetSaucerInfo();
    DrawSimpSprite(&desc);
}

// Wait for the player to press 1P or 2P, and then start the game
// with the appropriate flags.
// This loop is entered after the player has inserted a coin outside of game mode, see vblank_int()
static void WaitForStart()
{
    // xref 076e
    {
        // xref 1979
        // SuspendGameTasks
        DsableGameTasks();
        DrawNumCredits();
        PrintCreditLabel();
    }

    ClearPlayField();
    PrintMessage(xytosc(96, 152), m.MSG_PUSH, 4);

    while (TRUE)
    {
        timeslice();

        if ((m.numCoins - 1) != 0)
        {
            // Enough credits for either 1P or 2P start
            PrintMessage(xytosc(32, 128), m.MSG_1_OR_2PLAYERS_BUTTON, 20);

            // Handle 1P or 2P
            uint8_t inp = read_port(1);

            if (inp & 0x2) NewGame(1, 0x98, 0);
            if (inp & 0x4) NewGame(0, 0x99, 0);

            continue;
        }

        // Only enough credits for 1P start
        PrintMessage(xytosc(32, 128), m.MSG_ONLY_1PLAYER__BUTTON, 20);

        // Break if 1P start hit.
        if (read_port(1) & 0x4)
            break;
    }

    NewGame(0, 0x99, 0);
}

// Starts a new game, and runs the game loop.
// This routine is entered via either the WaitForStart() loop after inserting coins
// outside of game mode, or is entered after the player dies via player_death()
// to continue the game.
// is2p - set to true if 2P was pressed
// cost - credits to deduct in bcd (0x99=1, 0x98=2 credits)
// skip - used to skip certain parts of initialization, used for continue
static void NewGame(uint8_t is2p, uint8_t cost, int skip)
{
    // xref 0798
    // xref 079b
    int flags = ~skip;

    if (flags & INIT)
    {
        m.twoPlayers = is2p;

        {
            uint8_t unused_carry = 0;
            m.numCoins = bcd_add(m.numCoins, cost, &unused_carry);
        }

        DrawNumCredits();

        m.P1Scor.u16 = 0;
        m.P2Scor.u16 = 0;

        PrintP1Score();
        PrintP2Score();

        DsableGameTasks();

        m.gameMode = 1;

        m.playerStates.u16 = 0x0101;  // Both players alive
        m.playerExtras.u16 = 0x0101;  // Both players bonus available

        DrawStatus();
        DrawShieldP1();
        DrawShieldP2();

        uint8_t ships = GetShipsPerCred();

        m.p1ShipsRem = ships;
        m.p2ShipsRem = ships;

        InitAlienRacks();

        m.p1RackCnt = 0;
        m.p2RackCnt = 0;

        InitAliensP1();
        InitAliensP2();

        m.p1RefAlienPos = xytopix(24, 120);
        m.p2RefAlienPos = xytopix(24, 120);

        CopyRAMMirror();
        RemoveShip();
    }

    if (flags & PROMPT)
    {
        PromptPlayer();
        ClearPlayField();
        m.isrSplashTask = 0;
    }

    // xref 0804 top of new game loop
    while (TRUE)
    {
        if (flags & SHIELDS)
        {
            DrawBottomLine();

            if (m.playerDataMSB & 0x1)
            {
                RestoreShieldsP1();
            }
            else
            {
                RestoreShieldsP2();
                DrawBottomLine();
            }

            // xref 0814
            InitRack();
        }
        else
        {
            flags |= SHIELDS; // don't skip next time
        }

        EnableGameTasks();
        SoundBits3On(0x20);

        // xref 081f game loop

        while (TRUE)
        {
            PlrFireOrDemo();
            PlyrShotAndBump();
            CountAliens();

            AdjustScore();

            if (m.numAliens == 0)
            {
                HandleEndOfTurn();
                break;
            }

            AShotReloadRate();
            CheckAndHandleExtraShipAward();
            SpeedShots();
            ShotSound();

            if (! IsPlayerAlive())
                SoundBits3On(0x04); // Turn on player hit sound

            uint8_t w = FleetDelayExShip();
            write_port(6, w);                   // Feed the watchdog
            CtrlSaucerSound();
        }
    }
}

// Get reference alien velocity, position and pointer for the current player
static uint8_t* GetRefAlienInfo(uint8_t *dxr, Word *pos)
{
    // xref 0878
    *dxr = m.refAlienDelta.x;
    *pos = m.refAlienPos;
    return GetAlRefPtr();
}

// Get reference alien pointer for the current player
static uint8_t* GetAlRefPtr()
{
    // xref 0886
    return (m.playerDataMSB & 0x1) ? &m.p1RefAlienPos.l :
                                                &m.p2RefAlienPos.l;
}

// Print "PLAY PLAYER<n>" and flash the score at 15 hz for 3 seconds
// This is done upon starting a NewGame in 1P mode, or at the start
// of every turn in 2P mode.
static void PromptPlayer()
{
    // xref 088d

    // "PLAY PLAYER<1>"
    PrintMessage(xytosc(56,136), m.MSG_PLAY_PLAYER_1_, 14);

    // replace <1> with <2>
    if ((m.playerDataMSB & 0x1) == 0)
        DrawChar(xytosc(152, 136), 0x1c);

    m.isrDelay = 176; // 3 sec delay

    // xref 08a9
    while (TRUE)
    {
        timeslice();
        uint8_t isrtick = m.isrDelay;

        if (isrtick == 0)
            return;

        // Flash player score every 4 isrs
        if (isrtick & 0x4)
        {
            // xref 08bc
            Word sc = (m.playerDataMSB & 0x1) ? xytosc(24,224) : xytosc(168,224);
            ClearSmallSprite(sc, 32, 0);
            continue;
        }

        DrawScore(GetScoreDescriptor());
    }
}

// DIP5 and DIP3 control the number of extra lives the player starts with.
// DIP5 and DIP3 are wired into bits 1 and 0 of port 2 respectively.
//
// When read together as a two digit binary number, this is meant to be
// interpreted as the number of extra lives above the default of 3 that
// the player gets.
//
// 0 0 - 3 lives
// 0 1 - 4 lives
// 1 0 - 5 lives
// 1 1 - 6 lives
static uint8_t GetShipsPerCred()
{
    // xref 08d1
    return (read_port(2) & (DIP5_SHIPS2 | DIP3_SHIPS1)) + 3;
}

// Increase alien shot speed when there are less than nine aliens on screen
static void SpeedShots()
{
    // xref 08d8
    if (m.numAliens >= 9)
        return;

    m.alienShotDelta = -5; // from -4 to -5
}

// Prints a text message (msg, n) on the screen at pos
// Used to print all the splash screen text, and other game messages
static void PrintMessage(Word sc, uint8_t* msg, size_t n)
{
    // xref 08f3
    // DebugMessage(sc, msg, n);

    for (size_t i = 0; i < n; ++i)
    {
        uint8_t c = msg[i];
        sc = DrawChar(sc, c);
    }
}

// Draw a text character c on the screen at pos
// Used by PrintMessage()
static Word DrawChar(Word sc, uint8_t c)
{
    // xref 08ff
    SprDesc desc;
    desc.sc = sc;
    desc.spr = u16_to_word(0x1e00 + c*8);
    desc.n = 8;

    return DrawSimpSprite(&desc);
}

// Timing logic that controls when the saucer appears (Every 25.6 secs)
// Called via vblank_int()
static void TimeToSaucer()
{
    // xref 0913
    // No ticking until alien rack has dropped down a bit
    if (m.refAlienPos.y >= 120)
        return;

    uint16_t timer = m.saucerTimer.u16;

    if (timer == 0)
    {
        timer         = 0x600; // reset timer to 1536 game loops (25.6s)
        m.saucerStart = 1;
    }

    m.saucerTimer.u16 = timer - 1;
}

// Get number of lives for the current player
static uint8_t GetNumberOfShips(uint8_t* *ptr)
{
    // xref 092e
    *ptr = (GetPlayerDataPtr() + 0xff);
    return *(*ptr);
}

// Award the one and only bonus life if the player's score is high enough,
// and fix up the lives indicators to reflect that.
static void CheckAndHandleExtraShipAward()
{
    // xref 0935
    if (*(CurPlyAlive() - 2) == 0)
        return;

    // Bonus dip bit - award at 1000 or 1500
    uint8_t b = (read_port(2) & DIP6_BONUS) ? 0x10 : 0x15;
    uint8_t score_msb = *(GetScoreDescriptor() + 1);

    // score not high enough for bonus yet
    if (score_msb < b)
        return;

    uint8_t* nships_ptr;
    GetNumberOfShips(&nships_ptr);

    // Award the bonus life
    (*nships_ptr)++;

    int nships = *nships_ptr;

    SprDesc desc;
    desc.sc = xytosc(8 + 16 * nships, 8);
    desc.spr = ptr_to_word(m.PLAYER_SPRITES);
    desc.n = 16;

    DrawSimpSprite(&desc);

    PrintNumShips(nships+1);
    *(CurPlyAlive() - 2) = 0;    // Flag extra ship has been awarded
    m.extraHold = 0xff;          // Handle Extra-ship sound
    SoundBits3On(0x10);
}

// Lookup score for alien based on the given row
static uint8_t* AlienScoreValue(uint8_t row)
{
    // xref 097c
    uint8_t si = 0;

    if      (row < 2) si = 0;
    else if (row < 4) si = 1;
    else              si = 2;

    return  (m.AlienScores + si);
}

// Add the score delta to the current player's score, and draw it.
// Called as part of the game loop.
//
// scoreDelta is modified in two places:
//     PlayerShotHit() upon killing an alien    (main thread)
//     GameObj4()      upon hitting the saucer  (either vblank or mid depending on saucer x pos)
static void AdjustScore()
{
    // xref 0988
    uint8_t* sptr = GetScoreDescriptor();
    if (m.adjustScore == 0) return;

    m.adjustScore = 0;

    Word adj = m.scoreDelta;
    uint8_t carry = 0;

    Word score;

    score.l = *(sptr);
    score.l = bcd_add(score.l, adj.l, &carry);
    *sptr = score.l;

    score.h = *(sptr+1);
    score.h = bcd_add(score.h, adj.h, &carry);
    *(sptr+1) = score.h;

    Word sc;
    sc.l = *(sptr+2);
    sc.h = *(sptr+3);

    Print4Digits(sc, score);
}

// Print 4 digits using the bcd values in val.h and val.l
// Called via DrawScore and AdjustScore
static void Print4Digits(Word sc, Word val)
{
    // xref 09ad
    sc = DrawHexByte(sc, val.h);
    sc = DrawHexByte(sc, val.l);
}

// Draw the the hi and lo nibble of the bcd value in c at sc
static Word DrawHexByte(Word sc, uint8_t c)
{
    // xref 09b2
    sc = DrawHexByteSub(sc, c >> 4);
    sc = DrawHexByteSub(sc, c & 0xf);
    return sc;
}

// Draw the digit in c at sc
static Word DrawHexByteSub(Word sc, uint8_t c)
{
    // xref 09c5
    return DrawChar(sc, c + 0x1a);
}

// Return a pointer to the score info for the current player
static uint8_t* GetScoreDescriptor()
{
    // xref 09ca
    return (m.playerDataMSB & 0x1) ? &m.P1Scor.l : &m.P2Scor.l;
}

// Clear the play field in the center of the screen.
// Horizontally, the play field is the full width of the screen.
// Vertically, the play field is the area above the lives and credits (16 pixels)
// and below the scores (32 pixels).
static void ClearPlayField()
{
    // xref 09d6
    uint8_t* screen = m.vram;

    for (int x = 0; x < 224; ++x)
    {
        screen += 2;

        for (int b = 0; b < 26; ++b)
            *screen++ = 0;

        screen += 4;
    }
}

// Called from the game loop when the player has killed all aliens in the rack.
static void HandleEndOfTurn()
{
    // xref 09ef
    HandleEndOfTurnSub(); // wait for player to finish dying if necessary

    m.gameTasksRunning = 0;
    ClearPlayField();

    uint8_t pnum = m.playerDataMSB;

    CopyRAMMirror();

    m.playerDataMSB = pnum;
    pnum = m.playerDataMSB; // redundant load

    uint8_t rack_cnt = 0;

    uint8_t* rcptr = u16_to_ptr(pnum << 8 | 0xfe);
    rack_cnt = (*rcptr % 8) + 1;
    *rcptr = rack_cnt;

    // Starting Y coord for rack for new level
    uint8_t y = m.AlienStartTable[rack_cnt-1];

    uint8_t* refy = u16_to_ptr(pnum << 8 | 0xfc);
    uint8_t* refx = refy + 1;

    *refy = y;
    *refx = 56;

    if (!(pnum & 0x1))
    {
        m.soundPort5 = 0x21;  // start fleet with first sound
        DrawShieldP2();
        InitAliensP2();
    }
    else
    {
        DrawShieldP1();
        InitAliensP1();
    }
}

// Called at start of HandleEndOfTurnSub() to handle the
// case of the player dying at the end of turn.
// (i.e. last alien and player both kill each other)
static void HandleEndOfTurnSub()
{
    // xref 0a3c

    if (IsPlayerAlive())
    {
        m.isrDelay = 48; // wait up to 3/4 of a sec

        do
        {
            // xref 0a47
            timeslice(); // spin
            if (m.isrDelay == 0)
                return;

        } while (IsPlayerAlive());
    }

    // If player is not alive, wait for resurrection
    while (!IsPlayerAlive())
    {
        // xref 0a52
        timeslice(); // spin
    }
}

// Returns 1 if player is alive, 0 otherwise
static uint8_t IsPlayerAlive()
{
    // xref 0a59
    return m.playerAlive == 0xff;
}

// Called as part of the player bullet collision response in PlayerShotHit()
// when the player bullet kills an alien.
static void ScoreForAlien(uint8_t row)
{
    // xref 0a5f
    if (!m.gameMode)
        return;

    SoundBits3On(0x08);

    uint8_t score = *(AlienScoreValue(row));

    m.scoreDelta.h = 0;
    m.scoreDelta.l = score;
    m.adjustScore = 1;
}

// Companion routine to SplashSprite
// Called from the main thread to initiate and wait for splash animations (CCOIN / PLAy).
static void Animate()
{
    // xref 0a80
    // Directs ISRSplTasks() (in vblank_int()) to call SplashSprite()
    m.isrSplashTask = 2;

    // Spin until sprite in animation reaches its target position
    do {
        // xref 0a85
        write_port(6, 2); // feed watchdog and spin
    }
    while (!m.splashReached);

    // Directs ISRSplTasks() to do nothing
    m.isrSplashTask = 0;
}

// Prints the animated text messages (such as "PLAY" "SPACE INVADERS"),
// by drawing the characters that make up the message with a short
// delay between them. (7 frames per character)
static Word PrintMessageDel(Word sc, uint8_t* str, uint8_t n)
{
    // xref 0a93
    // DebugMessage(sc, str, n);

    for (int i = 0; i < n; ++i)
    {
        sc = DrawChar(sc, str[i]);
        m.isrDelay = 7;
        while (m.isrDelay != 1) { timeslice(); } // spin
    }

    return sc;
}

// Need for the shooting C in CCOIN animation.
// Initiated in AnimateShootingSplashAlien(), and called
// via ISRSplTasks() during vblank_int()
static void SplashSquiggly()
{
    // xref 0aab
    // this works because this is the last game object.
    RunGameObjs(u16_to_ptr(SQUIGGLY_SHOT_ADDR));
}

// Wait for approximately one second. (64 vblanks).
static void OneSecDelay()
{
    // xref 0ab1
    WaitOnDelay(64);
}

// Wait for approximately two seconds. (128 vblanks).
static void TwoSecDelay()
{
    // xref 0ab6
    WaitOnDelay(128);
}

// Runs the game objects in demo mode to attract players.
// Initiated from the main thread and called
// via ISRSplTasks() during vblank_int()
static void SplashDemo()
{
    // xref 0abb
    // xref 0072
    m.shotSync = m.rolShotHeader.TimerExtra;

    DrawAlien();
    RunGameObjs(u16_to_ptr(PLAYER_ADDR)); // incl player
    TimeToSaucer();
}

// Runs the appropriate splash screen task (from vblank_int())
static void ISRSplTasks()
{
    // xref 0abf
    switch (m.isrSplashTask)
    {
        case 1: SplashDemo(); break;         // Attract players with game demo
        case 2: SplashSprite(); break;       // Moves a sprite to a target location for an animation
        case 4: SplashSquiggly(); break;     // Run an alien shot for an animation ( CCOIN )
    }
}

// Print an animated message in the center of the screen.
static void MessageToCenterOfScreen(uint8_t* str)
{
    // xref 0acf
    PrintMessageDel(xytosc(56,160), str, 0x0f);
}

// Wait for n vblank interrupts to occur, using m.isrDelay
static void WaitOnDelay(uint8_t n)
{
    // xref 0ad7
    // Wait on ISR counter to reach 0
    m.isrDelay = n;

    while (m.isrDelay != 0)  { timeslice(); } // spin
}

// Copy src into the splash animation structure.
// The four animations copied this way are
//
// (for PLAy animation)
//
// 0x1a95 - Move alien left to grab y
// 0x1bb0 - Move alien (with y) to right edge
// 0x1fc9 - Bring alien back (with Y) to message
//
// (for CCOIN animation)
//
// 0x1fd5 - Move alien to point above extra 'C'
static void IniSplashAni(uint8_t* src)
{
    // xref 0ae2
    BlockCopy(&m.splashAnForm, src, 12);
}

// Called during (splash screens) to do some miscellaneous tasks
//   a) Player shot collision response
//   b) Detecting and handling the alien rack bumping the screen edges
//   c) Checking for TAITO COP input sequence
static uint8_t CheckPlyrShotAndBump()
{
    // xref 0bf1
    PlyrShotAndBump();
    CheckHiddenMes();
    return 0xff;
}

// Erases a sprite by clearing the four bytes it
// could possibly be in.
static void EraseSimpleSprite(Word pos, uint8_t n)
{
    // xref 1424
    Word sc = CnvtPixNumber(pos);

    for (int i = 0; i < n; ++i, sc.u16 += xysc(1, 0))
    {
        uint8_t* screen = word_to_ptr(sc);

        *screen++ = 0;
        *screen++ = 0;
    }
}

// Draws a non shifted sprite from desc->spr horizontally
// across the screen at desc->pos for desc->n bytes.
// Each byte of the sprite is a vertical 8 pixel strip
static Word DrawSimpSprite(SprDesc *desc)
{
    // xref 1439
    uint8_t* screen = word_to_ptr(desc->sc);
    uint8_t* sprite = word_to_ptr(desc->spr);

    for (size_t i = 0; i < desc->n; ++i, screen += xysc(1, 0))
        *screen = sprite[i];

    return ptr_to_word(screen);
}

// Using pixnum, set the shift count on the hardware shifter
// and return the screen coordinates for rendering
static Word CnvtPixNumber(Word pos)
{
    // xref 1474
    write_port(2, (pos.u16 & 0xff) & 0x07);
    return ConvToScr(pos);
}

// Draw a shifted sprite to the screen, blending with screen contents
static void DrawShiftedSprite(struct SprDesc *desc)
{
    // xref 1400
    DrawSpriteGeneric(desc, OP_BLEND);
}

// Erase a shifted sprite from the screen, zeroing screen contents
static void EraseShifted(struct SprDesc *desc)
{
    // xref 1452
    DrawSpriteGeneric(desc, OP_ERASE);
}

// Draw a shifted sprite to the screen, blending with screen contents,
// and detect if drawn sprite collided with existing pixels
static void DrawSprCollision(struct SprDesc *desc)
{
    // xref 1491
    DrawSpriteGeneric(desc, OP_COLLIDE);
}

// Draw a shifted sprite to the screen, overwriting screen contents.
static void DrawSprite(struct SprDesc *desc)
{
    // xref 15d3
    DrawSpriteGeneric(desc, OP_BLIT);
}

// Generic sprite drawing routine for shifted spries
//   desc->spr      - source pointer
//   desc->pixnum   - pixel position to draw at
//   desc->n        - width
//   op             - erase | blit | blend | collide
static void DrawSpriteGeneric(struct SprDesc *desc, int op)
{
    Word sc = CnvtPixNumber(desc->pos);
    uint8_t* sprite = word_to_ptr(desc->spr);

    if (op == OP_COLLIDE)
        m.collision = 0;

    for (int i = 0; i < desc->n; ++i, sc.u16 += xysc(1,0))
    {
        uint8_t* screen = word_to_ptr(sc);

        uint8_t shift_in[2];
        shift_in[0] = sprite[i];
        shift_in[1] = 0;

        for (int j = 0; j < 2; ++j)
        {
            write_port(4, shift_in[j]);             // write into shift reg
            uint8_t shifted = read_port(3);  // get the shifted pixels (shift based on pix num)

            if (op == OP_COLLIDE && (shifted & *screen))
                m.collision = 1;

            if (op == OP_COLLIDE || op == OP_BLEND)
                *screen = shifted | *screen;
            else if (op == OP_BLIT)
                *screen = shifted;
            else if (op == OP_ERASE)
                *screen = (shifted ^ 0xff) & *screen;

            screen++;
        }
    }
}

// Repeat (width n) the pixel strip in byte v horizontally across the screen
static Word ClearSmallSprite(Word sc, uint8_t n, uint8_t v)
{
    // xref 14cb
    for (int i = 0; i < n; ++i, sc.u16 += xysc(1,0))
        *(word_to_ptr(sc)) = v;

    return sc;
}

// Player bullet collision response
static void PlayerShotHit()
{
    // xref 14d8
    uint8_t status = m.plyrShotStatus;

    // if alien explosion state, bail
    if (status == 5)
        return;

    // if not normal movement, bail
    if (status != 2)
        return;

    // Get the Y coord
    uint8_t shoty = m.playerShotDesc.pos.y;

    if (shoty >= 216)
    {
        // missed and hit top of screen
        m.plyrShotStatus = 3;
        m.alienIsExploding = 0;
        SoundBits3Off(0xf7);
        return;
    }

    // xref 14ea
    if (!m.alienIsExploding)
        return;

    if (shoty >= 206)
    {
        // hit the saucer
        // xref 1579
        m.saucerHit = 1;
        m.plyrShotStatus = 4;

        // xref 154a
        m.alienIsExploding = 0;
        SoundBits3Off(0xf7);
        return;
    }

    shoty += 6;

    {
        uint8_t refy = m.refAlienPos.y;

        // refy can wrap around, if the topmost alien row gets near the bottom of the screen
        // in usual play, refy will be < 144.
        if ((refy < 144) && (refy >= shoty))
        {
            // hit the shields
            m.plyrShotStatus = 3;
            m.alienIsExploding = 0;
            SoundBits3Off(0xf7);
            return;
        }
    }

    // xref 1504
    // Get here if player shot hits an alien or an alien shot.
    // There is a subtle bug here, see CodeBug1 in CA
    Word res = FindRow(shoty);

    uint8_t row = res.h;
    uint8_t ay = res.l;

    res = FindColumn(m.playerShotDesc.pos.x);

    uint8_t col = res.h;
    uint8_t ax  = res.l;

    m.expAlien.pos = u8_u8_to_word(ax, ay);
    m.plyrShotStatus = 5;

    uint8_t* alienptr = GetAlienStatPtr(row, col);

    if (*alienptr == 0)
    {
        // If alien is dead, then the player shot must have hit an alien shot
        m.plyrShotStatus = 3;
        m.alienIsExploding = 0;
        SoundBits3Off(0xf7);
        return;
    }

    // Kill the alien
    *alienptr = 0;
    ScoreForAlien(row);
    SprDesc desc = ReadDesc(&m.expAlien);
    DrawSprite(&desc);
    m.expAlienTimer = 16;
}

// Counts the number of 16s between *v and target.
// This is roughly (tgt - *v) / 16.
static uint8_t Cnt16s(uint8_t *v, uint8_t tgt)
{
    // xref 1554
    uint8_t n = 0;

    if ((*v) >= tgt)
    {
        do
        {
            // wrap ref
            n++;
            (*v) += 16;

        } while ((*v) & 0x80);
    }

    while ((*v) < tgt)
    {
        (*v) += 16;
        n++;
    }

    return n;
}

// Find alien row given y pos
static Word FindRow(uint8_t y)
{
    // xref 1562
    uint8_t ry    = m.refAlienPos.y;
    uint8_t rnum  = Cnt16s(&ry, y) - 1;
    uint8_t coord = (ry - 16);

    return u8_u8_to_word(rnum, coord);
}

// Find alien column given x pos
static Word FindColumn(uint8_t x)
{
    // xref 156f
    uint8_t rx    = m.refAlienPos.x;
    uint8_t cnum  = Cnt16s(&rx, x);
    uint8_t coord = (rx - 16);

    return u8_u8_to_word(cnum, coord);
}

// Return a pointer to the alien status for the current player
// given the row and column of the alien
static uint8_t* GetAlienStatPtr(uint8_t row, uint8_t col)
{
    // xref 1581
    // row is 0 based
    // col is 1 based

    uint8_t idx = row * 11 + (col - 1);
    return u16_to_ptr(m.playerDataMSB << 8 | idx);
}

// Change alien deltaX and deltaY when alien rack bumps edges
static void RackBump()
{
    // xref 1597
    // Change alien deltaX and deltaY when rack bumps edges
    uint8_t dx = 0;
    uint8_t dir = 0;

    if (m.rackDirection == 0)
    {
        // xref 159e check right edge
        if (!RackBumpEdge(xytosc(213,32)))
            return;

        dx = -2;
        dir = 1;  // rack now moving left
    }
    else
    {
        // check left edge
        if (!RackBumpEdge(xytosc(9,32)))
            return;

        // rack now moving right
        // inline 18f1
        dx = m.numAliens == 1 ? 3 : 2;  // go faster if only one alien remaining
        dir = 0;                        // rack now moving right
    }

    m.rackDirection = dir;
    m.refAlienDelta.x = dx;
    m.refAlienDelta.y = m.rackDownDelta;
}

// Check 23 bytes vertically up from sc for pixels.
// Used by RackBump to detect whether alien rack is hitting the edges of the play area.
static uint8_t RackBumpEdge(Word sc)
{
    // xref 15c5
    uint8_t* screen = word_to_ptr(sc);

    for (int i = 0; i < 23; ++i)
    {
        timeslice();

        // found some pixels
        if (*screen++)
            return 1;
    }

    return 0;
}

// Count the number of live aliens for the current player
static void CountAliens()
{
    // xref 15f3
    uint8_t* iter = GetPlayerDataPtr(); // Get active player descriptor
    uint8_t n = 0;

    for (int i = 0; i < 55; ++i)
    {
        timeslice();

        if (*iter++ != 0)
            ++n;
    }

    m.numAliens = n;

    if (n != 1)
        return;

    // Apparently unused
    *(u16_to_ptr(0x206b)) = 1;
}

// Return a pointer the the current player's RAM area
static uint8_t* GetPlayerDataPtr()
{
    // xref 1611
    return u16_to_ptr(m.playerDataMSB << 8);
}

// Handles player firing in game and demo mode.
// In both cases, nothing happens if there is a shot on the screen.
// In game mode, reads the fire button and debounces to detect press.
// In demo mode, initiates a shot always, and consumes the next movement command from the buffer.
static void PlrFireOrDemo()
{
    // xref 1618
    if (m.playerAlive != 0xff)
        return;

    uint8_t timer_hi = m.playerHeader.TimerMSB;
    uint8_t timer_lo = m.playerHeader.TimerLSB;

    // Return if not ready yet.
    if (timer_lo | timer_hi)
        return;

    // Return if player has a shot still on screen
    if (m.plyrShotStatus)
        return;

    // xref 162b
    if (m.gameMode)
    {
        // Handle fire button reading and debouncing
        uint8_t prev = m.fireBounce;
        uint8_t cur  = (ReadInputs() & 0x10) != 0;

        if (prev == cur)
            return;

        if (cur)
            m.plyrShotStatus = 1;       // Flag shot active

        m.fireBounce = cur;
        return;
    }
    else
    {
        // Demo player constantly fires

        m.plyrShotStatus = 1;

        // Consume demo command from circular buffer 0x1f74 <-> 0x1f7e
        //
        //   DemoCommands:
        //; (1=Right, 2=Left)
        //      74 75 76 77 78 79 7A 7B 7C 7D 7E
        //1F74: 01 01 00 00 01 00 02 01 00 02 01

        Word iter = u16_to_word(m.demoCmdPtr.u16 + 1);

        if (iter.l >= 0x7e)
            iter.l = 0x74; // wrap

        m.demoCmdPtr = iter;
        m.nextDemoCmd = *(word_to_ptr(iter));
    }
}

// Called when all players are dead in game mode
// Prints "GAME OVER" and sets things up to reenter splash screens.
static void GameOver()
{
    // xref 16c9

    PrintMessageDel(xytosc(72,192), m.MSG_GAME_OVER__PLAYER___, 10);
    TwoSecDelay();
    ClearPlayField();
    m.gameMode = 0;
    write_port(5, 0);      // all sound off
    EnableGameTasks();
    main_init(1);
    assert(FALSE); // won't return
}

// Called when the player loses the game upon an alien reaching the bottom
static void on_invaded()
{
    // xref 16ea
    m.playerAlive = 0;

    do {
        PlayerShotHit();
        SoundBits3On(4);
    }
    while (!IsPlayerAlive());

    DsableGameTasks();
    DrawNumShipsSub(xytosc(24, 8)); // 19fa
    PrintNumShips(0);

    // xref 196b
    SoundBits3Off(0xfb);
    player_death(1);

    // won't return
    assert(FALSE);
}

// Increases the difficulty of the game as the player's score gets higher by
// decreasing time between alien shots.
static void AShotReloadRate()
{
    // xref 170e
    uint8_t score_hi = *(GetScoreDescriptor() + 1);

    // Uses these tables, in decimal
    //   02 16 32 48       (AReloadScoreTab)
    //   48 16 11 08 07    (ShotReloadRate)

    int i = 0;

    // xref 171c
    for (i = 0; i < 4; ++i)
    {
        if (m.AReloadScoreTab[i] >= score_hi)
            break;
    }

    // xref 1727
    m.aShotReloadRate = m.ShotReloadRate[i];
}

// Turn player shot sound on/off depending on m.plyrShotStatus
static void ShotSound()
{
    // xref 172c
    if (m.plyrShotStatus == 0)
    {
        SoundBits3Off(0xfd);
        return;
    }

    SoundBits3On(0x02);
}

// Ticks down and reset the timers that determines when the alien sound is changed.
// The sound is actually changed in FleetDelayExShip()
static void TimeFleetSound()
{
    // xref 1740
    if (--m.fleetSndHold == 0)
        DisableFleetSound();

    if (m.playerOK == 0)
    {
        DisableFleetSound();
        return;
    }

    if (--m.fleetSndCnt != 0)
        return;

    write_port(5, m.soundPort5);

    if (m.numAliens == 0)
    {
        DisableFleetSound();
        return;
    }

    m.fleetSndCnt = m.fleetSndReload;
    m.changeFleetSnd = 0x01;
    m.fleetSndHold = 0x04;
}

// Turn off the fleet movement sounds
static void DisableFleetSound()
{
    // xref 176d
    SetSoundWithoutFleet(m.soundPort5);
}

// Mask fleet movement sound off from given byte, and use it to set sound
static void SetSoundWithoutFleet(uint8_t v)
{
    // xref 1770
    write_port(5, v & 0x30);
}

// Handles rotating the fleet sounds if it is time to do so, and determines the
// delay between them using a table keyed by the number of live aliens.
// The bonus ship sound is also handled here.
static uint8_t FleetDelayExShip()
{
    // xref 1775
    // The two sound tables (in decimal):
    //   [ 50 43 36 28 22 17 13 10 08 07 06 05 04 03 02 01 ] (soundDelayKey)
    //   [ 52 46 39 34 28 24 21 19 16 14 13 12 11 09 07 05 ] (soundDelayValue)

    uint8_t snd_b = 0;
    uint8_t snd_a = 0;

    if (m.changeFleetSnd)
    {
        uint8_t n = m.numAliens;

        // xref 1785
        int i = 0;

        for (i = 0; i < 16; ++i)
        {
            if (n >= m.soundDelayKey[i])
                break;
        }

        m.fleetSndReload = m.soundDelayValue[i];

        snd_b = m.soundPort5 & 0x30; // Mask off all fleet movement sounds
        snd_a = m.soundPort5 & 0x0f; // Mask off all except fleet sounds

        // Rotate to next sound and wrap if neccessary
        snd_a = (snd_a << 1) | (snd_a >> 7);

        if (snd_a == 0x10)
            snd_a = 0x01;

        m.soundPort5 = snd_a | snd_b;
        m.changeFleetSnd = 0;
    }

    // xref 17aa
    if (--m.extraHold == 0)
        SoundBits3Off(0xef);

    return snd_a;
}

// Read the input port corresponding to the current player.
static uint8_t ReadInputs()
{
    // xref 17c0
    uint8_t port = m.playerDataMSB & 0x1 ? 1 : 2;
    return read_port(port);
}

// End the game if tilt switch is activated.
static void CheckHandleTilt()
{
    // xref 17cd
    if (!(read_port(2) & TILT_BIT)) return;
    if (m.tilt) return;

    yield(YIELD_TILT);
    assert(FALSE);
}

// This routine is entered after the stack reset in CheckHandleTilt
// It prints the tilt message and ends the game, cycling back to the splash screen.
static void on_tilt()
{
    // xref 17dc
    for (size_t i = 0; i < 4; ++i)
        ClearPlayField();

    m.tilt = 1;
    DsableGameTasks();
    enable_interrupts();

    PrintMessageDel(xytosc(96,176), m.MSG_TILT, 4);
    OneSecDelay();

    m.tilt = 0;
    m.waitStartLoop = 0;

    GameOver(); // does not return.
    assert(FALSE);
}

// Play appropriate sounds based on saucer state.
static void CtrlSaucerSound()
{
    // xref 1804
    if (m.saucerActive == 0)
    {
        SoundBits3Off(0xfe);
        return;
    }

    if (m.saucerHit)
        return;

    SoundBits3On(0x01);
}

// Draws the text and sprites for the "SCORE ADVANCE TABLE" in the splash screens.
static void DrawAdvTable()
{
    // xref 1815
    PrintMessage(xytosc(32,128), m.MSG__SCORE_ADVANCE_TABLE_, 0x15);

    // PrintMessageAdv uses this
    m.temp206C = 10;

    PriCursor cursor;

    // Sprite display list for score advance table
    cursor.src = m.SCORE_ADV_SPRITE_LIST;

    while (!ReadPriStruct(&cursor))
        Draw16ByteSprite(cursor.sc, cursor.obj);

    // Message display list for score advance table
    cursor.src = m.SCORE_ADV_MSG_LIST;

    while (!ReadPriStruct(&cursor))
        PrintMessageAdv(cursor.sc, cursor.obj);
}

// Used when drawing the Score Advance Table to draw the alien and saucer sprites
static void Draw16ByteSprite(Word sc, uint8_t* sprite)
{
    // xref 1844
    SprDesc desc;
    desc.sc = sc;
    desc.spr = ptr_to_word(sprite);
    desc.n = 16;

    DrawSimpSprite(&desc);
}

// Used when drawing the Score Advance Table to draw the text
static void PrintMessageAdv(Word sc, uint8_t* msg)
{
    // xref 184c
    size_t n = m.temp206C;
    PrintMessageDel(sc, msg, n);
}

// A PriStruct is a display list, containing a list of
// objects to display (either sprites or text), and their position.
// This routine is used to iterate through the list and read each member.
static int ReadPriStruct(PriCursor *pri)
{
    // xref 1856
    pri->sc.l = *pri->src++;

    if (pri->sc.l == 0xff)
        return TRUE; // hit end

    pri->sc.h = *pri->src++;

    Word obj;
    obj.l = *pri->src++;
    obj.h = *pri->src++;

    pri->obj = word_to_ptr(obj);

    return FALSE; // keep going
}

// Required for CCOIN and PLAy splash animations
// The animation structure used here is set up by IniSplashAni()
// Moves and animates a sprite until it reaches a target position
static void SplashSprite()
{
    // xref 1868
    ++m.splashAnForm;
    uint8_t* vptr = &m.splashDelta.y;

    uint8_t dy = *vptr;
    uint8_t x = AddDelta(vptr, dy);

    if (m.splashTargetX != x)
    {
        uint8_t flip = m.splashAnForm & 0x04;
        Word spr = m.splashImRest;

        if (flip == 0) { spr.u16 += 48; }

        m.splashPic = spr;

        SprDesc desc = ReadDesc((SprDesc*) u16_to_ptr(SPLASH_DESC_ADDR));

        // splash desc is out of order, needs swapping.
        Word tmp = desc.pos;

        desc.pos = desc.spr;
        desc.spr = tmp;

        DrawSprite(&desc);
        return;
    }

    // xref 1898
    m.splashReached = 1;
}

// Handles the shooting part of the CCOIN splash animation
// Companion routine is SplashSquiggly()
static void AnimateShootingSplashAlien()
{
    // xref 189e
    BlockCopy(u16_to_ptr(SQUIGGLY_SHOT_ADDR), m.SPLASH_SHOT_OBJDATA, 16);

    m.shotSync = 2;
    m.alienShotDelta = 0xff;
    m.isrSplashTask = 4;

    // spin until shot collides
    while ((m.squShotData.Status & SHOT_BLOWUP) == 0)
    {
        // xref 18b8
        timeslice(); // spin
    }

    // spin until shot explosion finishes
    while ((m.squShotData.Status & SHOT_BLOWUP) != 0)
    {
        // xref 18c0
        timeslice(); // spin
    }

    // replace extra 'C' with blank space
    DrawChar(xytosc(120,136), 0x26);

    TwoSecDelay();
}

// Handle initialization and splash screens.
// Initially entered upon startup via reset(), with skip=0
// Is is terminated when the stack is reset upon the insertion of credits, and is
// replaced by WaitForStart()
// The routine is eventually re-entered with skip=0 via GameOver()
static void main_init(int skip)
{
    // xref 18d4
    int init = !skip;

    if (init)
    {
        CopyRomtoRam();
        DrawStatus();
    }

    // 18df
    while (TRUE)
    {
        if (init)
        {
            m.aShotReloadRate = 8;

            write_port(3, 0); // turn off sound 1
            write_port(5, 0); // turn off sound 2

            // SetISRSplashTask
            m.isrSplashTask = 0;

            // xref 0af2
            enable_interrupts();

            OneSecDelay();

            // xref 0af6
            PrintMessageDel(xytosc(96, 184),
                            m.splashAnimate ? m.MSG_PLAY : m.MSG_PLAY2,
                            4);

            // xref 0b08
            MessageToCenterOfScreen(m.MSG_SPACE__INVADERS);

            // xref 0b0e
            OneSecDelay();
            DrawAdvTable();
            TwoSecDelay();

            // xref 0b17
            if (m.splashAnimate == 0)
            {
                // run script for alien twiddling with upside down 'Y'
                IniSplashAni(u16_to_ptr(0x1a95));
                Animate();
                IniSplashAni(u16_to_ptr(0x1bb0));
                Animate();

                OneSecDelay();

                IniSplashAni(u16_to_ptr(0x1fc9));
                Animate();

                OneSecDelay();

                ClearSmallSprite(xytosc(125, 184), 10, 0);
                TwoSecDelay();
            }

            // xref 0b4a
            ClearPlayField();

            if (m.p1ShipsRem == 0)
            {
                // xref 0b54
                m.p1ShipsRem = GetShipsPerCred();
                RemoveShip();
            }

            // xref 0b5d
            CopyRAMMirror();
            InitAliensP1();

            DrawShieldP1();
            RestoreShieldsP1();
            m.isrSplashTask = 1;

            DrawBottomLine();

            // xref 0b71

            do
            {
                PlrFireOrDemo();

                // xref 0b74
                // check player shot, and aliens bumping screen, also handle hidden message
                uint8_t a2 = CheckPlyrShotAndBump();

                // feed the watchdog
                write_port(6, a2);

            } while (IsPlayerAlive());

            // xref 0b7f
            m.plyrShotStatus = 0;

            // wait for demo player to finish exploding.
            while (! IsPlayerAlive() )
            {
                // xref 0b83
                timeslice(); // spin
            }
        }

        // xref 0b89
        m.isrSplashTask = 0;
        OneSecDelay();
        ClearPlayField();

        PrintMessage(xytosc(64,136), m.MSG_INSERT__COIN, 12);

        // draw extra 'C' for CCOIN
        if (m.splashAnimate == 0)
            DrawChar(xytosc(120,136), 2);

        PriCursor cursor;
        cursor.src = m.CREDIT_TABLE;

        ReadPriStruct(&cursor);
        PrintMessageAdv(cursor.sc, cursor.obj);

        // Only print coin info if DIP7 is set
        if ((read_port(2) & DIP7_COININFO) == 0)
        {
            cursor.src = m.CREDIT_TABLE_COINS;

            // xref 183a
            while (!ReadPriStruct(&cursor))
                PrintMessageAdv(cursor.sc, cursor.obj);
        }

        TwoSecDelay();

        // xref 0bc6
        if (m.splashAnimate == 0)
        {
            // xref 0bce
            // shoot C animation
            IniSplashAni(u16_to_ptr(0x1fd5));
            Animate();
            AnimateShootingSplashAlien();
        }

        // xref 0bda
        m.splashAnimate = !m.splashAnimate;
        ClearPlayField();
    }
}

// Return pointer to non current player's alive status
static uint8_t* GetOtherPlayerAliveFlag()
{
    // xref 18e7
    return  (m.playerDataMSB & 0x1 ? &m.playerStates.h : &m.playerStates.l);
}

// Use a mask to enable sounds on port 3
static void SoundBits3On(uint8_t mask)
{
    // xref 18fa
    uint8_t snd = m.soundPort3;
    snd |= mask;
    m.soundPort3 = snd;
    write_port(3, snd);
}

// Init all the aliens for P2
static void InitAliensP2()
{
    // xref 1904
    InitAliensSub(u16_to_ptr(P2_ADDR));
}

// Called from the main thread to do some miscellaneous tasks
// a) Player shot collision response
// b) Detecting and handling the alien rack bumping the screen edges
static void PlyrShotAndBump()
{
    // xref 190a
    PlayerShotHit();
    RackBump();
}

// Return pointer to current player's alive status
static uint8_t* CurPlyAlive()
{
    // xref 1910
    return  (m.playerDataMSB & 0x1 ? &m.playerStates.l : &m.playerStates.h);
}

// Draw the score text labels at the top of the screen
static void DrawScoreHead()
{
    // xref 191a
    PrintMessage(xytosc(0,240), m.MSG__SCORE_1__HI_SCORE_SCORE_2__, 28);
}

// Draw the score for P1
static void PrintP1Score()
{
    // xref 1925
    DrawScore(&m.P1Scor.l);
}

// Draw the score for P2
static void PrintP2Score()
{
    // xref 192b
    DrawScore(&m.P2Scor.l);
}

// Draw the score using the given descriptor in iter
static void DrawScore(uint8_t* iter)
{
    // xref 1931

    Word pos;
    Word val;

    val.l = *iter++;
    val.h = *iter++;
    pos.l = *iter++;
    pos.h = *iter++;

    Print4Digits(pos, val);
}

// Draw the credit text label at the bottom right
static void PrintCreditLabel()
{
    // xref 193c
    PrintMessage(xytosc(136,8), m.MSG_CREDIT_, 7);
}

// Draw the number of credits at the bottom right
static void DrawNumCredits()
{
    // xref 1947
    DrawHexByte(xytosc(192,8), m.numCoins);
}

// Draw the high score
static void PrintHiScore()
{
    // xref 1950
    DrawScore(&m.HiScor.l);
}

// Clear the screen and draw all the text surrounding the playfield
static void DrawStatus()
{
    // xref 1956
    ClearScreen();
    DrawScoreHead();

    PrintP1Score();
    PrintP2Score();

    PrintHiScore();

    PrintCreditLabel();
    DrawNumCredits();

    // Midway patched this out
    // PrintTaitoCorporation();
}

// Prints "* TAITO CORPORATION *" at the bottom of the screen
// This is a bit of dead code due to the patching out in DrawStatus()
static void PrintTaitoCorporation()
{
    // xref 198b
    PrintMessage(xytosc(32, 24), u16_to_ptr(0x19be), 0x13);
}

// Called during the game demo to check if player has entered the correct
// button combos to display the easter egg, "TAITO COP"
static void CheckHiddenMes()
{
    // xref 199a
    uint8_t a = 0;

    if (m.hidMessSeq == 0)
    {
        a = read_port(1);
        a &= 0x76;
        a -= 0x72;

        if (a)
            return;

        m.hidMessSeq = 1;
    }

    a = read_port(1);
    a &= 0x76;
    a -= 0x34;

    if (a)
        return;

    PrintMessage(xytosc(80,216), m.MSG_TAITO_COP, 9);
}

// Allow game related tasks in interrupt routines
static void EnableGameTasks()
{
    // xref 19d1
    m.gameTasksRunning = 1;
}

// Disallow game related tasks in interrupt routines
static void DsableGameTasks()
{
    // xref 19d7
    m.gameTasksRunning = 0;
}

// Use a mask to turn off sounds in port 3
static void SoundBits3Off(uint8_t mask)
{
    // xref 19dc
    uint8_t snd = m.soundPort3;
    snd &= mask;
    m.soundPort3 = snd;
    write_port(3, snd);
}

// Draw the sprites representing the number of lives (0 based) remaining at the bottom left
static void DrawNumShips(uint8_t n)
{
    // xref 19e6
    SprDesc desc;

    desc.sc = xytosc(24,8);
    desc.spr = ptr_to_word(m.PLAYER_SPRITES);
    desc.n = 16;

    for (int i = 0; i < n; ++i)
        desc.sc = DrawSimpSprite(&desc);

    DrawNumShipsSub(desc.sc);
}

// Clears the space to the right of the ship sprites (used to remove lives)
static void DrawNumShipsSub(Word pos)
{
    // xref 19fa
    // Clear up to x = 136 (start of credit label)

    do
    {
        pos = ClearSmallSprite(pos, 16, 0);
    } while ((pos.x != 0x35));
}

// Returns true if given obj is positioned on the half of screen that is not currently being drawn.
// Used to control which interrupt draws a particular game object.
// This prevents flicker.
static uint8_t CompXrToBeam(uint8_t* posaddr)
{
    // xref 1a06
    uint8_t b = m.vblankStatus;
    uint8_t a = *posaddr & XR_MID;

    return a == b;
}

// memcpy
static void BlockCopy(void *_dest, void *_src, size_t n)
{
    // xref 1a32

    uint8_t* dest = (uint8_t*) (_dest);
    uint8_t* src = (uint8_t*) (_src);

    for (size_t i = 0; i < n; ++i)
        *dest++ = *src++;
}

// Return a copy of a Sprite Descriptor from src
static SprDesc ReadDesc(SprDesc* src)
{
    // xref 1a3b
    SprDesc desc;
    desc.spr.l = src->spr.l;
    desc.spr.h = src->spr.h;

    desc.pos.l = src->pos.l;
    desc.pos.h = src->pos.h;

    desc.n = src->n;
    return desc;
}

// Convert a pixel pos to a screen address
// Pixel positions in memory are pre-offset by +32 pixels, meaning that when
// they are converted to a screen coordinate, 0x400 has already been added.
// Hence the or with 0x2000 below, instead of +0x2400
// See xpix()
static Word ConvToScr(Word pos)
{
    // xref 1a47
    return u16_to_word((pos.u16 >> 3) | 0x2000);
}

// bzero the 7168 bytes of vram
static void ClearScreen()
{
    // xref 1a5c
    uint8_t* screen = m.vram;
    size_t n = 7168;

    for (size_t i = 0; i < n; ++i)
        screen[i] = 0;
}

// CopyShields() subroutine.
//   cursor   - used to iterate through the screen and the player buffer
//   spr_size - contains the number of rows and bytes per row of the sprite
//   dir=0 - Copy a shield from the buffer to the screen
//   dir=1 - Copy a shield from the screen to the buffer
static void CopyShieldBuffer(ShieldBufferCursor *cursor, Word spr_size, uint8_t dir)
{
    // xref 1a69
    uint8_t nr = spr_size.h;
    uint8_t nb = spr_size.l;

    for (int i = 0; i < nr; ++i, cursor->sc.u16 += xysc(1,0))
    {
        uint8_t* screen = word_to_ptr(cursor->sc);

        for (int j = 0; j < nb; ++j)
        {
            if (dir == 0)
                *screen = *cursor->iter | *screen;
            else
                *cursor->iter = *screen;

            cursor->iter++;
            screen++;
        }
    }
}

// Take a life away from the player, and update the indicators
static void RemoveShip()
{
    // xref 1a7f
    uint8_t* nships_ptr;
    uint8_t num = GetNumberOfShips(&nships_ptr);

    if (num == 0)
        return;

    *nships_ptr = num-1;

    // The sprite indicator is 0 based.
    DrawNumShips(num-1);

    // The text indicator is 1 based.
    DrawHexByteSub(xytosc(8,8), num & 0xf);
}

// Print the numeric lives indicator at the bottom left
static void PrintNumShips(uint8_t num)
{
    // xref 1a8b
    DrawChar(xytosc(8,8), (num & 0x0f) + 0x1a);
}

// GAMECODE FINISH
