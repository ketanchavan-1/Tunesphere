#include "PlaylistService.h"
#include <fstream>
#include <algorithm>
PlaylistService::PlaylistService(std::string p):path_(std::move(p)){}
void PlaylistService::load(){std::ifstream f(path_);if(f){nlohmann::json j;f>>j;lists_=j.get<std::vector<Playlist>>();}}
void PlaylistService::save()const{std::ofstream(path_)<<nlohmann::json(lists_).dump(2);}
Playlist* PlaylistService::find(int id){for(auto&p:lists_)if(p.id==id)return&p;return nullptr;}
Playlist PlaylistService::create(std::string name){int id=1;for(auto&p:lists_)id=std::max(id,p.id+1);lists_.push_back({id,std::move(name),{}});save();return lists_.back();}
bool PlaylistService::erase(int id){auto it=std::remove_if(lists_.begin(),lists_.end(),[&](auto&p){return p.id==id;});if(it==lists_.end())return false;lists_.erase(it,lists_.end());save();return true;}
bool PlaylistService::addSong(int id,int song){auto*p=find(id);if(!p)return false;if(std::find(p->songIds.begin(),p->songIds.end(),song)==p->songIds.end())p->songIds.push_back(song);save();return true;}
bool PlaylistService::removeSong(int id,int song){auto*p=find(id);if(!p)return false;p->songIds.erase(std::remove(p->songIds.begin(),p->songIds.end(),song),p->songIds.end());save();return true;}
