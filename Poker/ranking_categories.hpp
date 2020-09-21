#ifndef RANKING_CATEGORY_HPP_INCLUDED
#define RANKING_CATEGORY_HPP_INCLUDED

#include "poker.hpp"

namespace ranking_categories {

using Category = poker::Category;
using cards_type = poker::cards_type;
using category_type = poker::category_type;

// For finding `suit's` rank.
size_t find( const char& suit ) noexcept;

// For finding `rank's` rank.
size_t find( std::string& rank ) noexcept;

// Sorting cards from `begin` to `end` by ranks: first come `A`, `K`, `Q`, ... `3` and `2`.
void sort_by_ranks( cards_type::iterator begin, cards_type::iterator end ) noexcept;

// Sorting cards from `begin` to `end` by suits: first come `C`, `D`, `H` and `S`.
void sort_by_suits( cards_type::iterator begin, cards_type::iterator end ) noexcept;

// Checks if cards from `begin` to `end` is sequential by ranks's rank.
bool is_sequential( cards_type::iterator begin, cards_type::iterator end );

category_type flushes( cards_type& cards );
category_type four_of_a_kind( cards_type& cards );
category_type full_house( cards_type& cards );
category_type straight( cards_type& cards );
category_type three_of_a_kind( cards_type& cards );
category_type two_pair( cards_type& cards );
category_type pair( cards_type& cards );
category_type high_card( cards_type& );

// Checks every possible category for a hand from highest to lowest.
template< typename... Funcs>
category_type search( cards_type& cards, Funcs... func );

// Returns `search` s return value.
category_type category( cards_type& cards );

} // namespace ranking_categories

#endif // RANKING_CATEGORY_HPP_INCLUDED
