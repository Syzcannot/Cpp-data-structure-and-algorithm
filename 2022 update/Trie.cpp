#include<bits/stdc++.h>
using namespace std;
class Trie {
private:
    vector<Trie*> children;
    bool isEnd;
    Trie* searchPrefix(string prefix) {
        Trie* node = this;
        for (char ch : prefix) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                return nullptr;
            }
            node = node->children[ch];
        }
        return node;
    }
public:
    Trie() : children(26), isEnd(false) {}
    void insert(string word) {
        Trie* node = this;
        for (char ch : word) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                node->children[ch] = new Trie();
            }
            node = node->children[ch];
        }
        node->isEnd = true;
    }
    bool search(string word) {
        Trie* node = this->searchPrefix(word);
        return node != nullptr && node->isEnd==true;
    }
    bool startsWith(string prefix) {
        Trie* node = this->searchPrefix(prefix);
        return node != nullptr;
    }
    string search_two_word_prefix(string s1,string s2){
        Trie* node1= this;
        Trie* node2= this;
        string ans="";
        int p=0;
        while (node1==node2&&p<s1.length()&&p<s2.length()){
            node1 = node1->children[s1[p]-'a'];
            node2 = node2->children[s2[p]-'a'];
            ans+=s1[p];
            p++;
        }
        return ans;
    }
};

int main(){
    Trie a;
    a.insert("apple");
    a.insert("app");
    cout<<a.search("apple")<<endl;
    cout<<a.search_two_word_prefix("apple","app");
    return 0;
}