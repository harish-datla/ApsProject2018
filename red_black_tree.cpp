#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;
#include <chrono>
using namespace std::chrono;
#define RED 1
#define BLACK 2

struct node
{
	int key;
	struct node *left, *right, *p;
	int color;
	int height;
	int nodes;
};

typedef struct node *NODEPTR;
struct node NIL;
NODEPTR NILPTR = &NIL;

void inorder(NODEPTR x)
{
	if (x != NILPTR)
	{
		inorder(x->left);
		printf("%d ", x->key);
		inorder(x->right);
	}
}

void leftrotate(NODEPTR *treeroot, NODEPTR x)
{
	NODEPTR y = x->right;
	x->right = y->left;
	if (x->left && x->right)
	{
		x->height = 1 + max(x->left->height, x->right->height);
		x->nodes = 1 + x->left->nodes + x->right->nodes;
	}
	else if (x->left)
	{
		x->height = 1 + x->left->height;
		x->nodes = 1 + x->left->nodes;
	}
	else if (x->right)
	{
		x->height = 1 + x->right->height;
		x->nodes = 1 + x->right->nodes;
	}
	else
	{
		x->height = 1;
		x->nodes = 1;
	}

	if (y->left != NILPTR)
	{
		y->left->p = x;
		if (y->left->p->left && y->left->p->right)
		{
			y->left->p->height = 1 + max(y->left->p->left->height, y->left->p->right->height);
			y->left->p->nodes = 1 + y->left->p->left->nodes + y->left->p->right->nodes;
		}
		else if (y->left->p->left)
		{
			y->left->p->height = 1 + y->left->p->left->height;
			y->left->p->nodes = 1 + y->left->p->left->nodes;
		}
		else if (y->left->p->right)
		{
			y->left->p->height = 1 + y->left->p->right->height;
			y->left->p->nodes = 1 + y->left->p->right->nodes;
		}
		else
		{
			y->left->p->height = 1;
			y->left->p->nodes = 1;
		}
	}
	y->p = x->p;
	if (y->p->left && y->p->right)
	{
		y->p->height = 1 + max(y->p->left->height, y->p->right->height);
		y->p->nodes = 1 + y->p->left->nodes + y->p->right->nodes;
	}
	else if (y->p->left)
	{
		y->p->height = 1 + y->p->left->height;
		y->p->nodes = 1 + y->p->left->nodes;
	}
	else if (y->p->right)
	{
		y->p->height = 1 + y->p->right->height;
		y->p->nodes = 1 + y->p->right->nodes;
	}
	else
	{
		y->p->height = 1;
		y->p->nodes = 1;
	}

	if (x->p == NILPTR)
		*treeroot = y;
	else if (x->p->left == x)
	{
		x->p->left = y;
		if (x->p->left && x->p->right)
		{
			x->p->height = 1 + max(x->p->left->height, x->p->right->height);
			x->p->nodes = 1 + x->p->left->nodes + x->p->right->nodes;
		}
		else if (x->p->left)
		{
			x->p->height = 1 + x->p->left->height;
			x->p->nodes = 1 + x->p->left->nodes;
		}
		else if (x->p->right)
		{
			x->p->height = 1 + x->p->right->height;
			x->p->nodes = 1 + x->p->right->nodes;
		}
		else
		{
			x->p->height = 1;
			x->p->nodes = 1;
		}
	}
	else
	{
		x->p->right = y;
		if (x->p->left && x->p->right)
		{
			x->p->height = 1 + max(x->p->left->height, x->p->right->height);
			x->p->nodes = 1 + x->p->left->nodes + x->p->right->nodes;
		}
		else if (x->p->left)
		{
			x->p->height = 1 + x->p->left->height;
			x->p->nodes = 1 + x->p->left->nodes;
		}
		else if (x->p->right)
		{
			x->p->height = 1 + x->p->right->height;
			x->p->nodes = 1 + x->p->right->nodes;
		}
		else
		{
			x->p->height = 1;
			x->p->nodes = 1;
		}
	}
	y->left = x;
	if (y->left && y->right)
	{
		y->height = 1 + max(y->left->height, y->right->height);
		y->nodes = 1 + y->left->nodes + y->right->nodes;
	}
	else if (y->left)
	{
		y->height = 1 + y->left->height;
		y->nodes = 1 + y->left->nodes;
	}
	else if (y->right)
	{
		y->height = 1 + y->right->height;
		y->nodes = 1 + y->right->nodes;
	}
	else
	{
		y->height = 1;
		y->nodes = 1;
	}
	x->p = y;
	if (x->p->left && x->p->right)
	{
		x->p->height = 1 + max(x->p->left->height, x->p->right->height);
		x->p->nodes = 1 + x->p->left->nodes + x->p->right->nodes;
	}
	else if (x->p->left)
	{
		x->p->height = 1 + x->p->left->height;
		x->p->nodes = 1 + x->p->left->nodes;
	}
	else if (x->right)
	{
		x->p->height = 1 + x->p->right->height;
		x->p->nodes = 1 + x->p->right->nodes;
	}
	else
	{
		x->p->height = 1;
		x->p->nodes = 1;
	}
}

