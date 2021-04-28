
//{{BLOCK(sky_main)

//======================================================================
//
//	sky_main, 256x512@4, 
//	+ palette 256 entries, not compressed
//	+ 148 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x64 
//	Total size: 512 + 4736 + 4096 = 9344
//
//	Time-stamp: 2020-01-14, 20:18:25
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SKY_MAIN_H
#define GRIT_SKY_MAIN_H

#define sky_mainTilesLen 4736
extern const unsigned int sky_mainTiles[1184];

#define sky_mainMapLen 4096
extern const unsigned short sky_mainMap[2048];

#define sky_mainPalLen 512
extern const unsigned short sky_mainPal[256];

#endif // GRIT_SKY_MAIN_H

//}}BLOCK(sky_main)
