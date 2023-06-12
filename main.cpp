/*
Anmildeep Sandhu
This is my own work.
*/
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

/* Node in binary tree has data*/ 
class node  
{  
    public: 
    string data;  
    node* left;  
    node* right;  

/* This is constructor which allocates the new node with given data*/
    node(string data) 
    { 
        this->data = data;  
        this->left = NULL;  
        this->right = NULL;  
    } 
}; 
//Utility function is creating a new BST node
node* newNode(string item)
{
     node* temp = new node(item);   
    return temp;
}
 
//This utility function is to do the inorder traversal of BST
void inorder( node* root)
{
    if (root != NULL) {
        inorder(root->left);
        cout << root->data<<" ";
        inorder(root->right);
    }
}
/*This utility function is to insert a new node with given key in BST*/
 node* insert( node* node, string key)
{
    //This if statement is for checking if tree is empty, then it is returnning new node.
    if (node == NULL)
        return newNode(key);
    /*This is for if node already present return the current node*/
    if(node->data==key){
        return node;
    }
    if (key < node->data)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
 
    /* This is returning the unchanged node pointer */
    return node;
}
/*This Function is searching the node with the given key in tree
and also counts the number of steps*/
node * search(node* root, string key,int steps){
    if(root==NULL){
        return NULL;
    }
    if(root->data==key){
        cout<<"Inspected "<<steps<<" elements\n";
        cout<<"'"<<key<<"'"<<" located"<<endl;
        return root;
    }
    if(root->data > key){
        return search(root->left,key,steps+1);
    }
    else{
        return search(root->right,key,steps+1);
    }
}
// non-empty binary search tree
 node* minValueNode( node* node1)
{
     node * current = node1;
 
    //This while loop helps to find the leftmost leaf 
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}
 
/* This is a binary search tree and a key, and this function is deleting the key and returns the new root */
 node* deleteNode( node* root, string key)
{
    if (root == NULL)
        return root;
 
// If key is deleted and it is smaller than the root's key, then it lies in left subtree
    if (key < root->data)
        root->left = deleteNode(root->left, key);
 
    // If key is to be deleted is greater than the roots key, then it lies in right subtree
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
 
    // if key is same as root's key, then This is the node to be deleted
    else {
        // node with only one child or no child
        if (root->left == NULL) {
             node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            delete root;
            return temp;
        }
 
        // node with two children: Get the inorder successor
        struct node* temp = minValueNode(root->right);
        root->data = temp->data;
        // Deleting the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
 
// Main code, which is running the code
int main()
{
   //This is initializing root as null
     node* root = NULL;
     //This is opening words.txt file
    ifstream file("words.txt");
    string line;
    getline(file,line);
    // This is seperating the words using space
    string delimiter = " ";

size_t pos = 0;
string token;
while ((pos = line.find(delimiter)) != std::string::npos) {
    token = line.substr(0, pos);
   
    //This function is inserting the each word into tree
    root=insert(root,token);
    line.erase(0, pos + delimiter.length());
}
// Taking input from the user
  root=insert(root,line);   
    cout << "Inorder traversal of the given tree \n";
    inorder(root);
    cout<<endl;
   while(1){
       cout<<"Enter string, enter -1 to quit: ";
       string temp;
       cin>>temp;
       if(temp=="-1"){
           break;
       }
       if(search(root,temp,1)==NULL){
           cout<<temp<<" not located\n";
       }
   }
   while(1){
       cout<<"Enter string to delete, enter -1 to quit: ";
       string temp;
       cin>>temp;
       if(temp=="-1"){
           break;
       }
       root=deleteNode(root,temp);
       inorder(root);
       cout<<endl;
   }
  
    return 0;
}