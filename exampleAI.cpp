#include "colorfight.h"

#include <string>
#include <iostream>

using namespace std;

int main( int argc, char **argv ) {
	Game &g = *( new Game() );
	cout << g.width << " " << g.height << endl;
	return -1;
}