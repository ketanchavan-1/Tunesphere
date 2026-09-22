#include "../server.h"
using json=nlohmann::json;
static crow::response reply(const json& j,int code=200){return crow::response{code,j.dump()};}
void registerSongRoutes(TuneSphereServer& s){
 CROW_ROUTE(s.app,"/api/songs").methods(crow::HTTPMethod::Get)([&]{return reply(s.songs.all());});
 CROW_ROUTE(s.app,"/api/songs/<int>")([&](int id){auto*p=s.songs.find(id);return p?reply(*p):reply({{"error","Song not found"}},404);});
 CROW_ROUTE(s.app,"/api/songs/play/<int>").methods(crow::HTTPMethod::Post)([&](int id){auto song=s.songs.select(id);if(!song)return reply({{"error","Song not found"}},404);s.user.played(id);return reply(*song);});
 CROW_ROUTE(s.app,"/api/songs/next")([&]{auto song=s.songs.next();return song?reply(*song):reply({{"error","No songs"}},404);});
 CROW_ROUTE(s.app,"/api/songs/previous")([&]{auto song=s.songs.previous();return song?reply(*song):reply({{"error","No songs"}},404);});
 CROW_ROUTE(s.app,"/api/songs/search")([&](const crow::request& r){return reply(s.songs.search(r.url_params.get("q")?r.url_params.get("q"):""));});
 CROW_ROUTE(s.app,"/api/songs/language/<string>")([&](std::string v){return reply(s.songs.language(v));});
 CROW_ROUTE(s.app,"/api/songs/genre/<string>")([&](std::string v){return reply(s.songs.genre(v));});
 CROW_ROUTE(s.app,"/api/debug/circular")([&]{return reply(s.songs.debug());});
 CROW_ROUTE(s.app,"/api/songs").methods(crow::HTTPMethod::Post)([&](const crow::request&r){try{auto song=json::parse(r.body).get<Song>();s.songs.add(song);s.songs.save();return reply(song,201);}catch(...){return reply({{"error","Invalid song JSON"}},400);}});
 CROW_ROUTE(s.app,"/api/songs/<int>").methods(crow::HTTPMethod::Delete)([&](int id){if(!s.songs.remove(id))return reply({{"error","Song not found"}},404);s.songs.save();return reply({{"deleted",id}});}); }
