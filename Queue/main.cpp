#include <cstdio>
#include <queue>

#define MININT (1 << 31)

void init();
void push(int x);
int pop();
int front();
int size();

namespace
{
	typedef unsigned int uint;
	static uint seed;
	static uint mrand(uint num) {
		seed = seed * 1103515245 + 37209;
		return ((seed >> 8) % num);
	}
	static int mrand31() {
		seed = seed * 1103515245 + 37209;
		uint acc = seed >> 1;
		seed = seed * 1103515245 + 37209;
		return acc ^ (seed >> 8);
	}

	struct Checker {
		bool test() {
			int nKeys;
			scanf("%d%u", &nKeys, &seed);
			init();
			for (int i = 0; i < nKeys; ++i) {
				int action = mrand(4);
				switch (action) {
				case 0: //push
					push(mrand31());
					break;
				case 1: //pop
					if (!pop()) {
						return false;
					}
					break;
				case 2: //front
					if (!front()) {
						return false;
					}
					break;
				case 3: //size
					if (!size()) {
						return false;
					}
					break;
				}
			}
			return true;
		}
	private:
		std::queue<int> q;
		void init() {
			::init();
			while (!q.empty())
				q.pop();
		}
		void push(int x) {
			::push(x);
			q.push(x);
		}
		bool pop() {
			int target = MININT;
			if (!q.empty()) {
				target = q.front();
				q.pop();
			}
			return ::pop() == target;
		}
		bool front()
		{
			return ::front() == (q.empty() ? MININT : q.front());
		}
		bool size()
		{
			return ::size() == q.size();
		}
	};
}

int main()
{
	setbuf(stdout, NULL);
	int ntests = 0;
	scanf("%d", &ntests);
	Checker c;
	for (int t = 1; t <= ntests; ++t) {
		printf("#%d %d\n", t, c.test() ? 100 : 0);
	}
	return 0;
}