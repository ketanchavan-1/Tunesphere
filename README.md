# TuneSphere — Music Without Boundaries

TuneSphere is a vanilla HTML/CSS/JavaScript music player backed by C++17 and Crow. Its source of truth is a **circular singly linked list**: each `Song` is stored in a dynamically allocated node and `tail->next` always points to `head`.

## Architecture

`Browser → Fetch /api → Crow route → service → CircularSongList node → JSON → HTML5 Audio`

The frontend never owns a hard-coded song catalogue. It requests song metadata, favorites, recents, navigation, and playlists from the backend. JSON files persist library metadata and user data; at startup songs are converted to linked-list nodes.

## Layout

```text
link_web/
├── frontend/                 # responsive vanilla UI
│   ├── index.html
│   ├── css/                  # layout, player, mobile rules
│   └── js/                   # API, rendering, playback, search, playlists
├── backend/
│   ├── models/               # Song, Playlist, User data models
│   ├── data_structures/      # CircularSongList (primary store)
│   ├── services/             # song, playlist, user persistence logic
│   ├── routes/               # REST endpoint registration
│   ├── storage/              # songs, playlists, favorites/recent JSON
│   ├── music/                # add legally licensed MP3s here
│   ├── tests/
│   └── CMakeLists.txt
└── database/                 # persistence explanation
```

## Prerequisites and build

Install CMake, a C++17 compiler, Git, and CMake-supported OpenSSL. CMake downloads Crow (which brings nlohmann/json) on its first configure.

```powershell
cd "link_web/backend"
cmake -S . -B build
cmake --build build --config Release
./build/Release/TuneSphere.exe # Windows multi-config generators
# or: ./build/TuneSphere       # Ninja / Linux / macOS
```

Open `http://localhost:8080`. Keep `backend` as the working directory, as shown above, so `storage/*.json` resolves correctly.

## Audio setup

No copyrighted audio is included. Add legally usable MP3s matching the `audioPath` values in `backend/storage/songs.json`, e.g. `backend/music/hindi/neon-raag.mp3`, and configure your Crow static-file route/proxy to expose `/music`. Update `songs.json` if you use different names. Covers are illustrative Unsplash URLs.

## REST API

| Endpoint | Purpose |
|---|---|
| `GET /api/songs` | list songs by linked-list traversal |
| `GET /api/songs/{id}` | retrieve one song |
| `POST /api/songs/play/{id}` | select current node and add to recent |
| `GET /api/songs/next` / `previous` | circular node navigation |
| `GET /api/songs/search?q=` | title/artist/metadata search |
| `GET /api/songs/language/{name}` | language filter |
| `GET /api/songs/genre/{name}` | genre filter |
| `POST`, `DELETE /api/songs` | create/remove songs |
| `GET`, `POST /api/favorites/{id}` | favorites/list toggle |
| `GET /api/recent` | recently played IDs |
| `GET`, `POST /api/playlists` | list/create playlist |
| `POST`, `DELETE /api/playlists/{id}/songs/{songId}` | modify playlist |
| `DELETE /api/playlists/{id}` | remove a playlist |
| `GET /api/debug/circular` | visualizer state: head/current/tail |

Examples: `curl http://localhost:8080/api/songs/next` and `curl "http://localhost:8080/api/songs/search?q=atlas"`.

## Why a circular linked list?

Insertion appends in O(1): the new node points to `head`, then the old tail points to it. `next` is O(1), including the last-to-first transition. In this singly linked implementation `previous`, search, filtering, and deletion are O(n), because traversal is needed to find a predecessor or match. `CircularSongList` has a destructor and deletes every node safely.

## Testing and troubleshooting

`backend/tests/CircularSongListTests.cpp` checks insertion, wraparound next/previous, deletion, and search; compile it with `CircularSongList.cpp` and Crow/nlohmann headers available. If CMake cannot download Crow, install Crow/nlohmann with vcpkg and pass the vcpkg toolchain file when configuring. If the UI says it cannot reach the server, confirm port 8080 is free and open the address served by the backend rather than opening `index.html` directly.

Future scope: login/authentication, SQLite, streaming byte-range support, and a real audio asset catalogue.
