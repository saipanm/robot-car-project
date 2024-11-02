#!/bin/bash
export FLASK_APP=robot_control_api.py  # Replace with your Flask app file name
export FLASK_ENV=production
gunicorn -w 4 -b 0.0.0.0:1212 robot_control_api:app  # Adjust port and workers as needed
