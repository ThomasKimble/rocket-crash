
@{{BLOCK(cube1)

@=======================================================================
@
@	cube1, 16x16@4, 
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
	.global cube1Tiles		@ 128 unsigned chars
cube1Tiles:
	.word 0x33333330,0x11111113,0x44444413,0x44444333,0x44443223,0x44432223,0x44322223,0x44322223
	.word 0x03333333,0x31111111,0x34444444,0x33344444,0x32234444,0x32253444,0x32522344,0x35222344
	.word 0x44322253,0x44322523,0x44435223,0x44443223,0x44444333,0x44444413,0x44444413,0x33333330
	.word 0x32222344,0x32222344,0x32223444,0x32234444,0x33344444,0x34444444,0x34444444,0x03333333

	.section .rodata
	.align	2
	.global cube1Pal		@ 32 unsigned chars
cube1Pal:
	.hword 0x7C00,0x0217,0x739C,0x0000,0x02DF,0x7FFF,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(cube1)
