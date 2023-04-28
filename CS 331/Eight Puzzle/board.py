from __future__ import annotations
from typing import List, Tuple, Union
import numpy as np
import random
import copy

# Dict of possible movement directions
moveset = {"right": (0, -1), "left": (0, 1), "up": (1, 0), "down": (-1, 0)}

class Board:
    def __init__(self, m: int, seed = None):
        self.open_space = (2, 2)
        self.solution = np.append(np.arange(1, 9, 1), 0).reshape((3, 3))
        self.state = np.copy(self.solution)
        if seed != None:
            random.seed(seed)
        self._shuffle(m)
        self.initial_state = np.copy(self.state)

    '''
    This function returns a list of tuples containing possible next states and the move direction that created that state
    '''
    def next_action_states(self) -> List[Tuple(Board,str)]:
        return [tuple([copy.deepcopy(self)._move(move), direction]) for move, direction in self._possible_moves()]

    '''
    This function resets the board to its intial state
    '''
    def reset_board(self) -> None:
        self.state = np.copy(self.initial_state)

    '''
    This function checks to see if the board is in the goal state and returns a bool
    '''
    def goal_test(self) -> bool:
        return str(self.state) == str(self.solution)

    '''
    This function allows you to check if a solution (list of directions) correctly solves the current board state 

    This function takes a list of strings that are in the set: ["right", "left", "up", "down"]
    '''
    def check_solution(self, solution: List[str]) -> bool:
        b = self
        for i in solution:
            p_moves = b.next_action_states()
            check = 0
            for m in p_moves:
                if i == m[1]:
                    b = m[0]
                    break
                else:
                    check = check + 1
            if check >= len(p_moves):
                return False
        return b.goal_test()
    

    '''
    A private function used to shuffle the board
    '''
    def _shuffle(self, m: int) -> np.ndarray:
        prev_move = 0
        for _ in range(0, m):
            move = random.choice(
                list(filter(lambda x: self.state[x[0]] != prev_move, self._possible_moves()))
            )
            prev_move = self.state[move[0]]
            self._move(move[0])

    '''
    A private function used to generate possible moves
    '''
    def _possible_moves(self) -> List[List[Tuple[int, int], str]]:
        return list(
            filter(
                lambda x: not any(i >= 3 or i < 0 for i in x[0]),
                [[tuple(sum(y) for y in zip(self.open_space, x)),z] for z, x in moveset.items()],
            )
        )

    '''
    A private function used to execute a move
    '''
    def _move(self, move: Tuple[int, int]) -> None:
        self.state = self._swap(self.open_space, move, self.state)
        self.open_space = move
        return self

    '''
    A private helper function for the move
    '''
    def _swap(self, open: Tuple[int, int], move: Tuple[int, int], state: np.ndarray) -> np.ndarray:
        state = np.copy(state)
        state[open], state[move] = state[move], state[open]
        return state

    '''
    This function makes str(Board) return a string representation of Board.state
    '''
    def __str__(self):
        return str(self.state)