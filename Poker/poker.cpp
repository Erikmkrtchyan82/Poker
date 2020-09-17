#include <string>
#include <cctype>
#include <vector>
#include <ostream>
#include <sstream>
#include <algorithm>

#include "poker.hpp"
#include "exceptions.hpp"
#include "ranking_categories.hpp"

using namespace std::string_literals;

namespace poker {

player::player( cards_type&& cards ) :cards_( std::move( cards ) ) {
	check_duplicates_();
};

const category_type& player::get_category() const noexcept {
	return category_;
}

void player::find_category() {

	ranking_categories::sort_by_ranks( cards_.begin(), cards_.end() );

	category_ = ranking_categories::catergory( cards_ );
}

std::ostream& operator<<( std::ostream& os, player& p1 ) {
	for ( const auto& [suit, rank] : p1.cards_ )
		os << suit << rank;
	return os;
}

void player::check_duplicates_() {
	for ( auto it = cards_.begin(); it != cards_.end() - 1; ++it )
		if ( std::find( it + 1, cards_.end(), *it ) != cards_.end() )
			throw exceptions::duplicate_card_in_a_hand_exception( "Duplicate card in a hand: "s + it->first + it->second );
}

std::string sort_by_strength( player& player1, player& player2 ) {

	auto get_string = []( std::string&& high, std::string&& low )->std::string {
		return { "The " + high + " hand ranks higher than the " + low };
	};

	if ( player1.category_.second > player2.category_.second )
		return get_string( "first", "second" );
	else if ( player1.category_.second < player2.category_.second )
		return get_string( "second", "first" );
	else {
		for ( size_t i = 0; i < player::CARDS_SIZE; ++i ) {

			if ( ranking_categories::find( player1.cards_[ i ].second ) > ranking_categories::find( player2.cards_[ i ].second ) )
				return get_string( "first", "second" );

			else if ( ranking_categories::find( player1.cards_[ i ].second ) < ranking_categories::find( player2.cards_[ i ].second ) )
				return get_string( "second", "first" );
		}
	}

	return { "Hand ranks are equal" };
}

cards_type::value_type add( char& suit, std::string& rank ) {
	if ( !is_valid( suit ) )
		throw exceptions::invalid_card_suit_exception( "Invalid card suit "s + suit );
	if ( !is_valid( rank ) )
		throw exceptions::invalid_card_rank_exception( "Invalid card rank "s + rank );

	return { suit, rank };
}

cards_type make_cards( const std::string& card_string ) {

	cards_type cards;

	std::stringstream ss( card_string );
	char character;

	while ( ss >> character ) {

		char suit = character;

		std::string rank {};
		if ( ss >> character )
			rank += character;

		if ( std::isdigit( character ) ) {
			while ( ss >> character && std::isdigit( character ) ) {
				rank += character;
			}
			ss.putback( character );
		}

		cards.push_back( add( suit, rank ) );
	}

	if ( cards.size() != 5 )
		throw exceptions::wrong_number_of_cards_in_a_hand_exception( "Wrong number of cards in a hand (should be 5)" );

	return cards;
}

bool is_valid( char& suit ) noexcept {
	try {
		[[maybe_unused]] auto a = suits.at( suit );
		return true;
	}
	catch ( std::out_of_range& ) {
		return false;
	}
}

bool is_valid( std::string& rank ) noexcept {
	try {
		[[maybe_unused]] auto a = ranks.at( rank );
		return true;
	}
	catch ( std::out_of_range& ) {
		return false;
	}
}

} // namespace poker
