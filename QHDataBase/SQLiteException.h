#ifndef SQLiteException_H
#define SQLiteException_H

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include "QHDataBase.h"

namespace QHDB
{	
	//! Exception class for sqlite and QHDBSQLiteWrapper errors
	class _SQLiteWrapperExport SQLiteException
	{
	public:
		//! Overloaded constructor
		SQLiteException(const std::string &filename, unsigned int lineNumber, std::string errDescription = "", int internalSqliteResultCode = -1):
		mErrorDescription(errDescription),
		mFilename(filename),
		mLineNumber(lineNumber),
		mInternalSqliteResultCode(internalSqliteResultCode)
		{
		}
		
		//! Overloaded constructor
		SQLiteException(const std::string &filename, unsigned int lineNumber, const char *errDescription = "", int internalSqliteResultCode = -1):
		mErrorDescription(std::string(errDescription)),
		mFilename(filename),
		mLineNumber(lineNumber),
		mInternalSqliteResultCode(internalSqliteResultCode)
		{
		}

		//! Shows all error information (filename, line, error message).\n
		//! Output: std::cerr
		inline void Show() const {std::cerr << "file: " << mFilename << "\nline number: " << mLineNumber << "\nerror: " << mErrorDescription << std::endl;}
		
		//! Get all error information (filename, line, error message) as std::string.
		std::string GetString() const 
		{
			std::stringstream strStream;
			strStream << "file: " << mFilename << "\nline number: " << mLineNumber << "\nerror: " << std::string(mErrorDescription) << "\n";
			return strStream.str();
		}

		//! Returns an error description.
		std::string GetErrorDescription() const {return mErrorDescription;}

		//! Returns the filename in which the error occured.
		std::string GetFilename() const {return mFilename;}

		//! Returns the line number in which the error occured.
		unsigned int GetLineNumber() const {return mLineNumber;}
		
		//! Returns the SQLite result code. It will also return extended result codes.\n
		//! Please refer to the following links to see the existing codes.\n
		//! SQLite Result Codes: http://sqlite.org/c3ref/c_abort.html \n
		//! SQLite Extended Result Codes: http://sqlite.org/c3ref/c_abort_rollback.html \n
		//! In case that this SQLiteWrapper will throw an own exception the result code will be -1.
		int GetSqliteResultCode() const {return mInternalSqliteResultCode;}

	private:
		//! Error description
		std::string mErrorDescription;
		//! Filename in which the error occured
		std::string mFilename;
		//! Line number in which the error occured
		unsigned int mLineNumber;
		//! Internal SQLite result code
		int mInternalSqliteResultCode;
	};
};

#endif // QHDBSQLiteException_H

#ifndef QHDB_EXCEPT
#define QHDB_EXCEPT(errorString, internalSqliteResultCode) throw SQLiteException(__FILE__, __LINE__, errorString, internalSqliteResultCode)
#endif
