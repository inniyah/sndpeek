/* dywapitchtrack.h
 
 Dynamic Wavelet Algorithm Pitch Tracking library
 Released under the MIT open source licence
 
 Copyright (c) 2010 Antoine Schmitt
  
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

/* Documentation
 
 The dywapitchtrack library computes the pitch of an audio stream in real time.
 
 The pitch is the main frequency of the waveform (the 'note' being played or sung).
 It is expressed as a float in Hz.
 
 Unlike the human ear, pitch detection is difficult to achieve for computers. Many
 algorithms have been designed and experimented, but there is no 'best' algorithm.
 They all depend on the context and the tradeoffs acceptable in terms of speed and
 latency. The context includes the quality and 'cleanness' of the audio : obviously
 polyphonic sounds (multiple instruments playing different notes at the same time)
 are extremely difficult to track, percussive or noisy audio has no pitch, most
 real-life audio have some noisy moments, some instruments have a lot of harmonics,
 etc...
 
 The dywapitchtrack is based on a custom-tailored algorithm which is of very high quality:
 both very accurate (precision < 0.05 semitones), very low latency (< 23 ms) and
 very low error rate. It has been  thoroughly tested on human voice.
 
 It can best be described as a dynamic wavelet algorithm (dywa):
 
 The heart of the algorithm is a very powerful wavelet algorithm, described in a paper
 by Eric Larson and Ross Maddox : "Real-Time Time-Domain Pitch Tracking Using Wavelets"
 http://online.physics.uiuc.edu/courses/phys498pom/NSF_REU_Reports/2005_reu/Real-Time_Time-Domain_Pitch_Tracking_Using_Wavelets.pdf
 
 This central algorithm has been improved by adding dynamic tracking, to reduce the
 common problems of frequency-halving and voiced/unvoiced errors. This dynamic tracking
 explains the need for a tracking structure (dywapitchtracker). The dynamic tracking assumes
 that the main function dywapitch_computepitch is called repeatedly, as it follows the pitch
 over time and makes assumptions about human voice capabilities and reallife conditions
 (as documented inside the code).
 
 Note : The algorithm currently assumes a 44100Hz audio sampling rate. If you use a different
 samplerate, you can just multiply the resulting pitch by the ratio between your samplerate and 44100.
*/

/* Usage

 // Allocate your audio buffers and start the audio stream.
 // Allocate a 'dywapitchtracker' structure.
 // Start the pitch tracking by calling 'dywapitch_inittracking'.
 dywapitchtracker pitchtracker;
 dywapitch_inittracking(&pitchtracker);
 
 // For each available audio buffer, call 'dywapitch_computepitch'
 double thepitch = dywapitch_computepitch(&pitchtracker, samples, start, count);
 
*/

#ifndef DYWAPITCHTRACK_H_1A1BA0C2_EB8C_11E3_AC6E_10FEED04CD1C
#define DYWAPITCHTRACK_H_1A1BA0C2_EB8C_11E3_AC6E_10FEED04CD1C

class dywapitchtracker {
	public:
		typedef float Sample;

		dywapitchtracker() : _prevPitch(-1.0), _pitchConfidence(-1) {
		}

		void init() {
			_prevPitch = -1.;
			_pitchConfidence = -1;
		}

	// returns the number of samples needed to compute pitch for fequencies equal and above the given minFreq (in Hz)
	// useful to allocate large enough audio buffer 
	// ex : for frequencies above 130Hz, you need 1024 samples (assuming a 44100 Hz samplerate)
	int neededSampleCount(int minFreq);

	static unsigned int getMidiNoteFromFreq(double freq, const double ref_freq = 440.0) ;

	static double getFreqFromMidiNote(unsigned int midi_note, const double ref_freq = 440.0);

	static const char * getMidiNoteName(unsigned int midi_note) ;

	// computes the pitch. Pass the inited dywapitchtracker structure
	// samples : a pointer to the sample buffer
	// startsample : the index of teh first sample to use in teh sample buffer
	// samplecount : the number of samples to use to compte the pitch
	// return 0.0 if no pitch was found (sound too low, noise, etc..)
	double computePitch(const Sample * samples, int startsample, int samplecount, int samplerate=44100);

		double getPrevPitch() const {
			return _prevPitch;
		};

		int getPitchConfidence() const {
			return _pitchConfidence;
		};

	protected:
		double computeWaveletPitch(const Sample * samples, int startsample, int samplecount);
		double dynamicProcess(double pitch);

	private:
		double _prevPitch;
		int _pitchConfidence;
		int _sampleRate;
};

#endif // DYWAPITCHTRACK_H_1A1BA0C2_EB8C_11E3_AC6E_10FEED04CD1C
