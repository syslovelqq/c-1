#include <iostream>
//#include <fstream>
#include"TextQuery.h"
#include"Query.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

ostream& operator<<(ostream& os,const Query& query){
	return os<<query.rep();
}
int main(int argc, char** argv) {
	string infile="in.txt";
 	ifstream input(infile);
//	input.open(infile);
 	cout<<input.is_open();
 	if(input){
 		TextQuery in1(input);
 		string word;
 		Query q=Query("fiery")&Query("bird")|Query("wind");
 		cout<<q<<endl;
 		print(cout,q.eval(in1));
 	//		Query q=Query("hair")|Query("Alice");
 	//		cout<<q<<endl;
 	//		print(cout,q.eval(in1));
 	//		Query q=~Query("Alice");
 	//		cout<<q.rep()<<endl;
 	//		print(cout,q.eval(in1));
	 }
	return 0;
}
