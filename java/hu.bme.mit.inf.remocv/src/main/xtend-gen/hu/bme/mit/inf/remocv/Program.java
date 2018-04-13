package hu.bme.mit.inf.remocv;

import hu.bme.mit.inf.remocv.Exam;

@SuppressWarnings("all")
public class Program {
  public static void main(final String[] args) {
    String examName = null;
    String examShortName = null;
    examName = "PPZH";
    examShortName = "PPZH";
    Exam.saveExam(10, 100, examShortName, examName, "Terem", "405");
  }
}
