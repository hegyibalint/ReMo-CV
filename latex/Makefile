PROJECTNAME=ReMo

.PHONY: all clean osx

all: clean
	mkdir -p out
	latexmk -xelatex -outdir=out -jobname=$(PROJECTNAME) main.tex

clean:
	rm -rf out/

osx: clean all
	open -a Skim out/$(PROJECTNAME).pdf
