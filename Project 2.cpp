#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main(){

    vector<vector<double>> dataSet;
    ifstream myfile("CS170_Small_Data__96.txt"); 
    string content;
    double value; //change all doubles to floats to see if it still runs accurately and runs faster

    while(getline(myfile, content)){
        stringstream row(content); 
        vector<double> temp;
        while(row >> value){
            temp.push_back(value);
        }
        dataSet.push_back(temp);
    }

    myfile.close();

    /*
    for (int i = 0; i < dataSet.size(); i++)
    {
        for (int j = 0; j < dataSet[i].size(); j++)
        {
            cout << dataSet[i][j] << " ";
        }

        cout << endl;
    }
    */

    return 0;
}