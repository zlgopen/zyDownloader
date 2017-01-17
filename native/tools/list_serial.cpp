#include <iostream>
#include "serial/serial.h"
//
// 列出当前可用的串口。
//
int main() {
	std::vector<serial::PortInfo> ports = serial::list_ports();
	size_t len = ports.size();
	for(size_t i = 0; i < len; i++) {
		serial::PortInfo pi = ports[i];
		std::cout << pi.port <<" " << pi.description << " " << pi.hardware_id << std::endl;
	}

	return 0;
}
