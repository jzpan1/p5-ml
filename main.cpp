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
	void train(csvstream &train_data, bool debug) {
		map<string, string> row;
		if (debug) cout << "training data:\n";
		while (train_data >> row) {
			total_posts++;

			string label = row["tag"];
			set<string> post_words = unique_words(row["content"]);
			if (debug) {
				cout << "  label = " << label << ", content = " << row["content"] << "\n";
			}
			
			label_posts[label]++;
			for(const string &word : post_words) {
				word_posts[word]++;
				label_word_posts[make_pair(label, word)]++;
			}
		}
		vocabulary = word_posts.size();
		cout << "trained on " << total_posts << " examples\n";

		if (debug) {
			cout << "vocabulary size = " << vocabulary << "\n\n"
			     << "classes:\n";
			
			for (map<string, int>::iterator it = label_posts.begin(); it != label_posts.end();
					 it++) {
				cout << "  " << it->first << ", " << it->second << " examples, log-prior = " 
						 << log(static_cast<double>(it->second)/total_posts) << "\n";
			}
			
			cout << "classifier parameters:\n";
				for (auto it = label_word_posts.begin(); it != label_word_posts.end(); it++) {
				cout << "  " << it->first.first << ":" << it->first.second << ", count = " 
						 << it->second << ", log-likelihood = " 
						 << makePredic(it->first.second, it->first.first) << "\n";
			}
		}
	}

	void predict(csvstream &test_data, bool debug){
		int total_correct = 0; //correcly predicted
		int total = 0; //total data given

		cout << "test data:" << '\n';

		map<string, string> row;
		while (test_data >> row) {
			map<string, double> label_scores; //This hold the label and their long scores

			//loops through all the labels that needs log-probability score
			map<string, int>::iterator it = label_posts.begin();  

			string label = row["tag"];
			set<string> post_words = unique_words(row["content"]);

			while(it != label_posts.end()) {
				string predictLabel = it->first;
				//initial lnP(C)
				double logPredict = log(static_cast<double>(it->second)/total_posts); 
				for(string word : post_words) {
					double log_prob = makePredic(word, predictLabel);
					if (log_prob == -INFINITY) throw runtime_error("WAHFDSIAJIAHJVDI");
					logPredict += log_prob;

				}
				label_scores.insert(make_pair(predictLabel, logPredict));
				it++;
			}

			map<string, double>::iterator it1 = label_scores.begin();

			double max_value = it1->second;
			string nameLabel = it1->first;
			for(; it1 != label_scores.end(); it1++) { //compares the log-probability score  
  			 	if (it1 ->second > max_value) {
   			    	nameLabel = it1->first;
    		   		max_value = it1->second;
    			}
			}
			cout << "  correct = " << label << ", " << "predicted = " << nameLabel << ", " 
					 << "log-probability score = " << max_value << '\n';
			cout << "  content = " << row["content"] << "\n\n";
			if (label == nameLabel)
				total_correct++;
			total++;
		}
		cout << "performance: " << total_correct << " / " << total
				 << " posts predicted correctly\n";
	}
 private:


	double makePredic(const std::string& word, const std::string& label){
		std::pair<std::string, std::string> label_word_pair = std::make_pair(label, word);

		//word found within the given label
		if (label_word_posts.find(label_word_pair) != label_word_posts.end()) { 
			return log(static_cast<double>(label_word_posts[label_word_pair]) 
					/ label_posts[label]);
		} 
		//word found outside of the given label
		else if(word_posts.find(word) != word_posts.end()){
			return log(static_cast<double>(word_posts[word]) / total_posts);
		} 
		//the word does not exist
		else {
			return log(1.0 / (total_posts));
		}
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

	cout.precision(3);

	//error checking
  if (argc != 3) {
		if (argc == 4 && static_cast<string>(argv[3]) == "--debug");
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
	Classifier classifier;
	classifier.train(train_file, argc == 4);
	cout << "\n";
	classifier.predict(test_file, argc == 4);

	return 0;
}