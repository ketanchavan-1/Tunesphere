#include "SongService.h"
#include <fstream>
SongService::SongService(std::string path):path_(std::move(path)){}
void SongService::load(){ std::ifstream f(path_); if(!f) return; nlohmann::json j; f>>j; for(const auto& item:j) songs_.insertSong(item.get<Song>()); }
void SongService::save()const{ std::ofstream(path_)<<nlohmann::json(songs_.all()).dump(2); }
