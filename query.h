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
#include"TextQuery.h"

using namespace std;

class Query_base{
	friend class Query;
	protected:
	//	using line_no=TextQuery::line_no;
		virtual ~Query_base()=default;
	private:
		//eval返回与当天Query匹配的QueryResult
		virtual QueryResult eval(const TextQuery&)const=0;
		//rep是表示查询的一个string
		virtual string rep()const =0; 
};

class Query{
	friend Query operator~(const Query&);
	friend Query operator|(const Query&,const Query&);
	friend Query operator&(const Query&,const Query&);
	
	public:
		Query(const string&);//构建一个新的WordQuery
		//接口函数：调用对应的Query_base操作
		QueryResult eval(const TextQuery& t)const {return q->eval(t);}
		
		string rep()const{return q->rep();}
	private:
		
		Query(shared_ptr<Query_base>query):q(query){}
		
		shared_ptr<Query_base>q; 
};



class WordQuery:public Query_base{
	friend class Query;
	WordQuery(const string&s):query_word(s){}
	QueryResult eval(const TextQuery& t)const{return t.query(query_word);}
	
	string rep()const{return query_word;}
	string query_word;
};
inline Query::Query(const string& s):q(new WordQuery(s)){}//Query中的参数为string的构造函数 

class NotQuery:public Query_base{
	friend Query operator~(const Query&);
	NotQuery(const Query& q):query(q){}//构造函数 
	//具体的类，NotQuery将定义所继承而来的纯虚函数
	string rep()const{
		return "~("+query.rep()+")";
	} 
	QueryResult eval(const TextQuery&)const;
	Query query;
};

inline Query operator~(const Query &operand){
	return shared_ptr<Query_base>(new NotQuery(operand));
	//隐含shared_ptr<Query_base>tme(new NotQuery(operand));
	//	   return Query(tme); 
}

class BinaryQuery:public Query_base{
	protected:
		BinaryQuery(const Query& l,const Query& r,string s):lhs(l),rhs(r),opSym(s){}
		//抽象类：不定义eval
		string rep()const{return "("+lhs.rep()+" "+opSym+" "+rhs.rep()+")";}
		Query lhs,rhs;//左侧和右侧运算对象 
		string opSym;//运算符的名字 
};

class AndQuery:public BinaryQuery{
	friend Query operator&(const Query&,const Query&);
	AndQuery(const Query& left,const Query& right):BinaryQuery(left,right,"&"){}
	QueryResult eval(const TextQuery&)const;
};
inline Query operator&(const Query& lhs,const Query& rhs){
	return shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}

class OrQuery:public BinaryQuery{
	friend Query operator|(const Query&,const Query&);
	OrQuery(const Query& left,const Query& right):BinaryQuery(left,right,"|"){}
	QueryResult eval(const TextQuery&)const;
};

inline Query operator|(const Query& lhs,const Query& rhs){
	return shared_ptr<Query_base>(new OrQuery(lhs,rhs));
}
