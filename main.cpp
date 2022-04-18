/*
 Boost Software License - Version 1.0 - August 17th, 2003

 Permission is hereby granted, free of charge, to any person or organization
 obtaining a copy of the software and accompanying documentation covered by
 this license (the "Software") to use, reproduce, display, distribute,
 execute, and transmit the Software, and to prepare derivative works of the
 Software, and to permit third-parties to whom the Software is furnished to
 do so, all subject to the following:

 The copyright notices in the Software and this entire statement, including
 the above license grant, this restriction and the following disclaimer,
 must be included in all copies of the Software, in whole or in part, and
 all derivative works of the Software, unless such copies or derivative
 works are solely in the form of machine-executable object code generated by
 a source language processor.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
 */

#include <iostream>
#include <algorithm>
#include<assert.h>
using namespace std;

const int MAX_USERS = 10;
const int MAX_BOOKS = 10;

struct book {

	//member data
	string book_name;
	int book_id;
	int total_quantity;
	int total_borrowed;
	//member functions

	book() {
		book_name = " ";
		book_id = 000;
		total_quantity = 0;
		total_borrowed = 0;
	}

	void read_book_info() {
		cout << "\nEnter book Name: ";
		cin >> book_name;
		cout << "Enter book ID: ";
		cin >> book_id;
		cout << "Enter no.of book Copies:";
		cin >> total_quantity;
	}

	void print_book_info() {
		cout << "\n -> Book name: " << book_name << " -> ID: " << book_id
				<< " -> Quantity: " << total_quantity << " copies."
				<< " -> Total borrowed: " << total_borrowed << " copies.";
		if (total_quantity == total_borrowed)
			cout << "(not available!)";
		cout << "\n";
	}

	//searching algirithm : substring of a big string

	bool is_substring(string &substring) {

		if (substring.size() > book_name.size()) // prefix name greater than book name
			return false;

		for(int i=0;i<(int) book_name.size()-(int) substring.size()+1;i++) {

			bool is_match=true;

			for(int j=0;j<(int)substring.size()&& is_match;j++) {
				if(substring[j]!=book_name[i+j])
					is_match=false;
			}
			if(is_match)
				return true;
		}
		return false;
	}

	bool user_borrow_copy(int user_id) {

		if (total_quantity - total_borrowed == 0)
			return false;

		total_borrowed++; //here
		return true;
	}
	void user_return_copy() {

		assert(total_borrowed > 0); //total borrowed must be greater than zero. if not assertion failed

		total_borrowed--;
	}

};

bool compare_books_by_id(book &a, book &b) {
	return a.book_id < b.book_id;
}
bool compare_books_by_name(book &a, book &b) {
	return a.book_name < b.book_name;
}

struct user {

	string user_name;
	int user_id;
	int borrowed_books_ids[MAX_BOOKS];
	int len;

	user() {
		user_name = "";
		user_id = 000;
		len = 0;
	}

	void read_user_info() {
		cout << "\nEnter user Name:";
		cin >> user_name;
		cout << "Enter user National ID:";
		cin >> user_id;
	}

	void print_user_info() {

		sort(borrowed_books_ids, borrowed_books_ids + len);

		cout << "\n-> user name : " << user_name << " -> ID: " << user_id
				<< " -> Borrowed books IDs: ";

		for (int i = 0; i < len; i++) {

			cout << borrowed_books_ids[i] << " ";

		}
		if (len == 0)
			cout << "(No borrowed copies)";
		cout << "\n";

	}

	void borrow_copy(int book_id) {
		borrowed_books_ids[len++] = book_id;
	}
	void return_copy(int book_id) {

		bool removed = false; //first element still not removed

		for (int i = 0; i < len; i++) {

			if (borrowed_books_ids[i] == book_id)
				for (int j = i + 1; j < len; j++) //left shift to remove the first element in the borrowed books array
					borrowed_books_ids[i - 1] = borrowed_books_ids[i];
			removed = true; //first element removed sucessfully
			len--; //decrease total books by one
			break;
		}
	}

