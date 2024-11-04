# Robot Control API

This project provides a Flask-based API to control a robot car via an ESP8266 microcontroller using serial communication.

## Prerequisites

1. **Python**: Ensure you have Python installed on your system.
2. **Flask**: Install Flask and other dependencies by running `pip install -r requirements.txt` after cloning the repository.

## Installation

1. **Clone the Repository**:
    ```bash
    git clone <repository-url>
    cd <repository-directory>
    ```

2. **Install Dependencies**:
    ```bash
    pip install -r requirements.txt
    ```

## Configuration

1. **Set Up Serial Connection**:
    - Ensure the ESP8266 is connected to the correct serial port.
    - Adjust the serial port in the code if necessary:
      ```python
      ser = serial.Serial('/dev/serial0', 9600, timeout=1)  # Replace '/dev/serial0' with the actual port
      ```

## Running the API

1. **Start the Flask API**:
    ```bash
    flask run
    ```
    Alternatively, for a production environment, you can use `gunicorn`:
    ```bash
    gunicorn -w 4 -b 0.0.0.0:1212 robot_control_api:app
    ```

## API Endpoints

### 1. Move the Robot

- **Endpoint**: `/api/move`
- **Method**: `POST`
- **Description**: Moves the robot in the specified direction.
- **Request Body**:
    ```json
    {
        "direction": "forward" | "reverse" | "left" | "right" | "stop"
    }
    ```
- **Response**:
    ```json
    {
        "status": "moving <direction>",
        "response": "<response from esp>"
    }
    ```

### 2. Check API and Serial Connection Status

- **Endpoint**: `/api/status`
- **Method**: `GET`
- **Description**: Checks the status of the API and the serial connection.
- **Response**:
    ```json
    {
        "status": "API is running",
        "serial_connection": "connected" | "disconnected"
    }
    ```

## Code Explanation

### Serial Communication

The function **`send_command`** sends a command to the ESP8266 and waits for a response.

    ```python
    def send_command(command):
        if ser and ser.is_open:
            ser.write((command + "\n").encode('utf-8'))
            response = ser.readline().decode('utf-8', errors='ignore').strip()
            return response if response else "No response"
        else:
            return "No connection"
    ```

### API Resources

- **MoveResource**: Handles POST requests to move the robot.
    ```python
    class MoveResource(Resource):
        def post(self):
            data = request.json
            direction = data.get("direction")
            if not direction:
                return {"error": "No direction provided"}, 400
            valid_directions = ["forward", "reverse", "left", "right", "stop"]
            if direction not in valid_directions:
                return {"error": "Invalid direction"}, 400
            response = send_command(direction)
            return {"status": f"moving {direction}", "response": response}
    ```

- **StatusResource**: Handles GET requests to check the API and serial connection status.
    ```python
    class StatusResource(Resource):
        def get(self):
            connection_status = "connected" if ser and ser.is_open else "disconnected"
            return {"status": "API is running", "serial_connection": connection_status}
    ```
