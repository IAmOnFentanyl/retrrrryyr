#include <algorithm>
#include "TrackManager.h"
#include <algorithm>
#include <utility>

namespace aether {

TrackManager::TrackManager(AudioEngine& engine) : audioEngine(engine)
{
}

TrackManager::~TrackManager()
{
}

Track* TrackManager::addTrack(const juce::String& name, TrackType type)
{
    auto track = std::make_unique<Track>(name, type);
    auto* trackPtr = track.get();

    // In a real implementation, we would add a processor node to the engine's graph
    // track->node = audioEngine.getGraph().addNode(...);

    tracks.push_back(std::move(track));
    return trackPtr;
}

void TrackManager::removeTrack(Track* track)
{
    tracks.erase(std::remove_if(tracks.begin(), tracks.end(),
        [track](const std::unique_ptr<Track>& t) { return t.get() == track; }), tracks.end());
}

} // namespace aether
