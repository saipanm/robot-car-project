import React from 'react';
import './dpad.css'
import gifpokemon from './assets/4OKl.gif'

const App = () => {
  //ส่งคำสั่ง control
  const sendCommand = async (command) => {
    try {
      const response = await fetch('http://localhost:5000/api/robot/control', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({ command }),
      });

      if (response.ok) {
        console.log(`${command} command sent successfully`);
      } else {
        console.error(`Failed to send ${command} command`);
      }
    } catch (error) {
      console.error(`Error sending ${command} command:`, error);
    }
  };

  return (
    <div>
      <h2 className="title">
        <img src={gifpokemon} alt="Loading" className="title-gif" />
        RoboSphere
      </h2>     
      <div style={{display: 'flex', justifyContent:'center'}}>
      <div className="set blue">
        <div className="d-pad">
          <a className="up" onClick={() => sendCommand('up')} href="#"/>
          <a className="right" onClick={() => sendCommand('right')} href="#"/>
          <a className="down" onClick={() => sendCommand('down')} href="#"/>
          <a className="left" onClick={() => sendCommand('left')} href="#"/>
        </div>
      </div>
      </div>
    </div>
  );



};

export default App;
