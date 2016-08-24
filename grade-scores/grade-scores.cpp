// Transmax "grade-scores" Console Application
//
// - Takes as a parameter a string that represents a text file containing a list of names, and their scores.
// - Orders the names by their score. If scores are the same, order by their last name followed by first name.
// - Creates a new text file called <input-file-name>-graded.txt with the list of sorted score and names.
//////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "functions.h"
//////////////////////////////////////////////////////////////////////////////

/**
 @description Main function of Transmax Console Application
 @methodOf
 @name nain
 @returns {int} = 0 on success, 1 on failure
 @author <a href="mailto:kwillis@vuware.com">Keith Willis</a>
*/
int main()
{
 String^ exampleUsage = "Example Usage: \"grade-scores C:\\names.txt\"";

 try
 {
  array<String^>^args = Environment::GetCommandLineArgs();

  if (args->Length != 2)  // Check for correct number of command line arguments
  {
   Console::WriteLine(exampleUsage);
   return 1;
  }

  String^ inputFile = args[1];
  StreamReader^ din = File::OpenText(inputFile);

  Collections::ArrayList^ records = gcnew Collections::ArrayList();

  String^ delimiters = ",";
  array<Char>^ delimiter = delimiters->ToCharArray();

  String^ record;
  int count = 0;
  while ((record = din->ReadLine()) != nullptr)
  {
   count++;
   parseRecord(3, delimiter, record, records);
  }

  IComparer^ recordComparer = gcnew RecordComparer;
  records->Sort(recordComparer);

  String^ outputFile = Path::GetFileNameWithoutExtension(inputFile) + "-graded" + Path::GetExtension(inputFile);
  StreamWriter^ writer = gcnew StreamWriter(Path::GetDirectoryName(inputFile) + outputFile);

  Console::SetOut(writer);
  for each(array<String^>^ record in records) Console::WriteLine("{0}, {1}, {2}", record[0], record[1], record[2] );
  writer->Close();

  StreamWriter^ standardOutput = gcnew StreamWriter(Console::OpenStandardOutput());  // Recover the standard output stream in order to display the "Finished" message.
  standardOutput->AutoFlush = true;
  Console::SetOut(standardOutput);
  Console::WriteLine("Finished: created {0}.", outputFile);

  return 0;
 }
 catch (Exception^ e)
 {
  TextWriter^ errorWriter = Console::Error;
  errorWriter->WriteLine(e->Message);
 }

 return 1;
}
//////////////////////////////////////////////////////////////////////////////
