#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <list>


void init();
void decIterator();
void incIterator();
void erase();
void addBefore(int value);
int getValue();


namespace {
    typedef unsigned int uint;
    static uint seed;
    static uint mrand(uint num)
    {
        seed = seed * 1103515245 + 37209;
        return ((seed >> 8) % num);
    }
    static uint mrand31()
    {
        seed = seed * 1103515245 + 37209;
        uint acc = seed >> 1;
        seed = seed * 1103515245 + 37209;
        return acc ^ (seed >> 8);
    }

    bool test_random()
    {
        int nIterations;
        scanf("%d%u", &nIterations, &seed);
        init();
        std::list<int> numbers;
        std::list<int>::iterator it = numbers.begin();
        for (int i = 0; i < nIterations; ++i) {
            int action = mrand(5);
            switch (action) {
            case 0:
                if (it != numbers.begin()) {
                    --it;
                    decIterator();
                    int target = *it;
                    int val = getValue();
                    if (target != val) {
                        return false;
                    }
                }
                break;
            case 1:
                if (it != numbers.end()) {
                    if (*it != getValue()) {
                        return false;
                    }
                    ++it;
                    incIterator();
                }
                break;
            case 2:
                if (it != numbers.end()) {
                    if (*it != getValue()) {
                        return false;
                    }
                    it = numbers.erase(it);
                    erase();
                }
                break;
            default:
                int value = mrand31();
                numbers.insert(it, value);
                addBefore(value);
                break;
            }
        }
        return true;
    }
}

int main()
{
    setbuf(stdout, NULL);
    int ntests = 0;
    scanf("%d", &ntests);
    for (int t = 1; t <= ntests; ++t) {
        printf("#%d %d\n", t, test_random() ? 100 : 0);
    }
    return 0;
}