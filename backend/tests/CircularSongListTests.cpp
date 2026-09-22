#include "../data_structures/CircularSongList.h"
#include <cassert>
int main(){CircularSongList list;Song a{1,"A"},b{2,"B"},c{3,"C"};list.insertSong(a);list.insertSong(b);list.insertSong(c);assert(list.size()==3);list.setCurrent(3);assert(list.getNext()->id==1);assert(list.getPrevious()->id==3);list.setCurrent(1);assert(list.getPrevious()->id==3);assert(list.search("B").front().id==2);assert(list.deleteSong(2));assert(list.size()==2);}
