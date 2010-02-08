#ifndef GOSU_EXT_BEZIERCURVES_HPP
#define GOSU_EXT_BEZIERCURVES_HPP

#include <Gosu/Gosu.hpp>

#include <GL/glew.h>
#ifdef _MSC_VER
	#pragma comment(lib, "glew32.lib")
#endif

#include <vector>

#define SEGMENT_START1 1
#define SEGMENT_START2 2
#define SEGMENT_MID1 3
#define SEGMENT_MID2 4
#define SEGMENT_END1 5
#define SEGMENT_END2 6

namespace Gosu
{

	class BezierCurves
	{
	

	public:

		static void drawCubicBezierCurve(Graphics &graphics,
										 float x0, 
										 float y0, 
										 float x1, 
										 float y1,
										 float x2, 
										 float y2, 
										 float x3,
										 float y3, 
										 float w,
										 float r,
										 float g, 
										 float b,
										 float a, 
										 int segments)
		{
			graphics.beginGL();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
			Gosu::PostProcessing local(graphics);
			static Gosu::ShaderProgram program = local.compile(Gosu::sharedResourcePrefix() + L"shader/bezier/bezier.frag",
															   Gosu::sharedResourcePrefix() + L"shader/bezier/cubicBezier.vert");
			glUseProgram(program.program);

			glUniform4f(glGetUniformLocation(program.program, "c1"), x0, y0, 0.0f, 0.0f);
			glUniform4f(glGetUniformLocation(program.program, "c2"), x1, y1, 1.0f, 0.0f);
			glUniform4f(glGetUniformLocation(program.program, "c3"), x2, y2, 1.0f, 0.0f);
			glUniform4f(glGetUniformLocation(program.program, "c4"), x3, y3, 1.0f, 0.0f);
			glUniform1f(glGetUniformLocation(program.program, "width"), w/2);
			glUniform1f(glGetUniformLocation(program.program, "step"), 1.0 / (float) segments);


			glUniform4f(glGetUniformLocation(program.program, "color"), r/255, g/255, b/255, a/255);

			//glColor4f (r, g, b, a);
			glBegin(GL_QUAD_STRIP);
			
			glVertex3f(SEGMENT_START1, -1.0f, 0.0f);
			glVertex3f(SEGMENT_START2, -1.0f, 0.0f);
			
			for(int i = 0; i <= segments; i++)
			{
				//glUniform1f(glGetUniformLocation(program.program, "lvl"), i / (float) segments);
				glVertex3f(SEGMENT_MID1, (float)i, (float)i / (float) segments);
				glVertex3f(SEGMENT_MID2, (float)i, (float)i / (float) segments);
			}

			//glUniform1f(glGetUniformLocation(program.program, "lvl"), 1.0f);

			glVertex3f(SEGMENT_END1, -1.0f, 1.0f);
			glVertex3f(SEGMENT_END2, -1.0f, 1.0f);


			glVertex3f(100, 101.0f, 1.0f);
			glVertex3f(101, 100.0f, 1.0f);
			glVertex3f(200, 100.0f, 1.0f);
			glVertex3f(200, 101.0f, 1.0f);

			glEnd();
	
			glUseProgram(0);
			glDisable(GL_BLEND);
			graphics.endGL();

		};

	};
}

#endif