#pragma once

template <typename T>
class Node {
public:
    T val;
    Node* next;

    Node(T c_val) : val{ c_val } {};
};