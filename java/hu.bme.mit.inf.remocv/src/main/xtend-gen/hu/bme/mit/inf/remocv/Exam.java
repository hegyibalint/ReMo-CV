package hu.bme.mit.inf.remocv;

import java.io.PrintWriter;
import org.eclipse.xtend2.lib.StringConcatenation;
import org.eclipse.xtext.xbase.lib.Exceptions;
import org.eclipse.xtext.xbase.lib.IntegerRange;

@SuppressWarnings("all")
public class Exam {
  public static CharSequence generateExamPage(final int code, final String examName, final String barcode, final String kind) {
    StringConcatenation _builder = new StringConcatenation();
    _builder.append("\\noindent");
    _builder.newLine();
    _builder.append("\\begin{center}");
    _builder.newLine();
    _builder.append("    ");
    _builder.append("\\begin{tabu} to \\textwidth {r X l@{\\hskip 5mm} l }");
    _builder.newLine();
    _builder.append("    \t");
    _builder.append("\\multicolumn{2}{c}{\\LARGE\\bfseries Rendszermodellezés -- ");
    _builder.append(examName, "    \t");
    _builder.append("} & Feladat & \\multicolumn{1}{c}{Pontszám} \\\\[1mm]");
    _builder.newLineIfNotEmpty();
    _builder.append("    \t");
    _builder.append("\\toprule");
    _builder.newLine();
    _builder.append("        ");
    _builder.append("\\hspace{1cm}\\textbf{Kód:}    & ");
    _builder.append(code, "        ");
    _builder.append(" &        &\\bigstrut                        \\\\");
    _builder.newLineIfNotEmpty();
    _builder.append("    \t");
    _builder.append("\\hspace{1cm}\\textbf{Név:}    & & Beugró & \\hspace{1cm}\\textbf{/10}\\bigstrut \\\\");
    _builder.newLine();
    _builder.append("    \t");
    _builder.append("\\hspace{1cm}\\textbf{Neptun:} & &        &\\bigstrut                        \\\\");
    _builder.newLine();
    _builder.append("    \t");
    _builder.append("\\bottomrule");
    _builder.newLine();
    _builder.append("    ");
    _builder.append("\\end{tabu}");
    _builder.newLine();
    _builder.append("\\end{center}");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\begin{center}");
    _builder.newLine();
    _builder.append("\t");
    _builder.append("\\textbf{A DOLGOZATOT TOLLAL ÍRJA!}\\\\[4mm]");
    _builder.newLine();
    _builder.append("    ");
    _builder.append("\\newcolumntype{?}{!{\\vrule width 2pt}}");
    _builder.newLine();
    _builder.append("    ");
    _builder.append("\\rowcolors{1}{white}{gray!20}");
    _builder.newLine();
    _builder.append("    ");
    _builder.append("\\begin{tabu} to \\textwidth { ? c | X[c] X[c] | X[c] X[c] | X[c] X[c] | X[c] X[c] ? }");
    _builder.newLine();
    _builder.append("        ");
    _builder.append("\\specialrule{2pt}{0mm}{0mm}");
    _builder.newLine();
    _builder.append("        ");
    _builder.append("\\multicolumn{1}{?c|}{} & \\multicolumn{2}{c|}{\\bf A} & \\multicolumn{2}{c|}{\\bf B} & \\multicolumn{2}{c|}{\\bf C} & \\multicolumn{2}{c?}{\\bf D} \\bigstrut[t] \\\\");
    _builder.newLine();
    _builder.append("        ");
    _builder.append("\\specialrule{\\lightrulewidth}{0mm}{0mm}");
    _builder.newLine();
    _builder.append("        ");
    _builder.append("\\textbf{1} & \\answerbox{} & \\answerbox{} & \\answerbox{} & \\answerbox{}\\bigstrut \\\\");
    _builder.newLine();
    _builder.append("        ");
    _builder.append("\\textbf{2} & \\answerbox{} & \\answerbox{} & \\answerbox{} & \\answerbox{}\\bigstrut \\\\");
    _builder.newLine();
    _builder.append("        ");
    _builder.append("\\textbf{3} & \\answerbox{} & \\answerbox{} & \\answerbox{} & \\answerbox{}\\bigstrut \\\\");
    _builder.newLine();
    _builder.append("        ");
    _builder.append("\\textbf{4} & \\answerbox{} & \\answerbox{} & \\answerbox{} & \\answerbox{}\\bigstrut \\\\");
    _builder.newLine();
    _builder.append("        ");
    _builder.append("\\textbf{5} & \\answerbox{} & \\answerbox{} & \\answerbox{} & \\answerbox{}\\bigstrut \\\\");
    _builder.newLine();
    _builder.append("        ");
    _builder.append("\\textbf{6} & \\answerbox{} & \\answerbox{} & \\answerbox{} & \\answerbox{}\\bigstrut \\\\");
    _builder.newLine();
    _builder.append("        ");
    _builder.append("\\textbf{7} & \\answerbox{} & \\answerbox{} & \\answerbox{} & \\answerbox{}\\bigstrut \\\\");
    _builder.newLine();
    _builder.append("        ");
    _builder.append("\\textbf{8} & \\answerbox{} & \\answerbox{} & \\answerbox{} & \\answerbox{}\\bigstrut \\\\");
    _builder.newLine();
    _builder.append("        ");
    _builder.append("\\textbf{9} & \\answerbox{} & \\answerbox{} & \\answerbox{} & \\answerbox{}\\bigstrut \\\\");
    _builder.newLine();
    _builder.append("        ");
    _builder.append("\\textbf{10} & \\answerbox{} & \\answerbox{} & \\answerbox{} & \\answerbox{}\\bigstrut \\\\");
    _builder.newLine();
    _builder.append("        ");
    _builder.append("\\specialrule{2pt}{0mm}{0mm}");
    _builder.newLine();
    _builder.append("    ");
    _builder.append("\\end{tabu}");
    _builder.newLine();
    _builder.append("\\end{center}");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\noindent");
    _builder.newLine();
    _builder.append("Minden kérdés (pl. \\emph{2. C}) esetén a helyes válasz $\\sfrac{1}{4}$ pontot ér, míg az üresen hagyott rubrika $0$ pontot, a hibás válasz $\\sfrac{1}{4}$ pont levonást ér. A pontozási rendszer révén a véletlenszerű tippelés \\emph{nem} kifizetődő.");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\noindent\\textbf{Egyértelműen jelölje} (satírozás vagy egymást keresztező vonalak), hogy az adott válaszlehetőség \\emph{igaz}~(I) vagy \\emph{hamis}~(H); bizonytalanság esetén a rubrika \\emph{üresen hagyható}.");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\noindent\\textbf{$\\bm{10}$ pontból $\\bm{5}$ pont} megszerzése szükséges a beugrókérdésekből; ennél alacsonyabb pontszám esetén a zárthelyi a nagyfeladatok eredményétől függetlenül elégtelen.");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\noindent\\textbf{Automatikusan dolgozzuk fel} a feladatlapokat, így nyomatékosan kérjük, hogy a nem megválaszolt rubrikákba semmilyen jelölést ne tegyen! A lapon csak az egyes kérdésekre adott válaszokat, továbbá nevét és Neptun-kódját jelölje!");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\noindent\\textbf{Javítást nem fogadunk el}, ezért javasoljuk a válaszokat csak erős átgondolás után átvezetni a táblázatba.");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\noindent\\textbf{Tévesztés esetén} mindkét válaszlehetőség bejelölésével a válasz törölhető.");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\vfill");
    _builder.newLine();
    _builder.append("\\noindent");
    _builder.newLine();
    _builder.append("\\begin{pspicture}(5mm, 0cm)");
    _builder.newLine();
    _builder.append("    ");
    _builder.append("\\psbarcode{");
    _builder.append(barcode, "    ");
    _builder.append("}{height=0.196850394 width=7.48031496}{code128}");
    _builder.newLineIfNotEmpty();
    _builder.append("\\end{pspicture}");
    _builder.newLine();
    return _builder;
  }
  
  public static void saveExam(final int number, final int base, final String examShortName, final String examName, final String room, final String kind) {
    try {
      final String res = Exam.generateExam(number, base, examShortName, examName, room, kind);
      final PrintWriter printer = new PrintWriter((((((("tex/" + examShortName) + "_") + room) + "_") + kind) + ".tex"), "UTF-8");
      printer.print(res);
      printer.close();
    } catch (Throwable _e) {
      throw Exceptions.sneakyThrow(_e);
    }
  }
  
  public static String generateExam(final int number, final int base, final String examShortName, final String examName, final String room, final String kind) {
    StringConcatenation _builder = new StringConcatenation();
    _builder.append("\\documentclass[a4paper]{article}");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\usepackage[");
    _builder.newLine();
    _builder.append("  ");
    _builder.append("margin=10mm,");
    _builder.newLine();
    _builder.append("  ");
    _builder.append("footskip=5mm,");
    _builder.newLine();
    _builder.append("]{geometry}");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\usepackage[magyar]{babel}");
    _builder.newLine();
    _builder.append("\\usepackage{fontspec}");
    _builder.newLine();
    _builder.append("\\usepackage{lmodern}");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\usepackage[table]{xcolor}");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\usepackage{framed}");
    _builder.newLine();
    _builder.append("\\usepackage{bigstrut}");
    _builder.newLine();
    _builder.append("\\usepackage{tabu}");
    _builder.newLine();
    _builder.append("\\usepackage{booktabs}");
    _builder.newLine();
    _builder.append("\\usepackage{multirow}");
    _builder.newLine();
    _builder.append("\\usepackage{pst-barcode}");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\usepackage{xfrac}");
    _builder.newLine();
    _builder.append("\\usepackage{bm}");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\pagestyle{empty}");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\usepackage{inc/checkbox}");
    _builder.newLine();
    _builder.newLine();
    _builder.append("%\\usepackage{showframe}");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\begin{document}");
    _builder.newLine();
    _builder.append("\\frenchspacing");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\vspace*{\\fill}");
    _builder.newLine();
    _builder.append("\\begin{center}");
    _builder.newLine();
    _builder.append("\\fontsize{2cm}{2.5cm}\\selectfont");
    _builder.newLine();
    _builder.append(examName, "");
    _builder.append("\\\\");
    _builder.newLineIfNotEmpty();
    _builder.append(room, "");
    _builder.append("\\\\");
    _builder.newLineIfNotEmpty();
    _builder.append(kind, "");
    _builder.append(" csoport\\\\");
    _builder.newLineIfNotEmpty();
    _builder.append(number, "");
    _builder.append(" példány\\\\");
    _builder.newLineIfNotEmpty();
    _builder.append("\\told");
    _builder.append(base, "");
    _builder.append("+tol{} ");
    _builder.newLineIfNotEmpty();
    _builder.append("\\end{center}");
    _builder.newLine();
    _builder.append("\\vspace*{\\fill}");
    _builder.newLine();
    _builder.append("\\clearpage");
    _builder.newLine();
    _builder.newLine();
    _builder.append("\\large");
    _builder.newLine();
    _builder.append("\\setlength{\\parskip}{0.5em}");
    _builder.newLine();
    _builder.newLine();
    {
      IntegerRange _upTo = new IntegerRange(1, number);
      boolean _hasElements = false;
      for(final Integer i : _upTo) {
        if (!_hasElements) {
          _hasElements = true;
        } else {
          _builder.appendImmediate("\n\\clearpage\n%---------------------\n", "");
        }
        String _string = Integer.valueOf((base + (i).intValue())).toString();
        String _plus = ((((((examShortName + ";") + room) + ";") + kind) + ";") + _string);
        CharSequence _generateExamPage = Exam.generateExamPage((base + (i).intValue()), examName, _plus, kind);
        _builder.append(_generateExamPage, "");
        _builder.newLineIfNotEmpty();
      }
    }
    _builder.newLine();
    _builder.append("\\end{document}");
    _builder.newLine();
    return _builder.toString();
  }
}