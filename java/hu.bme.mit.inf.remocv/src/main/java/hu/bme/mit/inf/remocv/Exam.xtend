package hu.bme.mit.inf.remocv

import java.io.PrintWriter

class Exam {

	def static generateExamPage(int code, String examName, String barcode, String kind) '''		
		\noindent
		\begin{center}
		    \begin{tabu} to \textwidth {r X l@{\hskip 5mm} l }
		    	\multicolumn{2}{c}{\LARGE\bfseries Rendszermodellezés -- «examName»} & Feladat & \multicolumn{1}{c}{Pontszám} \\[1mm]
		    	\toprule
		        \hspace{1cm}\textbf{Kód:}    & «code» &        &\bigstrut                        \\
		    	\hspace{1cm}\textbf{Név:}    & & Beugró & \hspace{1cm}\textbf{/10}\bigstrut \\
		    	\hspace{1cm}\textbf{Neptun:} & &        &\bigstrut                        \\
		    	\bottomrule
		    \end{tabu}
		\end{center}
		
		\begin{center}
			\textbf{A DOLGOZATOT TOLLAL ÍRJA!}\\[4mm]
		    \newcolumntype{?}{!{\vrule width 2pt}}
		    \rowcolors{1}{white}{gray!20}
		    \begin{tabu} to \textwidth { ? c | X[c] X[c] | X[c] X[c] | X[c] X[c] | X[c] X[c] ? }
		        \specialrule{2pt}{0mm}{0mm}
		        \multicolumn{1}{?c|}{} & \multicolumn{2}{c|}{\bf A} & \multicolumn{2}{c|}{\bf B} & \multicolumn{2}{c|}{\bf C} & \multicolumn{2}{c?}{\bf D} \bigstrut[t] \\
		        \specialrule{\lightrulewidth}{0mm}{0mm}
		        \textbf{1} & \answerbox{} & \answerbox{} & \answerbox{} & \answerbox{}\bigstrut \\
		        \textbf{2} & \answerbox{} & \answerbox{} & \answerbox{} & \answerbox{}\bigstrut \\
		        \textbf{3} & \answerbox{} & \answerbox{} & \answerbox{} & \answerbox{}\bigstrut \\
		        \textbf{4} & \answerbox{} & \answerbox{} & \answerbox{} & \answerbox{}\bigstrut \\
		        \textbf{5} & \answerbox{} & \answerbox{} & \answerbox{} & \answerbox{}\bigstrut \\
		        \textbf{6} & \answerbox{} & \answerbox{} & \answerbox{} & \answerbox{}\bigstrut \\
		        \textbf{7} & \answerbox{} & \answerbox{} & \answerbox{} & \answerbox{}\bigstrut \\
		        \textbf{8} & \answerbox{} & \answerbox{} & \answerbox{} & \answerbox{}\bigstrut \\
		        \textbf{9} & \answerbox{} & \answerbox{} & \answerbox{} & \answerbox{}\bigstrut \\
		        \textbf{10} & \answerbox{} & \answerbox{} & \answerbox{} & \answerbox{}\bigstrut \\
		        \specialrule{2pt}{0mm}{0mm}
		    \end{tabu}
		\end{center}
		
		\noindent
		Minden kérdés (pl. \emph{2. C}) esetén a helyes válasz $\sfrac{1}{4}$ pontot ér, míg az üresen hagyott rubrika $0$ pontot, a hibás válasz $\sfrac{1}{4}$ pont levonást ér. A pontozási rendszer révén a véletlenszerű tippelés \emph{nem} kifizetődő.
		
		\noindent\textbf{Egyértelműen jelölje} (satírozás vagy egymást keresztező vonalak), hogy az adott válaszlehetőség \emph{igaz}~(I) vagy \emph{hamis}~(H); bizonytalanság esetén a rubrika \emph{üresen hagyható}.
		
		\noindent\textbf{$\bm{10}$ pontból $\bm{5}$ pont} megszerzése szükséges a beugrókérdésekből; ennél alacsonyabb pontszám esetén a zárthelyi a nagyfeladatok eredményétől függetlenül elégtelen.
		
		\noindent\textbf{Automatikusan dolgozzuk fel} a feladatlapokat, így nyomatékosan kérjük, hogy a nem megválaszolt rubrikákba semmilyen jelölést ne tegyen! A lapon csak az egyes kérdésekre adott válaszokat, továbbá nevét és Neptun-kódját jelölje!
		
		\noindent\textbf{Javítást nem fogadunk el}, ezért javasoljuk a válaszokat csak erős átgondolás után átvezetni a táblázatba.
		
		\noindent\textbf{Tévesztés esetén} mindkét válaszlehetőség bejelölésével a válasz törölhető.
		
		\vfill
		\noindent
		\begin{pspicture}(5mm, 0cm)
		    \psbarcode{«barcode»}{height=0.196850394 width=7.48031496}{code128}
		\end{pspicture}
	'''

	def static void saveExam(int number, int base, String examShortName, String examName, String room, String kind) {
		val String res = generateExam(number, base, examShortName, examName, room, kind);
		val printer = new PrintWriter("tex/" + examShortName + '_' + room + '_' + kind + ".tex", "UTF-8");
		
		printer.print(res);
		printer.close;
	}

	def static String generateExam(int number, int base, String examShortName, String examName, String room, String kind) '''
		\documentclass[a4paper]{article}
		
		\usepackage[
		  margin=10mm,
		  footskip=5mm,
		]{geometry}
		
		\usepackage[magyar]{babel}
		\usepackage{fontspec}
		\usepackage{lmodern}
		
		\usepackage[table]{xcolor}
		
		\usepackage{framed}
		\usepackage{bigstrut}
		\usepackage{tabu}
		\usepackage{booktabs}
		\usepackage{multirow}
		\usepackage{pst-barcode}
		
		\usepackage{xfrac}
		\usepackage{bm}
		
		\pagestyle{empty}
		
		\usepackage{inc/checkbox}
		
		%\usepackage{showframe}
		
		\begin{document}
		\frenchspacing
		
		\vspace*{\fill}
		\begin{center}
		\fontsize{2cm}{2.5cm}\selectfont
		«examName»\\
		«room»\\
		«kind» csoport\\
		«number» példány\\
		\told«base»+tol{} 
		\end{center}
		\vspace*{\fill}
		\clearpage
		
		\large
		\setlength{\parskip}{0.5em}
		
		«FOR i : 1..number SEPARATOR "\n\\clearpage\n%---------------------\n"»
			«generateExamPage(
				(base+i), 
				examName,
				examShortName + ';' + room + ';' + kind + ';' + (base+i).toString(), 
				kind
			)»
		«ENDFOR»
		
		\end{document}
	'''

}
