import numpy as np
import cv2 as cv

DebugMode = True

# ----------------------bruteforce and print out result----------------------
def show_progress(board):
    """
    Convert the number matrix into a color image to display in a window.
    """
    cell_size = 50  # Each cell is 50x50 pixels
    h, w = board.shape
    img = np.zeros((h * cell_size, w * cell_size, 3), dtype=np.uint8)

    # Define colors in BGR format
    colors = {
        0: (50, 50, 50),  # 0: Wall (Dark Gray)
        1: (255, 255, 255),  # 1: Empty Space (White)
        2: (0, 0, 255),  # 2: Piece 1 (Red)
        3: (0, 255, 0),  # 3: Piece 2 (Green)
        4: (255, 0, 0)  # 4: Piece 3 (Blue)
    }

    # Draw each cell on the image
    for r in range(h):
        for c in range(w):
            val = int(board[r, c])
            color = colors.get(val, (0, 255, 255))  # Default to Yellow for unknown pieces

            # Calculate coordinates and draw rectangles
            top_left = (c * cell_size, r * cell_size)
            bottom_right = (c * cell_size + cell_size, r * cell_size + cell_size)
            cv.rectangle(img, top_left, bottom_right, color, -1)
            cv.rectangle(img, top_left, bottom_right, (0, 0, 0), 1)  # Black border

    if DebugMode == True:
        cv.imshow("Solver Progress", img)
    # cv.waitKey(200)  # Pause for 200ms to visualize the process


def get_variations(piece):
    """ Generate all unique rotated and flipped variations of a piece """
    variations = []
    for p in [piece, np.fliplr(piece)]:
        for i in range(4):
            rotated = np.rot90(p, i)
            if not any(np.array_equal(rotated, v) for v in variations):
                variations.append(rotated)
    return variations


def solve_recursive(board, pieces, piece_id):
    """ Simplified Core Backtracking Algorithm """
    # WIN CONDITION: No empty spaces (1s) left
    if not np.any(board == 1):
        return True

    # Take the first available piece
    piece = pieces[0]
    remaining_pieces = pieces[1:]

    # Try all variations of this piece
    for var in get_variations(piece):
        ph, pw = var.shape

        # Scan the board coordinates
        for r in range(board.shape[0] - ph + 1):
            for c in range(board.shape[1] - pw + 1):

                # Extract the board section
                board_section = board[r:r + ph, c:c + pw]

                # Check if the piece fits perfectly into empty spaces
                if np.all((var == 1) <= (board_section == 1)):

                    # STEP A: Place the piece
                    board_section[var == 1] = piece_id
                    show_progress(board)  # UPDATE UI

                    # STEP B: Move forward with remaining pieces
                    if solve_recursive(board, remaining_pieces, piece_id + 1):
                        return True

                    # STEP C: Backtrack (remove the piece)
                    board_section[var == 1] = 1
                    show_progress(board)  # UPDATE UI

    return False  # Failed to place the piece


def solve_ubongo(board_matrix, pieces_list):
    """ Main function to start the solver """
    board_copy = board_matrix.copy()

    # Show initial state
    show_progress(board_copy)
    cv.waitKey(1000)  # Wait 1 second before starting

    if solve_recursive(board_copy, pieces_list, piece_id=2):
        print("\nSUCCESS! Puzzle solved!")
        k = cv.waitKey(0)
    else:
        print("\nFAILED! Cannot solve the puzzle.")
    return True
