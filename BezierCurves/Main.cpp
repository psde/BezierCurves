#include "Gosu.hpp"

using namespace std;

class Window : public Gosu::Window
{
	private:
		Gosu::Font *font;
		Gosu::fpsCounter *fps;

	public:
		Window()
		 :	Gosu::Window(1024, 768, false)
		{
			glewInit();
			this->font = new Gosu::Font(graphics(), Gosu::defaultFontName(), 20);
			this->fps = new Gosu::fpsCounter(&graphics(), Gosu::realWidth(graphics())-205, 5, 200, 100);

		}

		void draw()
		{
			float height = Gosu::realHeight(graphics());
			float width = Gosu::realWidth(graphics());
			for(int i=0;i<250;i++)
			{
				Gosu::BezierCurves::drawCubicBezierCurve(graphics(), Gosu::random(0,width), Gosu::random(0,height), Gosu::random(0,width), Gosu::random(0,height), Gosu::random(0,width), Gosu::random(0,height), Gosu::random(0,width), Gosu::random(0,height), Gosu::random(1, 8), Gosu::random(0,255), Gosu::random(0,255), Gosu::random(0,255), Gosu::random(10,125), 64);
			}

			fps->updateFPS();
			fps->draw();
		}

		void update()
		{

		}

		void buttonDown(Gosu::Button button)
		{
			if(button == Gosu::kbEscape) close();
		}
};

int main(int argc, char* argv[])
{

    Window win;
    win.show();

	return 0;
}
