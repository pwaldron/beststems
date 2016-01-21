all: binary OWL3 OWL2 OWL1

binary:
	g++ -O2 beststems.cpp -o beststems
	g++ -O2 layout.cpp -o layout
	
OWL3:
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

OWL2:
	./beststems OWL2-wordsonly.txt 6 > beststems6-OWL2.txt
	./beststems OWL2-wordsonly.txt 7 > beststems7-OWL2.txt
	sort beststems6-OWL2.txt -k4,4nr -k3,3nr -k1,1 | head -100 | cut -f1 > 6LetterStem.txt
	sort beststems7-OWL2.txt -k4,4nr -k3,3nr -k1,1 | head -100 | cut -f1 > 7LetterStem.txt
	./layout OWL2-wordsonly.txt
	mv SixLettersSingle.tex SixLettersSingle-OWL2.tex
	mv SixLettersDouble.tex SixLettersDouble-OWL2.tex
	mv SevenLettersSingle.tex SevenLettersSingle-OWL2.tex
	pdflatex SixLettersSingle-OWL2.tex
	pdflatex SixLettersDouble-OWL2.tex
	pdflatex SevenLettersSingle-OWL2.tex

OWL1:
	./beststems OWL1-wordsonly.txt 6 > beststems6-OWL1.txt
	./beststems OWL1-wordsonly.txt 7 > beststems7-OWL1.txt
	sort beststems6-OWL1.txt -k4,4nr -k3,3nr -k1,1 | head -100 | cut -f1 > 6LetterStem.txt
	sort beststems7-OWL1.txt -k4,4nr -k3,3nr -k1,1 | head -100 | cut -f1 > 7LetterStem.txt
	./layout OWL1-wordsonly.txt
	mv SixLettersSingle.tex SixLettersSingle-OWL1.tex
	mv SixLettersDouble.tex SixLettersDouble-OWL1.tex
	mv SevenLettersSingle.tex SevenLettersSingle-OWL1.tex
	pdflatex SixLettersSingle-OWL1.tex
	pdflatex SixLettersDouble-OWL1.tex
	pdflatex SevenLettersSingle-OWL1.tex
