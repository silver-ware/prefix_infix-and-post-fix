#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>


 using namespace std;


//create a binary tree class with a root node (data),left side and right side data fields.
//set root data to data and all other fields to null. 
 class BinaryTree{
     public: char data;
     BinaryTree *left,*right;
     BinaryTree(char data){
         this->data=data;
         this->left=NULL;
         this->right=NULL;
     }
 };

//incorporate binary tree into a stack tree
 class TreeStack{
     public: BinaryTree *Btree;
     TreeStack *node;
     TreeStack(BinaryTree*Btree){
         this->Btree = Btree;
         node =NULL;
     }
 };

class OverallTree{
    private: TreeStack *top;
    public: OverallTree(){
        top = NULL;
    }

    void clear_stack() {
        top = NULL;
    }

    void push(BinaryTree *pointer){
        //IF TOP OF STACK IS NULL , REPLACE THE STACK POINTER WITH THE CURRENT POINTER
        if(top == NULL){
            top = new TreeStack(pointer);
        }
        //ELSE 
        else{
            TreeStack *new_pointer = new TreeStack(pointer);
            new_pointer->node = top;
            top = new_pointer;
        }
    }

    BinaryTree *pop() {
        if (top == NULL){
            cout<<"Underflow"<<endl;
        }
        else{
            BinaryTree *pointer = top->Btree;
            top = top->node;
            return pointer;
        }
    }    
     
    
    //call peak to check the topmost element in the stack/tree
    BinaryTree *peek(){
        return top->Btree;
    }


    bool isOperator(char val){
        return val == '+' || val == '-' || val =='/' || val == '*';
    }

    bool isDigit(char val){
        return val >= '0' && val <= '9'; 
    }

    int to_digit(char val) {
        return val - '0';
    }    

    void insertion(char value){
        if (isDigit(value)){
            BinaryTree *newpointer = new BinaryTree(value);
            push(newpointer);
        }
        else if (isOperator(value)){
            BinaryTree *newpointer = new BinaryTree(value);
            newpointer->left = pop();
            newpointer->right = pop();
            push(newpointer);        
        }
        else {
            cout<<"Invalid expression"<<endl;
            return;
        }
    }

//buildng the binary tree 
    void constructTree(string exp){
        for(int x = exp.length() -1; x >= 0 ; x--){
            insertion(exp[x]);
        }
    }

    void prefix(){
        preOrder(peek());
    }

    void preOrder(BinaryTree *pointer){
        if(pointer != NULL){
            cout<< pointer->data;
            preOrder(pointer->left);
            preOrder(pointer->right);
        }
    }

    void infix(){
        inOrder(peek());
    }

    void inOrder(BinaryTree *pointer){
        if(pointer != NULL){
            inOrder(pointer->left);
            cout<<pointer->data;
            inOrder(pointer->right);
            
        }
    }

    void postfix(){
         postOrder(peek());

    }

    void postOrder(BinaryTree *pointer){
        if(pointer != NULL){
            postOrder(pointer->left);
            postOrder(pointer->right);
            cout<<pointer->data;            
        }
    }

};


int main(){
    string ds;
    OverallTree Ot;
    cout<<"\n Please enter your equation (default: prefix): ";
    cin>>ds;
    Ot.constructTree(ds);

    cout<<"\n For prefix : ";
    Ot.prefix();

    cout<<"\n For infix: ";
    Ot.infix();

    cout<<"\n For postfix: ";
    Ot.postfix();

}


 