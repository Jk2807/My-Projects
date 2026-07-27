# Ubongo Card Solver using Computer Vision

## Overview

This project presents a **real-time computer vision system** that detects and processes **Ubongo playing cards** using Python and OpenCV.  
It was developed as part of the **Image Processing 2** module project and combines practical image analysis with algorithmic puzzle solving.

The implementation supports two operation modes:

- detection from a **single image**, and
- detection from a **continuous camera stream**.

After card/puzzle detection, the program maps the layout digitally and applies a **backtracking-based solver** to compute valid puzzle solutions automatically.


## Project Information

- **Project Name:** Ubongo Card Solver using Computer Vision  
- **Duration:** March 2026 – July 2026  
- **Type:** Module Project (Image Processing 2)  
- **Role:** Lead Coder


## Objectives

- Build a robust computer vision pipeline for Ubongo card/puzzle detection.
- Support both static-image and live-camera input workflows.
- Convert visual puzzle data into a structured digital representation.
- Solve mapped puzzle layouts automatically using a backtracking algorithm.


## Key Concepts Used

- **Computer Vision with OpenCV**
- **Real-time frame processing**
- **Image preprocessing and feature extraction**
- **Puzzle state mapping**
- **Backtracking algorithm for constraint-based solving**


## Features

- Two operation modes:
  - **Single Image Mode** (process one image input)
  - **Live Camera Mode** (continuous stream detection)
- Compatible with external camera input (e.g., **Logitech G920/C920**).
- Automatic puzzle layout interpretation from detected card data.
- Backtracking-based automatic solver for valid arrangement generation.
- Modular Python structure for testing and future extension.


## Tools and Environment

- **Python**
- **OpenCV (cv2)**
- Standard scientific/programming Python workflow for image-processing tasks


## Learning Outcome

This project strengthened practical understanding of real-time image processing pipelines, camera-based detection workflows, and the integration of classical algorithms (backtracking) with computer vision systems to solve structured puzzles automatically.


## How to Run

For setup steps, dependencies, and execution instructions, please refer to:

**`HowtoRun`**


## Notes

This project is intended as both a functional puzzle-solving system and a learning-focused implementation that demonstrates the bridge between computer vision and algorithmic problem solving.
