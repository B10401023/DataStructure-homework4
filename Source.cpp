#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node
{
	int data;
	Node *left;
	Node *right;
	int leftSize;
	Node() { left = 0; right = 0; }
};

class BST
{
private:
	Node *root;
	Node *currentNode;
	Node *pastNode;
	int computsize(Node *);
	Node *search(int);
	int rank(int);
public:
	BST();
	void insertion(int);
	void deletion();
	void levelorder();
	int computsize(int);
	void leftLevelorder();
	int aveSmall(int, int);
	int aveLarge(int, int);
	int Median(int);
};

BST::BST()
{
	root = NULL;
}

void BST::insertion(int p)
{
	if (root)
	{
		currentNode = root;
		while (currentNode)
		{
			if (currentNode->data > p)
			{
				pastNode = currentNode;
				currentNode->leftSize++;
				currentNode = currentNode->left;
			}
			else if (currentNode->data < p)
			{
				pastNode = currentNode;
				currentNode = currentNode->right;
			}
		}
		Node *leaf = new Node;
		leaf->data = p;
		leaf->leftSize = 1;
		if (pastNode->data > p)
			pastNode->left = leaf;
		else if (pastNode->data < p)
			pastNode->right = leaf;
	}
	else
	{
		root = new Node;
		root->data = p;
		root->leftSize = 1;
	}
}

void BST::deletion()
{
	currentNode = root;
	while (currentNode->right)
	{
		pastNode = currentNode;
		currentNode = currentNode->right;
	}
	if (currentNode == root)
	{
		if (currentNode->left)
			root = currentNode->left;
		else
			root = NULL;
	}
	else
	{
		if (currentNode->left)
			pastNode->right = currentNode->left;
		else
			pastNode->right = NULL;
	}
	delete currentNode;
}

Node *BST::search(int p)
{
	currentNode = root;
	while (currentNode)
	{
		if (p > currentNode->data)
			currentNode = currentNode->right;
		else if (p < currentNode->data)
			currentNode = currentNode->left;
		else
		{
			currentNode = currentNode->left;
			return currentNode;
		}
	}
}

void BST::levelorder()
{
	std::queue<Node *> Myqueue;
	currentNode = root;
	Myqueue.push(root);
	while (currentNode)
	{
		currentNode = Myqueue.front();
		cout << currentNode->data << " ";
		if (currentNode->left)
			Myqueue.push(currentNode->left);
		if (currentNode->right)
			Myqueue.push(currentNode->right);
		Myqueue.pop();
		if (Myqueue.empty())
			return;
	}
}

void BST::leftLevelorder()
{
	std::queue<Node *> Myqueue;
	currentNode = root;
	Myqueue.push(root);
	while (currentNode)
	{
		currentNode = Myqueue.front();
		cout << currentNode->leftSize << " ";
		if (currentNode->left)
			Myqueue.push(currentNode->left);
		if (currentNode->right)
			Myqueue.push(currentNode->right);
		Myqueue.pop();
		if (Myqueue.empty())
			return;
	}
}

int BST::rank(int p)
{
	currentNode = root;
	while (currentNode)
	{
		if (p < currentNode->leftSize)
			currentNode = currentNode->left;
		else if (p > currentNode->leftSize)
		{
			p -= currentNode->leftSize;
			currentNode = currentNode->right;
		}
		else
			return currentNode->data;
	}
}

int BST::aveSmall(int NUM, int k)
{
	if (k > NUM)
		return -1;
	else if (k <= 0)
		return 0;
	else
	{
		int sum = 0;
		for (int i = 1; i <= k; i++)
		{
			sum = sum + rank(i);
		}
		return sum / k;
	}
}

int BST::aveLarge(int NUM, int k)
{
	if (k > NUM)
		return -1;
	else if (k <= 0)
		return 0;
	else
	{
		int sum = 0;
		for (int i = NUM - k + 1; i <= NUM; i++)
		{
			sum = sum + rank(i);
		}
		return sum / k;
	}
}

int BST::Median(int NUM)
{
	if (NUM % 2 == 0)
	{
		NUM = NUM / 2;
		return (rank(NUM) + rank(NUM + 1)) / 2;
	}
	else
	{
		NUM = NUM / 2 + 1;
		return rank(NUM);
	}
}

int BST::computsize(int p)
{
	return (computsize(search(p)));
}

int BST::computsize(Node *cur)
{
	int count = 1;
	if (cur->left)
	{
		count = count + computsize(cur->left);
	}
	if (cur->right)
	{
		count = count + computsize(cur->right);
	}
	return count;
}

void main()
{
	BST tree;
	while (1)
	{
		int NUM, j, times = 0, p, k;
		cout << "Amount:";
		cin >> NUM;
		cout << "Please enter a sequence of integers." << endl;
		for (int times = 0; times < NUM; times++)
		{
			cin >> p;
			tree.insertion(p);
		}
		tree.levelorder();
		cout << endl;
		tree.leftLevelorder();
		cout << endl;
		cout << "1.Insert\n" << "2.Delete\n" << "3.Find out the total number of elements in the left subtree\n" << "4.The average of SMALLEST k elements\n" << "5.The average of LARGEST k elements\n" << "6.The median element\n" << "7.Restart\n" << endl;
		while (1)
		{
			cin >> j;
			if (j == 1)
			{
				cin >> p;
				tree.insertion(p);
				tree.levelorder();
				cout << "\n";
				tree.leftLevelorder();
				cout << "\n";
			}
			else if (j == 2)
			{
				tree.deletion();
				tree.levelorder();
				tree.leftLevelorder();
				cout << "\n";
			}
			else if (j == 3)
			{
				int count = 0;
				cin >> p;
				cout << tree.computsize(p) << endl;
			}
			else if (j == 4)
			{
				cin >> k;
				cout << "Average of SMALLEST " << k << " elements: " << tree.aveSmall(NUM, k) << endl;
			}
			else if (j == 5)
			{
				cin >> k;
				cout << "Average of LARGEST " << k << " elements: " << tree.aveLarge(NUM, k) << endl;
			}
			else if (j == 6)
			{
				cout << "Median element: " << tree.Median(NUM) << endl;
			}
			else if (j == 7)
				break;
		}
	}
}