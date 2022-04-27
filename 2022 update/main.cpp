#include <iostream>
#include <bits/stdc++.h>
using namespace std;
vector<int> getnext(string &s){
    int len=s.length();
    vector<int> nex(len);
    nex[0]=-1;
    int j=0,k=-1;
    while (j<len-1){
        if (k==-1 || s[j]==s[k]) {
            j++; k++;
            if (s[j]==s[k]){
                nex[j]=nex[k];
            } else nex[j]=k;
        } else {
            k=nex[k];
        }
    }
    return nex;
}
int KMP(string s,string p){
    auto next=getnext(p);
    int i=0; int j=0;
    int lens=s.length();
    int lenp=p.length();
    while (i<lens && j<lenp){
        if (j==-1 || s[i]==p[j]){
            i++; j++;
        }
        else j=next[j];
    }
    if (j==p.length()) return (i-j);
    else return -1;
}
int main() {
    string s,p;
    getline(cin,s);
    getline(cin,p);
    cout<<KMP(s,p);
    return 0;
}
