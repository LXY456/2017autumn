#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<conio.h>
#include<cstdio>
using namespace std;
enum StatusCode {SUCCESS,FAIL,UNDER_FLOW,OVER_FLOW,RANGE_ERROR,DUPLICATE_ERROR,NOT_PRESENT,ENTRY_INSERTED,ENTRY_FOUND,VISITED,UNVISITED};
template<class ElemType>
struct DblNode
{
	ElemType data;
	DblNode<ElemType> *back;
	DblNode<ElemType> *next;
	DblNode();
	DblNode(ElemType item,DblNode<ElemType> *linkback = NULL,DblNode<ElemType>*linknext = NULL);
};
template<class ElemType>
DblNode<ElemType>::DblNode()
{
	next = NULL;
}
template<class ElemType>
DblNode<ElemType>::DblNode(ElemType item,DblNode<ElemType> *linkback,DblNode<ElemType>*linknext)
{
	data = item;
	back = linkback;
	next = linknext;
}


template<class ElemType>
class DblLinkList
{
	public:
		DblNode<ElemType> *head;
		mutable int curPosition;
		mutable DblNode<ElemType> *curPtr;
		int count;
		DblNode<ElemType> *GetElemPtr(int position) const;
		void Init();
	public:
		DblLinkList();
		virtual ~DblLinkList();
		int Length() const;
		bool Empty() const;
		void Clear();
		void Traverse(void (*visit)(const ElemType &)) const;
		StatusCode GetElem(int position,ElemType &e) const;
		StatusCode SetElem(int position,const ElemType &e);
		StatusCode Delete(int position,ElemType &e);
		StatusCode Insert(int position,const ElemType &e);
		DblLinkList(const DblLinkList<ElemType>&copy);
	    DblLinkList<ElemType>&operator=(const DblLinkList<ElemType>&copy);
};
template<class ElemType>
DblNode<ElemType> *DblLinkList<ElemType>::GetElemPtr(int position) const
{
	if(curPosition<position)
	{
		for(;curPosition<position;curPosition++)
		{
			curPtr=curPtr->next;
		}
	}
	else if(curPosition>position)
	{
		for(;curPosition>position;curPosition--)
		{
			curPtr=curPtr->back;
		}
	}
	return curPtr;
}
template<class ElemType>
void DblLinkList<ElemType>::Init()
{
	head=new DblNode<ElemType>;
	head->next=head;
	curPtr=head;curPosition=0;
	count=0;
}
template<class ElemType>
DblLinkList<ElemType>::DblLinkList()
{
	Init();
}
template<class ElemType>
DblLinkList<ElemType>::~DblLinkList()
{
	Clear();
	delete head;
}
template<class ElemType>
int DblLinkList<ElemType>::Length() const
{
	return count;
}
template<class ElemType>
bool DblLinkList<ElemType>::Empty() const
{
	return head->next=NULL;
}
template<class ElemType>
void DblLinkList<ElemType>::Clear()
{
	ElemType tmpElem;
	while(Length()>0)
	{
		Delete(1,tmpElem);
	}
}
template<class ElemType>
void DblLinkList<ElemType>::Traverse(void(*visit)(const ElemType &)) const
{
	for(DblNode<ElemType>*tmpPtr=head->next;tmpPtr!=NULL;tmpPtr=tmpPtr->next)
	{
		(*visit)(tmpPtr->data);
	}
}
template<class ElemType>
StatusCode DblLinkList<ElemType>::GetElem(int position,ElemType &e) const
{
	if(position<1||position>Length())
	{
		return RANGE_ERROR;
	}
	else
	{
		DblNode<ElemType>*tmpPtr;
		tmpPtr=GetElemPtr(position);
		e=tmpPtr->data;
		return ENTRY_FOUND; 
	}
}
template<class ElemType>
StatusCode DblLinkList<ElemType>::SetElem(int position,const ElemType &e)
{
	if(position<1||position>Length())
	{
		return RANGE_ERROR;
	}
	else
	{
		DblNode<ElemType>*tmpPtr;
		tmpPtr=GetElemPtr(position);
		tmpPtr->data=e;
		return SUCCESS; 
	}
}
template<class ElemType>
StatusCode DblLinkList<ElemType>::Insert(int position,const ElemType &e)
{
	if(position<1||position>Length()+1)
	{
		return RANGE_ERROR;
	}
	else
	{
		DblNode<ElemType>*tmpPtr,*nextPtr,*newPtr;
		tmpPtr=GetElemPtr(position-1);
		nextPtr=tmpPtr->next;
		newPtr=new DblNode<ElemType>(e,tmpPtr,nextPtr);
		tmpPtr->next=newPtr;
		nextPtr->back=newPtr;
		curPosition=position;
		curPtr=newPtr;
		count++;
		return SUCCESS; 
	}
}
template<class ElemType>
StatusCode DblLinkList<ElemType>::Delete(int position,ElemType &e)
{
	if(position<1||position>Length())
	{
		return RANGE_ERROR;
	}
	else
	{
		DblNode<ElemType>*tmpPtr;
		tmpPtr=GetElemPtr(position-1);
		tmpPtr=tmpPtr->next;
		tmpPtr->back->next=tmpPtr->next;
		tmpPtr->next->back=tmpPtr->back;
		e=tmpPtr->data;
		if(position==Length())
		{
			curPosition=count-1;
			curPtr=tmpPtr->back;
		}
		else
		{
			curPosition=position;
			curPtr=tmpPtr->next;
		}
		count--;
		delete tmpPtr;
		return SUCCESS; 
	}
}
int main(void)
{
	DblLinkList<string> test;
	//input file
	ifstream infile;
	char infilename[1024];
	cout<<"Please input inputfile name(eg. file_in.txt):";
	cin>>infilename;
	infile.open(infilename,ios::in);
	//infile.open("test.txt",ios::in);
	if(infile.fail())
	{
		cout<<"open file error"<<endl;
		return -1;
	}
	
	ofstream outfile;
	char outfilename[1024];
	cout<<"Please input outputfile name(eg. file_out.txt):";
	cin>>outfilename;
	outfile.open(outfilename,ios::out);
	//outfile.open("another.txt",ios::out);
	
	/*if(test.Empty()==false)
	{
		cout<<"File buffer is empty(please press r to read file to buffer)."<<endl;
		cout<<"??";
	}*/ 
	cout<<"??";
    while(!false)
    {
    	int str = getchar();
    	switch(str)
	    {
		    case 'h':
		    {
			    cout<<"Valid commands are:"<<endl;
	            cout<<"b(egin),"<<"c(hange),"<<"d(el),"<<"e(nd),"<<"f(ind),"<<endl;
	            cout<<"g(o),"<<"h(elp),"<<"i(nsert),"<<"l(ength),"<<"n(ext),"<<endl;
	            cout<<"p(rior),"<<"q(uit),"<<"r(ead),"<<"s(ubstitute),"<<"v(iew),"<<"w(rite)"<<endl;
			    cout<<"??";
			    break;
			}
			case 'b':
			{
				if(test.count==0)
				{
					cout<<"0:"<<test.head->next->data<<endl;
				}
				else
				{
			    cout<<"1:"<<test.head->next->data<<endl;
			    }
				cout<<"??"; 
				break;
			}
			case 'r':
			{
				int testcount = 0;
				string buffer;
				char buf[1024];
				while(infile.getline(buf,sizeof(buf)))
				{
					buffer=buf;
					testcount=testcount+1;
					test.Insert(testcount,buffer);
				}
				cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
				cout<<"??";
	        	break;
	        }
	        case 'l':
	        {
	        	cout<<"There are "<<test.Length()<<" lines"<<endl;
	        	cout<<"Current line has "<<sizeof(test.curPtr->data)<<"..."<<endl;
	        	cout<<"??";
	        	break;
			}
			case 'e':
	        {
	        	cout<<test.count<<":"<<test.head->back->data<<endl;
	        	cout<<"??";
	        	break;
			}
			case 'd':
		    {
		    	string dteststr;
		    	test.Delete(test.curPosition,dteststr);
		    	if(test.count==0)
		    	{
		    		cout<<"There are not line."<<endl;
				}
				else
				{
		    	cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
		        }
		    	cout<<"??";
	        	break;
			}
			case 'g':
			{
				cin.get();
			    cout<<"Which line you want to go?  ";
			    int gi;
			    cin>>gi;
			    if(gi>test.count)
			    {
			    	cout<<"There are just "<<test.count<<" lines."<<endl;
				}
				else
				{
			    test.GetElemPtr(gi);
			    cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
			    }
				cout<<"??";
				break;
			}
			case 'i':
			{
				cin.get();
				cout<<"Which line you want to insert:  ";
				int ii;
				cin>>ii;
				cout<<"What you want to input:  ";
				string iteststr;
				cin>>iteststr;
				test.Insert(ii,iteststr);
				cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
				cout<<"??";
				break;
			}
			case 'n':
			{
				if(test.curPosition==test.count)
				{
					cout<<"this is the last line."<<endl; 
				}
				else
				{
					test.curPosition++;
					test.curPtr=test.curPtr->next;
				}
				cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
				cout<<"??";
				break;
			}
			case 'p':
			{
				if(test.curPosition==1)
				{
					cout<<"this is the first line."<<endl;
				}
				else
				{
					test.curPosition--;
					test.curPtr=test.curPtr->back;
				}
				cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
				cout<<"??";
				break;
			}
			case 'q':
			{
				return 0;
				break;
			}
			case 'v':
			{
				DblNode<string> *v;
				v=test.head;
				for(int i=0; i<test.count ; i++)
				{
					cout<<i+1<<":"<<v->next->data<<endl;
					v=v->next;
				}
				cout<<"??";
				break;
			} 
			case 's':
			{
				cin.get();
				cout<<"Which line you want to substitute:  ";
				int ci;
				cin>>ci;
				cout<<"substitute to:  ";
				string steststr;
				cin>>steststr;
				test.SetElem(ci,steststr);
				cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
				cout<<"??";
				break;
			}
			case 'c':
			{
				string cteststr1;
				string cteststr2;
				string cteststr3;
				cin.get();
				cout<<"What you want to change:";
				getline(cin,cteststr1);
				cout<<"change to:";
				getline(cin,cteststr2);
				//cout<<cteststr1<<","<<cteststr2<<endl;
				for(int i=0; i<test.count ; i++)
				{
					test.GetElem(i+1,cteststr3);
					if(cteststr3==cteststr1)
					{
						test.SetElem(i+1,cteststr2);
					}
				}
				cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
				cout<<"??";
				break;
			}
			case 'w':
			{
				outfile<<test.curPtr->data<<endl;
				cout<<test.curPosition<<":"<<test.curPtr->data<<endl;
				cout<<"??";
				break;
			}
			case 'f':
			{ 
			    string f;
			    cin.get();
			    cout<<"What you want to find:";
			    getline(cin,f);
                size_t position;  
                DblNode<string> *ff;
                ff=test.head->next;
                int fline=1;
                int fcount=0;
                for(int i=0;i<test.count;i++)
                {
                position = ff->data.find(f);  
                if (position != string::npos)  
                {
                    cout<<fline<<":"<<ff->data<< endl; 
					cout<<"  "; 
                    for(int j=0;j<position;j++)
                    {
                    	cout<<" ";
					}
					size_t len = f.size();
					for(int k=0;k<len;k++)
					{
						cout<<"^";
					}
					cout<<endl;
                }
                else  
                {
				    fcount++;
				}
				ff=ff->next;
				fline++;
			    }
			    if(fcount==test.count)
			    {
			    	cout<<"Not found!"<<endl;
				}
				cout<<"??";
				break;
			}
		}
    }
	return 0;
}




