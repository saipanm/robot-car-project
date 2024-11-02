import React from 'react';
import './dpad.css';

function App() {
  // Define handler functions for each direction
  const handleMove = (direction) => {
    console.log(`Moving ${direction}`);
    // You can add any code here to send the direction to your backend or robot control API
  };

  return (
    <div >
      <h1 style={{display: 'flex', flexDirection: 'row', justifyContent: 'center'}}>Robot Webapp</h1>
      <div className="set blue">
        <div className="d-pad">
          <a className="up" onClick={() => handleMove('up')} href="#"/>
          <a className="right" onClick={() => handleMove('right')} href="#"/>
          <a className="down" onClick={() => handleMove('down')} href="#"/>
          <a className="left" onClick={() => handleMove('left')} href="#"/>
         
        </div>
      </div>
    </div>
  );
}

export default App;
