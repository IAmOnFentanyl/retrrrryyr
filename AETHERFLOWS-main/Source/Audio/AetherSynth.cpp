#include "AetherSynth.h"
#include <cmath>

namespace aether {

AetherVoice::AetherVoice()
{
    adsr.setParameters(juce::ADSR::Parameters(0.01f, 0.1f, 0.8f, 0.3f));
}

bool AetherVoice::canPlaySound(juce::SynthesiserSound* sound) { return dynamic_cast<AetherSound*>(sound) != nullptr; }

void AetherVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int)
{
    level = velocity * 0.25;
    auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    auto samplesPerCycle = getSampleRate() / cyclesPerSecond;
    angleDelta = juce::MathConstants<double>::twoPi / samplesPerCycle;
    adsr.noteOn();
}

void AetherVoice::stopNote(float, bool allowTailOff)
{
    if (allowTailOff) adsr.noteOff();
    else clearCurrentNote();
}

void AetherVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (angleDelta != 0.0)
    {
        for (int i = 0; i < numSamples; ++i)
        {
            auto sample = (float)(std::sin(currentAngle) * level * adsr.getNextSample());
            for (auto ch = outputBuffer.getNumChannels(); --ch >= 0;)
                outputBuffer.addSample(ch, startSample + i, sample);
            currentAngle += angleDelta;
            if (!adsr.isActive()) { clearCurrentNote(); angleDelta = 0.0; break; }
        }
    }
}

AetherSynthProcessor::AetherSynthProcessor()
{
    for (int i = 0; i < 16; ++i) synth.addVoice(new AetherVoice());
    synth.addSound(new AetherSound());
}

void AetherSynthProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void AetherSynthProcessor::releaseResources() {}

void AetherSynthProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

} // namespace aether
