#include <gtest/gtest.h>
#include <unordered_set>

extern "C" {
#include <model/card.h>
#include <model/deck.h>
}

int count_cards(LinkedCard* deck) {// Count the number of cards in the deck
    int count = 0;
    while (deck != nullptr) {
        count++;
        deck = deck->next;
    }
    return count;
}

// Check if all cards are unique
bool are_all_cards_unique(LinkedCard* deck) {
    std::unordered_set<std::string> card_set;
    while (deck != nullptr) {
        std::string card_id = std::string(1, deck->rank) + deck->suit;
        if (card_set.find(card_id) != card_set.end()) {
            return false; // Duplicate card found
        }
        card_set.insert(card_id);
        deck = deck->next;
    }
    return true; // All cards are unique
}

TEST(deck_test, test_shuffle_deck) {
    LinkedCard *deck = create_deck();
    ASSERT_NE(deck, nullptr);
    ASSERT_EQ(count_cards(deck), 52);

    // Shuffle the deck
    LinkedCard *shuffled_deck = shuffle_deck(deck);
    ASSERT_NE(shuffled_deck, nullptr);
    ASSERT_EQ(count_cards(shuffled_deck), 52);

    // Check that all cards are unique and no duplicates are present
    bool all_unique = are_all_cards_unique(shuffled_deck);
    ASSERT_TRUE(all_unique);
}

