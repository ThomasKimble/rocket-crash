//Modes
#define LEVEL	0
#define INF		1

//States
#define MENU	0
#define PLAY	1
#define PAUSE	2
#define OVER 	3
#define STATS	4

//Cubes and Powers
#define NONE	0
#define	INV		1
#define	WALL	2
#define	MUL		3
#define	DIV		4
#define	BOM		5

//Screen parameters
#define SKY_HEIGHT			320
#define SCREEN_WIDTH		256
#define SCREEN_WIDTH_TILE	32
#define	SCREEN_HEIGHT		192
#define SCREEN_HEIGHT_TILE	24
#define SCREEN_WIDTH_OBS	8
#define SCREEN_HEIGHT_OBS	24
#define OBSTACLE_WIDTH		8

//Rocket Sprite
#define	ROCKET_WIDTH		16
#define	ROCKET_HEIGHT		16
#define ROCKET_BLANK		3
#define SPEED				2

//Cube Sprites
#define CUBE_WIDTH			16
#define CUBE_HEIGHT			16
#define CUBE_TIME			80

//Power parameters
#define POWER_TIME			130
#define POWER_SUB_Y			1
#define POWER_SUB_X			15

//Highscore parameters
#define HS_NUM				4
#define HS_LEFT				3
#define HS_V				3
#define HS_H				22

//Copied tiles parameters
#define TILES_WIDTH			22

//Level parameters
#define NUM_LEVEL1			65

//Selector parameters for graphics
#define SELECTOR_X0			7
#define SELECTOR_X1			24
#define SELECTOR_Y0			4
#define SELECTOR_Y1			8
#define SELECTOR_SPACE		5
#define SELECTOR_OFFSET		3

//Selector parameters for touch control
#define SELECTOR_ZONE_X0	67
#define SELECTOR_ZONE_X1	193
#define SELECTOR_ZONE_Y0	42
#define SELECTOR_ZONE_Y1	149
#define SELECTOR_ZONE_PLAY	120
#define SELECTOR_BACK_X		33
#define SELECTOR_BACK_Y		25
#define SELECTOR_TOP_1		77
#define SELECTOR_TOP_2		95
#define SELECTOR_BOTTOM_1	114

//Score parameters
#define NUM_DIGITS			6
#define SCORE_X_MAIN		26
#define SCORE_Y_MAIN		19
#define SCORE_X_SUB			22
#define SCORE_Y_SUB			10

//State title parameters
#define TITLE_X0			4
#define TITLE_X1			28
#define TITLE_Y0			4
#define TITLE_Y1			17

//Palettes
#define PAL8	8*16
#define PAL9	9*16
#define PAL10	10*16
#define PAL11	11*16
#define PAL12	12*16
#define PAL13	13*16

//Colors
#define GOLD	ARGB16(1,31,30,24)
#define SILVER	ARGB16(1,31,29,29)
#define BRONZE	ARGB16(1,31,26,20)
#define BLUE	ARGB16(1,0,25,31)
