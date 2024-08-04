#include "banjo.h"

const song_data_t cmajor_sn = {
	.magic_byte=0xba,
	.bank=0,
	.channel_count=4,
	.loop=1,
	.sfx_channel=255,
	.has_sn=1,
	.has_fm=0,
	.has_fm_drums=0,
	.time_base=1,
	.speed_1=6,
	.speed_2=6,
	.pattern_length=64,
	.orders_length=1,
	.instrument_pointers=cmajor_sn_instrument_pointers,
	.order_pointers=cmajor_sn_order_pointers,
	.subtic=0,
	.tic=0,
	.line=0,
	.order=0,
	.process_new_line=0,
	.noise_mode=0,
	.panning=0xff,
	.channel_types={ 0, 0, 0, 1, 0, 2, 0, 3, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 }
};

static const unsigned char cmajor_sn_volume_macro_0[] = { 1, 2, 3, 4, 6, 8, 11, 14, 15 };
static const unsigned char cmajor_sn_volume_macro_1[] = { 2, 5, 13, 15 };
static const unsigned char cmajor_sn_volume_macro_2[] = { 0, 0, 1, 2, 13, 15 };
static const unsigned char cmajor_sn_volume_macro_3[] = { 14, 13, 13, 12, 11, 11, 10, 9, 8, 8, 9, 10, 9, 8, 7, 8, 9 };
static const unsigned char cmajor_sn_volume_macro_4[] = { 2, 5, 8, 9, 9, 9, 4, 6, 11 };

static const instrument_t * const cmajor_sn_instrument_pointers[] = {
	&cmajor_sn_instrument_0,
	&cmajor_sn_instrument_1,
	&cmajor_sn_instrument_2,
	&cmajor_sn_instrument_3,
	&cmajor_sn_instrument_4,
};

static const instrument_t cmajor_sn_instrument_0 = {
	.volume_macro_len=9, .volume_macro_loop=255,
	.volume_macro_ptr=cmajor_sn_volume_macro_0,
	.fm_preset=255,
	.fm_patch={ 255, 255, 255, 255, 255, 255, 255, 255 }
};

static const instrument_t cmajor_sn_instrument_1 = {
	.volume_macro_len=4, .volume_macro_loop=255,
	.volume_macro_ptr=cmajor_sn_volume_macro_1,
	.fm_preset=255,
	.fm_patch={ 255, 255, 255, 255, 255, 255, 255, 255 }
};

static const instrument_t cmajor_sn_instrument_2 = {
	.volume_macro_len=6, .volume_macro_loop=255,
	.volume_macro_ptr=cmajor_sn_volume_macro_2,
	.fm_preset=255,
	.fm_patch={ 255, 255, 255, 255, 255, 255, 255, 255 }
};

static const instrument_t cmajor_sn_instrument_3 = {
	.volume_macro_len=17, .volume_macro_loop=255,
	.volume_macro_ptr=cmajor_sn_volume_macro_3,
	.fm_preset=255,
	.fm_patch={ 255, 255, 255, 255, 255, 255, 255, 255 }
};

static const instrument_t cmajor_sn_instrument_4 = {
	.volume_macro_len=9, .volume_macro_loop=255,
	.volume_macro_ptr=cmajor_sn_volume_macro_4,
	.fm_preset=255,
	.fm_patch={ 255, 255, 255, 255, 255, 255, 255, 255 }
};

static const unsigned char * const * const cmajor_sn_order_pointers[] = {
	cmajor_sn_orders_channel_0,
	cmajor_sn_orders_channel_1,
	cmajor_sn_orders_channel_2,
	cmajor_sn_orders_channel_3,
};

static const unsigned char * const cmajor_sn_orders_channel_0[] = {
	cmajor_sn_patterns_0_0,
};
static const unsigned char * const cmajor_sn_orders_channel_1[] = {
	cmajor_sn_patterns_1_0,
};
static const unsigned char * const cmajor_sn_orders_channel_2[] = {
	cmajor_sn_patterns_2_0,
};
static const unsigned char * const cmajor_sn_orders_channel_3[] = {
	cmajor_sn_patterns_3_0,
};