void rightrotate(NODEPTR *treeroot, NODEPTR y)
{
	NODEPTR x = y->left;
	y->left = x->right;
	if (y->left && y->right)
	{
		y->height = 1 + max(y->left->height, y->right->height);
		y->nodes = 1 + y->left->nodes + y->right->nodes;
	}
	else if (y->left)
	{
		y->height = 1 + y->left->height;
		y->nodes = 1 + y->left->nodes;
	}
	else if (y->right)
	{
		y->height = 1 + y->right->height;
		y->nodes = 1 + y->right->nodes;
	}
	else
	{
		y->height = 1;
		y->nodes = 1;
	}
	if (x->right != NILPTR)
	{
		x->right->p = y;
		if (x->right->p->left && x->right->p->right)
		{
			x->right->p->height = 1 + max(x->right->p->left->height, x->right->p->right->height);
			x->right->p->nodes = 1 + x->right->p->left->nodes + x->right->p->right->nodes;
		}
		else if (x->right->p->left)
		{
			x->right->p->height = 1 + x->right->p->left->height;
			x->right->p->nodes = 1 + x->right->p->left->nodes;
		}
		else if (x->right->p->right)
		{
			x->right->p->height = 1 + x->right->p->right->height;
			x->right->p->nodes = 1 + x->right->p->right->nodes;
		}
		else
		{
			x->right->p->height = 1;
			x->right->p->nodes = 1;
		}
	}

	x->p = y->p;
	if (x->p->left && x->p->right)
	{
		x->p->height = 1 + max(x->p->left->height, x->p->right->height);
		x->p->nodes = 1 + x->p->left->nodes + x->p->right->nodes;
	}
	else if (x->p->left)
	{
		x->p->height = 1 + x->p->left->height;
		x->p->nodes = 1 + x->p->left->nodes;
	}
	else if (x->p->right)
	{
		x->p->height = 1 + x->p->right->height;
		x->p->nodes = 1 + x->p->right->nodes;
	}
	else
	{
		x->p->height = 1;
		x->p->nodes = 1;
	}
	if (y->p == NILPTR)
		*treeroot = x;
	else if (y->p->left == y)
	{
		y->p->left = x;
		if (y->p->left && y->p->right)
		{
			y->p->height = 1 + max(y->p->left->height, y->p->right->height);
			y->p->nodes = 1 + y->p->left->nodes + y->p->right->nodes;
		}
		else if (y->p->left)
		{
			y->p->height = 1 + y->p->left->height;
			y->p->nodes = 1 + y->p->left->nodes;
		}
		else if (y->p->right)
		{
			y->p->height = 1 + y->p->right->height;
			y->p->nodes = 1 + y->p->right->nodes;
		}
		else
		{
			y->p->height = 1;
			y->p->nodes = 1;
		}
	}
	else
	{
		y->p->right = x;
		if (y->p->left && y->p->right)
		{
			y->p->height = 1 + max(y->p->left->height, y->p->right->height);
			y->p->nodes = 1 + y->p->left->nodes + y->p->right->nodes;
		}
		else if (y->p->left)
		{
			y->p->height = 1 + y->p->left->height;
			y->p->nodes = 1 + y->p->left->nodes;
		}
		else if (y->p->right)
		{
			y->p->height = 1 + y->p->right->height;
			y->p->nodes = 1 + y->p->right->nodes;
		}
		else
		{
			y->p->height = 1;
			y->p->nodes = 1;
		}
	}

	x->right = y;
	if (x->left && x->right)
	{
		x->height = 1 + max(x->left->height, x->right->height);
		x->nodes = 1 + x->left->nodes + x->right->nodes;
	}
	else if (x->left)
	{
		x->height = 1 + x->left->height;
		x->nodes = 1 + x->left->nodes;
	}
	else if (x->right)
	{
		x->height = 1 + x->right->height;
		x->nodes = 1 + x->right->nodes;
	}
	else
	{
		x->height = 1;
		x->nodes = 1;
	}
	y->p = x;
	if (y->p->left && y->p->right)
	{
		y->p->height = 1 + max(y->p->left->height, y->p->right->height);
		y->p->nodes = 1 + y->p->left->nodes + y->p->right->nodes;
	}
	else if (y->p->left)
	{
		y->p->height = 1 + y->p->left->height;
		y->p->nodes = 1 + y->p->left->nodes;
	}
	else if (y->right)
	{
		y->p->height = 1 + y->p->right->height;
		y->p->nodes = 1 + y->p->right->nodes;
	}
	else
	{
		y->p->height = 1;
		y->p->nodes = 1;
	}
}

