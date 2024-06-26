#include <iostream>
#include <cstring>
using namespace std;

//YOUR CODE HERE:

class ElementAlreadyExists {
public:
    void message() { cout << "Element already exists."; }
};

template<typename T>
class List {
private:
    T *array;
    int n;
    void copy (const List & l){
        this->n = l.n;
        this->array = new T[n];
        for(int i = 0; i < n; i++){
            this->array[i] = l.array[i];
        }
    }
public:
    List() {
        n = 0;
        array = new T[n];
    }
    List(const List<T> & other){
        copy(other);
    }

    int getN() const {
        return n;
    }

    List & operator=(const T & other){
        if(this!=*other){
            delete[]array;
            copy(other);
        }
        return * this;
    }

    List & operator+=(const T &element) {

        for (int i = 0; i < n; i++) {
            if (array[i] == element) {
                throw ElementAlreadyExists();
            }
        }

        T *tmp = new T[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = array[i];
        }
        tmp[n++] = element;
        delete[] array;
        array = tmp;
        return *this;
    }

    friend ostream & operator<< (ostream & out, const List & l){
        if(l.n == 0){
            out << "List is empty!";
        }else{
            for(int i = 0; i < l.n; i++){
                out << l.array[i];
            }
        }
        return out;
    }

    T & operator[](int n){
        return array[n];
    }

};

enum TYPE{
    ACADEMIC,
    ROMAN
};

class Book{
private:
    char name[31];
    int serialNum;
    static int ID;
    int id;
    TYPE type;
    double price;
    void copy(const Book & b){
        strcpy(this->name, b.name);
        this->serialNum = b.serialNum;
        this->type = b.type;
        this->price = b.price;
    }
public:
    Book(){}
    Book(char *name, int serialNum, double price) {
        strcpy(this->name,name);
        this->id = ++ID;
        this->serialNum = serialNum;
        this->price = price;
        if(serialNum == 0){
            this->type = ACADEMIC;
        }else if(serialNum == 1){
            this->type = ROMAN;
        }
    }
    Book(const Book & other){
        copy(other);
    }

    TYPE getType() const {
        return type;
    }

    double getPrice() const {
        return price;
    }

    Book & operator=(const Book & other){
        if(this!=&other){
            copy(other);
        }
        return * this;
    }

    double & operator+=(double margin){
        price += margin;
        return price;
    }

    int getId() const {
        return id;
    }

    bool operator==(const Book & b){
        return id == b.id;
    }

    friend ostream &operator<<(ostream &os, const Book &book) {
        os << book.id << " - " << book.name << " ";
        if (book.type == ACADEMIC){ os << "academic";}
        else if (book.type == ROMAN){ os << "roman";}
        os << " " << book.price << endl;
        return os;
    }
    friend class BookStore;
};

class BookStore{
private:
    char name[21];
    List<Book> books;
    void copy(const BookStore & bs){
        strcpy(this->name, bs.name);
        this->books = bs.books;
    }
public:
    BookStore(char *name = ""){
        strcpy(this->name, name);

    }
    BookStore(const BookStore & other){
        copy(other);
    }
    BookStore & operator=(const BookStore & other){
        if(this!=&other){
            strcpy(this->name,name);
            this->books = other.books;
        }
        return * this;
    }
    ~BookStore(){
    }

    BookStore & operator+=(const Book & other){
        this->books += other;
        return * this;
    }

    friend ostream &operator<<(ostream &os, const BookStore &store) {
        os << store.name << endl;
        os << store.books;
        return os;
    }

    bool operator>(const BookStore & other){
        return books.getN() > other.books.getN();
    }
    // need to work on this method
    void createMarketPrice(){
        for(int i = 0; i < books.getN(); i++){
            if(books[i].getType() == 0){
                float fee = books[i].getPrice() * 0.05;
                books[i] += fee;
            }else{
                float fee = books[i].getPrice() * 0.03;
                books[i] += fee;
            }
        }
    }
};
// TODO: work on this method
int best(BookStore * books, int n){

}
int Book::ID = 777550;

