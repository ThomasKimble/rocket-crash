#include <nds.h>
#include <stdio.h>

#include "defines.h"

#include "sky_main.h"
#include "menu_main.h"
#include "pause_main.h"
#include "over_main.h"
#include "stats_main.h"
#include "empty_main.h"
#include "tiles_main.h"

#include "rocket.h"
#include "cube0.h"
#include "cube1.h"
#include "cube2.h"
#include "cube3.h"
#include "cube4.h"


//*****************************************************************************
//******************* POINTERS AND MAIN ENGINE VARIABLES **********************
//*****************************************************************************

u16* bg0MemoryMain;
u16* gfxRocket;
u16* gfxCube0;
u16* gfxCube1;
u16* gfxCube2;
u16* gfxCube3;
u16* gfxCube4;

int obstacles[SCREEN_WIDTH_TILE*SCREEN_HEIGHT_TILE];



//*****************************************************************************
//*********************** MAIN ENGINE CONFIGURATIONS **************************
//*****************************************************************************

/*
 * VOID CONFIGGRAPHICS_MAIN(INT STATE)
 * This function configures the graphics for the MAIN engine. The input, state,
 * determines which backgrounds are used. It configures the MAIN engine in
 * mode 3 with the appropriate backgrounds, configures the VRAM bank A and
 * configures the correct backgrounds.
 */
void configGraphics_Main(int state);



//*****************************************************************************
//********************* MAIN BACKGROUND CONFIGURATIONS ************************
//*****************************************************************************

/*
 * VOID CONFIGBG0_MAIN()
 * This function configures the main background 0 in tile mode using a 32x32
 * map. It copies the tiles and the palette found in "tiles_main" in a 16 color
 * palette.
 */
void configBG0_Main();

/*
 * VOID CONFIGBG0_MAIN()
 * This function configures the main background 0 in tile mode using a 32x64
 * map. It copies the tiles and the palette found in "sky_main" in a 16 color
 * palette.
 */
void configBG1_Main();

/*
 * VOID CONFIGBG3_MAIN(INT STATE)
 * This function configures the main background 0 in extended rotoscale mode
 * using 8 bit pixels and a 256x256 image. It copies the tiles and the palette
 * found in the appropriate image according to the input, state.
 */
void configBG3_Main(int state);



//*****************************************************************************
//*************************** BACKGROUND FUNCTIONS ****************************
//*****************************************************************************

/*
 * VOID CLEARBG0_MAIN()
 * This function clears bg0 by filling it with empty tiles.
 */
void clearBG0_Main();

/*
 * VOID UPDATEBG0_MAIN()
 * This function updates the map in bg0 with the obstacles using the
 * appropriate tiles and palette. It uses the updated obstacles[] array.
 */
void updateBG0_Main(int count);

/*
 * VOID INITOBSTACLEGRID_MAIN()
 * This function initializes the obstacles[] array by filling it with zeros
 */
void initObstacleGrid_Main();

/*
 * VOID UPDATEOBSTACLEGRID_MAIN(INT COUNT)
 * This function updates the obstacles[] array by filling it with the correct
 * values to be passed the map. The input, count, decides weather obstacles
 * are created or not.
 */
void updateObstacleGrid_Main(int count);

/*
 * VOID SHOWSCORE_MAIN(INT NUMBER)
 * This function displays the input, number, on the main screen in the correct
 * position.
 */
void showScore_Main(int number);

/*
 * VOID HIDETITLE_MAIN()
 * This function hides the title of states PAUSE and OVER by creating a blue
 * rectangle from tiles.
 */
void hideTitle_Main();

/*
 * VOID SHOWTITLE_MAIN()
 * This function shows the title of states PAUSE and OVER by filling the map
 * with empty tiles.
 */
void showTitle_Main();



//*****************************************************************************
//*************************** SPRITE CONFIGURATION ****************************
//*****************************************************************************

/*
 * VOID CONFIGSPRITES_MAIN()
 * This function configures the rocket and cubes sprites. It configures the
 * VRAM B bank and copies them to the memory. A unique palette of 16 colors is
 * used for each sprite.
 */
void configSprites_Main();



//*****************************************************************************
//***************************** SPRITE FUNCTIONS ******************************
//*****************************************************************************

/*
 * VOID UPDATESPRITEROCKET_MAIN()
 * This function updates the position and configuration of the rocket sprite.
 */
void updateSpriteRocket_Main(int x, int y, bool h_flip);

/*
 * VOID UPDATESPRITECUBE_MAIN()
 * This function updates the position and configuration of the cube sprites.
 */
void updateSpriteCube_Main(int x, int y, int cube);
