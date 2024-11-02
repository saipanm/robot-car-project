import React, { useEffect, useRef, useState } from 'react';

const Video = () => {
  const websocketUrl = `ws://${window.location.hostname}:8765`;
  const [connected, setConnected] = useState(false);
  const canvasRef = useRef(null);

  useEffect(() => {
    // Adjust the canvas size to fit the window size
    const resizeCanvas = () => {
      const canvas = canvasRef.current;
      canvas.width = window.innerWidth;
      canvas.height = (window.innerWidth * 480) / 640; // Maintains aspect ratio of 640x480
    };

    resizeCanvas(); // Set initial size
    window.addEventListener('resize', resizeCanvas); // Adjust on resize

    // Create a WebSocket connection
    const ws = new WebSocket(websocketUrl);

    ws.onopen = () => {
      console.log('Connected to WebSocket server');
      setConnected(true);
    };

    ws.onmessage = (event) => {
      const imgSrc = `data:image/jpeg;base64,${event.data}`;
      const img = new Image();
      img.src = imgSrc;

      img.onload = () => {
        const canvas = canvasRef.current;
        const context = canvas.getContext('2d');
        context.clearRect(0, 0, canvas.width, canvas.height);
        context.drawImage(img, 0, 0, canvas.width, canvas.height);
      };
    };

    ws.onclose = () => {
      console.log('Disconnected from WebSocket server');
      setConnected(false);
    };

    ws.onerror = (error) => {
      console.error('WebSocket error:', error);
    };

    // Cleanup on component unmount
    return () => {
      ws.close();
      window.removeEventListener('resize', resizeCanvas); // Cleanup event listener
    };
  }, [websocketUrl]);

  return (
    <div className="video-stream-container">
      <canvas ref={canvasRef} style={{ border: 'none' }} />
      
    </div>
  );
};

export default Video;
