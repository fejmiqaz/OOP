#include <iostream>
#include <cstring>

using namespace std;

enum Genre{
    HORROR,
    COMEDY,
    DOCUMENTARY
};

class Movie{
private:
    int ID;
    char name[31];
    double price;
    Genre genre;
    void copy(const Movie & m){
        strcpy(this->name, m.name);
        this->ID = m.ID;
        this->genre = m.genre;
        this->price = m.price;
    }
public:
    Movie(){}
    Movie(int id, char *name, Genre genre, double price) {
        this->ID = id;
        strcpy(this->name, name);
        this->genre = genre;
        this->price = price;
    }
    Movie(const Movie & other){
        copy(other);
    }

    friend ostream &operator<<(ostream &os, const Movie &movie) {
        os << movie.name << " " << movie.genre << " " << movie.price << endl;
        return os;
    }

    Movie & operator=(const Movie & other){
        if(this!=&other){
            copy(other);
        }
        return * this;
    }

    bool operator==(const Movie & other){
        return ID  == other.ID;
    }
    double & operator+=(double increase){
        price *= (1.0 + increase / 100.0);
        return price;
    }
};

class Cinema{
private:
    char name[41];
    Movie * movies;
    int n;
    static int LOYAL_DISCOUNT;
    void copy( const Cinema & c){
        strcpy(this->name, c.name);
        this->n = c.n;
        movies = new Movie[this->n];
        for(int i = 0; i < this->n; i++){
            this->movies[i] = c.movies[i];
        }
    }
public:
    Cinema(char *name = ""){
        strcpy(this->name, name);
        this->n = 0;
        movies = new Movie[0];
    }
    Cinema(const Cinema & other){
        copy(other);
    }
    ~Cinema(){
        delete[] movies;
    }

    Cinema & operator+=(const Movie & other){
        for(int i = 0; i < n; i++){
            if(movies[i] == other){
                return * this;
            }
        }

        Movie * temp = new Movie[n+1];
        for(int i = 0; i < n; i++){
            temp[i] = movies[i];
        }
        temp[n++] = other;
        delete[]movies;
        movies = temp;
        return * this;
    }
    bool operator<(const Cinema & other){
        return n < other.n;
    }

    static int getLOYAL_DISCOUNT() {
        return LOYAL_DISCOUNT;
    }

    static void setLOYAL_DISCOUNT(int loyalDiscount) {
        LOYAL_DISCOUNT = loyalDiscount;
    }

    friend ostream &operator<<(ostream &os, const Cinema &cinema) {
        os << cinema.name << endl;
        for(int i = 0; i < cinema.n; i++){
            os << cinema.movies[i];
        }
        return os;
    }
    // need to work on this method
    void increase(Genre genre, double price){}
};
// need to work on this method
Cinema smallestChoice(Cinema * cinema, int n){}

int Cinema::LOYAL_DISCOUNT = 0;

