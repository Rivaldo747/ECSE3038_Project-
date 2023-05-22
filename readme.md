To implement a IoT platform that controls basic appliances and allow user interaction through a webpage, 
you will need to set up the hardware and develop the necessary software components. 
How the setup of the project was carried out:

Hardware Setup:

Connect the Espressif ESP32 development module to the lamp and fan, ensuring proper electrical connections.
Connect a digital temperature sensor  to the ESP32 module to measure the room temperature.
Connect a passive infrared sensor to the ESP32 module to detect presence in the room.
S
oftware Setup:

Install the required libraries for ESP32 development using Python.
Set up the FastAPI Python framework to create the RESTful API. Install the necessary dependencies, such as FastAPI and Uvicorn, using pip.
Create a new Python file to implement the API endpoints and functionality.

Implementing the API:

Define the necessary API routes and their corresponding HTTP methods in the Python file
Implement the logic for each API endpoint based on the requirements mentioned.
Use appropriate libraries or APIs to fetch the sunset time based on the user's location.
Implement functions to control the lamps and fans connected to the ESP32 module.
Implement functions to read data from the temperature sensor and passive infrared sensor.
Implement the logic to combine the temperature-based control, time-based control, and presence detection features.
Implement an API endpoint to retrieve the most recent sensor readings for visualization on the webpage.

Webpage Integration:

Host the webpage that allows users to interact with the IoT devices remotely. Ensure it has the necessary input fields and buttons to control the appliances and display sensor data.
Make sure the webpage sends appropriate requests to your API endpoints based on user actions.


Testing:
when testing,
Test the functionality of your IoT platform by interacting with the webpage and verifying that the appliances respond as expected.
Test different scenarios, such as setting temperature and time-based controls, and observe the behavior of the appliances.

this lab overral wasnt bad, have a few hiccups with connectin to render but the functionality of the app should work.

