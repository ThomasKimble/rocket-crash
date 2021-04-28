
@{{BLOCK(rocket)

@=======================================================================
@
@	rocket, 16x16@4, 
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
	.global rocketTiles		@ 128 unsigned chars
rocketTiles:
	.word 0x22000000,0x22200000,0x37720000,0x27720000,0x27720000,0x37732000,0x37734200,0x37734420
	.word 0x00000022,0x00000222,0x00002773,0x00002772,0x00002772,0x00023773,0x00243773,0x02443773
	.word 0x73733442,0x77334332,0x77734442,0x27724442,0x62262442,0x65562220,0x51100000,0x66000000
	.word 0x24433737,0x23343377,0x24443777,0x24442772,0x24426226,0x02226556,0x00000115,0x00000066

	.section .rodata
	.align	2
	.global rocketPal		@ 32 unsigned chars
rocketPal:
	.hword 0x7C00,0x001F,0x0000,0x5EF7,0x739C,0x03FF,0x01FF,0x7FFF
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(rocket)
