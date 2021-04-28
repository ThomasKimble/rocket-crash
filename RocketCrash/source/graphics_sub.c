#include "graphics_sub.h"

//*****************************************************************************
//*********************** SUB ENGINE CONFIGURATIONS ***************************
//*****************************************************************************

void configGraphics_Sub(int state) {
	//Activate and configure VRAM  C bank
	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

	//Activate main engine and backgrounds 3 and 0
	REG_DISPCNT_SUB = MODE_3_2D | DISPLAY_BG3_ACTIVE | DISPLAY_BG0_ACTIVE;

	//Configure backgrounds 3 and 0
	configBG3_Sub(state);
	configBG0_Sub();
}


//*****************************************************************************
//********************** SUB BACKGROUND CONFIGURATIONS ************************
//*****************************************************************************

void configBG0_Sub() {
	//Configure the Background
	BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_16 | BG_MAP_BASE(24) | BG_TILE_BASE(4);

	//Copy tiles and palette
	dmaCopy(tiles_subTiles, BG_TILE_RAM_SUB(4), tiles_subTilesLen);
	dmaCopy(tiles_subPal, &BG_PALETTE_SUB[PAL8], tiles_subPalLen);

	//Create new palettes (For highscores)
	BG_PALETTE_SUB[PAL10 + HS_NUM] = GOLD;
	BG_PALETTE_SUB[PAL11 + HS_NUM] = SILVER;
	BG_PALETTE_SUB[PAL12 + HS_NUM] = BRONZE;
	BG_PALETTE_SUB[PAL13 + HS_NUM] = BLUE;

	//Set pointer
	bg0MemorySub = (u16*) BG_MAP_RAM_SUB(24);

	//Clear background 0
	clearBG0_Sub();
}

void configBG3_Sub(int state) {
	//Configure BG 3 Sub
	BGCTRL_SUB[3] = BG_BMP_BASE(0) | BgSize_B8_256x256;

	//Affine Marix Transformation
	REG_BG3PA_SUB = SCREEN_WIDTH;
	REG_BG3PC_SUB = 0;
	REG_BG3PB_SUB = 0;
	REG_BG3PD_SUB = SCREEN_WIDTH;

	//Copy to memory according to state
	if (state == MENU) {
		swiCopy(menu_subPal, BG_PALETTE_SUB, menu_subPalLen / 2);
		swiCopy(menu_subBitmap, BG_GFX_SUB, menu_subBitmapLen / 2);
	} else if (state == PLAY) {
		swiCopy(play_subPal, BG_PALETTE_SUB, play_subPalLen / 2);
		swiCopy(play_subBitmap, BG_GFX_SUB, play_subBitmapLen / 2);
	} else if (state == PAUSE) {
		swiCopy(pause_subPal, BG_PALETTE_SUB, pause_subPalLen / 2);
		swiCopy(pause_subBitmap, BG_GFX_SUB, pause_subBitmapLen / 2);
	} else if (state == OVER) {
		swiCopy(over_subPal, BG_PALETTE_SUB, over_subPalLen / 2);
		swiCopy(over_subBitmap, BG_GFX_SUB, over_subBitmapLen / 2);
	} else if (state == STATS) {
		swiCopy(stats_subPal, BG_PALETTE_SUB, stats_subPalLen / 2);
		swiCopy(stats_subBitmap, BG_GFX_SUB, stats_subBitmapLen / 2);
	}
}


//*****************************************************************************
//************************* SUB BACKGROUND FUNCTIONS **************************
//*****************************************************************************

void clearBG0_Sub() {
	int tile = 32 * 32;
	while (tile--)
		bg0MemorySub[tile] = tiles_subMap[44];
}

void showPower_Sub(int power) {
	bg0MemorySub[POWER_SUB_Y * SCREEN_WIDTH_TILE + POWER_SUB_X]
			= tiles_subMap[66 + 2 * power] | TILE_PALETTE(8);

	bg0MemorySub[POWER_SUB_Y * SCREEN_WIDTH_TILE + POWER_SUB_X + 1]
			= tiles_subMap[67 + 2 * power] | TILE_PALETTE(8);

	bg0MemorySub[(POWER_SUB_Y + 1) * SCREEN_WIDTH_TILE + POWER_SUB_X]
			= tiles_subMap[88 + 2 * power] | TILE_PALETTE(8);

	bg0MemorySub[(POWER_SUB_Y + 1) * SCREEN_WIDTH_TILE + POWER_SUB_X + 1]
			= tiles_subMap[89 + 2 * power] | TILE_PALETTE(8);
}

