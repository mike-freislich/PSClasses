#pragma once

class AudioConnection;
class AudioStream;

#define AUDIO_BLOCK_SAMPLES 128

typedef struct audio_block_struct
{
	uint8_t ref_count;
	uint8_t reserved1;
	uint16_t memory_pool_index;
	int16_t data[AUDIO_BLOCK_SAMPLES];
} audio_block_t;

class AudioConnection
{
public:
	AudioConnection() {}
	AudioConnection(AudioStream &source, AudioStream &destination)
		: AudioConnection() { connect(source, destination); }
	AudioConnection(AudioStream &source, unsigned char sourceOutput,
					AudioStream &destination, unsigned char destinationInput)
		: AudioConnection() { connect(source, sourceOutput, destination, destinationInput); }
	friend class AudioStream;
	~AudioConnection() {}
	int disconnect(void) { return 0; }
	int connect(void) { return 0; }
	int connect(AudioStream &source, AudioStream &destination) { return connect(source, 0, destination, 0); };
	int connect(AudioStream &source, unsigned char sourceOutput,
				AudioStream &destination, unsigned char destinationInput) { return 0; }

protected:
	AudioStream *src; // can't use references as...
	AudioStream *dst; // ...they can't be re-assigned!
	unsigned char src_index;
	unsigned char dest_index;
	AudioConnection *next_dest; // linked list of connections from one source
	bool isConnected;
};

class AudioStream
{
public:
	AudioStream(unsigned char ninput, audio_block_t **iqueue) {}
	static void initialize_memory(audio_block_t *data, unsigned int num) {}
	float processorUsage(void) { return 0; }
	float processorUsageMax(void) { return 0; }
	void processorUsageMaxReset(void) {}
	virtual bool isActive(void) { return false; }	// this was edited to be virtual to enable polymorphism
	uint16_t cpu_cycles;
	uint16_t cpu_cycles_max;
	static uint16_t cpu_cycles_total;
	static uint16_t cpu_cycles_total_max;
	static uint16_t memory_used;
	static uint16_t memory_used_max;
};


class AUMockObject : public AudioStream
{
public:
    AUMockObject() : AudioStream(1, NULL) {}
    virtual void update(void) {}
};

class AudioEffectEnvelope : public AudioStream
{
public:
    AudioEffectEnvelope() : AudioStream(1, NULL) {}
    void noteOn() {}
    void noteOff() {}
    void delay(float milliseconds) { LOG("delay set to : " << milliseconds); }
    void attack(float milliseconds) { LOG("attack set to : " << milliseconds); }
    void hold(float milliseconds) { LOG("hold set to : " << milliseconds); }
    void decay(float milliseconds) { LOG("decay set to : " << milliseconds); }
    void sustain(float level) { LOG("sustain set to : " << level); }
    void release(float milliseconds) { LOG("release set to : " << milliseconds); }
    void releaseNoteOn(float milliseconds) {}
    bool isActive() {return false; }
    bool isSustain() { return false; }
    virtual void update(void) {}
};

class AudioSynthWaveformDc : public AudioStream
{
public:
    AudioSynthWaveformDc() : AudioStream(0, NULL) {}
    void amplitude(float n) { LOG("DC-amplitude set to : " << n);}
    void amplitude(float n, float milliseconds) { }
    float read(void) { return 0; }
    virtual void update(void) {}
};

class AudioMixer4 : public AudioStream
{
public:
    AudioMixer4(void) : AudioStream(4, NULL) {}
    virtual void update(void) {}
    void gain(unsigned int channel, float gain) { LOG("mixer channel: " << channel <<  ", set to : " << gain); }
};

class AudioAmplifier : public AudioStream
{
public:
    AudioAmplifier(void) : AudioStream(1, NULL) {}
    virtual void update(void) {}
    void gain(float n) {LOG("gain set to : " << n);}
private:
};

