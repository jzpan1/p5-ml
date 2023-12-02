#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include "csvstream.hpp"
#include <valarray>

using namespace std;

class Classifier {
 public:
	Classifier() : total_posts(0), vocabulary(0) {}

	//REQUIRES: train_data is valid dataset
	//MODIFIES: this Classifier
	// EFFECTS: Updates classifier's internal maps with
	// 					new data
	void train(csvstream &train_data) {
		map<string, string> row;
		while (train_data >> row) {
			total_posts++;

			string label = row["tag"];
			set<string> post_words = unique_words(row["content"]);
			
			label_posts[label]++;
			for(const string &word : post_words) {
				word_posts[word]++;
				label_word_posts[make_pair(label, word)];
			}
		}
		vocabulary = word_posts.size();
	}
	void predict(const csvstream &test_data){

	}
 private:
	set<string> unique_words(const string &str) {
		istringstream source(str);
		set<string> words;
		string word;
		while (source >> word) {
			words.insert(word);
		}
		return words;
	}
	
	int total_posts;
	int vocabulary;
	map<string, int> word_posts;
	map<string, int> label_posts;
	map<pair<string, string>, int> label_word_posts;
};

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

	csvstream train_file(argv[1]);
	csvstream test_file(argv[2]);
	
	if (!train_file) {
		cout << "Error opening file: " << argv[1] << endl;
		return 1;
	}

	if (!test_file) {
		cout << "Error opening file: " << argv[2] << endl;
		return 1;
	}


}