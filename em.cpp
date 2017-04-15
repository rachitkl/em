#include <bits/stdc++.h>
#include <fstream>
using namespace std;

int main ()
{
	ifstream if1,if2;
	if1.open("english.txt");
	if2.open("french.txt");	
	
	vector<vector<int> > vec[2];
	vector<string>hash[2];
	
	vector<vector<string> >rough1,rough2;
	
	while(!if1.eof())
	{
		vector<string>v;
		string g;
		getline(if1,g,'\n');
		//tokenize
		int b = 0;
		g = g + " ";
		for (int i = 0; i< g.length(); i++)
		{
        		if (g[i] == ' ' && g.compare(" ") != 0)
        		{
                		string st = g.substr(b, i);
                		//cout << st << endl;
                		v.push_back(st);
                		b = i + 1;
        		}
        		//if (b >= g.length())
        		//break;
		}
		for (int i = 0; i < v.size(); i ++)
		{
		cout << v[i] << "*****" << endl;
		}

		rough1.push_back(v);
	}
	
	while(!if2.eof())
	{
		vector<string>v;
		string g;
		getline(if2,g,'\n');
		//tokenize
		int b = 0;
		g = g + " ";
		for (int i = 0; i< g.length(); i++)
		{
        		if (g[i] == ' '&& g.compare(" ") != 0)
        		{
                		string st = g.substr(b, i);
                		//cout << st << endl;
                		v.push_back(st);
                		b = i + 1;
        		}
		}
		rough2.push_back(v);
	}
	if1.close();
	if2.close();
	map<string,int>m1,m2;
	for(int i = 0;i<rough1.size();i++)
	{
		for(int j = 0;j<rough1[i].size();j++)
		{
			m1[rough1[i][j]] = 0;
		}
	}

	for(int i = 0;i<rough2.size();i++)
	{
		for(int j = 0;j<rough2[i].size();j++)
		{
			m2[rough2[i][j]] = 0;
		}
	}
	
	int u = 0;
	for(map<string,int>::iterator it = m1.begin();it!=m1.end();it++)
	{
		(*it).second = u;
		hash[0].push_back((*it).first);
		u++;
	}
	u = 0;
	for(map<string,int>::iterator it = m2.begin();it!=m2.end();it++)
	{
		(*it).second = u;
		hash[1].push_back((*it).first);
		u++;
	}
	
	for(int i = 0;i<rough1.size();i++)
	{
		vector<int>chut;
		for(int j = 0;j<rough1[i].size();j++)
		{
			chut.push_back(m1[rough1[i][j]]);
		}
		vec[0].push_back(chut);
	}
	
	for(int i = 0;i<rough2.size();i++)
	{
		vector<int>chut;
		for(int j = 0;j<rough2[i].size();j++)
		{
			chut.push_back(m2[rough2[i][j]]);
		}
		vec[1].push_back(chut);
	}

	rough1.clear();
	rough2.clear();
	m1.clear();
	m2.clear();
	cout<<"mard ka bachha"<<endl;
////////////////////////////////////////////////////////////////////
//all okay
	
	string en = "The dog barks";
	string fr = "Le chien aboge"; 
	int e,f;
	e = 6;
	f = 6;
	//assume we have total 'e' words in english and 'f' in french
	double t[e][f];//initialize to uniform value 1/e
	double count[e][f];//sum of probabilities across the sentences in sentence pairs
	double ftotal[f];
	double etotal[e];
	bool convergence = 1;
	
	//vector<vector<int>> evec; = vec[0]
	//vector<vector<int>> fvec; = vec[1]
	int kappa = 0;
	
	for (int j = 0; j <f; j++/* for all french words*/)
		{
			for (int i = 0; i <e; i++/* for all english words*/)
			{
				t[i][j] = 0.25;
			}
		}
		
		//cout<<"dard ka bachha"<<endl;
	while (convergence)
	{
		// initialize count and total to zero
		for (int j = 0; j <f; j++)
		{
			ftotal[j] = 0;
		}

		for (int i = 0; i <e; i++)
		{	
			for (int j = 0; j <f; j++)
			{
				count[i][j] = 0;
			}
		}

		//pre-req sentence pair in some form
		// m = no of wordse in the sentence pair english
		// n = no of wordse in the sentence pair french
		//cout << vec[0].size() <<" " << vec[1].size() << endl;
		//cout << vec[0][1][2] << endl;
		
		
		for (int senp = 0; senp < vec[0].size(); senp++ )
		{
			for (int engword = 0; engword < vec[0][senp].size(); engword++/* words in english that sentence pair sentence*/)//m times
			{
				etotal[vec[0][senp][engword]] = 0;//for the specific word from vocabulary for the sentence
				for (int frword = 0; frword < vec[1][senp].size() ; frword ++/* words in french sentence*/)//n times 
				{
					etotal[vec[0][senp][engword]] += t[vec[0][senp][engword]][vec[1][senp][frword]];
				}
			}


			for (int engword = 0; engword < vec[0][senp].size(); engword++/* words in english that sentence pair sentence*/)//m times
			{
				for (int frword = 0; frword < vec[1][senp].size() ; frword ++/* words in french sentence*/)//n times
				{
					count[vec[0][senp][engword]][vec[1][senp][frword]]+= (t[vec[0][senp][engword]][vec[1][senp][frword]])/etotal[vec[0][senp][engword]];
					ftotal[vec[1][senp][frword]]+= (t[vec[0][senp][engword]][vec[1][senp][frword]])/etotal[vec[0][senp][engword]];
				}
			}
		//******* end of sentence pair loop*******
		 }
		 for (int j = 0; j <f; j++/* for all french words*/)
		{
			for (int i = 0; i <e; i++/* for all english words*/)
			{
				cout << count[i][j] << endl;; 
			}
		}
		cout << "space" << endl;
		convergence = 0;
		for (int j = 0; j <f; j++/* for all french words*/)
		{
			for (int i = 0; i <e; i++/* for all english words*/)
			{
				t[i][j] = (count[i][j]) / ftotal[j];
				if(t[i][j] > 0.1 && t[i][j] < 0.9)
				convergence = 1;
			}
		}
		// end of while
		//convergence = 0;
		kappa++;
	}
	cout<<kappa<<endl;
		for (int j = 0; j <f; j++/* for all french words*/)
		{
			for (int i = 0; i <e; i++/* for all english words*/)
			{
				cout << hash[1][j]<<"\t"<<hash[0][i]<<"\t"<<t[i][j] <<  endl;
				
			}
		}
	//*************
}

