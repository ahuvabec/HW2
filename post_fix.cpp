//***********************************************************
// Author: D.S. Malik
//
// Program: Postfix Calculator  
// This program evaluates postfix expressions.
//***********************************************************
  
#include <iostream>  
#include <iomanip>
#include <fstream>
#include "mystack.h"
 
using namespace std; 
//defining function headers 
void evaluateExpression(ifstream& inpF, ofstream& outF, 
                        stackType<double>& stack,
                        char& ch, bool& isExpOk);
void evaluateOpr(ofstream& out, stackType<double>& stack,
                 char& ch, bool& isExpOk);
void discardExp(ifstream& in, ofstream& out, char& ch);
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk);

int main()
{
    bool expressionOk;
    char ch;
    stackType<double> stack(100);//creating a stack that can hold doubles 
    ifstream infile;
    ofstream outfile;
 
    infile.open("RpnData.txt"); //reads in file

    if (!infile)//if file fails to open
    {
        cout << "Cannot open the input file. " //prints message 
             << "Program terminates!" << endl;
        return 1;
    }
     
    outfile.open("RpnOutput.txt");//file to output results

    outfile << fixed << showpoint;
    outfile << setprecision(2); 

    infile >> ch;
    while (infile) //while were reading in from the file
    {
        stack.initializeStack();//initializing stack
        expressionOk = true; //setting our check for valid expressions to true
        outfile << ch; //taking in the character and printing in outfile  

        evaluateExpression(infile, outfile, stack, ch, //function to evaluate given expression
                           expressionOk);
        printResult(outfile, stack, expressionOk); //printing the result
        infile >> ch; //begin processing the next expression
    } //end while 

    infile.close(); //closing the files 
    outfile.close();

    return 0;

} //end main

//function to evaluate given expression
void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack,char& ch, bool& isExpOk)
{
    double num;

    while (ch != '=')//while we don't reach the = sign, keep evaluating
    {
        switch (ch) //different cases based on the characters encountered 
        {
        case '#': //if we encounter a # we know we have numbers to process 
            inpF >> num;
            outF << num << " ";
            if (!stack.isFullStack())//if our stack is not full
                stack.push(num);//push on a number
            else//if the stack is full
            {
                cout << "Stack overflow. "
                     << "Program terminates!" << endl;
                exit(0);  //terminate the program
            }

            break;
        default: 
            evaluateOpr(outF, stack, ch, isExpOk); //calling 
        }//end switch

        if (isExpOk) //if no error
        {
            inpF >> ch; //taking in and printing out the characters 
            outF << ch;

            if (ch != '#') //if we dont have a # were not a character thet needs to be evaluated
                outF << " ";// so we ouput a space
        }
        else
            discardExp(inpF, outF, ch);//function defined below, takes in the character and outs it
    } //end while (!= '=')
} //end evaluateExpression

//function to evaluate expressions 
void evaluateOpr(ofstream& out, stackType<double>& stack,
              char& ch, bool& isExpOk)
{
    double op1, op2;

    if (stack.isEmptyStack()) //if the stck is empty
    {
        out << " (Not enough operands)"; 
        isExpOk = false;//setting out check to false
    }
    else
    {
        op2 = stack.top();//setting the 2nd op to the top of stck
        stack.pop(); //popping the stack

        if (stack.isEmptyStack())//if the stack is empty we cant operate 
        {
            out << " (Not enough operands)";
            isExpOk = false;//setting out check to false
        }
        else //last case we have numbers in the stack to operate on 
        {
            op1 = stack.top();
            stack.pop();

            switch (ch)//cases differ based on mathematical character operator  
            {
            	//cases where we have addition, subtraction, multiplication, and devision
            case '+': 
                stack.push(op1 + op2); //push on the sum
                break;
            case '-': 
                stack.push(op1 - op2);//push on the subtraction result
                break;
            case '*': 
                stack.push(op1 * op2);//push on the multiplication of the two numbers
                break;
            case '/': 
                if (op2 != 0)//checking were not dividing by 0
                    stack.push(op1 / op2);//pushing on the subtraction
                else
                {
                    out << " (Division by 0)";//outputing error message 
                    isExpOk = false;//setting the epression to not ok
                }
                break;
            default:  
                out << " (Illegal operator)";
                isExpOk = false;
            }//end switch
        } //end else
    } //end else
} //end evaluateOpr

//function to get rid of an expression
void discardExp(ifstream& in, ofstream& out, char& ch)
{
    while (ch != '=') //whilw we dont reach the = sign
    {
        in.get(ch); //take in the character
        out << ch;//cout it 
    }
} //end discardExp

//function to print the results 
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk)
{
    double result;

    if (isExpOk) //if no error, print the result
    {
        if (!stack.isEmptyStack())//if the stack is not empty
        {
            result = stack.top();//our result is at the top so we set it = to double result
            stack.pop();//pop the result

            if (stack.isEmptyStack())//if now the stack is empty
                outF << result << endl;//output the result
            else
                outF << " (Error: Too many operands)" << endl;
        } //end if
        else
            outF << " (Error in the expression)" << endl;
    }
    else
        outF << " (Error in the expression)" << endl;

    outF << "_________________________________" 
         << endl << endl;
} //end printResult

