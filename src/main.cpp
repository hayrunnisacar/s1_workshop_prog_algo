#include <sil/sil.hpp>
#include "random.hpp"

//Ex 1 : Keep only the green
void only_green(sil::Image& image){
    for (glm::vec3& color : image.pixels()){
        color.r = 0.f;
        color.b = 0.f;
    }
}

//Ex 2 : Swap channels
void change_channels(sil::Image& image){
    for (glm::vec3& color : image.pixels()){
        std::swap(color.r, color.b);
    }
}

//Ex 3 : Black & White
void black_white(sil::Image& image){
    for (glm::vec3& color : image.pixels()){
        float gray = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;

        color.r = gray;
        color.g = gray;
        color.b = gray;
    }
}

//Ex 4 : Negative
//Attention, valeur entre 0-1 et non 0-255
void negative(sil::Image& image){
    for (glm::vec3& color : image.pixels()){
        color.r = 1 - color.r;
        color.g = 1 - color.g;
        color.b = 1 - color.b;
    }
}

//Ex 5 : Gradient
void gradient(sil::Image& image){
    for (int x{0}; x < image.width(); ++x){
        for (int y{0}; y < image.height(); ++y){
            image.pixel(x, y) = glm::vec3{static_cast<float>(x) / static_cast<float>(image.width() - 1)};
        }
    }
}

//Ex 6 : Mirror
void mirror(sil::Image& image){
    for (int x{0}; x < image.width()/2; ++x){
        for (int y{0}; y < image.height(); ++y){
            std::swap(image.pixel(x, y), image.pixel(image.width() - 1 - x, y));
        }
    }
}

//Ex 7 : Noise
void noise(sil::Image& image){
    for (glm::vec3& color : image.pixels()){
        if(true_with_probability(0.2f)){
            color.r = random_float(0.f, 1.f);
            color.g = random_float(0.f, 1.f);
            color.b = random_float(0.f, 1.f);

        }
    }
}

//Ex 8 : Rotation
void rotation(sil::Image& image){
    sil::Image new_image{image.height(), image.width()};

    for (int x{0}; x < image.width(); ++x){
        for (int y{0}; y < image.height(); ++y){
            int const new_x{image.height() - 1 - y};
            int const new_y{x};
            new_image.pixel(new_x, new_y) = image.pixel(x, y);
        }
    }

    image = new_image;
}



int main(){
    sil::Image image{"images/logo.png"};

    //Ex 1
    // only_green(image);
    // image.save("output/ex1_test1.png");
    
    //Ex 2
    // change_channels(image);
    // image.save("output/ex2_test1.png");

    //Ex 3
    // black_white(image);
    // image.save("output/ex3_test1.png");

    //Ex 4
    // negative(image);
    // image.save("output/ex4_test2.png");

    //Ex 5
    // sil::Image image{300, 200};
    // gradient(image);
    // image.save("output/ex5_test1.png");

    //Ex 6
    // mirror(image);
    // image.save("output/ex6_test1.png");

    //Ex 7
    // noise(image);
    // image.save("output/ex7_test1.png");

    //Ex 8
    rotation(image);
    image.save("output/ex8_test1.png");
}