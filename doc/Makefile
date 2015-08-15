latex:
	pdflatex skil.tex
	pdflatex skil.tex

pdf: latex
	pdftk skil.pdf cat 2-end output 1.pdf
	pdftk skil-caratula.pdf 1.pdf cat output skil.pdf

clean:
	rm -rf 1.pdf skil.aux skil.out caratula.aux skil.log
