
@{{BLOCK(cube4)

@=======================================================================
@
@	cube4, 16x16@4, 
@	Transparent color : 00,00,FF
@	+ palette 16 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2020-01-14, 20:18:25
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global cube4Tiles		@ 128 unsigned chars
cube4Tiles:
	.word 0x33333330,0x11111113,0x44444413,0x44444413,0x33444413,0x22344413,0x32234413,0x33223413
	.word 0x03333333,0x31111111,0x34453334,0x34444443,0x34444433,0x34444322,0x34443333,0x34433333
	.word 0x33323413,0x33323413,0x33323413,0x33334413,0x33344413,0x33444413,0x44444413,0x33333330
	.word 0x34433333,0x34433333,0x34433333,0x34443333,0x34444333,0x34444433,0x34444444,0x03333333

	.section .rodata
	.align	2
	.global cube4Pal		@ 32 unsigned chars
cube4Pal:
	.hword 0x7C00,0x0217,0x739C,0x0000,0x02DF,0x001F,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(cube4)
