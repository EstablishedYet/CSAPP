import serial
import time

# Set the serial port parameters
SERIAL_PORT = "COM14"  # Replace with your actual serial port (e.g., COM1, /dev/ttyUSB0)
BAUD_RATE = 115200  # Baud rate for the TTL connection

# Open the serial port
ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)

# Define the command to turn the yaw (left-right rotation)
turn_yaw = 70  
turn_pitch = 20  

# Prepare the command in the format specified by the SDK
send_buf = bytearray([0x55, 0x66, 0x01, 0x04, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x7C, 0xFC, 0x4F, 0xA4])

# Send the data to the gimbal via serial
ser.write(send_buf)

# Wait for acknowledgment (or any response)
time.sleep(1)

# Read the response from the gimbal (if any)
response = ser.read(ser.in_waiting)  # Read available bytes
if response:
    print("Received response:", response.hex())  # Print the response in hexadecimal
else:
    print("No response received.")

# Close the serial connection
ser.close()