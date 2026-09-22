async function createPlaylist(){const name=prompt('Playlist name:');if(name?.trim())await API.send('playlists','POST',{name:name.trim()});}
