#include <iostream>
#include <queue>
#include<vector>
#include<stack>
#include<queue>
struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

//1.
bool IsSubBT(TreeNode* root, TreeNode* subRoot)
{
	std::queue<TreeNode*> q;
	q.push(root);
	TreeNode* node = q.front();
	std::queue<TreeNode*> sq;
	sq.push(subRoot);

	TreeNode* sNode;
	while (!q.empty())
	{
		node = q.front();
		q.pop();
		if (node->val == subRoot->val)
		{
			//탐색코드
			break;
		}
		else
		{
			if (node->left) { q.push(node->left); }
			if (node->right) { q.push(node->right); }
		}
	}

	return false;

}

//2.n^2
bool Search(std::vector<std::vector<char>>& board, int* x, int* y, char c, std::vector<std::vector<bool>>& check)
{
	check[*x][*y] = true;
	int row[]{0,1,1,-1};
	int columns[]{-1, 0,1,0};

	for (int i = 0; i < 4; i++)
	{
		if ((*x) + row[i] >= 0 && (*y) + columns[i] >= 0 &&
			(*x) +row[i] < board[0].size() && (*y) + columns[i] > board.size())
		{
			if (board[(*y) + columns[i]][(*x) + row[i]] == c && check[(*y) + columns[i]][(*x) + row[i]] == false)
			{
				*x += row[i];
				*y += columns[i];
				return true;
			}
		}
	}
	return false;
}
bool ExistInMatrix(std::vector<std::vector<char>>& board, std::string word)
{
	int x{-1}, y{-1};
	std::vector<std::vector<bool>> check(board.size(), std::vector<bool>(board[0].size(), false));

	for (int i = 0; i< board.size();i++)
	{
		for (int j = 0 ; j < board[0].size(); j++)
		{
			if (board[i][j] == word[0])
			{
				x = i;
				y = j;
				check[x][y] = true;
				for (int i = 1; i < word.size(); i++)
				{
					if (!Search(board, &x, &y, word[i], check))
					{
						return false;
					}
				}
				break;
			}
		}
	}

	if (x < 0 || y < 0)
	{
		return false;
	}

	check[x][y] = true;

	return true;
}

//3.n*m
int CombinationSum(std::vector<int>& nums, const int target)
{
	std::vector<int> a(target + 1, 0);
	a[0] = 1;
	for (int i = 0; i <= target; i++)
	{
		for (int j = 0; j < nums.size();j++)
		{
			if (i >= nums[j])
			{
				a[i] += a[i - nums[j]];
			}
		}
	}
	
	return a[target];
}

//4.n^3
int CountPalindromeSubstrings(std::string s)
{
	std::vector<char> v;
	int count{};
	int flag{};
	for (int j = 0; j < s.size(); j++)
	{
		for (int i = j; i < s.size(); i++)
		{
			v.push_back(s[i]);
			auto start = 0;
			auto end = v.size() - 1;
			while (start < end)
			{
				if (v[start] != v[end])
				{
					flag = 1;
					break;
				}
				start++;
				end--;
			}
			if (flag == 1)
			{
				continue;
			}
			count++;
		}
		v.clear();
		flag = 0;
	}
	return count;
}

//5.n^3
int Max(std::vector<int>& height, int x)
{
	int max{};
	int h{};
	for (int i = x; i >= 0; i--)
	{
		int temp = std::min(height[x], height[i]);
		for (int j = x; j > i; j--)
		{
			h += temp;
		}
		if (max < h)
		{
			max = h;
		}
		h = 0;;
	}

	for (int i = x; i < height.size(); i++)
	{
		int temp = std::min(height[x], height[i]);
		for (int j = x; j < i; j++)
		{
			h += temp;
		}
		if (max < h)
		{
			max = h;
		}
		h = 0;;
	}
	
	return max;
}

int MaxAmountOfWater(std::vector<int>& height)
{
	int max{};
	int temp{};
	for (int i = 0; i < height.size(); i++)
	{
		temp = Max(height, i);
		if (max < temp)
		{
			max = temp;
		}
	}
	return max;
}

int MaxAmountOfWater2(std::vector<int>& height) {
	int answer = 0;
	int left = 0;
	int right = height.size() - 1;

	while (left < right) {
		// Calculate the amount of water using the shorter line
		int width = right - left;
		int currentHeight = std::min(height[left], height[right]);
		int comp = width * currentHeight;

		// Update the maximum water amount found so far
		if (comp > answer) {
			answer = comp;
		}

		// Move the pointer which points to the shorter line
		if (height[left] < height[right]) {
			++left;
		}
		else {
			--right;
		}
	}
	return answer;
}

int main()
{
	//// 예시 테스트 케이스
	//TreeNode* root = new TreeNode(3);
	//root->left = new TreeNode(4);
	//root->right = new TreeNode(5);
	//root->left->left = new TreeNode(1);
	//root->left->right = new TreeNode(2);

	//TreeNode* subRoot = new TreeNode(4);
	//subRoot->left = new TreeNode(1);
	//subRoot->right = new TreeNode(2);

	//bool result = IsSubBT(root, subRoot);
	//std::cout << "Is subRoot a subtree of root? " << (result ? "Yes" : "No") << std::endl;


	//std::vector<int> v{ 1,2,3 };
	//std::cout << CombinationSum(v, 4);

	//std::cout << CountPalindromeSubstrings("aaa");

	//std::vector<int> h{ 1,8,6,2,5,4,8,3,7 };
	//std::cout << MaxAmountOfWater(h) << std::endl;
	//std::cout << MaxAmountOfWater2(h) << std::endl;

	//std::vector<int> h2{ 2,3,2,3,2,3,2,3,2 };
	//std::cout << MaxAmountOfWater(h2) << std::endl;
	//std::cout << MaxAmountOfWater2(h2) << std::endl;

	//	std::vector<std::vector<char>> board{ 
	//		{'A', 'B', 'C', 'E'}, 
	//		{'S', 'F', 'C', 'S'},
	//        {'A', 'D', 'E', 'E',} };
	//std::string word{ "SEE" };
	//std::cout << std::boolalpha << ExistInMatrix(board, word) << std::endl;
}
