/****************************************
    Hunter Stout
    2/18/2022
    Playlist.cc
    Class definition for Playlist.h
****************************************/

#include "Playlist.h"
#include "Song.h"
#include <cctype>
#include <iostream>
#include <iomanip>
using namespace std;

//#################### ↓  C O N S T R U C T O R  ↓ ####################

Playlist::Playlist() {
    capacity = 5;
    used = 0;
    current_index = 0;
    data = new Song[capacity];
}

//###################### ↓  B I G   T H R E E  ↓ ######################

Playlist::~Playlist() { //Deconstructor
    delete[] data;
}

Playlist::Playlist(const Playlist& other) { //Copy Constructor
    used = other.used;
    capacity = other.capacity;
    data = new Song[capacity];
    for(int i = 0; i < used; i++) {
        data[i] = other.data[i];
    }
}

void Playlist::operator = (const Playlist& other) { //Assignment Constructor
    if (this == &other) {
        return;
    }
    delete[] data;
    used = other.used;
    capacity = other.capacity;
    data = new Song[capacity];
    for(int i = 0; i < used; i++) {
        data[i] = other.data[i];
    }
}
//######################## ↓  P R I V A T E  ↓ ########################

void Playlist::resize() { //Adds 5 to capacity.
    Song *tmp;
    tmp = new Song[capacity + 5];
    for (int i = 0; i < used; i++) {
        tmp[i] = data[i];
    }
    delete[] data;
    capacity += 5;
    data = tmp;
}

//################# ↓  C U R S O R   H E L P E R S  ↓ #################

void Playlist::start() {
    current_index = 0;
}

void Playlist::advance() {
    current_index++;
}

bool Playlist::is_item()const {
    return current_index < used;
}

Song Playlist::current()const {
    return data[current_index];
}

//######################## ↓   H E L P E R S  ↓ #######################

void Playlist::remove_current() {
    Song *tmp;
    tmp = new Song[capacity];
    for(int i = 0; i < used; i++) { //Copies array
        if (i != current_index) { //Ignores song on cursor.
            if (i > current_index) { //Adjusts array size once song is removed.
                tmp[i-1] = data[i];
            }
            else { //Normal copy.
                tmp[i] = data[i];
            }
        }
    }
    delete[] data;
    data = tmp;
    used--;
}

void Playlist::insert(const Song& s) { //Adds song before cursor.
    Song input, tmp;
    if (used == capacity) { //Checks for resize.
        resize();
    }
    input = data[current_index]; //Updates input song & saves old one.
    data[current_index] = s;
    used++;
    for (int i = current_index + 1; i < used; i++) {  //Pushes back array.
        tmp = data[i];
        data[i] = input;
        input = tmp;
    }
}

void Playlist::attach(const Song& s) { //Adds song after cursor.
    advance();
    insert(s);
    current_index--;
}

void Playlist::show_all(ostream& outs)const { 
    for (int i = 0; i < used; i++){
        outs << data[i] << endl;
    }
}

void Playlist::releaseDate_sort() { //Date bubble sort.
    Song temp;
    bool done = false;
    while (!done) {
        done = true;
        for (int i = 0; i < used - 1; i++) {
            if (data[i].get_release() > data[i + 1].get_release()) {
                temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
                done = false;
            }
        }
    }
}

void Playlist::artist_sort() { //Artist bubble sort.
    Song temp;
    bool done = false;
    while (!done) {
        done = true;
        for (int i = 0; i < used - 1; i++) {
            if (data[i].get_artist() > data[i + 1].get_artist()) {
                temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
                done = false;
            }
        }
    }
}

Song Playlist::find_song(const string& name)const {
    Song temp;
    for (int i = 0; i < used; i++){ 
        if (name == data[i].get_name()){ //Checks array for song name.
            temp = data[i];
        }
    }
        return temp;
}

bool Playlist::is_song(const Song& s)const { //Checks if song is in playlist.
    for(int i = 0; i < used; i++) {
        if (data[i] == s) {
            return true;
        }
    }
    return false;
}

//##################### ↓   L O A D  &  S A V E  ↓ ####################

void Playlist::load(istream& ins) {
    Song placeholder;
    while(ins >> placeholder){
        if (used == capacity) {
            resize();
        }
        data[used] = placeholder;
        used++;
    }
}

void Playlist::save(ostream& outs)const {
    for (int i = 0; i < used; i++) {
        outs << data[i].get_name() << endl;
        outs << data[i].get_artist() << endl;
        outs << data[i].get_release() << endl;
    }
}