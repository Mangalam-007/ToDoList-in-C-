#include<bits/stdc++.h>
#include<ostream>
#include<ctime>
using namespace std;
void help()
{
    cout<<"Usage:-"<<endl;
    cout<<"$ ./todo add \"todo item\"  # Add a new todo"<<endl;
    cout<<"$ ./todo ls               # Show remaining todos"<<endl;
    cout<<"$ ./todo del NUMBER       # Delete a todo"<<endl;
    cout<<"$ ./todo done NUMBER      # Complete a todo"<<endl;
    cout<<"$ ./todo help             # Show usage"<<endl;
    cout<<"$ ./todo report           # Statistics"<<endl;
}
void listTask(list<string> &taskList)
{
    int i=taskList.size();
    if(i==0)
        cout<<"There is no task to do.";
    else
    {
        for(auto it = taskList.end(); it != taskList.begin();)
            {
                it--;
                cout <<"["<<i<<"] "<<*it<<endl;
                i--;
            }
    }
}
void printTime(int t,int d) 
{
    time_t now = time(0);
   tm *ltm = localtime(&now);
   cout << 1900 + ltm->tm_year;
   if((1 + ltm->tm_mon)<10)
   cout <<"-0"<< 1 + ltm->tm_mon;
   if((ltm->tm_mday)<10)
   cout <<"-0"<< ltm->tm_mday ;
    cout<<" Pending : "<<t<<" Completed : "<<d<<endl;
}
void addTask(int argc,char* argv[],list<string> &taskList)
{
    string st="";
    for(int i=2;i<argc;i++)
        {
            st+=argv[i];
            st+=" ";
        }
    taskList.push_back(st);
    cout<<"Added todo: "<<st<<endl;
}
void deleteTask(char* argv[], list<string> &taskList)
{
    int number=atoi(argv[2]),i=1;
    if(number<=taskList.size())
    {
        cout<<"Deleted todo #"<<number<<endl;
        auto it=taskList.begin();
            while(i<number)
            {
                it++;
                i++;
            }
        taskList.erase(it);
    }
    else
        cout<<"todo #"<<number<<" does not exist. Nothing deleted."<<endl;
}
void taskDone(char* argv[],list<string> &taskList,list<string> &doneTask)
{
    int number=atoi(argv[2]),i=1;
    if(number<=taskList.size())
    {   
        auto it=taskList.begin();
        while(i<number)
        {
            i++;
            it++;
        }
        doneTask.push_back(*it);
        taskList.erase(it);
        cout<<"Marked todo #"<<number<<" as done."<<endl;
    }
    else
        cout<<"todo #"<<number<<" does not exist."<<endl;
}
void updateToDo(list<string> taskList)
{
    ofstream fout;
    fout.open("todo.txt");
    for(auto it:taskList)
    {
        string line=it;
        fout << line<<endl ;
    }
    fout.close();
}
void updateDone(list<string> doneTask)
{
    ofstream fout;
    fout.open("done.txt");
    for(auto it:doneTask)
    {
        string line=it;
        fout << line<<endl ;
    }
    fout.close();
}
void readToDo(list<string> &taskList)
{
    ifstream fin;
    string line;
    fin.open("todo.txt");
    while (fin) 
    {
        getline(fin, line);
        taskList.push_back(line);
    }
    if(taskList.size()>0)
        taskList.pop_back();
    fin.close();
}
void readDoneTask(list<string> &doneTask)
{
    ifstream fin;
    string line;
    fin.open("done.txt");
    while (fin) 
    {
       getline(fin, line);
        doneTask.push_back(line);
    }
    if(doneTask.size()>0)
        doneTask.pop_back();
    fin.close();
}

int main(int argc, char* argv[])
{
    if(argc==1)
        {
            help();
            return 0;
        }
    int number,n,i;
    string task,line,st;
    list<string> taskList,doneTask;
    readToDo(taskList);
    readDoneTask(doneTask);
    map<string,int> m={{"help",1},{"ls",2},{"add",3},{"del",4},{"done",5},{"report",6}};
    n=m[argv[1]];
    switch(n)
    {
        case 1: help();
            break;
        case 2: listTask(taskList);
            break;
        case 3: addTask(argc,argv,taskList);
                updateToDo(taskList);
            break;
        case 4: deleteTask(argv,taskList);
                updateToDo(taskList);
            break;
        case 5: taskDone(argv,taskList,doneTask);
                updateToDo(taskList);
                updateDone(doneTask);
            break;
        case 6:
            printTime(taskList.size(),doneTask.size());
            break;
    }
    return 0;
}
