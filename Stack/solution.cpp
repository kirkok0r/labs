#include "limits.h"
#define _CRT_SECURE_NO_WARNINGS
#define nullptr 0

struct node {
  node *prev;
  int value;
};

node* bottom = nullptr;
node* upper = nullptr;

unsigned long counter;

void erase() {
  node* temp = upper;
  if (upper == bottom) {
    upper = bottom = nullptr;
  }
  else {
    upper = upper->prev;
  }
  delete temp;
  counter--;

}

void init() {
  while (bottom != nullptr) {
    erase();
  }
  bottom = upper = nullptr;
  counter = 0;
}


void push(int x) {
  if (bottom == nullptr) {
    bottom = upper = new node;
    upper->value = x;
    upper->prev = nullptr;
  }
  else {
    node* temp = upper;
    upper = new node;
    upper->prev = temp;
    upper->value = x;
  }
  counter++;
}

int pop() {
  if (counter == 0) {
    return INT_MIN;
  }
  else {
    int val = upper->value;
    erase();
    return val;
  }
}

int top() {
  if (counter == 0) {
    return INT_MIN;
  }
  else {
    return upper->value;
  }
}

int size() {
  return counter;
}
