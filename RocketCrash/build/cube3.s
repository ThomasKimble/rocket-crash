
@{{BLOCK(cube3)

@=======================================================================
@
@	cube3, 16x16@4, 
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
	.global cube3Tiles		@ 128 unsigned chars
cube3Tiles:
	.word 0x33333330,0x11111113,0x44444413,0x44444413,0x44444413,0x44333413,0x44323413,0x33333333
	.word 0x03333333,0x31111111,0x34444444,0x34444444,0x33333333,0x33222223,0x33233333,0x33233333
	.word 0x32222233,0x33333333,0x44323413,0x44333413,0x44444413,0x44444413,0x44444413,0x33333330
	.word 0x33222223,0x33333323,0x33333323,0x33222223,0x33333333,0x34444444,0x34444444,0x03333333

	.section .rodata
	.align	2
	.global cube3Pal		@ 32 unsigned chars
cube3Pal:
	.hword 0x7C00,0x0217,0x7FFF,0x0000,0x02DF,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(cube3)
