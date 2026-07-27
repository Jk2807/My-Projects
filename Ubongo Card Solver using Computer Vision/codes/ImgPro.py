import cv2 as cv
import numpy as np
import random as rd
from matplotlib import pyplot as plt
import math

# average taken from blue.jpeg
RefAvgPi =  58.58403333333333
RefAvgPu =  88.80224444444445

FIXEDWIDTH = 400
FIXEDHEIGHT = 600
DebugMode = True
CANNY_THRESH = 115


def ContourDraw(width, height, contours):

    rd.seed(1384)

    # Get the moments
    mu = [None] * len(contours)
    for i in range(len(contours)):
        mu[i] = cv.moments(contours[i])
    # Get the mass centers
    mc = [None] * len(contours)
    for i in range(len(contours)):
        # add 1e-5 to avoid division by zeroRefAvgPi
        mc[i] = (mu[i]['m10'] / (mu[i]['m00'] + 1e-5), mu[i]['m01'] / (mu[i]['m00'] + 1e-5))
    ret = np.zeros((height, width, 3), dtype=np.uint8)
    for i in range(len(contours)):
        cv.drawContours(ret, contours, i, (rd.randrange(0, 255), rd.randrange(0, 255), rd.randrange(0, 255)), 2)
        cv.circle(ret, (int(mc[i][0]), int(mc[i][1])), 4, (rd.randrange(0, 255), rd.randrange(0, 255), rd.randrange(0, 255)), -1)

    # Print all contours
    # print("-------------------------------------")
    # for i in range(len(contours)):
    #     print(' * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f' % (i, mu[i]['m00'],
    #                                                                                       cv.contourArea(contours[i]),
    #                                                                                       cv.arcLength(contours[i],
    #                                                                                                    True)))

    return ret

def Perpendicular(col, width, height):
    grey = cv.cvtColor(col, cv.COLOR_BGR2GRAY)
    canny_output = cv.Canny(grey, CANNY_THRESH, CANNY_THRESH * 2)
    # Return pair: (Contours, Hierarchy)
    contours,_ = cv.findContours(canny_output, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)


    # POLYGON APPROXIMATION (GEMINI)-----------------------------------------------------------------------------------------------------------------
    # Calculate the perimeter (arc length)
    CardBound = contours[0]
    for i in range(len(contours)):
        if cv.contourArea(CardBound) < cv.contourArea(contours[i]): CardBound = contours[i]
    perimeter = cv.arcLength(CardBound, True)

    # Approximate the contour to a polygon
    # The epsilon (0.02 * perimeter) determines the precision
    epsilon = 0.02 * perimeter
    approx = cv.approxPolyDP(CardBound, epsilon, True)

    # Check if the approximated polygon has 4 vertices
    if len(approx) == 4:
        corners = approx.reshape(4, 2)
    else:
        print("Cannot approximate")
        return -1


    # Draw contours
    if DebugMode == True:
        drawing = ContourDraw(width, height,  contours)
        drawing = cv.circle(drawing, (corners[0][0], corners[0][1]), 1, (0, 0, 255), 5)
        drawing = cv.circle(drawing, (corners[1][0], corners[1][1]), 1, (0, 0, 255), 5)
        drawing = cv.circle(drawing, (corners[2][0], corners[2][1]), 1, (0, 0, 255), 5)
        drawing = cv.circle(drawing, (corners[3][0], corners[3][1]), 1, (0, 0, 255), 5)
        cv.imshow('Card Contour Points', drawing)
    # -----------------------------------------------------------------------------------------------------------------------------------------------
    # print(corners)

    rect = np.zeros((4, 2), dtype="float32")

    # New Method: Pick one corner, find the distance to other corners: closest->short vertice; furthest->diag
    dist_list = [np.sqrt((corners[0][0] - corners[i][0]) ** 2 + (corners[0][1] - corners[i][1]) ** 2) for i in range(1, 4)]

    dist_arr = np.array(dist_list)
    sorted_indices = dist_arr.argsort()
    # print(sorted_indices)

    rect[0] = corners[0]
    rect[1] = corners[sorted_indices[0] + 1]
    rect[2] = corners[sorted_indices[2] + 1]
    rect[3] = corners[sorted_indices[1] + 1]

    # # Old Method
    # s = corners.sum(axis=1)
    # rect[0] = corners[np.argmin(s)]
    # rect[2] = corners[np.argmax(s)]
    #
    # # 2. Difference of coordinates (y-x)
    # # Top-Right has smallest difference; Bottom-Left has largest difference
    # diff = np.diff(corners, axis=1)
    # rect[1] = corners[np.argmin(diff)]
    # rect[3] = corners[np.argmax(diff)]
    #
    # # drawing = cv.circle(drawing, (CardBound[2] + CardBound[0], CardBound[3] + CardBound[1]), 1, (0, 0, 255), 5)
    #
    # print("Old Method = ", rect)


    pts1 = np.array(rect).reshape(4, 2).astype(np.float32)
    pts2 = np.float32([[0, 0], [width, 0], [width, height], [0, height]])

    M = cv.getPerspectiveTransform(pts1, pts2)

    return cv.warpPerspective(col, M, (width, height))

