#include "SMSlib.h"
#include "bank2.h"

#define DIR_LEFT 0
#define DIR_RIGHT 1

struct player {
  	float x;
  	float y;
  	float xspeed;
  	float yspeed;
  	unsigned char direction;
  	unsigned char frame;
  	unsigned char frame_t;
};

void update_player(struct player *p) {
  	unsigned int keys = SMS_getKeysStatus();
  	unsigned int keys_pressed = SMS_getKeysPressed();

  	if (keys & PORT_A_KEY_LEFT) {
  	  	p->xspeed = -2;
  	  	p->direction = DIR_LEFT;
  	} else if (keys & PORT_A_KEY_RIGHT) {
  	  	p->xspeed = 2;
  	  	p->direction = DIR_RIGHT;
  	} else {
  	  	p->xspeed = 0;
  	  	p->frame_t = 0;
  	}

  	if (p->y < 128) {
  	  	p->yspeed += 0.2;
  	} else {
  	  	if (keys_pressed & PORT_A_KEY_1) {
  	  	  	p->yspeed = -4;
  	  	} else {
  	  	  	p->yspeed = 0;
  	  	  	p->y = 128;
  	  	}
  	}

  	p->x += p->xspeed;
  	p->y += p->yspeed;

  	if (p->x < 0) p->x = 0;

  	if (p->yspeed != 0) {
  	  	p->frame = 0;
  	} else if (p->xspeed != 0) {
  	  	p->frame_t = (p->frame_t + 1) % 16;
  	  	if (p->frame_t == 0) p->frame = 0;
  	  	else if (p->frame_t/4 == 1) p->frame = 1;
  	  	else if (p->frame_t/4 == 2) p->frame = 2;
  	  	else if (p->frame_t/4 == 3) p->frame = 1;
  	} else {
  	  	p->frame = 3;
  	}
}

void draw_player(struct player *p) {
  	SMS_addTwoAdjoiningSprites(p->x, p->y 	, 0 + p->frame*8 + p->direction*4);
  	SMS_addTwoAdjoiningSprites(p->x, p->y+8, 2 + p->frame*8 + p->direction*4);
}

void draw_16x16_block(unsigned char x, unsigned char y) {
  	SMS_setTileatXY(x, y, 1);
  	SMS_setTileatXY(x+1, y, 2);
  	SMS_setTileatXY(x, y+1, 3);
  	SMS_setTileatXY(x+1, y+1, 4);
}

void main(void)
{
  	SMS_VRAMmemsetW(0, 0x0000, 16384);

  	SMS_useFirstHalfTilesforSprites(0);
  	SMS_loadPSGaidencompressedTiles(turnip_spr0_left_psgcompr,  	256);
  	SMS_loadPSGaidencompressedTiles(turnip_spr0_right_psgcompr, 256+4);
  	SMS_loadPSGaidencompressedTiles(turnip_spr1_left_psgcompr,  	256+8);
  	SMS_loadPSGaidencompressedTiles(turnip_spr1_right_psgcompr, 256+12);
  	SMS_loadPSGaidencompressedTiles(turnip_spr2_left_psgcompr,  	256+16);
  	SMS_loadPSGaidencompressedTiles(turnip_spr2_right_psgcompr, 256+20);
  	SMS_loadPSGaidencompressedTiles(turnip_spr3_left_psgcompr,  	256+24);
  	SMS_loadPSGaidencompressedTiles(turnip_spr3_right_psgcompr, 256+28);
  	SMS_loadSpritePalette(turnip_spr_pal_bin); 

  	SMS_loadPSGaidencompressedTiles(block_psgcompr, 1);
  	SMS_loadBGPalette(block_pal_bin);
  	SMS_setBGPaletteColor(0, RGBHTML(0x55ffaa));

  	for (int y = 0; y < 3; y++)
  	  	for (int x = 0; x < 16; x++)
  	  	  	draw_16x16_block(x*2, 18+y*2);

  	SMS_displayOn();

  	struct player p;
  	p.x = 16;
  	p.y = 16;
  	p.direction = 0;
  	p.frame = 0;

  	for(;;) {
  	  	update_player(&p);

  	  	SMS_initSprites();
  	  	draw_player(&p);

  	  	SMS_waitForVBlank();
  	  	SMS_copySpritestoSAT();
  	}
}

SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
SMS_EMBED_SDSC_HEADER_AUTO_DATE(1, 0, "kivutar", "platformer", "A platformer example");
