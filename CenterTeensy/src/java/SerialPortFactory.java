import gnu.io.CommPortIdentifier;
import gnu.io.NoSuchPortException;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.UnsupportedCommOperationException;

import java.io.IOException;
import java.util.Enumeration;


public class SerialPortFactory {

    
    public static CommPortIdentifier findCommPortByName(String portName) throws IOException {
        Enumeration<?> portEnum = CommPortIdentifier.getPortIdentifiers();
        while (portEnum.hasMoreElements()) {
            CommPortIdentifier portId = (CommPortIdentifier) portEnum.nextElement();
            if (portId.getName().equals(portName)) 
                return portId;
              
            }
        throw new IOException("Could not find " + portName);
        }
    
    public static SerialPort findSerialPortByName(String portName, int baudRate) throws NoSuchPortException, PortInUseException, UnsupportedCommOperationException {
        CommPortIdentifier portId = CommPortIdentifier.getPortIdentifier(portName);
            // open serial port, and use class name for the appName.
            SerialPort serialPort = (SerialPort) portId.open("Teensy",
                    2000);

            // set port parameters
            serialPort.setSerialPortParams(baudRate,
                    SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_1,
                    SerialPort.PARITY_NONE);
            return serialPort;
    }
}
       

