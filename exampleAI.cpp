#include "colorfight.h"

#include <string>
#include <iostream>

using namespace std;

int main( int argc, char **argv ) {
	Game g;
	if( g.JoinGame( "AI++" ) ) {
		g.Refresh();
		cout << g.uid << endl;
		cout << g.token << endl;
	}
	return -1;
}