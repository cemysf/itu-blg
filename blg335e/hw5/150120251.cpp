/// BLG335E Prj5
/// Cem Yusuf Aydoğdu
/// 150120251

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/// enum definitions
enum Gender{ FEMALE, MALE };
enum Color{ RED, BLACK };

/// data structures
struct TreeNode
{
    // key
    int age;

    // additional info
    string name;
    Gender gender;

    Color color;
    TreeNode *leftChild;
    TreeNode *rightChild;
    TreeNode *parent;

};

class RbTree
{
    TreeNode *root;
    int treeSize;

    void deleteNodes(TreeNode *node);
    void leftRotate(TreeNode *x);
    void rightRotate(TreeNode *y);

    public:
        RbTree()
        {
            root = NULL;
            treeSize=0;
        }
        ~RbTree() { deleteNodes(root); }

        void insert(string &_name, int &_age, Gender _gender);
        void print();


};

// used for printing the tree
class Stack
{
    TreeNode **data_array;  // array of pointers
    const int size;
    int top_element;

    public:

        Stack(int _size) : size(_size)
        {
            data_array = new TreeNode*[size];
            top_element = 0;
        }
        ~Stack() { delete[] data_array; }

        void push(TreeNode *node) { data_array[top_element++] = node; }
        TreeNode* pop() { return data_array[--top_element]; }
        TreeNode* top() { return data_array[top_element]; }
        bool isEmpty() { return (top_element==0); }
        int get_top_element() { return top_element; }
};

/// tree functions
void RbTree::deleteNodes(TreeNode *node)
{
    if(node != NULL)
    {
        if(node->leftChild != NULL)
        {
            deleteNodes(node->leftChild);
            node->leftChild = NULL;
        }

        if(node->rightChild != NULL)
        {
            deleteNodes(node->rightChild);
            node->rightChild = NULL;
        }

        delete node;
    }
}


void RbTree::insert(string &_name, int &_age, Gender _gender)
{
    /// first, insert to tree like a BST

    TreeNode *newnode = new TreeNode;
    newnode->leftChild = newnode->rightChild = NULL;

    newnode->name = _name;
    newnode->age = _age;
    newnode->color = RED;       //default color is RED in all addition operations
    newnode->gender = _gender;

    // inserting first node
    if(root == NULL)
    {
        root = newnode;
        root->color = BLACK;    // root must have BLACK color
        root->parent = NULL;

        return;
    }

    TreeNode *traverse = root;
    bool completed = false;
    while(!completed && (traverse != NULL))
    {
        if( newnode->age < traverse->age)
        {
            if(traverse->leftChild != NULL)
                traverse = traverse->leftChild;
            else
            {
                traverse->leftChild = newnode;
                newnode->parent = traverse;
                completed = true;
            }
        }

        if( newnode->age > traverse->age)
        {
            if(traverse->rightChild != NULL)
                traverse = traverse->rightChild;
            else
            {
                traverse->rightChild = newnode;
                newnode->parent = traverse;
                completed = true;
            }
        }
    }
    treeSize++;

    /// second, check for conflict and resolve if any

    while(newnode->parent->color == RED)
    {
        if(newnode->parent == newnode->parent->parent->leftChild)   // if newnode's parent is a left child
        {
            TreeNode *uncle = newnode->parent->parent->rightChild;      //////// !!!!!!!!!!!!!!!!!!

            if(uncle != NULL)
            {
                if(uncle->color == RED)         //case 1
                {
                    newnode->parent->color = BLACK;
                    uncle->color = BLACK;
                    newnode->parent->parent->color = RED;
                    newnode = newnode->parent->parent;
                }
            }
            else
            {
                if(newnode == newnode->parent->rightChild) //case 2
                {
                    newnode = newnode->parent;
                    leftRotate(newnode);
                }

                newnode->parent->color = BLACK;         //case 3
                newnode->parent->parent->color = RED;
                rightRotate(newnode->parent->parent);
            }

        }
        else    // if newnode's parent is a right child
        {
            TreeNode *uncle = newnode->parent->parent->leftChild;

            if(uncle != NULL)
            {
                if(uncle->color == RED)         //case 1
                {
                    newnode->parent->color = BLACK;
                    uncle->color = BLACK;
                    newnode->parent->parent->color = RED;
                    newnode = newnode->parent->parent;
                }
            }
            else
            {
                if(newnode == newnode->parent->leftChild) //case 2
                {
                    newnode = newnode->parent;
                    rightRotate(newnode);
                }

                newnode->parent->color = BLACK;         //case 3
                newnode->parent->parent->color = RED;
                leftRotate(newnode->parent->parent);
            }
        }

        if(newnode == root)
            break;

    } // end while

    root->color = BLACK;
}


void RbTree::print()
{
    TreeNode *curr = root;
    Stack s(treeSize);

    while(curr != NULL || s.isEmpty() == false)
    {
        if(curr != NULL)
        {
            s.push(curr);
            curr = curr->leftChild;
        }
        else
        {
            curr = s.pop();

            for(int i=0; i<s.get_top_element(); i++)
                cout << "[";

            cout << "[";
            cout << curr->name << "-";
            cout << curr->age << "-";
            if(curr->gender==FEMALE)
                cout << "F";
            else
                cout << "M";
            cout << "]  ";

            curr = curr->rightChild;

        }

    }

    cout << endl;

}

void RbTree::leftRotate(TreeNode *x)
{
    TreeNode *y = x->rightChild;

    // transfer y's left child as x's right child
    x->rightChild = y->leftChild;
    if(y->leftChild != NULL)
        y->leftChild->parent = x;

    // x's parent becomes y's parent
    y->parent = x->parent;
    if(x->parent == NULL)
        root = y;
    else if(x == x->parent->leftChild)
        x->parent->leftChild = y;
    else
        x->parent->rightChild = y;

    // x becomes y's left child
    y->leftChild = x;
    x->parent = y;
}


void RbTree::rightRotate(TreeNode *y)
{
    TreeNode *x = y->leftChild;

    // transfer x's right child as y's left child
    y->leftChild = x->rightChild;
    if(x->rightChild != NULL)
        x->rightChild->parent = y;

    // y's parent becomes x's parent
    x->parent = y->parent;
    if(y->parent == NULL)
        root = x;
    else if(y == y->parent->rightChild)
        y->parent->rightChild = x;
    else
        y->parent->leftChild = x;

    // y becomes x's right child
    x->rightChild = y;
    y->parent = x;

}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        cout << "Usage: ./150120251 <filename>" << endl;
        return 1;
    }

    string filename(argv[1]);
    ifstream file(filename.c_str(), ios::in);
    if(!file.is_open())
    {
        cout << "File error: cannot open " << filename << endl;
        return 2;
    }

    RbTree tree;

    string line;
    while(getline(file,line))
    {
        stringstream linestream(line);

        int age;
        string name;
        string gender;


        getline(linestream, name, '\t');
        getline(linestream, gender, '\t');
        linestream >> age;

        if(gender.compare(string("F")) == 0 )
            tree.insert (name, age, FEMALE);
        else
            tree.insert (name, age, MALE);

    }

    tree.print();

    return 0;
}
