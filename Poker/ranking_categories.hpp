#ifndef RANKING_CATEGORY_HPP_INCLUDED
#define RANKING_CATEGORY_HPP_INCLUDED

#include "poker.hpp"

namespace ranking_categories {

using Category = poker::Category;
using cards_type = poker::cards_type;
using category_type = poker::category_type;

size_t find( const char& suit ) noexcept;
size_t find( std::string& rank ) noexcept;

void sort_by_ranks( cards_type::iterator begin, cards_type::iterator end ) noexcept;
void sort_by_suits( cards_type::iterator begin, cards_type::iterator end ) noexcept;

bool is_sequential( cards_type::iterator begin, cards_type::iterator end );

category_type high_card( cards_type& );
category_type pair( cards_type& cards );
category_type flush( cards_type& cards );
category_type straight( cards_type& cards );
category_type two_pair( cards_type& cards );
category_type full_house( cards_type& cards );
category_type four_of_a_kind( cards_type& cards );
category_type three_of_a_kind( cards_type& cards );

template< typename... Funcs>
category_type search( cards_type& cards, Funcs... func );
category_type catergory( cards_type& cards );

} // namespace ranking_categories

#endif // RANKING_CATEGORY_HPP_INCLUDED
