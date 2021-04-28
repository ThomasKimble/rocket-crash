#include "game.h"

//*****************************************************************************
//****************************** INITIALIZATION *******************************
//*****************************************************************************

void game_init() {
	//NDS specific initializations
	fatInitDefault();
	consoleDemoInit();

	//Initialize timers
	initTimer0();
	initTimer1();
	initTimer2();
	initTimer3();

	//Sound
	//Init the sound library
	mmInitDefaultMem((mm_addr) soundbank_bin);
	//Load module
	mmLoad(MOD_MUSIC);
	//Load effect
	mmLoadEffect(SFX_TICKTOCK);
	mmLoadEffect(SFX_SWITCH);
	mmLoadEffect(SFX_SELECT);
	mmLoadEffect(SFX_POWER);
	mmLoadEffect(SFX_CRASH);
	//Start Music
	mmStart(MOD_MUSIC,MM_PLAY_LOOP);

	//Start game at main menu
	mode = INF;
	game_menu();
}


//*****************************************************************************
//******************************** GAME STATES ********************************
//*****************************************************************************

void game_menu() {
	//Play Music
	mmResume();

	//Main Menu state
	state = MENU;

	//Reset game
	game_reset();

	//Configure correct graphics
	configGraphics_Sub(state);
	configGraphics_Main(state);

	//Clear Background 0
	clearBG0_Sub();

	//Selector in first position
	selector = 0;

	//Infinite loop for state = MENU
	while (1) {
		showSelector_Sub(selector, state);
		keyControl_menu();
		swiWaitForVBlank();
	}
}

void game_play() {
	//Stop Music
	mmPause();

	//Play state
	state = PLAY;

	//Configure correct graphics
	configGraphics_Sub(state);
	configGraphics_Main(state);

	//Clear Background 0
	clearBG0_Sub();

	//Configure sprites
	configSprites_Main();

	//Manage timers
	irqEnable(IRQ_TIMER1);
	irqEnable(IRQ_TIMER2);
	if (mode == INF)
		irqEnable(IRQ_TIMER3);
	irqDisable(IRQ_TIMER0);

	//Infinit loop for state = PLAY
	while (1) {
		REG_BG1VOFS = bg1V;
		showScore_Sub(score);
		showPower_Sub(power);
		updateSpriteRocket_Main(xr, yr, h_flip);
		updateSpriteCube_Main(xc, yc, cube);
		checkObstacleDistance();
		checkCubeDistance();
		keyControl_play();
		swiWaitForVBlank();
	}
}

void game_pause() {
	//Pause state
	state = PAUSE;

	//Configure correct graphics
	configGraphics_Sub(state);
	configGraphics_Main(state);

	//Clear Background 0
	clearBG0_Sub();

	//Display Score on main screen
	showScore_Main(score);

	//Selector in first position
	selector = 0;

	//Manage timers
	irqDisable(IRQ_TIMER1);
	irqDisable(IRQ_TIMER2);
	irqDisable(IRQ_TIMER3);
	irqEnable(IRQ_TIMER0);

	//Infinite loop for state = pause
	while (1) {
		showSelector_Sub(selector, state);
		keyControl_pause();
		swiWaitForVBlank();
	}
}

void game_over() {
	//Play game over effect
	mmEffect(SFX_CRASH);

	//Pause state
	state = OVER;

	//Configure correct graphics
	configGraphics_Sub(state);
	configGraphics_Main(state);

	//Clear Background 0
	clearBG0_Sub();

	//Display Score on main screen
	showScore_Main(score);

	//Selector in first position
	selector = 0;

	//Manage timers
	irqDisable(IRQ_TIMER1);
	irqDisable(IRQ_TIMER2);
	irqDisable(IRQ_TIMER3);
	irqEnable(IRQ_TIMER0);

	//Infinite loop for state = OVER
	while (1) {
		showSelector_Sub(selector, state);
		keyControl_over();
		swiWaitForVBlank();
	}
}

void game_stats() {
	//Stats state
	state = STATS;

	//Configure correct graphics
	configGraphics_Sub(state);
	configGraphics_Main(state);

	//Clear Background 0 and show high scores
	clearBG0_Sub();
	showHighScores_Sub();

	//Infinite loop for state = STATS
	while (1) {
		keyControl_stats();
		swiWaitForVBlank();
	}
}

