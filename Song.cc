/****************************************
    Hunter Stout
    2/18/2022
    Song.cc
    Class definition for Song.h
****************************************/

#include "Song.h"
#include "date.h"
#include <cctype>
#include <iostream>
#include <iomanip>
using namespace std;

//#################### ↓  C O N S T R U C T O R  ↓ ####################

Song::Song() {
    name = "N/A";
    release = Date();
    artist = "N/A";
}

//######################## ↓  G E T T E R S  ↓ ########################

string Song::get_name()const {
    return name;
}

Date Song::get_release()const {
    return release;
}

string Song::get_artist()const {
    return artist;
}

//################## ↓  I N P U T  &  O U T P U T  ↓ ##################

void Song::input(istream& ins) {
    string placeholder;
    if (&ins == &cin){ //Cin

        //Song name.
        cout << "Enter song name:" << endl;
        while(ins.peek() == '\n' || ins.peek() == '\r') {
        	ins.ignore();
		}
        getline(ins, placeholder);
        name = placeholder;

        //Artist name.
        cout << "Enter artist name:" << endl;
        while(ins.peek() == '\n' || ins.peek() == '\r') {
        	ins.ignore();
		}
        getline(ins, placeholder);
        artist = placeholder;

        //Release date.
		cout << "Enter release date (MM/DD/YYYY):" << endl;
		ins >> release;
    }
    else { //File

        //Song name.
        while(ins.peek() == '\n' || ins.peek() == '\r') {
			ins.ignore();
		}
        getline(ins, placeholder);
        name = placeholder;

        //Artist name.
        while(ins.peek() == '\n' || ins.peek() == '\r') {
			ins.ignore();
		}
        getline(ins, placeholder);
        artist = placeholder;

        //Release date.
        ins >> release;
    }
}

void Song::output(ostream& outs)const {
    if (&outs == &cout) { //Cout
        cout << "Song: " << name << endl;
        cout << "Artist: " << artist << endl;
        cout << "Release Date: " << release << endl;
    }
    else { //File
        outs << name << endl;
        outs << artist << endl;
        outs << release << endl;
    }
}

istream& operator >> (istream& ins, Song& s){
	s.input(ins);
	return ins;
}

ostream& operator << (ostream& outs, const Song& s){
	s.output(outs);
	return outs;
}

//############# ↓  O P E R A T O R   O V E R L O A D S  ↓ #############

bool Song::operator == (const Song& other)const {
    return name == other.name && artist == other.artist && release == other.release;
}

bool Song::operator != (const Song& other)const {
    return name != other.name || artist != other.artist || release != other.release;
}