int main() {
    int test_case;
    cin >> test_case;

    switch (test_case) {
        case 0: {
            cout << "TESTING MOVIE CONSTRUCTOR" << endl;

            Movie movie1(0, "Imaginary", Genre::HORROR, 300);
            Movie movie2(1, "Hangover", Genre::COMEDY, 350);
            Movie movie3(2, "Stormy", Genre::DOCUMENTARY, 300);

            cout << "TEST PASSED" << endl;
            break;
        }
        case 1: {
            cout<<"TESTING MOVIE OPERATOR <<"<<endl;

            Movie movie1(0, "Imaginary", Genre::HORROR, 300);
            Movie movie2(1, "Hangover", Genre::COMEDY, 350);
            Movie movie3(2, "Stormy", Genre::DOCUMENTARY, 300);

            cout << movie1;
            cout << movie2;
            cout << movie3;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 2: {
            cout<<"TESTING MOVIE OPERATOR +="<<endl;

            Movie movie1(0, "Imaginary", Genre::HORROR, 300);
            Movie movie2(1, "Hangover", Genre::COMEDY, 350);
            Movie movie3(2, "Stormy", Genre::DOCUMENTARY, 300);

            cout << movie1;
            cout << movie2;
            cout << movie3;

            movie1 += 15;
            movie2 += 25.5;
            movie3 += 37;

            cout << movie1;
            cout << movie2;
            cout << movie3;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 3: {
            cout<<"TESTING CINEMA CONSTRUCTOR and <<"<<endl;

            Cinema cinema("Cineplexx");
            cout << cinema;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 4: {
            cout<<"TESTING CINEMA OPERATOR += and <<"<<endl;

            Movie movie(0, "Imaginary", Genre::HORROR, 300);
            Movie movie1(1, "Hangover", Genre::COMEDY, 350);
            Movie movie2(2, "Stormy", Genre::DOCUMENTARY, 300);

            Cinema cinema("Cineplexx");

            cinema += movie;
            cinema += movie1;
            cinema += movie2;

            Cinema::setLOYAL_DISCOUNT(20);
            cout << cinema << endl;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 5: {
            cout<<"TESTING CINEMA OPERATOR += and <<"<<endl;

            Movie movie(0, "Imaginary", Genre::HORROR, 300);
            Movie movie1(1, "Hangover", Genre::COMEDY, 350);
            Movie movie2(2, "Stormy", Genre::DOCUMENTARY, 300);

            Cinema cinema("Cineplexx");

            cinema += movie;
            cinema += movie1;
            cinema += movie2;
            cinema += movie2;

            Cinema::setLOYAL_DISCOUNT(25);
            cout << cinema << endl;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 6: {
            cout<<"TESTING CINEMA COPY-CONSTRUCTOR and OPERATOR ="<<endl;

            Movie movie(0, "Imaginary", Genre::HORROR, 300);
            Movie movie1(1, "Hangover", Genre::COMEDY, 350);
            Movie movie2(2, "Stormy", Genre::DOCUMENTARY, 300);
            Movie movie3(3, "Omen", Genre::HORROR, 300);
            Movie movie4(4, "Argylle", Genre::COMEDY, 350);

            Cinema cinema1("Cineplexx");

            cinema1 += movie;
            cinema1 += movie1;
            cinema1 += movie2;


            Cinema cinema2(cinema1);
            Cinema cinema4;
            {
                Cinema cinema3("Galaxy");
                cinema3 += movie3;
                cinema3 += movie4;
                cinema4 = cinema3;
            }

            cout << cinema2;
            cout << cinema4;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 7: {
            cout<<"TESTING CINEMA OPERATOR < "<<endl;
            Movie horror(0, "Imaginary", Genre::HORROR, 300);
            Movie comedy(1, "Hangover", Genre::COMEDY, 350);
            Movie documentary(2, "Stormy", Genre::DOCUMENTARY, 300);

            Movie horror1(0, "Omen", Genre::HORROR, 300);
            Movie comedy1(3, "Argylle", Genre::COMEDY, 350);
            Movie documentary1(2, "Christspiracy", Genre::DOCUMENTARY, 300);

            Cinema cinema1("Galaxy");
            cinema1 += horror;
            cinema1 += comedy;
            cinema1 += documentary;

            Cinema cinema2("Encore");
            cinema2 += horror1;
            cinema2 += comedy;
            cinema2 += comedy1;
            cinema2 += documentary1;

            if (cinema1 < cinema2) {
                cout << "TEST PASSED" << endl;
            }
            break;

        }
        case 8: {
            cout<<"TESTING METHOD increase"<<endl;

            char name[40];
            cin.ignore();
            cin.getline(name, 40);

            Cinema cinema(name);

            int n;
            cin >> n;

            int id;
            char title[30];
            int genre;
            float cost;
            float percent;

            for (int i = 0; i < n; i++) {
                cin >> id;
                cin.ignore();
                cin.getline(title, 30);
                cin >> genre;
                cin >> cost;

                Movie movie(id, title, (Genre) genre, cost);
                cinema += movie;
            }

            cin >> percent;
            cin >> genre;
            cout << cinema << endl;
            cinema.increase((Genre)genre, percent);
            cout << cinema << endl;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 9: {
            cout<<"TESTING METHOD smallestChoiceCinema"<<endl;

            int n;
            cin >> n;
            Cinema cinemas[n];
            char name[40];

            for (int i = 0; i < n; i++) {
                cin.ignore();
                cin.getline(name, 40);
                Cinema cinema(name);

                int m;
                cin >> m;

                int id;
                char title[30];
                int genre;
                float cost;

                for (int j = 0; j < m; j++) {
                    cin >> id;
                    cin.ignore();
                    cin.getline(title, 30);
                    cin >> genre;
                    cin >> cost;

                    Movie movie(id, title, (Genre) genre, cost);
                    cinema += movie;
                }

                cinemas[i] = cinema;
            }

            Cinema smallestChoiceCinema = smallestChoice(cinemas, n);
            cout << smallestChoiceCinema << endl;

            cout << "TEST PASSED" << endl;

            break;
        }
    }
    return 0;
}
