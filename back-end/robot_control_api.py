from flask import Flask, jsonify, request
from flask_restful import Resource, Api
import serial
import time

# Set up serial connection to the esp (adjust as needed)
try:
    ser = serial.Serial('/dev/cu.URT0', 9600, timeout=1)  # Adjust with the correct serial port
    time.sleep(2)  # Allow time for the connection to initialize
except serial.SerialException:
    ser = None
    print("Error: Could not open serial connection. Check the port.")

# Initialize Flask app and API
app = Flask(__name__)
api = Api(app)

# Function to send a command to the esp
def send_command(command):
    if ser and ser.is_open:
        ser.write((command + "\n").encode('utf-8'))  # Send command with newline character
        print(f"Sent to esp: {command}")

        # Wait for esp response
        response = ser.readline().decode('utf-8', errors='ignore').strip()
        if response:
            print(f"esp response: {response}")
            return response
        else:
            print("No response from esp.")
            return "No response"
    else:
        print("Error: Serial connection is not open.")
        return "No connection"

# Define the movement resource
class MoveResource(Resource):
    def post(self):
        """POST request to move the robot in the specified direction."""
        data = request.json
        direction = data.get("direction")

        if not direction:
            return {"error": "No direction provided"}, 400

        valid_directions = ["forward", "reverse", "left", "right", "stop"]
        if direction not in valid_directions:
            return {"error": "Invalid direction"}, 400

        response = send_command(direction)
        return {"status": f"moving {direction}", "response": response}

# Define the status resource
class StatusResource(Resource):
    def get(self):
        """GET request to check API and serial connection status."""
        connection_status = "connected" if ser and ser.is_open else "disconnected"
        return {"status": "API is running", "serial_connection": connection_status}

# Add resources to the API
api.add_resource(MoveResource, '/api/move')
api.add_resource(StatusResource, '/api/status')

# Run the Flask app
if __name__ == '__main__':
    try:
        print("Starting Flask API for robot control...")
        app.run(host='0.0.0.0', port=1212, debug=True, threaded=True)
    except KeyboardInterrupt:
        print("Shutting down due to KeyboardInterrupt.")
    finally:
        if ser and ser.is_open:
            ser.close()  # Close the serial connection on exit
