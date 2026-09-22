#include "UserService.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <algorithm>
UserService::UserService(std::string p):path_(std::move(p)){}
void UserService::load(){std::ifstream f(path_);if(f){nlohmann::json j;f>>j;favorites_=j.value("favorites",std::vector<int>{});recent_=j.value("recent",std::vector<int>{});}}
void UserService::save()const{std::ofstream(path_)<<nlohmann::json{{"favorites",favorites_},{"recent",recent_}}.dump(2);}
bool UserService::toggleFavorite(int id){auto it=std::find(favorites_.begin(),favorites_.end(),id);bool added=it==favorites_.end();if(added)favorites_.push_back(id);else favorites_.erase(it);save();return added;}
void UserService::played(int id){recent_.erase(std::remove(recent_.begin(),recent_.end(),id),recent_.end());recent_.insert(recent_.begin(),id);if(recent_.size()>20)recent_.pop_back();save();}