void game_reset() {
	//Manage timers
	irqDisable(IRQ_TIMER1);
	irqDisable(IRQ_TIMER2);
	irqDisable(IRQ_TIMER3);
	irqDisable(IRQ_TIMER0);

	//(Re-)initialize obstacle grid
	initObstacleGrid_Main();

	//Bottom of sky background (BG1 main)
	REG_BG1VOFS = SKY_HEIGHT;
	bg1V = SKY_HEIGHT;

	//Update if highscore
	updateHighscores();

	//Reset score, timer ticks and switches to zero
	score = 0;
	timer2_ticks = 0;
	timer2_switch = 0;
	timer3_ticks = 0;

	//No cubes or powers
	cube = NONE;
	power = NONE;
	yc = -2 * CUBE_HEIGHT;

	//Reset sprite position
	xr = (SCREEN_WIDTH - ROCKET_WIDTH) / 2;
	yr = SCREEN_HEIGHT - ROCKET_HEIGHT - 8;
	h_flip = false;
}


//*****************************************************************************
//******************************** KEY CONTROLS *******************************
//*****************************************************************************

void keyControl_menu() {
	scanKeys();
	unsigned press = keysDown();

	//Touch Pad
	if (press & KEY_TOUCH) {
		touchPosition touch;
		touchRead(&touch);
		if (touch.py > SELECTOR_ZONE_Y0 && touch.py < SELECTOR_ZONE_Y1
				&& touch.px > SELECTOR_ZONE_X0 && touch.px < SELECTOR_ZONE_X1) {
			if (touch.py < SELECTOR_TOP_1) {
				mmEffect(SFX_SELECT);
				mode = INF;
				game_play();
			} else if (touch.py > SELECTOR_BOTTOM_1) {
				mmEffect(SFX_SELECT);
				game_stats();
			} else {
				mmEffect(SFX_SELECT);
				mode = LEVEL;
				game_play();
			}
		}
	}

	//Play if start key is pressed
	if (press & KEY_START || press & KEY_B || press & KEY_X) {
		mmEffect(SFX_SELECT);
		game_play();
	}

	//Modify position selector accordingly with the keys
	if (press & KEY_UP) {
		if (selector != 0) {
			mmEffect(SFX_SWITCH);
			selector--;
		}
	}
	if (press & KEY_DOWN) {
		if (selector != 2) {
			mmEffect(SFX_SWITCH);
			selector++;
		}
	}

	//Select action from sub menu
	if (press & KEY_A || press & KEY_SELECT) {
		if (selector == 0) {
			mmEffect(SFX_SELECT);
			mode = INF;
			game_play();
		} else if (selector == 1) {
			mmEffect(SFX_SELECT);
			mode = LEVEL;
			game_play();
		} else if (selector == 2) {
			mmEffect(SFX_SELECT);
			game_stats();
		}
	}
}

void keyControl_play() {
	scanKeys();
	unsigned hold = keysHeld();
	unsigned press = keysDown();

	int offset = 0;
	if (power == MUL)
		offset = 2;
	else if (power == DIV)
		offset = -1;

	//Pause if start key is pressed
	if (press & KEY_START) {
		irqDisable(IRQ_TIMER1);
		mmEffect(SFX_SELECT);
		game_pause();
	}

	//Modify position of the sprite accordingly
	//Touch Pad
	if (hold & KEY_TOUCH) {
		touchPosition touch;
		touchRead(&touch);
		if (touch.py > SELECTOR_ZONE_PLAY) {
			if (touch.px > SCREEN_WIDTH / 2) {
				if (power == INV) {
					xr -= SPEED;
					h_flip = true;
					if (xr < 0)
						xr = 0;
				} else {
					xr += SPEED + offset;
					h_flip = false;
					if (xr > (SCREEN_WIDTH - ROCKET_WIDTH)) {
						if (power == WALL)
							xr = 0;
						else
							xr = (SCREEN_WIDTH - ROCKET_WIDTH);
					}
				}
			} else {
				if (power == INV) {
					xr += SPEED;
					h_flip = false;
					if (xr > (SCREEN_WIDTH - ROCKET_WIDTH))
						xr = (SCREEN_WIDTH - ROCKET_WIDTH);
				} else {
					xr -= SPEED + offset;
					h_flip = true;
					if (xr < 0) {
						if (power == WALL)
							xr = (SCREEN_WIDTH - ROCKET_WIDTH);
						else
							xr = 0;
					}
				}
			}
		}
	}

	//Keys
	if (hold & KEY_RIGHT || hold & KEY_R) {
		if (power == INV) {
			xr -= SPEED;
			h_flip = true;
			if (xr < 0)
				xr = 0;
		} else {
			xr += 2 + offset;
			h_flip = false;
			if (xr > (SCREEN_WIDTH - ROCKET_WIDTH)) {
				if (power == WALL)
					xr = 0;
				else
					xr = (SCREEN_WIDTH - ROCKET_WIDTH);
			}
		}
	}
	if (hold & KEY_LEFT || hold & KEY_L) {
		if (power == INV) {
			xr += SPEED;
			h_flip = false;
			if (xr > (SCREEN_WIDTH - ROCKET_WIDTH))
				xr = (SCREEN_WIDTH - ROCKET_WIDTH);
		} else {
			xr -= SPEED + offset;
			h_flip = true;
			if (xr < 0) {
				if (power == WALL)
					xr = (SCREEN_WIDTH - ROCKET_WIDTH);
				else
					xr = 0;
			}
		}
	}
}

