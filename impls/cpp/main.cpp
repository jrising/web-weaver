#include <stdio.h>
#include "HTMLReader/LiteHTMLReader.h"

int main(int argc, const char* argv) {
  // arg1: entry class
  // arg2-N+1: column classes

  CLiteHTMLReader theReader;

  TCHAR   strToParse[] = _T("<HTML>"
							"<HEAD>"
							"<TITLE>"
							"<!-- title goes here -->"
							"</TITLE>"
							"</HEAD>"
							"<BODY LEFTMARGIN=\"15px\">This is a sample HTML document.</BODY>"
							"</HTML>");
  theReader.Read(strToParse);
  println(theReader);
}

