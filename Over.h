#pragma once
#include "Resource.h"

#include <string>
#include <vector>

using std::string; using std::vector;


namespace OVER
{
	struct TextArg
	{
		string text;
		int x;
		int y;

		int a;
		int r;
		int g;
		int b;
	};

	extern vector<TextArg> TextArguments;

	void Setup();
	bool ProcessMessages();
};
