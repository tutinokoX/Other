
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {

	if (argc != 2) {
		cerr << " err : input ... ( > " << argv[0] <<" [filename] )" << endl;
		return -1;
	}
	
	string filename = argv[1];
	char delim = '\t';

	ifstream ifs(filename);
	if (ifs.fail()) {
		cerr << "err : file open -> " << filename << endl;
		return -1;
	}

	
	vector <vector <int>> data;

	string _line;
	while (ifs, getline(ifs, _line)) {
		
		stringstream line(_line);
		string str;
		vector <int> line_data;

		while (line, getline(line, str, delim)) {

			istringstream iss(str);
			int num = 0;
			iss >> num;
			line_data.push_back(num);
		}

		data.push_back(line_data);
	}
/*
	// Ši”[Šm”F
	for (auto da : data) {
		for (auto d : da) {
			cout << d << "\t";
		}
		cout << endl;
	}
*/
	cout << endl;
	vector <int> count;
	for (auto da : data) {
		for (auto d : da) {
			
			while (1) {
				if ((int)count.size() > d) break;
				count.push_back(0);
			}
			count[d] ++;
		}
	}

	int min_count = 0;
	for (vector<int>::iterator itr = count.begin(); itr != count.end(); itr++) {
		cout << "  " << distance(count.begin(), itr) << "\t: ";
		for (int i = 0; i < *itr; i++) cout << "*";
		if (count[min_count] > *itr) min_count = distance(count.begin(), itr);
		cout << endl;
	}

	cout << endl << "   Threshold = " << min_count << " (" << count[min_count] << ") " << endl;
}