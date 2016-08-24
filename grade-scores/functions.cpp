#include "stdafx.h"
#include "functions.h"
//////////////////////////////////////////////////////////////////////////////

/**
 @description Parse, (split) a comma separated value record and add result to a list of records passed in as a managed pointer.
 @methodOf
 @name parseRecord
 @param numFields {int} Number of expected field values in record
 @param delimiters {array<Char>^} Array of field delimiter characters
 @param record {String^} Record string
 @param records {Collections::ArrayList^} List of records
 @returns {bool} = true on success
 @author <a href="mailto:kwillis@vuware.com">Keith Willis</a>
*/
System::Boolean parseRecord(int numFields, array<Char>^ delimiter, String^ recordStr, Collections::ArrayList^ records)
{
 try
 {
  if (numFields <= 0) return false;
  if (delimiter == nullptr) return false;
  if (recordStr == nullptr) return false;
  if (records == nullptr) return false;

  array<String^>^ record;

  record = recordStr->Split(delimiter);
  if (record->Length == numFields)  // Check for correct number of field values per line
  {
   for (int i = 0; i<numFields; i++) record[i] = record[i]->Trim();
   records->Add(record);
  }

  return true;
 }
 catch (Exception^ e)
 {
  TextWriter^ errorWriter = Console::Error;
  errorWriter->WriteLine(e->Message);
  return false;
 }
}
//////////////////////////////////////////////////////////////////////////////
