#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>
#include<math.h>
#include<fstream>
#include<chrono>
#include <ctime>
using namespace std::chrono;
using namespace std;

struct avl_tree_node *update_balances(struct avl_tree_node *);
struct avl_tree_node *update_heights(struct avl_tree_node *);

int k_small;

int max(int a, int b)
{
    if (a >= b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

struct avl_tree_node // Data structure of AVL tree node

{
    int data;                    //value
    struct avl_tree_node *left;  //left sub tree
    struct avl_tree_node *right; // right sub ree
    int height;                  // height of the node
    int balance;                 // Balance i.e, abs(height(left sub tree) - height(right sub tree))
    int left_nodes;              //total no of nodes to left of node
    int total_nodes;             //total no of nodes under the node
} * root;

struct avl_tree_node *balance(struct avl_tree_node *);

struct avl_tree_node *bst_delete(int, struct avl_tree_node *);

class avl_tree // avl tree class
{
  public:
    avl_tree()

    {

        root = NULL; //inititalization of root to NULL
    }

    struct avl_tree_node *delete_node(int val, struct avl_tree_node *node)
    {

        if (node == NULL) // base case if no node is found just dont do anything
        {
            return node;
        }
        if (node->data > val) // search in left sub tree
        {

            node->left = delete_node(val, node->left);
        }
        else if (node->data < val) // search in right sub tree
        {

            node->right = delete_node(val, node->right);
        }
        else if (node->data == val) // the node is foun no delete
        {
            if (!node->left && !node->right) // if both left sub tree and right sub tree doesnt exist
            {
                avl_tree_node *temp = NULL;
                free(node);
                node = temp; // just delete the node
            }
            else if (!node->right && node->left) // if right subtree doesnt exist
            {
                avl_tree_node *temp = node;
                free(node);
                node = temp->left; // just delete and assign left subtree to the parent
            }
            else if (node->right) // if right subtree exists
            {
                avl_tree_node *temp = node;
                temp = temp->right;
                while (temp->left != NULL)
                {
                    temp = temp->left;
                }
                int data = temp->data; //find the inorder successor and replace the node

                node->right = delete_node(data, node->right); //delete the inorder successor.
                node->data = data;
            }
        }

        if (node) //checks in each if else conditional to avoid segfault, updates heights and node
        {
            if (node->left && node->right)
            {
                node->height = 1 + max(node->left->height, node->right->height);            //check to avoid segfault
                node->left_nodes = 1 + node->left->total_nodes;                             //update left nodes
                node->total_nodes = 1 + node->left->total_nodes + node->right->total_nodes; //upate total nodes
            }
            else if (node->left) //check to avoid segfault
            {
                node->height = 1 + node->left->height;           //check to avoid segfault
                node->left_nodes = 1 + node->left->total_nodes;  //update left nodes
                node->total_nodes = 1 + node->left->total_nodes; //upate total nodes
            }
            else if (node->right) //check to avoid segfault
            {
                node->height = 1 + node->right->height;           //check to avoid segfault
                node->left_nodes = 1;                             //update left nodes
                node->total_nodes = 1 + node->right->total_nodes; //upate total nodes
            }
            else if (!node->left && !node->right) //check to avoid segfault
            {
                node->height = 0;      //check to avoid segfault
                node->left_nodes = 1;  //update left nodes
                node->total_nodes = 1; //upate total nodes
            }

            if (node->left && node->right) //check to avoid segfault
            {
                node->balance = node->left->height - node->right->height;
            }
            else if (node->left) //check to avoid segfault
            {
                node->balance = 1 + node->left->height;
            }
            else if (node->right) //check to avoid segfault
            {
                node->balance = -node->right->height - 1;
            }
            else if (!node->left && !node->right) //check to avoid segfault
            {
                node->balance = 0;
            }

            if (abs(node->balance) > 1) //balances the tree if the node is imbalanced
            {

                node = balance(node);
            }
        }

        return node;
    }

    struct avl_tree_node *insert_node(int val, struct avl_tree_node *node)
    {
        //insert the node after searching for its position
        if (node == NULL)

        {
            node = new avl_tree_node;
            node->data = val;
            node->left = NULL;
            node->right = NULL;
            node->height = 0;
            node->balance = 0;
            node->left_nodes = 1;
            node->total_nodes = 1;
            return node;
        }
        //searches for function in left sub tree if the key is
        //less than current nodes value
        else if (node->data > val)
        {
            node->left = insert_node(val, node->left);
        }
        //searches for function in right sub tree if the key is
        //greater than current nodes value
        else if (node->data < val)
        {
            node->right = insert_node(val, node->right);
        }
        else
        {
            return node;
        }
        //all the conditions in the if else conditionals
        //below is to avoid segfault, the basic formula
        //for updating heights remaining is same
        if (node->left && node->right)
        {
            node->height = 1 + max(node->left->height, node->right->height);
            node->left_nodes = 1 + node->left->total_nodes;
            node->total_nodes = 1 + node->left->total_nodes + node->right->total_nodes;
        }
        else if (node->left)
        {
            node->height = 1 + node->left->height;
            node->left_nodes = 1 + node->left->total_nodes;
            node->total_nodes = 1 + node->left->total_nodes;
        }
        else if (node->right)
        {
            node->height = 1 + node->right->height;
            node->left_nodes = 1;
            node->total_nodes = 1 + node->right->total_nodes;
        }
        else
        {
            node->height = 0;
            node->left_nodes = 1;
            node->total_nodes = 1;
        }
        //all the conditions in the if else conditionals
        //below is to avoid segfault, the basic formula for
        //updating balances remaining is same

        if (node->left && node->right)
        {
            node->balance = node->left->height - node->right->height;
        }
        else if (node->left)
        {
            node->balance = 1 + node->left->height;
        }
        else if (node->right)
        {
            node->balance = -node->right->height - 1;
        }
        else
        {
            node->balance = 0;
        }
        // balance by performing rotations if the height
        // difference is greater than one
        if (abs(node->balance) > 1)
        {
            node = balance(node);
        }

        return node;
    }
    // normal search function that gives 1 if the element is found else 0
    int search(int data, struct avl_tree_node *node)
    {
        int isThere;
        if (node == NULL)
        {
            isThere = 0;
        }
        else if (node->data > data)
        {
            isThere = search(data, node->left);
        }
        else if (node->data < data)
        {
            isThere = search(data, node->right);
        }
        else if (node->data == data)
        {
            isThere = 1;
        }
        return isThere;
    }

    //helper function gives the kth smallest element in the tree
    struct avl_tree_node *searchKsmall(int index, struct avl_tree_node *root)
    {
        avl_tree_node *temp = root;
        avl_tree_node *dummy;
        avl_tree_node *ret;
        int flag = 1;

        while (flag)
        {
            if (temp->left_nodes > index)
            {
                temp = temp->left;
            }
            else if (temp->left_nodes < index)
            {
                index = index - temp->left_nodes;
                temp = temp->right;
            }
            else if (temp->left_nodes == index)
            {
                k_small = temp->data;
                ret = delete_node(temp->data, root);
                flag = 0;
            }
        }
        return ret;
    }
};

//updates the balances after rotations performed
//the checks are for avoiding segfaults
//tha basic formula for updating the balance remains the same
struct avl_tree_node *update_balances(struct avl_tree_node *node)
{
    if (!node->right && node->left)
    {
        if (node->left->left && node->left->right)
        {
            node->left->balance = node->left->left->height - node->left->right->height;
        }
        else if (node->left->left)
        {
            node->left->balance = node->left->left->height + 1;
        }
        else if (node->left->right)
        {
            node->left->balance = -node->left->right->height - 1;
        }
        else if (!node->left->right && !node->left->left)
        {
            node->left->balance = 0;
        }
        node->balance = node->left->height;
    }
    if (node->right && !node->left)
    {
        if (node->right->left && node->right->right)
        {
            node->right->balance = node->right->left->height - node->right->right->height;
        }
        else if (node->right->left)
        {
            node->right->balance = node->right->left->height + 1;
        }
        else if (node->right->right)
        {
            node->right->balance = -node->right->right->height - 1;
        }
        else if (!node->right->right && !node->right->left)
        {
            node->right->balance = 0;
        }
        node->balance = -node->right->height;
    }
    if (node->left && node->right)
    {
        if (node->left->left && node->left->right)
        {
            node->left->balance = node->left->left->height - node->left->right->height;
        }
        else if (node->left->left)
        {
            node->left->balance = node->left->left->height + 1;
        }
        else if (node->left->right)
        {
            node->left->balance = -node->left->right->height - 1;
        }
        else if (!node->left->right && !node->left->left)
        {
            node->left->balance = 0;
        }
        if (node->right->left && node->right->right)
        {
            node->right->balance = node->right->left->height - node->right->right->height;
        }
        else if (node->right->left)
        {
            node->right->balance = node->right->left->height + 1;
        }
        else if (node->right->right)
        {
            node->right->balance = -node->right->right->height - 1;
        }
        else if (!node->right->right && !node->right->left)
        {
            node->right->balance = 0;
        }
        node->balance = node->left->height - node->right->height;
    }

    if (!node->right && !node->left)
    {
        node->balance = 0;
    }

    return node;
}

//updates the heights after rotations performed
//the checks are for avoiding segfaults
//tha basic formula for updating the heights remains the same
struct avl_tree_node *update_heights(struct avl_tree_node *node)
{

    if (node->right && !node->left)
    {
        if (node->right->right && node->right->left)
        {
            node->right->height = 1 + max(node->right->right->height, node->right->left->height);
            node->right->left_nodes = 1 + node->right->left->total_nodes;
            node->right->total_nodes = 1 + node->right->left->total_nodes + node->right->right->total_nodes;
        }
        else if (!node->right->right && node->right->left)
        {
            node->right->height = 1 + node->right->left->height;
            node->right->left_nodes = 1 + node->right->left->total_nodes;
            node->right->total_nodes = 1 + node->right->left->total_nodes;
        }
        else if (node->right->right && !node->right->left)
        {
            node->right->height = 1 + node->right->right->height;
            node->right->left_nodes = 1;
            node->right->total_nodes = 1 + node->right->right->total_nodes;
        }
        else
        {
            node->right->height = 0;
            node->right->left_nodes = 1;
            node->right->total_nodes = 1;
        }
        node->height = 1 + node->right->height;
        node->left_nodes = 1;
        node->total_nodes = 1 + node->right->total_nodes;
    }

    if (node->left && !node->right)
    {
        if (node->left->right && node->left->left)
        {
            node->left->height = 1 + max(node->left->right->height, node->left->left->height);
            node->left->left_nodes = 1 + node->left->left->total_nodes;
            node->left->total_nodes = 1 + node->left->left->total_nodes + node->left->right->total_nodes;
        }
        else if (!node->left->right && node->left->left)
        {
            node->left->height = 1 + node->left->left->height;
            node->left->left_nodes = 1 + node->left->left->total_nodes;
            node->left->total_nodes = 1 + node->left->left->total_nodes;
        }
        else if (node->left->right && !node->left->left)
        {
            node->left->height = 1 + node->left->right->height;
            node->left->left_nodes = 1;
            node->left->total_nodes = 1 + node->left->right->total_nodes;
        }
        else
        {
            node->left->height = 0;
            node->left->left_nodes = 1;
            node->left->total_nodes = 1;
        }
        node->height = 1 + node->left->height;
        node->left_nodes = 1 + node->left->total_nodes;
        node->total_nodes = 1 + node->left->total_nodes;
    }

    if (node->right && node->left)
    {
        if (node->right->right && node->right->left)
        {
            node->right->height = 1 + max(node->right->right->height, node->right->left->height);
            node->right->left_nodes = 1 + node->right->left->total_nodes;
            node->right->total_nodes = 1 + node->right->left->total_nodes + node->right->right->total_nodes;
        }
        else if (!node->right->right && node->right->left)
        {
            node->right->height = 1 + node->right->left->height;
            node->right->left_nodes = 1 + node->right->left->total_nodes;
            node->right->total_nodes = 1 + node->right->left->total_nodes;
        }
        else if (node->right->right && !node->right->left)
        {
            node->right->height = 1 + node->right->right->height;
            node->right->left_nodes = 1;
            node->right->total_nodes = 1 + node->right->right->total_nodes;
        }
        else
        {
            node->right->height = 0;
            node->right->left_nodes = 1;
            node->right->total_nodes = 1;
        }

        if (node->left->right && node->left->left)
        {
            node->left->height = 1 + max(node->left->right->height, node->left->left->height);
            node->left->left_nodes = 1 + node->left->left->total_nodes;
            node->left->total_nodes = 1 + node->left->left->total_nodes + node->left->right->total_nodes;
        }
        else if (!node->left->right && node->left->left)
        {
            node->left->height = 1 + node->left->left->height;
            node->left->left_nodes = 1 + node->left->left->total_nodes;
            node->left->total_nodes = 1 + node->left->left->total_nodes;
        }
        else if (node->left->right && !node->left->left)
        {
            node->left->height = 1 + node->left->right->height;
            node->left->left_nodes = 1;
            node->left->total_nodes = 1 + node->left->right->total_nodes;
        }
        else
        {
            node->left->height = 0;
            node->left->left_nodes = 1;
            node->left->total_nodes = 1;
        }

        node->height = 1 + max(node->left->height, node->right->height);
        node->left_nodes = 1 + node->left->total_nodes;
        node->total_nodes = 1 + node->right->total_nodes + node->left->total_nodes;
    }

    if (!node->right && !node->left)
    {
        node->height = 1;
        node->left_nodes = 1;
        node->total_nodes = 1;
    }

    return node;
}
// RR rotation performed when the balance factor
// of root is -2 and that of root of right subtree is -1
struct avl_tree_node *R_R_rotate(struct avl_tree_node *node)
{
    avl_tree_node *temp_left = node;
    avl_tree_node *temp_right_left = node->right->left;
    avl_tree_node *temp_root = node->right;
    avl_tree_node *temp_right = node->right->right;
    node = temp_root;
    node->left = temp_left;
    node->left->right = temp_right_left;
    node->right = temp_right;
    node = update_heights(node);
    node = update_balances(node);
    return node;
}

// LL rotation performed when the balance factor
// of root is +2 and that of root of left subtree is +1
struct avl_tree_node *L_L_rotate(struct avl_tree_node *node) // LL rotation performed when the balance factor is +2
{
    avl_tree_node *temp_right = node;
    avl_tree_node *temp_root = node->left;
    avl_tree_node *temp_left_right = node->left->right;
    avl_tree_node *temp_left = node->left->left;
    node = temp_root;
    node->left = temp_left;
    node->right = temp_right;
    node->right->left = temp_left_right;
    node = update_heights(node);
    node = update_balances(node);
    return node;
}

// LR rotation performed when the balance factor
// of root is +2 and that of root of left subtree is -1
struct avl_tree_node *L_R_rotate(struct avl_tree_node *node) //
{
    avl_tree_node *temp_right = node;
    avl_tree_node *temp_root = node->left->right;
    avl_tree_node *temp_left = node->left;
    avl_tree_node *temp_left_right_left = node->left->right->left;
    avl_tree_node *temp_left_right_right = node->left->right->right;
    node = temp_root;
    node->left = temp_left;
    node->right = temp_right;
    node->left->right = temp_left_right_left;
    node->right->left = temp_left_right_right;
    node = update_heights(node);
    node = update_balances(node);
    return node;
}

// RL rotation performed when the balance factor
// of root is -2 and that of root of right subtree is +1
struct avl_tree_node *R_L_rotate(struct avl_tree_node *node)
{
    avl_tree_node *temp_left = node;
    avl_tree_node *temp_root = node->right->left;
    avl_tree_node *temp_right = node->right;
    avl_tree_node *temp_right_left_left = node->right->left->left;
    avl_tree_node *temp_right_left_right = node->right->left->right;
    node = temp_root;
    node->left = temp_left;
    node->right = temp_right;
    node->left->right = temp_right_left_left;
    node->right->left = temp_right_left_right;
    node = update_heights(node);
    node = update_balances(node);
    return node;
}

//balance function which checks for the appropriate 
// balance condition and performs that particular rotation.
struct avl_tree_node *balance(struct avl_tree_node *node)
{

    avl_tree_node *temp = NULL;
    if (node->left && node->right)
    {
        if (node->balance > 1 && node->left->balance < 0)
        {
            temp = L_R_rotate(node);
        }
        if (node->balance > 1 && node->left->balance >= 0)
        {

            temp = L_L_rotate(node);
        }
        if (node->balance < -1 && node->right->balance > 0)
        {

            temp = R_L_rotate(node);
        }
        if (node->balance < -1 && node->right->balance <= 0)
        {

            temp = R_R_rotate(node);
        }
    }

    else if (node->right)
    {

        if (node->balance < -1 && node->right->balance > 0)
        {

            temp = R_L_rotate(node);
        }
        if (node->balance < -1 && node->right->balance <= 0)
        {

            temp = R_R_rotate(node);
        }
    }

    else if (node->left)
    {
        if (node->balance > 1 && node->left->balance < 0)
        {

            temp = L_R_rotate(node);
        }
        if (node->balance > 1 && node->left->balance >= 0)
        {

            temp = L_L_rotate(node);
        }
    }

    return temp;
}



int main()
{
    avl_tree avl;
    ofstream HeightsVsNodes;
    HeightsVsNodes.open ("height_vs_nodes_avl.csv");
    HeightsVsNodes << "height,nodes\n";
    auto start = high_resolution_clock::now();

	for (int i = 0; i < 1048576; i++) {
		root = avl.insert_node(i, root);
		//cout << root->height << " " << root->total_nodes << endl;
		HeightsVsNodes << root->height << "," << root->total_nodes << endl;
		}
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by AVL tree for inserting for 10^6 elements is : " << duration.count() <<"micro seconds" << endl;
	//cout << root->height << endl;
	HeightsVsNodes.close();
    HeightsVsNodes.open ("avltree_performance.csv");
	HeightsVsNodes << "nodes,time\n";
	root = NULL;
	 start = high_resolution_clock::now();
	for (int i = 0; i < 16; i++) {
		root = avl.insert_node(i, root);
		}
		 stop = high_resolution_clock::now();
     duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Red Black Tree inserting for 10^6 elements is : " << duration.count() <<"micro seconds" << endl;
	HeightsVsNodes << duration.count() <<"," << 16 << endl;
	root = NULL;
	 start = high_resolution_clock::now();
	for (int i = 0; i < 128; i++) {
		root = avl.insert_node(i, root);
		}
		 stop = high_resolution_clock::now();
     duration = duration_cast<microseconds>(stop - start);
    HeightsVsNodes << duration.count() <<"," << 128 << endl;
	cout << "Time taken by Red Black Tree inserting for 10^6 elements is : " << duration.count() <<"micro seconds" << endl;
	root = NULL;
	 start = high_resolution_clock::now();
	for (int i = 0; i < 1024; i++) {
		root = avl.insert_node(i, root);
		}
		 stop = high_resolution_clock::now();
     duration = duration_cast<microseconds>(stop - start);
    HeightsVsNodes << duration.count() <<"," << 1024 << endl;
	cout << "Time taken by Red Black Tree inserting for 10^6 elements is : " << duration.count() <<"micro seconds" << endl;

	root = NULL;
	 start = high_resolution_clock::now();
	for (int i = 0; i <16384; i++) {
		root = avl.insert_node(i, root);
		}
		 stop = high_resolution_clock::now();
     duration = duration_cast<microseconds>(stop - start);
    HeightsVsNodes << duration.count() <<"," << 16384 << endl;
	cout << "Time taken by Red Black Tree inserting for 10^6 elements is : " << duration.count() <<"micro seconds" << endl;
	root = NULL;
	 start = high_resolution_clock::now();
	for (int i = 0; i < 131072; i++) {
		root = avl.insert_node(i, root);
		}
		 stop = high_resolution_clock::now();
     duration = duration_cast<microseconds>(stop - start);
	HeightsVsNodes << duration.count() <<"," << 131072 << endl;
    cout << "Time taken by Red Black Tree inserting for 10^6 elements is : " << duration.count() <<"micro seconds" << endl;
	root = NULL;
	 start = high_resolution_clock::now();
	for (int i = 0; i < 1048575; i++) {
		root = avl.insert_node(i, root);
		}
		 stop = high_resolution_clock::now();
     duration = duration_cast<microseconds>(stop - start);
	HeightsVsNodes << duration.count() <<"," << 1048575 << endl;
    cout << "Time taken by Red Black Tree inserting for 10^6 elements is : " << duration.count() <<"micro seconds" << endl;
	HeightsVsNodes.close();
	
    // int size, queries;
    // cin >> size >> queries;
    // for (int i = 0; i < size; i++)
    // {
    //     int val;
    //     cin >> val;
    //     root = avl.insert_node(val, root);
    // }

    // for (int i = 0; i < queries; i++)
    // {
    //     int que, data;
    //     cin >> que >> data;
    //     if (que == 1)
    //     {
    //         root = avl.insert_node(data, root);
    //     }
    //     else if (que == 2)
    //     {
    //         int p = avl.search(data, root);
    //         cout << p << "\n";
    //     }
    //     else if (que == 3)
    //     {
    //         root = avl.searchKsmall(data, root);
    //         cout << k_small << "\n";
    //     }
    // }
}

