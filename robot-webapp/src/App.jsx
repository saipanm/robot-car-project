import React, { useState } from 'react';
import axios from 'axios';
import './dpad.css';
import gifpokemon from './assets/4OKl.gif';
import VDO from './vdo';

const App = () => {
  const [commandStatus, setCommandStatus] = useState(''); // State to store the status message

  // Send control command to the robot
  const sendCommand = async (direction) => {
    try {
      const response = await axios.post(`http://192.168.137.77:1212/api/move`, {
        direction,
      });

      if (response.status === 200) {
        setCommandStatus(`Command '${direction}' sent successfully`);
        console.log(`Command '${direction}' sent successfully`);
      } else {
        setCommandStatus(`Failed to send command '${direction}'`);
        console.error(`Failed to send command '${direction}'`);
      }
    } catch (error) {
      setCommandStatus(`Error sending command '${direction}': ${error.message}`);
      console.error(`Error sending command '${direction}':`, error);
    }
  };

  return (
    <div>
      <h2 className="title">
        <img src={gifpokemon} alt="Loading" className="title-gif" />
        RoboSphere
      </h2>     
      <VDO />
      <div style={{ display: 'flex', justifyContent: 'center' }}>
        <div className="set blue">
          <div className="d-pad">
            <a className="up" onClick={() => sendCommand('forward')} href="#"></a>
            <a className="right" onClick={() => sendCommand('right')} href="#"></a>
            <a className="down" onClick={() => sendCommand('reverse')} href="#"></a>
            <a className="left" onClick={() => sendCommand('left')} href="#"></a>
          </div>
        </div>
      </div>
      {/* Display the command status below the D-pad */}
      <div className="command-status" style={{ textAlign: 'center', marginTop: '10px' }}>
        {commandStatus}
      </div>
      
    </div>
  );
};

export default App;
