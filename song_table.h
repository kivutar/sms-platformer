
// Song tables

// References to Songs which will be matched up at link time
extern song_data_t const cmajor_sn;

// SN Song table
// SONG_DEF(SONG_LABEL, SONG_BANK)
song_t const song_table_sn[] = {
	SONG_DEF(cmajor_sn, 3),
};

