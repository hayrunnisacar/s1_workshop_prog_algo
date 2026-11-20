#include <sil/sil.hpp>
#include <string>
#include "random.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <complex>

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

//Ex 14 : Rosette
void rosette(sil::Image& image){
    int const image_center_x{image.width()/2};
    int const image_center_y{image.height()/2};
    int const radius{100};
    int const thickness {10};

    for(int num{0}; num <= 6; ++num){
        int circle_x{image_center_x};
        int circle_y{image_center_y};

        if (num > 0){
            float const angle{num*2.f*3.14159f/6.f};
            circle_x = image_center_x + radius * std::cos(angle);
            circle_y = image_center_y + radius * std::sin(angle);
        }

        for (int x{0}; x < image.width(); ++x){
            for (int y{0}; y < image.height(); ++y){
                int const distance_x{x - circle_x};
                int const distance_y{y - circle_y};

                int const pythagoras{distance_x * distance_x + distance_y * distance_y};
                int const radius_pythagoras{radius * radius};
                int const radius_thickness{(radius - thickness) * (radius - thickness)};

                if (pythagoras <= radius_pythagoras
                    && pythagoras >= radius_thickness){
                    image.pixel(x, y) = glm::vec3{1};
                }
            }
        }
    }
}

//Ex 15 : Mosaic
void mosaic(sil::Image& image){
    sil::Image new_image{image.width(), image.height()};
    int const copy{5};

    for (int x{0}; x < image.width(); ++x){
        for (int y{0}; y < image.height(); ++y){
            int const source_x{
                (x * copy) % image.width()
            };
            int const source_y{
                (y * copy) % image.height()
            };

            new_image.pixel(x, y) = image.pixel(source_x, source_y);
        }
    }
    image = new_image;
}

//Ex 16 : Glitch
void glitch(sil::Image& image){
    for (int n{0}; n < 70; ++n){
        int width{
            random_int(5, 50)
        };
        int height{
            random_int(1, 10)
        };

        int ax{
            random_int(0, image.width() - width)
        };
        int ay{
            random_int(0, image.height() - height)
        };
        int bx{
            random_int(0, image.width() - width)
        };
        int by{
            random_int(0, image.height() - height)
        };

        for (int i{0}; i < width; ++i){
            for (int j{0}; j < height; ++j){
                std::swap(image.pixel(ax + i, ay + j), image.pixel(bx + i, by + j));
            }
        }
    }
}

//Ex 17 : Sort pixels
float sort_brightness(glm::vec3 const& color){
    return 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
}
//Num 1
void sort_all_pixels(sil::Image& image){
    std::sort(
        image.pixels().begin(),
        image.pixels().end(),
        [](glm::vec3 const& color1, glm::vec3 const& color2){
            return sort_brightness(color1) < sort_brightness(color2);
        }
    );
}
//Num 2
void sort_lines_pixel(sil::Image& image){
    for (int y{0}; y < image.height(); ++y){
        std::sort(
            image.pixels().begin() + y * image.width(),
            image.pixels().begin() + (y + 1) * image.width(),
            [](glm::vec3 const& color1, glm::vec3 const& color2){
                return sort_brightness(color1) < sort_brightness(color2);
            }
        );
    }
}
//Num 3
void sort_random_pixel(sil::Image& image){
    for (int y{0}; y < image.height(); ++y){
        int const start{
            random_int(0, (image.width() - 1))
        };
        int const end{
            random_int(start, (image.width()))
        };

        std::sort(
            image.pixels().begin() + y * image.width() + start,
            image.pixels().begin() + y * image.width() + end,
            [](glm::vec3 const& color1, glm::vec3 const& color2){
                return sort_brightness(color1) < sort_brightness(color2);
            }
        );
    }
}

//Ex 18 : Fractal
void fractal(sil::Image& image){
    sil::Image new_image{image.width(), image.height()};
    int const max_iterations{50};

    for (int x{0}; x < image.width(); ++x){
        for (int y{0}; y < image.height(); ++y){
            std::complex<float> c{
                (static_cast<float>(x) / image.width() - 0.5f)*2.5f - 0.6f,
                (static_cast<float>(y) / image.height() - 0.5f)*2.5f
            };
            std::complex<float> z{0.f, 0.f};

            bool in_fractal{true};

            for (int i{0}; i < max_iterations; ++i){
                z = z * z + c;
                if (std::abs(z) > 2){
                    in_fractal = false;
                    break;
                }
            }

            if (in_fractal){
                new_image.pixel(x,y) = glm::vec3{1};
            }
        }
    }
    image = new_image;
}



int main(){
    // sil::Image image{"images/logo.png"};
    // sil::Image image{"images/photo.jpg"};

    sil::Image image{500, 500};
    fractal(image);
    image.save("output/ex18_test1.png");
}