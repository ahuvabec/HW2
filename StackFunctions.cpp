#include <iostream>
#include <stack>
using namespace std;

void listElements( stack<int> stack); 

void Insert(stack<int> &stack, int element, int pos);

int main(){
	
	//testing our code
	stack<int> testing;
	for(int i =1; i < 10; i++){
		testing.push(i);
	}
	
	listElements(testing);
	cout<< endl;
	
	Insert(testing, 19, 4);
	
	while(!testing.empty()){
		cout << testing.top() <<" ";
		testing.pop();
	}
	
	return 0;
}
	


void listElements( stack<int> stack){//listing all the elements in a stack
	while(!stack.empty()){
		cout<< stack.top() << " "; //outputing the top
		stack.pop();               //then popping to get the next element   
	}
}

void Insert(stack<int> &stack, int element, int pos){
	
	std::stack<int> tracker;//stack to keep track of popped elements 
	int size = stack.size();

	for(int i = size; i >= (size - pos - 1); i--){//loop to pop and at the same time push on to the tracker
		tracker.push(stack.top());                //the elements before the required position 
		stack.pop();
	}
	stack.push(element); //inserting the element at the correct position 
	
	for(int i = size; i >= (size - pos - 1); i--){//pusing back onto the original stack the 
		stack.push(tracker.top());                //previously popped elements 
		tracker.pop();
	}
	
};
