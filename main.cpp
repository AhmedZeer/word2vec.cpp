#include <iostream>
#include "vectorizer.h"

#define WINDOW_SIZE 1

using::std::string;
using::std::vector;

// Init Embeds.
vector<vector<int>> init_embeds( int vocab_size, int dim, int seed );


// TODO : Batch Processing.

int main (int argc, char *argv[]) {
	
	string corpus = "This is a corpus. That contains a bunch of words !!!!!"
		"and stuff 2 be deleted.";

	auto vec = Vectorizer(corpus);
	for( auto elem : vec.vocab ){
		std::cout << elem.second << std::endl;
	}

	return 0;
}

