#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define MAXN 1000000
#define MAXVALUE 16000000
void sortArray(int *data, int size);

typedef unsigned int uint;
static uint seed;
static uint mrand(uint num)
{
    seed = seed * 1103515245 + 37209;
    return ((seed >> 8) % num);
}

bool check(int *data, int size)
{
    std::vector<int> user(size);
    for (int i = 0; i < size; ++i) user[i] = data[i];
    std::sort(data, data + size);
    sortArray(&user.front(), size);
    for (int i = 0; i < size; ++i) if (data[i] != user[i]) {
        return false;
    }
    return true;
}

bool test_random()
{
    int size, nTests;
    scanf("%d %d %u\n", &size, &nTests, &seed);
    std::vector<int> data(size);
    for (int tst = 0; tst < nTests; ++tst) {
        for (int i = 0; i < size; ++i) data[i] = mrand(MAXVALUE);
        if (!check(&data.front(), size)) return false;
    }
    return true;
}

bool test_manual()
{
    int size;
    scanf("%d", &size);
    std::vector<int> data(size);
    for (int i = 0; i < size; ++i) scanf("%d", &data[i]);
    return check(&data.front(), size);
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