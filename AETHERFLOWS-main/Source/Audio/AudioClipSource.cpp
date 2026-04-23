#include <memory>
#include "AudioClipSource.h"

namespace aether {

AudioClipSource::AudioClipSource(const juce::File& file, juce::AudioFormatManager& formatManager)
{
    if (auto reader = formatManager.createReaderFor(file))
    {
        readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
    }
}

AudioClipSource::~AudioClipSource() {}

void AudioClipSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    if (readerSource)
        readerSource->prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void AudioClipSource::releaseResources()
{
    if (readerSource)
        readerSource->releaseResources();
}

void AudioClipSource::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource)
        readerSource->getNextAudioBlock(bufferToFill);
    else
        bufferToFill.clearActiveBufferRegion();
}

void AudioClipSource::setNextReadPosition(juce::int64 newPosition)
{
    if (readerSource)
        readerSource->setNextReadPosition(newPosition);
}

juce::int64 AudioClipSource::getNextReadPosition() const
{
    return readerSource ? readerSource->getNextReadPosition() : 0;
}

juce::int64 AudioClipSource::getTotalLength() const
{
    return readerSource ? readerSource->getTotalLength() : 0;
}

} // namespace aether
