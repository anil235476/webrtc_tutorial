
#include <iostream>
#include "desktop_capturer_wrapper.h"

using namespace std;




int main() {
	cout << "hi\n";
	desktop_capturer_wrapper capturer;
	capturer.start(nullptr);
	capturer.capture();
	return 0;
}