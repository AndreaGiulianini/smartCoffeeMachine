package seriale;

import seriale.CommChannel;
import java.io.*;
import java.util.concurrent.*;
import jssc.*;

/**
 * Comm channel implementation based on serial port.
 * 
 * @author aricci
 *
 */
public class SerialCommChannel implements CommChannel, SerialPortEventListener {

	private SerialPort serialPort;
	private BlockingQueue<String> queue;

	public SerialCommChannel(String port, int rate) throws Exception {
		queue = new ArrayBlockingQueue<String>(100);

		serialPort = new SerialPort(port);
		try {
		    serialPort.openPort();

		    serialPort.setParams(rate,
		                         SerialPort.DATABITS_8,
		                         SerialPort.STOPBITS_1,
		                         SerialPort.PARITY_NONE);

		    serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | 
		                                  SerialPort.FLOWCONTROL_RTSCTS_OUT);

		    // serialPort.addEventListener(this, SerialPort.MASK_RXCHAR);
			serialPort.addEventListener(this);

		}
		catch (SerialPortException ex) {
		    System.out.println("There are an error on writing string to port т: " + ex);
		}
		
		// add event listeners

	}

	@Override
	public void sendMsg(String msg) {
		char[] array = (msg+"\n").toCharArray();
		byte[] bytes = new byte[array.length];
		for (int i = 0; i < array.length; i++){
			bytes[i] = (byte) array[i];
		}
		try {
			serialPort.writeBytes(bytes);
		} catch(Exception ex){
			ex.printStackTrace();
		}
	}

	@Override
	public String receiveMsg() throws InterruptedException {
		// TODO Auto-generated method stub
		return queue.take();
	}

	@Override
	public boolean isMsgAvailable() {
		// TODO Auto-generated method stub
		return !queue.isEmpty();
	}

	/**
	 * This should be called when you stop using the port.
	 * This will prevent port locking on platforms like Linux.
	 */
	public void close() {
		try {
			if (serialPort != null) {
				serialPort.removeEventListener();
				serialPort.closePort();
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	/**
	 * Handle an event on the serial port. Read the data and print it.
	 */
	public void serialEvent(SerialPortEvent event) {
        if (event.isRXCHAR()) {
            try {
                String msg = serialPort.readString(event.getEventValue());
				queue.put(msg);
            }
            catch (Exception ex) {
                System.out.println("Error in receiving string from COM-port: " + ex);
            }
        }
	}


}
