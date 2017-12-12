
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <list>
#include <ctype.h>

typedef long long llong;
typedef unsigned long long ullong;


struct Node {
    Node(llong p = -1) : parent(p) {};

    llong id;
    llong parent;
    llong h = 0;
    llong animal = 0;
};

struct Tree {

    Tree(std::string s_, int N_) : N(N_), s(s_) {

        powers = std::vector<llong>(N);
        powers[0] = 1;
        for (size_t i = 1; i < N; ++i) {
            powers[i] = (powers[i - 1] * b) % M;
        }

        llong idx = 0;
        build(idx, 0);
    }

    llong hash(const llong & num) const {
        return (num * powers[N-num]) % M;
    }

    llong hash_combine(const llong & h, const llong & h2) const {
        return (h+h2) % M;
    }

    llong build(llong & idx, llong parent) {
        if (s[idx] == '(') {
            Node n(parent);
            nodes.push_back(n);
            llong me = nodes.size()-1;
            nodes[me].id = me;

            ++idx; // next char
            llong left_h = build(idx, me);

            // second branch
            ++idx; //skip comma
            llong right_h = build(idx, me);
            // next char should be )
            ++idx;
            nodes[me].h = hash_combine(nodes[me].h, left_h);
            nodes[me].h = hash_combine(nodes[me].h, right_h);
            return nodes[me].h;

        } else if (isdigit(s[idx])) {
            llong begin_idx = idx;
            llong len = 0;
            while (isdigit(s[idx])) {
                ++len;
                ++idx;
            }

            llong num = std::stoll(s.substr(begin_idx,len));

            Node n(parent);
            nodes.push_back(n);
            llong me = nodes.size() - 1;
            nodes[me].id = me;
            nodes[me].h = hash(num);
            nodes[me].animal = num;

            return nodes[me].h;

        } else if (s[idx] == ',') { // should never happen
            std::cout << "oh shit\n";
            return build(++idx,parent);
        } else {
            // should never happen
            std::cout << "wtf\n";
            return 0;
        }

    }

    llong N;
    std::string s;
    std::vector<Node> nodes;
    std::vector<llong> powers;

    const llong M = 999999999989;
    //const llong M = 2038104527;
    const llong b = 104729;
};





int main() {
    int N;

    std::cin >> N;

    std::string s1;
    std::string s2;

    std::getline(std::cin, s1);
    std::getline(std::cin, s1);
    std::getline(std::cin, s2);


    Tree t1(s1,N);
    std::unordered_set<llong> t1_hashes;    
    for (auto n : t1.nodes) {
        //std::cout << n.id << "\t" << n.parent << "\t" << n.animal << "\t" << n.h << "\n"; 
        t1_hashes.insert(n.h);
    }

    //std::cout << "\n";

    Tree t2(s2,N);

    llong ans=0;
    for (auto n : t2.nodes) {
        //std::cout << n.id << "\t" << n.parent << "\t" << n.animal << "\t" << n.h << "\n";
        if(t1_hashes.count(n.h)) ++ans;
    }

    std::cout << ans << "\n";
    //std::cout << s1 << "\n";
    //std::cout << s2 << "\n";












    return 0;
}









