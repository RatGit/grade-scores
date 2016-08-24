#ifndef functions_h
#define functions_h
//////////////////////////////////////////////////////////////////////////////

using namespace System;
using namespace System::IO;
using namespace System::Collections;
//////////////////////////////////////////////////////////////////////////////

System::Boolean parseRecord(int numFields=0, array<Char>^ delimiter=nullptr, String^ recordStr=nullptr, Collections::ArrayList^ records=nullptr);
//////////////////////////////////////////////////////////////////////////////

ref class RecordComparer:  public System::Collections::IComparer
{
 private:
  virtual int Compare(Object^ obj1, Object^ obj2) sealed = IComparer::Compare
  {
   array<String^>^ record1 = (array<String^>^)obj1;
   array<String^>^ record2 = (array<String^>^)obj2;

   int score1 = Convert::ToInt32(record1[2]);
   int score2 = Convert::ToInt32(record2[2]);

   if (score1 > score2) return -1;
   if (score1 < score2) return 1;

   String^ surname1 = record1[0]->ToUpper();
   String^ surname2 = record2[0]->ToUpper();

   int result = String::Compare(surname1, surname2);
   if (result != 0) return result;

   String^ firstname1 = record1[1]->ToUpper();
   String^ firstname2 = record2[1]->ToUpper();

   return String::Compare(firstname1, firstname2);
  }
};
//////////////////////////////////////////////////////////////////////////////

#endif
