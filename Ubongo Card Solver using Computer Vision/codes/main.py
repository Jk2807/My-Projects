from pathlib import Path

import numpy as np
import cv2 as cv
import sys
from ImgPro import *
from solver import *

DebugMode = True

FIXEDWIDTH = 400
FIXEDHEIGHT = 600

#1. Static images
# IMAGE = Path("Images/yellow_tilted.jpeg")

kernel = np.array([[ 0, -1,  0],
                   [-1,  5, -1],
                   [ 0, -1,  0]])

# Open the default camera
# My camera ID = 4
cam = cv.VideoCapture(1)

# Get the default frame width and height
width = int(cam.get(cv.CAP_PROP_FRAME_WIDTH))
height = int(cam.get(cv.CAP_PROP_FRAME_HEIGHT))


while True:
    ret, frame = cam.read()
    try:

        lab = cv.cvtColor(frame, cv.COLOR_BGR2LAB)
        l_channel, a, b = cv.split(lab)

        # Apply CLAHE to the L-channel
        clahe = cv.createCLAHE(clipLimit=2.0, tileGridSize=(8, 8))
        cl = clahe.apply(l_channel)

        # Merge the channels back together
        merged = cv.merge((cl, a, b))

        # Convert back to BGR
        img = cv.cvtColor(merged, cv.COLOR_LAB2BGR)


        #print out the image
        if img is None:
            sys.exit("Could not read the image.")

        if (width > height):
            img = cv.rotate(img, cv.ROTATE_90_CLOCKWISE)
            width, height = height, width

        if DebugMode == True:
            # Perpendicular perspective Transformation
            source_window = 'Source'
            cv.imshow(source_window, img)

        Card = Perpendicular(img, width, height)
        if DebugMode == True:
            cv.imshow('Original Card', Card)
        Card = cv.resize(Card, (int(FIXEDWIDTH), int(FIXEDHEIGHT)))

        # SANDBOX!!!!!

        PiecesImg, PuzzleImg = CardCut(Card)

        if DebugMode == True:
            cv.imshow('Pieces', PiecesImg)
            cv.imshow('Puzzle', PuzzleImg)

        # Represent the puzzle as a matrix
        PuzzleMat = GetPuzzle(PuzzleImg)

        print(PuzzleMat)

        # ------------------------------------ Solver Part -----------------------------------------------


        # Count number of white area (represented by 1s)
        total_field_blocks = int(np.sum(PuzzleMat == 1))

        # Use pieces' shape and total play area for approximation
        extracted_pieces = process_pieces_image(PiecesImg, total_field_blocks)

        if len(extracted_pieces) > 0:
            solve_ubongo(PuzzleMat, extracted_pieces)
    except:
        print("PROCESS FAILED! RETRYING...")
        k = cv.waitKey(100)
        continue
    # -----------------------------------------
    # k = cv.waitKey(0)

