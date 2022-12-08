#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>
#include <cmath>

using namespace std;

double crossValidation(vector<vector<double>> &data, vector<int> &currentFeatures, int featuretoAdd)
{
    int number_correctly_classified = 0;
    for(int i = 0; i < data.size(); i++){
        int objectLabel = data[i][0];

        double nearest_neighbor_distance = numeric_limits<double>::max();
        int nearest_neighbor_location = numeric_limits<int>::max();
        int nearest_neighbor_label = 0;

        for(int j = 0; j < data.size(); j++)
        {
            double distance = 0;
            if (j != i)
            {
                for(int k = 0; k < currentFeatures.size(); k++){
                    distance += pow(data[i][currentFeatures[k]] - data[j][currentFeatures[k]], 2);
                }

                distance += (pow(data[i][featuretoAdd] - data[j][featuretoAdd], 2.0));
                distance = sqrt(distance);

                if (distance < nearest_neighbor_distance)
                {
                    nearest_neighbor_distance = distance;
                    nearest_neighbor_location = j;
                    nearest_neighbor_label = data[nearest_neighbor_location][0];
                }
            }
        }
        if (objectLabel == nearest_neighbor_label)
        {
            number_correctly_classified++;
        }
    }
   
    return (double)number_correctly_classified/data.size()*100;
}

void search(vector<vector<double>> &data)
{
    vector<int> current_set_of_features;
    vector<int> bestFeatureSet;
    
    cout << "\nThis dataset has " << data[0].size()-1 << " features (not including the class attribute), with " << data.size() << " instances.\n\n";

    double bestOverallAccuracy = 0;
    double localBestAccuracy = 0;

    for(int i = 1; i < data[i].size(); i++){
        
        int feature_to_add_at_this_level;
        double bestAccuracy = 0;
        vector<int> outputfeature;
        
        for (int j = 1; j < data[j].size(); j++)
        {
            if (!(find(current_set_of_features.begin(), current_set_of_features.end(), j) != current_set_of_features.end()))
            {
                
                double accuracy = crossValidation(data, current_set_of_features, j);

                outputfeature = current_set_of_features;
                outputfeature.push_back(j);

                cout << "Using features(s) {";

                for (int i = 0; i < outputfeature.size(); i++)
                {
                    cout << outputfeature[i];
                    if(i != outputfeature.size()-1)
                    {
                        cout << ",";
                    }
                }

                cout << "} accuracy is "<< accuracy <<"%"<<endl;
                
                if (accuracy > bestAccuracy)
                {
                    bestAccuracy = accuracy;
                    localBestAccuracy = bestAccuracy;
                    feature_to_add_at_this_level = j;
                }
            }
        }

        if (bestAccuracy > bestOverallAccuracy)
        {
            bestOverallAccuracy = bestAccuracy;
            bestFeatureSet.push_back(feature_to_add_at_this_level);
        }

        current_set_of_features.push_back(feature_to_add_at_this_level);

        if (localBestAccuracy < bestOverallAccuracy)
        {
            cout << "\n(Warning, Accuraacy has decreased! Continuing search in case of local maxima)";
        }
        cout << "\nFeature set {";

        for (int i = 0; i < current_set_of_features.size(); i++)
        {
            cout << current_set_of_features[i];
            if(i != current_set_of_features.size()-1)
            {
                cout << ",";
            }
        }

        cout <<"} was best, accuracy is "<<localBestAccuracy<<"%\n";

        cout <<endl;
    
    }

    cout <<"Finished search!! The best feature subset is {";
    for (int i = 0; i < bestFeatureSet.size(); i++)
    {
            cout << bestFeatureSet[i];
            if(i != bestFeatureSet.size()-1)
            {
                cout << ",";
            }
    }
    cout << "}, which has an accuracy of " << bestOverallAccuracy << "%\n";
}

int main(){

    vector<vector<double>> dataSet; // small 17 large 95 is actual
    ifstream myfile("CS170_Small_Data__96.txt");  //CS170_Small_Data__96.txt for testing
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

    search(dataSet);
    
    return 0;
}