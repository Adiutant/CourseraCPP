#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;


class Person{
public:
    Person(const string& first_name,const string& last_name,const int& birth_year){
        ChangeFirstName(birth_year,first_name);
        ChangeLastName(birth_year,last_name);
        birth_date = birth_year;
    }
    Person(){}
    void ChangeFirstName(int year, const string& first_name) {
        if (m_history_[year].empty()) {
            if ( std::find(m_years.begin(), m_years.end(), year)== m_years.end()) {
                m_years.push_back(year);
            }
            m_history_[year] = {"","",""};
            if (findLastYear(year)!=0&&!m_history_[findLastYear(year)][1].empty())
            {
                m_history_[year][1] = m_history_[findLastYear(year)][1];
            }
            m_history_[year][0] = first_name;
            m_history_[year][2] += "f";


        }
        else if( m_history_[year][0].empty()||m_history_[year][2]=="l"){
            if( std::find(m_years.begin(), m_years.end(), year) == m_years.end()) {
                m_years.push_back(year);
            }
            m_history_[year][0] = first_name;
            if (findLastYear(year)!=0&&!m_history_[findLastYear(year)][1].empty())
            {
                m_history_[year][1] = m_history_[findLastYear(year)][1];
            }
            m_history_[year][2] += "f";

        }
        actualizeList();
    }
    void ChangeLastName(int year, const string& last_name) {
        if (m_history_[year].empty()) {
            if( std::find(m_years.begin(), m_years.end(), year) == m_years.end()) {
                m_years.push_back(year);
            }
            m_history_[year] = {"","",""};
            m_history_[year][1] = last_name;
            if (findLastYear(year)!=0&&!m_history_[findLastYear(year)][0].empty())
            {
                m_history_[year][0] = m_history_[findLastYear(year)][0];
            }

            m_history_[year][2] += "l";

        }
        else if( m_history_[year][1].empty()||m_history_[year][2]=="f"){
        if ( std::find(m_years.begin(), m_years.end(), year) == m_years.end()) {
                m_years.push_back(year);
            }
            m_history_[year][1] = last_name;
            if (findLastYear(year)!=0&&!m_history_[findLastYear(year)][0].empty())
            {
                m_history_[year][0] = m_history_[findLastYear(year)][0];
            }

            m_history_[year][2] += "l";

        }
        actualizeList();
    }
    string GetFullName(int year) {

        if (findLastYear(year)==0)
        {
            return "Incognito";
        }
        if (m_history_[findLastYear(year)][0].empty()&&!m_history_[findLastYear(year)][0].empty())
        {
            return m_history_[findLastYear(year)][1] + " with unknown first name";
        }
         if (m_history_[findLastYear(year)][1].empty()&&!m_history_[findLastYear(year)][0].empty())
        {
            return m_history_[findLastYear(year)][0] + " with unknown last name";
        }
        return m_history_[findLastYear(year)][0] + " " + m_history_[findLastYear(year)][1];
    }
    string GetFullNameWithHistory(int year) {
        return formFullHistoryName(year);
    }
private:
    string formFullHistoryName(int year){
        actualizeList();
        string name;
        string lastname;
        string nameHistory ="(";
        string lastnameHistory = "(";
        string result;
        if (findLastYear(year)==0)
        {
            return "Incognito";
        }
        else
        {
            lastname += m_history_[findLastYear(year)][1];
            name += m_history_[findLastYear(year)][0] ;
        }
        //int indexOfYear = 0;
        auto n = find(m_years.begin(), m_years.end(), findLastYear(year));
        auto indexOfYear = n-m_years.begin();
        string currentName= name;
        string currentLastname = lastname;
        for (int i = indexOfYear;i>=0;i--) {
            if (m_history_[m_years[i]][2] =="f"&&m_history_[m_years[i]][0]!=currentName) {
                currentName =m_history_[m_years[i]][0];
                if (nameHistory!="(")
                {
                    nameHistory+=", ";
                }
                nameHistory += m_history_[m_years[i]][0];
            }
            if (m_history_[m_years[i]][2] =="l"&&m_history_[m_years[i]][1]!=currentLastname) {
                currentLastname =m_history_[m_years[i]][1];
                if (lastnameHistory!="(")
                {
                    lastnameHistory+=", ";
                }
                lastnameHistory += m_history_[m_years[i]][1];
            }
            if (m_history_[m_years[i]][2] =="fl"&&m_history_[m_years[i]][1]!=currentLastname) {
                currentLastname =m_history_[m_years[i]][1];
                if (lastnameHistory!="(")
                {
                    lastnameHistory+=", ";
                }
                lastnameHistory += m_history_[m_years[i]][1];
            }
            if (m_history_[m_years[i]][2] =="fl"&&m_history_[m_years[i]][0]!=currentName) {
                currentName =m_history_[m_years[i]][0];
                if (nameHistory!="(")
                {
                    nameHistory+=", ";
                }
                nameHistory += m_history_[m_years[i]][0];
            }
        }
        nameHistory+=")";
        lastnameHistory+=")";
        if (nameHistory!="()")
        {
            name += " " + nameHistory;
        }
        if (lastnameHistory!="()")
        {
            lastname += " " + lastnameHistory;
        }
        if (name.empty())
        {
            return lastname+" " +"with unknown firstname";
        }
        if (lastname.empty())
        {
            return name+" " +"with unknown lastname";
        }
        return result+=name+" "+lastname;
    }
    void actualizeList(){
        sort(m_years.begin(),m_years.end());
        for (int i = m_years.size()-1;i>0;i--) {
            if (m_history_[m_years[i-1]][2] == "f"&&m_history_[m_years[i]][2] == "l"){
                m_history_[m_years[i]][0] =m_history_[m_years[i-1]][0];
            }
            if (m_history_[m_years[i-1]][2] == "l"&&m_history_[m_years[i]][2] == "f"){
                m_history_[m_years[i]][1] =m_history_[m_years[i-1]][1];
            }
            if (m_history_[m_years[i-1]][2] == "l"&&m_history_[m_years[i]][2] == "l"){
                m_history_[m_years[i]][0] =m_history_[m_years[i-1]][0];
            }
            if (m_history_[m_years[i-1]][2] == "f"&&m_history_[m_years[i]][2] == "f"){
                m_history_[m_years[i]][1] =m_history_[m_years[i-1]][1];
            }
        }
    }
    int findLastYear(int year)
    {
        sort(m_years.begin(),m_years.end());
        for (int i = m_years.size()-1;i>=0;i--)
        {
            if (m_years[i]<=year)
            {
                return m_years[i];
            }
        }
        return 0;
    }
    int birth_date;
    vector<int> m_years;
    map<int,vector<string>> m_history_;
};

int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}
