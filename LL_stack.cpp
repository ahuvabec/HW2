//Header File: linkedStack.h 

#ifndef H_StackType
#define H_StackType
 
#include <iostream>
#include <cassert> 
 
#include "stackADT.h"

using namespace std;


template <class Type>
struct nodeType //node class
{
    Type info; //creating the node info
    nodeType<Type> *link;//creating the node link
};

template <class Type>
class linkedStackType: public stackADT<Type>//ADT liked list stack class
{
public:
	//defining function headers
    const linkedStackType<Type>& operator=
                              (const linkedStackType<Type>&);

    
    bool isEmptyStack() const;


    bool isFullStack() const;


    void initializeStack();


    void push(const Type& newItem);


    Type top() const;


    void pop();


    linkedStackType(); 


    linkedStackType(const linkedStackType<Type>& otherStack); 
  

    ~linkedStackType();

private:
    nodeType<Type> *stackTop; //pointer to the stack

    void copyStack(const linkedStackType<Type>& otherStack); //function copy stack that user has no access to

};


    
template <class Type> 
linkedStackType<Type>::linkedStackType()//defult constructro 
{
    stackTop = nullptr;//setting top pointer to null
}

template <class Type>
bool linkedStackType<Type>::isEmptyStack() const //function checking if stack is empty
{
    return(stackTop == nullptr);//if top pointer is null, then its empty
} 

template <class Type>
bool linkedStackType<Type>:: isFullStack() const //cheching if the stack is full
{
    return false;
} 

template <class Type>
void linkedStackType<Type>:: initializeStack()//function that deletes/clears the stack
{
    nodeType<Type> *temp; //creating a holder node so we dont delete the first node and loose the rest of the stack

    while (stackTop != nullptr) //while we dont reach the end
    {
        temp = stackTop;    //set the temp node to the top/current top node
                           
        stackTop = stackTop->link;  // advance stack top  to the next node
                                   
        delete temp;   //delete the memory of temp which is the old top
    }
} 

template <class Type>
void linkedStackType<Type>::push(const Type& newElement)//function to push node onto stack
{
    nodeType<Type> *newNode;  //creating the new node

    newNode = new nodeType<Type>; 

    newNode->info = newElement; //setting the info of the new node
    newNode->link = stackTop; //setting the link of the node behind the previous node/stackTop
                             //this is building the list backwards
    stackTop = newNode;    //setting the new node to be the new top of the stack    
                             
} //end push


template <class Type>
Type linkedStackType<Type>::top() const//function that returns the information at the top of the stack
{
    assert(stackTop != nullptr); //checking that the top is not empty/null
                              
    return stackTop->info; //returning the information 
}//end top

template <class Type>
void linkedStackType<Type>::pop()//deleting a node from the stack
{
    nodeType<Type> *temp; //creating a temp node so we dont delete the first node and loose the rest of the stack

    if (stackTop != nullptr) //while the stack is not empty
    {
        temp = stackTop;  //setting temp to point to current node

        stackTop = stackTop->link; // advance stack top to the next node
                                    
        delete temp;    //deleting the memory of temp/the first node
    }
    else
        cout << "Cannot remove from an empty stack." << endl;//if the list is empty
}//end pop

template <class Type> 
void linkedStackType<Type>::copyStack
                     (const linkedStackType<Type>& otherStack)//copying a stack (deep copy)
{
    nodeType<Type> *newNode, *current, *last; //creating 3 nodes to keep track of our position in the stack

    if (stackTop != nullptr) //if the stack is not empty, initialieze it so we have an empty stack
        initializeStack();

    if (otherStack.stackTop == nullptr)//if the others stacks top = null set this stack top to null
        stackTop = nullptr;
    else
    {
        current = otherStack.stackTop;  //set curreent to to of stack about to be occupied

         //copying the stackTop element of the stack 
        stackTop = new nodeType<Type>;  //creating the new node

        stackTop->info = current->info; //copy the info
        stackTop->link = nullptr;  //set the top link to null
                               
        last = stackTop;     //setting last to point to the node   
        current = current->link;    //setting current to point to the next node

           
        while (current != nullptr) //while we dont reach the end
        {
            newNode = new nodeType<Type>; //create the new node

            newNode->info = current->info; //copy the info
            newNode->link = nullptr; //set the top to null
            last->link = newNode; //setting last to point to the new node
            last = newNode;// now set new node to be the last
            current = current->link;//advance current to the next node
        }
    }
} 

 //copying the stack using the previously created copyStack method
template <class Type>   
linkedStackType<Type>::linkedStackType(
                      const linkedStackType<Type>& otherStack)
{
    stackTop = nullptr;
    copyStack(otherStack);
}

  //emptying the stack 
template <class Type> 
linkedStackType<Type>::~linkedStackType()
{
    initializeStack();
}
    
template <class Type>   
const linkedStackType<Type>& linkedStackType<Type>::operator=
    			  (const linkedStackType<Type>& otherStack)//overloading the = operator 
{ 
    if (this != &otherStack) //uetlizing our copy function to check if two stacks are equal 
        copyStack(otherStack);

    return *this; 
}

#endif
