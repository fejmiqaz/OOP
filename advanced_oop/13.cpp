#include<iostream>
#include<string>
#include<cstring>
using namespace std;

class ExistingPodcast {
private:
    string name;
public:
    ExistingPodcast(const string &name) : name(name) {
    }
    void message() {
        cout << "The podcast is already in the collection" << endl;
    };
};

class Podcast {
protected:
    char name[100];
    char url[1000];
    float price;
    int discount;
    void copy(const Podcast & p){
        strcpy(this->name, p.name);
        strcpy(this->url, p.url);
        this->price = p.price;
        this->discount = p.discount;
    }
public:
    Podcast(){}
    Podcast(char * name, char * url, float price, int discount) : price(price), discount(discount) {
        strcpy(this->name,name);
        strcpy(this->url, url);
    }

    Podcast(const Podcast & other){
        copy(other);
    }

    float getPrice() const {
        return price;
    }

    friend ostream &operator<<(ostream & os, Podcast p){
        os << "Podcast: " << p.name << endl;
        os << "URL: " << p.url << endl;
        os << "regular price: $" << p.price;
        if(p.discount > 0 && p.discount < 100){
            cout << ", bought on discount";
        }
        return os;
    }

    Podcast & operator=(const Podcast & other){
        if(this!=&other){
            copy(other);
        }
        return * this;
    }

    friend istream& operator>>(istream&in, Podcast&p){
        in >> ws;
        in.getline(p.name, 100);
        in >> ws;
        in.getline(p.url,1000);
        in >> p.price;
        in >> p.discount;
        return in;
    }

    bool operator==(const Podcast & p){
        return (strcmp(static_cast<char*>(url), p.url)==0);
    }

};

class StreamingPodcast : public Podcast {
protected:
     float monthlyFee;
     int month, year;
     void copy(const StreamingPodcast & sp){
         this->monthlyFee = sp.monthlyFee;
         this->month = sp.month;
         this->year = sp.year;
     }
public:
    StreamingPodcast(){}
    StreamingPodcast(char * name, char * url, float price, int discount,float monthlyFee, int month, int year)
            : Podcast(name, url, price, discount), monthlyFee(monthlyFee), month(month), year(year) {}

    StreamingPodcast(const StreamingPodcast & other){
         copy(other);
    }

    float getMonthlyFee() const {
        return monthlyFee;
    }

    int getMonth() {
        return month;
    }

    int getYear() {
        return year;
    }

    friend istream& operator>>(istream & in, StreamingPodcast & s){
        in >> ws;
        in.getline(s.name,100);
        in.getline(s.url,1000);
        in >> s.price >> s.discount >> s.monthlyFee >> s.month >> s.year;
        return in;
    }

    friend ostream &operator<<(ostream &os, const StreamingPodcast &podcast) {
        os << static_cast<const Podcast &>(podcast) << ", monthly fee: $" << podcast.monthlyFee << ", purchased: "
           << podcast.month << "-" << podcast.year << endl;
        return os;
    }
};

class Playlist {
protected:
    string playlistName;
    Podcast * podcasts;
    StreamingPodcast sp;
    int n;
    void copy(const Playlist & playlist){
        this->playlistName = playlist.playlistName;
        this->n = playlist.n;
        this->podcasts = new Podcast[n];
        for(int i = 0; i < n; i++){
            this->podcasts[i] = playlist.podcasts[i];
        }
    }
public:
    Playlist(const string &playlistName) {
        this->playlistName = playlistName;
        this->n = 0;
        this->podcasts = new Podcast[n];
    }
    Playlist(const Playlist & p){
        copy(p);
    }
    ~Playlist(){
        delete[] podcasts;
    }

    Playlist &operator +=(Podcast & p){
        for(int i = 0; i < n; i++){
            if(podcasts[i] == p){
                throw ExistingPodcast(playlistName);
            }
        }
        Podcast * tmp = new Podcast [n+1];
        for(int i = 0; i < n; i++){
            tmp[i] = podcasts[i];
        }
        tmp[n++] = p;
        delete[] podcasts;
        podcasts = tmp;
        return * this;
    }
    double total_spent(){
        double total = 0.0;
        for(int i = 0; i < n; i++){
            total+= podcasts[i].getPrice();
        }
        return total;
    }

    friend istream & operator>>(istream & in, Playlist & p){
        getline(in,p.playlistName);
        for(int i = 0; i < p.n; i++){
            in >> p.podcasts[i];
        }
        return in;
    }

