#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define fi first
#define se second
#define mp make_pair

char color[200][200]={'\0'};
map<string,ll>M;
vector< pair<ll,ll> > v[100010];
ll N;
string station[200];
map <string,string> tourm;

class comparedis
{
	public:bool operator()(pair<ll,ll> &p,pair<ll,ll> &q)
		{
			return (p.se > q.se); // For min heap use > sign
		}
};

void gettour()
{
	ifstream fin;
	string s1,s2;
	fin.open("tourplace.txt",ios::in);
	if(!fin)
		cout<<"Not Found\n";
	fin.seekg(0);
	fin.clear();
	while(!fin.eof())
	{
		getline(fin,s1);
		getline(fin,s2);
		tourm[s1]=s2;   
	}
	fin.close();
}

void consmap()
{
	ifstream fin;
	string s;
	fin.open("list.txt",ios::in);
	ll l=0;
	fin.seekg(0);
	fin.clear();
	while(!fin.eof())
	{
		getline(fin,s);
		M[s]=l;
		station[l]=s;
		l++;
	}
	N=l-1;
	fin.close();
}

void disp(ll src,ll dest,ll par[])
{
	ll i,x,y,cn=0,ci=0;
	stack<ll> st;
	st.push(dest);
	i=dest;
	while(par[i]!=-1)
	{
		i=par[i];
		st.push(i);				
	}
	char col='\0';
	while(!st.empty())
	{
		x=st.top();
		st.pop();
		if(!st.empty())
			y=st.top();
		cout<<station[x]<<" ";
		cn++;
		if(col=='\0'){
			col=color[x][y];
            string cl;
            if(col=='b'){
                cl="blue";
            }
            else if(col=='g'){
                cl="green";
            }
            else if(col=='o'){
                cl="orange";
            }
            else if(col=='r'){
                cl="red";
            }
            else if(col=='v'){
                cl="violet";
            }
            else{
                cl="yellow";
            }
            cout<<"\t\tTake "<<cl<<" line";
        }
		else if(col!='\0'&&col!=color[x][y])
		{
			char c=color[x][y];
			ci++;
			if(c=='b')
				cout<<"\t\tChange to blue line";
			else if(c=='y')
				cout<<"\t\tChange to yellow line";
			else if(c=='o')
				cout<<"\t\tChange to orange line";
			else if(c=='g')
				cout<<"\t\tChange to green line";
			else if(c=='r')
				cout<<"\t\tChange to red line";
			else if(c=='v')
				cout<<"\t\tChange to Violet line";
			col=c;
		}		
		cout<<endl;
	}
	cout<<endl<<"No of stations ="<<cn<<endl;
    if(ci<1){
        ci=1;
    }
	cout<<"No of interchange stations ="<<ci-1<<endl;
	cout<<endl;
}

//To find shortest path
void bfs(ll src,ll dest) 
{
	bool vis[100010]={false};
	ll par[100010];
	for(ll i=0;i<N;i++)
		par[i]=-1;
	queue<ll> q;
	q.push(src);
	vis[src]=true;
	while(!q.empty())
	{
		ll x=q.front();
		q.pop();
		ll vsz=v[x].size();
		for(ll i=0;i<vsz;i++)
		{
			ll y=v[x][i].fi;
			if(!vis[y])
			{
				par[y]=x;
				vis[y]=true;
				q.push(y);
			}
		}
		v[x].clear();
	}
	disp(src,dest,par);
}

//To find most economical path
void dijkstra(ll src,ll dest)
{
	// bool vis[100010]={false};
	ll dist[100010], par[100010];
	for(ll i=0;i<N;i++)
	{
		dist[i]=LLONG_MAX;
		par[i]=-1;
	}
	priority_queue< pair<ll,ll>,vector< pair<ll,ll> >,comparedis > pq;
	pq.push(mp(src,0));
	dist[src]=0;
	par[src]=-1;
	// vis[src]=true;
	while(!pq.empty())
	{
		pair<ll,ll> k=pq.top();
		pq.pop();
		ll x=k.fi;
		ll vsz=v[x].size();
		for(ll i=0;i<vsz;i++)
		{
			ll y=v[x][i].fi;
			ll w=v[x][i].se;
			if(dist[x]+w < dist[y])
			{
				par[y]=x;
				dist[y]=dist[x]+w;
                pq.push(mp(y,dist[y]));
			}
			// if(!vis[y])
			// {
			// 	vis[y]=true;
			// 	pq.push(mp(y,dist[y]));
			// }
		}
		v[x].clear();
	}
	disp(src,dest,par);
}

void addedge(const char fname[],ll w)
{
	ifstream fin;
	string s;
	ll x,y;
	fin.open(fname,ios::in);
	fin.seekg(0);
	getline(fin,s);
	x=M[s];
	char c=fname[0];
	fin.clear();
	while(!fin.eof())
	{
		getline(fin,s);
		y=M[s];
		v[x].pb(mp(y,w));
		v[y].pb(mp(x,w));
		color[x][y]=c;
		color[y][x]=c;
		x=y;
	}
	fin.close();
}

void consgraph()
{
	// string s;
	addedge("blueline.txt",0);
	addedge("yellowline.txt",0);
	addedge("redline.txt",0);
	addedge("greenline.txt",0);
	addedge("violetline.txt",0);
	addedge("bluext.txt",0);
	addedge("orangeline.txt",0);
}

int main()
{
	string source,destination;
	ll i,x,y,w,src,dest,k,choice,dec;
	char ch;
	gettour();
	consmap();
	do
	{
		cout<<endl;
		cout<<"1.To Route between two stations\n";
		cout<<"2.To check nearest metro station to a tourist place\n";
        cout<<endl;
		cin>>dec;
        cout<<endl;
		switch(dec)
		{
			case 1:
					do
					{
						consgraph();
						cout<<"Enter source station\n";
						getline(cin,source);
						getline(cin,source);
						//cout<<source<<endl;
                        cout<<endl;
						cout<<"Enter destination station\n";
						getline(cin,destination);
                        cout<<endl;
						//cout<<destination<<endl;
						src=M[source];
						dest=M[destination];
						cout<<"1.For most economic path\n";
						cout<<"2.For shortest path";
                        cout<<endl<<endl;
						cin>>choice;
                        cout<<endl;
						switch(choice)
						{
							case 1:dijkstra(src,dest);
									break;
							case 2:bfs(src,dest);
									break;
						}
						cout<<"Do you wish to check for any other station\n";
						cin>>ch;
                        cout<<endl;
					}while(ch=='Y'||ch=='y');	
					break;	
			case 2:
					do
					{
						string place;
						cout<<"Enter a place\n";
						getline(cin,place);
						getline(cin,place);
						string st;
						st=tourm[place];
						cout<<endl<<"Nearest Metro Station is "<<st<<endl<<endl;
						cout<<"Do you wish to check for any other place\n";
						cin>>ch;
                        cout<<endl;
					}while(ch=='Y'||ch=='y');
					break;
		}
		cout<<"Do you wish to go back to main menu\n";
		cin>>ch;
        cout<<endl;
	}while(ch=='Y'||ch=='y');
	return 0;
}

