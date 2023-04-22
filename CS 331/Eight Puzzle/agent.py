from __future__ import annotations
from board import Board
from collections.abc import Callable
import copy

class BoardState:
    def __init__(self, board: Board, move: str, pastMoves):
        self.board = board

        if move != '':
            pastMoves.append(move)

        self.pastMoves = pastMoves

    def Seen(self, seenList):
        for string_outer_seen in seenList:
            for (string_inner_seen, new_str) in zip(string_outer_seen, self.pastMoves):
                if string_inner_seen != new_str:
                    print("has been!")
                    return True
        return False

'''
Heuristics
'''
def MT(board: Board) -> int:
    return 

def CB(board: Board) -> int:
    return 

def NA(board: Board) -> int:
    return 0



'''
A* Search 
'''
def a_star_search(board: Board, heuristic: Callable[[Board], int]):
    frontier = []
    seen = []
    newState = BoardState(board, "", []) # Initial state

    # While the board is not in a goal state
    while not newState.board.goal_test():
        for possibleMove in newState.board.next_action_states(): # Iterate over all possible moves
            newState = BoardState(possibleMove[0], possibleMove[1], newState.pastMoves) # Create a new board state for this move

            if not newState.Seen(seen): # Check if this string has been seen before
                frontier.append(newState)
                seen.append(newState.pastMoves)

        # Sort by the amount of moves + the heuristic func
        frontier.sort(key=(lambda a : len(a.pastMoves) + heuristic(a)))
        newState = frontier.pop(0)
        
    return newState.pastMoves
