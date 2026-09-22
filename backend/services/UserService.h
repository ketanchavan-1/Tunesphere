#pragma once
#include <string>
#include <vector>
class UserService { std::string path_; std::vector<int> favorites_, recent_; public: explicit UserService(std::string); void load(); void save()const; const std::vector<int>& favorites()const{return favorites_;} const std::vector<int>& recent()const{return recent_;} bool toggleFavorite(int); void played(int); };
