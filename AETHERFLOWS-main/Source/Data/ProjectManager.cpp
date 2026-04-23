#include "ProjectManager.h"

namespace aether {

ProjectManager::ProjectManager(TrackManager& tm) : trackManager(tm) {}

ProjectManager::~ProjectManager() {}

bool ProjectManager::saveProject(const juce::File& file)
{
    auto yaml = generateYaml();
    return file.replaceWithText(yaml);
}

bool ProjectManager::loadProject(const juce::File& file)
{
    if (!file.existsAsFile()) return false;
    parseYaml(file.loadFileAsString());
    return true;
}

juce::String ProjectManager::generateYaml()
{
    juce::String out = "version: 0.1\n";
    out << "tracks:\n";

    for (const auto& track : trackManager.getTracks())
    {
        out << "  - name: " << track->getName() << "\n";
        out << "    type: " << (int)track->getType() << "\n";
        out << "    volume: " << track->getVolume() << "\n";
        out << "    muted: " << (track->getMuted() ? "true" : "false") << "\n";
    }

    return out;
}

void ProjectManager::parseYaml(const juce::String& content)
{
    // Basic YAML-like parser for the specific format we generate
    auto lines = juce::StringArray::fromLines(content);

    juce::String currentTrackName;
    TrackType currentType = TrackType::Audio;
    float currentVolume = 1.0f;
    bool currentMuted = false;

    for (auto line : lines)
    {
        line = line.trim();
        if (line.startsWith("- name:"))
        {
            if (currentTrackName.isNotEmpty())
            {
                auto* t = trackManager.addTrack(currentTrackName, currentType);
                t->setVolume(currentVolume);
                t->setMuted(currentMuted);
            }
            currentTrackName = line.fromFirstOccurrenceOf("- name:", false, false).trim();
        }
        else if (line.startsWith("type:"))
        {
            currentType = (TrackType)line.fromFirstOccurrenceOf("type:", false, false).trim().getIntValue();
        }
        else if (line.startsWith("volume:"))
        {
            currentVolume = line.fromFirstOccurrenceOf("volume:", false, false).trim().getFloatValue();
        }
        else if (line.startsWith("muted:"))
        {
            currentMuted = line.fromFirstOccurrenceOf("muted:", false, false).trim() == "true";
        }
    }

    // Last track
    if (currentTrackName.isNotEmpty())
    {
        auto* t = trackManager.addTrack(currentTrackName, currentType);
        t->setVolume(currentVolume);
        t->setMuted(currentMuted);
    }
}

} // namespace aether
