//------------------------------------------------------------------------------
// main.cc
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "snowflakeapp.h"

int main(int argc, const char** argv) {
	SnowflakeApp::SnowflakeApp app;
	if (app.Open())
	{
		app.Run();
		app.Close();
	}
	app.Exit();
}