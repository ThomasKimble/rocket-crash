
@{{BLOCK(cube2)

@=======================================================================
@
@	cube2, 16x16@4, 
@	Transparent color : 00,00,FF
@	+ palette 16 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2020-01-14, 20:18:24
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global cube2Tiles		@ 128 unsigned chars
cube2Tiles:
	.word 0x33333330,0x11111113,0x44444413,0x44444413,0x44444413,0x33344333,0x32333233,0x33232333
	.word 0x03333333,0x31111111,0x34444444,0x34444444,0x33333333,0x33222223,0x33233333,0x33233333
	.word 0x43323313,0x33232333,0x32333233,0x33343333,0x44444413,0x44444413,0x44444413,0x33333330
	.word 0x33222223,0x33333323,0x33333323,0x33222223,0x33333333,0x34444444,0x34444444,0x03333333

	.section .rodata
	.align	2
	.global cube2Pal		@ 32 unsigned chars
cube2Pal:
	.hword 0x7C00,0x0217,0x7FFF,0x0000,0x02DF,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(cube2)
