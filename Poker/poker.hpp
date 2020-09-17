#ifndef POKER_HPP_INCLUDED
#define POKER_HPP_INCLUDED

#include <map>
#include <string>
#include <vector>
#include <ostream>

namespace poker {

enum class Category {
	No_category,
	High_card,
	One_pair,
	Two_pair,
	Three_of_a_kind,
	Baby_straight,
	Straight,
	Broadway_straight,
	Flush,
	Full_house,
	Four_of_a_kind,
	Steel_wheel_straight_flush,
	Straight_flush,
	Royal_straight_flush
};

using category_type = std::pair<std::string, Category>;
using cards_type = std::vector< std::pair< char, std::string > >;

// All suits with their rank for printing.
const std::map < const char, size_t> suits {
	{'S',1},
	{'H',2},
	{'D',3},
	{'C',4}
};

// All ranks with their rank for comparison.
const std::map < std::string, size_t> ranks {
	{"2",1},
	{"3",2},
	{"4",3},
	{"5",4},
	{"6",5},
	{"7",6},
	{"8",7},
	{"9",8},
	{"10",9},
	{"J",10},
	{"Q",11},
	{"K",12},
	{"A",13}
};

class player {
public:
	// Size for cards in a hand
	static const size_t CARDS_SIZE = 5;

	player( cards_type cards );

	const category_type& get_category() const noexcept;
	void find_category();
	friend std::ostream& operator<<( std::ostream& os, player& p1 );

private:
	cards_type cards_;
	category_type category_;

	// Checking duplicates in a hand.
	// Throws `duplicate_card_in_a_hand_exception`.
	void check_duplicates_();

	// Returned string tells which hand have the highest category.
	friend std::string sort_by_strength( player& player1, player& player2 );
};

// Returns a card if `suit` and `rank` are valid.
// Throws `invalid_card_suit_exception` and `invalid_card_rank_exception`.
cards_type::value_type add( char& suit, std::string& rank );

// Reads from `str` and creating cards.
// Throws `wrong_number_of_cards_in_a_hand_exception`.
cards_type make_cards( const std::string& str );

// Checks if `suit` is valid.
bool is_valid( char& suit ) noexcept;

// Checks if `rank` is valid.
bool is_valid( std::string& rank ) noexcept;

} // namespace player


#endif // POKER_HPP_INCLUDED
