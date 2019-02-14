#include "colorfight.h"

#include <string>
#include <iostream>
#include <curl/curl.h>

using namespace std;

LinkedList::LinkedList() {

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

void Game::init_response( Response *r ) {
	r->size = 0;
	r->text = ( char * ) malloc( 1 );
	r->text[ 0 ] = '\0';
}

size_t Game::response_handler( void *ptr, size_t size, size_t nmemb, Response *r ) {
	size_t respSize = size * nmemb;
	r->text = ( char * ) realloc( r->text, r->size + respSize + 1 );
	if( r->text == NULL ) exit( EXIT_FAILURE );
	memcpy( r->text + r->size, ptr, respSize );
	r->text[ r->size + respSize ] = '\0';
	r->size += respSize;
	return respSize;
}

char *Game::post_json( const char *url, const char *data ) {
	CURL *curl;
	CURLcode res;
	Response r;
	init_response( &r );
	curl = curl_easy_init();
	if( curl ) {
		struct curl_slist *chunk = NULL;
		chunk = curl_slist_append( chunk, "Content-Type: application/json" );
		curl_easy_setopt( curl, CURLOPT_URL, url );
		curl_easy_setopt( curl, CURLOPT_POSTFIELDS, data );
		curl_easy_setopt( curl, CURLOPT_HTTPHEADER, chunk );
		curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, &Game::response_handler );
		curl_easy_setopt( curl, CURLOPT_WRITEDATA, &r );
		res = curl_easy_perform( curl );
		if( res != CURLE_OK ) {
			fprintf( stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror( res ) );
		}
		curl_easy_cleanup( curl );
	}
	return r.text;
}