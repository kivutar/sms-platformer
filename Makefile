CC=sdcc
DEVKITSMS_BASE=$(HOME)/devkitSMS
IHX2SMS=$(DEVKITSMS_BASE)/ihx2sms/Linux/ihx2sms
MAKESMS=$(DEVKITSMS_BASE)/makesms/Linux/makesms
SMSLIB_BASE=$(DEVKITSMS_BASE)/SMSlib
SMSLIB_INCDIR=$(SMSLIB_BASE)/src
PEEP_RULES=$(SMSLIB_BASE)/src/peep-rules.txt
CRT0=$(DEVKITSMS_BASE)/crt0/crt0_sms.rel
SMSLIB_LIB=$(SMSLIB_BASE)/SMSlib.lib
BANJO_INCDIR=music_driver_sdas

CFLAGS=-mz80 -I$(SMSLIB_INCDIR) -I$(BANJO_INCDIR) --peep-file $(PEEP_RULES)
LDFLAGS=-mz80 --no-std-crt0 --data-loc 0xC000

PROGNAME=platformer

OBJS=main.rel bank2.rel music_driver_sdas/lib/music_driver_fm_drums.rel cmajor_sn.rel

all: $(PROGNAME).sms

%.rel: %.c
	$(CC) $(CFLAGS) -c $<

%.rel: %.c %.h
	$(CC) $(CFLAGS) -c $<

$(PROGNAME).ihx: $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $(CRT0) $(SMSLIB_LIB) $^

$(PROGNAME).sms: $(PROGNAME).ihx
	$(IHX2SMS) $< $@

clean:
	rm -f *.rel *.ihx *.asm *.sym *.lst *.noi *.lk *.map *.sms *.gg

# When a linking error occurs, sdcc returns an error and make fails. However
# a .ihx output file still gets created. This leads to make thinking that the .ihx
# file is up to date the next time it runs... This forces linking to take place
# every time make is called.
.PHONY: $(PROGNAME).ihx

