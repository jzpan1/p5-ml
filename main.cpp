#include <iostream>
#include <fstream>
using namespace std;

void print_usage() {
	cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
}

int main(int argc, char* argv[]) {

	//error checking
  if (argc != 3) {
	if (argc == 4 && argv[3] == "--debug") ;
		else {
			print_usage();
			return 1;
		}
  }

	ifstream train_file(argv[1]);
	ifstream test_file(argv[2]);
	
	if (!train_file) {
		cout << "Error opening file: " << argv[1] << endl;
		return 1;
	}

	if (!test_file) {
		cout << "Error opening file: " << argv[2] << endl;
		return 1;
	}


}