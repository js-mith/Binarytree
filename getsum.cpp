#include <iostream>
#include <queue>
using namespace std;



template <typename T>
class BinaryTreeNode {
   public:
    T data;
    BinaryTreeNode<T>* left;
    BinaryTreeNode<T>* right;

    BinaryTreeNode(T data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};



BinaryTreeNode<int>* takeInput() {
    int rootData;
    cin >> rootData;
    if (rootData == -1) {
        return NULL;
    }
    BinaryTreeNode<int>* root = new BinaryTreeNode<int>(rootData);
    queue<BinaryTreeNode<int>*> q;
    q.push(root);
    while (!q.empty()) {
        BinaryTreeNode<int>* currentNode = q.front();
        q.pop();
        int leftChild, rightChild;

        cin >> leftChild;
        if (leftChild != -1) {
            BinaryTreeNode<int>* leftNode = new BinaryTreeNode<int>(leftChild);
            currentNode->left = leftNode;
            q.push(leftNode);
        }

        cin >> rightChild;
        if (rightChild != -1) {
            BinaryTreeNode<int>* rightNode =
                new BinaryTreeNode<int>(rightChild);
            currentNode->right = rightNode;
            q.push(rightNode);
        }
    }
    return root;
}

void printLevelWise(BinaryTreeNode<int> *root) {
    // Write your code here
    if (root == nullptr)
      return;
    queue<BinaryTreeNode<int> *> *inputQ, *outputQ, *temp;
    inputQ = new queue<BinaryTreeNode<int> *>();
    outputQ = new queue<BinaryTreeNode<int> *>();
    inputQ->push(root);
    do {
      while (!inputQ->empty()) {
        BinaryTreeNode<int> *curr = inputQ->front();
        inputQ->pop();
        cout << curr->data << ' ';
        if (curr->left != nullptr)
          outputQ->push(curr->left);
        if (curr->right != nullptr)
          outputQ->push(curr->right);
      }
      cout << endl;
      temp = inputQ;
      inputQ = outputQ;
      outputQ = temp;
    } while (!inputQ->empty());
    // Clean up: delete queues created on heap
    delete inputQ;
    delete outputQ;
}


int getSum(BinaryTreeNode<int>* root) {
    // Write your code here
 if (root == NULL)
        return 0;
    return (root->data + getSum(root->left) + getSum(root->right));
}

BinaryTreeNode<int>* removeLeafNodes(BinaryTreeNode<int> *root) {
    // Write your code here
    if (root == nullptr)
      return nullptr;
    if (root->left == nullptr && root->right == nullptr) {
      delete root;
      return nullptr;
    }
    root->left = removeLeafNodes(root->left);
    root->right = removeLeafNodes(root->right);
    return root;
}

void printNodesWithoutSibling(BinaryTreeNode<int> *root) {
    // Write your code here
    if (root == nullptr)
      return;
    if (root->left == nullptr && root->right != nullptr) {
      /* right node has no sibling. Print right node and call recursion */
      cout << root->right->data << ' ';
      printNodesWithoutSibling(root->right);
      return;
    }
    if (root->left != nullptr && root->right == nullptr) {
      /* left node has no sibling. Print left node and call recursion */
      cout << root->left->data << ' ';
      printNodesWithoutSibling(root->left);
      return;
    }
    printNodesWithoutSibling(root->right);
    printNodesWithoutSibling(root->left);
}


int main() {
    BinaryTreeNode<int>* root = takeInput();
      root = removeLeafNodes(root);
     printLevelWise(root);
      printNodesWithoutSibling(root);
    cout << getSum(root);
}