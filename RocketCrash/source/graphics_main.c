#include "graphics_main.h"

//*****************************************************************************
//*********************** MAIN ENGINE CONFIGURATION ***************************
//*****************************************************************************

void configGraphics_Main(int state) {
	//Configure the MAIN engine in mode 3 activating correct backgrounds
	if (state == PLAY)
		REG_DISPCNT = MODE_3_2D | DISPLAY_BG1_ACTIVE | DISPLAY_BG0_ACTIVE;
	else
		REG_DISPCNT = MODE_3_2D | DISPLAY_BG3_ACTIVE | DISPLAY_BG0_ACTIVE;

	//Configure the VRAM bank A
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

	//Configure correct background(s)
	if (state == PLAY)
	configBG1_Main();
	else
	configBG3_Main(state);
	configBG0_Main();
}


//*****************************************************************************
//************************ BACKGROUND CONFIGURATION ***************************
//*****************************************************************************

void configBG0_Main() {
	//Configure BG 0 to tile mode
	BGCTRL[0] = BG_32x32 | BG_COLOR_16 | BG_MAP_BASE(25) | BG_TILE_BASE(5);

	//Copy tiles and palette
	dmaCopy(tiles_mainTiles, BG_TILE_RAM(5), tiles_mainTilesLen);
	dmaCopy(tiles_mainPal, &BG_PALETTE[PAL9], tiles_mainPalLen);

	//Set pointer
	bg0MemoryMain = (u16*) BG_MAP_RAM(25);

	//Clear background
	clearBG0_Main();
}

void configBG1_Main() {
	//Configure background 0 to tile mode using 32x64 map
	BGCTRL[1] = BG_32x64 | BG_COLOR_16 | BG_MAP_BASE(27) | BG_TILE_BASE(6);

	//Copy tiles and palette to the corresponding place
	dmaCopy(sky_mainTiles, BG_TILE_RAM(6), sky_mainTilesLen);
	dmaCopy(sky_mainPal, BG_PALETTE, sky_mainPalLen);

	//Copy map to the map base(s): As the used map is 2 times a standard one,
	//we will need 2 map bases (i.e. 32x64 components * 16 bits = 4 KB)
	int i;

	//TOP half of the image in first map base
	for (i = 0; i < 32; i++)
		dmaCopy(&sky_mainMap[i * 32], &BG_MAP_RAM(27)[i * 32], 64);

	//BOTTOM half of the image in second map base
	for (i = 0; i < 32; i++)
		dmaCopy(&sky_mainMap[(i + 32) * 32], &BG_MAP_RAM(28)[i * 32], 64);
}

void configBG3_Main(int state) {
	// Configure background BG3 in extended rotoscale
	BGCTRL[3] = BG_BMP_BASE(0) | BG_BMP8_256x256;

	// Set up affine matrix
	REG_BG3PA = SCREEN_WIDTH;
	REG_BG3PC = 0;
	REG_BG3PB = 0;
	REG_BG3PD = SCREEN_WIDTH;

	//Copy to memory according to state
	if (state == MENU) {
		swiCopy(menu_mainPal, BG_PALETTE, menu_mainPalLen / 2);
		swiCopy(menu_mainBitmap, BG_GFX, menu_mainBitmapLen / 2);
	} else if (state == PAUSE) {
		swiCopy(pause_mainPal, BG_PALETTE, pause_mainPalLen / 2);
		swiCopy(pause_mainBitmap, BG_GFX, pause_mainBitmapLen / 2);
	} else if (state == OVER) {
		swiCopy(over_mainPal, BG_PALETTE, over_mainPalLen / 2);
		swiCopy(over_mainBitmap, BG_GFX, over_mainBitmapLen / 2);
	} else if (state == STATS) {
		swiCopy(stats_mainPal, BG_PALETTE, stats_mainPalLen / 2);
		swiCopy(stats_mainBitmap, BG_GFX, stats_mainBitmapLen / 2);
	} else {
		swiCopy(empty_mainPal, BG_PALETTE, empty_mainPalLen / 2);
		swiCopy(empty_mainBitmap, BG_GFX, empty_mainBitmapLen / 2);
	}
}


//*****************************************************************************
//************************ MAIN BACKGROUND FUNCTIONS **************************
//*****************************************************************************

void clearBG0_Main() {
	int tile = 32 * 32;
	//Fill BG0 with empty tile
	while (tile--)
		bg0MemoryMain[tile] = tiles_mainMap[1] | TILE_PALETTE(9);
}

