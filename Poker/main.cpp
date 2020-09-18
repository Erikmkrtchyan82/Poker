#include <string>
#include <iostream>
#include <stdexcept>

#include "poker.hpp"
#include "exceptions.hpp"
#include "ranking_categories.hpp"

int main( int argc, char*argv[] ) {

	if ( argc != 3 ) {
		std::cerr << "Usage: " << argv[ 0 ] << " <first-hand> <second-hand>\n";
		return 1;
	}
	try {

		poker::player player1 ( poker::make_cards( argv[ 1 ] ));
		poker::player player2 ( poker::make_cards( argv[ 2 ] ));

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
