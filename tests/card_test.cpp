#include <gtest/gtest.h>
extern "C" {
    #include <core/card.h>
}

TEST(CardTest, CardCreateTest) {
    LinkedCard* card = create_card('A', 'S');
    ASSERT_NE(card, nullptr);
    ASSERT_EQ(card->rank, 'A');
    ASSERT_EQ(card->suit, 'S');
}

TEST(DeckTest, DeckSaveAndLoadTest) {
    LinkedCard* deck = create_deck();

    char str[14] = "test_deck.txt";
    save_deck_to_file(deck, str);
    LinkedCard* deckFromFile = create_deck_from_file(str);
    for (int i = 0; i < 52; i++) {
        ASSERT_NE(deckFromFile, nullptr);
        deckFromFile = deckFromFile->next;
    }
}

TEST(DeckTest, DeckCreateTest) {
    LinkedCard* deck = create_deck();
    for (int i = 0; i < 52; i++) {
        ASSERT_NE(deck, nullptr);
        deck = deck->next;
    }
}