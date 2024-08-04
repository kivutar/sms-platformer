#include "SMSlib.h"
#include "banjo.h"

#include "bank2.h"
#include "song_table.h"

#define DIR_LEFT 0
#define DIR_RIGHT 1

char map[12*64] = {
	8,5,9,0,0,0,0,0,0,0,0,0,3,5,5,4,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,10,0,0,0,0,0,0,0,0,8,5,5,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,8,9,0,0,0,0,0,2,0,2,0,2,0,0,2,0,2,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,3,10,4,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,10,10,10,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,4,0,0,0,0,0,0,0,0,8,10,9,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,10,0,0,0,0,0,0,0,10,0,5,5,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,3,5,5,4,0,0,0,0,0,0,0,3,5,5,5,4,10,0,0,0,0,2,2,2,2,0,0,2,0,2,0,2,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,3,5,5,5,5,4,0,0,0,0,0,3,5,5,5,5,5,4,0,0,0,2,2,0,0,2,2,0,2,0,2,0,0,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,7,7,1,1,1,1,1,1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	6,6,6,6,6,6,6,6,0,0,0,10,3,6,6,6,6,6,6,6,6,6,6,6,6,7,7,6,6,6,6,6,6,7,7,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	6,6,6,6,6,6,6,6,7,7,7,7,7,6,6,6,6,6,6,6,6,6,6,6,6,7,7,6,6,6,6,6,6,7,7,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

struct player {
	int x;
	int y;
	int old_x;
	int xspeed;
	int yspeed;
	unsigned char direction;
	unsigned char frame;
	unsigned char frame_t;
};

char running[4] = {0, 1, 2, 1};

char map_get(int x, int y) {
	char t = map[((y>>4)<<6)+(x>>4)];
	return t == 1 || t == 6 || t == 2;
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

	if (p->x < 8) p->x = 8;
	else if (p->x > 256*4-16) p->x = 256*4-16;
	if (p->y > 192) p->y = 0;

	if (p->yspeed != 0) {
		p->frame = 0;
	} else if (p->xspeed != 0) {
		p->frame_t = (p->frame_t + 1) % 16;
		p->frame = running[p->frame_t>>2];
	} else {
		p->frame = 3;
	}

	if (p->x >= 128) {
		int scrollx = - p->old_x + 128;
		if (p->x > p->old_x && scrollx % 8 == 0)
			SMS_loadTileMapColumn((32 - scrollx / 8) % 32, 0, &map_tilemap_cmraw[(32 - scrollx / 8) * 48], 24);
		else if (p->x < p->old_x && scrollx % 8 == 0)
			SMS_loadTileMapColumn((-scrollx / 8) % 32, 0, &map_tilemap_cmraw[(-scrollx / 8) * 48], 24);
		SMS_setBGScrollX(scrollx);
	}

	p->old_x = p->x;
}

void draw_player(struct player *p) {
	int x = p->x;
	if (x > 128) x = 128;
	SMS_addTwoAdjoiningSprites(x, p->y  , 0 + p->frame*8 + p->direction*4);
	SMS_addTwoAdjoiningSprites(x, p->y+8, 2 + p->frame*8 + p->direction*4);
}

void main(void)
{
	SMS_VRAMmemsetW(0, 0x0000, 16384);

	SMS_VDPturnOnFeature(VDPFEATURE_HIDEFIRSTCOL);

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
	SMS_setBackdropColor(1);

	for (int x = 0; x < 32; x++)
		SMS_loadTileMapColumn(x, 0, &map_tilemap_cmraw[x*48], 24);

	SMS_displayOn();

	struct player p;
	p.x = 8;
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
