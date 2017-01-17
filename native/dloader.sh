
URL="tcp://localhost/./data.bin?server=localhost&port=9988"
URL="tftp_server://localhost/./data.bin?server=localhost&port=10220"
URL="serial://localhost/./data.bin?device=/dev/tty.wchusbserial14120&baudrate=115200&bytesize=8&stopbits=1&flowcontrol=0&parity=0"

./build/bin/dloader "$URL"