    friend ostream &operator<<(ostream &os, const Playlist &playlist) {
        cout << endl;
        os << "Playlist: "<< playlist.playlistName << endl;
        for(int i = 0; i <playlist.n; i++){
            os << playlist.podcasts[i] << endl;
        }
        return os;
    }
};

int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Podcast
    char podcast_name[100];
    char podcast_url[1000];
    float podcast_price;
    int podcast_discount;

    // for StreamingPodcast
    float sub_podcast_monthly_fee;
    int sub_podcast_month, sub_podcast_year;

    // for Playlist
    char name[100];
    int num_podcasts_in_playlist;

    if (test_case_num == 1){
        cout<<"Testing class Podcast and operator&lt;&lt; for Podcast"<<std::endl;
        cin.get();
        cin.getline(podcast_name,100);
        cin.getline(podcast_url, 1000);
        //cin.get();
        cin>>podcast_price>>podcast_discount;

        Podcast p(podcast_name, podcast_url, podcast_price, podcast_discount);

        cout<<p;
    }
    else if (test_case_num == 2){
        cout<<"Testing class StreamingPodcast and operator&lt;&lt; for StreamingPodcast"<<std::endl;
        cin.get();
        cin.getline(podcast_name,100);
        cin.getline(podcast_url, 1000);
        //cin.get();
        cin>>podcast_price>>podcast_discount;

        cin>>sub_podcast_monthly_fee;
        cin>>sub_podcast_month>>sub_podcast_year;

        StreamingPodcast sp(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
        cout<<sp;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator&gt;&gt; for Podcast"<<std::endl;
        Podcast p;

        cin>>p;

        cout<<p;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator&gt;&gt; for StreamingPodcast"<<std::endl;
        StreamingPodcast sp;

        cin>>sp;

        cout<<sp;
    }
    else if (test_case_num == 5){
        cout<<"Testing class Playlist and operator+= for Playlist"<<std::endl;
        cin.get();
        cin.getline(name,100);
        Playlist u(name);

        int num_user_podcasts;
        int podcast_type;
        cin >>num_user_podcasts;

        try {

            for (int i=0; i<num_user_podcasts; ++i){

                cin >> podcast_type;

                Podcast *g;
                // 1 - Game, 2 - SubscriptionGame
                if (podcast_type == 1){
                    cin.get();
                    cin.getline(podcast_name, 100);
                    cin.getline(podcast_url, 1000);

                    cin>>podcast_price>>podcast_discount;
                    g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
                }
                else if (podcast_type == 2){
                    cin.get();
                    cin.getline(podcast_name, 100);
                    cin.getline(podcast_url, 1000);

                    cin>>podcast_price>>podcast_discount;

                    cin>>sub_podcast_monthly_fee;
                    cin>>sub_podcast_month>>sub_podcast_year;
                    g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }catch(ExistingPodcast &ex){
            ex.message();
        }

        cout<<u;

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingPodcast for Playlist"<<std::endl;
        cin.get();
        cin.getline(name,100);
        Playlist u(name);

        int num_podcasts_in_playlist;
        int podcast_type;
        cin >>num_podcasts_in_playlist;

        for (int i=0; i<num_podcasts_in_playlist; ++i){

            cin >> podcast_type;

            Podcast *g;
            // 1 - Game, 2 - SubscriptionGame
            if (podcast_type == 1){
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin>>podcast_price>>podcast_discount;
                g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
            }
            else if (podcast_type == 2){
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin>>podcast_price>>podcast_discount;

                cin>>sub_podcast_monthly_fee;
                cin>>sub_podcast_month>>sub_podcast_year;
                g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
            }

            //cout<<(*g);
            try {
                u+=(*g);
            }
            catch(ExistingPodcast &ex){
                ex.message();
            }
        }

        cout<<u;
    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for Playlist"<<std::endl;
        cin.get();
        cin.getline(name,100);
        Playlist u(name);

        int num_podcasts_in_playlist;
        int podcast_type;
        cin >>num_podcasts_in_playlist;

        for (int i=0; i<num_podcasts_in_playlist; ++i){

            cin >> podcast_type;

            Podcast *g;
            // 1 - Game, 2 - SubscriptionGame
            if (podcast_type == 1){
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin>>podcast_price>>podcast_discount;
                g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
            }
            else if (podcast_type == 2){
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin>>podcast_price>>podcast_discount;

                cin>>sub_podcast_monthly_fee;
                cin>>sub_podcast_month>>sub_podcast_year;
                g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingPodcast &ex){
                ex.message();
            }
        }

        cout<<u;

        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
}
