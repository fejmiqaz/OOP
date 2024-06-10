#include<iostream>
#include<cstring>
using namespace std;

class Camera {
protected:
    char manufacturer[20];
    char model[20];
    int yearOfProduction;
    float resolution;
public:
    Camera(char *manufacturer, char *model, int yearOfProduction, float resolution) : yearOfProduction(yearOfProduction), resolution(resolution) {
        strcpy(this->manufacturer,manufacturer);
        strcpy(this->model,model);
    }
    virtual double price() const = 0;
    virtual double rentalPrince(int days) const = 0;

    bool operator<(const Camera & c){
        return price() < c.price();
    }
};

class PhotoCamera : public Camera {
protected:
    bool supportsRAW;
public:
    PhotoCamera(char *manufacturer, char *model, int yearOfProduction, float resolution, bool supportsRaw) : Camera(
            manufacturer, model, yearOfProduction, resolution), supportsRAW(supportsRaw) {}

    double rentalPrince(int days) const override {
        PhotoCamera::price() * (1/100);
        if(days > 7){
            PhotoCamera::price() * 0.80;
        }
        return PhotoCamera::price();
    }

    double price() const override {
        double price = 0;
        price = 100 + resolution * 20.0;
        if(supportsRAW){
            price += 50.0;
        }
        return price;
    }
};

class VideoCamera : public Camera {
protected:
    int maxLength;
public:
    VideoCamera(char *manufacturer, char *model, int yearOfProduction, float resolution, int maxLength) : Camera(
            manufacturer, model, yearOfProduction, resolution), maxLength(maxLength) {}

    double rentalPrince(int days) const override {
        VideoCamera::price() * (1/100);
        if(days > 7){
            VideoCamera::price() * 0.80;
        }
        return VideoCamera::price();
    }

    double price() const override {
        double price = resolution * 80.0;
        if(maxLength > 60){
            price = price + price * 0.40;
        }
        return price;
    }
};

class FilmCamera : public Camera {
protected:
    int maxFPS;
public:
    FilmCamera(char *manufacturer, char *model, int yearOfProduction, float resolution, int maxFps) : Camera(
            manufacturer, model, yearOfProduction, resolution), maxFPS(maxFps) {}

    double rentalPrince(int days) const override {
        double price = 500.0;
        if(maxFPS > 60){
            price * 2.0;
        }
        return price;
    }

    double price() const override {
        double price = 5000.0;
        if (maxFPS > 30) {
            int n = 0;
            for (int i = 30; i < maxFPS; i++) {
                n++;
            }
            price += n * 5000.0;
        }
        return price;
    }
};

//TODO: Need to work on this method
double production(Camera ** c, int n, int days){
    double price = 0.0;
    for(int i = 0; i < n; i++){
        price += c[i]->rentalPrince(days);
    }
    return price;
}
//TODO: Need to work on this method aswell
Camera mostExpensiveCamera(Camera ** c, int n){}

int main(){
    // Variables for reading input
    char model[20], producer[20];
    int year, length, fps, n;
    float resolution;
    bool raw;

    int t;

    // Array of cameras
    Camera *c [10];

    // Read number of cameras
    cin>>n;

    for(int i = 0; i < n; ++i){

        // Camera type: 1 - Photo, 2 - Video, 3 - Film
        cin>>t;

        if (t==1){
            cin >> producer >> model >> year >> resolution;
            cin >> raw;
            c[i] = new PhotoCamera(producer, model, year, resolution, raw);
        }
        else if (t==2){
            cin >> producer >> model >> year >> resolution;
            cin >> length;
            c[i] = new VideoCamera(producer, model, year, resolution, length);
        }
        else if (t==3){
            cin >> producer >> model >> year >> resolution;
            cin >> fps;
            c[i] = new FilmCamera(producer, model, year, resolution, fps);
        }
    }


    // Production days
    int days;
    cin >> days;


    cout<<"\n" << "Price of production is: " << production(c, n, days);
    cout<<"\n" << "Most expensive camera used in production is: " << mostExpensiveCamera(c, n);


    return 0;
}