#include <memory>
#include <vector>
#pragma once
#include <JuceHeader.h>
#include "AetherLookAndFeel.h"
#include "ClipComponent.h"
#include <vector>
#include <memory>

namespace aether {

class TimelineComponent : public juce::Component
{
public:
    TimelineComponent();
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    std::vector<std::unique_ptr<Clip>> demoClips;
    std::vector<std::unique_ptr<ClipComponent>> clipComponents;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TimelineComponent)
};

} // namespace aether