class AudioSynthWaveformModulated : public AudioStream
{
public:
    AudioSynthWaveformModulated(void) : AudioStream(2, NULL) {}
    void frequency(float freq) { LOG("WaveformModulated frequency set to " << freq); }
    void amplitude(float n) { LOG("WaveformModulated amplitude set to " << n); }
    void offset(float n) {}
    void begin(short t_type) {
		LOG("wioefh oiw eofij woief jowiej foijwoiefj owij efoiwj oe fj");
	}
    void begin(float t_amp, float t_freq, short t_type) {
		LOG("WaveFormModulated.begin( amp=" << t_amp << ", freq=" << t_freq << ", type=" << t_type << ")");
	}
    void arbitraryWaveform(const int16_t *data, float maxFreq) {}
    void frequencyModulation(float octaves) {}
    void phaseModulation(float degrees) {}
    virtual void update(void) {}
};

class AudioEffectMultiply : public AudioStream
{
public:
    AudioEffectMultiply() : AudioStream(2, NULL) {}
    virtual void update(void) {}
};

class AudioSynthWaveform : public AudioStream
{
public:
    AudioSynthWaveform(void) : AudioStream(0, NULL) {}
    void frequency(float freq) {LOG("WaveForm-freq set to : " << freq);}
    void phase(float angle) {}
    void amplitude(float n) {LOG("WaveForm-amp set to : " << n);}
    void offset(float n) {}   
    void pulseWidth(float n) {}
    void begin(short t_type) {}
    void begin(float t_amp, float t_freq, short t_type) {
		LOG("WaveForm.begin( amp=" << t_amp << ", freq=" << t_freq << ", type=" << t_type << ")");
	}
    void arbitraryWaveform(const int16_t *data, float maxFreq) {}
    virtual void update(void) {}
};

class AudioSynthNoiseWhite : public AudioStream
{
public:
	AudioSynthNoiseWhite() : AudioStream(0, NULL) {}
	void amplitude(float n) {LOG("WhiteNoise-amp set to : " << n);}	
	virtual void update(void) {}
};

class AudioSynthNoisePink : public AudioStream
{
public:
	AudioSynthNoisePink() : AudioStream(0, NULL) {}	
	void amplitude(float n) {LOG("PinkNoise-amp set to : " << n);}
	virtual void update(void) {}
};

class AudioEffectWaveshaper : public AudioStream
{
  public:
    AudioEffectWaveshaper(void): AudioStream(1, NULL) {}
    ~AudioEffectWaveshaper() {}
    virtual void update(void) {}
    void shape(float* waveshape, int length) {}
};

class AudioFilterStateVariable: public AudioStream
{
public:
	AudioFilterStateVariable() : AudioStream(2, NULL) {}
	void frequency(float freq) {LOG("SVFilter-freq set to : " << freq);}
	void resonance(float q) {LOG("SVFilter-res set to : " << q);}
	void octaveControl(float n) {LOG("SVFilter-octaves set to : " << n);}
	virtual void update(void) {}
};

enum AudioFilterLadderInterpolation {
	LADDER_FILTER_INTERPOLATION_LINEAR,
	LADDER_FILTER_INTERPOLATION_FIR_POLY
};
class AudioFilterLadder: public AudioStream
{
public:
	AudioFilterLadder() : AudioStream(3, NULL) { };
	void frequency(float FC) {LOG("LadderFilter-freq set to : " << FC);}
	void resonance(float reson) {LOG("LadderFilter-res set to : " << reson);}
	void octaveControl(float octaves) {LOG("LadderFilter-octaves set to : " << octaves);}
	void passbandGain(float passbandgain) {}
	void inputDrive(float drv) {}
	void interpolationMethod(AudioFilterLadderInterpolation im) {}
	virtual void update(void) {}
};

class AudioAnalyzePeak : public AudioStream
{
public:
	AudioAnalyzePeak(void) : AudioStream(1, NULL) {}
	bool available(void) { return false; }
	float read(void) { return 0; }
	float readPeakToPeak(void) {return 0;}
	virtual void update(void) {}
};

class AudioOutputUSB : public AudioStream
{
public:
	AudioOutputUSB(void) : AudioStream(2, NULL) {  }
	virtual void update(void) {}
	void begin(void) {}
	friend unsigned int usb_audio_transmit_callback(void) { return 0;}
};