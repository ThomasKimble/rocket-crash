
@{{BLOCK(cube0)

@=======================================================================
@
@	cube0, 16x16@4, 
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
	.global cube0Tiles		@ 128 unsigned chars
cube0Tiles:
	.word 0x33333330,0x11111113,0x44333413,0x44323313,0x33332333,0x22222233,0x33332333,0x44323313
	.word 0x03333333,0x31111111,0x34444444,0x34444444,0x34444443,0x34444443,0x34444443,0x34433344
	.word 0x44333413,0x34444413,0x34444413,0x34444413,0x44444413,0x44444413,0x44444413,0x33333330
	.word 0x34332344,0x33323333,0x33222222,0x33323333,0x34332344,0x34433344,0x34444444,0x03333333

	.section .rodata
	.align	2
	.global cube0Pal		@ 32 unsigned chars
cube0Pal:
	.hword 0x7C00,0x0217,0x739C,0x0000,0x02DF,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(cube0)
