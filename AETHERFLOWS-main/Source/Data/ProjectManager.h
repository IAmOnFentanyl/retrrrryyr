#pragma once
#include <JuceHeader.h>
#include "../Core/TrackManager.h"

namespace aether {

class ProjectManager
{
public:
    ProjectManager(TrackManager& tm);
    ~ProjectManager();

    bool saveProject(const juce::File& file);
    bool loadProject(const juce::File& file);

private:
    TrackManager& trackManager;

    // Minimal YAML-like serialization (since we don't have yaml-cpp yet)
    juce::String generateYaml();
    void parseYaml(const juce::String& content);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProjectManager)
};

} // namespace aether
