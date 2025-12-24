
import std;
import Win32;

int main()
{

    std::string title   = "Hello Habr!";
    std::string message = "Crazy programming!";

    MessageBoxA(GetActiveWindow(), title.c_str(), message.c_str(), 0x00000000L);

    ExitProcess(0);

	return 0;
}
