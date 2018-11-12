#include <bits/stdc++.h>
#include <math.h>
#include <fstream>
#include <chrono>
#include <ctime>
#include <time.h>
using namespace std::chrono;
using namespace std;

ofstream HeightsVsNodesInsert;
ofstream HeightsVsNodesDelete;

ofstream quickinsert;

ofstream avg_delete;

ofstream avg_insert;

struct BStreeNode // a structure for the representation of nodes of a randomized BST
{
    int value;
    int size;
    int height;
    struct BStreeNode *left;
    struct BStreeNode *right;
} * root;

int RandomTime()
{
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);

    return nanoseconds.count();
}

int Random()
{

    srand(RandomTime());
    return rand();
    
}

class BStree
{
  public:
    BStree()
    {
        root = NULL;
    }

    int GetSize(struct BStreeNode *node)
    {
        if (!node)
            return 0;

        return node->size;
    }

    int GetHeight(struct BStreeNode *node)
    {
        if (!node)
            return 0;

        return node->height;
    }

    struct BStreeNode *ModifySize(struct BStreeNode *node)
    {

        node->size = GetSize(node->left) + GetSize(node->right) + 1;
        return node;
    }

    struct BStreeNode *ModifyHeight(struct BStreeNode *node)
    {

        node->height = max(GetHeight(node->left), GetHeight(node->right)) + 1;
        //cout << node->value << endl;
        //		/cout << node->height << endl;
        return node;
    }

    struct BStreeNode *rotateright(struct BStreeNode *node)
    {

        BStreeNode *temp = node->left;
        if (!temp)
        {
            return node;
        }
        node->left = temp->right;
        temp->right = node;
        temp->size = node->size;
        temp->height = node->height;
        node = ModifySize(node);
        node = ModifyHeight(node);
        temp = ModifySize(temp);
        temp = ModifyHeight(temp);
        return temp;
    }

    struct BStreeNode *rotateleft(struct BStreeNode *node)
    {

        BStreeNode *temp = node->right;
        if (!temp)
        {
            return node;
        }
        node->right = temp->left;
        temp->left = node;
        temp->size = node->size;
        temp->height = node->height;
        node = ModifySize(node);
        node = ModifyHeight(node);
        temp = ModifySize(temp);
        temp = ModifyHeight(temp);
        return temp;
    }

    struct BStreeNode* InsertRoot(int val, struct BStreeNode* node) {

    	if (node == NULL) {
    		node = new BStreeNode;
    		node->value = val;
    		node->left = NULL;
    		node->right = NULL;
    		node->height = 1;
    		node->size = 1;
    		return node;
    	}

    	if (node->value > val) {
    		node->left = InsertRoot(val, node->left);
    		return rotateright(node);
    	} else {
    		node->right = InsertRoot(val, node->right);
    		return rotateleft(node);
    	}

    }

    struct BStreeNode *Insert(int val, struct BStreeNode *node)
    {

        if (node == NULL)
        {
            node = new BStreeNode;
            node->value = val;
            node->left = NULL;
            node->right = NULL;
            node->height = 1;
            node->size = 1;
            return node;
        }
        if (Random() % (node->size + 1) == 0) {
        	return InsertRoot(val, node);
        }

        if (node->value > val)
        {
            node->left = Insert(val, node->left);
        }
        else if (node->value < val)
        {
            node->right = Insert(val, node->right);
        }

        node = ModifySize(node);
        node = ModifyHeight(node);
        return node;
    }

    struct BStreeNode *QuickInsert(int val, struct BStreeNode *node)
    {

        if (node == NULL)
        {
            node = new BStreeNode;
            node->value = val;
            node->left = NULL;
            node->right = NULL;
            node->height = 1;
            node->size = 1;
            return node;
        }
        // if (Random(rand_flag) % (node->size + 1) == 0) {
        // 	return InsertRoot(val, node);
        // }

        if (node->value > val)
        {
            node->left = QuickInsert(val, node->left);
        }
        else if (node->value < val)
        {
            node->right = QuickInsert(val, node->right);
        }

        node = ModifySize(node);
        node = ModifyHeight(node);
        return node;
    }

    
    
    
    
    struct BStreeNode *InorderSuccessor(int val, struct BStreeNode *node)
    {

        if (node->right == NULL && node->left == NULL)
        {
            BStreeNode *temp = NULL;
            free(node);
            node = temp;
        }
        else if (node->right == NULL)
        {
            BStreeNode *temp = node->left;
            free(node);
            node = temp;
        }
        else
        {
            BStreeNode *temp = node;
            temp = temp->right;
            while (temp->left != NULL)
            {
                temp = temp->left;
            }
            int successor = temp->value;
            node->right = Delete(successor, node->right);
            node->value = successor;
        }
        return node;
    }