void updateBG0_Main(int count) {
	//Update Obstacle Grid
	updateObstacleGrid_Main(count);

	int i, j;

	for (i = 0; i < SCREEN_HEIGHT_TILE; i++) {
		for (j = 0; j < SCREEN_WIDTH_TILE; j++) {
			if (obstacles[i * SCREEN_WIDTH_TILE + j] == 4) {
				bg0MemoryMain[i * SCREEN_WIDTH_TILE + j]
								        = tiles_mainMap[23] | TILE_PALETTE(9);
			} else if (obstacles[i * SCREEN_WIDTH_TILE + j] == 3) {
				bg0MemoryMain[i * SCREEN_WIDTH_TILE + j]
										= tiles_mainMap[44] | TILE_PALETTE(9);
			} else if (obstacles[i * SCREEN_WIDTH_TILE + j] == 2) {
				bg0MemoryMain[i * SCREEN_WIDTH_TILE + j]
										= tiles_mainMap[22] | TILE_PALETTE(9);
			} else if (obstacles[i * SCREEN_WIDTH_TILE + j] == 1) {
				bg0MemoryMain[i * SCREEN_WIDTH_TILE + j]
										= tiles_mainMap[0] | TILE_PALETTE(9);
			} else {
				bg0MemoryMain[i * SCREEN_WIDTH_TILE + j]
										= tiles_mainMap[1] | TILE_PALETTE(9);
			}
		}
	}
}

void initObstacleGrid_Main() {
	int i, j;
	//Initialize empty obstacle grid
	for (i = 0; i < SCREEN_HEIGHT_TILE; i++)
		for (j = 0; j < SCREEN_WIDTH_TILE; j++)
			obstacles[i * SCREEN_WIDTH_TILE + j] = 0;
}

void updateObstacleGrid_Main(int count) {
	int i, j, k;
	int tempGrid[SCREEN_WIDTH_TILE * SCREEN_HEIGHT_TILE];
	int r = (1 + rand() % (OBSTACLE_WIDTH - 1));

	//Store current grid in a temporary grid
	for (i = 0; i < SCREEN_HEIGHT_TILE; i++)
		for (j = 0; j < SCREEN_WIDTH_TILE; j++)
			tempGrid[i * SCREEN_WIDTH_TILE + j]
			         = obstacles[i * SCREEN_WIDTH_TILE + j];

	//New updated map
	for (i = 0; i < SCREEN_HEIGHT_TILE; i++) {
		for (j = 0; j < SCREEN_WIDTH_TILE; j += 4) {
			if (i == 0) {
				if (count == -1) {
					for (k = 0; k < 4; k++)
						obstacles[i * SCREEN_WIDTH_TILE + j + k] = 4;
				} else if (count % 11 == 0) {
					if (j/4 == r) {
						for (k = -4; k < 4; k++)
							obstacles[i * SCREEN_WIDTH_TILE + j + k] = 0;
					} else {
						obstacles[i * SCREEN_WIDTH_TILE + j] = 1;
						obstacles[i * SCREEN_WIDTH_TILE + j + 1] = 2;
						obstacles[i * SCREEN_WIDTH_TILE + j + 2] = 2;
						obstacles[i * SCREEN_WIDTH_TILE + j + 3] = 3;
					}
				} else {
					for (k = 0; k < 4; k ++)
						obstacles[i * SCREEN_WIDTH_TILE + j + k] = 0;
				}
			} else {
				for (k = 0; k < 4; k++)
					obstacles[i * SCREEN_WIDTH_TILE + j + k]
					              = tempGrid[(i-1) * SCREEN_WIDTH_TILE + j + k];
			}
		}
	}
}

