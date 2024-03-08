#include <bits/stdc++.h>

struct customStruct{
    bool isPairFound = false;
    std::pair<int, int> pairSumToTarget;
};

customStruct HasPairWithTargetSum(std::vector<int> values, int targetSum){
    customStruct myPair;
    std::unordered_set<int> complementsVector;
    for(int data : values){
        if(complementsVector.find(data) != complementsVector.end()){
            myPair.isPairFound = true;
            myPair.pairSumToTarget.first = targetSum - data;
            myPair.pairSumToTarget.second = data;
            return myPair;
        }

        complementsVector.insert(targetSum - data);
    }

    return myPair;
}

int main(){
    std::vector<int> values = {1, 4, 5, 9, 7};
    int targetSum = 10;
    customStruct myPair = HasPairWithTargetSum(values, targetSum);
    if(myPair.isPairFound){
        std::cout <<"The pairs that sum to " << targetSum << " in the vector are : " << myPair.pairSumToTarget.first << " and " << myPair.pairSumToTarget.second << ".";
    }else{
        std::cout << "No matching pairs were found in the vector that sum to " << targetSum << ".";
    }

    std::cout << '\n';
    return 0;
}
