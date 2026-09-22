#include "server.h"
#include <filesystem>
#include <fstream>
#include <iostream>
static bool hasSuffix(const std::string& value,const std::string& suffix){return value.size()>=suffix.size()&&value.compare(value.size()-suffix.size(),suffix.size(),suffix)==0;}
static crow::response serveFile(const std::string& path){
	std::ifstream file(path,std::ios::binary);
	if(!file) return crow::response(404);
	std::string body((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
	crow::response response{std::move(body)};
	if(hasSuffix(path,".html")) response.set_header("Content-Type","text/html");
	else if(hasSuffix(path,".css")) response.set_header("Content-Type","text/css");
	else if(hasSuffix(path,".js")) response.set_header("Content-Type","application/javascript");
	else if(hasSuffix(path,".mp3")) response.set_header("Content-Type","audio/mpeg");
	return response;
}
void TuneSphereServer::run(){ songs.load();playlists.load();user.load();registerSongRoutes(*this);registerPlaylistRoutes(*this);registerUserRoutes(*this); const auto frontend=std::filesystem::absolute("../frontend").lexically_normal().string(); const auto music=std::filesystem::absolute("music").lexically_normal().string(); CROW_ROUTE(app,"/")([frontend]{return serveFile(frontend+"/index.html");}); CROW_ROUTE(app,"/music/<path>")([music](std::string file){return serveFile(music+"/"+file);}); CROW_ROUTE(app,"/<path>")([frontend](std::string file){return serveFile(frontend+"/"+file);}); std::cout<<"TuneSphere: http://localhost:8080 | songs: "<<songs.all().size()<<"\n";app.port(8080).multithreaded().run(); }
