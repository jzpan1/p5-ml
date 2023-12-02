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
		map<string, string> post;
		while(test_data >> post) {
            // Calculate the log-probability scores for each label
            std::map<std::string, double> label_scores;

            for (const auto& label_count : label_posts) {
                const std::string& label = label_count.first;
                double log_prior = log(static_cast<double>(label_count.second) / total_posts);
                double log_likelihood = 0.0;

                for (const auto& word : post) {
                    // Calculate log-likelihood based on whether the word is seen in training data
                    double word_likelihood = getWordLikelihood(word, label);
                    log_likelihood += word_likelihood;
                }

                label_scores[label] = log_prior + log_likelihood;
            }

            // Find the label with the highest log-probability score
            auto max_label = std::max_element(
                label_scores.begin(), label_scores.end(),
                [](const auto& lhs, const auto& rhs) {
                    return lhs.second < rhs.second;
                }
            );

            std::cout << "Predicted Label: " << max_label->first << std::endl;
        
        }
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