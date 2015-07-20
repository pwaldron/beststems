all:
	g++ -O2 beststems.cpp -o beststems
	g++ -O2 layout.cpp -o layout
	./beststems OWL3-wordsonly.txt 6 > beststems6-OWL3.txt
	./beststems OWL3-wordsonly.txt 7 > beststems7-OWL3.txt
	sort beststems6-OWL3.txt -k4,4nr -k3,3nr -k1,1 | head -100 | cut -f1 > 6LetterStem.txt
	sort beststems7-OWL3.txt -k4,4nr -k3,3nr -k1,1 | head -100 | cut -f1 > 7LetterStem.txt
	./layout OWL3-wordsonly.txt
	mv SixLettersSingle.tex SixLettersSingle-OWL3.tex
	mv SixLettersDouble.tex SixLettersDouble-OWL3.tex
	mv SevenLettersSingle.tex SevenLettersSingle-OWL3.tex
	pdflatex SixLettersSingle-OWL3.tex
	pdflatex SixLettersDouble-OWL3.tex
	pdflatex SevenLettersSingle-OWL3.tex



