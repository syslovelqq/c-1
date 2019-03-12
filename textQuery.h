#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<list>
#include<map>
#include<set>
#include<algorithm>
#include<numeric>
#include<memory>
#include<utility>

using namespace std;

#ifndef __TestC____TextQuery__
#define __TestC____TextQuery__
class QueryResult;
class TextQuery;
//using line_no =vector<string>::size_type;
typedef vector<string>::size_type line_no
class TextQuery{
	friend class QueryResult;
	public:
		
		TextQuery(ifstream&);//构造函数 
		QueryResult query(const string&) const;//查询 
	
	private:
		shared_ptr<vector<string>>file;//用来存储每行的数据 
		map<string,std::shared_ptr<set<line_no>>>wm;//用来存储单词与行号的联系。 
};


//class TextQuery;
class QueryResult{
		friend TextQuery;
		friend ostream& print(ostream&,const QueryResult&);
		
	public:
		QueryResult()=default;
		QueryResult(const string&s,shared_ptr<set<line_no>>p,shared_ptr<vector<string>>f):sought(s),lines(p),file(f){}
		set<line_no>::iterator begin();
		set<line_no>::iterator end();
		shared_ptr<vector<string>>get_file();
	private:
		string sought;//查询单词 
		shared_ptr<set<line_no>>lines;//出现行号的set的智能指针。 
		shared_ptr<vector<string>>file;//输入文件 
};
#endif
