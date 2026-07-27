# Facial Emotion Recognition Using Deep Learning

## Overview

This project focuses on the development of a Deep Learning model to classify facial emotions using the FER-2013 dataset. 
It addresses significant challenges associated with imbalanced and noisy data, as well as hardware constraints (such as Google Colab session limits). To maximize performance and efficiency, the project evolved from a custom Convolutional Neural Network (CNN) architecture to a Transfer Learning approach utilizing VGG-19.


## Project Information

- **Project Name:** Facial Emotion Classification
- **Duration:** March 2026 – July 2026
- **Type:** Module Project (Intelligent Systems) - Group 1
- **Role:** Lead Coder
- **Dataset:** FER-2013 (Kaggle)


## Objectives

- Design a Deep Learning model that accurately classifies images according to facial emotions.
- Achieve a target validation accuracy of 70-80% on the FER-2013 dataset.
- Mitigate the effects of a noisy and unbalanced dataset (e.g., sacrificing the heavily underrepresented 'disgust' class to improve overall performance).


## Key Concepts Used

- Convolutional Neural Networks (CNN)
- Transfer Learning (VGG-19, ConvNeXt-Tiny)
- Image Preprocessing and Data Augmentation
- Multi-phase Training (Layer freezing/unfreezing)
- Dynamic Learning Rate Adjustments and Early Stopping


## Features

- **Custom CNN Prototypes:** Initial exploration using custom multi-layer CNNs with varying batch sizes, Batch Normalization, and Dropout to establish a baseline.
- **Transfer Learning Implementations:** Transitioned to VGG-19 after encountering resolution and scaling issues with ConvNeXt-Tiny.
- **Advanced Data Handling:** Implemented online data augmentation (rotation, shifting, shearing, zooming, and horizontal flipping) and class balancing to improve model robustness.
- **Strategic Fine-Tuning:** Executed a 3-phase training strategy:
  1. Train classification head with a frozen VGG-19 base.
  2. Unfreeze Block 5 with a reduced learning rate.
  3. Fully unfreeze the model with a minimal learning rate.
- **Performance Optimization:** Integrated `ReduceLROnPlateau` and `EarlyStopping` callbacks to prevent severe overfitting.


## Tools and Environment

- **Frameworks & Libraries:** TensorFlow, Keras, OpenCV, NumPy, Matplotlib
- **Environment:** Google Colab


## Future Plans

- Experiment with K-fold cross-validation to further validate model robustness.
- Expand testing to alternative, cleaner datasets such as AffectNet or RAF-DB.
- Explore PyTorch and Hugging Face models for future transfer learning applications.
