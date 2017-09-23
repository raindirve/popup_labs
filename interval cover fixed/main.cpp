
#include "lab1.h"




int main() {
	double begin, end;
	int n;
	//  cin >> begin >> end >> n;
	while (cin >> begin >> end >> n) {
		pair<double, double> interval = make_pair(begin, end);

		vector<pair<double, double>> intervals(n);

		for (int i = 0; i < n; ++i) {
			cin >> intervals[i].first >> intervals[i].second;
		}

		vector<int> indices = cover(interval, intervals.begin(), intervals.end());

		if (indices.empty()) {
			cout << "impossible" << endl;
		} else {
			cout << indices.size() << "\n";
			printiter(indices.begin(), indices.end());
		}
	}
}




















