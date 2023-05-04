#include <iostream>
#include <queue>
#include <vector>
using namespace std;


template <typename T>
class Node {
   public:
    T data;
    Node<T> *next;
    Node(T data) {
        this->data = data;
        this->next = NULL;
    }
};

template <typename T>
class BinaryTreeNode {
   public:
    T data;
    BinaryTreeNode<T> *left;
    BinaryTreeNode<T> *right;

    BinaryTreeNode(T data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

template <typename T>
class nodelist{
    public:  // Exposing Everything which is not the best way. But the idea over
        //  here is only to modularize the code
        Node<T> *start, *end;
        nodelist(Node<T> *p=nullptr)
            :start(p), end(p)
        {
            if(p==nullptr) return;
            p->next = nullptr;
        }
        void pushnode(Node<T> *p)
        {
            if(p==nullptr) return;
            p->next = nullptr;
            if(start==nullptr)
            {
                /* First Node to insert */
                start = end = p;
                return;
            }
            end->next = p;
            end = p;
        }
        void popEndnode()
        {
            if(end==nullptr) return;
            if(end==start)
            {
                /* last node to return */
                delete end;
                start = end = nullptr;
                return;
            }
            Node<T> *curr=start;
            while(curr->next!=end) curr = curr->next;
            curr->next = nullptr;
            delete end;
            end = curr;
        }
};

vector<Node<int>*> constructLinkedListForEachLevel(BinaryTreeNode<int> *root) {
    // Write your code here
      vector<Node<int>*> result;
    if(root==nullptr) return result;
    queue<BinaryTreeNode<int>*> *inputQ, *outputQ, *temp;
    inputQ = new queue<BinaryTreeNode<int>*>();
    outputQ = new queue<BinaryTreeNode<int>*>();
    inputQ->push(root);
    /* Here we want to add a link list into result */
    Node<int> *ptr = new Node<int>(root->data);
    ptr->next=nullptr;
    result.push_back(ptr);
    do
    {
        //nodelist<int> *list = new nodelist<int>();
        nodelist<int> list;
        while(!inputQ->empty())
        {
            BinaryTreeNode<int> *curr = inputQ->front();
            inputQ->pop();
            if(curr->left!=nullptr)
            {
                outputQ->push(curr->left);
                ptr = new Node<int>(curr->left->data);
                list.pushnode(ptr);
            }
            if(curr->right!=nullptr)
            {
                outputQ->push(curr->right);
                ptr = new Node<int>(curr->right->data);
                list.pushnode(ptr);
            }
        }
        temp = inputQ;
        inputQ = outputQ;
        outputQ = temp;
        result.push_back(list.start);
    } while(!inputQ->empty());
    // Clean up: delete queues created on heap
    delete inputQ;
    delete outputQ;
    return result;
}



BinaryTreeNode<int> *takeInput() {
    int rootData;
    
    cin >> rootData;
    if (rootData == -1) {
        return NULL;
    }
    BinaryTreeNode<int> *root = new BinaryTreeNode<int>(rootData);
    queue<BinaryTreeNode<int> *> q;
    q.push(root);
    while (!q.empty()) {
        BinaryTreeNode<int> *currentNode = q.front();
        q.pop();
        int leftChild, rightChild;
        
        cin >> leftChild;
        if (leftChild != -1) {
            BinaryTreeNode<int> *leftNode = new BinaryTreeNode<int>(leftChild);
            currentNode->left = leftNode;
            q.push(leftNode);
        }
        
        cin >> rightChild;
        if (rightChild != -1) {
            BinaryTreeNode<int> *rightNode =
                new BinaryTreeNode<int>(rightChild);
            currentNode->right = rightNode;
            q.push(rightNode);
        }
    }
    return root;
}

void print(Node<int> *head) {
    Node<int> *temp = head;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    BinaryTreeNode<int> *root = takeInput();
    vector<Node<int> *> ans = constructLinkedListForEachLevel(root);

    for (int i = 0; i < ans.size(); i++) {
        print(ans[i]);
    }
}