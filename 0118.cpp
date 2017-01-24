#include <array>
#include <cstdio>
#include <chrono>

using State = std::array<int, 16>;
const std::array<int, 4> movements{-4, -1, 1, 4};

int find_hole(const State &state)
{
	for (int i=0; i<16; ++i) {
		if (state[i] == 0) {
			return i;
		}
	}
	throw 1;
}

bool modify(State &state, int move)
{
	int hole = find_hole(state);
	if (hole + move < 0 or hole + move >= 16) {
		return false;
	} else if ((move == -1 and hole % 4 == 0) or (move == 1 and hole % 4 == 3)) {
		return false;
	} else {
		state[hole] = state[hole + move];
		state[hole + move] = 0;
		return true;
	}
}

bool solve(const State &start, const State &end, int distance)
{
	if (distance == 0) {
		return start == end;
	} else {
		for (int move : movements) {
			State step = start;
			if (modify(step, move) and solve(step, end, distance - 1)) {
				printf("move %i\n", step[find_hole(start)]);
				return true;
			}
		}
		return false;
	}
}

int main()
{
    State start = {0, 2, 4, 3, 5, 6, 1, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    State end = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	std::chrono::high_resolution_clock::time_point t_start = std::chrono::high_resolution_clock::now();
	for (int distance=0; distance<80; ++distance) {
		printf("distance %i...\n", distance);
		if (solve(start, end, distance)) {
			float elapsedTime = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - t_start).count();
			printf("Solved in %g seconds.\n", elapsedTime);
			#ifdef _WIN32
			getch();
			#endif
			return 0;
		}
	}
	printf("Failed.\n");
	return 1;
}
