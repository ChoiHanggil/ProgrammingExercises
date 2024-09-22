#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>

struct ListNode
{
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

//1.O(n log n)
bool HasCycle(ListNode* head)
{
	std::unordered_set<ListNode*> s;
	auto p = head;
	int size{};

	while (p)
	{
		s.insert(p);
		if (size == s.size())
		{
			return true;
		}
		p = p->next;
		size = s.size();
	}
	return false;
}

//2.O(m*n)
void LandResearch(std::vector<std::vector<char>> grid, std::vector<std::vector<int>>& temp, int x, int y)
{
	static const int dRow[4]{ -1,1,0,0 };
	static const int dCol[4]{ 0,0,-1,1 };

	std::queue<std::pair<int, int>> q;
	q.push({ x,y });
	temp[x][y] = 1;

	while (!q.empty())
	{
		x = q.front().first;
		y = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int dx = x + dRow[i];
			int dy = y + dCol[i];
			if (dx < 0 || dx >= grid.size() || dy < 0 || dy >= grid[0].size())
			{
				continue;
			}
			if (grid[dx][dy] == '1'&& temp[dx][dy] == 0 )
			{
				q.push({ dx,dy });
				temp[dx][dy] = 1;
			}
		}
	}
}

int NumIslands(std::vector<std::vector<char>>& grid)
{
	int answer{};
	std::vector<std::vector<int>> temp(grid.size(), std::vector<int>(grid[0].size(), 0));
	
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[0].size(); j++)
		{
			if (grid[i][j] == '1' && temp[i][j] == 0)
			{
				LandResearch(grid, temp, i, j);
				answer++;
			}
		}
	}
	return answer;
}

//3.O(n*n*n)
//시뮬레이션
int TurnoverCount(std::vector<std::vector<int>> temp, int x, int y)
{
	static const int dRow[8]{ -1,-1,0,1,1,1,0,-1 };
	static const int dCol[8]{ 0,1,1,1,0,-1,-1,-1, };

	int count = 0;
	int r{}, c{};

	std::priority_queue<int> max;
	max.push(0);

	for (int i = 0; i < 8; i++)
	{
		if (temp[x + dRow[i]][y + dCol[i]] == 2)
		{
			r = dRow[i];
			c = dCol[i];
			while (temp[x + r][y + c])
			{
				r += dRow[i];
				c += dCol[i];
				count++;
				if (temp[x + r][y + c] == 1)
				{
					max.push(count);
					break;
				}
			}
			count = 0;
		}
	}
	return max.top();
}
int bestMove(std::vector<std::vector<int>>& board)
{
	std::vector<std::vector<int>> temp(board.size()+2, std::vector<int>(board[0].size() + 2, 0));
	std::priority_queue<int> count;
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[0].size(); j++)
		{
			temp[i + 1][j + 1] = board[i][j];
		}
	}

	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			count.push(TurnoverCount(temp, i, j));
		}
	}
	return count.top();
}
//4.O(m*n)
int UniquePaths(int m, int n)
{
	std::vector<std::vector<int>> v(m+1, std::vector<int>(n+1, 0));
	for (int i = 1; i < m; i++)
	{
		for (int j = 1; j < n; j++)
		{
			v[i][j] = v[i-1][j] + v[i][j - 1];
		}
	}
	return v[m][n];
}

//5.O(n log n)
//sweep line algorithm
std::vector<std::vector<int>> MergeIntervals(std::vector<std::vector<int>>& intervals)
{
	std::sort(intervals.begin(), intervals.end());
	std::vector<std::vector<int>> answer;
	answer.push_back(intervals[0]);

	for (auto i = 1;i < intervals.size(); i++)
	{
		if (intervals[i][0] <= answer.back()[1])
		{
			answer.back()[1] = std::max(intervals[i][1], answer.back()[1]);
		}
		else
		{
			answer.push_back(intervals[i]);
		}
	};

	return answer;
}

int main()
{
	//ListNode a(1);
	//ListNode b(2);
	//ListNode c(3);
	//a.next = &b;
	//b.next = &c;
	//c.next = &a;

	//std::cout << HasCycle(&a);

	//std::vector<std::vector<char>> grid = {
	//	{'1', '1', '1', '1', '0'},
	//	{'1', '1', '0', '1', '0'},
	//	{'1', '1', '0', '0', '0'},
	//	{'0', '0', '0', '0', '0'}
	//};
	//std::cout << NumIslands(grid);

	//std::vector<std::vector<int>> board = {
	// {0, 0, 0, 0, 0, 0, 0, 0},
	// {0, 0, 0, 0, 0, 0, 0, 0},
	// {0, 0, 0, 1, 1, 0, 0, 0},
	// {0, 0, 0, 1, 0, 0, 0, 0},
	// {0, 0, 1, 1, 2, 0, 0, 0},
	// {0, 0, 2, 2, 2, 0, 0, 0},
	// {0, 0, 0, 0, 2, 1, 0, 0},
	// {0, 0, 0, 0, 0, 0, 0, 0}
	//};

	//std::cout << bestMove(board);

	//std::vector<std::vector<int>> intervalss =
	//{
	//	{ 1, 2 }, { 3, 4 }, { 2, 3 }, { 4, 5 }
	//};

	//for (auto e : MergeIntervals(intervalss))
	//{
	//	std::cout << e[0] << "," << e[1] << std::endl;
	//}
}
