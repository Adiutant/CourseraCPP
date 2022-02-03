#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class SortedStrings{
    private:
    vector<string> m_strings_{};
    void SortStrings(){
        sort(this->m_strings_.begin(),this->m_strings_.end());
    }
    public:
    vector<string> GetSortedStrings()
    {
        SortStrings();
        return m_strings_;
    }
    void AddString(const string& new_string)
    {
        m_strings_.push_back(new_string);
    }


};

void PrintSortedStrings(SortedStrings& strings)
{
    for (auto str : strings.GetSortedStrings())
    {
        cout<<str<<endl;
    }
}


