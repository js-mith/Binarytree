#include<iostream>
#include "binarytreenode.h"
#include<queue>
#include<limits.h>
using namespace std;

BinaryTreeNode<int> *takeinputlevelwise(){
     int rootdata;

    cout << "enter the data" << endl;
    cin>>rootdata;

    if(rootdata == -1){
        return NULL;
    }
    BinaryTreeNode<int> *root = new BinaryTreeNode<int>(rootdata);
    queue<BinaryTreeNode<int>*> pendingnodes;
    pendingnodes.push(root);
    while(pendingnodes.size() != 0){
        BinaryTreeNode<int> *front = pendingnodes.front();
        pendingnodes.pop();
        cout << "enter the left child of " << front-> data << endl;
        int leftchilddata;
        cin>>leftchilddata;
        if(leftchilddata != -1){
            BinaryTreeNode<int> *child = new BinaryTreeNode<int>(leftchilddata);
            front->left = child;
            pendingnodes.push(child);
        }
         cout << "enter the right child of " << front-> data << endl;
        int rightchilddata;
        cin>>rightchilddata;
        if(rightchilddata != -1){
            BinaryTreeNode<int> *child = new BinaryTreeNode<int>(rightchilddata);
            front->right = child;
            pendingnodes.push(child);
        }
    }
    return root;
}

void printTree(BinaryTreeNode<int> *root){
    if(root == NULL){
        return;
    }
    cout << root -> data << " : ";
    if(root -> left != NULL){
        cout << " L " << root -> left ->data;
    }
    if(root ->right != NULL){
        cout << " R " << root -> right -> data;
    }

    cout << endl;
    printTree(root -> left);
    printTree(root -> right);
}
BinaryTreeNode<int> *takeinput(){
    int rootdata;

    cout << "enter the data" << endl;
    cin>>rootdata;

    if(rootdata == -1){
        return NULL;
    }
    BinaryTreeNode<int> *root = new BinaryTreeNode<int>(rootdata);
    BinaryTreeNode<int> *leftchild = takeinput();
    BinaryTreeNode<int> *rightchild = takeinput();
    root -> left = leftchild;
    root -> right = rightchild;
    return root;
}

int numnodes(BinaryTreeNode<int>*root){
    if(root == NULL){
        return 0;
    }
    return 1+numnodes(root ->left)+numnodes(root->right);
}
void inorder(BinaryTreeNode<int>*root){
    if(root == NULL){
        return;
    }
    inorder(root -> left);
    cout << root -> data << " ";
    inorder(root -> right);
    
}
BinaryTreeNode<int> *buildtreehelper(int *in , int *pre , int inS , int inE , int preS , int preE){
    if(inS > inE){
    return NULL;
    }
    int rootdata = pre[preS];
    int rootindex = -1;
    for(int i = inS ; i<=inE ; i++){
        if(in[i] == rootdata){
            rootindex = i;
            break;
        }
    }
    int lpreS = preS +1 ;
    
    int linS = inS;
    int linE = rootindex -1;
    int lpreE = linE - linS +lpreS;
     int rpreS = lpreE +1;
    int rpreE = preE;
    int rinS = rootindex +1;
    int rinE = inE;
    BinaryTreeNode<int> *root = new BinaryTreeNode<int>(rootdata);
    root -> left = buildtreehelper(in , pre , linS , linE , lpreS , lpreE);
    root -> right = buildtreehelper(in , pre , rinS , rinE , rpreS , rpreE);
    return root;
}

BinaryTreeNode<int> *buildtree(int *in , int *pre , int size){
    return buildtreehelper(in , pre , 0 , size-1 , 0 , size-1);
}

int height(BinaryTreeNode<int>*root){
    if(root == NULL){
        return 0;
    }
    return 1+max(height(root -> left),height(root->right));
}

int diameter(BinaryTreeNode<int> *root){
    if(root == NULL){
        return 0;
    }
    int option1 = height(root->left) + height(root->right);
    int option2 = diameter(root->left);
    int option3 = diameter(root -> right);

    return max(option1 , max(option2,option3));
}

pair<int,int>heightdiameter(BinaryTreeNode<int>*root){
    if(root == NULL){
        pair<int,int> p;
        p.first = 0;
        p.second = 0;
        return p;
    }
    pair<int,int> leftans = heightdiameter(root -> left);
    pair<int,int> rightans = heightdiameter(root -> right);
    int ld = leftans.second;
    int lh = leftans.first;
    int rd = rightans.second;
    int rh = rightans.first;

    int height = 1+ max(lh,rh);
    int diameter = max(lh+rh , max(ld,rd));
    pair<int,int> p;
    p.first = height;
    p.second = diameter;
    return p;

}

void mirrorBinaryTree(BinaryTreeNode<int>* root) {
    // Write your code here
	if(root == NULL){
		return ;
	}
	BinaryTreeNode<int>*left = root -> left;
	root -> left = root -> right;
	root -> right = left;
	mirrorBinaryTree(root ->left);
	mirrorBinaryTree(root -> right);
}


pair<int, int> getMinAndMax(BinaryTreeNode<int> *root) {
  // Write your code here
  if (root == NULL) {
    pair<int, int> answer;
    answer.first = INT_MIN;
    answer.second = INT_MAX;
    return answer;
  }
  // Initialize answer as root node data
  pair<int,int> left = getMinAndMax(root->left);
  pair <int,int>right = getMinAndMax(root->right);
  int minimum = min(root->data, min(left.first, right.first));
  int maximum = max(root->data, max(left.second, right.second));

  pair<int,int> answer;
  answer.first = minimum;
  answer.second = maximum;
  return answer;
}

// 1 2 3 4 5 6 7 -1 -1 -1 -1 8 9 -1 -1 -1 -1 -1 -1
int main() {
     /*BinaryTreeNode<int> *root = new BinaryTreeNode<int>(1);
     BinaryTreeNode<int> *node1 = new BinaryTreeNode<int>(2);
     BinaryTreeNode<int> *node2 = new BinaryTreeNode<int>(3);
      root -> left = node1;
      root -> right = node2;
      */
   /*
     int in[] = {4,2,5,1,8,6,9,3,7};
     int pre[]= {1,2,4,5,3,6,8,9,7};
     */
     
      
     BinaryTreeNode<int> *root = takeinputlevelwise();
      printTree(root);
      mirrorBinaryTree(root);
       pair<int, int> ans = getMinAndMax(root);
    cout << ans.first << " " << ans.second;
      cout << "num of nodes :" << numnodes(root) << endl;

      inorder(root);
      cout << endl;

      pair<int,int> p = heightdiameter(root);
      cout << "height :" << p.first << endl;
      cout << "diameter : " << p.second << endl;
      
      delete root;
     return 0;
}