#include <iostream>
#include <fstream>

using namespace std;
//total number of programmers and departments we are matching 
const int NUMOFMATCHES = 5;

bool programmerPrefersCurDept(int preferences[NUMOFMATCHES*2][NUMOFMATCHES],int programmerIndex,int dep,int curDep){
    //checks the preferences of the programmer and if curDep appears first, we return true
    //if dep appears first, return false.
    for(int i = 0; i < NUMOFMATCHES; i++){
        if(preferences[programmerIndex][i] == curDep){
            return true;
        }
        if(preferences[programmerIndex][i] == dep){
            return false;
        }
    }
    //some error occurs default return false
    return false;
};
void matchPreferences(int preferences[NUMOFMATCHES*2][NUMOFMATCHES])
{
    //department assigned to the programmer at each index(i+1), Programmer[1] will hold the department that programmer 2 is assigned to
    int programmer[NUMOFMATCHES] = {-1,-1,-1,-1,-1};
    //keeps track of departments that do not have a programmer assigned to them
    bool takenDepart[NUMOFMATCHES] = {};
    int freeDep = 5;

    while(freeDep > 0){
        int d;
        //look for a department that needs to be matched.
        for(d=0; d<NUMOFMATCHES; d++){
            if(takenDepart[d] == false){
                break;
            }
        }
        //look through all of the departments matches as long as it is not matches and i<5
        for(int i = 0; i<NUMOFMATCHES && takenDepart[d]==false; i++)
        {
            //progPref is the programmer the current department prefers
            int progPref = preferences[d][i];
            //if programmer that department prefers is empty, assign this department to that programmer
            if(programmer[progPref-1]==-1){
                programmer[progPref-1]= d;
                takenDepart[d]= true;
                freeDep--;
            }
            else{
                //the current department that is assigned to the programmer
                int curDep = programmer[progPref-1];
                //pass index of the progPref and indexs of the current Department and the challenging department
                //if false is returned then the programmer prefers the challenging department more than the current department
                if(programmerPrefersCurDept(preferences, progPref+4, d+1, curDep+1) == false)
                {
                    programmer[progPref-1]= d;
                    takenDepart[d]= true;
                    takenDepart[curDep]=false;
                }
            }
        }
    }
    //print solution
    for (int i = 0; i < NUMOFMATCHES; i++){
        //cout << "Department #" << i+1 << " will get Programmer " << programmer[i]+1 << endl;
        for(int j=0; j < NUMOFMATCHES; j++){
            if(i==programmer[j]){
                cout << "Department #" << i+1 << " will get Programmer " << j+1 << endl; 
            }
        }
    }
};
int main()
{
    int preferences[NUMOFMATCHES*2][NUMOFMATCHES] = {-1};
    //get all the inputs from file if it is opened properly
    ifstream myFile;
    myFile.open("C:/Users/jsing/Desktop/EECS 348/EC1/matching-data.txt");
    if(myFile.fail())
    {
        cout << "File was unable to be opened."; 
    }
    else{
        while(myFile){
            for(int i = 0; i < NUMOFMATCHES; i++)
            {
                for(int j = 0; j < NUMOFMATCHES; j++)
                {
                    myFile >> preferences[j][i];                    
                }
            }
            for(int i = 0; i < NUMOFMATCHES; i++)
            {
                for(int j = NUMOFMATCHES; j < NUMOFMATCHES*2; j++)
                {
                    myFile >> preferences[j][i];             
                }
            }
        }
    }
    myFile.close();

    matchPreferences(preferences);
    return 0;
}