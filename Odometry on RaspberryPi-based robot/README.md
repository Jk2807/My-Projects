# Odometry on RaspberryPi-based Robot Using ROS and Python


## Overview

This project presents the **design and implementation of an odometry module for a Raspberry Pi-based mobile robot** using ROS and Python.  
It was developed as part of the **Electronics System Lab** module project and applies core concepts from **robotics, embedded sensing, and mathematical modeling**.

The implementation demonstrates end-to-end system behavior including:

- ROS-based communication between robot components,
- real-time acquisition of motion sensor data, and
- position/orientation estimation using odometry equations.

A simple vector-based graph visualization is also included for coherent interpretation of robot movement.


## Project Information

- **Project Name:** Odometry on RaspberryPi-based robot  
- **Duration:** March 2026 – July 2026  
- **Type:** Module Project (Electronics System Lab)  
- **Role:** ROS network deployer, co-coder  
- **Inspiration / Learning Source:** Sensor integration and ROS-based robotics workflow in embedded systems


## Objectives

- Build a ROS network to transfer sensor readings, control commands, and system information between modules.
- Acquire and process data from **PMW3901 optical flow sensor** and **optical slot sensors**.
- Compute robot **position** and **orientation** using odometry and mathematical models.
- Provide a lightweight vector graph for intuitive trajectory and motion visualization.


## Key Concepts Used

- **ROS (Robot Operating System) communication architecture**
- **Python-based node development**
- **Odometry and kinematic estimation**
- **Sensor fusion / multi-sensor data handling**
- **Vector-based motion visualization**


## Features

- ROS topic-based data communication across sensing and control modules.
- Real-time processing pipeline for PMW3901 and optical slot sensor inputs.
- Mathematical estimation of displacement and heading angle.
- Simple vector graph output for coherent representation of movement path.
- Modular implementation for extension to navigation and control experiments.


## Tools and Environment

- **Python**
- **ROS2 Humble**
- **Raspberry Pi-based robot chassis**
- **PMW3901 sensor**
- **Optical slot sensors**


## External Video Demo

Videos for operation and abnormality demo, alongside the project can be found in the following Google Drive link:

- **[Google Drive Folder](https://drive.google.com/drive/folders/1nFWj1f0-TUXj9HnZ1L2tu5h1vtE7Omyi?usp=sharing)** 


## Learning Outcome

This project improved practical skills in ROS-based distributed robotic systems, real-time sensor integration, and odometry computation for mobile robots.  
It also strengthened understanding of how mathematical modeling and software architecture work together in embedded robotic platforms.


## Notes

This repository contains the implementation of ROS communication and odometry computation for a Raspberry Pi robot platform, intended as both a learning artifact and a baseline for further robotics experiments.