int main() {
    int testCase;
    cin>>testCase;
    if(testCase==0)
    {
        cout<<"TESTING BOOK CONSTRUCTOR"<<endl;
        Book book1("Object-oriented programming",0,2300);
        Book book2("Discrete Mathematics",0,1800);
        Book book3("Crime and punishment",1,950);
        cout<<"TEST PASSED"<<endl;
    }else if(testCase==1)
    {
        cout<<"TESTING BOOK OPERATOR <<"<<endl;
        Book book1("Object-oriented programming",0,2300);
        Book book2("Discrete Mathematics",0,1800);
        Book book3("Crime and punishment",1,950);
        cout<<book1;
        cout<<book2;
        cout<<book3;
        cout<<"TEST PASSED"<<endl;
    } else if(testCase==2)
    {
        cout<<"TESTING BOOK OPERATOR +="<<endl;
        Book book1("Object-oriented programming",0,2300);
        Book book2("Discrete Mathematics",0,1800);
        Book book3("Crime and punishment",1,950);
        cout<<book1;
        cout<<book2;
        cout<<book3;
        book1+=200;
        book2+=300;
        book3+=150;
        cout<<"===== INCREASE ====="<<endl;
        cout<<book1;
        cout<<book2;
        cout<<book3;
        cout<<"TEST PASSED"<<endl;
    }else if(testCase==3)
    {
        cout<<"TESTING BOOKSTORE CONSTRUCTOR"<<endl;
        BookStore bookStore1("The Book Cellar");
        cout<<bookStore1;
        cout<<"TEST PASSED"<<endl;
    }else if(testCase==4)
    {
        cout<<"TESTING BOOKSTORE OPERATOR += and <<"<<endl;
        Book book1("Object-oriented programming",0,2300);
        Book book2("Discrete Mathematics",0,1800);
        Book book3("Crime and punishment",1,950);
        BookStore bookStore1("The Book Cellar");
        bookStore1+=book1;
        bookStore1+=book2;
        bookStore1+=book3;
        cout<<bookStore1;
        cout<<"TEST PASSED"<<endl;
    }
    else if(testCase==5)
    {
        cout<<"TESTING BOOKSTORE OPERATOR += and <<"<<endl;
        Book book1("Object-oriented programming",0,2300);
        Book book2("Discrete Mathematics",0,1800);
        Book book3("Crime and punishment",1,950);
        BookStore bookStore1("The Book Cellar");
        bookStore1+=book1;
        bookStore1+=book2;
        bookStore1+=book3;
        cout<<bookStore1;
        bookStore1+=book1;
        cout<<"TEST PASSED"<<endl;
    }
    else if(testCase==6)
    {
        cout<<"TESTING BOOKSTORE COPY-CONSTRUCTOR and OPERATOR ="<<endl;
        Book book1("Object-oriented programming",0,2300);
        Book book2("Discrete Mathematics",0,1800);
        Book book3("Crime and punishment",1,950);
        Book book4("Anna Karenina",1,1200);
        Book book5("Calculus 1",0,1320);
        BookStore bookStore1("The Book Cellar");
        bookStore1+=book1;
        bookStore1+=book2;
        bookStore1+=book3;
        BookStore bookStore2(bookStore1);
        BookStore bookStore4;
        {
            BookStore bookStore3("Word Wizardry Books");
            bookStore3+=book4;
            bookStore3+=book5;
            bookStore4=bookStore3;
        }
        cout<<bookStore2;
        cout<<bookStore4;
        cout<<"TEST PASSED"<<endl;

    }else if(testCase==7)
    {
        cout<<"TESTING BOOKSTORE OPERATOR > "<<endl;
        Book book1("Object-oriented programming",0,2300);
        Book book2("Discrete Mathematics",0,1800);
        Book book3("Crime and punishment",1,950);
        Book book4("Anna Karenina",1,1200);
        Book book5("Calculus 1",0,1320);
        BookStore bookStore1("The Book Cellar");
        bookStore1+=book1;
        bookStore1+=book2;
        bookStore1+=book3;
        BookStore bookStore3("Word Wizardry Books");
        bookStore3+=book4;
        bookStore3+=book5;
        if(bookStore1>bookStore3)
        {
            cout<<"TEST PASSED"<<endl;
        }
        else
        {
            cout<<"TEST FAILED"<<endl;
        }
    }else if(testCase==8)
    {
        cout<<"TESTING METHOD createMarketPrice()"<<endl;
        char name[30],name1[30];
        int type, numofBookStores, numberOfBooks;
        float price;
        cin>>numofBookStores;
        cin.ignore();
        BookStore bookStores[10];
        for(int i=0;i<numofBookStores;i++)
        {
            cin.getline(name,20);
            bookStores[i]=BookStore(name);
            cin>>numberOfBooks;
            cin.ignore();
            Book books[10];
            for(int j=0;j<numberOfBooks;j++)
            {
                cin >> name1 >> type >> price;
                cin.ignore();
                books[j]=Book(name1,type,price);
                try {
                    bookStores[i]+=books[j];
                }catch (ElementAlreadyExists & e){
                    e.message();
                }
            }
        }
        for(int i=0;i<numofBookStores;i++)
        {
            cout<<bookStores[i];
            cout<<"CREATED MARKET PRICES"<<endl;
            bookStores[i].createMarketPrice();
            cout<<bookStores[i];
        }

    }else if(testCase==9)
    {
        cout<<"TESTING METHOD best()"<<endl;
        char name[30],name1[30];
        int type, numofBookStores, numberOfBooks;
        float price;
        cin>>numofBookStores;
        cin.ignore();
        BookStore bookStores[10];
        for(int i=0;i<numofBookStores;i++)
        {
            cin.getline(name,20);
            bookStores[i]=BookStore(name);
            cin>>numberOfBooks;
            cin.ignore();
            Book books[10];
            for(int j=0;j<numberOfBooks;j++)
            {
                cin >> name1 >> type >> price;
                cin.ignore();
                books[j]=Book(name1,type,price);
                bookStores[i]+=books[j];
            }
        }
        cout<<best(bookStores,numofBookStores);
    }
    return 0;
}