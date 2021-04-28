#include <nds.h>
#include <stdio.h>
#include <math.h>
#include <fat.h>

#include "defines.h"
#include "graphics_main.h"
#include "graphics_sub.h"
#include "storage.h"

#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"


//*****************************************************************************
//*************************** GAME AND TIME VARIABLES *************************
//*****************************************************************************

int mode;
int state;
int cube;
int power;
int selector;
int bg1V;
int timer0_switch;
int timer2_ticks;
int timer2_switch;
int timer3_ticks;
int power_ticks;
int xr;
int yr;
int xc;
int yc;
bool h_flip;



//*****************************************************************************
//****************************** INITIALIZATION *******************************
//*****************************************************************************

/*
 * VOID GAME_INIT()
 * This function initializes the game. This includes NDS specific initializations,
 * the timers and the sound. It then calls the game menu.
 */
void game_init();



//*****************************************************************************
//******************************** GAME STATES ********************************
//*****************************************************************************

/*
 * VOID GAME_MENU()
 * This function is called while in the MENU state. It plays music, resets the
 * game, configures the appropriate graphics, and calls an infinite loop to
 * select another game state: play (in mode level or infinite) or stats. The
 * loop calls the appropriate key controls and displays the selector.
 */
void game_menu();

/*
 * VOID GAME_PLAY()
 * This function is called while in the PLAY state. It stops the music,
 * configures the appropriate graphics and sprites, manages the appropriate
 * timers and calls an infinite loop to play the game. The loop calls the
 * appropriate key controls, updates the graphics and checks for sprite
 * collisions.
 */
void game_play();

/*
 * VOID GAME_PAUSE()
 * This function is called while in the PAUSE state. It configures the
 * appropriate graphics, manages the appropriate timers and calls an infinite
 * loop to select another game state: play (reset or resume) or menu. The loop
 * calls appropriate key controls and displays the selector.
 */
void game_pause();

/*
 * VOID GAME_OVER()
 * This function is called while in the OVER state. It configures the
 * appropriate graphics, manages the appropriate timers and calls an infinite
 * loop to select another game state: play (reset) or menu. The loop
 * calls appropriate key controls and displays the selector.
 */
void game_over();

/*
 * VOID GAME_STATS()
 * This function is called while in the STATS state. It configures the
 * appropriate graphics, and calls an infinite loop to show the four highest
 * scores. The loop calls appropriate key controls.
 */
void game_stats();

/*
 * VOID GAME_RESET()
 * This function is called to reset all of the game parameters. It also manages
 * the appropriate timers.
 */
void game_reset();



//*****************************************************************************
//******************************** KEY CONTROLS *******************************
//*****************************************************************************

/*
 * VOID KEYCONTROL_MENU()
 * This function is during the MENU state infinite loop. It manages the key
 * and touch controls for the appropriate state.
 */
void keyControl_menu();

/*
 * VOID KEYCONTROL_PLAY()
 * This function is during the PLAY state infinite loop. It manages the key
 * and touch controls for the appropriate state.
 */
void keyControl_play();

/*
 * VOID KEYCONTROL_PAUSE()
 * This function is during the PAUSE state infinite loop. It manages the key
 * and touch controls for the appropriate state.
 */
void keyControl_pause();

/*
 * VOID KEYCONTROL_OVER()
 * This function is during the OVER state infinite loop. It manages the key
 * and touch controls for the appropriate state.
 */
void keyControl_over();

/*
 * VOID KEYCONTROL_STATS()
 * This function is during the STATS state infinite loop. It manages the key
 * and touch controls for the appropriate state.
 */
void keyControl_stats();



//*****************************************************************************
//****************************** GAME FUNCTIONS *******************************
//*****************************************************************************

/*
 * VOID CHECKOBSTACLEDISTANCE()
 * This function checks the distance between the sprite and all of the
 * obstacles around it. If it detects a collision the game_over() function is
 * called.
 */
void checkObstacleDistance();

/*
 * VOID CHECKCUBEDISTANCE()
 * This function checks the distance between the sprite and the current falling
 * cube. If a collision is detected, the appropriate power is assigned, or in
 * case of a bomb, the game_over() function is called.
 */
void checkCubeDistance();



//*****************************************************************************
//*************************** TIMER INITIALIZATION ****************************
//*****************************************************************************

/*
 * VOID INITTIMER0()
 * This initializes timer 0 to trigger an interrupt every 500 ms. It also
 * associates the the appropriate ISR to call if triggered.
 */
void initTimer0();

/*
 * VOID INITTIMER1()
 * This initializes timer 1 to trigger an interrupt every 100 ms. It also
 * associates the the appropriate ISR to call if triggered.
 */
void initTimer1();

/*
 * VOID INITTIMER2()
 * This initializes timer 2 to trigger an interrupt every 333 ms. It also
 * associates the the appropriate ISR to call if triggered.
 */
void initTimer2();

/*
 * VOID INITTIMER3()
 * This initializes timer 3 to trigger an interrupt every 71 ms. It also
 * associates the the appropriate ISR to call if triggered.
 */
void initTimer3();



//*****************************************************************************
//************************ INTERRUPT SERVICE ROUTINES *************************
//*****************************************************************************

/*
 * VOID TIMER0ISR()
 * Interrupt service routine for timer 0. This enables the tiles to flash by
 * using a switch.
 */
void timer0ISR();

/*
 * VOID TIMER1ISR()
 * Interrupt service routine for timer 1. This moves the sky for the main
 * background 1.
 */
void timer1ISR();

/*
 * VOID TIMER2ISR()
 * Interrupt service routine for timer 2. This moves the obstacles in the main
 * background 0.
 */
void timer2ISR();

/*
 * VOID TIMER3ISR()
 * Interrupt service routine for timer 3. This creates and moves the sprites
 * that are the cubes.
 */
void timer3ISR();



//*****************************************************************************
//***************************** HELPER FUNCTIONS ******************************
//*****************************************************************************

/*
 * INT GETDISTANCEX(INT X1, INT X2)
 * Helper function that calculates the distance between two values along the
 * x-axis
 */
int getDistanceX(int x1, int x2);

/*
 * INT GETDISTANCEY(INT Y1, INT Y2)
 * Helper function that calculates the distance between two values along the
 * y-axis
 */
int getDistanceY(int y1, int y2);
