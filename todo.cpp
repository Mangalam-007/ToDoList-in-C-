#include<bits/stdc++.h>
#include<ostream>
#include<iterator>
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

void printTime() {
    time_t now = time(0);
   tm *ltm = localtime(&now);
   cout << 1900 + ltm->tm_year;
   if((1 + ltm->tm_mon)<10)
   cout <<"-0"<< 1 + ltm->tm_mon;
   if((ltm->tm_mday)<10)
   cout <<"-0"<< ltm->tm_mday ;
}

int main(int argc, char* argv[])
{
    if(argc==1)
            {help();return 0;}

    int number,n,i,completed=0;
    list <string> :: iterator it;
    string task,line,st;
    list<string> taskList;
    list<string> doneTask;
     ifstream fin;

    //read todo.txt
	fin.open("todo.txt");
	while (fin) {
		getline(fin, line);
		taskList.push_back(line);
        }
    if(taskList.size()>0)
        taskList.pop_back();
	fin.close();

	//read done.txt
	fin.open("done.txt");
	while (fin) {


		getline(fin, line);


		doneTask.push_back(line);

	}
    if(doneTask.size()>0)
        doneTask.pop_back();
	fin.close();

    map<string,int> m;
    m.insert(pair<string,int>("help",1));
    m.insert(pair<string,int>("ls",2));
    m.insert(pair<string,int>("add",3));
    m.insert(pair<string,int>("del",4));
    m.insert(pair<string,int>("done",5));
    m.insert(pair<string,int>("report",6));
        n=m[argv[1]];
        switch(n)
            {
                case 1: help();
                    break;
                case 2: i=taskList.size();
                        for(it = taskList.end(); it != taskList.begin();)
                            {
                                it--;
                                cout <<"["<<i<<"] "<<*it<<endl;
                                i--;
                            }
                    break;
                case 3: st=argv[2];
                    taskList.push_back(st);
                        cout<<"Added todo: "<<argv[2]<<endl;
                        break;
                case 4: number=atoi(argv[2]);
                if(number<=taskList.size())
                {
		    cout<<"Deleted todo #"<<number<<endl;
                    it=taskList.begin();
                    number--;
                        while(number--)
                        {
                            it++;
                        }
                    taskList.erase(it);
                }
                else
                    cout<<"todo #"<<number<<" does not exist. Nothing deleted."<<endl;
                        break;
                case 5:number=atoi(argv[2]);
                if(number<=taskList.size())
                {   cout<<"Marked todo #"<<number<<" as done."<<endl;
                        number--;
                        it=taskList.begin();
                        while(number--)
                        {
                            it++;
                        }
                        doneTask.push_back(*it);
                        taskList.erase(it);
                        completed++;
                }
                else
                    cout<<"todo #"<<number<<" does not exist."<<endl;
                break;
                case 6:
                    printTime();
                    cout<<" Pending : "<<taskList.size()<<" Completed : "<<doneTask.size()<<endl;
                            break;
            }


//todo.txt write
if(n>2&&n<6)
{
    ofstream fout;
	fout.open("todo.txt");
	for(it=taskList.begin();it!=taskList.end();it++)
		{
        line=*it;
        if((it++)==taskList.end())
            {fout<<line;break;}
        else
		{it--;
		fout << line<<endl ;
		}
		}
	fout.close();
}

//done.txt write
        if(n==5)
           {
               ofstream fout;

	fout.open("done.txt");
	for(it=doneTask.begin();it!=doneTask.end();it++)
		{
        line=*it;
        if((it++)==doneTask.end())
            {fout<<line;break;}
        else
            {it--;
            fout << line<<endl ;
            }
		}
	fout.close();
           }
            return 0;
}
