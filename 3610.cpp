#include <iostream>
#include <string>

using namespace std;

int main()
{
	int T;
	string b,g,x;

	cin >> T;

	while (T--) {
		cin >> b >> g >> x;

		cout << g << " will survive" << endl;  // girl always win
	}

	return 0;
}