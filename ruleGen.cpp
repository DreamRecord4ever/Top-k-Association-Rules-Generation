#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include "double_map.h"


#define OVERFLOW 0
#define NORMAL   1

using namespace std;

string buffer;
string MovieID,UserID;
double_map MovieData;

class Rule;
class Pair;

/* get next line of this file */
bool NextLine(fstream &file,string &buffer){

    while( getline(file,buffer) ){

        if(  buffer.substr(0,19) == "product/productId: "
          || buffer.substr(0,15) == "review/userId: " )

             return true;

    }

    return false;

}

class MovieList{

    vector <int> List;

public:

    MovieList(int NewMovieID = -1){

        List.push_back( NewMovieID );
    }

    void add(int NewMovieID = -1){

        List.push_back( NewMovieID );
    }

    void show(fstream &OutputFile){

        for(vector<int>::iterator It = List.begin() ; It != List.end() ; It++)
            OutputFile<<*It<<" ";

        OutputFile<<endl;
    }

};

/* increment counter */
bool _increment(string& IndexStr, int index){
    IndexStr[index] += 1;
    if(IndexStr[index] == '2'){
        IndexStr[index] = '0';
        return true; // carry
    }
    return false;
}

int Increment(string& IndexStr){
    int len = IndexStr.length();
    int i = 0;
    while(1){
        bool carry = _increment(IndexStr, i);
        if(carry){
            i++;
            if(i == len)
                return OVERFLOW;
        }
        else
            break;
    }
    return NORMAL;
}

bool ItemCompare(int a,int b){

    string string1 = MovieData.find_movie_name(a);
    string string2 = MovieData.find_movie_name(b);

    if( string1.compare(string2) < 0 )
        return true;

    return false;
}

class Rule{

    vector<int> Left;
    vector<int> Right;
    double      Support;
    double      Confidence;

public:

    void addLeftSide(int newMovie){

        Left.push_back(newMovie);
        ReOrder();
    }

    void addRightSide(int newMovie){

        Right.push_back(newMovie);
        ReOrder();
    }

    void addSupport(double newSupport){
        Support = newSupport;
    }

    const vector<int>& RetLeft(){
        return Left;
    }

    const vector<int>& RetRight(){
        return Right;
    }

    double ComputeConf(double LeftSup){

        Confidence = Support / LeftSup;
        return Confidence;
    }

    double RetSup(){
        return Support;
    }

    double RetConf(){
        return Confidence;
    }

    void ReOrder(){

        sort(Left.begin() , Left.end() , ItemCompare);
        sort(Right.begin() , Right.end() , ItemCompare);

    }

    void show(){

        for(int i=0 ; i<Left.size() ; i++){
            cout<<MovieData.find_movie_name( Left[i] );

            if(i == Left.size()-1 )
                break;

            cout<<",";
        }

        cout<<"->";

        for(int i=0 ; i<Right.size() ; i++){
            cout<<MovieData.find_movie_name( Right[i] );

            if(i == Right.size()-1 )
                break;

            cout<<",";
        }

        cout<<" Sup = "<<Support<<" Conf = "<<Confidence<<endl;
    }
};

class Pair{

    vector<int> MovieList;
    double      Support;
    int         counter;

public:

    Pair(){
        counter = 0;
    }

    void addNewMovie(int newMovie){
        MovieList.push_back(newMovie);
        ReOrder();
        counter++;
    }

    void addSupport(double newSupport){
        Support = newSupport / 100;
    }

    const vector<int>& RetMovieList(){
        return MovieList;
    }

    void ReOrder(){

        sort(MovieList.begin() , MovieList.end() , ItemCompare);
    }

    double RetSupport(){
        return Support;
    }

    int RetCounter(){
        return counter;
    }

    void GenRules(vector<Rule> &RuleList){

        string IndexStr(MovieList.size() , '0');

        while( Increment(IndexStr) != OVERFLOW ){

            Rule temp;

            for(int i=0 ; i<IndexStr.length() ; i++){
                if( IndexStr[i] == '0' )
                    temp.addLeftSide(MovieList[i]);
                else
                    temp.addRightSide(MovieList[i]);
            }

            temp.addSupport(Support);
            RuleList.push_back(temp);
        }

        RuleList.pop_back();
    }

    void show(){
        for(vector<int>::iterator MovieList_It=MovieList.begin() ; MovieList_It!=MovieList.end() ; MovieList_It++)
            cout<<*MovieList_It<<" ";

        cout<<"Support = "<<Support<<endl;
    }
};



/* in main */
    /* sort pair */
bool PairCompare(Pair a, Pair b){

    if(a.RetSupport() != b.RetSupport())
        return a.RetSupport() > b.RetSupport();
    return a.RetCounter() < b.RetCounter();

}

/* in main */
    /* sort Rule */
