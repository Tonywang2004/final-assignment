#include "Server.h"
#pragma comment(lib, "ws2_32.lib")


int main()
{
	TCPServer t;
	t.AcceptConnection();
}