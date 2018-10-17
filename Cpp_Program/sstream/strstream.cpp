#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

struct PersonInfo
{
  string name;
  vector<string> phones;
};

int main()
{
  string line, word;
  vector<PersonInfo> people;
  ifstream ifiles("phone.txt");
  istringstream record;
  while (getline(ifiles,line))
  {
    // cout << "ifiles" << endl;
    PersonInfo personInfo;
    record.clear();
    record.str(line);
    record >> personInfo.name;
    while (record >> word)
      personInfo.phones.push_back(word);
    people.push_back(personInfo);
  }
  for (const auto &entry : people)
  {
    cout << entry.name <<endl;;
    ostringstream osNums;
    for (const auto &nums : entry.phones)
    {
      osNums << nums; // 向ostringstream写入，进行检验就很有用！
      cout << nums <<endl;;
    }
  }
  ifiles.close();
  // cin.tie(&cout);
  // ostream *old_tie = cin.tie(nullptr);
  // cin.tie(&cerr);
  // cin.tie(old_tie);
  int timeout;
  cout << timeout << endl;
  return 0;
}
