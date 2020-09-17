#include <iostream>
#include <sstream>

#include "poker.hpp"
#include "ranking_categories.hpp"
#include "exceptions.hpp"

void test() {

	auto k = []( poker::player& first ) {
		std::cout << first << " has category " << first.get_category().first << std::endl;
	};

	std::cout << "C D H S\n\n";
	std::vector<std::string> v {
		"D8C4H10S7C6",	// high card					// 10 8 7 6 4
		"S4C6H3DAH2",	// high card					// A 6 4 3 2

		"C3SQC5S5D3",	// 2 pair						// 5 5 3 3 Q
		"CASQC5DAS5",	// 2 pair						// A A 5 5 Q
		"CAS2C5DAS5",	// 2 pair						// A A 5 5 2
		"CJH9C4HJS4",	// 2 pair						// J J 4 4 9

		"D6D4D7D5D3",	// straight flush				// 7 6 5 4 3
		"HQHAHJH10HK",	// straight flush royal			// A K Q J 10
		"H5H2H4HAH3",	// straight flush steel wheel	// 5 4 3 2 A

		"HKC2S2D2H2",	// 4 of a kind					// 2 2 2 2 K
		"C4H2S4D4H4",	// 4 of a kind					// 4 4 4 4 2
		"C9S9HJD9H9",	// 4 of a kind					// 9 9 9 9 J
		"C7S7D7H8H7",	// 4 of a kind					// 7 7 7 7 8
		"C5S5D5H5H6",	// 4 of a kind					// 5 5 5 5 6

		"C3S3D3C6H6",	// full house					// 3 3 3 6 6
		"C7S7C5D7H5",	// full house					// 7 7 7 5 5
		"C7C9S7D7H9",	// full house					// 7 7 7 9 9
		"C2C4S4D4H2",	// full house					// 4 4 4 2 2
		"CACQSQHADQ",	// full house					// Q Q Q A A

		"D6D3DQD4D7",	// flush						// Q 7 6 4 3
		"H10HJH3H8H4",	// flush						// J 10 8 4 3

		"DJDACQCKS10",	// straight broadway			// A K Q J 10
		"S5D4D3S2HA",	// straight baby				// 5 4 3 2 A
		"C9D6C7D5C8",	// straight						// 9 8 7 6 5

		"S9H8H9D10D9",	// 3 of a kind					// 9 9 9 10 8
		"H6D2C2SKS2",	// 3 of a kind					// 2 2 2 K 6

		"C10H8S6C8C5",	// pair							// 8 8 10 6 5

	};

	std::vector<poker::player> p;

	for ( auto x : v ) {
		p.push_back( { poker::make_cards( x ) } );
	}

	for ( auto x : p ) {
		x.find_category();
		k( x );
	}
}

void test1() {
	std::string s1 { "CASQCKDACQ" };
	std::string s2 { "C10H8S6C8C5" };
	poker::player p1 = poker::make_cards( s1 );
	poker::player p2 = poker::make_cards( s2 );
	p1.find_category();
	p2.find_category();

	std::cout << "The first hand " << p1 << " has category " << p1.get_category().first << std::endl;

	std::cout << "The second hand " << p2 << " has category " << p2.get_category().first << std::endl;

	std::cout << sort_by_strength( p1, p2 ) << std::endl << std::endl;

}

int main( int argc, char*argv[] ) {

	if ( argc != 3 ) {
		std::cerr << "Usage: " << argv[ 0 ] << " <first-hand> <second-hand>\n";
		return 1;
	}
	try {
		std::string first = argv[ 1 ];
		std::string second = argv[ 2 ];

		poker::player player1 = poker::make_cards( first );
		poker::player player2 = poker::make_cards( second );

		player1.find_category();
		player2.find_category();

		std::cout << "The first hand " << player1 << " has category " << player1.get_category().first << std::endl;

		std::cout << "The second hand " << player2 << " has category " << player2.get_category().first << std::endl;

		std::cout << sort_by_strength( player1, player2 ) << std::endl << std::endl;


	}
	catch ( std::exception& e ) {
		std::cout << e.what() << std::endl << std::endl;
	}
	catch ( ... ) {
		std::cerr << "UNEXPECTED EXCEPTION" << std::endl;
		return -1;
	}

	return 0;
}
