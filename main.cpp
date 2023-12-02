#include <iostream>
#include <fstream>
#include <map>
using namespace std;

class Classifier {
 public:
	Classifier() {}
	void train(ifstream train_data);
	void predict(ifstream test_data);
 private:
	int total_posts;
	int vocabulary;
	map<string, int> word_posts;
	map<string, int> label_posts;
	map<pair<string, string>, int> label_word_posts;
};

void print_usage() {
	cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
}

set<string> unique_words(const string &str) {
  istringstream source(str);
  set<string> words;
  string word;
  while (source >> word) {
    words.insert(word);
  }
  return words;
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