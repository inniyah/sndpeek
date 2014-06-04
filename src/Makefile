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
CFLAGS=-D__LINUX_ALSA__ -D__LITTLE_ENDIAN__
LIBS=-L/usr/X11R6/lib -lglut -lGL -lGLU -lasound -lXmu -lX11 -lXext -lXi -lm -lsndfile -lpthread

#JACK
#CFLAGS=-D__LINUX_JACK__ -D__LITTLE_ENDIAN__
#LIBS=-L/usr/X11R6/lib -lpthread -lstdc++ -lglut -lGL -lGLU -lasound -ljack -lXmu -lX11 -lXext -lXi -lm -lsndfile -lpthread

OPT_CFLAGS=-O3

OBJS=chuck_fft.o RtAudio.o Thread.o sndpeek.o Stk.o \
	Centroid.o DownSampler.o Flux.o LPC.o MFCC.o RMS.o Rolloff.o \
	System.o fvec.o AutoCorrelation.o Communicator.o Hamming.o \
	MagFFT.o NormRMS.o MarSignal.o fmatrix.o dywapitchtrack.o

PROGRAM=bin/sndpeek

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	mkdir -p bin
	$(CPP) -o $@ $(OBJS) $(LIBS)

%.o: $(SNDPEEK_DIR)/%.cpp
	$(CC) $(INCLUDES) $(CFLAGS) $(OPT_CFLAGS) -o $@ -c $+

%.o: $(SNDPEEK_DIR)/%.c
	$(CC) $(INCLUDES) $(CFLAGS) $(OPT_CFLAGS) -o $@ -c $+

%.o: $(MARSYAS_DIR)/%.cpp
	$(CC) $(INCLUDES) $(CFLAGS) $(OPT_CFLAGS) -o $@ -c $+

%.o: $(MARSYAS_DIR)/%.c
	$(CC) $(INCLUDES) $(CFLAGS) $(OPT_CFLAGS) -o $@ -c $+

%.o: $(DYWAPITCHTRACK_DIR)/%.cpp
	$(CC) $(INCLUDES) $(CFLAGS) $(OPT_CFLAGS) -o $@ -c $+

%.o: $(DYWAPITCHTRACK_DIR)/%.c
	$(CC) $(INCLUDES) $(CFLAGS) $(OPT_CFLAGS) -o $@ -c $+

clean:
	rm -f $(OBJS)
	rm -f $(PROGRAM)
	rm -f *.o *.a *~
