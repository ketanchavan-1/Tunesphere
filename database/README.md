# Persistence

TuneSphere uses JSON files in `backend/storage` for academic simplicity. `songs.json` is loaded into C++ nodes at startup; playlists, favorites, and recents are saved immediately after changes.
