#include "SMSlib.h"
#include "banjo.h"

#include "bank2.h"
#include "song_table.h"

#define DIR_LEFT 0
#define DIR_RIGHT 1

char map[12*16] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

struct player {
	int x;
	int y;
	int xspeed;
	int yspeed;
	unsigned char direction;
	unsigned char frame;
	unsigned char frame_t;
};

char running[4] = {0, 1, 2, 1};

char map_get(int x, int y) {
	return map[(y>>4<<4)+(x>>4)];
}

void update_player(struct player *p) {
	unsigned int keys = SMS_getKeysStatus();
	unsigned int keys_pressed = SMS_getKeysPressed();

	if (keys & PORT_A_KEY_LEFT) {
		p->xspeed = -32;
		p->direction = DIR_LEFT;
	} else if (keys & PORT_A_KEY_RIGHT) {
		p->xspeed = 32;
		p->direction = DIR_RIGHT;
	} else {
		p->xspeed = 0;
		p->frame_t = 0;
	}

	if (keys_pressed & PORT_A_KEY_1 && p->yspeed == 0)
		p->yspeed = -64;
	else
		p->yspeed += 3;

	if (p->yspeed > 0 && (map_get(p->x, p->y+16) || map_get(p->x+15, p->y+16))) {
		p->yspeed = 0;
		p->y = p->y>>4<<4;
	}

	if ((p->xspeed < 0 && (map_get(p->x-1,  p->y) || map_get(p->x-1,  p->y+15)))
	 || (p->xspeed > 0 && (map_get(p->x+16, p->y) || map_get(p->x+16, p->y+15)))) {
		p->xspeed = 0;
		p->x = p->x>>4<<4;
	}

	p->x += p->xspeed>>4;
	p->y += p->yspeed>>4;

	if (p->x < 0) p->x = 0;
	else if (p->x > 256-16) p->x = 256-16;

	if (p->yspeed != 0) {
		p->frame = 0;
	} else if (p->xspeed != 0) {
		p->frame_t = (p->frame_t + 1) % 16;
		p->frame = running[p->frame_t>>2];
	} else {
		p->frame = 3;
	}
}

void draw_player(struct player *p) {
	SMS_addTwoAdjoiningSprites(p->x, p->y  , 0 + p->frame*8 + p->direction*4);
	SMS_addTwoAdjoiningSprites(p->x, p->y+8, 2 + p->frame*8 + p->direction*4);
}

void main(void)
{
	SMS_VRAMmemsetW(0, 0x0000, 16384);

	banjo_init(MODE_SN);
	banjo_set_song_table(song_table_sn);

	SMS_loadPSGaidencompressedTiles(turnip_spr0_left_psgcompr,  256);
	SMS_loadPSGaidencompressedTiles(turnip_spr0_right_psgcompr, 256+4);
	SMS_loadPSGaidencompressedTiles(turnip_spr1_left_psgcompr,  256+8);
	SMS_loadPSGaidencompressedTiles(turnip_spr1_right_psgcompr, 256+12);
	SMS_loadPSGaidencompressedTiles(turnip_spr2_left_psgcompr,  256+16);
	SMS_loadPSGaidencompressedTiles(turnip_spr2_right_psgcompr, 256+20);
	SMS_loadPSGaidencompressedTiles(turnip_spr3_left_psgcompr,  256+24);
	SMS_loadPSGaidencompressedTiles(turnip_spr3_right_psgcompr, 256+28);
	SMS_loadSpritePalette(turnip_spr_pal_bin);

	SMS_loadPSGaidencompressedTiles(map_psgcompr, 0);
	SMS_loadBGPalette(map_pal_bin);
	SMS_loadTileMapArea(0, 0, map_tilemap_bin, 32, 24);

	SMS_displayOn();

	struct player p;
	p.x = 48;
	p.y = 16;
	p.direction = DIR_RIGHT;
	p.frame = 0;
	p.yspeed = 0;
	p.xspeed = 0;

	banjo_queue_song(0);

	for(;;) {
		update_player(&p);

		SMS_initSprites();
		draw_player(&p);

		SMS_waitForVBlank();
		SMS_copySpritestoSAT();

		banjo_update();
	}
}

SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
SMS_EMBED_SDSC_HEADER_AUTO_DATE(1, 0, "kivutar", "platformer", "A platformer example");