def CardCut(img):
    # Sensor noise (pepper noise) removal
    img = cv.fastNlMeansDenoisingColored(img, None, 10, 10, 7, 21)

    # Analyse the histogram of the top 25% and the bottom 25%
    height, width, _ = img.shape
    imgGray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
    top25_1D = imgGray[0:int(25 * height / 100), :].ravel()
    bot25_1D = imgGray[int(75 * height / 100):, :].ravel()

    # Draw Plot()
    # if DebugMode == True:
    #     plt.hist(bot25_1D, 256, [0, 256])
    #     plt.title('bottom 25%')
    #     plt.show()
    #     plt.hist(top25_1D, 256, [0, 256])
    #     plt.title('top 25%')
    #     plt.show()


    # black_thres = 50    #Theshold for defining black pixels
    # countsTop, _ = np.histogram(top25_1D, bins=256, range=(0, 256))
    # countsTop = countsTop[:black_thres]
    # countsBot, _ = np.histogram(bot25_1D, bins=256, range=(0, 256))
    # countsBot = countsBot[:black_thres]

    # print(np.mean(top25_1D) , " ", np.mean(bot25_1D))
    if np.mean(top25_1D) > np.mean(bot25_1D):
        img = cv.flip(img, 0)
        # imgGray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
        print("Flipped")

    pieces = img[0:int(25 * height / 100), :]
    puzzle = img[int(25 * height / 100):, :]


    return pieces, puzzle


    # Push the saturation of the images to the taken reference

    piecesHsv = cv.cvtColor(pieces, cv.COLOR_BGR2HSV)
    puzzleHsv = cv.cvtColor(puzzle, cv.COLOR_BGR2HSV)

    piecesMultiplier = RefAvgPi/np.mean(piecesHsv[:, :, 2])
    puzzleMultiplier = RefAvgPu/np.mean(puzzleHsv[:, :, 2])

    new_pieces_V = np.clip(piecesHsv[:, :, 2] * piecesMultiplier, 0, 255)
    new_puzzle_V = np.clip(puzzleHsv[:, :, 2] * puzzleMultiplier, 0, 255)

    piecesHsv[:, :, 2] = new_pieces_V
    puzzleHsv[:, :, 2] = new_puzzle_V

    piecesHsv = np.array(piecesHsv, dtype=np.uint8)
    puzzleHsv = np.array(puzzleHsv, dtype=np.uint8)


    retPi = cv.cvtColor(piecesHsv, cv.COLOR_HSV2BGR)
    retPu = cv.cvtColor(puzzleHsv, cv.COLOR_HSV2BGR)

    return retPi, retPu
    # return pieces, puzzle


