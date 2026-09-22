#pragma once
#include "../models/Playlist.h"
#include <vector>
#include <string>
class PlaylistService { std::string path_; std::vector<Playlist> lists_; public: explicit PlaylistService(std::string p); void load(); void save()const; const std::vector<Playlist>& all()const{return lists_;} Playlist* find(int); Playlist create(std::string); bool erase(int); bool addSong(int,int); bool removeSong(int,int); };
