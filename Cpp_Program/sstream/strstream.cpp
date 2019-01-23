#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

#define UV_HANDLE_FIELDS \
void* data; \
int* pint;

using namespace std;

// class uv__loop_t{
//   public:
//    int closing_handles;
//    int stop_flag;
//   private:
//    int update_time;
// };
struct PersonInfo
{
  string name;
  vector<string> phones;
  UV_HANDLE_FIELDS;
};

int main()
{
  // uv__loop_t* loop;
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
    int i = 13;
    personInfo.data = &i;
    cout << personInfo.data <<endl;
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
  // const int csint = 12;
  // const int *const pint = &csint;
  // cout << *pint << endl;
  // cin.tie(&cout);
  // ostream *old_tie = cin.tie(nullptr);
  // cin.tie(&cerr);
  // cin.tie(old_tie);
  //int timeout;
  // cout << timeout << endl;
  return 0;
}
