# Quoc An Nguyen | Electrical & Computer Engineering

Welcome to my university projects repository! I am a third-year Electrical and Computer Engineering student, currently studying at Vietnamese-German University (VGU). My passion lies at the intersection of embedded systems, wireless communications, and machine learning. I enjoy taking a hands-on approach to hardware-software integration, whether that's tuning control nodes for robotics, building deep learning models, or optimizing low-level system architectures. 

Below is an overview of the key academic projects I have developed and documented in this repository:

## 📁 Projects Overview

### **[Simulation and Evaluation of OFDM MIMO System Using MATLAB](./Simulation%20and%20evaluation%20of%20an%20OFDM%20MIMO%20System)**

A MATLAB-based communication systems project that simulates and evaluates a 2×2 MIMO-OFDM transmission chain. The implementation focuses on step-by-step signal processing, including data encoding, OFDM modulation/demodulation, transmission channel simulation using a MIMO channel, channel estimation with pilot signals using 2D spline interpolation, and data equalization.

### **[Odometry on RaspberryPi-based Robot Using ROS and Python](./Odometry%20on%20RaspberryPi-based%20robot)**
A robotics and embedded systems project that implements an odometry module for a Raspberry Pi-based mobile robot using ROS 2 and Python. The project integrates motion sensors (PMW3901 optical flow sensor and infrared slot wheel encoders), computes position and orientation (yaw angle) using differential kinematics and coordinate transformation matrices, and implements sensor cross-correction to discard erroneous encoder readings during instances of physical obstruction or wheel slip.

### **[Application of the FFT - Noise Filtering](FFT%20and%20Applications)**
A Digital Signal Processing project that explores the theory and practical applications of the Fast Fourier Transform in MATLAB. The project demonstrates FFT-based signal analysis through two use cases: Heartbeat sensing and Audio noise filtering, using a threshold-based denoising algorithm.

### **[8-bit Computer](./8-bit%20Computer)**
A breadboard-based digital system design project that builds an 8-bit computer using discrete IC chips. Inspired by Ben Eater’s educational computer architecture, this project explores clocking, registers, RAM, and CPU cycles, which were fully designed and simulated in Proteus 8 before physical circuit implementation.

### **[Ubongo Card Solver using Computer Vision](Ubongo%20Card%20Solver%20using%20Computer%20Vision)**
A computer vision project developed in Python and OpenCV for detecting and processing Ubongo cards from either a single image or a live camera stream. After detection, the system applies dynamic CLAHE histogram equalization, perspective transformation, thresholding, and morphological operations to extract the puzzle fields and pieces. Finally, a recursive backtracking algorithm finds the exact placement and orientation to automatically solve the digitally mapped puzzle layouts.

### **[Wild West Shootout Game](Wild-West-Shootout%20Game)**
A console-based C game project created as part of an introductory programming course, developed entirely in Microsoft Visual Studio using Raylib for graphics and interface. The project demonstrates beginner programming concepts such as control flow, random number generation, input/output processing, and features a turn-based 2-player mechanism loosely inspired by Russian Roulette with custom player skills and a leaderboard that records win streaks.

### **[Electrical Components Classification & Identification](Electrical%20components%20classification%20&%20identification)**
An embedded AI project that uses ESP32-CAM and Edge Impulse for real-time electrical component detection and classification. The system combines computer vision (using a MobileNetV2-based FOMO model), edge inference, and object-oriented programming principles in C++ to handle storage management (with a comprehensive warehouse map layout) and an interactive checkout billing system.

## 💻 Tech Stack & Tools
* **Languages:** Python, MATLAB, C/C++
* **Machine Learning & Data:** TensorFlow, Keras
* **Robotics & Hardware:** ROS 2, KiCad, Raspberry Pi
* **Systems:** Linux (Ubuntu/Zsh), Git

*Feel free to explore the individual project directories for source code, setup instructions, and detailed technical documentation!*
