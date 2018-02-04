#include <unordered_set>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>


/*
* @Author: Nicholas Hays
* @Date: 2018-01-27 15:27:11
* @Last Modified by:   Nicholas Hays
* @Last Modified time: 2018-01-27 15:27:11
*/
using namespace std;

//uint8_t underlying data type is unsigned char
static uint8_t NUM_COINS;

bool ins_prefix(map<uint8_t, uint8_t> &prefix, map<uint8_t, unordered_set<string>> & roots, uint8_t & root) {
	bool ins = false;
	static string prefix_str;
	prefix_str.clear();
	for (auto key_val : prefix) {
		if (key_val.second) {
			prefix_str.push_back((uint8_t)key_val.second);
			prefix_str.push_back((uint8_t)key_val.first);
		}
	}
	if (!(roots[root].count(prefix_str))) {
		roots[root].insert(prefix_str);
		ins = true;
	}
	return ins;
}

void getComb(uint8_t root, vector<uint8_t> & coins, map<uint8_t, uint8_t> & prefix, map<uint8_t, unordered_set<string>> & roots, uint8_t i) {
	int j = i;
	i = 0;
	while (i < NUM_COINS && root - coins[i] >= 0) {
		uint8_t coin = coins[i];
		prefix[coin]++;
		uint8_t child = root - coin;
		bool insert = ins_prefix(prefix, roots, child);
		if (child == 0) {
			prefix[coin]--;
			break;
		} else if (!insert) {
			--(prefix[coin]);
		} else {
			getComb(child, coins, prefix, roots, i);
		}
		i++;
	}
	prefix[coins[j]]--;
}

void getWays(uint8_t n, vector<uint8_t> coins ) {

	sort(coins.begin(), coins.end()); //asc order
	map<uint8_t, uint8_t> prefix;
	map<uint8_t, unordered_set<string>> roots;
	getComb(n, coins, prefix,roots, 0);
	cout << roots[0].size();
}

/*
entry point for program.
*/
int main() {
	int t = 0;
	cin >> t;
	uint8_t n = t;
	cin >> t;
	NUM_COINS = t;
	vector<uint8_t> coins(NUM_COINS);
	for (int i = 0; i < NUM_COINS; i++) {
		cin >> t;
		coins[i] = t;
	}
	getWays(n, coins);
}