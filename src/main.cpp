#include <sil/sil.hpp>
#include <string>
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

//Ex 9 : RGB Split
void split(sil::Image& image){
    int shift {30};

    sil::Image new_image{image.width(), image.height()};

    for (int x{0}; x < image.width(); ++x){
        for (int y{0}; y < image.height(); ++y){
            
            int x_left{x + shift};
            int x_right{x - shift};

            if (x_right < 0){
                x_right = 0;
            }
            if (x_left > image.width() - 1){
                x_left = image.width() - 1;
            }

            new_image.pixel(x, y).r = image.pixel(x_right, y).r;
            new_image.pixel(x, y).g = image.pixel(x, y).g;
            new_image.pixel(x, y).b = image.pixel(x_left, y).b;
            
        }
    }
    image = new_image;
}

//Ex 10 : Brightness
void brightness(sil::Image& image){
    float const power{1.4f};

    for (glm::vec3& color : image.pixels()){
        color.r = std::pow(color.r, power);
        color.g = std::pow(color.g, power);
        color.b = std::pow(color.b, power);
    }
}

//Ex 11 : Disk
void disk(sil::Image& image){
    int const center_x{image.width()/2};
    int const center_y{image.height()/2};
    int const radius{100};

    for (int x{0}; x < image.width(); ++x){
        for (int y{0}; y < image.height(); ++y){
            int const distance_x{x - center_x};
            int const distance_y{y - center_y};
            int pythagoras {distance_x * distance_x + distance_y * distance_y };

            if(pythagoras <= radius * radius){
                image.pixel(x,y) = glm::vec3{1};
            }
        }
    }
}

//Ex 12 : Circle
void circle(sil::Image& image){
    int const center_x{image.width()/2};
    int const center_y{image.height()/2};
    int const radius{100};

    int const thickness {10};

    for (int x{0}; x < image.width(); ++x){
        for (int y{0}; y < image.height(); ++y){
            int const distance_x{x - center_x};
            int const distance_y{y - center_y};

            int pythagoras {distance_x * distance_x + distance_y * distance_y };
            int radius_pythagoras {radius * radius};

            int radius_thickness {(radius - thickness) * (radius - thickness)};

            if(pythagoras <= radius_pythagoras
                && pythagoras >= radius_thickness){
                image.pixel(x,y) = glm::vec3{1};
            }
        }
    }
}

//Ex 13 : Animation
void animation(){
    int num{0};

    for(int center_x{}; center_x < 500; center_x=center_x+40){
        sil::Image image{500, 500};

        int const center_y{image.height()/2};
        int const radius{100};

        for (int x{0}; x < image.width(); ++x){
            for (int y{0}; y < image.height(); ++y){
                int const distance_x{x - center_x};
                int const distance_y{y - center_y};
                int pythagoras {distance_x * distance_x + distance_y * distance_y };

                if(pythagoras <= radius * radius){
                    image.pixel(x,y) = glm::vec3{1};
                }
            }
        }
        image.save("output/ex13_" + std::to_string(num) + ".png");

        num = num+1;
    }
}



int main(){
    // sil::Image image{"images/logo.png"};
    // sil::Image image{"images/photo.jpg"};

    animation();
}