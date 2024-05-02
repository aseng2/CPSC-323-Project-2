#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
string display(stack<char> input){
    std::string value;
    std::vector<char> v1;
    while(!input.empty())
    {
        v1.insert(v1.begin(), input.top());
        input.pop();
    }
    for(int i = 0; i < v1.size(); i++)
    {
        value += v1[i];
    }
    return value;
}
stack<char> reduction_Rules(stack<char> input){
    stack<char> sk2; //Return Stack
    //sk2.push('$');
    //sk2.push('0');
    vector<char> t1;
    //changes stack to vector
    while(!input.empty())
    {
        t1.insert(t1.begin(), input.top());
        input.pop();
    }
    for(int i = 0; i < t1.size(); i++) //Looks for reduction
    {
        if(t1[i] == 'i') //Deals with id F->id
        {
            auto it = find(t1.begin(), t1.end(), 'i'); //Needs to be tested
            it--; //Get previous state
            if(*it == '4' || *it == '6' || *it == '0')
            {
                it++;
                *it = 'F';
                it++;
                *it = '3';
                it++;
                t1.erase(it); //Erase Num
            }
            else if(*it == '7')
            {
                it++;
                t1.erase(it, t1.end()); //Erase Num
                t1.push_back('F');
                t1.push_back('1');
                t1.push_back('0');
            }
            
        }
        else if(t1[i] == '(') //Handles F -> (E) Needs to be testd
        {
            auto it = find(t1.begin(), t1.end(), '(');
            auto it2 = find(t1.begin(), t1.end(), 'E');
            auto it3 = find(t1.begin(), t1.end(), ')');
            if(it != t1.end() && it2 != t1.end() && it3 != t1.end()) //Reduces 
            {
                it--;
                if(*it == '0')
                {
                    it++;
                    t1.erase(it, t1.end());
                    t1.push_back('F');
                    t1.push_back('3');
                }
            }
        }
        else if(t1[i] == 'F') //Handles T->F (Complete)
        {
            auto it = find(t1.begin(), t1.end(), 'F');
            it--; //gets previous 
            if(*it == '0' || '4')
            {
                it++;
                *it = 'T';
                it++;
                *it = '2';
                //it++;
                //t1.erase(it); //Erase Num
            }
            else if(*it == '6') //+6
            {
                it++;
                *it = 'T';
                it++;
                *it = '9';
                //it++;
                //t1.erase(it); //Erase Num
            }
        }
        else if(t1[i] == 'T') //Handles both T->T*F and E->T (Incomplete)
        {
            auto it = find(t1.begin(), t1.end(), 'T');
            auto it2 = find(t1.begin(), t1.end(), '*');
            auto it3 = find(t1.begin(), t1.end(), 'F');
            if(it != t1.end() && it2 != t1.end() && it3 != t1.end()) //Reduces 
            {
                it--;
                if(*it == '0') //CHECK PREVIOUS STATE
                {
                    it++;  
                    t1.erase(it, t1.end());
                    t1.push_back('T');
                    t1.push_back('2');
                }
            }
            else if(it != t1.end()) //E->T NEEDS TO BE FIXED
            {
                it--;
                if(*it == '0' && t1.size() == 4) //End State
                {
                    it++;
                    t1.erase(it, t1.end());
                    t1.push_back('E');
                    t1.push_back('1');
                }
                else if(*it == '4' && t1.size() == 6) //NEEDS TO BE FIXED
                {
                    it++;
                    t1.erase(it, t1.end());
                    t1.push_back('E');
                    t1.push_back('8');
                    //t1.erase(it); //Erase Num
                }
            }
        }
        else if(t1[i] == 'E') //Handles E->E+T (Incomplete)
        {
            auto it = find(t1.begin(), t1.end(), 'E');
            auto it2 = find(t1.begin(), t1.end(), '+');
            auto it3 = find(t1.begin(), t1.end(), 'T');
            if(it != t1.end() && it2 != t1.end() && it3 != t1.end()) //Reduces 
            {
                it--;
                if(*it == '0') //CHECK PREVIOUS STATE
                {
                    it++;
                    t1.erase(it, t1.end());
                    t1.push_back('E');
                    t1.push_back('1');
                }
                else if(*it == '4')
                {
                    it++;
                    t1.erase(it, t1.end());
                    t1.push_back('E');
                    t1.push_back('8');
                }
            }
            
        }
        // else if(t1[i] == 'F') //Don't forget to change it to the correct PRule 
        // {
        //     auto it = find(t1.begin(), t1.end(), 'F');
        //     //Possible to do it-- to get the previous char
        //     *it = 'E'; 
        //     it++; //should be i++
        //     *it = '1';
            
        // }
    }
    //Convert back to stack
    for(int i = 0; i < t1.size(); i++)
    {
        sk2.push(t1[i]);
    }
    return sk2; 
}
// Function to perform parsing using context free grammar
void cfg_Parsing(string input) {
    
    int step = 1;
    stack<char> stk;
    stk.push('$');
    stk.push('0');
    int i = 0; //Beginning of stack
    cout << "Step\t\tStack\t\t\tInput\t\tAction\n";
    cout << "-------------------------------------------------------------------\n";
    if (input.size() >=7){
    	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\tPush\n";
    }
    else{
    	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\t\tPush\n"; //Print out the beginning
    }
    step++;
    while (!stk.empty()) {
        char top = stk.top();
        //NEED TO FIX FOR E!!
        if(step > 25)
        {
            break;
        }
        if (top == '1' && stk.size() <= 4) { 
            if (input[i] == '$') {
                cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\t\tAccepted\n";
                step++;
                break; //Break out 
            }
            else {
                cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\t\tError\n";
                step++;
                break; //Break out of while loop
            }
        }
        else{
            if (input[i] == 'i' && top == '0')
            {   
                stk.push('i');
                stk.push('d');
                stk.push('5');
                input.erase(0,1); //erase id from input
                input.erase(0,1);
                if (stk.size() > 7){
                	cout << step << "\t\t" << display(stk) << "\t\t" << input << "\t\tPush\n";
                }
                else if (input.size() >=7){
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\tPush\n";
                }
                else{
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\t\tPush\n";
                }
                step++;
            }
            else if (input[i] == 'i' && top == '4'){
                stk.push('i');
                stk.push('d');
                stk.push('5');
                input.erase(0,1); 
                input.erase(0,1);
                if (stk.size() > 7){
                	cout << step << "\t\t" << display(stk) << "\t\t" << input << "\t\tPush\n";
                }
                else if (input.size() >=7){
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\tPush\n";
                }
                else{
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\t\tPush\n";
		}
                step++;
            }
            else if (input[i] == 'i' && top == '7'){
                stk.push('i');
                stk.push('d');
                stk.push('5');
                input.erase(0,1); 
                input.erase(0,1);
                if (stk.size() > 7){
                	cout << step << "\t\t" << display(stk) << "\t\t" << input << "\t\tPush\n";
                }
                else if (input.size() >=7){
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\tPush\n";
                }
                else{
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\t\tPush\n";
		}
                step++;
            }
            else if (input[i] == 'i' && top == '6'){
                stk.push('i');
                stk.push('d');
                stk.push('5');
                input.erase(0,1); 
                input.erase(0,1);
                if (stk.size() > 7){
                	cout << step << "\t\t" << display(stk) << "\t\t" << input << "\t\tPush\n";
                }
                else if (input.size() >=7){
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\tPush\n";
                }
                else{
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\t\tPush\n";
		}
                step++;
            }
            else if(input[i] == '(' && top == '0')
            {
                stk.push('(');
                stk.push('4');
                input.erase(0,1);
                if (stk.size() > 6){
                	cout << step << "\t\t" << display(stk) << "\t\t" << input << "\t\tPush\n";
                }
                else if (input.size() >=7){
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\tPush\n";
                }
                else{
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\t\tPush\n";
		}
                step++;
            }
            else if(input[i] == ')' && top == '8')
            {
                stk.push(')');
                stk.push('1');
                stk.push('1');
                input.erase(0,1);
                if (stk.size() > 7){
                	cout << step << "\t\t" << display(stk) << "\t\t" << input << "\t\tPush\n";
                }
                else if (input.size() >=7){
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\tPush\n";
                }
                else{
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\t\tPush\n";
		}
                step++;
            }
            else if(input[i] == ')' && top == '7')
            {
                stk.push(')');
                stk.push('2');
                input.erase(0,1);
                if (stk.size() > 7){
                	cout << step << "\t\t" << display(stk) << "\t\t" << input << "\t\tPush\n";
                }
                else if (input.size() >=7){
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\tPush\n";
                }
                else{
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\t\tPush\n";
		}
                step++;
            }
            else if(input[i] == '+' && top == '8')
            {
                stk.push('+');
                stk.push('6');
                input.erase(0,1);
                if (stk.size() > 7){
                	cout << step << "\t\t" << display(stk) << "\t\t" << input << "\t\tPush\n";
                }
                else if (input.size() >=7){
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\tPush\n";
                }
                else{
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\t\tPush\n";
		}
                step++;
            }
            else if(input[i] == '*' && top == '2')
            {
                stk.push('*');
                stk.push('7');
                input.erase(0,1);
                if (stk.size() > 7){
                	cout << step << "\t\t" << display(stk) << "\t\t" << input << "\t\tPush\n";
                }
                else if (input.size() >=7){
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\tPush\n";
                }
                else{
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\t\tPush\n";
		}
                step++;
            }
            //Check for reduction
            else
            {
                stack<char> sk2;
                sk2 = stk;
                stk = reduction_Rules(stk);
                if (stk.size() > 7){
                	cout << step << "\t\t" << display(stk) << "\t\t" << input << "\t\tReduce\n";
                }
                else if (input.size() >=7){
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\tReduce\n";
                }
                else{
                	cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\t\tReduce\n";
		}
                step++;
                if(sk2.top() == stk.top())
                {
                    if (stk.size() > 7){
                		cout << step << "\t\t" << display(stk) << "\t\t" << input << "\t\tREJECTED\n";
			}
			else if (input.size() >=7){
                		cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\tREJECTED\n";
                	}      		         	
			else{
                		cout << step << "\t\t" << display(stk) << "\t\t\t" << input << "\t\tREJECTED\n";
			}
                    break; //Break out of while loop
                }
            }
            //cout << display(stk) << endl;
            //break;
        }
        
        
        
    }
}
    
int main() {
    // Test input strings
    vector<string>inputs;
    //inputs.push_back("id$");
    inputs.push_back("(id+id)*id$");
    inputs.push_back("id*id$");
    inputs.push_back("(id*)$");
    inputs.push_back("id$");
    inputs.push_back("(id)$");
    // vector<string> inputs = {
    //     "id$",
    //     "(id+id)*id$",
    //     "id*id$",
    //     "(id*)$"
    // };
    //cout << inputs[2] << endl;
    //cfg_Parsing(inputs[2]); //Testing 
    // Perform predictive parsing for each input string
    for (int i = 0; i < 5; i++) {
        cout << "Input String: " << inputs[i] << "\n";
        cfg_Parsing(inputs[i]);
        cout << "-------------------------------------------------------------------\n\n";
    }
    return 0;
}