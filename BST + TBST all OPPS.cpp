#include <bits/stdc++.h>
using namespace std;

class bst
{
    private:
        int data;
        bst *left, *right;
    public:
        bst *Insertion(bst *root, int data);
        bst *newNode(int data);
        bst *SearchBST(bst *root, int data);
        bst *Max(bst *root);
        bst *Min(bst *root);
        bst *DeletionBST(bst *root, int data);
        void Preorder(bst *root);
        void Inorder(bst *root);
        void Postorder(bst *root);
        void Levelorder(bst *root);
};
class tbst 
{
    private:
        int data;
        tbst *left, *right;
        bool lthread, rthread;
    public:
        tbst *InsertionTBST(tbst *root, int data);
        tbst *InSucc(tbst *root);
        tbst *InPre(tbst *ptr);
        void InorderTBST(tbst *root);
        tbst *caseA(tbst *root, tbst *parent, tbst *ptr);
        tbst *caseB(tbst *root, tbst *parent, tbst *ptr);
        tbst *caseC(tbst *root, tbst *parent, tbst *ptr);
        tbst *DeletionTBST(tbst *root, int data);
};
bst *bst::newNode(int data)
{
    bst *temp = new bst;
    if(temp == NULL)
    {
        cout << "\nInsufficient Memory Space!!" << endl;
        return NULL;
    }
    temp -> data = data;
    temp -> left = temp -> right = NULL;
    return temp;
}
bst *bst::Insertion(bst *root, int data)
{
    if(root == NULL)
    {
        return newNode(data);
    }
    if(data < (root -> data))
    {
        root -> left = Insertion(root -> left, data);
    }
    else
    {
        root -> right = Insertion(root -> right, data);
    }
    return root;
}
bst *bst::Max(bst *root)
{
    if(root != NULL)
    {
        while(root -> right != NULL)
        {
            root = root -> right;
        }
        return root;
    }
    return NULL;
}
bst *bst::Min(bst *root)
{
    if(root != NULL)
    {
        while(root -> left != NULL)
        {
            root = root -> left;
        }
        return root;
    }
    return NULL;
}
bst *bst::DeletionBST(bst *root, int data)
{
    if(root == NULL)
    {
        cout << "\nData not found!!" << endl;
        return root;
    }
    if(data < (root -> data))
    {
        root -> left = DeletionBST(root -> left, data);
    }
    else if(data > (root -> data))
    {
        root -> right = DeletionBST(root -> right, data);
    }
    else
    {
        if(root -> left == NULL)
        {
            bst *temp = root -> right;
            delete root;
            return temp;
        }
        else if(root -> right == NULL)
        {
            bst *temp = root -> left;
            delete root;
            return temp;
        }
        bst *temp = Min(root -> right);
        root -> data = temp -> data;
        root -> right = DeletionBST(root -> right, temp -> data);
        return root;
    }
}
void bst::Preorder(bst *root)
{
    bst *save[20];
    int top = 0;
    save[top++] = root;
    
    while(top != 0)
    {
        root = save[--top];
        cout << root -> data << "       ";
        
        if(root -> right != NULL)
        {
            save[top++] = root -> right;
        }
        if(root -> left != NULL)
        {
            save[top++] = root -> left;
        }
    }
}
void bst::Inorder(bst *root)
{
    bst *save[20], *ptr = root;
    int top = 0;
    
    while(1)
    {
        while(ptr -> left != NULL)
        {
            save[top++] = ptr;
            ptr = ptr -> left;
        }
        while(ptr -> right == NULL)
        {
            cout << ptr -> data << "        ";
            
            if(top == 0)
            {
                return;
            }
            ptr = save[--top];
        }
        cout << ptr -> data <<  "       ";
        ptr = ptr -> right;
    }
}
void bst::Postorder(bst *root)
{
    bst *save[20], *q, *ptr = root;
    int top = 0;
    
    q = ptr;
    while(1)
    {
        while(ptr -> left != NULL)
        {
            save[top++] = ptr;
            ptr = ptr -> left;
        }
        while(ptr -> right == NULL || ptr -> right == q)
        {
            cout << ptr -> data << "        ";
            q = ptr;
            
            if(top == 0)
            {
                return;
            }
            ptr = save[--top];
        }
        save[top++] = ptr;
        ptr = ptr -> right;
    }
}
void bst::Levelorder(bst *root)
{
    std::queue<bst *> save;
    bst *ptr = root;
    save.push(ptr);
    
    while(!save.empty())
    {
        ptr = save.front();
        save.pop();
        cout << ptr -> data << "        ";
        
        if(ptr -> left != NULL)
        {
            save.push(ptr -> left);
        }
        if(ptr -> right != NULL)
        {
            save.push(ptr -> right);
        }
    }
}
tbst *tbst::InsertionTBST(tbst *root, int data)
{
    tbst *ptr = root, *parent = NULL;
    
    while(ptr != NULL)
    {
        if(data == (ptr -> data))
        {
            cout <<"\nDuplicate key not allowed!!" << endl;
            return root;
        }
        parent = ptr;
        if(data < (ptr -> data))
        {
            if(ptr -> lthread == false)
            {
                ptr = ptr -> left;
            }
            else
            {
                break;
            }
        }
        else
        {
            if(ptr -> rthread == false)
            {
                ptr = ptr -> right;
            }
            else
            {
                break;
            }
        }
    }
    tbst *temp = new tbst;
    temp -> data = data;
    temp -> lthread = temp -> rthread = true;
    
    if(parent == NULL)
    {
        root = temp;
        temp -> left = temp -> right = NULL;
    }
    else if(data < (parent -> data))
    {
        temp -> left = parent -> left;
        temp -> right = parent;
        parent -> lthread = false;
        parent -> left = temp;
    }
    else
    {
        temp -> left = parent;
        temp -> right = parent -> right;
        parent -> rthread = false;
        parent -> right = temp;
    }
    return root;
}
tbst *tbst::InSucc(tbst *root)
{
    if(root -> rthread == true)
    {
        return root -> right;
    }
    root = root -> right;
    while(root -> lthread == false)
    {
        root = root -> left;
    }
    return root;
}
tbst *tbst::InPre(tbst *root)
{
     if(root -> lthread == true)
    {
        return root -> left;
    }
    root = root -> left;
    while(root -> rthread == false)
    {
        root = root -> right;
    }
    return root;
}
void tbst::InorderTBST(tbst *root)
{
    if(root == NULL)
    {
        cout << "\nTree is Empty!!!" << endl;
        return;
    }
    tbst *ptr = root;
    while(ptr -> lthread == false)
    {
        ptr = ptr -> left;
    }
    while(ptr != NULL)
    {
        cout << ptr -> data << "        ";
        ptr = InSucc(ptr);
    }
}
tbst *tbst::caseA(tbst *root, tbst *parent, tbst *ptr)
{
    if(parent == NULL)
    {
        root = NULL;
    }
    else if(ptr == (parent -> left))
    {
        parent -> left = ptr -> left;
        parent -> lthread = true;
    }
    else
    {
        parent -> right = ptr -> right;
        parent -> rthread = true;
    }
    return root;
}
tbst *tbst::caseB(tbst *root, tbst *parent, tbst *ptr)
{
    tbst *child;
    if(ptr -> lthread == false)
    {
        child = ptr -> left; 
    }
    else
    {
        child = ptr -> right;
    }
    if(parent == NULL)
    {
        root = child;
    }
    else if(ptr == (parent -> left))
    {
        parent -> left = child;
    }
    else
    {
        parent -> right = child;
    }
    tbst *s = InSucc(ptr);
    tbst *p = InPre(ptr);
    if(ptr -> lthread == false)
    {
        p -> right = s;   
    }
    else
    {
        if(ptr -> rthread == false)
            s -> left = p;
    }
    delete ptr;
    return root;
}
tbst *tbst::caseC(tbst *root, tbst *parent, tbst *ptr)
{
    tbst *succ = ptr -> right;
    tbst *parentSucc = ptr;
    
    while(succ -> left != NULL)
    {
        parentSucc = succ;
        succ = succ -> left;
    }
    ptr -> data = succ -> data;
    if(succ -> lthread == true && succ -> rthread == true)
    {
        root = caseA(root, parentSucc, succ);
    }
    else
    {
        root = caseB(root, parentSucc, succ);
    }
    return root;
    
}
tbst *tbst::DeletionTBST(tbst *root, int data)
{
    tbst  *parent = NULL, *ptr = root;
    bool found = false;
    
    while(ptr != NULL)
    {
        if(data == (ptr -> data))
        {
            found = true;
            break;
        }
        parent = ptr;
        if(data < (ptr -> data))
        {
            if(ptr -> lthread == false)
            {
                ptr = ptr -> left;;
            }
            else
            {
                break;
            }
        }
        else
        {
            if(ptr -> rthread == false)
            {
                ptr = ptr -> right;
            }
            else
            {
                break;
            }
        }
    }
    if(found == false)
    {
        cout << "\nKey you are searching for is not available!!!" << endl;
    }
    else if(ptr -> lthread == false && ptr -> rthread == false)
    {
        root = caseC(root, parent, ptr);
    }
    else if(ptr -> lthread == false)
    {
        root = caseB(root, parent, ptr);
    }
    else if(ptr -> rthread == false)
    {
        root = caseB(root, parent, ptr);
    }
    else
    {
        root = caseA(root, parent, ptr);
    }
    return root;
}
int32_t main(void)
{
    bst *root = NULL;
    root = root -> Insertion(root, 10);
    root = root -> Insertion(root, 7);
    root = root -> Insertion(root, 15);
    root = root -> Insertion(root, 5);
    root = root -> Insertion(root, 8);
    root = root -> Insertion(root, 20);
    root = root -> Insertion(root, 12);
    root = root -> Insertion(root, 2);
    root = root -> Insertion(root, 25);
    
    cout << "\nPreorder :- " << flush;
    root -> Preorder(root);
    
    cout << "\nInorder :- " << flush;
    root -> Inorder(root);
    
    cout << "\nPostorder :- " << flush;
    root -> Postorder(root);
    
    cout << "\nLevelorder :- " << flush;
    root -> Levelorder(root);
    
    int data;
    cout << "\n\nEnter data item you want to delete :- " << flush;
    cin >> data;
    
    root = root -> DeletionBST(root, data);
    
    cout << "\n\nPreorder :- " << flush;
    root -> Preorder(root);
    
    cout << "\nInorder :- " << flush;
    root -> Inorder(root);
    
    cout << "\nPostorder :- " << flush;
    root -> Preorder(root);
    
    cout << "\nLevelorder :- " << flush;
    root -> Levelorder(root);
    
    cout <<"\n\n\nThreaded BST code" << endl;
    
    tbst *root1 = NULL;
    root1 = root1 -> InsertionTBST(root1, 10);
    root1 = root1 -> InsertionTBST(root1, 7);
    root1 = root1 -> InsertionTBST(root1, 15);
    root1 = root1 -> InsertionTBST(root1, 5);
    root1 = root1 -> InsertionTBST(root1, 8);
    root1 = root1 -> InsertionTBST(root1, 20);
    root1 = root1 -> InsertionTBST(root1, 12);
    root1 = root1 -> InsertionTBST(root1, 2);
    root1 = root1 -> InsertionTBST(root1, 25);
    
    cout << "\nInorder traversal in TBST :- " << flush;
    root1 -> InorderTBST(root1);
    cout << "\nEnter data item you want to delete :- " << flush;
    cin >> data;
    
    root1 =  root1 -> DeletionTBST(root1, data);
    cout << "\nInorder traversal in TBST :- " << flush;
    root1 -> InorderTBST(root1);
    return 0;
}





