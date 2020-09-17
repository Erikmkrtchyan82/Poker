#ifndef EXCEPTIONS_HPP_INCLUDED
#define EXCEPTIONS_HPP_INCLUDED

#include <stdexcept>

namespace exceptions {

class invalid_card_suit_exception :public std::invalid_argument {
	using invalid_argument::invalid_argument;
};

class invalid_card_rank_exception :public std::invalid_argument {
	using invalid_argument::invalid_argument;
};

class duplicate_card_in_a_hand_exception :public std::invalid_argument {
	using invalid_argument::invalid_argument;
};

class wrong_number_of_cards_in_a_hand_exception :public std::length_error {
	using length_error::length_error;
};

} // namespace exceptions

#endif // EXCEPTIONS_HPP_INCLUDED
