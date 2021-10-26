# Arduino + Python Password Manager  
Small project made for ELEN30013, 2021
## Setup  
0. Ensure that:  
- the Arduino is connected to the computer, and the code (pwtest.ino) has been uploaded to the board
- Python is installed (tested on Python 3.8+)  
- tk is installed (should be preinstalled for Windows, some Linux distros (and possibly Macs) will need to install tk, which can be done through a package manager)  
1. Install Python module requirements. In a command prompt / terminal, run:  
`python -m pip install -r requirements.txt`  
2. Run the Python script  
`python pw.py`  
3. Specify the correct serial port (type exactly as it appears in the Arduino IDE - usually has COM on Windows, and /dev/ttyUSB for Macs/Linux)  
