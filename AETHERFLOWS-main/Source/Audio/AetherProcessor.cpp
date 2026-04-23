#include "AetherProcessor.h"

namespace aether {

AetherProcessor::AetherProcessor()
    : AudioProcessor(BusesProperties()
                     .withInput("Input", juce::AudioChannelSet::stereo(), true)
                     .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

AetherProcessor::~AetherProcessor() {}

void AetherProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {}
void AetherProcessor::releaseResources() {}
void AetherProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {}

} // namespace aether