void showSelector_Sub(int pos, int mode) {
	int i, j;
	int offset = 0;
	if (mode == OVER)
		offset = SELECTOR_OFFSET;

	clearBG0_Sub();

	for (j = SELECTOR_X0 + 1; j < SELECTOR_X1; j++) {
		bg0MemorySub[(SELECTOR_Y0 + offset + pos * SELECTOR_SPACE)
				* SCREEN_WIDTH_TILE + j] = tiles_subMap[1] | TILE_PALETTE(8);

		bg0MemorySub[(SELECTOR_Y1 + offset + pos * SELECTOR_SPACE)
				* SCREEN_WIDTH_TILE + j] = tiles_subMap[0] | TILE_PALETTE(8);
	}

	for (i = (SELECTOR_Y0 + offset + pos * 5); i <= (SELECTOR_Y1 + offset + pos
			* 5); i++) {
		bg0MemorySub[i * SCREEN_WIDTH_TILE + SELECTOR_X0] = tiles_subMap[23]
				| TILE_PALETTE(8);

		bg0MemorySub[i * SCREEN_WIDTH_TILE + SELECTOR_X1] = tiles_subMap[22]
				| TILE_PALETTE(8);
	}
}

void showScore_Sub(int score) {
	int j, i, number;

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
		bg0MemorySub[(SCORE_X_SUB - 2 * i) + SCORE_Y_SUB * SCREEN_WIDTH_TILE]
				= tiles_subMap[(10 - number) * 2] | TILE_PALETTE(8);

		bg0MemorySub[(SCORE_X_SUB - 2 * i) + SCORE_Y_SUB * SCREEN_WIDTH_TILE
				+ 1] = tiles_subMap[(10 - number) * 2 + 1] | TILE_PALETTE(8);

		bg0MemorySub[(SCORE_X_SUB - 2 * i) + (SCORE_Y_SUB + 1)
				* SCREEN_WIDTH_TILE] = tiles_subMap[TILES_WIDTH + (10 - number)
				* 2] | TILE_PALETTE(8);

		bg0MemorySub[(SCORE_X_SUB - 2 * i) + (SCORE_Y_SUB + 1)
				* SCREEN_WIDTH_TILE + 1] = tiles_subMap[TILES_WIDTH + (10
				- number) * 2 + 1] | TILE_PALETTE(8);

		bg0MemorySub[(SCORE_X_SUB - 2 * i) + (SCORE_Y_SUB + 2)
				* SCREEN_WIDTH_TILE] = tiles_subMap[2 * TILES_WIDTH + (10
				- number) * 2] | TILE_PALETTE(8);

		bg0MemorySub[(SCORE_X_SUB - 2 * i) + (SCORE_Y_SUB + 2)
				* SCREEN_WIDTH_TILE + 1] = tiles_subMap[2 * TILES_WIDTH + (10
				- number) * 2 + 1] | TILE_PALETTE(8);
	}
}

void showHighScores_Sub() {
	int j, i, number, pos;

	readMaxScores();

	for (pos = 0; pos < HS_NUM; pos++) {
		for (i = NUM_DIGITS; i > 0; i--) {
			//calculate the power of i-1 in j
			j = i - 1;
			number = 1;
			while (j--)
				number = number * 10;

			//Obtain the number to render
			number = max_score[pos] / number;
			number = number % 10;

			//Render the number
			bg0MemorySub[(HS_H - 2 * i) + (HS_V + SELECTOR_SPACE * pos)
					* SCREEN_WIDTH_TILE] = tiles_subMap[(10 - number) * 2]
					| TILE_PALETTE(10+pos);

			bg0MemorySub[(HS_H - 2 * i) + (HS_V + SELECTOR_SPACE * pos)
					* SCREEN_WIDTH_TILE + 1] = tiles_subMap[(10 - number) * 2
					+ 1] | TILE_PALETTE(10+pos);

			bg0MemorySub[(HS_H - 2 * i) + (HS_V + SELECTOR_SPACE * pos + 1)
					* SCREEN_WIDTH_TILE] = tiles_subMap[TILES_WIDTH + (10
					- number) * 2] | TILE_PALETTE(10+pos);

			bg0MemorySub[(HS_H - 2 * i) + (HS_V + SELECTOR_SPACE * pos + 1)
					* SCREEN_WIDTH_TILE + 1] = tiles_subMap[TILES_WIDTH + (10
					- number) * 2 + 1] | TILE_PALETTE(10+pos);

			bg0MemorySub[(HS_H - 2 * i) + (HS_V + SELECTOR_SPACE * pos + 2)
					* SCREEN_WIDTH_TILE] = tiles_subMap[2 * TILES_WIDTH + (10
					- number) * 2] | TILE_PALETTE(10+pos);

			bg0MemorySub[(HS_H - 2 * i) + (HS_V + SELECTOR_SPACE * pos + 2)
					* SCREEN_WIDTH_TILE + 1] = tiles_subMap[2 * TILES_WIDTH
					+ (10 - number) * 2 + 1] | TILE_PALETTE(10+pos);
		}
	}
}
