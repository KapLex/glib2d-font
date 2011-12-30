PSPSDK = $(shell psp-config --pspsdk-path)
PSPDIR = $(shell psp-config --psp-prefix)

CFLAGS = -O2 -G0

OBJS = src/glib2d_font_ascii.o src/glib2d_font_hzk.o
TARGET_LIB = libglib2d_font.a

include $(PSPSDK)/lib/build.mak

install: all
	mkdir -p $(PSPDIR)/include $(PSPDIR)/lib
	cp src/*.h $(PSPDIR)/include
	cp *.a $(PSPDIR)/lib
