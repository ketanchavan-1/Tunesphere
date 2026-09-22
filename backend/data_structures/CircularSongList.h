#pragma once
#include "../models/Song.h"
#include <vector>
#include <optional>

// Primary song store. Nodes, not a vector, own the complete collection.
class CircularSongList {
    struct Node { Song song; Node* next{nullptr}; explicit Node(Song value): song(std::move(value)) {} };
    Node* head_{nullptr}; Node* tail_{nullptr}; Node* current_{nullptr}; int count_{0};
public:
    ~CircularSongList();
    CircularSongList() = default;
    CircularSongList(const CircularSongList&) = delete;
    void insertSong(const Song& song);
    bool deleteSong(int id);
    Song* findSong(int id);
    std::optional<Song> setCurrent(int id);
    std::optional<Song> getNext();
    std::optional<Song> getPrevious();
    std::vector<Song> all() const;
    std::vector<Song> search(const std::string& query) const;
    std::vector<Song> filterLanguage(const std::string& language) const;
    std::vector<Song> filterGenre(const std::string& genre) const;
    int size() const { return count_; }
    nlohmann::json debug() const;
};
