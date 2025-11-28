The Cyber Management System is a C-based application designed to store, manage, and modify customer usage records in a cyber café. It uses a structure (struct CyberRecord) and file handling (records.dat) to maintain data permanently.

The program displays a menu that allows the user to:

1. Add New Record
	•	The user enters details such as ID, name, PC number, login time, logout time, and amount.
	•	The record is saved to records.dat using binary file writing.

2. Search a Record
	•	A specific record can be searched using a user ID.
	•	If found, all details of the customer are displayed.
	•	If not found, a “No record found” message is shown.

3. Update an Existing Record
	•	The program searches the record by ID.
	•	If found, the user enters new details.
	•	The selected record is overwritten with the updated information using fseek().

4. Delete a Record
	•	A record can be deleted using its ID.
	•	The program copies all records except the one to be deleted into a temporary file.
	•	The old file is replaced with the updated file.

5. Display All Records
	•	All stored cyber café records are read and displayed in a clean, table-like format.

6. Exit
	•	The program prints a termination message and closes.

⸻

📌 Key Features
	•	Uses file handling to store data permanently.
	•	Uses structures to group related record fields.
	•	Allows CRUD operations: Create, Read, Update, Delete.
	•	Provides a clean menu-driven interface.
	•	Automatically clears the screen for better readability.

⸻

📌 What the Program Achieves

This system makes it easy for a cyber café administrator to:
	•	Track computer usage
	•	Maintain login/logout records
	•	Calculate and store payment amounts
	•	Retrieve records quickly
	•	Update or delete incorrect entries
