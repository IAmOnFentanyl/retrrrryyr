#include "AetherEffects.h"

namespace aether {

// EQ Implementation
AetherEQ::AetherEQ() : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo()).withOutput("Output", juce::AudioChannelSet::stereo())) {}
void AetherEQ::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec { sampleRate, (juce::uint32) samplesPerBlock, 2 };
    filterChain.prepare(spec);
}
void AetherEQ::releaseResources() {}
void AetherEQ::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block(buffer);
    filterChain.process(juce::dsp::ProcessContextReplacing<float>(block));
}

// Compressor Implementation
AetherCompressor::AetherCompressor() : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo()).withOutput("Output", juce::AudioChannelSet::stereo())) {}
void AetherCompressor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec { sampleRate, (juce::uint32) samplesPerBlock, 2 };
    compressor.prepare(spec);
}
void AetherCompressor::releaseResources() {}
void AetherCompressor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block(buffer);
    compressor.process(juce::dsp::ProcessContextReplacing<float>(block));
}

} // namespace aether
