let searchTimer;

function initSearch() {
	document.querySelector('#search-input').addEventListener('input', event => {
	clearTimeout(searchTimer);
	searchTimer = setTimeout(async () => {
		const query = event.target.value.trim();
		if (!query) {
			UI.render(state.songs, 'Popular right now');
			return;
		}

		try {
			const results = await API.get(`songs/search?q=${encodeURIComponent(query)}`);
			UI.render(results, `Results for "${query}"`);
		} catch (error) {
			const needle = query.toLowerCase();
			const results = state.songs.filter(song =>
				[song.title, song.artist, song.album, song.language, song.genre]
					.some(value => value.toLowerCase().includes(needle))
			);
			UI.render(results, `Results for "${query}"`);
		}
	}, 180);
	});
}