# WORK IN PROGRESS ---------------------------------------------------------------------------------------------------
def GetPuzzle(img):
    sat_thres = 50
    erIt = 6            #Number of erosion using a 3x3 kernel

    h, w, _ = img.shape


    # Method: Static Threshold
    imgHSV = cv.cvtColor(img, cv.COLOR_BGR2HSV)
    # Use pixel saturation to check for white pixels
    thres_mask = imgHSV[:, :, 1] > sat_thres
    whitepix = img.copy()

    # set the color to black everywhere the saturation is above the threshold
    whitepix[thres_mask] = (0, 0, 0)
    # whitepix = cv.medianBlur(whitepix, 5)
    whitepix = cv.cvtColor(whitepix, cv.COLOR_BGR2GRAY)
    ret, whitepix = cv.threshold(whitepix, 127, 255, cv.THRESH_BINARY)
    if DebugMode == True:
        cv.imshow('uneroded', whitepix)
    # -------------------------------------------------------

    kernel = np.ones((3, 3), np.uint8)
    separated_img = cv.erode(whitepix, kernel, iterations=erIt)

    # 2. Apply the Opening operation
    separated_img = cv.morphologyEx(separated_img, cv.MORPH_OPEN, kernel)

    #---------------------------------------------------------------------------------

    if DebugMode == True:
        cv.imshow('separated puzzle', separated_img)

    # Find contours
    canny_output = cv.Canny(separated_img, CANNY_THRESH, CANNY_THRESH * 2)
    contours, _ = cv.findContours(canny_output, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)

    # Filter out fragments
    contours = [i for i in contours if cv.contourArea(i) > 100]

    ret = np.zeros((5, 5))

    # Get the center and rotation for each square
    try:
        boxes = [cv.minAreaRect(b) for b in contours]
        minx = int(min(b[0][0] for b in boxes))
        miny = int(min(b[0][1] for b in boxes))
        meanbw = int(round(np.mean([b[1][0] for b in boxes])))
        meanbh = int(round(np.mean([b[1][1] for b in boxes])))
    except:
        print("Cannot get each square in Puzzle")
        return -1

    if DebugMode == True:
        print("Origin coordinate: ", minx, "-", miny)
    for b in boxes:
        (x, y), (bw, bh), _ = b

        # Erode x7 and dialate x1 --> remove 6 layers from each side --> reduce 12 pixels in distance
        sqDist = erIt*2

        if DebugMode == True:
            print(b)
            print(int(round((x-minx)/(meanbw+sqDist))), " ", int(round((y - miny) / (meanbh+sqDist))))
        try:
            ret[int(round((y - miny) / (meanbh+sqDist)))][int(round((x - minx) / (meanbw+sqDist)))] = 1
        except:
            print("COORDINATE MAPPING ERROR")

    if DebugMode == True:
        ImgCon = ContourDraw(w, h, contours)
        ImgCon = cv.circle(ImgCon, (minx,miny), radius=3, color=(255, 255, 255), thickness=3)
        cv.imshow('Puzzle Contours', ImgCon)
    return ret

#-----------------------------------------------------------------------------------------------------------------------
def show_matrix_as_image(title, matrix):
    """
    Converts a 0-1 matrix into a colorful image and shows it in a window.
    Green = Piece, Gray = Empty.
    """
    cell_size = 40
    h, w = matrix.shape
    # Create background
    vis = np.zeros((h * cell_size, w * cell_size, 3), dtype=np.uint8)

    for r in range(h):
        for c in range(w):
            color = (0, 255, 0) if matrix[r, c] == 1 else (50, 50, 50)
            top_left = (c * cell_size, r * cell_size)
            bottom_right = ((c + 1) * cell_size, (r + 1) * cell_size)
            cv.rectangle(vis, top_left, bottom_right, color, -1)
            cv.rectangle(vis, top_left, bottom_right, (0, 0, 0), 1)  # border

    if DebugMode == True:
        cv.imshow(title, vis)


def reconstruct_grid(piece_meta, thresh_img):
    """
    Improved Phase 3: Piece Grid Reconstruction with individual windows.
    """
    x, y, w, h = piece_meta["bbox"]
    est_blocks = piece_meta["blocks"]
    ar = piece_meta["aspect_ratio"]

    # 1. Best fit grid guess
    best_grid = (1, 1)
    min_diff = float('inf')

    # list of potential dimension sets
    canidates = []

    for cols in range(1, 6):
        for rows in range(1, 6):
            if cols * rows >= est_blocks:
                diff = abs((cols / rows) - ar)
                dim = (cols, rows)
                canidates.append((diff, dim))
                # if diff < min_diff:
                #     min_diff, best_grid = diff, (cols, rows)

    # sort the canidate list by ascending difference
    canidates.sort()

    # _, col, rows = canidates[0]


    #----------------------------Construction in progress------------------------------
    for can in canidates:
        (_, (cols, rows)) = can

        #----------------------------------------------------------------------------------
        # cols, rows = best_grid
        matrix = np.zeros((rows, cols), dtype=np.int8)
        cell_w, cell_h = w / float(cols), h / float(rows)
        piece_patch = thresh_img[y:y + h, x:x + w]

        cnt = 0

        # 2. Density Sampling
        for r in range(rows):
            for c in range(cols):
                cell = piece_patch[int(r * cell_h):int((r + 1) * cell_h), int(c * cell_w):int((c + 1) * cell_w)]
                if cell.size > 0 and cv.countNonZero(cell) > 0.3 * cell.size:
                    matrix[r, c] = 1
                    cnt += 1
        if cnt != est_blocks: continue

        # 3. Clean empty boundaries
        matrix = matrix[~np.all(matrix == 0, axis=1)]
        matrix = matrix[:, ~np.all(matrix == 0, axis=0)]

        # 4. SHOW INDIVIDUAL WINDOW
        show_matrix_as_image(f"Piece {piece_meta['id']} Structure", matrix)

        return matrix

    return -1

