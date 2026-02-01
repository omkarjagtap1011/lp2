#include<iostream>
#include<vector>
using namespace std;

void printArray(vector<int>& arr){
    for(int i: arr){
        cout<<i<<" ";
    }
    cout<<"\n";
}

void swapElements(int i, int j, vector<int>& arr){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}


int main(){
    int n;
    cout<<"Enter Size of array: ";
    cin>>n;

    vector<int> arr(n);

    cout<<"\nEnter Elements:\n";
    for(int i; i<n; i++){
        cin>>arr[i];
    }

    for(int i=0; i<n; i++){
        cout<<"\nIteration "<< i + 1<<endl;
        cout<<"Array State\n";
        printArray(arr);
        cout<<"i="<<i<<endl;
        cout<<"arr[i]="<<arr[i]<<"\n\n";

        int minEleIndex = i;
        for(int j=i+1; j<n; j++){
            if(arr[j] < arr[minEleIndex]) minEleIndex = j;
        }
        
        cout<<"Minimum Element in range of arr[i] to arr[n-1]: "<<arr[minEleIndex]<<endl;
        cout<<"Swapping MinElement with arr[i]"<<endl;
        swapElements(i, minEleIndex, arr);
        cout<<"Array State\n";
        printArray(arr);
        cout<<"================================\n";
    }
    cout<<"Time Complexity: O(n^2)\nSpace Complexity: O(n) [input array]";
    return 0;
}