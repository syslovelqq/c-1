#include"Query.h"
#include"TextQuery.h"



 
 QueryResult OrQuery::eval(const TextQuery& text)const{
 	auto right=rhs.eval(text),left=lhs.eval(text);
 	auto ret_lines=make_shared<set<line_no>>(left.begin(),left.end());
 	ret_lines->insert(right.begin(),right.end());
 	return QueryResult(rep(),ret_lines,left.get_file());
 }
 
 QueryResult AndQuery::eval(const TextQuery& text)const{
 	auto left=lhs.eval(text),right=rhs.eval(text);
 	
 	auto ret_lines=make_shared<set<line_no>>();
 	//将两个范围的交集写入一个目的迭代器
	 set_intersection(left.begin(),left.end(),right.begin(),right.end(),inserter(*ret_lines,ret_lines->begin()));
	 return QueryResult(rep(),ret_lines,left.get_file()); 
 }
 
 QueryResult NotQuery::eval(const TextQuery& text)const{
 	auto result=query.eval(text);
 	//开始时set为空
	 auto ret_lines=make_shared<set<line_no>>(); 
	 auto beg=result.begin(),end=result.end();
	 //对于输入文件的每一行，如果该行不再result当中，则将其添加到set中
	 auto sz=result.get_file()->size();//10
	 for(size_t n=0;n!=sz;++n){
	 	if(beg==end||*beg!=n){
	 		ret_lines->insert(n);
		 }else if(beg!=end){
		 	beg++;
		 }
	 } 
	 return QueryResult(rep(),ret_lines,result.get_file());
 }