def process_pieces_image(pieces_img, total_field_blocks):
    """
    Real-time ready Piece Analysis: Auto-Adaptive Canny Edge Detection + Morphological Masking.
    Immune to lighting changes, shadows, and background camouflage.
    """
    print("\n--- DYNAMIC PIECE ANALYSIS (REAL-TIME MODE) ---")
    print(f"Total blocks required by the field (Checksum): {total_field_blocks}")

    # 1. Grayscale
    gray = cv.cvtColor(pieces_img, cv.COLOR_BGR2GRAY)

    # 2. Aggressive Blur (Webcam noise killer)
    blurred = cv.GaussianBlur(gray, (7, 7), 0)

    # 3. AUTO-ADAPTIVE CANNY (Crucial for changing light)
    v = np.median(blurred)
    sigma = 0.33
    lower = int(max(0, (1.0 - sigma) * v))
    upper = int(min(255, (1.0 + sigma) * v))
    edges = cv.Canny(blurred, lower, upper)

    # 4. Morphological Closing
    kernel = np.ones((5, 5), np.uint8)
    closed_edges = cv.morphologyEx(edges, cv.MORPH_CLOSE, kernel)

    # 5. Extract Contours
    contours, _ = cv.findContours(closed_edges, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)

    # 6. Strict Filtering remove irrelevant objects
    valid_contours = []
    for c in contours:
        area = cv.contourArea(c)
        if 1000 < area < 25000:
            valid_contours.append(c)

    # Calculate the total area of the pieces
    total_area = sum(cv.contourArea(c) for c in valid_contours)

    if total_area == 0:
        print("Error: No valid pieces detected in real-time constraints!")
        # Debug live feed
        if DebugMode == True:
            cv.imshow("Debug Edges", closed_edges)
        cv.waitKey(200)
        return []

    # 7. Create Solid Mask for Grid Reconstruction
    solid_mask = np.zeros_like(gray)
    cv.drawContours(solid_mask, valid_contours, -1, 255, thickness=cv.FILLED)

    output_img = pieces_img.copy()
    pieces_metadata = []

    print("total_area = ", total_area)

    # 8. Analyze Area Ratio & Extract Math
    for i, c in enumerate(valid_contours):
        area = cv.contourArea(c)
        ratio = area / total_area
        estimated_blocks = int(round(total_field_blocks * ratio))
        print("Estimated blocks for piece ", i," = ", estimated_blocks)

        if estimated_blocks == 0:
            estimated_blocks = 1

        x, y, w, h = cv.boundingRect(c)
        aspect_ratio = w / float(h)

        pieces_metadata.append({
            "id": i + 1,
            "blocks": estimated_blocks,
            "aspect_ratio": aspect_ratio,
            "bbox": (x, y, w, h),
            "contour": c
        })
        if DebugMode == True:
            # Visualization
            cv.drawContours(output_img, [c], -1, (0, 255, 0), 2)
            cv.rectangle(output_img, (x, y), (x + w, y + h), (0, 0, 255), 2)
            info_text = f"P{i + 1}: {estimated_blocks} blks | AR: {aspect_ratio:.1f}"
            cv.putText(output_img, info_text, (x, y - 10), cv.FONT_HERSHEY_SIMPLEX, 0.4, (0, 255, 0), 1)
            print(
                f"Piece {i + 1}: Area={area:.1f}px, Ratio={ratio:.2f}, Est. Blocks={estimated_blocks}, AR={aspect_ratio:.2f}")

    if DebugMode == True:
        cv.imshow("Dynamic Piece Analysis", output_img)
        cv.imshow("Solid Mask", solid_mask)
        cv.waitKey(200)

    extracted_matrices = []
    print("\n--- PHASE 3: GRID RECONSTRUCTION ---")

    for meta in pieces_metadata:
        mat = reconstruct_grid(meta, solid_mask)
        extracted_matrices.append(mat)
        print(f"Piece {meta['id']} Matrix ({mat.shape[1]}x{mat.shape[0]}):")
        print(mat)
        print("-" * 20)

    return extracted_matrices