#include <bits/stdc++.h>
#include <fstream>
#include <omp.h>
using namespace std;

vector<vector<long> > doc[2];
vector<string>hash[2];
vector<vector<long> >psbv[2];

template<typename T> T summation(vector<T>&vec)
{
	long i =  0;
	T sum = 0;
	long lim = vec.size();
	#pragma omp parallel for private(i) reduction(+:sum)
	for(i = 0;i<lim;i++)
	{
		sum+=vec[i];
	}
	return sum;
}
template<typename T> long bin_srch(vector<T>&vec,T val)
{
	long lo = 0;
	long hi = vec.size()-1;
	while(lo<=hi)
	{
		long mid = lo + ((hi-lo)/2);
		if(vec[mid] == val)return mid;
		if(vec[mid]<val) lo = mid+1;
		else
			hi = mid- 1;
	}
	return -1;
}
vector<string> toke(const string& str)
{  
   const string delimiters = 
   " .,<>;:?!{}[]()\"\n\t123456890/*-+@#$%^&|\\";
   vector<string> tokens;
   string::size_type lastPos = str.find_first_not_of(delimiters, 0);
   string::size_type pos = str.find_first_of(delimiters, lastPos);
   while (string::npos != pos || string::npos != lastPos)
	{  
    	tokens.push_back(str.substr(lastPos, pos - lastPos));
	    lastPos = str.find_first_not_of(delimiters, pos);
      	pos = str.find_first_of(delimiters, lastPos);
   	}
    return tokens;
}
string masti(const string& str)
{
	string g = "";
	for(long i = 0;i<str.size();i++)
	{
		unsigned char c = str[i];
		if(c<='Z' && c>='A')
		{
			c = c -'A' + 'a';
			g+=c; 
		}
		else if ( c>=32 && c<127)
		g+=c;
		else
		{
			/*
			switch(c)
			{
				case '\x80':g+='C';break;
				case '\x81':g+='u';break;
				case '\x82':g+='e';break;
				case '\x83':g+='a';break;
				case '\x84':g+='a';break;
				case '\x85':g+='a';break;
				case '\x86':g+='a';break;
				case '\x87':g+='c';break;
				case '\x88':g+='e';break;
				case '\x89':g+='e';break;
				case '\x8A':g+='e';break;
				case '\x8B':g+='i';break;
				case '\x8C':g+='i';break;
				case '\x8D':g+='i';break;
				case '\x8E':g+='A';break;
				case '\x8F':g+='A';break;

				case '\x90':g+='E';break;
				case '\x91':g+="ae";break;
				case '\x92':g+="AE";break;
				case '\x93':g+='o';break;
				case '\x94':g+='o';break;
				case '\x95':g+='o';break;
				case '\x96':g+='u';break;
				case '\x97':g+='u';break;
				case '\x98':g+='y';break;
				case '\x99':g+='O';break;
				case '\x9A':g+='U';break;
				
				case '\xA0':g+='a';break;
				case '\xA1':g+='i';break;
				case '\xA2':g+='o';break;
				case '\xA3':g+='u';break;
				case '\xA4':g+='n';break;
				case '\xA5':g+='N';break;
				
				case '\xB5':g+='A';break;
				case '\xB6':g+='A';break;
				case '\xB7':g+='A';break;

				case '\xC6':g+='a';break;
				case '\xC7':g+='A';break;
				
				case '\xD2':g+='E';break;
				case '\xD3':g+='E';break;
				case '\xD4':g+='E';break;
				case '\xD5':g+='i';break;
				case '\xD6':g+='I';break;
				case '\xD7':g+='I';break;
				case '\xD8':g+='I';break;

				case '\xE0':g+='O';break;
				case '\xE1':g+='B';break;
				case '\xE2':g+='O';break;
				case '\xE3':g+='O';break;
				case '\xE4':g+='o';break;
				case '\xE5':g+='O';break;

				case '\xE9':g+='U';break;
				case '\xEA':g+='U';break;
				case '\xEB':g+='U';break;
				case '\xEC':g+='y';break;
				case '\xED':g+='Y';break;
				
				default:g+=' ';break;
			}
			*/
			g+=' ';
		}
	}
	return g;
}
void prereader(string s11 = "english.txt",string s22 = "french.txt")
{
	string s1[2];
	s1[0] = s11;
	s1[1] = s22;
	ifstream f;
	string s,m;
	vector<string>v;
	vector<vector<string> >vec;
	vector<long>jec;
	long i,j,k;
	omp_set_num_threads(2);
	map<string,long>st;
	map<string,long>::iterator it;
	vector<string>fec;
	
	//for 2x file absorption speed up
	#pragma omp parallel for private(fec,it,f,s,v,i,j,k,m,st,vec,jec) //shared(doc,s1,hash)
	for(long i=0;i<2;i++)
	{
		//i = omp_get_thread_num();
		f.open(s1[i].c_str());	
		while(!f.eof())
		{
			getline(f,s,'\n');
			//vec.push_back(toke(s));
			fec = toke(masti(s));
			if(fec.size() == 0)continue;
			vec.push_back(fec);

			for(long j = 0;j<vec[vec.size()-1].size();j++)
			{
				st[vec[vec.size()-1][j]] = 0;
			}
		}
		f.close();
		j = 0;
		for(it = st.begin(); it != st.end();it++)
		{
			hash[i].push_back((*it).first);
			(*it).second = j;
			j++;
		}
		//cout<<st.size()<<"\t"<<hash[i].size()<<endl;
		for(j = 0;j<vec.size();j++)
		{
			jec.clear();
			for(k = 0;k<vec[j].size();k++)
			{	
				jec.push_back(st[vec[j][k]]);
			}
			doc[i].push_back(jec);
		}
		map<string,long>().swap(st);
		//st.clear();
		vector<vector<string> >().swap(vec);
		//vec.clear();
		//cout<<doc[i].size()<<endl;
		cout<<"Parsing file "<<i+1<<" completed"<<endl;
	}
}
void prewriter()
{
	string s[2],g[2];
	s[0] = "eng.txt";
	s[1] = "fre.txt";
	g[0] = "ken.txt";
	g[1] = "kfr.txt";
	long i,j,k;
	ofstream of;
	omp_set_num_threads(2);
	#pragma omp parallel for private(i,j,k,of)// shared(s,g,doc,hash)
	for(i=0;i<2;i++)
	{
		//i = omp_get_thread_num();
		of.open(s[i].c_str());
		for(j = 0;j<doc[i].size();j++)
		{
			for(k = 0;k<doc[i][j].size();k++)
			{
				of<<doc[i][j][k]<<" ";
			}
			of<<"-1\n";
		}
		of.close();
		of.open(g[i].c_str());
		for(j = 0;j<hash[i].size();j++)
		{
			of<<hash[i][j]<<"\n";
		}
		of.close();
	}
}
void postreader()
{
	ifstream f;
	string y;
	string s[2],g[2];
	s[0] = "eng.txt";
	s[1] = "fre.txt";
	g[0] = "ken.txt";
	g[1] = "kfr.txt";
	long i,t;
	vector<long>v;
	omp_set_num_threads(2);
	doc[0].clear();doc[1].clear();hash[0].clear();hash[1].clear();
	#pragma omp parallel for private(i,t,f,v,y)// shared(doc,hash)
	for(i=0;i<2;i++)
	{
		//i = omp_get_thread_num();
		f.open(s[i].c_str());
		while(!f.eof())
		{
			f>>t;
			if(t == -1)
			{
				doc[i].push_back(v);
				v.clear();
			}
			else
			v.push_back(t);
		}
		f.close();
		f.open(g[i].c_str());
		while(!f.eof())
		{
			f>>y;
			hash[i].push_back(y);
		}
		//cout<<i+1<<"\t"<<hash[i].size()<<"\t"<<doc[i].size()<<endl;
		cout<<"Parsing file "<<i+1<<" completed"<<endl;
		f.close();
	}
}
void conc()
{
	ofstream of;
	of.open("c.txt");
	for(long i = 0;i<5;i++)
	{
		of<<"english\t";
		for(long j = 0;j<doc[0][i].size();j++)
		of<<hash[0][doc[0][i][j]]<<" ";
		of<<endl;
		of<<"french\t";
		for(long j = 0;j<doc[1][i].size();j++)
		of<<hash[1][doc[1][i][j]]<<" ";
		of<<endl;
	}
}
vector<double> similarity(string s1,string s2)
{
	double ans = 0;
	double ans2 = 0;
	string s[2];
	s[0] = s1;
	s[1] = s2;
	map<string,double>M[2];
	map<string,double>::iterator it;
	double sum[2] = {0};
	int i,j,k;
	ifstream f;
	string g;
	#pragma omp parallel for private(it,i,g,f)
	for(int i=0;i<2;i++)
	{
		f.open(s[i].c_str());
		sum[i] = 0;
		while(!f.eof())
		{
			f>>g;
			M[i][g]+=1;
		}
		f.close();
		for(it = M[i].begin();it != M[i].end();it++)
		{
			sum[i]+=((*it).second)*((*it).second);
		}
		sum[i] = sqrt(sum[i]);
	}
	set<string>S;
	for(it = M[0].begin();it!=M[0].end();it++)
	{
		if(M[1].find((*it).first) != M[1].end())
		{
			ans+=(*it).second*M[1][(*it).first];
			ans2+=1;
		}
		S.insert((*it).first);
	}
	for(it = M[1].begin();it!=M[1].end();it++)
	{
		S.insert((*it).first);
	}
	double d = S.size();
	ans2 /= d;
	ans/=sum[0];
	ans/=sum[1];
	M[0].clear();
	M[1].clear();
	vector<double>veg;
	veg.push_back(ans);
	veg.push_back(ans2);
	return veg;
}
vector<double> cimilarity(char * s1,char * s2)
{
	double ans = 0;
	double ans2 = 0;
	char* s[2];
	s[0] = s1;
	s[1] = s2;
	map<string,double>M[2];
	map<string,double>::iterator it;
	double sum[2] = {0};
	int i,j,k;
	ifstream f;
	string g;
	#pragma omp parallel for private(it,i,g,f)
	for(int i=0;i<2;i++)
	{
		f.open(s[i]);
		sum[i] = 0;
		while(!f.eof())
		{
			f>>g;
			M[i][g]+=1;
		}
		f.close();
		for(it = M[i].begin();it != M[i].end();it++)
		{
			sum[i]+=((*it).second)*((*it).second);
		}
		sum[i] = sqrt(sum[i]);
	}
	set<string>S;
	for(it = M[0].begin();it!=M[0].end();it++)
	{
		if(M[1].find((*it).first) != M[1].end())
		{
			ans+=(*it).second*M[1][(*it).first];
			ans2+=1;
		}
		S.insert((*it).first);
	}
	for(it = M[1].begin();it!=M[1].end();it++)
	{
		S.insert((*it).first);
	}
	double d = S.size();
	ans2 /= d;
	ans/=sum[0];
	ans/=sum[1];
	M[0].clear();
	M[1].clear();
	vector<double>veg;
	veg.push_back(ans);
	veg.push_back(ans2);
	return veg;
}
void possiblity()
{
	omp_set_num_threads(2);
	string s[2];
	s[0] = "ten.txt";
	s[1] = "tfr.txt";
	long i,j,k,l,o;
	vector<set<long> >psb[2];
	set<long>::iterator it;
	ofstream of;
	#pragma omp parallel for private(i,j,k,l,o,of,it)
	for(i=0;i<2;i++)
	{
		psb[i].resize(hash[i].size());
		psbv[i].resize(hash[i].size());
		for(j=0;j<hash[i].size();j++)
		{
			psb[i][j].clear();
			psbv[i][j].clear();
		}
		o = i == 1?0:1;
		cout<<"yoyo  "<<i<<o<<endl;
		for(j=0;j<doc[i].size();j++)
		{
			for(k=0 ;k<doc[i][j].size();k++)
			{
				for(l = 0;l<doc[o][j].size();l++)
				{
					psb[i][doc[i][j][k]].insert(doc[o][j][l]);
				}
			}
		}
		cout<<i<<" okay 1"<<endl;
		of.open(s[i].c_str());
		for(j=0;j<psb[i].size();j++)
		{
			for(it = psb[i][j].begin();it!=psb[i][j].end();it++)
			{
				psbv[i][j].push_back(*it);
				of<<(*it)<<" ";
			}
			of<<"-1\n";
		}
		cout<<i<<" okay 2"<<endl;
		of.close();
	}
	omp_set_num_threads(8);
}
void readps()
{
	ifstream f;
	string s[2];
	s[0] = "ten.txt";
	s[1] = "tfr.txt";
	psbv[0].clear();
	psbv[1].clear();
	long i,j,k;
	vector<long>vec;
	#pragma omp parallel for private(i,j,k,f,vec)
	for(i = 0;i<2;i++)
	{
		psbv[i].clear();
		f.open(s[i].c_str());
		while(!f.eof())
		{
			f>>k;
			if(k == -1)
			{
				psbv[i].push_back(vec);
				vec.clear();
			}
			else
			vec.push_back(k);
		}
	} 
	f.close();
}
void rachit()
{
	//hash[0].size() = e;
	//hash[1].size() = f;
	//bash[0].size() = etotal;
	//bash[1].size() = ftotal;
	vector<double>bash[2];
	long i,j,k,l;
	double b;
	
	for(i = 0;i<hash[0].size();i++)
	bash[0].push_back(0);
	
	for(i = 0;i<hash[1].size();i++)
	bash[1].push_back(0);

	vector<vector<double> >t(hash[0].size());
	vector<vector<double> >c(hash[0].size());
	
	#pragma omp parallel for private(i)
	for(i = 0;i<psbv[0].size();i++)
	{
		for(j = 0;j<psbv[0][i].size();j++)
		{
			t[i].push_back(0.5);
		}
	}
	bool convergence = 1;
	int kappa  = 0;
	
	cout<<"okay 1"<<endl;
	double time = omp_get_wtime();
	while(convergence && kappa==0)
	{
		#pragma omp parallel for private(i)
		for(i = 0;i<c.size();i++)
		{
			c[i].clear();
			for(j = 0;j<psbv[0][i].size();j++)
			{
				c[i].push_back(0);
			}
		}
		
		#pragma omp parallel for private(i)
		for(i = 0;i<hash[1].size();i++)
		bash[1][i] = 0;
		cout<<"okay 2"<<endl;
		
		for(i = 0;i<doc[0].size();i++)
		{
			//#pragma omp parallel for private(j)
			for(j = 0;j<doc[0][i].size();j++)
			{
				bash[0][doc[0][i][j]] = 0;
				for(k = 0;k<doc[1][i].size();k++)
				{
					long bin = bin_srch(psbv[0][doc[0][i][j]],doc[1][i][k]);
					cout<<"2aa "<<bin<<" "<<t[doc[0][i][j]].size()<<endl;
					if(bin>= t[doc[0][i][j]].size())continue;
					bash[0][doc[0][i][j]]+=t[doc[0][i][j]][bin];
					cout<<"2ab "<<bin<<endl;					
				}
			}
			//cout<<"okay 2a"<<endl;	
			//#pragma omp parallel for private(j)
			for(j = 0;j<doc[0][i].size();j++)
			{
				for(k = 0;k<doc[1][i].size();k++)
				{
					long bin = bin_srch(psbv[0][doc[0][i][j]],doc[1][i][k]);
					cout<<"2ba "<<bin<<" "<<t[doc[0][i][j]].size()<<endl;
					//if(bin>= t[doc[0][i][j]].size())continue;
					b = t[doc[0][i][j]][bin]/bash[0][doc[0][i][j]];
					cout<<"2bb "<<bin<<" "<<c[doc[0][i][j]].size()<<endl;
					//if(bin>= c[doc[0][i][j]].size())continue;
					c[doc[0][i][j]][bin] += b;
					cout<<"2bc "<<bin<<endl;
					bash[1][doc[1][i][k]] += b;
					cout<<"2bd "<<bin<<endl;
				}
			}
			//cout<<"okay 2b"<<endl;
		}
		cout<<"okay 3"<<endl;
		for(i = 0;i<t.size();i++)
		{
			for(j = 0;j<t[i].size();j++)
			{
				t[i][j] = c[i][j]/bash[1][psbv[0][i][j]];
			}
		}
		kappa++;
	}
	time = omp_get_wtime() - time;
	cout<<"time "<<time<<endl;
}
void interface1()
{
	string s1,s2;
	cout<<"Enter the name of the file 1 to parse"<<endl;
	cin>>s1;
	cout<<"Enter the name of the file 2 to parse"<<endl;
	cin>>s2;
	prereader(s1,s2);
	prewriter();
	possiblity();
}
void interface2()
{
	postreader();
	readps();
}
int main()
{
	
	char c;
	cout<<"Are you running the code for the first time  y/n"<<endl;
	cin>>c;
	if(c == 'Y' || c == 'y')interface1();
	else interface2();
	//rachit();
	/*
	cout<<psbv[0][doc[0][0][0]].size()<<endl;
	cout<<doc[1][0].size()<<endl;
	for(long i=0;i<psbv[0][doc[0][0][0]].size();i++)
	{
		cout<<hash[1][psbv[0][doc[0][0][0]][i]]<<endl;
	}
	*/
	//for(long i = 0;i<10;i++)g +=g;
	//cout<<g<<endl<<sizeof(vector<string>)<<endl;
	string r;
	//cin>>r;
	return 0;
}