void rbinsertfixup(NODEPTR *treeroot, NODEPTR z)
{
	while (z->p->color == RED)
	{
		if (z->p == z->p->p->left)
		{
			NODEPTR y = z->p->p->right;
			if (y->color == RED)
			{
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else
			{
				if (z == z->p->right)
				{
					z = z->p;
					leftrotate(treeroot, z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				rightrotate(treeroot, z->p->p);
			}
		}
		else
		{
			NODEPTR y = z->p->p->left;
			if (y->color == RED)
			{
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else
			{
				if (z == z->p->left)
				{
					z = z->p;
					rightrotate(treeroot, z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				leftrotate(treeroot, z->p->p);
			}
		}
	}
	(*treeroot)->color = BLACK;
}

void rbinsert(NODEPTR *treeroot, int z)
{
	NODEPTR Z = (NODEPTR)malloc(sizeof(struct node));
	Z->key = z;
	NODEPTR y = NILPTR;
	NODEPTR x = *treeroot;
	while (x != NILPTR)
	{
		y = x;
		if (Z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	Z->p = y;
	if (y == NILPTR)
		*treeroot = Z;
	else if (Z->key < y->key)
		y->left = Z;
	else
		y->right = Z;
	Z->left = NILPTR;
	Z->right = NILPTR;
	Z->color = RED;
	Z->height = 1;
	Z->nodes = 1;
	rbinsertfixup(treeroot, Z);
}

main()
{
	NIL.left = NIL.right = NIL.p = NILPTR;
	NIL.color = BLACK;
	NODEPTR tree = NILPTR;
	int n;
	ofstream HeightsVsNodes;
    HeightsVsNodes.open ("height_vs_nodes_rbtree.csv");
    HeightsVsNodes << "height,nodes\n";
	auto start = high_resolution_clock::now();
	for (int i = 0; i < 1048576; i++) {
		rbinsert(&tree, i);
		HeightsVsNodes << tree->height << "," << i << endl;
		}
		auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Red Black Tree inserting for 10^6 elements is : " << duration.count() <<"micro seconds" << endl;
	HeightsVsNodes.close();
	HeightsVsNodes.open ("rbtree_performance.csv");
	HeightsVsNodes << "nodes,time\n";
	tree = NILPTR;
	 start = high_resolution_clock::now();
	for (int i = 0; i < 16; i++) {
		rbinsert(&tree, i);
		}
		 stop = high_resolution_clock::now();
     duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Red Black Tree inserting for 10^6 elements is : " << duration.count() <<"micro seconds" << endl;
	HeightsVsNodes << duration.count() <<"," << 16 << endl;
	tree = NILPTR;
	 start = high_resolution_clock::now();
	for (int i = 0; i < 128; i++) {
		rbinsert(&tree, i);
		}
		 stop = high_resolution_clock::now();
     duration = duration_cast<microseconds>(stop - start);
    HeightsVsNodes << duration.count() <<"," << 128 << endl;
	cout << "Time taken by Red Black Tree inserting for 10^6 elements is : " << duration.count() <<"micro seconds" << endl;
	tree = NILPTR;
	 start = high_resolution_clock::now();
	for (int i = 0; i < 1024; i++) {
		rbinsert(&tree, i);
		}
		 stop = high_resolution_clock::now();
     duration = duration_cast<microseconds>(stop - start);
    HeightsVsNodes << duration.count() <<"," << 1024 << endl;
	cout << "Time taken by Red Black Tree inserting for 10^6 elements is : " << duration.count() <<"micro seconds" << endl;

	tree = NILPTR;
	 start = high_resolution_clock::now();
	for (int i = 0; i <16384; i++) {
		rbinsert(&tree, i);
		}
		 stop = high_resolution_clock::now();
     duration = duration_cast<microseconds>(stop - start);
    HeightsVsNodes << duration.count() <<"," << 16384 << endl;
	cout << "Time taken by Red Black Tree inserting for 10^6 elements is : " << duration.count() <<"micro seconds" << endl;
	tree = NILPTR;
	 start = high_resolution_clock::now();
	for (int i = 0; i < 131072; i++) {
		rbinsert(&tree, i);
		}
		 stop = high_resolution_clock::now();
     duration = duration_cast<microseconds>(stop - start);
	HeightsVsNodes << duration.count() <<"," << 131072 << endl;
    cout << "Time taken by Red Black Tree inserting for 10^6 elements is : " << duration.count() <<"micro seconds" << endl;
	tree = NILPTR;
	 start = high_resolution_clock::now();
	for (int i = 0; i < 1048575; i++) {
		rbinsert(&tree, i);
		}
	stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
	HeightsVsNodes << duration.count() <<"," << 1048575 << endl;
    cout << "Time taken by Red Black Tree inserting for 10^6 elements is : " << duration.count() <<"micro seconds" << endl;
	HeightsVsNodes.close();
	
	// while (1)
	// {
	// 	printf("1.Insert\n2.Inorder Walk");
	// 	scanf("%d", &n);
	// 	if (n == 1)
	// 	{
	// 		printf("Enter any number:\n");
	// 		int num;
	// 		scanf("%d", &num);
	// 		rbinsert(&tree, num);
	// 	}

	// 	else if (n == 2)
	// 	{
	// 		inorder(tree);
	// 		printf("\n");
	// 	}
	// 	cout << tree->height << "," << tree->nodes << endl;
	// }

	return 0;
}

