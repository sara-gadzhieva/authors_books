#include <iostream>
#include <fstream>

using namespace std;
class book;
class author {
	public:
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
	author(char* f2,char* i2,char* o2,int g2): g(g2) {
		for(int j=0;j<30;j++) {
			f[j]=f2[j];
			i[j]=i2[j];
			o[j]=o2[j]; 
			}
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
		for (int j=0;j<30;j++) {
			if(f[j]=='\0'||i[j]=='\0'||o[j]=='\0')
			{
				break;
			}
			if(f[j]!=ob.f[j]) {
				return false;
				}
			if(i[j]!=ob.i[j]) {
				return false;
				}
			if(o[j]!=ob.o[j]) {
				return false;
				}
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
	public: ///пока что паблик
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
		for(int i=0; i<author_count;i++) {
			cout<<authors[i].get_i()<<endl;
			///cout << endl;
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
		for(int i=0;i<books[j].author_count;i++) {
			if(books[j].authors[i]==a) {
				books_a[c++]=books[j];
				}
			}
		}
		return books_a;
	}

int main (){
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
	author*authors=new author[author_count2];
	for (int i=0;i<author_count2;i++){
		char f2[30], i2[30], o2[30]; int g2;
		fin1>>f2>>i2>>o2>>g2;
		authors[i]=author(f2,i2,o2,g2);
		}
	
	int book_count2;
	fin2>>book_count2;
	book*books=new book[book_count2];
	///int real_book_count=0;
	for (int i=0;i<book_count2;i++) {
		char name2[30]; int page_count2, year2, count2;
		 ///count2 - количество авторов книги
		fin2>>name2>>page_count2>>year2>>count2;
		author* temp_authors=new author[count2];
		for(int j = 0; j < count2;j++) {
			char a_f[30],a_i[30],a_o[30];
			fin2>>a_f>>a_i>>a_o;
			temp_authors[j] = author(a_f, a_i, a_o, 0);
			}
		book booka(name2,count2,page_count2,year2,temp_authors);
		books[i]=booka;
		delete[] temp_authors;
	}
	/*for(int i=0;i<book_count2;i++)
	{
		for(int j=0;j<book_count2;j++)
		{
			if(books[i]==books[j])
			{
				
			}
		}
	}*/
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
			for(int j=0;j<book_count2;j++) {
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
				int c_max=book_count(books,book_count2,authors[0]);
				author author_max=authors[0];
				for(int i=0;i<author_count2;i++){
					if(book_count(books,book_count2,authors[i])>c_max){
						c_max=book_count(books,book_count2,authors[i]);
						author_max=authors[i];
						}
					}
				author_max.show();
			
				break;
			}
			case 4: {
				char f3[30], i3[30], o3[30];
				cout<<"введите фио автора: "<<endl;
				cin>>f3>>i3>>o3;
				author target(f3,i3,o3,0);
				bool flag=false;
				for (int i=0;i<book_count(books,book_count2,target);i++){
					flag = true;
					cout<<book_list(books,book_count2,target)[i].get_name()<<endl;
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
				for(int i=0;i<book_count2;i++) {
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