	bool is_borrowed(int book_id) {
		for (int i = 0; i < len; i++) {
			if (book_id == borrowed_books_ids[i])
				return true;
		}
		return false;
	}

};

bool compare_users_by_id(user &a, user &b) {
	return a.user_id < b.user_id;
}
bool compare_users_by_name(user &a, user &b) {
	return a.user_name < b.user_name;
}

struct library_system {

	book books[MAX_BOOKS];
	int total_books = 0; //counter

	user users[MAX_USERS];
	int total_users = 0;

	void run() {
		int main_choice = main_menu();

		if (main_choice == 3)
			return; //here

		while (main_choice == 1) {

			int admin_choice = admin_menu();

			if (admin_choice == 1)
				add_new_book();
			else if (admin_choice == 2)
				search_books();
			else if (admin_choice == 3)
				list_books_by_id();
			else if (admin_choice == 4)
				list_books_by_name();
			else if (admin_choice == 5)
				add_new_user();
			else if (admin_choice == 6)
				list_users_by_id();
			else if (admin_choice == 7)
				list_users_by_name();
			else if (admin_choice == 8)
				list_users_borrowed_specific_book();
			else if (admin_choice == 9) {
				run();
				main_choice = 3;
			} else
				break;

		}

		while (main_choice == 2) {

			int user_choice = user_menu();

			if (user_choice == 1)
				search_books();
			else if (user_choice == 2)
				borrow_book();
			else if (user_choice == 3)
				return_book();
			else if (user_choice == 4) {
				run();
				main_choice = 3;
			} else
				break;
		}
	}

	int main_menu() {

		int choice = -1;
		while (choice == -1) {
			cout << "\n1) Admin Dashboard\n"
					"2) User Dashboard\n"
					"3) Exit\n"
					"Enter your choice: ";
			cin >> choice;

			if (!(1 <= choice && choice <= 3)) {
				cout << "\ninvalid choice. Try again!\n";
				choice = -1;
			}

		}
		return choice;
	}
	int admin_menu() {
		int choice = -1;

		while (choice == -1) {
			cout << "\n1) Add new book\n"
					"2) Search books\n"
					"3) List books ordered by id\n"
					"4) List books ordered by name\n"
					"5) Add new user\n"
					"6) List users by id\n"
					"7) List users by name\n"
					"8) List users borrowed a specific book\n"
					"9) Back\n"
					"10)Exit\n"
					"Enter your choice:";
			cin >> choice;

			if (!(1 <= choice && choice <= 10)) {
				cout << "\nInvalid choice. Try again!\n";
				choice = -1;
			}

		}

		return choice;
	}
	int user_menu() {
		int choice = -1;

		while (choice == -1) {
			cout << "1) \nSearch books\n"
					"2) Borrow book\n"
					"3) Return book\n"
					"4) Back\n"
					"5) Exit\n"

					"Enter your choice:";
			cin >> choice;

			if (!(1 <= choice && choice <= 6)) {
				cout << "\ninvalid choice. Try again!\n";
			}

		}
		return choice;
	}

//admin options

	void add_new_book() {
		books[total_books++].read_book_info();
	}

	void search_books() {

		//test case: algorithms -> prefix :algo
		cout << "\nEnter book name :";
		string substring;
		cin >> substring;

		int cnt = 0; // if counter doesn't increase then there is no book with such name
		for (int i = 0; i < total_books; i++) {
			if (books[i].is_substring(substring)) {
				cout <<"\n"<< books[i].book_name << "\n";
				cnt++;
			}

		}

		if (!cnt)
			cout << "\nNo book with such name\n";

	}

	void list_books_by_id() {

		sort(books, books + total_books, compare_books_by_id); //descending order according to IDs : 101 < 202

		if (total_books == 0)
			cout << "\nNo books yet. Add some!\n";
		if (total_books == 1)
			cout << "\nThere is only one book in the library\n";

		if (total_books >= 2) //here --> max books number
			cout << "\nThere are " << total_books << " books in the library\n";

		for (int i = 0; i < total_books; i++)
			books[i].print_book_info();
		cout << "\n";
	}

