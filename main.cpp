#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
class book;
class author {
	char f[30], i[30], o[30];
	int g;
	public:
	
	///конструктор (без параметров):
	author():g(0) {
		f[0]='\0';
		i[0]='\0';
		o[0]='\0';
		}
		
	///конструктор (с параметрами):
	author(char* f2,char* i2,char* o2,int g2):g(g2) {
		int j;
		for (j=0;j<29 && f2[j]!='\0'; j++) {
			f[j]=f2[j];
			}
		f[j]='\0';
		for (j=0;j<29 && i2[j]!='\0';j++) {
			i[j]=i2[j];
			}
		i[j]='\0';
		for (j=0;j<29 && o2[j]!='\0'; ++j) {
			o[j]=o2[j];
			}
		o[j]='\0';
		}
	///конструктор копирования:
	author(const author &obb):g(obb.g) {
		for (int j=0;j<30;j++) {
			f[j]=obb.f[j];
			i[j]=obb.i[j];
			o[j]=obb.o[j];
		}
	}
	
	///деструктор:
	~author() {}
	
	///функция вывода:
	void show() const {
		cout<<f<<" "<<i<<" "<<o<<", "<<g<<" года рождения"<<endl;
		}
	
	///оператор сравнения
	bool operator==(const author &ob) const {
		int j=0;
		while (f[j]!='\0' || ob.f[j]!='\0') {
			if (f[j]!=ob.f[j]) {
				return false;
				}
			j++;
			}	
		j=0;
		while (i[j]!='\0' || ob.i[j]!='\0') {
			if (i[j]!=ob.i[j]) {
				return false;
				}
			j++;
			}
		j=0;
		while (o[j]!='\0' || ob.o[j]!='\0') {
			if (o[j]!=ob.o[j]) {
				return false;
				}
			j++;
			}
		return true;
		}

	///оператор присваивания	
	author &operator=(const author &ob) {
		if (this!=&ob) {
			for(int j=0;j<30;j++) {
				f[j]=ob.f[j];
				i[j]=ob.i[j];
				o[j]=ob.o[j];
			}
			g=ob.g;
		}
		return *this;
	}
	
	///геттеры:
	const char* get_f() const { 
		return f; 
		}
	const char* get_i() const { 
		return i; 
		}
	const char* get_o() const { 
		return o; 
		}
	int get_g() const { 
		return g; 
		}		
	};
	
class book {
	char name[30];
	int author_count, page_count, year;
	author*authors;
	public:
	
	///конструктор (без параметров):
	book():author_count(0), page_count(0), year(0),authors(nullptr){
		name[0]='\0';
		}
	
	///конструктор (с параметрами):
	book(char *name2, int author_count2, int page_count2, int year2, author *authors2):author_count(author_count2), page_count(page_count2), year(year2), authors(nullptr){
		int j;
		for(j=0;j<29&&name2[j]!='\0';j++) {
			name[j]=name2[j];
			}
		name[j]='\0';		
		authors=new author[author_count];
		for(int i=0;i<author_count;i++) {
			authors[i]=authors2[i];
			}
		} 
	
	///конструктор копирования:
	book(const book &obb): author_count(obb.author_count), page_count(obb.page_count), year(obb.year), authors(nullptr){
		int j;
		for(j=0;j<29&&obb.name[j]!='\0';j++) {
			name[j]=obb.name[j];
			}
		name[j]='\0';
		authors=new author[author_count];
		for(int i=0;i<author_count;i++) {
			authors[i]=obb.authors[i];
			}
	}
	
	///оператор присваивания:
	book &operator=(const book &obb) {
		if(this==&obb) {
			return *this;
			}
			delete[] authors;
		author_count=obb.author_count;
		page_count=obb.page_count;
		year=obb.year;
		for(int j=0;j<30;j++) {
			name[j]=obb.name[j];
			}
		authors=new author[author_count];
		for(int i=0;i<author_count;i++) {
			authors[i]=obb.authors[i];
			}
		return *this;
		}	

	///деструктор:
	~book() {
		delete[] authors;
		}
		
	///функция вывода:
	void show() const {
		cout<<"название книги: "<<name<<endl;
		cout<<"количество страниц: "<<page_count<<endl;
		cout<<"год издания: "<<year<<endl;
		cout<<"авторы: "<<endl;
		for (int i=0;i<author_count;i++) {
			cout<<authors[i].get_f()<<" "<< authors[i].get_i()<<" "<<authors[i].get_o()<<endl;
		}
	}
	
