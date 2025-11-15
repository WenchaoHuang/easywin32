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
#include <thread>
#include <vector>
#include <easywin32.h>

/*********************************************************************************
***********************************    main    ***********************************
*********************************************************************************/

extern void flagsTest();
extern void mouseEventTest(EzWindow & window);
extern void keyboardEventTest(EzWindow & window);

int main()
{
	EzWindow window;
	window.open("EasyWin32-Test", EzRect{ 100, 100, 900, 700 }, EzStyle::OverlappedWindow, EzExStyle::AcceptFiles);
	window.centerToScreen();
	window.show();

	std::vector<EzColorRGB> image(1920 * 1080, EzColorRGB{ 100, 200, 255 });

	//	Draw background
	window.onPaint = [&]()
	{
		window.drawBitmap(image.data(), 1920, 1080);

		return 0;
	};

	window.onDropFiles = [](const std::vector<easywin32::string_type> & filePaths)
	{
		for (size_t i = 0; i < filePaths.size(); i++)
		{
			printf("Drop file[%lld]: %s\n", i, filePaths[i].c_str());
		}

		return -1;
	};

	auto t0 = std::chrono::steady_clock::now();

	window.onTimer = [&](UINT_PTR id)
	{
		auto t1 = std::chrono::steady_clock::now();

		printf("Time = %fs\n", (t1 - t0).count() * 1e-9);

		return 0;
	};

	window.setTimer(0, 1000);

	flagsTest();
	mouseEventTest(window);
	keyboardEventTest(window);

	//	Setup callbacks
	window.onKeyboardPress = [&](EzKey key, EzKeyAction action)
	{
		if ((key == EzKey::Escape) && (action == EzKeyAction::Press))
		{
			window.close();
		}

		return 0;
	};

	//	Main loop
	while (window.isOpen())
	{
		if (!window.processEvents())
		{
			using namespace std::chrono_literals;

			std::this_thread::sleep_for(1ms);
		}
	}

	return 0;
}