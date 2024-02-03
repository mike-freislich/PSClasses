#pragma once
#include <stdlib.h>

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
