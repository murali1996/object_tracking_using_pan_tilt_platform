#include <SerialStream.h>
using namespace LibSerial ;
SerialStream my_serial_stream ;

int main(int argc, char **argv)
{
my_serial_stream.Open( "/dev/ttyACM0" ) ;
my_serial_stream.SetBaudRate(SerialStreamBuf::BAUD_9600);  
my_serial_stream.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
my_serial_stream << 'w' ;
return 0;
}