void showScore_Main(int score) {
	int j, i, number;

	//i, digit to display
	for (i = NUM_DIGITS; i > 0; i--) {
		//calculate the power of i-1 in j
		j = i - 1;
		number = 1;
		while (j--)
			number = number * 10;

		//Obtain the number to render
		number = score / number;
		number = number % 10;

		//Render the number
		bg0MemoryMain[(SCORE_X_MAIN - 2 * i) + SCORE_Y_MAIN * SCREEN_WIDTH_TILE]
				= tiles_mainMap[(10 - number) * 2] | TILE_PALETTE(9);

		bg0MemoryMain[(SCORE_X_MAIN - 2 * i) + SCORE_Y_MAIN * SCREEN_WIDTH_TILE
				+ 1] = tiles_mainMap[(10 - number) * 2 + 1] | TILE_PALETTE(9);

		bg0MemoryMain[(SCORE_X_MAIN - 2 * i) + (SCORE_Y_MAIN + 1)
				* SCREEN_WIDTH_TILE] = tiles_mainMap[TILES_WIDTH
				+ (10 - number) * 2] | TILE_PALETTE(9);

		bg0MemoryMain[(SCORE_X_MAIN - 2 * i) + (SCORE_Y_MAIN + 1)
				* SCREEN_WIDTH_TILE + 1] = tiles_mainMap[TILES_WIDTH + (10
				- number) * 2 + 1] | TILE_PALETTE(9);

		bg0MemoryMain[(SCORE_X_MAIN - 2 * i) + (SCORE_Y_MAIN + 2)
				* SCREEN_WIDTH_TILE] = tiles_mainMap[2 * TILES_WIDTH + (10
				- number) * 2] | TILE_PALETTE(9);

		bg0MemoryMain[(SCORE_X_MAIN - 2 * i) + (SCORE_Y_MAIN + 2)
				* SCREEN_WIDTH_TILE + 1] = tiles_mainMap[2 * TILES_WIDTH + (10
				- number) * 2 + 1] | TILE_PALETTE(9);
	}
}

void hideTitle_Main() {
	int i, j;
	//Fill area with blue tile (BG0)
	for (i = TITLE_Y0; i < TITLE_Y1; i++)
		for (j = TITLE_X0; j < TITLE_X1; j++)
			bg0MemoryMain[i * SCREEN_WIDTH_TILE + j] = tiles_mainMap[45]
					| TILE_PALETTE(9);
}

void showTitle_Main() {
	int i, j;
	//Fill area with empty tile (BG0)
	for (i = TITLE_Y0; i < TITLE_Y1; i++)
		for (j = TITLE_X0; j < TITLE_X1; j++)
			bg0MemoryMain[i * SCREEN_WIDTH_TILE + j] = tiles_mainMap[1]
					| TILE_PALETTE(9);
}


//*****************************************************************************
//*************************** SPRITE CONFIGURATION ****************************
//*****************************************************************************

void configSprites_Main() {
	//Set up memory bank to work in sprite mode (offset since we are using VRAM A for backgrounds)
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;

	//Initialize sprite manager and the engine
	oamInit(&oamMain, SpriteMapping_1D_32, false);

	//Allocate space for the graphic to show in the sprite
	gfxRocket = oamAllocateGfx(&oamMain, SpriteSize_16x16,
			SpriteColorFormat_16Color);
	gfxCube0 = oamAllocateGfx(&oamMain, SpriteSize_16x16,
			SpriteColorFormat_16Color);
	gfxCube1 = oamAllocateGfx(&oamMain, SpriteSize_16x16,
			SpriteColorFormat_16Color);
	gfxCube2 = oamAllocateGfx(&oamMain, SpriteSize_16x16,
			SpriteColorFormat_16Color);
	gfxCube3 = oamAllocateGfx(&oamMain, SpriteSize_16x16,
			SpriteColorFormat_16Color);
	gfxCube4 = oamAllocateGfx(&oamMain, SpriteSize_16x16,
			SpriteColorFormat_16Color);

	//Copy data for the graphic (palette and bitmap)
	swiCopy(rocketPal, SPRITE_PALETTE, rocketPalLen / 2);
	swiCopy(rocketTiles, gfxRocket, rocketTilesLen / 2);

	swiCopy(cube0Pal, &SPRITE_PALETTE[rocketPalLen / 2], cube0PalLen / 2);
	swiCopy(cube0Tiles, gfxCube0, cube0TilesLen / 2);

	swiCopy(cube1Pal, &SPRITE_PALETTE[(rocketPalLen + cube0PalLen) / 2],
			cube1PalLen / 2);
	swiCopy(cube1Tiles, gfxCube1, cube1TilesLen / 2);

	swiCopy(cube2Pal, &SPRITE_PALETTE[(rocketPalLen + cube0PalLen
			+ cube1PalLen) / 2], cube2PalLen / 2);
	swiCopy(cube2Tiles, gfxCube2, cube2TilesLen / 2);

	swiCopy(cube3Pal, &SPRITE_PALETTE[(rocketPalLen + cube0PalLen + cube1PalLen
			+ cube2PalLen) / 2], cube3PalLen / 2);
	swiCopy(cube3Tiles, gfxCube3, cube3TilesLen / 2);

	swiCopy(cube4Pal, &SPRITE_PALETTE[(rocketPalLen + cube0PalLen + cube1PalLen
			+ cube2PalLen + cube3PalLen) / 2], cube4PalLen / 2);
	swiCopy(cube4Tiles, gfxCube4, cube4TilesLen / 2);
}


