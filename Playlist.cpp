#include "Playlist.h"
#include <iostream>

PlaylistNode::PlaylistNode()
    : uniqueID("none"), songName("none"), artistName("none"),
      songLength(0), nextNodePtr(nullptr) {}

PlaylistNode::PlaylistNode(const std::string& id, const std::string& name,
                           const std::string& artist, int length)
    : uniqueID(id), songName(name), artistName(artist),
      songLength(length), nextNodePtr(nullptr) {}

void PlaylistNode::InsertAfter(PlaylistNode* node) {
    node->nextNodePtr = this->nextNodePtr;
    this->nextNodePtr = node;
}

void PlaylistNode::SetNext(PlaylistNode* node) {
    nextNodePtr = node;
}

const std::string& PlaylistNode::GetID() const {
    return uniqueID;
}

const std::string& PlaylistNode::GetSongName() const {
    return songName;
}

const std::string& PlaylistNode::GetArtistName() const {
    return artistName;
}

int PlaylistNode::GetSongLength() const {
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() {
    return nextNodePtr;
}

const PlaylistNode* PlaylistNode::GetNext() const {
    return nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() const {
    std::cout << "Unique ID: " << uniqueID << std::endl;
    std::cout << "Song Name: " << songName << std::endl;
    std::cout << "Artist Name: " << artistName << std::endl;
    std::cout << "Song Length (in seconds): " << songLength << std::endl;
}
