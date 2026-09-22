#include "../server.h"
using json=nlohmann::json; static crow::response ur(const json&j){return crow::response{j.dump()};}
void registerUserRoutes(TuneSphereServer&s){CROW_ROUTE(s.app,"/api/favorites")([&]{return ur(s.user.favorites());});CROW_ROUTE(s.app,"/api/favorites/<int>").methods(crow::HTTPMethod::Post)([&](int id){return ur({{"favorite",s.user.toggleFavorite(id)}});});CROW_ROUTE(s.app,"/api/recent")([&]{return ur(s.user.recent());});}