void keyControl_pause() {
	scanKeys();
	unsigned press = keysDown();

	//Touch Pad
	if (press & KEY_TOUCH) {
		touchPosition touch;
		touchRead(&touch);
		if (touch.py > SELECTOR_ZONE_Y0 && touch.py < SELECTOR_ZONE_Y1
				&& touch.px > SELECTOR_ZONE_X0 && touch.px < SELECTOR_ZONE_X1) {
			if (touch.py < SELECTOR_TOP_1) {
				mmEffect(SFX_SELECT);
				game_play();
			} else if (touch.py > SELECTOR_BOTTOM_1) {
				mmEffect(SFX_SELECT);
				game_menu();
			} else {
				mmEffect(SFX_SELECT);
				game_reset();
				game_play();
			}
		}
	}

	//Play if start key is pressed
	if (press & KEY_START || press & KEY_B || press & KEY_X) {
		mmEffect(SFX_SELECT);
		game_play();
	}

	//Modify position selector accordingly with the keys
	if (press & KEY_UP) {
		if (selector != 0) {
			mmEffect(SFX_SWITCH);
			selector--;
		}
	}
	if (press & KEY_DOWN) {
		if (selector != 2) {
			mmEffect(SFX_SWITCH);
			selector++;
		}
	}

	//Select action from sub menu
	if (press & KEY_A || press & KEY_SELECT) {
		if (selector == 0) {
			mmEffect(SFX_SELECT);
			game_play();
		} else if (selector == 1) {
			mmEffect(SFX_SELECT);
			game_reset();
			game_play();
		} else if (selector == 2) {
			mmEffect(SFX_SELECT);
			game_menu();
		}
	}
}

void keyControl_over() {
	scanKeys();
	unsigned press = keysDown();

	//Touch Pad
	if (press & KEY_TOUCH) {
		touchPosition touch;
		touchRead(&touch);
		if (touch.py > SELECTOR_ZONE_Y0 && touch.py < SELECTOR_ZONE_Y1
				&& touch.px > SELECTOR_ZONE_X0 && touch.px < SELECTOR_ZONE_X1) {
			if (touch.py < SELECTOR_TOP_2) {
				mmEffect(SFX_SELECT);
				game_reset();
				game_play();
			} else {
				mmEffect(SFX_SELECT);
				game_menu();
			}
		}
	}

	//Play if start key is pressed
	if (press & KEY_START || press & KEY_B || press & KEY_X) {
		mmEffect(SFX_SELECT);
		game_reset();
		game_play();
	}

	//Modify position selector accordingly with the keys
	if (press & KEY_UP) {
		if (selector != 0) {
			mmEffect(SFX_SWITCH);
			selector--;
		}
	}
	if (press & KEY_DOWN) {
		if (selector != 1) {
			mmEffect(SFX_SWITCH);
			selector++;
		}
	}

	//Select action from sub menu
	if (press & KEY_A || press & KEY_SELECT) {
		if (selector == 0) {
			mmEffect(SFX_SELECT);
			game_reset();
			game_play();
		} else if (selector == 1) {
			mmEffect(SFX_SELECT);
			game_menu();
		}
	}
}

void keyControl_stats() {
	scanKeys();
	unsigned press = keysDown();

	//Touch Pad
	if (press & KEY_TOUCH) {
		touchPosition touch;
		touchRead(&touch);
		if (touch.py > 0 && touch.py < SELECTOR_BACK_Y && touch.px > 0
				&& touch.px < SELECTOR_BACK_X) {
			mmEffect(SFX_SELECT);
			game_menu();
		}
	}

	//Play if start key is pressed
	if (press & KEY_START || press & KEY_B || press & KEY_X || press & KEY_Y) {
		mmEffect(SFX_SELECT);
		game_menu();
	}
}


//*****************************************************************************
//****************************** GAME FUNCTIONS *******************************
//*****************************************************************************

void checkObstacleDistance() {
	int distX, distY, i, j;

	for (i = 19; i < SCREEN_HEIGHT_TILE - 1; i++) {
		for (j = 0; j < SCREEN_WIDTH_TILE; j++) {
			if (obstacles[i * SCREEN_WIDTH_TILE + j] != 0) {
				distX = getDistanceX(xr + ROCKET_WIDTH / 2, j * 8 + 4);
				distY = getDistanceY(yr + ROCKET_HEIGHT, i * 8 + 4);
				if (distX < (ROCKET_WIDTH / 2 + 2) && (distY < ROCKET_HEIGHT))
					game_over();
			}
		}
	}
}

