
#include <gtest/gtest.h>
extern "C" {
    #include <model/card.h>
    #include <model/deck.h>
}

TEST(deck_test, test_create_deck) { // Test the 'create_deck' function.
    LinkedCard* deck = create_deck(); //create a deck of cards.
    ASSERT_NE(deck, nullptr); // Assert that the 'create_deck' function did not return a null pointer.

// Define the suits and ranks of the cards in the deck.
    char suits[4] = {'S', 'H', 'D', 'C'}; // Spades, Hearts, Diamonds, Clubs
    char ranks[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

    LinkedCard* temp = deck; // Temporary pointer to the deck of cards.
    int i = 0; // Counter to track the number of cards checked
    while (temp != nullptr) { // Loop through the deck of cards.

        ASSERT_EQ(temp->rank, ranks[i % 13]); // Assert that the rank of the card is the expected rank.
        ASSERT_EQ(temp->suit, suits[i / 13]); // Assert that the suit of the card is the expected suit.

        temp = temp->next; // Move to the next card in the deck.
        i++;
    }

    ASSERT_EQ(i, 52); // Assert that all 52 cards in the deck have been checked.
}
