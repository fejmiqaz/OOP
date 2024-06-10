#include<iostream>
#include<cstring>
using namespace std;

class Podcast{
    char name[100];
    char *url;
    double cost;
    int discount;
    void copy(const Podcast & p){
        strcpy(name, p.name);
        strcpy(url,p.url);
        discount = p.discount;
        cost = p.cost;
    }
    public:
    Podcast(char *name = "", char *url= "", double cost = 0, int discount = 0){
        strcpy(this->name,name);
        strcpy(this->url, url);
        this->cost = cost;
        this->discount = discount;
    }
    Podcast(const Podcast & other){
        copy(other);
    }

    double getCost() const {
        return cost;
    }

    friend istream& operator>>(istream & in, Podcast & other){
        in.getline(other.name, 100);
        in.getline(other.url,1000);
        in >> other.cost >> other.discount;
        in.ignore();
        return in;
    }

    };

class StreamingPodcast{
private:
    double monthlyFee;
    int month, year;
    void copy(const StreamingPodcast & sp){
        monthlyFee = sp.monthlyFee;
        month = sp.month;
        year = sp.year;
    }
public:
    StreamingPodcast(double monthlyFee = 0, int month = 1, int year = 2000) {
        this->monthlyFee = monthlyFee;
        this->month = month;
        this->year = year;
    }
    StreamingPodcast(const StreamingPodcast & other){
        copy(other);
    }
    friend istream& operator>>(istream & in, StreamingPodcast & sp){
        in >> sp.monthlyFee >> sp.month >> sp.year;
        return in;
    }
    };

class Playlist{
private:
    char name[100];
    Podcast * podcast;
    int n;
    void copy(const Playlist & p){
        strcpy(name, p.name);
        n = p.n;
        podcast = new Podcast[this->n];
        for(int i = 0; i < this->n; i++){
            this->podcast[i] = p.podcast[i];
        }
    }

public:
    Playlist(char *name = "", int n = 0){
        strcpy(this->name,name);
        this->n = n;
        podcast = new Podcast[0];
    }
    Playlist(const Playlist & other){
        copy(other);
    }

    Playlist & operator=(const Playlist & other){
        if(this!=&other){
            delete[] podcast;
            copy(other);
        }
        return * this;
    }

    Playlist & operator+=(const Podcast & other){
        Podcast * temp = new Podcast[n+1];
        for(int i = 0; i < n; i++){
            temp[i] = podcast[i];
        }
        temp[n++] = other;
        delete[] podcast;
        this->podcast = new Podcast[n];
        for(int i = 0; i < n; i++){
            this->podcast[i] = temp[i];
        }
        delete[] temp;
        return * this;
    }

    double total_spent(Playlist & p){
        double sum = 0;
        for(int i = 0; i < p.n; i++){
            sum += p.podcast[i].getCost();
        }
        return sum;
    }

    };


int main(){
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
        cout<<"Testing class Podcast and operator<< for Podcast"<<std::endl;
        cin.get();
        cin.getline(podcast_name,100);
        cin.getline(podcast_url, 1000);
        //cin.get();
        cin>>podcast_price>>podcast_discount;

        Podcast p(podcast_name, podcast_url, podcast_price, podcast_discount);

        cout<<p;
    }
    else if (test_case_num == 2){
        cout<<"Testing class StreamingPodcast and operator<< for StreamingPodcast"<<std::endl;
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
        cout<<"Testing operator>> for Podcast"<<std::endl;
        Podcast p;

        cin>>p;

        cout<<p;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator>> for StreamingPodcast"<<std::endl;
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

    return 0;
}