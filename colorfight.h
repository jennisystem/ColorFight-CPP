#include <string>
#include <iostream>
using namespace std;

class Cell {
	public:
		Cell();
		int owner;
		int attacker;
		bool isTaking;
		int x;
		int y;
		float occupyTime;
		float attackTime;
		float takeTime;
		float finishTime;
		string cellType;
		bool isBase;
		bool isBuilding;
		float buildTime;
};

class User {
	public:
		User();
		int id;
		string name;
		float cdTime;
		float buildCdTime;
		int cellNum;
		int baseNum;
		int goldCellNum;
		int energyCellNum;
		float energy;
		float gold;
};

class LinkedList {
	public:
		LinkedList();
		void add( User user );
		void get( int index );

		~LinkedList();
	private:
		struct Node {
			User *data;
			Node *next;
		};
		Node *head;
};

class Game {
	public:
		Game();

		bool data;
		string token;
		string name;
		int uid;
		float currTime;
		float endTime;
		float joinEndTime;
		float planStartTime;
		float lastUpdate;
		LinkedList *users;
		Cell *cells;
		int cellNum;
		int baseNum;
		int goldCellNum;
		int energyCellNum;
		float cdTime;
		float buildCdTime;
		float energy;
		float gold;
		int width;
		int height;

		bool JoinGame( string name );
	private:
		string refreshData;
		int refreshIndex;
		char thisParseChar;
		bool onParseKey;
		string parseKey;

		// Temporary Cell Data
		int ownerT;
		int attackerT;
		bool isTakingT;
		int xT;
		int yT;
		float occupyTimeT;
		float attackTimeT;
		float takeTimeT;
		float finishTimeT;
		string cellTypeT;
		bool isBaseT;
		bool isBuildingT;
		float buildTimeT;

		// Temporary User Data
		int idT;
		string nameT;
		float cdTimeT;
		float buildCdTimeT;
		int cellNumT;
		int baseNumT;
		int goldCellNumT;
		int energyCellNumT;
		float energyT;
		float goldT;

		//void init_response( Response &r );
		//size_t response_handler( void *ptr, size_t size, size_t nmemb, Response *r );
		//string PostData( string sub, const string data );
};

#ifdef COLORFIGHT_H
#define COLORFIGHT_H


#endif