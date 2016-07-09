
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

struct CELL{
	int value;
	bool check;
};

bool file_open(string filename , vector <vector<CELL>> &data) {

	char delim = ',';

	ifstream ifs(filename);
	if (ifs.fail()) {
		cerr << "err : file open -> " << filename << endl;
		return false;
	}

	string _line;
	while (ifs, getline(ifs, _line)) {

		stringstream line(_line);
		string str;
		vector <CELL> line_data;

		while (line, getline(line, str, delim)) {

			istringstream iss(str);
			CELL buf;
			iss >> buf.value;
			buf.check = (buf.value == 0) ? false : true;
			line_data.push_back(buf);
		}

		data.push_back(line_data);
	}

	return true;
}

void find_r(int y, int x , vector <vector<CELL>> &data , int &count) {

	data[y][x].check = false;
	data[y][x].value = count;

	for (int i = y - 1; i <= y + 1; i++) {
		
		if (i < 0 || i >= (int)data.size()) continue;
		for (int j = x - 1; j <= x + 1; j++) {
			
			if (j < 0 || j >= (int)data[i].size()) continue;	
			if (data[i][j].check) find_r(i, j, data, ++count);
		}
	}
}

void find(vector<vector <CELL>> &data) {

	int count = 0;
	int state = 0;

	for (size_t i = 0 ; i < data.size() ; i++){
		for(size_t j = 0 ; j < data[i].size() ; j++){
		
			if (!data[i][j].check) continue;
			find_r(i , j , data, ++count);
			state += 10;
			count = state;
		}
	}
}

int main(int argc , char *argv[]) {

	vector< vector <CELL> > data;

	if(!file_open(argv[1], data))return -1;

	find(data);
	
	for (auto da : data) {
		for (auto d : da) {
			cout << d.value << "\t";
		}
		cout << endl;
	}	
}