bool LexIsSmaller(Rule &a, Rule &b){

    /* combine LHS and RHS of rule a */
    vector<string> aStr;
    int aleftsize = a.RetLeft().size();
    int arightsize = a.RetRight().size();

    for(int i=0 ; i<aleftsize; i++){

        string str = MovieData.find_movie_name( (a.RetLeft())[i] );
        aStr.push_back(str);
    }

    for(int i=0 ; i<arightsize; i++){

        string str = MovieData.find_movie_name( (a.RetRight())[i] );
        aStr.push_back(str);
    }

    /* combine LHS and RHS of rule b */
    vector<string> bStr;
    int bleftsize = b.RetLeft().size();
    int brightsize = b.RetRight().size();

    for(int i=0 ; i<bleftsize; i++){

        string str = MovieData.find_movie_name( (b.RetLeft())[i] );
        bStr.push_back(str);
    }

    for(int i=0 ; i<brightsize; i++){

        string str = MovieData.find_movie_name( (b.RetRight())[i] );
        bStr.push_back(str);
    }

    for(int i=0 ; i<aStr.size() && i<bStr.size() ; i++){

        string str1 = aStr[i];
        string str2 = bStr[i];

        if( str1.compare(str2) < 0 )
            return true;
        else if( str1.compare(str2) > 0 )
            return false;

    }

    return aStr.size() < bStr.size();
}

bool RuleCompare(Rule a, Rule b){

    if( a.RetSup() != b.RetSup() )
        return a.RetSup() > b.RetSup();
    else if( a.RetConf() != b.RetConf() )
        return a.RetConf() > b.RetConf();
    return LexIsSmaller(a,b);

}
     /* a & LHS of a->b isEqual */
bool isEqual(const vector<int> &a,const vector<int> &b){

    if( a.size() != b.size() )
        return false;

    for(int i=0 ; i<a.size() ; i++){
        if( a[i] != b[i] )
            return false;
    }

    return true;
}

string ftoa(double value) {
  std::ostringstream o;
  if (!(o << value))
    return "";
  return o.str();
}

int main (int argc, char* argv[]){

    ///* Parser *///

{
    /* declaration */
    fstream InputFile1(argv[1],ios::in);
    fstream OutputFile1;
    map <string,MovieList> DataBase;
    map <string,MovieList>::iterator DataBase_It;

    while( NextLine(InputFile1,MovieID) ){

        /* get movie ID */
        MovieID.erase(0,19); // trim

        /* get user ID */
        NextLine(InputFile1,UserID);
        UserID.erase(0,15); // trim

        /* transfer MovieID to num */
        int temp = MovieData.find_id(MovieID);
        if( temp < 0 ) // not exist
            temp = MovieData.insert(MovieID);


        /* insert into Database */
            /* find if already exist */

        DataBase_It = DataBase.find( UserID );

        if( DataBase_It == DataBase.end() ) // not found
            DataBase.insert( pair<string,MovieList>(UserID,MovieList(temp)) );
        else
            DataBase_It->second.add(temp);

    }

    OutputFile1.open("Transaction", ios::out | ios::trunc);

    for(DataBase_It = DataBase.begin() ; DataBase_It != DataBase.end() ; DataBase_It++)
        DataBase_It->second.show(OutputFile1);


}

//cout<<"Parser done..."<<endl;

    ///* Frequent Itemset Gen *///

{
//    system("make clean -C ./FPgrowth/fpgrowth/src");
//    system("make -C ./FPgrowth/fpgrowth/src");
    char command[100];
    string MinSup(ftoa( atof(argv[2]) * 100 ));
    string temp = "./FPgrowth/fpgrowth/src/fpgrowth -s" + MinSup + " Transaction Itemset";
    strcpy(command,temp.c_str());
    system(command);
}

//cout<<"Itemset Gen done..."<<endl;

    ///* RuleGen *///

    /* declaration */
    fstream      InputFile2("Itemset",ios::in);
    vector<Pair> PairList;
    int          NumOfRules = atoi( argv[4] );
    int          RuleCounter = 0;
    double       MinConf = 0;

    while( InputFile2>>buffer ){

        /* parse frequent itemset */
        Pair temp;
        while(1){
            if(buffer[0] == '(')
                break;

            temp.addNewMovie( atoi( buffer.c_str() ) );
            InputFile2>>buffer;
        }

        buffer = buffer.substr(1,buffer.length()-2);
        temp.addSupport( atof( buffer.c_str() ) );

        PairList.push_back(temp);
    }

    sort(PairList.begin(),PairList.end(),PairCompare);

    /* get min_conf */
    MinConf = atof( argv[3] );
    vector<Rule> ResultRuleList;
    double CurSup = 2;

    for(int i=0 ; i<PairList.size() ; i++){

        /* if # of generated rules meet request */
        if(PairList[i].RetSupport() < CurSup){
            if( RuleCounter >= NumOfRules)
                break;
            CurSup = PairList[i].RetSupport();
        }

        if( PairList[i].RetCounter() > 1 ){

            vector<Rule> RuleList;
            PairList[i].GenRules( RuleList );

            /* delete rules whose Conf < MinConf */
            for(int j=0 ; j<RuleList.size() ; j++){

                for(int k=0 ; k<PairList.size() ; k++){

                    if( isEqual( PairList[k].RetMovieList() , RuleList[j].RetLeft() ) ){

                        double LeftSupport = PairList[k].RetSupport();

                        if( RuleList[j].ComputeConf( LeftSupport ) < MinConf )
                            RuleList.erase( RuleList.begin() + j );

                    }
                }
            }

            /* sort by confidence */

            //sort(RuleList.begin(),RuleList.end(),RuleCompare);

            /* output result rules */
            for(int j=0 ; j<RuleList.size(); j++){

                ResultRuleList.push_back( RuleList[j] );
                RuleCounter++;
            }
        }
    }

    /* sort again if any Sup(rules) or Conf(rules) are the same */
    sort(ResultRuleList.begin(),ResultRuleList.end(),RuleCompare);

    for(int j=0 ; j<NumOfRules; j++)
        ResultRuleList[j].show();
}
