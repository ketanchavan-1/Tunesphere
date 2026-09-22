#include "CircularSongList.h"
#include <algorithm>
#include <cctype>

CircularSongList::~CircularSongList() { while (count_) deleteSong(head_->song.id); }
void CircularSongList::insertSong(const Song& song) {
    auto* node = new Node(song);
    if (!head_) { head_=tail_=current_=node; node->next=node; }
    else { node->next=head_; tail_->next=node; tail_=node; }
    ++count_;
}
bool CircularSongList::deleteSong(int id) {
    if (!head_) return false;
    Node* previous=tail_; Node* node=head_;
    do { if (node->song.id==id) break; previous=node; node=node->next; } while (node!=head_);
    if (node->song.id!=id) return false;
    if (count_==1) head_=tail_=current_=nullptr;
    else { previous->next=node->next; if(node==head_) head_=node->next; if(node==tail_) tail_=previous; if(node==current_) current_=node->next; tail_->next=head_; }
    delete node; --count_; return true;
}
Song* CircularSongList::findSong(int id) { if(!head_) return nullptr; Node* n=head_; do { if(n->song.id==id) return &n->song; n=n->next; } while(n!=head_); return nullptr; }
std::optional<Song> CircularSongList::setCurrent(int id) { if(!head_) return {}; Node* n=head_; do { if(n->song.id==id) { current_=n; return n->song; } n=n->next; } while(n!=head_); return {}; }
std::optional<Song> CircularSongList::getNext() { if(!current_) return {}; current_=current_->next; return current_->song; }
std::optional<Song> CircularSongList::getPrevious() { if(!current_) return {}; Node* n=current_; while(n->next!=current_) n=n->next; current_=n; return current_->song; }
std::vector<Song> CircularSongList::all() const { std::vector<Song> r; if(!head_) return r; Node* n=head_; do { r.push_back(n->song); n=n->next; } while(n!=head_); return r; }
static std::string lower(std::string v) { std::transform(v.begin(),v.end(),v.begin(),[](unsigned char c){return std::tolower(c);}); return v; }
std::vector<Song> CircularSongList::search(const std::string& q) const { std::vector<Song> r; auto needle=lower(q); for(auto& s:all()) if(lower(s.title+" "+s.artist+" "+s.album+" "+s.language+" "+s.genre).find(needle)!=std::string::npos) r.push_back(s); return r; }
std::vector<Song> CircularSongList::filterLanguage(const std::string& v) const { std::vector<Song> r; for(auto&s:all()) if(lower(s.language)==lower(v)) r.push_back(s); return r; }
std::vector<Song> CircularSongList::filterGenre(const std::string& v) const { std::vector<Song> r; for(auto&s:all()) if(lower(s.genre)==lower(v)) r.push_back(s); return r; }
nlohmann::json CircularSongList::debug() const { auto name=[](Node*n){return n?n->song.title:"None";}; return {{"size",count_},{"head",name(head_)},{"tail",name(tail_)},{"current",name(current_)},{"songs",all()}}; }
