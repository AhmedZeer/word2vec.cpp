#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector>

#define WINDOW_SIZE 1

using::std::string;
using::std::vector;
using::std::map;
using::std::set;

const vector<string> stopwords = {
        "i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours",
        "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself",
        "it", "its", "itself", "they", "them", "their", "theirs", "themselves", "what", "which",
        "who", "whom", "this", "that", "these", "those", "am", "is", "are", "was", "were", "be",
        "been", "being", "have", "has", "had", "having", "do", "does", "did", "doing", "a", "an",
        "the", "and", "but", "if", "or", "because", "as", "until", "while", "of", "at", "by", "for",
        "with", "about", "against", "between", "into", "through", "during", "before", "after",
        "above", "below", "to", "from", "up", "down", "in", "out", "on", "off", "over", "under",
        "again", "further", "then", "once", "here", "there", "when", "where", "why", "how", "all",
        "any", "both", "each", "few", "more", "most", "other", "some", "such", "no", "nor", "not",
        "only", "own", "same", "so", "than", "too", "very", "s", "t", "can", "will", "just", "don",
        "should", "now"
    };


// Remove Puncts, Decaptialize.
void normalize_str( string& str );
void apply_char( string& str, void (*foo)( char &c) );
bool is_stopword( const string& str );

// Create The Vector.
map<int, string> create_vocab( set<string> word_set );
set<string> word_set( const string& str );

// Init Embeds.
vector<vector<int>> init_embeds( int vocab_size, int dim, int seed );


// Char Manipu. Funcs.
char to_lowercase( char& c ){
	return (tolower(c));
}

void to_lowercase_inplace( char& c ){
	c = to_lowercase(c);
}


// Generate ( Context, Center ) words.
map<int, vector<int>> gen_train( const map<int, string>& vocab, const string& corpus );


// TODO : Batch Processing.

int main (int argc, char *argv[]) {
	
	string corpus = "This is a corpus. That contains a bunch of words !!!!!"
		"and stuff 2 be deleted.";

	// string corpus = "AaAAAA.";

	normalize_str(corpus);
	apply_char(corpus, to_lowercase_inplace );

	// std::cout << corpus << std::endl;

	auto vocab = create_vocab( word_set(corpus) );

	map<int, vector<int>> train_ = gen_train(vocab, corpus);

	std::cout << "Corpus: " << corpus << std::endl;

	for( auto elem : train_ ){

		std::cout << "Center: " << vocab[elem.first] << std::endl;
		std::cout << "Context: ";

		for( auto context : elem.second ){
			std::cout << vocab[context] << ", ";
		}

		std::cout << std::endl << std::endl;
	}

	return 0;
}

void apply_char( string& str, void (*foo)(char &c) ){

	string::iterator b = str.begin();
	while( b != str.end() ){
		foo(*b);
		b++;
	}
}


// Remove Puncts, Decaptialize.
void normalize_str( string& str ){

	str.erase(std::remove_if( str.begin(), str.end(), ispunct ), str.end());
}

vector<string> tokenizer( const string& str ){

	vector<string> ret;
	string::const_iterator b = str.begin();
	string::const_iterator e = str.begin();

	while( b != str.end() ){

		while( isalnum(*e) ){
			++e;
		}

		while( !isalnum(*b) ){
			++b;
		}

		if( *e == ' ' || e == str.end() ){

			string temp = string(b,e);

			if( !is_stopword(temp) ){
				// std::cout << temp << std::endl;
				ret.push_back(temp);
			}
			b = e++;
		}
	}

	return ret;

}

set<string> word_set( const string& str ){

	set<string> ret;

	string::const_iterator b = str.begin();
	string::const_iterator e = str.begin();

	vector<string> splitted_str = tokenizer(str);

	for( auto elem : splitted_str ){
		ret.insert(elem);
	}

	return ret;
}

bool is_stopword( const string& str ){

	auto exists = std::find(stopwords.begin(), stopwords.end(), str);

	if( exists == stopwords.end() ){
		return false;
	}

	return true;
}

map<int, string> create_vocab( set<string> word_set ){

	map<int, string> ret;
	int idx = 0;

	for( auto elm : word_set ){
		ret[idx] = elm;
		idx++;
	}

	return ret;
}

map<int, vector<int>> gen_train( const map<int, string>& vocab, const string& corpus ){

	map<int, vector<int>> ret;
	map<string,int> stoi_vocab;

	for( auto pair : vocab ){
		stoi_vocab[pair.second] = pair.first;
	}

	vector<string> splitted_corpus = tokenizer(corpus);
	for( int i = WINDOW_SIZE; i < splitted_corpus.size() - WINDOW_SIZE; i++ ){

		string center_w = splitted_corpus[i];
		int center_ = stoi_vocab[center_w];
		vector<int> context_vec;

		for( int j = WINDOW_SIZE; j != 0; j-- ){

			string context1_ = splitted_corpus[ i - j ];
			string context2_ = splitted_corpus[ i + j ];
			context_vec.push_back( stoi_vocab[context1_] );
			context_vec.push_back( stoi_vocab[context2_] );
		}

		ret[center_] = context_vec;
	}

	return ret;
}
