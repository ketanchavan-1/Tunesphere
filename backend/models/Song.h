#pragma once
#include <string>
#include <nlohmann/json.hpp>

struct Song {
    int id{};
    std::string title, artist, album, language, genre, audioPath, coverPath;
    int duration{}, year{};
};

inline void to_json(nlohmann::json& j, const Song& s) { j = {{"id",s.id},{"title",s.title},{"artist",s.artist},{"album",s.album},{"language",s.language},{"genre",s.genre},{"audioPath",s.audioPath},{"coverPath",s.coverPath},{"duration",s.duration},{"year",s.year}}; }
inline void from_json(const nlohmann::json& j, Song& s) { j.at("id").get_to(s.id); j.at("title").get_to(s.title); j.at("artist").get_to(s.artist); j.at("album").get_to(s.album); j.at("language").get_to(s.language); j.at("genre").get_to(s.genre); j.at("audioPath").get_to(s.audioPath); j.at("coverPath").get_to(s.coverPath); j.at("duration").get_to(s.duration); j.at("year").get_to(s.year); }
