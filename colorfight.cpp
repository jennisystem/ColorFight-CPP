#include "colorfight.h"
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <curl/curl.h>

using namespace std;

const string URL = "http://troycolorfight.herokuapp.com/";

LinkedList::LinkedList() {
	this->head = NULL;
}

User::User() {

}

Cell::Cell() {

}

Game::Game() {
	this->data = false;
	this->currTime = 0.0;
	this->endTime = 0.0;
	this->joinEndTime = 0.0;
	this->planStartTime = -1;
	this->lastUpdate = 0.0;
	this->users = new LinkedList();
	this->cells = new Cell[ 900 ];
	this->cellNum = 0;
	this->baseNum = 0;
	this->goldCellNum = 0;
	this->energyCellNum = 0;
	this->cdTime = 0.0;
	this->buildCdTime = 0.0;
	this->energy = 0.0;
	this->gold = 0.0;
	this->width = 30;
	this->height = 30;
}

size_t response_handler( void *ptr, size_t size, size_t nmemb, string &s ) {
	s.append( ( char * ) ptr );
	return size * nmemb;
}

string PostData( string sub, string data ) {
	CURL *curl;
	CURLcode res;
	string str;
	curl = curl_easy_init();
	if( curl ) {
		struct curl_slist *chunk = NULL;
		chunk = curl_slist_append( chunk, "Content-Type: application/json" );
		curl_easy_setopt( curl, CURLOPT_URL, ( URL + sub ).c_str() );
		curl_easy_setopt( curl, CURLOPT_POSTFIELDS, data.c_str() );
		curl_easy_setopt( curl, CURLOPT_HTTPHEADER, chunk );
		curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, &response_handler );
		curl_easy_setopt( curl, CURLOPT_WRITEDATA, &str );
		res = curl_easy_perform( curl );
		if( res != CURLE_OK ) {
			fprintf( stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror( res ) );
		}
		curl_easy_cleanup( curl );
	}
	return str;
}

string &trim( string &str ) {
	string chars( "\t\n\v\f\r " );
	str.erase( 0, str.find_first_not_of( chars ) );
	str.erase( str.find_last_not_of( chars ) + 1 );
	return str;
}

bool Game::JoinGame( string name ) {
	name = trim( name );
	string responseText;
	ifstream tokenRead( "token" );
	if( tokenRead.fail() ) {
		responseText = PostData( "joingame", "{\"name\":\"" + name + "\"}" );
		int pos1 = responseText.find( "\"token\":\"" ) + 9;
		int pos2 = responseText.find( "\"", pos1 );
		this->token = responseText.substr( pos1, pos2 - pos1 );
		ofstream tokenWrite( "token" );
		if( tokenWrite.is_open() ) {
			tokenWrite << token;
			tokenWrite.close();
		}
	} else {
		string tokenStr = "";
		string line;
		while( getline( tokenRead, line ) ) {
			tokenStr += trim( line );
		}
		this->token = tokenStr;
		tokenRead.close();
	}
	return true;
}

void Game::Refresh() {
	this->refreshData = PostData( "getgameinfo", "{\"protocol\":2}" );
	cout << this->refreshData << endl;
}