void checkCubeDistance() {
	int distX = getDistanceX(xr + ROCKET_WIDTH / 2, xc + CUBE_WIDTH / 2);
	int distY = getDistanceY(yr + ROCKET_HEIGHT / 2, yc + CUBE_HEIGHT / 2);

	if (distX < ROCKET_WIDTH / 2 && distY < ROCKET_HEIGHT / 2) {
		yc = 0 - 2 * CUBE_HEIGHT;
		updateSpriteCube_Main(xc, yc, cube);
		power = cube;
		if (power == BOM)
			game_over();
		cube = NONE;
		mmEffect(SFX_POWER);
	}
}


//*****************************************************************************
//*************************** TIMER INITIALIZATION ****************************
//*****************************************************************************

void initTimer0() {
	//Initialize timer ticks to zero
	timer0_switch = 0;

	//Configure timer to trigger an interrupt every 0.5s
	TIMER0_DATA = TIMER_FREQ_1024(2);
	TIMER0_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ | TIMER_ENABLE;

	//Associate the ISR (timerISR) to the interrupt line and enable it
	irqSet(IRQ_TIMER0, &timer0ISR);
}

void initTimer1() {
	//Set timer switch
	timer0_switch = 0;

	//Configure timer to trigger an interrupt every 100ms
	TIMER1_DATA = TIMER_FREQ_1024(10);
	TIMER1_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ | TIMER_ENABLE;

	//Associate the ISR (timerISR) to the interrupt line
	irqSet(IRQ_TIMER1, &timer1ISR);
}

void initTimer2() {
	//Set timer ticks and switch
	timer2_ticks = 0;
	timer2_switch = 0;

	// Configure timer to trigger an interrupt every 333ms
	TIMER2_DATA = TIMER_FREQ_1024(3);
	TIMER2_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ | TIMER_ENABLE;

	// Associate the ISR (timerISR) to the interrupt line
	irqSet(IRQ_TIMER2, &timer2ISR);
}

void initTimer3() {
	//Set timer ticks
	timer3_ticks = 0;

	// Configure timer to trigger an interrupt every 71 ms
	TIMER3_DATA = TIMER_FREQ_1024(14);
	TIMER3_CR = TIMER_DIV_1024 | TIMER_IRQ_REQ | TIMER_ENABLE;

	// Associate the ISR (timerISR) to the interrupt line
	irqSet(IRQ_TIMER3, &timer3ISR);
}


//*****************************************************************************
//************************ INTERRUPT SERVICE ROUTINES *************************
//*****************************************************************************

void timer0ISR() {
	//Flash titles
	if (timer0_switch == 0) {
		hideTitle_Main();
		timer0_switch = 1;
	} else {
		showTitle_Main();
		timer0_switch = 0;
	}
}

void timer1ISR() {
	//Move sky (BG1 main) and update score
	bg1V--;
	score += 3;
}

void timer2ISR() {
	//Move obstacles (BG0 main)
	updateBG0_Main(timer2_ticks);
	if (mode == INF)
		timer2_ticks++;
	else if (mode == LEVEL) {
		if (bg1V > NUM_LEVEL1)
			timer2_ticks++;
		else if (timer2_switch == 0) {
			timer2_ticks = -1;
			timer2_switch = 1;
		} else
			timer2_ticks = 1;
	}
}

void timer3ISR() {
	//Create and move cubes (Sprites)
	if (cube == NONE) {
		timer3_ticks++;
		if (timer3_ticks == CUBE_TIME) {
			timer3_ticks = 0;
			cube = (1 + rand() % 5);
			xc = (1 + rand() % (SCREEN_WIDTH - CUBE_WIDTH));
			yc = 0;
		}
	} else
		yc++;

	if (yc > SCREEN_HEIGHT + 2 * CUBE_HEIGHT)
		cube = NONE;

	if (power != NONE) {
		power_ticks++;
		if (power_ticks == POWER_TIME - 75)
			mmEffect(SFX_TICKTOCK);
		if (power_ticks == POWER_TIME) {
			power_ticks = 0;
			power = NONE;
		}
	}
}


//*****************************************************************************
//***************************** HELPER FUNCTIONS ******************************
//*****************************************************************************

int getDistanceX(int x1, int x2) {
	//Get distance along x axis
	return sqrt((x2 - x1) * (x2 - x1));
}

int getDistanceY(int y1, int y2) {
	//Get distance along y axis
	return sqrt((y2 - y1) * (y2 - y1));
}
