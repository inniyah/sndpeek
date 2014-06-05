CC=gcc
CPP=g++
SNDPEEK_DIR=sndpeek
MARSYAS_DIR=marsyas
DYWAPITCHTRACK_DIR=dywapitchtrack
INCLUDES=-I$(SNDPEEK_DIR) -I$(MARSYAS_DIR) -I$(DYWAPITCHTRACK_DIR)

#OSS
#CFLAGS=-D__LINUX_OSS__ -D__LITTLE_ENDIAN__
#LIBS=-L/usr/X11R6/lib -lpthread -lstdc++ -lglut -lGL -lGLU -lXmu -lX11 -lXext -lXi -lm -lsndfile -lpthread

#ALSA
#CFLAGS=-D__LINUX_ALSA__ -D__LITTLE_ENDIAN__
#LIBS=-L/usr/X11R6/lib -lglut -lGL -lGLU -lasound -lXmu -lX11 -lXext -lXi -lm -lsndfile -lpthread

#JACK
#CFLAGS=-D__LINUX_JACK__ -D__LITTLE_ENDIAN__
#LIBS=-L/usr/X11R6/lib -lstdc++ -lglut -lGL -lGLU -lasound -ljack -lXmu -lX11 -lXext -lXi -lm -lsndfile -lpthread

#OBJS=chuck_fft.o RtAudio.o Thread.o sndpeek.o Stk.o \
#	Centroid.o DownSampler.o Flux.o LPC.o MFCC.o RMS.o Rolloff.o \
#	System.o fvec.o AutoCorrelation.o Communicator.o Hamming.o \
#	MagFFT.o NormRMS.o MarSignal.o fmatrix.o dywapitchtrack.o

FLTK_CONFIG=--use-glut --use-gl
FLTK_CFLAGS=$(shell fltk-config $(FLTK_CONFIG) --cflags)
FLTK_LIBS=$(shell fltk-config $(FLTK_CONFIG) --ldflags)

PKG_CONFIG=sndfile gl glu
PKG_CONFIG_CFLAGS=$(shell pkg-config --cflags $(PKG_CONFIG))
PKG_CONFIG_LIBS=$(shell pkg-config --libs $(PKG_CONFIG))

BASE_CFLAGS=$(INCLUDES) $(PKG_CONFIG_CFLAGS) $(FLTK_CFLAGS)
BASE_LIBS=$(PKG_CONFIG_LIBS) $(FLTK_LIBS)

CFLAGS=-g -Wall -O2
LIBS=-lstdc++ -lglut -lXmu -lX11 -lXext -lXi -lm -lpthread $(PKG_CONFIG_LIBS) $(FLTK_LIBS)
OBJS=main.o

PROGRAM=bin/sndpeek

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	mkdir -p bin
	$(CPP) -o $@ $(OBJS) $(LIBS) $(BASE_LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(BASE_CFLAGS) -o $@ -c $+

%.o: %.c
	$(CC) $(CFLAGS) $(BASE_CFLAGS) -o $@ -c $+

%.o: $(SNDPEEK_DIR)/%.cpp
	$(CC) $(CFLAGS) $(BASE_CFLAGS) -o $@ -c $+

%.o: $(SNDPEEK_DIR)/%.c
	$(CC) $(CFLAGS) $(BASE_CFLAGS) -o $@ -c $+

%.o: $(MARSYAS_DIR)/%.cpp
	$(CC) $(CFLAGS) $(BASE_CFLAGS) -o $@ -c $+

%.o: $(MARSYAS_DIR)/%.c
	$(CC) $(CFLAGS) $(BASE_CFLAGS) -o $@ -c $+

%.o: $(DYWAPITCHTRACK_DIR)/%.cpp
	$(CC) $(CFLAGS) $(BASE_CFLAGS) -o $@ -c $+

%.o: $(DYWAPITCHTRACK_DIR)/%.c
	$(CC) $(CFLAGS) $(BASE_CFLAGS) -o $@ -c $+

clean:
	rm -f $(OBJS)
	rm -f $(PROGRAM)
	rm -f *.o *.a *~
