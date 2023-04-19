#include "Application.h"

int main(int argc, char* argv[])
{
	try {
		Application app;
		app.OnExecute();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