	void list_books_by_name() {

		sort(books, books + total_books, compare_books_by_name); //descending order according to names : a < b , b < c(ASCII)

		if (total_books == 0)
			cout << "\nNo books yet. Add some!\n";
		if (total_books == 1)
			cout << "\nThere is only one book in the library\n";

		if (total_books >= 2) //here --> max books number
			cout << "\nThere are " << total_books << " books in the library\n";

		for (int i = 0; i < total_books; i++)
			books[i].print_book_info();
		cout << "\n";
	}

	void add_new_user() {
		users[total_users++].read_user_info();
	}

	void list_users_by_id() {

		sort(users, users + total_users, compare_users_by_id);

		for (int i = 0; i < total_users; i++)
			users[i].print_user_info();
		cout << "\n";
	}
	void list_users_by_name() {

		sort(users, users + total_users, compare_users_by_name);

		for (int i = 0; i < total_users; i++)
			users[i].print_user_info();
		cout << "\n";
	}

	void list_users_borrowed_specific_book() {

		string book_name;
		cout << "\nEnter book name: ";
		cin >> book_name;

		//check if book name valid or not
		int book_idx = find_book_id_by_book_name(book_name);
		if (book_idx == -1) {
			cout << "\ninvalid book name. try again!\n"; return;
		}
		//check if there is borrowed copies from a specific book
		if (books[book_idx].total_borrowed == 0) {
			cout << "\nNo borrowed copies yet!\n"; return;
		}

		//print users borrowed a specific book
		int book_id = books[book_idx].book_id;

		if (book_id >= 0)
			cout << "\nBook has been borrowed by:\n";

		for (int i = 0; i < total_users; i++)
			if (users[i].is_borrowed(book_id))
				cout << "User Name: " << users[i].user_name << " User ID: "
						<< users[i].user_id << "\n";
	}

//user options

	//borrow and return functionalities

	int find_user_id_by_user_name(string user_name) {

		for (int i = 0; i < total_users; i++)
			if (users[i].user_name == user_name)
				return i;

		return -1;
	}
	int find_book_id_by_book_name(string book_name) {

		for (int i = 0; i < total_books; i++)
			if (books[i].book_name == book_name)
				return i;

		return -1;
	}

	bool read_user_name_and_book_name(int &user_id, int &book_id,
			int trails = 3) {

		string user_name, book_name;

		while (trails--) {

			cout << "\nEnter user name and book name: ";
			cin >> user_name >> book_name;

			user_id = find_user_id_by_user_name(user_name);

			if (user_id == -1) {
				cout << "\ninvalid_user_name. try again!\n";
				continue;
			}

			book_id = find_book_id_by_book_name(book_name);

			if (book_id == -1) {
				cout << "\ninvalid book name. try again!\n";
				continue;
			}
			return true;

		}
		cout << "\nyou do several trails. try again later!\n";
		return false;
	}

	void borrow_book() {

		int user_idx, book_idx;

		if (!read_user_name_and_book_name(user_idx, book_idx))
			return;

		int user_id = users[user_idx].user_id;
		int book_id = books[book_idx].book_id;

		if (!books[book_idx].user_borrow_copy(user_id)) //increase total borrowed books by 1
				{
			cout << "\nNo more available copies from book with name "
					<< books[book_idx].book_name
					<< ". you can search for another one!\n";

		} else {
			users[user_idx].borrow_copy(book_id);
			cout << "\nBook borrowed sucessfully\n";
		}
	}

	void return_book() {
		int user_idx, book_idx;

		read_user_name_and_book_name(user_idx, book_idx);

		int book_id = books[book_idx].book_id;

		books[book_idx].user_return_copy(); // decrease total borrowed books by 1
		users[user_idx].return_copy(book_id);
		cout << "\n Book returned sucessfully\n";
	}

};

int main() {
	library_system library;
	library.run();

	return 0;

}
