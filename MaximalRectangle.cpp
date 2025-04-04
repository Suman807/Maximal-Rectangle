// Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
// Output: 6
// Explanation: The maximal rectangle is shown in the above picture.
// Example 2:

// Input: matrix = [["0"]]
// Output: 0
// Example 3:

// Input: matrix = [["1"]]
// Output: 1

// example 1
// 1 0 1 0 0
// 1 0 1 1 1
// 1 1 1 1 1
// 1 0 0 1 0

#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

void histogram_bruteforce(vector<int> &v, int &maxLen){
    for (int i = 0; i < v.size(); i++)
    {
        int minh = v[i];
        for (int j = i; j < v.size(); j++)
        {
            minh = min(minh,v[j]);
            maxLen = max(maxLen,(j-i+1)*minh);
        }
        
    }
    
}


//stack approach
void histogram_stack(vector<int> &v, int &maxLen){
    stack<int> st;
    vector<int> left(v.size(),0);
    vector<int> right(v.size(),0);
    int i = 0;
    for (int i = 0; i < v.size(); i++)
    {
        while (!st.empty() && v[i] <= v[st.top()])
        {
            st.pop();
        }

        if(st.empty()) left[i] = 0;
        else left[i] = st.top()+1;
        st.push(i);
    }

    while (!st.empty())
    {
        st.pop();
    }

    for (int i = v.size()-1; i >= 0; i--)
    {
        while (!st.empty() && v[i]<=v[st.top()])
        {
            st.pop();
        }

        if(st.empty()) right[i] = v.size()-1;
        else right[i] = st.top()-1;
        st.push(i);
    }
    
    for (int i = 0; i < v.size(); i++)
    {
        maxLen = max(maxLen,(right[i]-left[i]+1)*v[i]);
    }
    
}

//stack  2 approaches
void histogram_stack2(vector<int> &v,int &maxLen){
    stack<int> st;
    int rs=0,h=0;
    
    for (int i = 0; i <= v.size(); i++)
    {
        while (!st.empty() && (i==v.size() || v[i]<=v[st.top()]))
        {
            h = v[st.top()]; st.pop();
            if (st.empty()) rs = i;
            else rs = i-st.top()-1;
            maxLen = max(maxLen,rs*h);
        }
        st.push(i);
    }
    
}

void rec(vector<vector<char>> &nums,int &ans){
    vector<int> v(nums[0].size(),0);
    int maxLen = 0;
    
    for (size_t i = 0; i < nums.size(); i++)
    {
        for (size_t j = 0; j < nums[0].size();j++)
        {
            if (nums[i][j] == '1') v[j]++;
            else v[j] = 0;
        }
        histogram_stack2(v,maxLen);
    
    }
    ans = maxLen;
    
}

int main(){
    vector<vector<char>> nums = {{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}};
    int ans=0;
    
    auto startTime = high_resolution_clock::now();
    rec(nums,ans);
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(endTime-startTime);
    
    cout<<"sec : "<<duration.count()<<endl;
    cout<<ans<<endl;
    
    return 0;
}
