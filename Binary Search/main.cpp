#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define MAXN 1000000
const int *reinvent_lower_bound(const int *first, const int *last, int value);

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

bool check(const std::vector<int> &data, int value)
{
    const int *first = &data.front();
    const int *last = &data.back() + 1;
    const int *ansPtr = reinvent_lower_bound(first, last, value);
    if (ansPtr < first || last < ansPtr) {
        return false;
    }
    int answer = ansPtr - first;
    int correct = std::lower_bound(data.begin(), data.end(), value) - data.begin();
    return answer == correct;
}

bool test_random()
{
    int size, nRequests;
    scanf("%d %d %u\n", &size, &nRequests, &seed);
    std::vector<int> data(size);
    for (int i = 0; i < size; ++i) data[i] = mrand31();
    sort(data.begin(), data.end());

    for (int tst = 0; tst < nRequests; ++tst) {
        int value = mrand31();
        if (!check(data, value)) {
            return false;
        }
    }

    return true;
}

bool test_manual()
{
    int size, value;
    scanf("%d%d", &size, &value);
    std::vector<int> data(size);
    for (int i = 0; i < size; ++i) scanf("%d", &data[i]);
    sort(data.begin(), data.end());
    return check(data, value);
}

bool test()
{
    int method;
    scanf("%d", &method);
    return method == 1 ? test_random() : test_manual();
}

int main()
{
    setbuf(stdout, NULL);
    int ntests = 0;
    scanf("%d", &ntests);
    for (int t = 1; t <= ntests; ++t) {
        printf("#%d %d\n", t, test() ? 100 : 0);
    }
    return 0;
}