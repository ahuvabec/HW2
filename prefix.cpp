#include <iostream>
#include <vector>
#include <stack>
using namespace std;


double evalExpression(string s);
bool isDigit(char c);

int main(){
	
	string expression =  "%35";
    double ans = evalExpression(expression); 
	cout<<ans << endl;
    return 0;

	
}
bool isDigit(char c){ //function to determine if a character is a digit 
	
	return isdigit(c);
}


double evalExpression(string s){
	stack<double> stack; 
	double num1;
	double num2;
	
	for(int i = s.size() - 1; i >= 0; i--){
		if(isDigit(s[i])){
			stack.push(s[i]- '0');//convorting the character to its numerical value 
		
		}
		//assuming all expressions entered are legal
		//else would ancounter a operator 
		else{
			num1 = stack.top();
			stack.pop();
			num2 = stack.top();
			stack.pop();
			
			switch (s[i]) {//different cases based on what operation we encounter
            case '+':
                stack.push(num1 + num2);
                break;
            case '-':
                stack.push(num1 - num2);
                break;
            case '*':
                stack.push(num1 * num2);
                break;
            case '%':
            	stack.push(int(num1) % int(num2));//casting the numbers as integers since % operator only works or integers
            	break;
            case '/':
               	if (num2 != 0)//checking were not dividing by 0
                    stack.push(num1 / num2);//pushing on the subtraction
                else 
                    cout << " (Illegal Division by 0)";//outputing error message 
                break;
            default:  
                cout << " (Illegal operator)";
		}
	}
}
	return stack.top(); //returning the solution 
};
