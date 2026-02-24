#include <iostream>

using namespace std;

int main()
{
	string name;
	while (true) {
		cin >> name;
		if (name == "END") break;		
		
		else{
			cout << "Hello "<< name << "!" << endl;  //code added here
		}

	}
}

