
#include <iostream>
#include "desktop_capturer_wrapper.h"
#include "desktop_capturer_callback.h"

using namespace std;




int main() {
	cout << "hi\n";
	desktop_capturer_wrapper capturer;
	desktop_capturer_callback callback;
	capturer.start(&callback);
	capturer.capture();
	return 0;
}