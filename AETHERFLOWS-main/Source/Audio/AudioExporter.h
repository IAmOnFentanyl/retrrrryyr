#pragma once
#include <JuceHeader.h>
#include "AudioEngine.h"

namespace aether {

class AudioExporter
{
public:
    static bool exportProject(const juce::File& file, AudioEngine& engine, double duration);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioExporter)
};

} // namespace aether