    struct BStreeNode *Join(struct BStreeNode *left , struct BStreeNode *right)
    {
        if(!left)
        {
            return right;
        }
        if(!right)
        {
            return left;
        }
        srand(RandomTime());
        if(rand()%(left->size + right->size) < left->size)
        {
            left->right = Join(left->right, right);
            left = ModifyHeight(left);
            left = ModifySize(left);
            return left;
        }
        else
        {
            right->left = Join(left,right->left);
            right = ModifyHeight(right);
            right = ModifySize(right);
            return right;

        }
    }

    
    
    struct BStreeNode *Remove(struct BStreeNode* node , int k)
    {
        if(!node)
        {
            return node;
        }
        if(node->value == k)
        {
            BStreeNode * temp = Join(node->left,node->right);
            delete node;
            return temp;
        }
        else if(node->value > k)
        {
            node->left = Remove(node->left , k);
        }
        else
        {
            node->right = Remove(node->right , k);
        }

    return node;


    }
    
    
    
    
    
    struct BStreeNode *Delete(int val, struct BStreeNode *node)
    {

        if (node == NULL)
        {
            return node;
        }
        else if (node->value > val)
        {
            node = Delete(val, node->right);
        }
        else if (node->value < val)
        {
            node = Delete(val, node->left);
        }
        else
        {
            node = InorderSuccessor(val, node);
        }
        return node;
    }

    bool Search(int val, struct BStreeNode *node)
    {

        bool tmp;
        if (node == NULL)
        {
            tmp = false;
        }
        else
        {
            if (node->value > val)
            {
                tmp = Search(val, node->right);
            }
            if (node->value < val)
            {
                tmp = Search(val, node->left);
            }
            if (node->value == val)
            {
                tmp = true;
            }
        }

        return tmp;
    }
};

int random_pivot(int n, int L)
{
    srand(RandomTime());
    return rand() % n;
}

int partition(int L, int R)
{
    int rand;
    if (R > L)
    {
        rand = L + random_pivot(R - L + 1, L);
    }
    return rand;
}

struct BStreeNode* quick_insert(int L, int R, struct BStreeNode *node, BStree Bst, bool flag)
{

    if (R > L)
    {
        int pivot = partition(L, R);
        node = Bst.QuickInsert(pivot, node);
        node->left = quick_insert(L, pivot - 1, node->left, Bst, flag);
        node->right = quick_insert(pivot + 1, R, node->right, Bst, flag); 
        node = Bst.ModifyHeight(node);
        node = Bst.ModifySize(node);
    }
    else if(R == L)
    {
        node = Bst.QuickInsert(L, node);
        //HeightsVsNodes << node->height << "," << node->size << endl;
     }
    
    return node;
}