	///оператор сравнения
	bool operator==(const book &ob2) const {
		for(int j=0;name[j]!='\0' || ob2.name[j]!='\0';j++){
			if(name[j]!=ob2.name[j]) {
				return false;
				}
			}
		return true;
		}
	
	///геттеры:
	const char* get_name() const {
		return name;
		}
	int get_page_count() const { 
		return page_count; 
		}
	int get_author_count() const { 
		return author_count; 
		}
	int get_year() const { 
		return year; 
		}
	const author* get_authors() const {
		return authors; 
		}
		
	};

int book_count(book *books,int n,author &a) {
	int c=0;
	for(int j=0;j<n;j++){
		bool flag=false;
		for(int i=0;i<books[j].get_author_count();i++) {
			if(books[j].get_authors()[i]==a) {
				flag=true;
				break;
				}
			}
			if(flag==true) {
				c++;
				}
		}
	return c;
	}
	
book* book_list(book *books,int n,author a) {
	book *books_a=new book[book_count(books,n,a)];
	int c=0;
	for(int j=0;j<n;j++){
		for(int i=0;i<books[j].get_author_count();i++) {
			if(books[j].get_authors()[i]==a) {
				books_a[c++]=books[j];
				}
			}
		}
		return books_a;
	}

bool ff(const char* s) {
    for (int t=0; s[t]!='\0';t++) {
        if (s[t]>='0' && s[t]<='9')
            return true;
		}
    return false;
	}

