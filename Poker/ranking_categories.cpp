#include <string>
#include <algorithm>
#include <type_traits>

#include "poker.hpp"
#include "ranking_categories.hpp"

namespace ranking_categories {

using Category = poker::Category;
using cards_type = poker::cards_type;
using category_type = poker::category_type;

size_t find( const char& suit ) noexcept {
	return poker::suits.at( suit );
}

size_t find( std::string& rank ) noexcept {
	return poker::ranks.at( rank );
}

void sort_by_ranks( cards_type::iterator begin, cards_type::iterator end ) noexcept {
	std::sort( begin, end, []( auto& card1, auto& card2 ) {return find( card1.second ) > find( card2.second ); } );
}

void sort_by_suits( cards_type::iterator begin, cards_type::iterator end ) noexcept {
	std::sort( begin, end, []( auto& card1, auto& card2 ) {return find( card1.first ) > find( card2.first ); } );
}

bool is_sequential( cards_type::iterator begin, cards_type::iterator end ) {

	return std::adjacent_find( begin, end, []( auto& a, auto& b ) {
		return ( find( a.second ) - 1 ) != find( b.second );
	} ) == end;
}

category_type high_card( cards_type& ) {
	return { "High card",Category::High_card };
}

category_type pair( cards_type& cards ) {
	// 'A' A  K  Q  J
	//  A 'K' K  Q  J
	//  A  K 'Q' Q  J
	//  A  K  Q 'J' J
	auto find_pair = []( auto begin, auto end ) {
		return std::adjacent_find( begin, end, []( auto& a, auto& b ) {
			return a.second == b.second;
		} );
	};

	auto first = find_pair( cards.begin(), cards.end() );

	if ( first == cards.end() )
		return { {},Category::No_category };

	if ( first != cards.begin() ) {
		std::rotate( cards.begin(), first, cards.end() );
		sort_by_ranks( cards.begin() + 2, cards.end() );
	}

	/*
	if ( first != cards.begin() ) {
		size_t distance = 0;
		if ( first != cards.end() - 2 )
			distance = std::distance( cards.begin(), first );

		move_to_end( cards, cards.begin(), first );

		if ( distance )
			move_to_end( cards, cards.begin() + 2, cards.end() - distance );

		sort_by_suits( cards.begin(), cards.begin() + 2 );
	}
	*/

	return { "Pair",Category::One_pair };
}

category_type flush( cards_type& cards ) {

	auto all_suits_are_same = [&] {return std::adjacent_find( cards.begin(), cards.end(), []( auto& a, auto& b ) {
		return a.first != b.first; } ) == cards.end();
	};

	//	if all suits aren't same
	if ( !all_suits_are_same() )
		return { {},Category::No_category };

	// if `A` is the low rank, e.g. ( A 5 4 3 2 )
	if ( cards.begin()->second == "A" && ( cards.begin() + 1 )->second == "5" ) {

		std::rotate( cards.begin(), cards.begin() + 1, cards.end() );
		return { "Straight flush: Steel wheel",Category::Steel_wheel_straight_flush };
	}

	//	if ranks aren't sequential
	if ( !is_sequential( cards.begin(), cards.end() ) )
		return { "Flush",Category::Flush };

	// if `A` is the high rank
	if ( cards.front().second == "A" )
		return { "Straight flush: Royal",Category::Royal_straight_flush };

	return { "Straight flush",Category::Straight_flush };
}

category_type straight( cards_type& cards ) {

	// e.g. ( 7 6 5 4 3 )
	if ( is_sequential( cards.begin(), cards.end() ) ) {

		// e.g. ( A K Q J 10 )
		if ( cards.front().second == "A" )
			return { "Straight: Broadway",Category::Broadway_straight };

		return { "Straight",Category::Straight };
	}

	// e.g. ( A 5 4 3 2 ) or ( A 5 5 3 2 )
	if ( cards.begin()->second == "A" && ( cards.begin() + 1 )->second == "5" ) {

		// and ( _ x x x x ) is sequential
		if ( is_sequential( cards.begin() + 1, cards.end() ) ) {

			std::rotate( cards.begin(), cards.begin() + 1, cards.end() );
			return { "Straight: Baby",Category::Baby_straight };
		}
	}

	return { {},Category::No_category };
}

category_type two_pair( cards_type& cards ) {

	auto find_pair = []( auto begin, auto end ) {
		return std::adjacent_find( begin, end, []( auto& a, auto& b ) {
			return a.second == b.second;
		} );
	};

	auto first = find_pair( cards.begin(), cards.end() );

	decltype( first ) second;

	if ( first != cards.end() )
		second = find_pair( first + 1, cards.end() );

	if ( first == cards.end() || second == cards.end() /*|| first == second*/ )
		return { {},Category::No_category };

	/*
	// if distance from `first + 1` and `second` is 1,
	// e.g. ( A A K K Q ) or ( A K K Q Q )
	if ( std::distance( first + 1, second ) == 1 && first != cards.begin() ) {

		if ( first != cards.begin() )
			move_to_end( cards, cards.begin(), cards.begin() + 1 );

	}
	else if ( std::distance( first + 1, second ) == 2 )
		move_to_end( cards, cards.begin() + 2, cards.begin() + 3 );
	*/

	// e.g. ( A A K Q Q )
	if ( std::distance( first + 1, second ) == 2 )
		std::rotate( cards.begin() + 2, cards.begin() + 3, cards.end() );
	// e.g. ( A K K Q Q )
	else if ( first != cards.begin() )
		std::rotate( cards.begin(), cards.begin() + 1, cards.end() );

	sort_by_suits( cards.begin(), cards.begin() + 2 );
	sort_by_suits( cards.begin() + 2, cards.end() - 1 );

	return { "Two pair",Category::Two_pair };
}

category_type full_house( cards_type& cards ) {

	bool found = false;

	// e.g. ( A A A K K )
	if ( cards[ 0 ].second == cards[ 1 ].second &&
		 cards[ 0 ].second == cards[ 2 ].second &&
		 cards[ 3 ].second == cards[ 4 ].second ) {

		found = true;
	}
	// e.g. ( A A K K K )
	else if ( cards[ 0 ].second == cards[ 1 ].second &&
			  cards[ 2 ].second == cards[ 3 ].second &&
			  cards[ 2 ].second == cards[ 4 ].second ) {

		std::rotate( cards.begin(), cards.begin() + 2, cards.end() );
		found = true;
	}

	if ( found ) {
		sort_by_suits( cards.begin(), cards.begin() + 3 );
		sort_by_suits( cards.begin() + 3, cards.end() );
		return { "Full house",Category::Full_house };
	}

	return { {},Category::No_category };
}

category_type four_of_a_kind( cards_type& cards ) {

	bool found = false;

	// e.g. ( A A A A K )
	if ( cards[ 0 ].second == cards[ 1 ].second &&
		 cards[ 0 ].second == cards[ 2 ].second &&
		 cards[ 0 ].second == cards[ 3 ].second ) {

		found = true;
	}
	// e.g. ( A K K K K )
	else if ( cards[ 1 ].second == cards[ 2 ].second &&
			  cards[ 1 ].second == cards[ 3 ].second &&
			  cards[ 1 ].second == cards[ 4 ].second ) {

		std::rotate( cards.begin(), cards.begin() + 1, cards.end() );
		found = true;
	}

	if ( found ) {
		sort_by_suits( cards.begin(), cards.end() - 1 );
		return { "Four of a kind",Category::Four_of_a_kind };
	}

	return { {},Category::No_category };
}

category_type three_of_a_kind( cards_type& cards ) {

	bool found = false;

	// e.g. ( A A A K Q )
	if ( cards[ 0 ].second == cards[ 1 ].second &&
		 cards[ 0 ].second == cards[ 2 ].second ) {

		found = true;
	}
	// e.g. ( A K K K Q )
	else if ( cards[ 1 ].second == cards[ 2 ].second &&
			  cards[ 1 ].second == cards[ 3 ].second ) {

		found = true;
		std::rotate( cards.begin(), cards.begin() + 1, cards.end() );
		sort_by_ranks( cards.end() - 2, cards.end() );
	}
	// e.g. ( A K Q Q Q )
	else if ( cards[ 2 ].second == cards[ 3 ].second &&
			  cards[ 2 ].second == cards[ 4 ].second ) {

		found = true;
		std::rotate( cards.begin(), cards.begin() + 2, cards.end() );
	}

	if ( found ) {
		sort_by_suits( cards.begin(), cards.begin() + 3 );
		return { "Three of a kind",Category::Three_of_a_kind };
	}

	return { {},Category::No_category };
}


template<typename... Funcs>
category_type search( cards_type& cards, Funcs... func ) {

	using common_func_type = category_type( * )( cards_type& );
	static_assert( std::is_same_v<std::common_type<Funcs...>::type, common_func_type> );

	category_type category;
	( ( category = func( cards ), category.second != Category::No_category ? true : false ) || ... );

	return category;
}

category_type catergory( cards_type& cards ) {

	return search( cards,
				   flush,
				   four_of_a_kind,
				   full_house,
				   straight,
				   three_of_a_kind,
				   two_pair,
				   pair,
				   high_card );
}

} // namespace ranking_categories



