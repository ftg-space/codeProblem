#include <SFML/Graphics.hpp>
#include <cmath>
#include <time.h>
clock_t t=clock();
class RGB
{
public:
	unsigned char R;
	unsigned char G;
	unsigned char B;

	RGB(unsigned char r, unsigned char g, unsigned char b)
	{
		R = r;
		G = g;
		B = b;
	}

	bool Equals(RGB rgb)
	{
		return (R == rgb.R) && (G == rgb.G) && (B == rgb.B);
	}
};

class HSL
{
public:
	int H;
	float S;
	float L;

	HSL(int h, float s, float l)
	{
		H = h;
		S = s;
		L = l;
	}

	bool Equals(HSL hsl)
	{
		return (H == hsl.H) && (S == hsl.S) && (L == hsl.L);
	}
};

static float HueToRGB(float v1, float v2, float vH) {
	if (vH < 0)
		vH += 1;

	if (vH > 1)
		vH -= 1;

	if ((6 * vH) < 1)
		return (v1 + (v2 - v1) * 6 * vH);

	if ((2 * vH) < 1)
		return v2;

	if ((3 * vH) < 2)
		return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

	return v1;
}

static RGB HSLToRGB(HSL hsl) {
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;

	if (hsl.S == 0)
	{
		r = g = b = (unsigned char)(hsl.L * 255);
	}
	else
	{
		float v1, v2;
		float hue = (float)hsl.H / 360;

		v2 = (hsl.L < 0.5) ? (hsl.L * (1 + hsl.S)) : ((hsl.L + hsl.S) - (hsl.L * hsl.S));
		v1 = 2 * hsl.L - v2;

		r = (unsigned char)(255 * HueToRGB(v1, v2, hue + (1.0f / 3)));
		g = (unsigned char)(255 * HueToRGB(v1, v2, hue));
		b = (unsigned char)(255 * HueToRGB(v1, v2, hue - (1.0f / 3)));
	}

	return RGB(r, g, b);
}
void Drawing(sf::RenderWindow& m_window, const double dt=1)
{

                for(int i =1e3;i--;){

                    sf::RectangleShape shape;
                    shape.setSize({i,dt-i});
                    shape.move(1e3/2+(i-(dt))*std::cos(i-(dt)),1e3/2+(i-(dt))*std::sin(i-(dt)));
                    HSL data=HSL(((int)(dt*22)+i/3)%360,0.80f,0.30f);
                    RGB value=HSLToRGB(data);
                    sf::Color color(value.R,value.G,value.B);
                    shape.setFillColor(color);
                    m_window.draw(shape);

                }
}

int main()
{


    sf::RenderWindow window;
    window.create(sf::VideoMode(1920, 1080), "SFML works!",sf::Style::Default);
    window.setFramerateLimit(60);
    window.setPosition({0,0});

    double dt=0;
    while (window.isOpen())
    {


        window.clear();
        dt=(clock()-t)/(double) CLOCKS_PER_SEC;
        Drawing(window,dt);
        window.display();

    }

    return 0;
}
