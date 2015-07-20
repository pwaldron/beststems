#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <set>

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <Dictionary file>" << std::endl;
	}

	std::ifstream dictfile(argv[1]);
	std::ifstream slsstemfile("6LetterStem.txt");
	std::ifstream vlsstemfile("7LetterStem.txt");

	std::ofstream sls("SixLettersSingle.tex");
	std::ofstream sld("SixLettersDouble.tex");
	std::ofstream vls("SevenLettersSingle.tex");


	std::map<std::string, std::set<std::string> > dict;

	// Read the dictionary, put it in a map indexed by alphagram
	while (dictfile.good())	{
		std::string word, alphagram;

		dictfile >> word;

		alphagram = word;
		std::sort(alphagram.begin(), alphagram.end());
		
		dict[alphagram].insert(word);
	}


	dictfile.close();

	sls << "\\documentclass[twocolumn]{article}" << std::endl;
	sls << "\\usepackage{supertabular}" << std::endl;
	sls << "\\begin{document}" << std::endl;
	sls << std::endl;

	sld << "\\documentclass[twocolumn]{article}" << std::endl;
	sld << "\\usepackage{supertabular}" << std::endl;
	sld << "\\begin{document}" << std::endl;
	sld << std::endl;

	vls << "\\documentclass[twocolumn]{article}" << std::endl;
	vls << "\\usepackage{supertabular}" << std::endl;
	vls << "\\begin{document}" << std::endl;
	vls << std::endl;

	while (slsstemfile.good())	{
		std::string stem, alphagram;

		slsstemfile >> stem;

		if (stem == "")
			continue;

		sls << "\\section{" << stem << "}" << std::endl;
		sls << std::endl;
		sls << "\\begin{supertabular}{rl}" << std::endl;

		sld << "\\section{" << stem << "}" << std::endl;
		sld << std::endl;
		sld << "\\begin{supertabular}{rl}" << std::endl;

		for (char ch1 = 'A'; ch1 <= 'Z'; ch1++) {
			alphagram = stem + ch1;
			std::sort(alphagram.begin(), alphagram.end());

			if (dict.find(alphagram) != dict.end()) {
				for (std::set<std::string>::iterator It = dict[alphagram].begin(); It != dict[alphagram].end(); ++It) {
					sls << (It == dict[alphagram].begin() ? ch1 : ' ') << "\t&\t" << *It << " \\\\" << std::endl;									
				}
			}
	
			for (char ch2 = ch1; ch2 <= 'Z'; ch2++) {
				alphagram = stem + ch1 + ch2;
				std::sort(alphagram.begin(), alphagram.end());

				if (dict.find(alphagram) != dict.end()) {
					for (std::set<std::string>::iterator It = dict[alphagram].begin(); It != dict[alphagram].end(); ++It) {
						sld << (It == dict[alphagram].begin() ? ch1 : ' ') << (It == dict[alphagram].begin() ? ch2 : ' ') << "\t&\t" << *It << " \\\\" << std::endl;									
					}
				}
			}

		}

		sls << "\\end{supertabular}" << std::endl;
		sls << "\\newpage" << std::endl;

		sld << "\\end{supertabular}" << std::endl;
		sld << "\\newpage" << std::endl;

	}

	sls << "\\end{document}" << std::endl;
	sls << std::endl;

	sld << "\\end{document}" << std::endl;
	sld << std::endl;




	while (vlsstemfile.good())	{
		std::string stem, alphagram;

		vlsstemfile >> stem;

		if (stem == "")
			continue;

		vls << "\\section{" << stem << "}" << std::endl;
		vls << std::endl;
		vls << "\\begin{supertabular}{rl}" << std::endl;

		for (char ch1 = 'A'; ch1 <= 'Z'; ch1++) {
			alphagram = stem + ch1;
			std::sort(alphagram.begin(), alphagram.end());

			if (dict.find(alphagram) != dict.end()) {
				for (std::set<std::string>::iterator It = dict[alphagram].begin(); It != dict[alphagram].end(); ++It) {
					vls << (It == dict[alphagram].begin() ? ch1 : ' ') << "\t&\t" << *It << " \\\\" << std::endl;									
				}
			}
		}

		vls << "\\end{supertabular}" << std::endl;
		vls << "\\newpage" << std::endl;
	}

	vls << "\\end{document}" << std::endl;
	vls << std::endl;

	sls.close();
	sld.close();
	vls.close();

	return 0;
}
