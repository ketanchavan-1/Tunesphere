#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
struct Playlist { int id{}; std::string name; std::vector<int> songIds; };
inline void to_json(nlohmann::json& j, const Playlist& p) { j={{"id",p.id},{"name",p.name},{"songIds",p.songIds}}; }
inline void from_json(const nlohmann::json& j, Playlist& p) { j.at("id").get_to(p.id); j.at("name").get_to(p.name); j.value("songIds",std::vector<int>{}).swap(p.songIds); }
