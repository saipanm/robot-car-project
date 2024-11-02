import cv2
import asyncio
import websockets
import base64
import numpy as np

async def stream_webcam(websocket, path):
    # Open webcam
    cap = cv2.VideoCapture(0)
    
    try:
        while True:
            # Read frame from webcam
            ret, frame = cap.read()
            if not ret:
                break
            
            # Encode frame to JPEG
            _, buffer = cv2.imencode('.jpg', frame)
            # Convert to base64 for transmission
            frame_data = base64.b64encode(buffer).decode('utf-8')
            
            # Send frame over WebSocket
            await websocket.send(frame_data)
            
            # Wait a short period to control the frame rate (e.g., ~30fps)
            await asyncio.sleep(1 / 30)
    except websockets.ConnectionClosed:
        print("Client disconnected")
    finally:
        # Release the webcam when done
        cap.release()

# Main entry to start the WebSocket server
async def main():
    async with websockets.serve(stream_webcam, "0.0.0.0", 8765):
        print("WebSocket server running on ws://0.0.0.0:8765")
        await asyncio.Future()  # Run forever

# Run the server
asyncio.run(main())
