#include"TextQuery.h"


	TextQuery::TextQuery(ifstream& is):file(new vector<string>){
		string text;
		while(getline(is,text)){
			file->push_back(text);
			int n=file->size()-1;//当前行号 
			istringstream line(text);
			string word;
			while(line>>word){
				auto &lines=wm[word];//这里的引用很重要 
				if(!lines){
					lines.reset(new set<line_no>);
				}
				lines->insert(n);
			}
		}
		
	}
	
	QueryResult TextQuery::query(const string &sought)const{
	//如果未找到sought，我们返回一个指向此set的指针。
	static shared_ptr<set<line_no>>nodata(new set<line_no>);
	auto loc =wm.find(sought);//得到一个pair对 
	if(loc==wm.end()){
		return QueryResult(sought,nodata,file);
	}
	else{
		return QueryResult(sought,loc->second,file);
	}
}

ostream& print(ostream& os,const QueryResult &qr){
	os<<qr.sought<<" occurs "<<qr.lines->size()<<" "
	<<(qr.lines->size() > 1 ? " times" : " time")<<endl;
	
	for(auto num :*qr.lines){
		os<<"\t(line "<<num+1<<" )"<<*(qr.file->begin()+num)<<endl;
		
	}
	return os;
}
 set<line_no>::iterator QueryResult::begin(){
 	return lines->begin();
 }
 
 set<line_no>::iterator QueryResult::end(){
 	return lines->end();
 }
 
 shared_ptr<vector<string>> QueryResult::get_file(){
 	return file;
 }
