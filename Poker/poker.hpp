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

using cards_type = std::vector< std::pair< char, std::string > >;
using category_type = std::pair<std::string, Category>;

const std::map < const char, size_t> suits {
	{'S',1},
	{'H',2},
	{'D',3},
	{'C',4}
};
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
	static const size_t CARDS_SIZE = 5;

	player( cards_type&& cards );

	const category_type& get_category() const noexcept;
	void find_category();
	friend std::ostream& operator<<( std::ostream& os, player& p1 );

private:
	cards_type cards_;
	category_type category_;

	void check_duplicates_();
	friend std::string sort_by_strength( player& player1, player& player2 );
};

cards_type::value_type add( char& suit, std::string& rank );
cards_type make_cards( const std::string& str );

bool is_valid( char& x ) noexcept;
bool is_valid( std::string& x ) noexcept;

} // namespace player


#endif // POKER_HPP_INCLUDED
