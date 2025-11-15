/**
 *	Copyright (c) 2025 Wenchao Huang <physhuangwenchao@gmail.com>
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in all
 *	copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	SOFTWARE.
 */

#include <chrono>
#include <vector>
#include <easywin32.h>

/*********************************************************************************
********************************    julia_set    *********************************
*********************************************************************************/

struct Complex
{
	float x, y;
};


Complex complex_sqr(Complex z)
{
	Complex res;
	res.x = (z.x * z.x) - (z.y * z.y);
	res.y = 2.0f * z.x * z.y;
	return res;
}


void paint_kernel(EzColorRGB * pixels, int width, float invN, float t, int num)
{
#pragma omp parallel for
	for (int tid = 0; tid < num; tid++)
	{
		int i = tid % width;
		int j = tid / width;

		Complex c = { -0.8f, cosf(t) * 0.2f };

		float real = (i * invN - 1.0f) * 2.0f;
		float imag = (j * invN - 0.5f) * 2.0f;

		Complex z = { real, imag };
		int iterations = 0;

		while (iterations < 50 && (z.x * z.x + z.y * z.y) < 400.0f)
		{
			Complex z_sq = complex_sqr(z);
			z.x = z_sq.x + c.x;
			z.y = z_sq.y + c.y;
			iterations++;
		}

		float value = 1.0f - iterations * 0.02f;
		unsigned char color255 = static_cast<unsigned char>(value * 255);

		pixels[tid] = EzColorRGB{ color255, color255, color255 };
	}
}


int main()
{
	const int n = 512;
	const int width = n * 2;
	const int height = n;
	const size_t num_pixels = width * height;
	std::vector<EzColorRGB>		pixels(num_pixels);

	EzWindow window;
	window.open("Julia Set", EzSize{ width, height });
	window.centerToScreen();
	window.show();

	window.onPaint = [&]()
	{
		window.drawBitmap(pixels.data(), width, height);

		return 0;
	};

	window.onKeyboardPress = [&](EzKey key, EzKeyAction action)
	{
		if ((key == EzKey::Escape) && (action == EzKeyAction::Press))
		{
			window.close();
		}

		return 0;
	};

	int i = 0;
	int frames = 0;
	using namespace std::chrono_literals;
	auto t0 = std::chrono::steady_clock::now();
	
	while (window.isOpen())
	{
		window.processEvents();

		////////////////////////////////////////////////////////////

		float t = (i++) * 0.03f;

		paint_kernel(pixels.data(), width, 1.0f / height, t, num_pixels);

		window.requestRedraw();

		frames++;

		auto t1 = std::chrono::steady_clock::now();

		if (t1 - t0 > 0.5s)
		{
			int fps = int(frames * 1e9f / (t1 - t0).count());

			std::string text = "Julia Set (" + std::to_string(fps) + " FPS)";

			window.setTitle(text);

			frames = 0;

			t0 = t1;
		}
	};

	return 0;
}