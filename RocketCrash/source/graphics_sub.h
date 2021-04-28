#include <nds.h>
#include <stdio.h>
#include <fat.h>

#include "defines.h"
#include "storage.h"

#include "menu_sub.h"
#include "play_sub.h"
#include "pause_sub.h"
#include "over_sub.h"
#include "stats_sub.h"
#include "tiles_sub.h"


//*****************************************************************************
//******************************** POINTERS ***********************************
//*****************************************************************************

u16* bg0MemorySub;



//*****************************************************************************
//*********************** SUB ENGINE CONFIGURATIONS ***************************
//*****************************************************************************

/*
 * VOID CONFIGGRAPHICS_SUB(INT STATE)
 * This function configures the graphics for the SUB engine. The input, state,
 * determines which backgrounds are used. It configures the SUB engine in
 * mode 3 with the backgrounds 3 and 0, configures the VRAM bank C and
 * configures the correct backgrounds.
 */
void configGraphics_Sub(int state);



//*****************************************************************************
//********************** SUB BACKGROUND CONFIGURATIONS ************************
//*****************************************************************************

/*
 * VOID CONFIGBG0_SUB()
 * This function configures the main background 0 in tile mode using a 32x32
 * map. It copies the tiles and the palette found in "tiles_sub" in a 16 color
 * palette. It also creates an additional four palettes to modify the high
 * scores.
 */
void configBG0_Sub();

/*
 * VOID CONFIGBG3_SUB(INT STATE)
 * This function configures the sub background 0 in extended rotoscale mode
 * using 8 bit pixels and a 256x256 image. It copies the tiles and the palette
 * found in the appropriate image according to the input, state.
 */
void configBG3_Sub(int state);



//*****************************************************************************
//************************* SUB BACKGROUND FUNCTIONS **************************
//*****************************************************************************

/*
 * VOID CLEARBG0_SUB()
 * This function clears bg0 by filling it with empty tiles.
 */
void clearBG0_Sub();

/*
 * VOID SHOWPOWER_SUB()
 * This function displays tiles showimg the current power in the correct
 * position according to the input, power.
 */
void showPower_Sub(int power);

/*
 * VOID SHOWSELECTOR_SUB()
 * This function displays tiles showing the selector in the appropriate position
 * and mode according to the inputs.
 */
void showSelector_Sub(int pos, int mode);

/*
 * VOID SHOWSCORE_SUB(INT NUMBER)
 * This function displays the input, number, on the sub screen in the correct
 * position.
 */
void showScore_Sub(int number);

/*
 * VOID SHOWHIGHSCORES_SUB()
 * This function displays the four high scores in the correct position on the
 * sub screen. It uses four different palettes corresponding to podium colors,
 * and blue for the fourth.
 */
void showHighScores_Sub();