//*****************************************************************************
//***************************** SPRITE FUNCTIONS ******************************
//*****************************************************************************

void updateSpriteRocket_Main(int x, int y, bool h_flip) {
	oamSet(&oamMain, 					// oam handler
			0, 							// Number of sprite
			x, y,						// Coordinates
			0, 							// Priority
			0, 							// Palette to use
			SpriteSize_16x16, 			// Sprite size
			SpriteColorFormat_16Color, 	// Color format
			gfxRocket, 					// Loaded graphic to display
			-1, 						// Affine rotation to use (-1 none)
			false, 						// Double size if rotating
			false, 						// Hide this sprite
			h_flip, false, 				// Horizontal or vertical flip
			false 						// Mosaic
	);

	swiWaitForVBlank();

	//Update the sprites
	oamUpdate(&oamMain);
}

void updateSpriteCube_Main(int x, int y, int c) {
	if (c == INV || c == NONE) {
		oamSet(&oamMain, 					// oam handler
				1, 							// Number of sprite
				x, y,						// Coordinates
				0, 							// Priority
				1, 							// Palette to use
				SpriteSize_16x16, 			// Sprite size
				SpriteColorFormat_16Color, 	// Color format
				gfxCube0, 					// Loaded graphic to display
				-1, 						// Affine rotation to use (-1 none)
				false, 						// Double size if rotating
				false, 						// Hide this sprite
				false, false, 				// Horizontal or vertical flip
				false 						// Mosaic
		);
	} else if (c == WALL || c == NONE) {
		oamSet(&oamMain, 					// oam handler
				2, 							// Number of sprite
				x, y,						// Coordinates
				0, 							// Priority
				2, 							// Palette to use
				SpriteSize_16x16, 			// Sprite size
				SpriteColorFormat_16Color, 	// Color format
				gfxCube1, 					// Loaded graphic to display
				-1, 						// Affine rotation to use (-1 none)
				false, 						// Double size if rotating
				false, 						// Hide this sprite
				false, false, 				// Horizontal or vertical flip
				false 						// Mosaic
		);
	} else if (c == MUL || c == NONE) {
		oamSet(&oamMain, 					// oam handler
				3, 							// Number of sprite
				x, y,						// Coordinates
				0, 							// Priority
				3, 							// Palette to use
				SpriteSize_16x16, 			// Sprite size
				SpriteColorFormat_16Color, 	// Color format
				gfxCube2, 					// Loaded graphic to display
				-1, 						// Affine rotation to use (-1 none)
				false, 						// Double size if rotating
				false, 						// Hide this sprite
				false, false, 				// Horizontal or vertical flip
				false 						// Mosaic
		);
	} else if (c == DIV || c == NONE) {
		oamSet(&oamMain, 					// oam handler
				4, 							// Number of sprite
				x, y,						// Coordinates
				0, 							// Priority
				4, 							// Palette to use
				SpriteSize_16x16, 			// Sprite size
				SpriteColorFormat_16Color, 	// Color format
				gfxCube3, 					// Loaded graphic to display
				-1, 						// Affine rotation to use (-1 none)
				false, 						// Double size if rotating
				false, 						// Hide this sprite
				false, false, 				// Horizontal or vertical flip
				false 						// Mosaic
		);
	} else if (c == BOM || c == NONE) {
		oamSet(&oamMain, 					// oam handler
				5, 							// Number of sprite
				x, y,						// Coordinates
				0, 							// Priority
				5, 							// Palette to use
				SpriteSize_16x16, 			// Sprite size
				SpriteColorFormat_16Color, 	// Color format
				gfxCube4, 					// Loaded graphic to display
				-1, 						// Affine rotation to use (-1 none)
				false, 						// Double size if rotating
				false, 						// Hide this sprite
				false, false, 				// Horizontal or vertical flip
				false 						// Mosaic
		);
	}

	swiWaitForVBlank();

	//Update the sprites
	oamUpdate(&oamMain);
}

