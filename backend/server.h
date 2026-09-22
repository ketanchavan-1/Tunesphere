#pragma once
#include <crow.h>
#include "services/SongService.h"
#include "services/PlaylistService.h"
#include "services/UserService.h"
class TuneSphereServer { public: crow::SimpleApp app; SongService songs{"storage/songs.json"}; PlaylistService playlists{"storage/playlists.json"}; UserService user{"storage/users.json"}; void run(); };
void registerSongRoutes(TuneSphereServer&); void registerPlaylistRoutes(TuneSphereServer&); void registerUserRoutes(TuneSphereServer&);
