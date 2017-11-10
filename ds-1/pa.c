#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct Deck {
  uint_fast8_t size;
  uint_fast8_t head, tail;
  uint_fast8_t cards[50];
} Deck;

Deck mk_deck(uint_fast8_t size) {
  Deck deck = {
    .size = size,
    .head = 0,
    .tail = size - 1
  };
  
  for (uint_fast8_t i = 0; i < size; i++)
    deck.cards[i] = i + 1;
  
  return deck;
}

uint_fast8_t deck_pop(Deck* deck) {
  uint_fast8_t card = deck->cards[deck->head];
  deck->size--;
  
  deck->head++;
  if (deck->head == 50)
    deck->head = 0;
  
  return card;
}

void deck_return(Deck* deck) {
  uint_fast8_t card = deck->cards[deck->head];
  
  deck->head++;
  if (deck->head == 50)
    deck->head = 0;
  
  deck->tail++;
  if (deck->tail == 50)
    deck->tail = 0;
  
  deck->cards[deck->tail] = card;
}



int main() {
  uint_fast8_t n;
  
  while (scanf("%" SCNuFAST8, &n) == 1 && n > 0) {
    Deck deck = mk_deck(n);
    
    printf("Discarded cards: %" PRIuFAST8, deck_pop(&deck));
    while (deck.size > 1) {
      deck_return(&deck);
      printf(", %" PRIuFAST8, deck_pop(&deck));
    }
    
    printf("\nRemaining card: %" PRIuFAST8 "\n", deck_pop(&deck));
  }
  
  return 0;
}

