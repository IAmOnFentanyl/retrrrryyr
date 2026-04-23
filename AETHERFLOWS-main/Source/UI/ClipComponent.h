#pragma once
#include <JuceHeader.h>
#include "../Core/Clip.h"
#include "AetherLookAndFeel.h"

namespace aether {

class ClipComponent : public juce::Component
{
public:
    ClipComponent(Clip& clip);
    void paint(juce::Graphics& g) override;

private:
    Clip& clip;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ClipComponent)
};

} // namespace aether