int main(int argn , char *argv[])
{
    cin.tie(0);
    cout.tie(0);
    
     if(argn > 2)
    {
        cerr << "Too many arguments : only file name is expected , exiting program " << endl;
        exit(EXIT_FAILURE);
    }
    if(argn == 2)
    {
    BStree Bst;
    bool flag = false;
    auto start = high_resolution_clock::now();
    root = quick_insert(0, 1048575, root, Bst, flag);
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by quick insert for 10^6 elemnts is : " << duration.count() << endl;
    
    string file_path = argv[1];
    ifstream myReadFile;
    myReadFile.open(file_path);
    string x;
    root = NULL;
    start = high_resolution_clock::now();
    HeightsVsNodesInsert.open ("height_vs_nodes_insert.csv");
    HeightsVsNodesInsert << "height,nodes\n";
    int count = 0;
 if (myReadFile.is_open()) {
 while (!myReadFile.eof()) {


    getline(myReadFile,x);
    if(x != "")
    {
    int y = atoi(x.c_str());
    
    root = Bst.Insert(y, root);
    HeightsVsNodesInsert << root->height << "," << count << endl;
    
    }
    
count = count + 1;

 }
}
myReadFile.close();
HeightsVsNodesInsert.close();
stop = high_resolution_clock::now();
duration = duration_cast<microseconds>(stop - start);
cout << "Time taken by Rotation Insert(Dynamic) in randomized binary search tree for 10^6 elemnts is : " << duration.count() << endl;    
HeightsVsNodesDelete.open ("height_vs_nodes_delete.csv");
HeightsVsNodesDelete<< "height,nodes\n";
start = high_resolution_clock::now();
for (int i = 1048575; i >= 1; i--) {
			root = Bst.Remove(root,i);
            HeightsVsNodesDelete << root->height << "," << i << endl;		
	}
stop = high_resolution_clock::now();
duration = duration_cast<microseconds>(stop - start);
HeightsVsNodesDelete.close();
cout << "Time taken by Rotation Delete(Dynamic) in randomized binary search tree for 10^6 elemnts is : "  << duration.count() << endl;



quickinsert.open ("quick_insert_time.csv");
quickinsert << "size,time\n";
root = NULL;
start = high_resolution_clock::now();
root = quick_insert(0, 16, root, Bst, flag);
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
quickinsert << 16 << "," << duration.count() << endl;
cout << "Time taken by quick insert for 16 elemnts is  " << duration.count() << endl;
root = NULL;
start = high_resolution_clock::now();
root = quick_insert(0, 128, root, Bst, flag);
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
quickinsert << 128 << "," << duration.count() << endl;
cout << "Time taken by quick insert for 128 elemnts is " << duration.count() << endl;
root = NULL;
start = high_resolution_clock::now();
root = quick_insert(0, 1024, root, Bst, flag);
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
quickinsert << 1024 << "," << duration.count() << endl;
cout << "Time taken by quick insert for 1024 elemnts is " << duration.count() << endl;
root = NULL;
start = high_resolution_clock::now();
root = quick_insert(0, 16384, root, Bst, flag);
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
quickinsert << 16384 << "," << duration.count() << endl;
cout << "Time taken by quick insert for 16384 elemnts is " << duration.count() << endl;
root = NULL;
start = high_resolution_clock::now();
root = quick_insert(0,131072, root, Bst, flag);
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
quickinsert << 131072 << "," << duration.count() << endl;
cout << "Time taken by quick insert for 131072 elemnts is " << duration.count() << endl;
root = NULL;
start = high_resolution_clock::now();
root = quick_insert(0, 1048575, root, Bst, flag);
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
quickinsert <<  1048575 << "," << duration.count() << endl;
cout << "Time taken by quick insert for 1048575 elements is  " << duration.count() << endl;
quickinsert.close();

avg_insert.open ("rotate_insert_time.csv");
avg_insert << "size,time\n";
avg_delete.open ("rotate_delete_time.csv");
avg_delete << "size,time\n";
root = NULL;
start = high_resolution_clock::now();
for (int i = 0; i < 16; i++) {
			root = Bst.Insert(i, root);
		}
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
cout << "Time taken by Rotation Insert(Dynamic) in randomized binary search tree for 16 elemnts is : " << duration.count() << endl;
avg_insert<< 16 << "," << duration.count() << endl;
start = high_resolution_clock::now();
for (int i = 16; i >= 1; i--) {
			root = Bst.Remove(root,i);	
	}
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
avg_delete<< 16 << "," << duration.count() << endl;
cout << "Time taken by Rotation Delete(Dynamic) in randomized binary search tree for 16 elemnts is : " << duration.count() << endl;


root = NULL;
start = high_resolution_clock::now();
for (int i = 0; i < 128; i++) {
			root = Bst.Insert(i, root);
		}
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
avg_insert<< 128 << "," << duration.count() << endl;
cout << "Time taken by Rotation Insert(Dynamic) in randomized binary search tree for 128 elemnts is : " << duration.count() << endl;
start = high_resolution_clock::now();
for (int i = 128; i >= 1; i--) {
			root = Bst.Remove(root,i);		
	}
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
avg_delete<< 128 << "," << duration.count() << endl;
cout << "Time taken by Rotation Delete(Dynamic) in randomized binary search tree for 128 elemnts is : " << duration.count() << endl;

root = NULL;
start = high_resolution_clock::now();
for (int i = 0; i < 1024; i++) {
			root = Bst.Insert(i, root);
		}
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
avg_insert<< 1024 << "," << duration.count() << endl;
cout << "Time taken by Rotation Insert(Dynamic) in randomized binary search tree for 1024 elemnts is : " << duration.count() << endl;
start = high_resolution_clock::now();
for (int i = 1024; i >= 1; i--) {
			root = Bst.Remove(root,i);		
	}
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
avg_delete<< 1024 << "," << duration.count() << endl;
cout << "Time taken by Rotation Delete(Dynamic) in randomized binary search tree for 1024 elemnts is : " << duration.count() << endl;
root = NULL;
start = high_resolution_clock::now();
for (int i = 0; i < 16384; i++) {
			root = Bst.Insert(i, root);
		}
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
avg_insert<< 16384 << "," << duration.count() << endl;
cout << "Time taken by Rotation Insert(Dynamic) in randomized binary search tree for 16384 elemnts is : " << duration.count() << endl;
start = high_resolution_clock::now();
for (int i = 16384; i >= 1; i--) {
			root = Bst.Remove(root,i);		
	}
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
avg_delete<< 16384 << "," << duration.count() << endl;
cout << "Time taken by Rotation Delete(Dynamic) in randomized binary search tree for 16384 elemnts is : " << duration.count() << endl;

root = NULL;
start = high_resolution_clock::now();
for (int i = 0; i < 131072; i++) {
			root = Bst.Insert(i, root);
		}
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
avg_insert<< 131072 << "," << duration.count() << endl;
cout << "Time taken by Rotation Insert(Dynamic) in randomized binary search tree for 131072 elemnts is : " << duration.count() << endl;
start = high_resolution_clock::now();
for (int i = 131072; i >= 1; i--) {
			root = Bst.Remove(root,i);		
	}
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
avg_delete<< 131072 << "," << duration.count() << endl;
cout << "Time taken by Rotation Delete(Dynamic) in randomized binary search tree for 131072 elemnts is : " << duration.count() << endl;

root = NULL;
start = high_resolution_clock::now();
for (int i = 0; i < 1048575; i++) {
			root = Bst.Insert(i, root);
		}
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
avg_insert<< 1048575 << "," << duration.count() << endl;
cout << "Time taken by Rotation Insert(Dynamic) in randomized binary search tree for 1048575 elemnts is : " << duration.count() << endl;
start = high_resolution_clock::now();
for (int i = 16384; i >= 1; i--) {
			root = Bst.Remove(root,i);		
	}
stop = high_resolution_clock::now(); 
duration = duration_cast<microseconds>(stop - start);
avg_delete<< 1048575 << "," << duration.count() << endl;
cout << "Time taken by Rotation Delete(Dynamic) in randomized binary search tree for 1048575 elemnts is : " << duration.count() << endl;
avg_insert.close();
avg_delete.close();
    // }
    // HeightsVsNodes.open ("height_vs_nodes_avg_quick_insert.csv");
    // HeightsVsNodes << "height,nodes\n";
    // for(int i = 0 ; i < 200 ; i++)
    // {
    // root = quick_insert(0, 1048575, root, Bst, flag);
    // cout << i << endl;
    // cout << root->height << " " << root->size << endl;
    // HeightsVsNodes << root->height << "," << root->size << endl;
    // root = NULL;
    // }
    // cout << "dolt" << endl;
    // HeightsVsNodes.close();
    // int height[1048576] = {0};
    // //int size[1048576] = {0};
    // cout << "Yas" << endl;
    // HeightsVsNodes.open ("height_vs_nodes_avg_rotate.csv");
    // HeightsVsNodes << "height,nodes\n";
    // for(int k = 0 ; k < 100 ; k++ )
    // {
   
    
    // for (int i = 0; i < 1048576; i++) {
	// 		root = Bst.Insert(i, root);
	// 		//cout << root->height << " " << root->size << endl;
    //         height[i] = height[i] + root->height;
	// 	}

    // for(int i = 0 ; i < 1048576 ; i++)
    //  root = NULL;
    //  cout << k << endl;
    // }
    // for(int p = 0 ; p < 1048576 ; p++)
    // {
    //    HeightsVsNodes << p+1<< "," << height[p]/100 << endl; 
    //   cout << p+1<< "," << height[p]/100 << endl; 
    // }
    // HeightsVsNodes.close();
    // int height[1048576] = {0};
    // height[1048576] = {0};
    // avg_insert.open("rotate_avg_insert.csv");
    // avg_insert << "heights" ;

    // for(int k = 0 ; k < 100 ; k++ )
    // {
   
    // for (int i = 0; i < 1048576; i++) {
	// 		root = Bst.Insert(i, root);
			
	// 	}
    
    // avg_insert <<  root->height << endl;


    // for (int i = 1048575; i >= 0; i--) {
	// 		root = Bst.Remove(root,i);
    //         //cout << i << endl;
    //         if(root)
    //         {
    //         height[i] = height[i] + root->height;
    //         }			
	// 	}
    // root = NULL;
    // cout << k << endl;
    // }

    // HeightsVsNodes.open ("height_vs_nodes_delete.csv");
    // HeightsVsNodes << "height,nodes\n";
    // for(int p = 0 ; p < 1048576 ; p++)
    // {
    //    HeightsVsNodes << p+1<< "," << height[p]/100 << endl; 
    //   cout << p+1<< "," << height[p]/100 << endl; 
    // }
    // HeightsVsNodes.close();
    // avg_insert.close();


}
}

// int main() {

// 	ofstream HeightsVsNodes;
// 	HeightsVsNodes.open ("height_vs_nodes.csv");
// 	HeightsVsNodes << "height,nodes\n";

// 		BStree Bst;
//         bool flag = false;

// 		for (int i = 0; i < 1048576; i++) {
// 			root = Bst.Insert(i, root, flag);
// 			cout << root->height << " " << root->size << endl;
// 		    HeightsVsNodes << root->height << "," << root->size << endl;
// 		}

// 	HeightsVsNodes.close();

// }