static const unsigned char cmajor_sn_patterns_0_0[] = {
	INSTRUMENT_CHANGE, 4, VOLUME_CHANGE, 144, NOTE_ON, 43, (END_LINE | 3), NOTE_ON, 52, (END_LINE | 1), NOTE_ON, 53, (END_LINE | 1), NOTE_ON, 55, (END_LINE | 3), NOTE_ON, 40, (END_LINE | 3), NOTE_ON, 43, (END_LINE | 1), NOTE_ON, 52, (END_LINE | 1), NOTE_ON, 43, (END_LINE | 1), NOTE_ON, 52, (END_LINE | 1), NOTE_ON, 55, (END_LINE | 3), NOTE_ON, 40, (END_LINE | 3), NOTE_ON, 43, (END_LINE | 3), NOTE_ON, 50, (END_LINE | 1), NOTE_ON, 52, (END_LINE | 1), NOTE_ON, 53, (END_LINE | 1), NOTE_ON, 55, (END_LINE | 1), NOTE_ON, 53, (END_LINE | 1), NOTE_ON, 52, (END_LINE | 1), NOTE_ON, 52, (END_LINE | 3), NOTE_ON, 52, (END_LINE | 1), NOTE_ON, 53, (END_LINE | 1), NOTE_ON, 52, (END_LINE | 1), NOTE_ON, 50, (END_LINE | 1), NOTE_ON, 48, (END_LINE | 1), NOTE_ON, 47, (END_LINE | 1)
};
static const unsigned char cmajor_sn_patterns_1_0[] = {
	INSTRUMENT_CHANGE, 3, ARPEGGIO, 92, VOLUME_CHANGE, 177, NOTE_ON, 24, (END_LINE | 15), ARPEGGIO, 88, NOTE_ON, 28, (END_LINE | 15), ARPEGGIO, 89, NOTE_ON, 26, (END_LINE | 15), ARPEGGIO, 88, NOTE_ON, 28, (END_LINE | 3), ARPEGGIO, 90, NOTE_ON, 26, (END_LINE | 3), ARPEGGIO, 76, NOTE_ON, 24, (END_LINE | 3), ARPEGGIO, 61, NOTE_ON, 23, (END_LINE | 3)
};
static const unsigned char cmajor_sn_patterns_2_0[] = {
	INSTRUMENT_CHANGE, 0, VOLUME_CHANGE, 208, NOTE_ON, 12, (END_LINE | 2), NOTE_ON, 12, (END_LINE | 2), NOTE_ON, 12, (END_LINE | 3), NOTE_ON, 19, (END_LINE | 1), NOTE_ON, 16, (END_LINE | 1), NOTE_ON, 19, (END_LINE | 1), NOTE_ON, 12, (END_LINE | 2), NOTE_ON, 12, (END_LINE | 2), NOTE_ON, 12, (END_LINE | 3), NOTE_ON, 21, (END_LINE | 1), NOTE_ON, 16, (END_LINE | 1), NOTE_ON, 21, (END_LINE | 1), NOTE_ON, 19, (END_LINE | 2), NOTE_ON, 19, (END_LINE | 2), NOTE_ON, 19, (END_LINE | 3), NOTE_ON, 19, (END_LINE | 1), NOTE_ON, 16, (END_LINE | 1), NOTE_ON, 19, (END_LINE | 1), NOTE_ON, 12, (END_LINE | 2), NOTE_ON, 12, (END_LINE | 2), NOTE_ON, 12, (END_LINE | 3), NOTE_ON, 19, (END_LINE | 1), NOTE_ON, 16, (END_LINE | 1), NOTE_ON, 19, (END_LINE | 1)
};
static const unsigned char cmajor_sn_patterns_3_0[] = {
	INSTRUMENT_CHANGE, 1, SN_NOISE_MODE, 228, VOLUME_CHANGE, 240, NOTE_ON, 2, (END_LINE | 1), NOTE_ON, 2, (END_LINE | 1), INSTRUMENT_CHANGE, 2, NOTE_ON, 0, (END_LINE | 1), INSTRUMENT_CHANGE, 1, NOTE_ON, 2, (END_LINE | 1), NOTE_ON, 2, (END_LINE | 1), NOTE_ON, 2, (END_LINE | 1), INSTRUMENT_CHANGE, 2, NOTE_ON, 0, (END_LINE | 1), INSTRUMENT_CHANGE, 1, NOTE_ON, 2, (END_LINE | 1), NOTE_ON, 2, (END_LINE | 1), NOTE_ON, 2, (END_LINE | 1), INSTRUMENT_CHANGE, 2, NOTE_ON, 0, (END_LINE | 1), INSTRUMENT_CHANGE, 1, NOTE_ON, 2, (END_LINE | 1), NOTE_ON, 2, (END_LINE | 1), NOTE_ON, 2, (END_LINE | 1), INSTRUMENT_CHANGE, 2, NOTE_ON, 0, (END_LINE | 1), NOTE_ON, 0, (END_LINE | 1), INSTRUMENT_CHANGE, 1, SN_NOISE_MODE, 228, NOTE_ON, 2, (END_LINE | 1), NOTE_ON, 2, (END_LINE | 1), INSTRUMENT_CHANGE, 2, NOTE_ON, 0, (END_LINE | 1), INSTRUMENT_CHANGE, 1, NOTE_ON, 2, (END_LINE | 1), NOTE_ON, 2, (END_LINE | 1), NOTE_ON, 2, (END_LINE | 1), INSTRUMENT_CHANGE, 2, NOTE_ON, 0, (END_LINE | 1), INSTRUMENT_CHANGE, 1, NOTE_ON, 2, (END_LINE | 1), NOTE_ON, 2, (END_LINE | 1), NOTE_ON, 2, (END_LINE | 1), INSTRUMENT_CHANGE, 2, NOTE_ON, 0, (END_LINE | 1), INSTRUMENT_CHANGE, 1, NOTE_ON, 2, (END_LINE | 1), NOTE_ON, 2, (END_LINE | 1), NOTE_ON, 2, (END_LINE | 1), INSTRUMENT_CHANGE, 2, NOTE_ON, 0, (END_LINE | 1), NOTE_ON, 0, (END_LINE | 1)
};