int main () {
	ifstream fin1("authors.txt");
	ifstream fin2("books.txt");
	if (!fin1.is_open()) {
		cout<<"файл authors.txt не открылся"<<endl;
		return 1;
		}
	if (!fin2.is_open()) {
		cout<<"файл books.txt не открылся"<<endl;
		return 2;
	}
	int author_count2;
	fin1>>author_count2;
	if (author_count2<=0) {
		cout<<"некорректное количество авторов"<<endl;
		return 1;
		}
	
	author*authors=new author[author_count2];
	for (int i=0;i<author_count2;i++){
		char f2[30], i2[30], o2[30], god[16]; 
		if(!(fin1>>f2>>i2>>o2>>god)) {
			cout<<"файл содержит меньше авторов, чем указано"<<endl;
			delete [] authors;
			return 2;
			}

		if (strlen(f2)>=30 || strlen(i2)>=30 || strlen(o2)>=30) {
			cout<<"слишком длинное ФИО автора в файле authors.txt"<<endl;
			delete[] authors;
			return 3;
			}
			if (ff(f2) || ff(i2) || ff(o2)) {
				cout<<"в имени автора недопустимые символы"<<endl;
				delete[] authors;
				return 4;
				}
			bool n=true;;
				for(int p=0;god[p]!='\0';p++) {
					if (god[p]<'0' || god[p]>'9') {
						n=false;;
						break;
						}
					}
				if(!n) {
					cout<<"в годе рождения автора некорректные символы "<<god<<endl;
					delete[] authors;
					return 4;
					}
				int g2=0;
				for(int p=0; god[p]!='\0';p++) {
					g2=g2*10+(god[p]-'0');
					}

		authors[i]=author(f2,i2,o2,g2);
		}
	
	///пример работы конструктора копирования
	author author2=authors[0]; 
	cout<<"оригинал: ";
	authors[0].show();
	cout<<"копия: ";
	author2.show();
	cout<<endl;
	
	int book_count2;
	fin2>>book_count2;
	if (book_count2<=0) {
		cout<<"некорректное количество книг"<<endl;
		delete [] authors;
		return 1;
		}
	book*books=new book[book_count2];
	int real_book_count=0;
	for (int i=0;i<book_count2;i++) {
		char name2[30];
		int page_count2, year2, count2;
		if(!(fin2>>name2>>page_count2>>year2>>count2)) {
			cout<<"файл содержит меньше книг, чем указано"<<endl;
			delete [] authors;
			delete [] books;
			return 2;
			}
		if (strlen(name2)>=30) {
			cout<<"слишком длинное название книги: "<<name2<<endl;
			delete[] authors;
			delete[] books;
			return 1;
			}	
		author* temp_authors=new author[count2];
		bool no_author=false;        
		for (int j=0;j<count2;j++) {
			char a_f[30], a_i[30], a_o[30];
			fin2>>a_f>>a_i>>a_o;
			if (ff(a_f) || ff(a_i) || ff(a_o)) {
				cout<<"в имени автора недопустимые символы"<<endl;
				delete[] temp_authors;
				delete[] authors;
				delete[] books;
				return 4;
				}
			///проверка на наличие автора
			bool found=false;
			author prob(a_f,a_i,a_o,0); ///для того чтобы сравнить
			for (int k=0;k<author_count2;k++) {
				if(authors[k]==prob) {
					temp_authors[j]=authors[k];
					found=true;
					break;
					}
				}	
			if (!found) {
				cout<<"автор "<<a_f<<" "<<a_i<<" "<<a_o<<" не найден в файле authors.txt. книга пропущена\n";
				no_author=true;
				}
		}
		if (no_author) {         
			delete[] temp_authors;
			continue;
			}

		///проверка на повторение автора
		bool dubl_authors=false;
		for (int a=0;a<count2 && !dubl_authors;a++) {
			for (int b=a+1; b<count2;b++) {
				if (temp_authors[a]==temp_authors[b]) { 
					dubl_authors=true; 
					break; 
					}
				}
			}
		if (dubl_authors) {
			cout<<"в книге указаны одинаковые авторы. книга пропущена\n";
			delete[] temp_authors;
			continue;
		}

		///проверка на повторение названия
		bool dubl_name=false;
		for (int t=0; t<real_book_count && !dubl_name;t++) {
			bool same=true;
			for(int x=0;books[t].get_name()[x]!='\0' || name2[x]!='\0';x++) {
				if (books[t].get_name()[x] != name2[x]) { 
					same=false; 
					break; 
					}
				}
			if (same) {
				dubl_name=true;
				}
			}
		if (dubl_name) {
			cout<<"книга с таким названием уже есть. книга пропущена\n";
			delete[] temp_authors;
			continue;
		}

		books[real_book_count++]=book(name2, count2, page_count2, year2, temp_authors);
		delete[] temp_authors;
	}

	int num;
	do {
		cout<<"1 - вывод подробной информации обо всех книгах"<<endl;
		cout<<"2 - вывод подробной информации обо всех авторах"<<endl;
		cout<<"3 - вывод авторов с наибольшим количеством книг"<<endl;
		cout<<"4 - вывод всех книг указанного автора"<<endl;
		cout<<"5 - вывод всех книг, выпущенных в указанный год"<<endl;
		cout<<"0 - выход из программы"<<endl;
		cin>>num;
		switch(num){
			case 1: {
			for(int j=0;j<real_book_count;j++) {
				books[j].show();
				}
			break;
			}
			case 2: { 
			for(int j=0;j<author_count2;j++) {
				authors[j].show();
				}
			break;
			}
			case 3: {
				int c_max=book_count(books,real_book_count,authors[0]);
				for(int i=0;i<author_count2;i++){
					if(book_count(books,real_book_count,authors[i])>c_max){
						c_max=book_count(books,real_book_count,authors[i]);
						}
					}
				for(int i=0;i<author_count2;i++){
					if(book_count(books,real_book_count,authors[i]) == c_max){
						authors[i].show();
						}
					}
				break;
			}
			case 4: {
				char f3[30], i3[30], o3[30];
				cout<<"введите фио автора: "<<endl;
				cin>>f3>>i3>>o3;
				author target(f3,i3,o3,0);
				bool flag=false;
				for (int i=0;i<book_count(books,real_book_count,target);i++){
					flag=true;
					cout<<book_list(books,real_book_count,target)[i].get_name()<<endl;
					}
				if(!flag) {
					cout<<"книг этого автора нет"<<endl;
					}
				break;
			}
			case 5: {
				int target_year;
				cout<<"введите год: "<<endl;
				cin>>target_year;
				bool flag=false;
				for(int i=0;i<real_book_count;i++) {
					if(books[i].get_year()==target_year) {
						cout<<books[i].get_name()<<endl;
						flag=true;
						}
					}
				if(!flag) {
					cout<<"нет книги, выпущенной в этот год"<<endl;
					}
				break;
				}
			case 0:
			break;
			default:
			cout<<"введите число от 0 до 5"<<endl;
			}
		}
	while (num!=0);
	fin1.close();
	fin2.close();
	delete[] authors;
	delete[] books;
	return 0;
	}
